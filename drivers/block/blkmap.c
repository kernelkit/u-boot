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
	struct udevice *dev;
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

static struct blkmap *blkmap_from_devnum(int devnum)
{
	struct udevice *dev;
	int err;

	err = blk_find_device(UCLASS_BLKMAP, devnum, &dev);

	return err ? NULL : dev_get_priv(dev);
}

static int blkmap_add(struct blkmap *bm, struct blkmap_slice *new)
{
	struct blk_desc *bd = dev_get_uclass_plat(bm->dev);
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
	bd->lba = bms->blknr + bms->blkcnt;
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

int blkmap_map_linear(int devnum, lbaint_t blknr, lbaint_t blkcnt,
		      enum uclass_id lcls, int ldevnum, lbaint_t lblknr)
{
	struct blkmap_linear *linear;
	struct blk_desc *bd, *lbd;
	struct blkmap *bm;
	int err;

	bm = blkmap_from_devnum(devnum);
	if (!bm)
		return -ENODEV;

	bd = dev_get_uclass_plat(bm->dev);
	lbd = blk_get_devnum_by_uclass_id(lcls, ldevnum);
	if (!lbd)
		return -ENODEV;

	if (lbd->blksz != bd->blksz)
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
	struct blk_desc *bd = dev_get_uclass_plat(bm->dev);
	char *src;

	src = bmm->addr + (blknr << bd->log2blksz);
	memcpy(buffer, src, blkcnt << bd->log2blksz);
	return blkcnt;
}

static ulong blkmap_mem_write(struct blkmap *bm, struct blkmap_slice *bms,
			      lbaint_t blknr, lbaint_t blkcnt,
			      const void *buffer)
{
	struct blkmap_mem *bmm = container_of(bms, struct blkmap_mem, slice);
	struct blk_desc *bd = dev_get_uclass_plat(bm->dev);
	char *dst;

	dst = bmm->addr + (blknr << bd->log2blksz);
	memcpy(dst, buffer, blkcnt << bd->log2blksz);
	return blkcnt;
}

static void blkmap_mem_destroy(struct blkmap *bm, struct blkmap_slice *bms)
{
	struct blkmap_mem *bmm = container_of(bms, struct blkmap_mem, slice);

	if (bmm->remapped)
		unmap_sysmem(bmm->addr);
}

int __blkmap_map_mem(int devnum, lbaint_t blknr, lbaint_t blkcnt, void *addr,
		     bool remapped)
{
	struct blkmap_mem *bmm;
	struct blkmap *bm;
	int err;

	bm = blkmap_from_devnum(devnum);
	if (!bm)
		return -ENODEV;

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

int blkmap_map_mem(int devnum, lbaint_t blknr, lbaint_t blkcnt, void *addr)
{
	return __blkmap_map_mem(devnum, blknr, blkcnt, addr, false);
}

int blkmap_map_pmem(int devnum, lbaint_t blknr, lbaint_t blkcnt,
		    phys_addr_t paddr)
{
	struct blk_desc *bd;
	struct blkmap *bm;
	void *addr;
	int err;

	bm = blkmap_from_devnum(devnum);
	if (!bm)
		return -ENODEV;

	bd = dev_get_uclass_plat(bm->dev);

	addr = map_sysmem(paddr, blkcnt << bd->log2blksz);
	if (!addr)
		return -ENOMEM;

	err = __blkmap_map_mem(devnum, blknr, blkcnt, addr, true);
	if (err)
		unmap_sysmem(addr);

	return err;
}

static struct udevice *blkmap_root(void)
{
	static struct udevice *dev;
	int err;

	if (dev)
		return dev;

	err = device_bind_driver(dm_root(), "blkmap_root", "blkmap", &dev);
	if (err)
		return NULL;

	err = device_probe(dev);
	if (err) {
		device_unbind(dev);
		return NULL;
	}

	return dev;
}

int blkmap_create(int devnum)
{
	struct udevice *root;
	struct blk_desc *bd;
	struct blkmap *bm;
	int err;

	if (devnum >= 0 && blkmap_from_devnum(devnum))
		return -EBUSY;

	root = blkmap_root();
	if (!root)
		return -ENODEV;

	bm = calloc(1, sizeof(*bm));
	if (!bm)
		return -ENOMEM;

	err = blk_create_devicef(root, "blkmap_blk", "blk", UCLASS_BLKMAP,
				 devnum, 512, 0, &bm->dev);
	if (err)
		goto err_free;

	bd = dev_get_uclass_plat(bm->dev);

	/* EFI core isn't keen on zero-sized disks, so we lie. This is
	 * updated with the correct size once the user adds a
	 * mapping.
	 */
	bd->lba = 1;

	dev_set_priv(bm->dev, bm);
	INIT_LIST_HEAD(&bm->slices);

	err = blk_probe_or_unbind(bm->dev);
	if (err)
		goto err_remove;

	return bd->devnum;

err_remove:
	device_remove(bm->dev, DM_REMOVE_NORMAL);
err_free:
	free(bm);
	return err;
}

int blkmap_destroy(int devnum)
{
	struct blkmap_slice *bms, *tmp;
	struct blkmap *bm;
	int err;

	bm = blkmap_from_devnum(devnum);
	if (!bm)
		return -ENODEV;

	err = device_remove(bm->dev, DM_REMOVE_NORMAL);
	if (err)
		return err;

	err = device_unbind(bm->dev);
	if (err)
		return err;

	list_for_each_entry_safe(bms, tmp, &bm->slices, node) {
		list_del(&bms->node);
		free(bms);
	}

	free(bm);
	return 0;
}

static ulong blkmap_read_slice(struct blkmap *bm, struct blkmap_slice *bms,
			       lbaint_t blknr, lbaint_t blkcnt, void *buffer)
{
	lbaint_t nr, cnt;

	nr = blknr - bms->blknr;
	cnt = (blkcnt < bms->blkcnt) ? blkcnt : bms->blkcnt;
	return bms->read(bm, bms, nr, cnt, buffer);
}

static ulong blkmap_read(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
			 void *buffer)
{
	struct blk_desc *bd = dev_get_uclass_plat(dev);
	struct blkmap *bm = dev_get_priv(dev);
	struct blkmap_slice *bms;
	lbaint_t cnt, total = 0;

	list_for_each_entry(bms, &bm->slices, node) {
		if (!blkmap_slice_contains(bms, blknr))
			continue;

		cnt = blkmap_read_slice(bm, bms, blknr, blkcnt, buffer);
		blknr += cnt;
		blkcnt -= cnt;
		buffer += cnt << bd->log2blksz;
		total += cnt;
	}

	return total;
}

static ulong blkmap_write_slice(struct blkmap *bm, struct blkmap_slice *bms,
				lbaint_t blknr, lbaint_t blkcnt,
				const void *buffer)
{
	lbaint_t nr, cnt;

	nr = blknr - bms->blknr;
	cnt = (blkcnt < bms->blkcnt) ? blkcnt : bms->blkcnt;
	return bms->write(bm, bms, nr, cnt, buffer);
}

static ulong blkmap_write(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
			  const void *buffer)
{
	struct blk_desc *bd = dev_get_uclass_plat(dev);
	struct blkmap *bm = dev_get_priv(dev);
	struct blkmap_slice *bms;
	lbaint_t cnt, total = 0;

	list_for_each_entry(bms, &bm->slices, node) {
		if (!blkmap_slice_contains(bms, blknr))
			continue;

		cnt = blkmap_write_slice(bm, bms, blknr, blkcnt, buffer);
		blknr += cnt;
		blkcnt -= cnt;
		buffer += cnt << bd->log2blksz;
		total += cnt;
	}

	return total;
}

static const struct blk_ops blkmap_ops = {
	.read	= blkmap_read,
	.write	= blkmap_write,
};

U_BOOT_DRIVER(blkmap_blk) = {
	.name		= "blkmap_blk",
	.id		= UCLASS_BLK,
	.ops		= &blkmap_ops,
};

U_BOOT_DRIVER(blkmap_root) = {
	.name		= "blkmap_root",
	.id		= UCLASS_BLKMAP,
};

UCLASS_DRIVER(blkmap) = {
	.id		= UCLASS_BLKMAP,
	.name		= "blkmap",
};