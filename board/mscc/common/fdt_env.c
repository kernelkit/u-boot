// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2020 Microsemi Corporation
 */

#include <common.h>
#include <fdt_support.h>
#include <env_internal.h>

#ifdef CONFIG_OF_BOARD_SETUP
void ft_fwd_env(void *blob, int offset, const char *tag)
{
	char *value = env_get(tag);
	if (value)
		if (fdt_setprop_string(blob, offset, tag, value) < 0)
			printf("Unable to add tag %s to DT\n", tag);
}

int ft_board_setup(void *blob, bd_t *bd)
{
	int node = fdt_path_offset(blob, "/meba");
	uchar mac_addr[6];

	if (node >= 0) {
		ft_fwd_env(blob, node, "pcb");
		ft_fwd_env(blob, node, "pcb_var");
		ft_fwd_env(blob, node, "chip_id");
		ft_fwd_env(blob, node, "port_cfg");
		ft_fwd_env(blob, node, "mux_mode");
		if (eth_env_get_enetaddr("ethaddr", mac_addr))
			(void) fdt_setprop(blob, node, "mac-address", &mac_addr, 6);
	}

	return 0;
}
#endif
