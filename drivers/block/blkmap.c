// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 Addiva Elektronik
 * Author: Tobias Waldekranz <tobias@waldekranz.com>
 */

#include <common.h>
#include <blk.h>
#include <blkmap.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/root.h>
#include <malloc.h>
#include <mapmem.h>
#include <part.h>

struct blkmap;

struct blkmap_slice {
	struct list_head node;

	lbaint_t blknr;
	lbaint_t blkcnt;

	ulong (*read)(struct blkmap *bm, struct blkmap_slice *bms,
		      lbaint_t blknr, lbaint_t blkcnt, void *buffer);
	ulong (*write)(struct blkmap *bm, struct blkmap_slice *bms,
		       lbaint_t blknr, lbaint_t blkcnt, const void *buffer);
	void (*destroy)(struct blkmap *bm, struct blkmap_slice *bms);
};

struct blkmap {
	char *label;
	struct blk_desc *bd;
	struct list_head slices;
};

static bool blkmap_slice_contains(struct blkmap_slice *bms, lbaint_t blknr)
{
	return (blknr >= bms->blknr) && (blknr < (bms->blknr + bms->blkcnt));
}

static bool blkmap_slice_available(struct blkmap *bm, struct blkmap_slice *new)
{
	struct blkmap_slice *bms;
	lbaint_t first, last;

	first = new->blknr;
	last = new->blknr + new->blkcnt - 1;

	list_for_each_entry(bms, &bm->slices, node) {
		if (blkmap_slice_contains(bms, first) ||
		    blkmap_slice_contains(bms, last) ||
		    blkmap_slice_contains(new, bms->blknr) ||
		    blkmap_slice_contains(new, bms->blknr + bms->blkcnt - 1))
			return false;
	}

	return true;
}

static int blkmap_add(struct blkmap *bm, struct blkmap_slice *new)
{
	struct list_head *insert = &bm->slices;
	struct blkmap_slice *bms;

	if (!blkmap_slice_available(bm, new))
		return -EBUSY;

	list_for_each_entry(bms, &bm->slices, node) {
		if (bms->blknr < new->blknr)
			continue;

		insert = &bms->node;
		break;
	}

	list_add_tail(&new->node, insert);

	/* Disk might have grown, update the size */
	bms = list_last_entry(&bm->slices, struct blkmap_slice, node);
	bm->bd->lba = bms->blknr + bms->blkcnt;
	return 0;
}

struct blkmap_linear {
	struct blkmap_slice slice;

	struct blk_desc *bd;
	lbaint_t blknr;
};

static ulong blkmap_linear_read(struct blkmap *bm, struct blkmap_slice *bms,
				lbaint_t blknr, lbaint_t blkcnt, void *buffer)
{
	struct blkmap_linear *bml = container_of(bms, struct blkmap_linear, slice);

	return blk_dread(bml->bd, bml->blknr + blknr, blkcnt, buffer);
}

static ulong blkmap_linear_write(struct blkmap *bm, struct blkmap_slice *bms,
				 lbaint_t blknr, lbaint_t blkcnt,
				 const void *buffer)
{
	struct blkmap_linear *bml = container_of(bms, struct blkmap_linear, slice);

	return blk_dwrite(bml->bd, bml->blknr + blknr, blkcnt, buffer);
}

int blkmap_map_linear(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		      enum uclass_id lcls, int ldevnum, lbaint_t lblknr)
{
	struct blkmap *bm = dev_get_plat(dev);
	struct blkmap_linear *linear;
	struct blk_desc *lbd;
	int err;

	lbd = blk_get_devnum_by_uclass_id(lcls, ldevnum);
	if (!lbd)
		return -ENODEV;

	if (lbd->blksz != bm->bd->blksz)
		/* We could support block size translation, but we
		 * don't yet.
		 */
		return -EINVAL;

	linear = malloc(sizeof(*linear));
	if (!linear)
		return -ENOMEM;

	*linear = (struct blkmap_linear) {
		.slice = {
			.blknr = blknr,
			.blkcnt = blkcnt,

			.read = blkmap_linear_read,
			.write = blkmap_linear_write,
		},

		.bd = lbd,
		.blknr = lblknr,
	};

	err = blkmap_add(bm, &linear->slice);
	if (err)
		free(linear);

	return err;
}

