/* SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2023 VEST
 */

#ifndef __VEST_E2I_PLUS_H
#define __VEST_E2I_PLUS_H

#include <linux/sizes.h>
#include <asm/arch/imx-regs.h>

/* Link Definitions */
#define CFG_SYS_INIT_RAM_ADDR	0x40000000
#define CFG_SYS_INIT_RAM_SIZE	0x80000

/* DDR Configuration */
#define CFG_SYS_SDRAM_BASE	0x40000000
#define PHYS_SDRAM		0x40000000
#define PHYS_SDRAM_SIZE		0xC0000000	/* 3 GB */
#define PHYS_SDRAM_2		0x100000000
#define PHYS_SDRAM_2_SIZE	0x40000000	/* 1 GB */

/* Serial configuration */
#define CFG_MXC_UART_BASE	UART2_BASE_ADDR

/* USDHC configuration */
#define CFG_SYS_FSL_USDHC_NUM	2

#endif /* __VEST_E2I_PLUS_H */
