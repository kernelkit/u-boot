/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2023 Addiva Elektronik
 * Author: Tobias Waldekranz <tobias@waldekranz.com>
 */

#ifndef _BLKMAP_H
#define _BLKMAP_H

#include <stdbool.h>

int blkmap_create(int devnum);
int blkmap_destroy(int devnum);

#endif	/* _BLKMAP_H */