struct blkmap_mem {
	struct blkmap_slice slice;
	void *addr;
	bool remapped;
};

static ulong blkmap_mem_read(struct blkmap *bm, struct blkmap_slice *bms,
			     lbaint_t blknr, lbaint_t blkcnt, void *buffer)
{
	struct blkmap_mem *bmm = container_of(bms, struct blkmap_mem, slice);
	char *src;

	src = bmm->addr + (blknr << bm->bd->log2blksz);
	memcpy(buffer, src, blkcnt << bm->bd->log2blksz);
	return blkcnt;
}

static ulong blkmap_mem_write(struct blkmap *bm, struct blkmap_slice *bms,
			      lbaint_t blknr, lbaint_t blkcnt,
			      const void *buffer)
{
	struct blkmap_mem *bmm = container_of(bms, struct blkmap_mem, slice);
	char *dst;

	dst = bmm->addr + (blknr << bm->bd->log2blksz);
	memcpy(dst, buffer, blkcnt << bm->bd->log2blksz);
	return blkcnt;
}

static void blkmap_mem_destroy(struct blkmap *bm, struct blkmap_slice *bms)
{
	struct blkmap_mem *bmm = container_of(bms, struct blkmap_mem, slice);

	if (bmm->remapped)
		unmap_sysmem(bmm->addr);
}

int __blkmap_map_mem(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		     void *addr, bool remapped)
{
	struct blkmap *bm = dev_get_plat(dev);
	struct blkmap_mem *bmm;
	int err;

	bmm = malloc(sizeof(*bmm));
	if (!bmm)
		return -ENOMEM;

	*bmm = (struct blkmap_mem) {
		.slice = {
			.blknr = blknr,
			.blkcnt = blkcnt,

			.read = blkmap_mem_read,
			.write = blkmap_mem_write,
			.destroy = blkmap_mem_destroy,
		},

		.addr = addr,
		.remapped = remapped,
	};

	err = blkmap_add(bm, &bmm->slice);
	if (err)
		free(bmm);

	return err;
}

int blkmap_map_mem(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		   void *addr)
{
	return __blkmap_map_mem(dev, blknr, blkcnt, addr, false);
}

int blkmap_map_pmem(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		    phys_addr_t paddr)
{
	struct blkmap *bm = dev_get_plat(dev);
	void *addr;
	int err;

	addr = map_sysmem(paddr, blkcnt << bm->bd->log2blksz);
	if (!addr)
		return -ENOMEM;

	err = __blkmap_map_mem(dev, blknr, blkcnt, addr, true);
	if (err)
		unmap_sysmem(addr);

	return err;
}

static ulong blkmap_blk_read_slice(struct blkmap *bm, struct blkmap_slice *bms,
				   lbaint_t blknr, lbaint_t blkcnt,
				   void *buffer)
{
	lbaint_t nr, cnt;

	nr = blknr - bms->blknr;
	cnt = (blkcnt < bms->blkcnt) ? blkcnt : bms->blkcnt;
	return bms->read(bm, bms, nr, cnt, buffer);
}

static ulong blkmap_blk_read(struct udevice *dev, lbaint_t blknr,
			     lbaint_t blkcnt, void *buffer)
{
	struct blk_desc *bd = dev_get_uclass_plat(dev);
	struct blkmap *bm = dev_get_parent_plat(dev);
	struct blkmap_slice *bms;
	lbaint_t cnt, total = 0;

	list_for_each_entry(bms, &bm->slices, node) {
		if (!blkmap_slice_contains(bms, blknr))
			continue;

		cnt = blkmap_blk_read_slice(bm, bms, blknr, blkcnt, buffer);
		blknr += cnt;
		blkcnt -= cnt;
		buffer += cnt << bd->log2blksz;
		total += cnt;
	}

	return total;
}

static ulong blkmap_blk_write_slice(struct blkmap *bm, struct blkmap_slice *bms,
				    lbaint_t blknr, lbaint_t blkcnt,
				    const void *buffer)
{
	lbaint_t nr, cnt;

	nr = blknr - bms->blknr;
	cnt = (blkcnt < bms->blkcnt) ? blkcnt : bms->blkcnt;
	return bms->write(bm, bms, nr, cnt, buffer);
}

