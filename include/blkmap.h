/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2023 Addiva Elektronik
 * Author: Tobias Waldekranz <tobias@waldekranz.com>
 */

#ifndef _BLKMAP_H
#define _BLKMAP_H

#include <stdbool.h>

int blkmap_map_linear(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		      enum uclass_id lcls, int ldevnum, lbaint_t lblknr);
int blkmap_map_mem(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		   void *addr);
int blkmap_map_pmem(struct udevice *dev, lbaint_t blknr, lbaint_t blkcnt,
		    phys_addr_t paddr);


struct udevice *blkmap_from_label(const char *label);
int blkmap_create(const char *label, struct udevice **devp);
int blkmap_destroy(struct udevice *dev);

#endif	/* _BLKMAP_H */
