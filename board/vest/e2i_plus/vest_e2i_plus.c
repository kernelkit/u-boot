// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2023 APC-VEST
 */

#include <config.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx8mp_pins.h>
#include <asm/arch/sys_proto.h>
#include <asm-generic/gpio.h>
#include <asm/global_data.h>
#include <asm/mach-imx/gpio.h>
#include <asm/mach-imx/iomux-v3.h>
#include <errno.h>
#include <env.h>
#include <init.h>
#include <linux/delay.h>
#include <micrel.h>
#include <miiphy.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL	(PAD_CTL_DSE6 | PAD_CTL_FSEL1)

/* VEST-i.MX8M-PLUS-SOM-USG-001 UART_2, Console/Debug UART */
static iomux_v3_cfg_t const uart_pads[] = {
	MX8MP_PAD_UART2_RXD__UART2_DCE_RX | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX8MP_PAD_UART2_TXD__UART2_DCE_TX | MUX_PAD_CTRL(UART_PAD_CTRL),
};

int board_early_init_f(void)
{
	imx_iomux_v3_setup_multiple_pads(uart_pads, ARRAY_SIZE(uart_pads));
	init_uart_clk(0);

	return 0;
}

int board_init(void)
{
	return 0;
}

int board_late_init(void)
{
	return 0;
}