static ulong blkmap_blk_write(struct udevice *dev, lbaint_t blknr,
			      lbaint_t blkcnt, const void *buffer)
{
	struct blk_desc *bd = dev_get_uclass_plat(dev);
	struct blkmap *bm = dev_get_parent_plat(dev);
	struct blkmap_slice *bms;
	lbaint_t cnt, total = 0;

	list_for_each_entry(bms, &bm->slices, node) {
		if (!blkmap_slice_contains(bms, blknr))
			continue;

		cnt = blkmap_blk_write_slice(bm, bms, blknr, blkcnt, buffer);
		blknr += cnt;
		blkcnt -= cnt;
		buffer += cnt << bd->log2blksz;
		total += cnt;
	}

	return total;
}

static const struct blk_ops blkmap_blk_ops = {
	.read	= blkmap_blk_read,
	.write	= blkmap_blk_write,
};

U_BOOT_DRIVER(blkmap_blk) = {
	.name		= "blkmap_blk",
	.id		= UCLASS_BLK,
	.ops		= &blkmap_blk_ops,
};

int blkmap_dev_bind(struct udevice *dev)
{
	struct blkmap *bm = dev_get_plat(dev);
	struct udevice *blk;
	int err;

	err = blk_create_devicef(dev, "blkmap_blk", "blk", UCLASS_BLKMAP,
				 dev_seq(dev), 512, 0, &blk);
	if (err)
		return log_msg_ret("blk", err);

	INIT_LIST_HEAD(&bm->slices);

	bm->bd = dev_get_uclass_plat(blk);
	snprintf(bm->bd->vendor, BLK_VEN_SIZE, "U-Boot");
	snprintf(bm->bd->product, BLK_PRD_SIZE, "blkmap");
	snprintf(bm->bd->revision, BLK_REV_SIZE, "1.0");

	/* EFI core isn't keen on zero-sized disks, so we lie. This is
	 * updated with the correct size once the user adds a
	 * mapping.
	 */
	bm->bd->lba = 1;

	return 0;
}

int blkmap_dev_unbind(struct udevice *dev)
{
	struct blkmap *bm = dev_get_plat(dev);
	struct blkmap_slice *bms, *tmp;

	list_for_each_entry_safe(bms, tmp, &bm->slices, node) {
		list_del(&bms->node);
		free(bms);
	}

	return 0;
}

U_BOOT_DRIVER(blkmap_root) = {
	.name		= "blkmap_dev",
	.id		= UCLASS_BLKMAP,
	.bind		= blkmap_dev_bind,
	.unbind		= blkmap_dev_unbind,
	.plat_auto	= sizeof(struct blkmap),
};

struct udevice *blkmap_from_label(const char *label)
{
	struct udevice *dev;
	struct uclass *uc;
	struct blkmap *bm;

	uclass_id_foreach_dev(UCLASS_BLKMAP, dev, uc) {
		bm = dev_get_plat(dev);
		if (bm->label && !strcmp(label, bm->label))
			return dev;
	}

	return NULL;
}

int blkmap_create(const char *label, struct udevice **devp)
{
	char *hname, *hlabel;
	struct udevice *dev;
	struct blkmap *bm;
	size_t namelen;
	int err;

	dev = blkmap_from_label(label);
	if (dev) {
		err = -EBUSY;
		goto err;
	}

	hlabel = strdup(label);
	if (!hlabel) {
		err = -ENOMEM;
		goto err;
	}

	namelen = strlen("blkmap-") + strlen(label) + 1;
	hname = malloc(namelen);
	if (!hname) {
		err = -ENOMEM;
		goto err_free_hlabel;
	}

	strlcpy(hname, "blkmap-", namelen);
	strlcat(hname, label, namelen);

	err = device_bind_driver(dm_root(), "blkmap_dev", hname, &dev);
	if (err)
		goto err_free_hname;

	device_set_name_alloced(dev);
	bm = dev_get_plat(dev);
	bm->label = hlabel;

	if (devp)
		*devp = dev;

	return 0;

err_free_hname:
	free(hname);
err_free_hlabel:
	free(hlabel);
err:
	return err;
}

int blkmap_destroy(struct udevice *dev)
{
	return device_unbind(dev);
}

UCLASS_DRIVER(blkmap) = {
	.id		= UCLASS_BLKMAP,
	.name		= "blkmap",
};
