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

static struct udevice *blkmap_root(void)
{
	static struct udevice *dev = NULL;
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

	if ((devnum >= 0) && blkmap_from_devnum(devnum))
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
