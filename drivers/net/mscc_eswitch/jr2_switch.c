// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2018 Microsemi Corporation
 */

#include <common.h>
#include <config.h>
#include <dm.h>
#include <dm/of_access.h>
#include <dm/of_addr.h>
#include <fdt_support.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <miiphy.h>
#include <net.h>
#include <wait_bit.h>

#include <dt-bindings/mscc/jr2_data.h>
#include "mscc_xfer.h"
#include "mscc_miim.h"

#define ANA_AC_RAM_CTRL_RAM_INIT		0x94358
#define ANA_AC_STAT_GLOBAL_CFG_PORT_RESET	0x94370
#define ANA_AC_SRC_CFG1(x)			(0x94400 + 0x4 * (x))
#define ANA_AC_SRC_CFG2(x)			(0x94404 + 0x4 * (x))

#define ANA_CL_PORT_VLAN_CFG(x)			(0x24018 + 0xc8 * (x))
#define		ANA_CL_PORT_VLAN_CFG_AWARE_ENA			BIT(19)
#define		ANA_CL_PORT_VLAN_CFG_POP_CNT(x)			((x) << 17)

#define ANA_L2_COMMON_FWD_CFG			0x8a2a8
#define		ANA_L2_COMMON_FWD_CFG_CPU_DMAC_COPY_ENA	BIT(6)

#define ASM_CFG_STAT_CFG			0x3508
#define ASM_CFG_PORT(x)				(0x36c4 + 0x4 * (x))
#define		ASM_CFG_PORT_NO_PREAMBLE_ENA		BIT(8)
#define		ASM_CFG_PORT_INJ_FORMAT_CFG(x)		((x) << 1)
#define ASM_RAM_CTRL_RAM_INIT			0x39b8

#define DEV_DEV_CFG_DEV_RST_CTRL		0x0
#define		DEV_DEV_CFG_DEV_RST_CTRL_SPEED_SEL(x)	((x) << 20)
#define DEV_MAC_CFG_MAC_ENA		0x1c
#define		DEV_MAC_CFG_MAC_ENA_RX_ENA		BIT(4)
#define		DEV_MAC_CFG_MAC_ENA_TX_ENA		BIT(0)
#define	DEV_MAC_CFG_MAC_IFG		0x34
#define		DEV_MAC_CFG_MAC_IFG_TX_IFG(x)		((x) << 8)
#define		DEV_MAC_CFG_MAC_IFG_RX_IFG2(x)		((x) << 4)
#define		DEV_MAC_CFG_MAC_IFG_RX_IFG1(x)		(x)
#define	DEV_PCS1G_CFG_PCS1G_CFG		0x40
#define		DEV_PCS1G_CFG_PCS1G_CFG_PCS_ENA		BIT(0)
#define	DEV_PCS1G_CFG_PCS1G_MODE	0x44
#define	DEV_PCS1G_CFG_PCS1G_SD		0x48
#define	DEV_PCS1G_CFG_PCS1G_ANEG	0x4c
#define		DEV_PCS1G_CFG_PCS1G_ANEG_ADV_ABILITY(x)	((x) << 16)

#define DSM_RAM_CTRL_RAM_INIT		0x8

#define HSIO_ANA_SERDES1G_DES_CFG		0xac
#define		HSIO_ANA_SERDES1G_DES_CFG_BW_HYST(x)		((x) << 1)
#define		HSIO_ANA_SERDES1G_DES_CFG_BW_ANA(x)		((x) << 5)
#define		HSIO_ANA_SERDES1G_DES_CFG_MBTR_CTRL(x)		((x) << 8)
#define		HSIO_ANA_SERDES1G_DES_CFG_PHS_CTRL(x)		((x) << 13)
#define HSIO_ANA_SERDES1G_IB_CFG		0xb0
#define		HSIO_ANA_SERDES1G_IB_CFG_RESISTOR_CTRL(x)	(x)
#define		HSIO_ANA_SERDES1G_IB_CFG_EQ_GAIN(x)		((x) << 6)
#define		HSIO_ANA_SERDES1G_IB_CFG_ENA_OFFSET_COMP	BIT(9)
#define		HSIO_ANA_SERDES1G_IB_CFG_ENA_DETLEV		BIT(11)
#define		HSIO_ANA_SERDES1G_IB_CFG_ENA_CMV_TERM		BIT(13)
#define		HSIO_ANA_SERDES1G_IB_CFG_DET_LEV(x)		((x) << 19)
#define		HSIO_ANA_SERDES1G_IB_CFG_ACJTAG_HYST(x)		((x) << 24)
#define HSIO_ANA_SERDES1G_OB_CFG		0xb4
#define		HSIO_ANA_SERDES1G_OB_CFG_RESISTOR_CTRL(x)	(x)
#define		HSIO_ANA_SERDES1G_OB_CFG_VCM_CTRL(x)		((x) << 4)
#define		HSIO_ANA_SERDES1G_OB_CFG_CMM_BIAS_CTRL(x)	((x) << 10)
#define		HSIO_ANA_SERDES1G_OB_CFG_AMP_CTRL(x)		((x) << 13)
#define		HSIO_ANA_SERDES1G_OB_CFG_SLP(x)			((x) << 17)
#define HSIO_ANA_SERDES1G_SER_CFG		0xb8
#define HSIO_ANA_SERDES1G_COMMON_CFG		0xbc
#define		HSIO_ANA_SERDES1G_COMMON_CFG_IF_MODE		BIT(0)
#define		HSIO_ANA_SERDES1G_COMMON_CFG_ENA_LANE		BIT(18)
#define		HSIO_ANA_SERDES1G_COMMON_CFG_SYS_RST		BIT(31)
#define HSIO_ANA_SERDES1G_PLL_CFG		0xc0
#define		HSIO_ANA_SERDES1G_PLL_CFG_FSM_ENA		BIT(7)
#define		HSIO_ANA_SERDES1G_PLL_CFG_FSM_CTRL_DATA(x)	((x) << 8)
#define		HSIO_ANA_SERDES1G_PLL_CFG_ENA_RC_DIV2		BIT(21)
#define HSIO_DIG_SERDES1G_DFT_CFG0		0xc8
#define HSIO_DIG_SERDES1G_TP_CFG		0xd4
#define HSIO_DIG_SERDES1G_MISC_CFG		0xdc
#define		HSIO_DIG_SERDES1G_MISC_CFG_LANE_RST		BIT(0)
#define HSIO_MCB_SERDES1G_CFG			0xe8
#define		HSIO_MCB_SERDES1G_CFG_WR_ONE_SHOT		BIT(31)
#define		HSIO_MCB_SERDES1G_CFG_ADDR(x)			(x)

#define HSIO_ANA_SERDES6G_DES_CFG		0x11c
#define		HSIO_ANA_SERDES6G_DES_CFG_SWAP_ANA		BIT(0)
#define		HSIO_ANA_SERDES6G_DES_CFG_BW_ANA(x)		((x) << 1)
#define		HSIO_ANA_SERDES6G_DES_CFG_SWAP_HYST		BIT(4)
#define		HSIO_ANA_SERDES6G_DES_CFG_BW_HYST(x)		((x) << 5)
#define		HSIO_ANA_SERDES6G_DES_CFG_CPMD_SEL(x)		((x) << 8)
#define		HSIO_ANA_SERDES6G_DES_CFG_MBTR_CTRL(x)		((x) << 10)
#define		HSIO_ANA_SERDES6G_DES_CFG_PHS_CTRL(x)		((x) << 13)
#define HSIO_ANA_SERDES6G_IB_CFG		0x120
#define		HSIO_ANA_SERDES6G_IB_CFG_REG_ENA		BIT(0)
#define		HSIO_ANA_SERDES6G_IB_CFG_EQZ_ENA		BIT(1)
#define		HSIO_ANA_SERDES6G_IB_CFG_SAM_ENA		BIT(2)
#define		HSIO_ANA_SERDES6G_IB_CFG_CAL_ENA(x)		((x) << 3)
#define		HSIO_ANA_SERDES6G_IB_CFG_CONCUR			BIT(4)
#define		HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_ENA		BIT(5)
#define		HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_OFF(x)	((x) << 7)
#define		HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_LP(x)	((x) << 9)
#define		HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_MID(x)	((x) << 11)
#define		HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_HP(x)	((x) << 13)
#define		HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_CLK_SEL(x)	((x) << 15)
#define		HSIO_ANA_SERDES6G_IB_CFG_TERM_MODE_SEL(x)	((x) << 18)
#define		HSIO_ANA_SERDES6G_IB_CFG_ICML_ADJ(x)		((x) << 20)
#define		HSIO_ANA_SERDES6G_IB_CFG_RTRM_ADJ(x)		((x) << 24)
#define		HSIO_ANA_SERDES6G_IB_CFG_VBULK_SEL		BIT(28)
#define		HSIO_ANA_SERDES6G_IB_CFG_SOFSI(x)		((x) << 29)
#define HSIO_ANA_SERDES6G_IB_CFG1		0x124
#define		HSIO_ANA_SERDES6G_IB_CFG1_FILT_OFFSET		BIT(4)
#define		HSIO_ANA_SERDES6G_IB_CFG1_FILT_LP		BIT(5)
#define		HSIO_ANA_SERDES6G_IB_CFG1_FILT_MID		BIT(6)
#define		HSIO_ANA_SERDES6G_IB_CFG1_FILT_HP		BIT(7)
#define		HSIO_ANA_SERDES6G_IB_CFG1_SCALY(x)		((x) << 8)
#define		HSIO_ANA_SERDES6G_IB_CFG1_TSDET(x)		((x) << 12)
#define		HSIO_ANA_SERDES6G_IB_CFG1_TJTAG(x)		((x) << 17)
#define HSIO_ANA_SERDES6G_IB_CFG2		0x128
#define		HSIO_ANA_SERDES6G_IB_CFG2_UREG(x)		(x)
#define		HSIO_ANA_SERDES6G_IB_CFG2_UMAX(x)		((x) << 3)
#define		HSIO_ANA_SERDES6G_IB_CFG2_TCALV(x)		((x) << 5)
#define		HSIO_ANA_SERDES6G_IB_CFG2_OCALS(x)		((x) << 10)
#define		HSIO_ANA_SERDES6G_IB_CFG2_OINFS(x)		((x) << 16)
#define		HSIO_ANA_SERDES6G_IB_CFG2_OINFI(x)		((x) << 22)
#define		HSIO_ANA_SERDES6G_IB_CFG2_TINFV(x)		((x) << 27)
#define HSIO_ANA_SERDES6G_IB_CFG3		0x12c
#define		HSIO_ANA_SERDES6G_IB_CFG3_INI_OFFSET(x)		(x)
#define		HSIO_ANA_SERDES6G_IB_CFG3_INI_LP(x)		((x) << 6)
#define		HSIO_ANA_SERDES6G_IB_CFG3_INI_MID(x)		((x) << 12)
#define		HSIO_ANA_SERDES6G_IB_CFG3_INI_HP(x)		((x) << 18)
#define HSIO_ANA_SERDES6G_IB_CFG4		0x130
#define		HSIO_ANA_SERDES6G_IB_CFG4_MAX_OFFSET(x)		(x)
#define		HSIO_ANA_SERDES6G_IB_CFG4_MAX_LP(x)		((x) << 6)
#define		HSIO_ANA_SERDES6G_IB_CFG4_MAX_MID(x)		((x) << 12)
#define		HSIO_ANA_SERDES6G_IB_CFG4_MAX_HP(x)		((x) << 18)
#define HSIO_ANA_SERDES6G_IB_CFG5		0x134
#define		HSIO_ANA_SERDES6G_IB_CFG4_MIN_OFFSET(x)		(x)
#define		HSIO_ANA_SERDES6G_IB_CFG4_MIN_LP(x)		((x) << 6)
#define		HSIO_ANA_SERDES6G_IB_CFG4_MIN_MID(x)		((x) << 12)
#define		HSIO_ANA_SERDES6G_IB_CFG4_MIN_HP(x)		((x) << 18)
#define HSIO_ANA_SERDES6G_OB_CFG		0x138
#define		HSIO_ANA_SERDES6G_OB_CFG_RESISTOR_CTRL(x)	(x)
#define		HSIO_ANA_SERDES6G_OB_CFG_SR(x)			((x) << 4)
#define		HSIO_ANA_SERDES6G_OB_CFG_SR_H			BIT(8)
#define		HSIO_ANA_SERDES6G_OB_CFG_SEL_RCTRL		BIT(9)
#define		HSIO_ANA_SERDES6G_OB_CFG_R_COR			BIT(10)
#define		HSIO_ANA_SERDES6G_OB_CFG_POST1(x)		((x) << 11)
#define		HSIO_ANA_SERDES6G_OB_CFG_R_ADJ_PDR		BIT(16)
#define		HSIO_ANA_SERDES6G_OB_CFG_R_ADJ_MUX		BIT(17)
#define		HSIO_ANA_SERDES6G_OB_CFG_PREC(x)		((x) << 18)
#define		HSIO_ANA_SERDES6G_OB_CFG_POST0(x)		((x) << 23)
#define		HSIO_ANA_SERDES6G_OB_CFG_POL			BIT(29)
#define		HSIO_ANA_SERDES6G_OB_CFG_ENA1V_MODE(x)		((x) << 30)
#define		HSIO_ANA_SERDES6G_OB_CFG_IDLE			BIT(31)
#define HSIO_ANA_SERDES6G_OB_CFG1		0x13c
#define		HSIO_ANA_SERDES6G_OB_CFG1_LEV(x)		(x)
#define		HSIO_ANA_SERDES6G_OB_CFG1_ENA_CAS(x)		((x) << 6)
#define HSIO_ANA_SERDES6G_SER_CFG		0x140
#define HSIO_ANA_SERDES6G_COMMON_CFG		0x144
#define		HSIO_ANA_SERDES6G_COMMON_CFG_IF_MODE(x)		(x)
#define		HSIO_ANA_SERDES6G_COMMON_CFG_QRATE(x)		(x << 2)
#define		HSIO_ANA_SERDES6G_COMMON_CFG_ENA_LANE		BIT(14)
#define		HSIO_ANA_SERDES6G_COMMON_CFG_SYS_RST		BIT(16)
#define HSIO_ANA_SERDES6G_PLL_CFG		0x148
#define		HSIO_ANA_SERDES6G_PLL_CFG_ROT_FRQ		BIT(0)
#define		HSIO_ANA_SERDES6G_PLL_CFG_ROT_DIR		BIT(1)
#define		HSIO_ANA_SERDES6G_PLL_CFG_RB_DATA_SEL		BIT(2)
#define		HSIO_ANA_SERDES6G_PLL_CFG_FSM_OOR_RECAL_ENA	BIT(3)
#define		HSIO_ANA_SERDES6G_PLL_CFG_FSM_FORCE_SET_ENA	BIT(4)
#define		HSIO_ANA_SERDES6G_PLL_CFG_FSM_ENA		BIT(5)
#define		HSIO_ANA_SERDES6G_PLL_CFG_FSM_CTRL_DATA(x)	((x) << 6)
#define		HSIO_ANA_SERDES6G_PLL_CFG_ENA_ROT		BIT(14)
#define		HSIO_ANA_SERDES6G_PLL_CFG_DIV4			BIT(15)
#define		HSIO_ANA_SERDES6G_PLL_CFG_ENA_OFFS(x)		((x) << 16)
#define HSIO_DIG_SERDES6G_MISC_CFG		0x108
#define		HSIO_DIG_SERDES6G_MISC_CFG_LANE_RST		BIT(0)
#define HSIO_MCB_SERDES6G_CFG			0x168
#define		HSIO_MCB_SERDES6G_CFG_WR_ONE_SHOT		BIT(31)
#define		HSIO_MCB_SERDES6G_CFG_ADDR(x)			(x)
#define HSIO_HW_CFGSTAT_HW_CFG			0x16c

#define LRN_COMMON_ACCESS_CTRL			0x0
#define		LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT	BIT(0)
#define LRN_COMMON_MAC_ACCESS_CFG0		0x4
#define LRN_COMMON_MAC_ACCESS_CFG1		0x8
#define LRN_COMMON_MAC_ACCESS_CFG2		0xc
#define		LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_ADDR(x)	(x)
#define		LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_TYPE(x)	((x) << 12)
#define		LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_VLD	BIT(15)
#define		LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_LOCKED	BIT(16)
#define		LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_COPY	BIT(23)
#define		LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_QU(x)	((x) << 24)

#define QFWD_SYSTEM_SWITCH_PORT_MODE(x)		(0x4 * (x))
#define		QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA		BIT(17)

#define QS_XTR_GRP_CFG(x)		(0x0 + 4 * (x))
#define QS_INJ_GRP_CFG(x)		(0x24 + (x) * 4)

#define QSYS_SYSTEM_RESET_CFG			0xf0
#define QSYS_CALCFG_CAL_AUTO(x)			(0x3d4 + 4 * (x))
#define QSYS_CALCFG_CAL_CTRL			0x3e8
#define		QSYS_CALCFG_CAL_CTRL_CAL_MODE(x)		((x) << 11)
#define QSYS_RAM_CTRL_RAM_INIT			0x3ec

#define REW_RAM_CTRL_RAM_INIT			0x53528

#define VOP_RAM_CTRL_RAM_INIT			0x43638

/* Serdes 10G register targets */
#define SD10G65_SD10G65_DES_CFG0 0x0
#define SD10G65_SD10G65_MOEBDIV_CFG0 0x4
#define SD10G65_SD10G65_OB_CFG0 0x40
#define SD10G65_SD10G65_OB_CFG1 0x44
#define SD10G65_SD10G65_OB_CFG2 0x48
#define SD10G65_SD10G65_OB_CFG3 0x4c
#define SD10G65_SD10G65_SBUS_TX_CFG 0x50
#define SD10G65_SD10G65_TX_SVN_ID 0x54
#define SD10G65_SD10G65_TX_REV_ID 0x58
#define SD10G65_SD10G65_IB_CFG0 0x80
#define SD10G65_SD10G65_IB_CFG1 0x84
#define SD10G65_SD10G65_IB_CFG2 0x88
#define SD10G65_SD10G65_IB_CFG3 0x8c
#define SD10G65_SD10G65_IB_CFG4 0x90
#define SD10G65_SD10G65_IB_CFG5 0x94
#define SD10G65_SD10G65_IB_CFG6 0x98
#define SD10G65_SD10G65_IB_CFG7 0x9c
#define SD10G65_SD10G65_IB_CFG8 0xa0
#define SD10G65_SD10G65_IB_CFG9 0xa4
#define SD10G65_SD10G65_IB_CFG10 0xa8
#define SD10G65_SD10G65_IB_CFG11 0xac
#define SD10G65_SD10G65_SBUS_RX_CFG 0xb0
#define SD10G65_SD10G65_RX_SVN_ID 0xb4
#define SD10G65_SD10G65_RX_REV_ID 0xb8
#define SD10G65_SD10G65_RX_RCPLL_CFG0 0xc0
#define SD10G65_SD10G65_RX_RCPLL_CFG1 0xc4
#define SD10G65_SD10G65_RX_RCPLL_CFG2 0xc8
#define SD10G65_SD10G65_RX_RCPLL_STAT0 0xcc
#define         SD10G65_SD10G65_RX_RCPLL_STAT0_PLLF_LOCK_STAT BIT(31)
#define SD10G65_SD10G65_RX_RCPLL_STAT1 0xd0
#define         SD10G65_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT 0xF
#define SD10G65_SD10G65_RX_SYNTH_CFG0 0x100
#define SD10G65_SD10G65_RX_SYNTH_CFG1 0x104
#define SD10G65_SD10G65_RX_SYNTH_CFG2 0x108
#define SD10G65_SD10G65_RX_SYNTH_CFG3 0x10c
#define SD10G65_SD10G65_RX_SYNTH_CFG4 0x110
#define SD10G65_SD10G65_RX_SYNTH_CDRLF 0x114
#define SD10G65_SD10G65_RX_SYNTH_QUALIFIER0 0x118
#define SD10G65_SD10G65_RX_SYNTH_QUALIFIER1 0x11c
#define SD10G65_SD10G65_RX_SYNTH_SYNC_CTRL 0x120
#define SD10G65_F2DF_CFG_STAT 0x124
#define SD10G65_SD10G65_TX_SYNTH_CFG0 0x140
#define SD10G65_SD10G65_TX_SYNTH_CFG1 0x144
#define SD10G65_SD10G65_TX_SYNTH_CFG3 0x148
#define SD10G65_SD10G65_TX_SYNTH_CFG4 0x14c
#define SD10G65_SD10G65_SSC_CFG0 0x150
#define SD10G65_SD10G65_SSC_CFG1 0x154
#define SD10G65_SD10G65_TX_RCPLL_CFG0 0x180
#define SD10G65_SD10G65_TX_RCPLL_CFG1 0x184
#define SD10G65_SD10G65_TX_RCPLL_CFG2 0x188
#define SD10G65_SD10G65_TX_RCPLL_STAT0 0x18c
#define         SD10G65_SD10G65_TX_RCPLL_STAT0_PLLF_LOCK_STAT BIT(31)
#define SD10G65_SD10G65_TX_RCPLL_STAT1 0x190
#define         SD10G65_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT 0xF
#define XFI_SHELL_KR_CONTROL 0x0
#define XFI_SHELL_XFI_MODE 0x4
#define XFI_SHELL_XFI_STATUS 0x8
#define XFI_SHELL_INT_CTRL 0xc
#define XFI_SHELL_SSF_HYST_ENA_CTRL 0x10
#define XFI_SHELL_SSF_HYST_TIMING_CTRL 0x14
#define XFI_SHELL_HSS_STICKY 0x18
#define XFI_SHELL_HSS_MASK 0x1c
#define XFI_SHELL_HSS_STATUS 0x20
#define XFI_SHELL_DATA_VALID_DETECT_CTRL 0x24

#define XTR_VALID_BYTES(x)	(4 - ((x) & 3))
#define MAC_VID			0
#define CPU_PORT		53
#define IFH_LEN			7
#define JR2_BUF_CELL_SZ		60
#define ETH_ALEN		6
#define PGID_BROADCAST		510
#define PGID_UNICAST		511
#define NPI_PORT		48

static const char * const regs_names[] = {
	"port0", "port1", "port2", "port3", "port4", "port5", "port6", "port7",
	"port8", "port9", "port10", "port11", "port12", "port13", "port14",
	"port15", "port16", "port17", "port18", "port19", "port20", "port21",
	"port22", "port23", "port24", "port25", "port26", "port27", "port28",
	"port29", "port30", "port31", "port32", "port33", "port34", "port35",
	"port36", "port37", "port38", "port39", "port40", "port41", "port42",
	"port43", "port44", "port45", "port46", "port47", "port48", "port49",
	"port50", "port51", "port52",
	"ana_ac", "ana_cl", "ana_l2", "asm", "hsio", "lrn",
	"qfwd", "qs", "qsys", "rew", "gcb", "icpu",
	"xgana0", "xgana1", "xgana2", "xgana3",
	"xgxfi0", "xgxfi1", "xgxfi2", "xgxfi3",
};

#define REGS_NAMES_COUNT ARRAY_SIZE(regs_names) + 1
#define MAX_PORT 53

enum jr2_ctrl_regs {
	ANA_AC = MAX_PORT,
	ANA_CL,
	ANA_L2,
	ASM,
	HSIO,
	LRN,
	QFWD,
	QS,
	QSYS,
	REW,
	GCB,
	ICPU,
	XGANA0,
	XGANA1,
	XGANA2,
	XGANA3,
	XGXFI0,
	XGXFI1,
	XGXFI2,
	XGXFI3,
};

#define JR2_MIIM_BUS_COUNT 3

struct jr2_phy_port_t {
	size_t phy_addr;
	struct mii_dev *bus;
	u8 serdes_index;
	u8 phy_mode;
};

struct jr2_private {
	void __iomem *regs[REGS_NAMES_COUNT];
	struct mii_dev *bus[JR2_MIIM_BUS_COUNT];
	struct jr2_phy_port_t ports[MAX_PORT];
};

static const unsigned long jr2_regs_qs[] = {
	[MSCC_QS_XTR_RD] = 0x8,
	[MSCC_QS_XTR_FLUSH] = 0x18,
	[MSCC_QS_XTR_DATA_PRESENT] = 0x1c,
	[MSCC_QS_INJ_WR] = 0x2c,
	[MSCC_QS_INJ_CTRL] = 0x34,
};

static struct mscc_miim_dev miim[JR2_MIIM_BUS_COUNT];
static int miim_count = -1;

static bool is_10g(u8 port)
{
	return (port > 48 && port < 53);
}

static void jr2_cpu_capture_setup(struct jr2_private *priv)
{
	/* ASM: No preamble and IFH prefix on CPU injected frames */
	writel(ASM_CFG_PORT_NO_PREAMBLE_ENA |
	       ASM_CFG_PORT_INJ_FORMAT_CFG(1),
	       priv->regs[ASM] + ASM_CFG_PORT(CPU_PORT));

	/* Set Manual injection via DEVCPU_QS registers for CPU queue 0 */
	writel(0x5, priv->regs[QS] + QS_INJ_GRP_CFG(0));

	/* Set Manual extraction via DEVCPU_QS registers for CPU queue 0 */
	writel(0x7, priv->regs[QS] + QS_XTR_GRP_CFG(0));

	/* Enable CPU port for any frame transfer */
	setbits_le32(priv->regs[QFWD] + QFWD_SYSTEM_SWITCH_PORT_MODE(CPU_PORT),
		     QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);

	/* Send a copy to CPU when found as forwarding entry */
	setbits_le32(priv->regs[ANA_L2] + ANA_L2_COMMON_FWD_CFG,
		     ANA_L2_COMMON_FWD_CFG_CPU_DMAC_COPY_ENA);
}

static void jr2_port_init(struct jr2_private *priv, int port)
{
	void __iomem *regs = priv->regs[port];
	u32 ofs, val;

	/* Enable PCS */
	writel(DEV_PCS1G_CFG_PCS1G_CFG_PCS_ENA,
	       regs + DEV_PCS1G_CFG_PCS1G_CFG);

	/* Disable Signal Detect */
	writel(0, regs + DEV_PCS1G_CFG_PCS1G_SD);

	/* Enable MAC RX and TX */
	writel(DEV_MAC_CFG_MAC_ENA_RX_ENA |
	       DEV_MAC_CFG_MAC_ENA_TX_ENA,
	       regs + DEV_MAC_CFG_MAC_ENA);

	/* Clear sgmii_mode_ena */
	writel(0, regs + DEV_PCS1G_CFG_PCS1G_MODE);

	/*
	 * Clear sw_resolve_ena(bit 0) and set adv_ability to
	 * something meaningful just in case
	 */
	writel(DEV_PCS1G_CFG_PCS1G_ANEG_ADV_ABILITY(0x20),
	       regs + DEV_PCS1G_CFG_PCS1G_ANEG);

	/* Set MAC IFG Gaps */
	writel(DEV_MAC_CFG_MAC_IFG_TX_IFG(4) |
	       DEV_MAC_CFG_MAC_IFG_RX_IFG1(5) |
	       DEV_MAC_CFG_MAC_IFG_RX_IFG2(1),
	       regs + DEV_MAC_CFG_MAC_IFG);

	/* Set link speed and release all resets */
	writel(DEV_DEV_CFG_DEV_RST_CTRL_SPEED_SEL(2),
	       regs + DEV_DEV_CFG_DEV_RST_CTRL);

	/* Make VLAN aware for CPU traffic */
	writel(ANA_CL_PORT_VLAN_CFG_AWARE_ENA |
	       ANA_CL_PORT_VLAN_CFG_POP_CNT(1) |
	       MAC_VID,
	       priv->regs[ANA_CL] + ANA_CL_PORT_VLAN_CFG(port));

	/* Enable 2G5 shadow device for 10G port */
	if (is_10g(port)) {
		val = readl(priv->regs[HSIO] + HSIO_HW_CFGSTAT_HW_CFG);
		ofs = port == 49 ? 12 : port == 50 ? 14 : port == 51 ? 16 : 18;
		val = val | (3 << ofs);
		writel(val, priv->regs[HSIO] + HSIO_HW_CFGSTAT_HW_CFG);
	}

	/* Enable CPU port for any frame transfer */
	setbits_le32(priv->regs[QFWD] + QFWD_SYSTEM_SWITCH_PORT_MODE(port),
		     QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA);
}

static void serdes6g_write(void __iomem *base, u32 addr)
{
	u32 data;

	writel(HSIO_MCB_SERDES6G_CFG_WR_ONE_SHOT |
	       HSIO_MCB_SERDES6G_CFG_ADDR(addr),
	       base + HSIO_MCB_SERDES6G_CFG);

	do {
		data = readl(base + HSIO_MCB_SERDES6G_CFG);
	} while (data & HSIO_MCB_SERDES6G_CFG_WR_ONE_SHOT);
}

static void serdes6g_setup(void __iomem *base, uint32_t addr,
			   phy_interface_t interface)
{
	u32 ib_if_mode = 0;
	u32 ib_qrate = 0;
	u32 ib1_tsdet = 0;
	u32 ob_lev = 0;
	u32 ob_ena_cas = 0;
	u32 ob_ena1v_mode = 0;
	u32 des_bw_ana = 0;
	u32 pll_fsm_ctrl_data = 0;

	switch (interface) {
	case PHY_INTERFACE_MODE_SGMII:
		ib_if_mode = 1;
		ib_qrate = 1;
		ib1_tsdet = 3;
		ob_lev = 48;
		ob_ena_cas = 2;
		ob_ena1v_mode = 1;
		des_bw_ana = 3;
		pll_fsm_ctrl_data = 60;
		break;
	case PHY_INTERFACE_MODE_QSGMII:
		ib_if_mode = 3;
		ib1_tsdet = 16;
		ob_lev = 24;
		des_bw_ana = 5;
		pll_fsm_ctrl_data = 120;
		break;
	default:
		pr_err("Interface not supported\n");
		return;
	}

	if (interface == PHY_INTERFACE_MODE_QSGMII)
		writel(0xfff, base + HSIO_HW_CFGSTAT_HW_CFG);

	writel(HSIO_ANA_SERDES6G_OB_CFG_RESISTOR_CTRL(1) |
	       HSIO_ANA_SERDES6G_OB_CFG_SR(7) |
	       HSIO_ANA_SERDES6G_OB_CFG_SR_H |
	       HSIO_ANA_SERDES6G_OB_CFG_ENA1V_MODE(ob_ena1v_mode) |
	       HSIO_ANA_SERDES6G_OB_CFG_POL, base + HSIO_ANA_SERDES6G_OB_CFG);

	writel(HSIO_ANA_SERDES6G_COMMON_CFG_IF_MODE(3),
	       base + HSIO_ANA_SERDES6G_COMMON_CFG);
	writel(HSIO_ANA_SERDES6G_PLL_CFG_FSM_CTRL_DATA(120) |
	       HSIO_ANA_SERDES6G_PLL_CFG_ENA_OFFS(3),
	       base + HSIO_ANA_SERDES6G_PLL_CFG);
	writel(HSIO_ANA_SERDES6G_IB_CFG_REG_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_EQZ_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_SAM_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_CONCUR |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_OFF(0) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_LP(2) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_MID(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_HP(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_CLK_SEL(7) |
	       HSIO_ANA_SERDES6G_IB_CFG_TERM_MODE_SEL(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_ICML_ADJ(5) |
	       HSIO_ANA_SERDES6G_IB_CFG_RTRM_ADJ(13) |
	       HSIO_ANA_SERDES6G_IB_CFG_VBULK_SEL |
	       HSIO_ANA_SERDES6G_IB_CFG_SOFSI(1),
	       base + HSIO_ANA_SERDES6G_IB_CFG);
	writel(HSIO_ANA_SERDES6G_IB_CFG1_FILT_OFFSET |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_LP |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_MID |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_HP |
	       HSIO_ANA_SERDES6G_IB_CFG1_SCALY(15) |
	       HSIO_ANA_SERDES6G_IB_CFG1_TSDET(3) |
	       HSIO_ANA_SERDES6G_IB_CFG1_TJTAG(8),
	       base + HSIO_ANA_SERDES6G_IB_CFG1);

	writel(HSIO_ANA_SERDES6G_IB_CFG2_UREG(4) |
	       HSIO_ANA_SERDES6G_IB_CFG2_UMAX(2) |
	       HSIO_ANA_SERDES6G_IB_CFG2_TCALV(12) |
	       HSIO_ANA_SERDES6G_IB_CFG2_OCALS(32) |
	       HSIO_ANA_SERDES6G_IB_CFG2_OINFS(7) |
	       HSIO_ANA_SERDES6G_IB_CFG2_OINFI(0x1f) |
	       HSIO_ANA_SERDES6G_IB_CFG2_TINFV(3),
	       base + HSIO_ANA_SERDES6G_IB_CFG2);

	writel(HSIO_ANA_SERDES6G_IB_CFG3_INI_OFFSET(0x1f) |
	       HSIO_ANA_SERDES6G_IB_CFG3_INI_LP(1) |
	       HSIO_ANA_SERDES6G_IB_CFG3_INI_MID(0x1f),
	       base + HSIO_ANA_SERDES6G_IB_CFG3);

	writel(HSIO_DIG_SERDES6G_MISC_CFG_LANE_RST,
	       base + HSIO_DIG_SERDES6G_MISC_CFG);

	serdes6g_write(base, addr);

	writel(HSIO_ANA_SERDES6G_IB_CFG_REG_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_EQZ_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_SAM_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_CONCUR |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_OFF(0) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_LP(2) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_MID(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_HP(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_CLK_SEL(0) |
	       HSIO_ANA_SERDES6G_IB_CFG_TERM_MODE_SEL(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_ICML_ADJ(5) |
	       HSIO_ANA_SERDES6G_IB_CFG_RTRM_ADJ(13) |
	       HSIO_ANA_SERDES6G_IB_CFG_VBULK_SEL |
	       HSIO_ANA_SERDES6G_IB_CFG_SOFSI(1),
	       base + HSIO_ANA_SERDES6G_IB_CFG);
	writel(HSIO_ANA_SERDES6G_IB_CFG1_FILT_OFFSET |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_LP |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_MID |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_HP |
	       HSIO_ANA_SERDES6G_IB_CFG1_SCALY(15) |
	       HSIO_ANA_SERDES6G_IB_CFG1_TSDET(16) |
	       HSIO_ANA_SERDES6G_IB_CFG1_TJTAG(8),
	       base + HSIO_ANA_SERDES6G_IB_CFG1);

	writel(0x0, base + HSIO_ANA_SERDES6G_SER_CFG);
	writel(HSIO_ANA_SERDES6G_COMMON_CFG_IF_MODE(ib_if_mode) |
	       HSIO_ANA_SERDES6G_COMMON_CFG_QRATE(ib_qrate) |
	       HSIO_ANA_SERDES6G_COMMON_CFG_ENA_LANE |
	       HSIO_ANA_SERDES6G_COMMON_CFG_SYS_RST,
	       base + HSIO_ANA_SERDES6G_COMMON_CFG);
	writel(HSIO_DIG_SERDES6G_MISC_CFG_LANE_RST,
	       base + HSIO_DIG_SERDES6G_MISC_CFG);

	writel(HSIO_ANA_SERDES6G_OB_CFG_RESISTOR_CTRL(1) |
	       HSIO_ANA_SERDES6G_OB_CFG_SR(7) |
	       HSIO_ANA_SERDES6G_OB_CFG_SR_H |
	       HSIO_ANA_SERDES6G_OB_CFG_ENA1V_MODE(ob_ena1v_mode) |
	       HSIO_ANA_SERDES6G_OB_CFG_POL, base + HSIO_ANA_SERDES6G_OB_CFG);
	writel(HSIO_ANA_SERDES6G_OB_CFG1_LEV(ob_lev) |
	       HSIO_ANA_SERDES6G_OB_CFG1_ENA_CAS(ob_ena_cas),
	       base + HSIO_ANA_SERDES6G_OB_CFG1);

	writel(HSIO_ANA_SERDES6G_DES_CFG_BW_ANA(des_bw_ana) |
	       HSIO_ANA_SERDES6G_DES_CFG_BW_HYST(5) |
	       HSIO_ANA_SERDES6G_DES_CFG_MBTR_CTRL(2) |
	       HSIO_ANA_SERDES6G_DES_CFG_PHS_CTRL(6),
	       base + HSIO_ANA_SERDES6G_DES_CFG);
	writel(HSIO_ANA_SERDES6G_PLL_CFG_FSM_CTRL_DATA(pll_fsm_ctrl_data) |
	       HSIO_ANA_SERDES6G_PLL_CFG_ENA_OFFS(3),
	       base + HSIO_ANA_SERDES6G_PLL_CFG);

	serdes6g_write(base, addr);

	/* set pll_fsm_ena = 1 */
	writel(HSIO_ANA_SERDES6G_PLL_CFG_FSM_ENA |
	       HSIO_ANA_SERDES6G_PLL_CFG_FSM_CTRL_DATA(pll_fsm_ctrl_data) |
	       HSIO_ANA_SERDES6G_PLL_CFG_ENA_OFFS(3),
	       base + HSIO_ANA_SERDES6G_PLL_CFG);

	serdes6g_write(base, addr);

	/* wait 20ms for pll bringup */
	mdelay(20);

	/* start IB calibration by setting ib_cal_ena and clearing lane_rst */
	writel(HSIO_ANA_SERDES6G_IB_CFG_REG_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_EQZ_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_SAM_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_CAL_ENA(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_CONCUR |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_OFF(0) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_LP(2) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_MID(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_HP(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_CLK_SEL(0) |
	       HSIO_ANA_SERDES6G_IB_CFG_TERM_MODE_SEL(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_ICML_ADJ(5) |
	       HSIO_ANA_SERDES6G_IB_CFG_RTRM_ADJ(13) |
	       HSIO_ANA_SERDES6G_IB_CFG_VBULK_SEL |
	       HSIO_ANA_SERDES6G_IB_CFG_SOFSI(1),
	       base + HSIO_ANA_SERDES6G_IB_CFG);
	writel(0x0, base + HSIO_DIG_SERDES6G_MISC_CFG);

	serdes6g_write(base, addr);

	/* wait 60 for calibration */
	mdelay(60);

	/* set ib_tsdet and ib_reg_pat_sel_offset back to correct values */
	writel(HSIO_ANA_SERDES6G_IB_CFG_REG_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_EQZ_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_SAM_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_CAL_ENA(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_CONCUR |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_ENA |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_OFF(0) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_LP(2) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_MID(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_REG_PAT_SEL_HP(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_SIG_DET_CLK_SEL(7) |
	       HSIO_ANA_SERDES6G_IB_CFG_TERM_MODE_SEL(1) |
	       HSIO_ANA_SERDES6G_IB_CFG_ICML_ADJ(5) |
	       HSIO_ANA_SERDES6G_IB_CFG_RTRM_ADJ(13) |
	       HSIO_ANA_SERDES6G_IB_CFG_VBULK_SEL |
	       HSIO_ANA_SERDES6G_IB_CFG_SOFSI(1),
	       base + HSIO_ANA_SERDES6G_IB_CFG);
	writel(HSIO_ANA_SERDES6G_IB_CFG1_FILT_OFFSET |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_LP |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_MID |
	       HSIO_ANA_SERDES6G_IB_CFG1_FILT_HP |
	       HSIO_ANA_SERDES6G_IB_CFG1_SCALY(15) |
	       HSIO_ANA_SERDES6G_IB_CFG1_TSDET(ib1_tsdet) |
	       HSIO_ANA_SERDES6G_IB_CFG1_TJTAG(8),
	       base + HSIO_ANA_SERDES6G_IB_CFG1);

	serdes6g_write(base, addr);
}

static void serdes1g_write(void __iomem *base, u32 addr)
{
	u32 data;

	writel(HSIO_MCB_SERDES1G_CFG_WR_ONE_SHOT |
	       HSIO_MCB_SERDES1G_CFG_ADDR(addr),
	       base + HSIO_MCB_SERDES1G_CFG);

	do {
		data = readl(base + HSIO_MCB_SERDES1G_CFG);
	} while (data & HSIO_MCB_SERDES1G_CFG_WR_ONE_SHOT);
}

static void serdes1g_setup(void __iomem *base, uint32_t addr,
			   phy_interface_t interface)
{
	writel(0x0, base + HSIO_ANA_SERDES1G_SER_CFG);
	writel(0x0, base + HSIO_DIG_SERDES1G_TP_CFG);
	writel(0x0, base + HSIO_DIG_SERDES1G_DFT_CFG0);
	writel(HSIO_ANA_SERDES1G_OB_CFG_RESISTOR_CTRL(1) |
	       HSIO_ANA_SERDES1G_OB_CFG_VCM_CTRL(4) |
	       HSIO_ANA_SERDES1G_OB_CFG_CMM_BIAS_CTRL(2) |
	       HSIO_ANA_SERDES1G_OB_CFG_AMP_CTRL(12) |
	       HSIO_ANA_SERDES1G_OB_CFG_SLP(3),
	       base + HSIO_ANA_SERDES1G_OB_CFG);
	writel(HSIO_ANA_SERDES1G_IB_CFG_RESISTOR_CTRL(13) |
	       HSIO_ANA_SERDES1G_IB_CFG_EQ_GAIN(2) |
	       HSIO_ANA_SERDES1G_IB_CFG_ENA_OFFSET_COMP |
	       HSIO_ANA_SERDES1G_IB_CFG_ENA_DETLEV |
	       HSIO_ANA_SERDES1G_IB_CFG_ENA_CMV_TERM |
	       HSIO_ANA_SERDES1G_IB_CFG_DET_LEV(3) |
	       HSIO_ANA_SERDES1G_IB_CFG_ACJTAG_HYST(1),
	       base + HSIO_ANA_SERDES1G_IB_CFG);
	writel(HSIO_ANA_SERDES1G_DES_CFG_BW_HYST(7) |
	       HSIO_ANA_SERDES1G_DES_CFG_BW_ANA(6) |
	       HSIO_ANA_SERDES1G_DES_CFG_MBTR_CTRL(2) |
	       HSIO_ANA_SERDES1G_DES_CFG_PHS_CTRL(6),
	       base + HSIO_ANA_SERDES1G_DES_CFG);
	writel(HSIO_DIG_SERDES1G_MISC_CFG_LANE_RST,
	       base + HSIO_DIG_SERDES1G_MISC_CFG);
	writel(HSIO_ANA_SERDES1G_PLL_CFG_FSM_ENA |
	       HSIO_ANA_SERDES1G_PLL_CFG_FSM_CTRL_DATA(0xc8) |
	       HSIO_ANA_SERDES1G_PLL_CFG_ENA_RC_DIV2,
	       base + HSIO_ANA_SERDES1G_PLL_CFG);
	writel(HSIO_ANA_SERDES1G_COMMON_CFG_IF_MODE |
	       HSIO_ANA_SERDES1G_COMMON_CFG_ENA_LANE |
	       HSIO_ANA_SERDES1G_COMMON_CFG_SYS_RST,
	       base + HSIO_ANA_SERDES1G_COMMON_CFG);

	serdes1g_write(base, addr);

	setbits_le32(base + HSIO_ANA_SERDES1G_COMMON_CFG,
		     HSIO_ANA_SERDES1G_COMMON_CFG_SYS_RST);

	serdes1g_write(base, addr);

	clrbits_le32(base + HSIO_DIG_SERDES1G_MISC_CFG,
		     HSIO_DIG_SERDES1G_MISC_CFG_LANE_RST);

	serdes1g_write(base, addr);
}


static void serdes10g_setup(struct jr2_private *priv, uint32_t port)
{
	void __iomem *tgt_ana;
	u32 val, indx = port - 49;

	writel(0x00200016, priv->regs[XGXFI0 + indx] + XFI_SHELL_XFI_MODE);

	tgt_ana = priv->regs[XGANA0 + indx];
	writel(0x7, tgt_ana + SD10G65_SD10G65_SBUS_RX_CFG);
	writel(0x7, tgt_ana + SD10G65_SD10G65_SBUS_TX_CFG);
	writel(0x2187, tgt_ana + SD10G65_SD10G65_OB_CFG0);
	writel(0x31fd7d, tgt_ana + SD10G65_SD10G65_TX_RCPLL_CFG2);
	writel(0x1ddc0117, tgt_ana + SD10G65_SD10G65_TX_SYNTH_CFG0);
	writel(0, tgt_ana + SD10G65_SD10G65_TX_SYNTH_CFG3);
	writel(0, tgt_ana + SD10G65_SD10G65_TX_SYNTH_CFG4);
	writel(0x1200008, tgt_ana + SD10G65_SD10G65_TX_SYNTH_CFG1);
	writel(0x1ddc001f, tgt_ana + SD10G65_SD10G65_TX_SYNTH_CFG0);
	writel(0x230000, tgt_ana + SD10G65_SD10G65_SSC_CFG1);
	writel(0x2127, tgt_ana + SD10G65_SD10G65_OB_CFG0);
	writel(0x42f0820, tgt_ana + SD10G65_SD10G65_OB_CFG1);
	writel(0x820820, tgt_ana + SD10G65_SD10G65_OB_CFG2);
	writel(0xa1e51d, tgt_ana + SD10G65_SD10G65_TX_RCPLL_CFG2);
	writel(0x2000021, tgt_ana + SD10G65_SD10G65_TX_RCPLL_CFG1);
	writel(0x20031, tgt_ana + SD10G65_SD10G65_TX_RCPLL_CFG0);
	mdelay(2);
	val = readl(tgt_ana + SD10G65_SD10G65_TX_RCPLL_STAT0);
	if ((SD10G65_SD10G65_TX_RCPLL_STAT0_PLLF_LOCK_STAT & val) == 0)
		debug("Error: SD10G65::SD10G65_TX_RCPLL_STAT0.PLLF_LOCK_STAT is not 1!\n");
	val = readl(tgt_ana + SD10G65_SD10G65_TX_RCPLL_STAT1);
	if ((SD10G65_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT & val) != 13)
		debug("Error: SD10G65_TX_RCPLL_STAT1.PLLF_FSM_STAT is not 13!\n");

	writel(0x7, tgt_ana + SD10G65_SD10G65_SBUS_RX_CFG);
	writel(0xa1e51d, tgt_ana + SD10G65_SD10G65_RX_RCPLL_CFG2);
	writel(0x1fcc35b, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG0);
	writel(0x14008, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG2);
	writel(0x4104ea6, tgt_ana + SD10G65_SD10G65_IB_CFG0);
	writel(0x811f0, tgt_ana + SD10G65_SD10G65_IB_CFG8);
	writel(0, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG3);
	writel(0, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG4);
	writel(0x5241008, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG1);
	writel(0x1fcc35b, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG0);
	writel(0, tgt_ana + SD10G65_SD10G65_RX_SYNTH_SYNC_CTRL);
	writel(0x1fcc35b, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CFG0);
	writel(0x14a52a3, tgt_ana + SD10G65_SD10G65_RX_SYNTH_CDRLF);
	writel(0x41f, tgt_ana + SD10G65_SD10G65_IB_CFG5);
	writel(0x2a17d0, tgt_ana + SD10G65_SD10G65_IB_CFG6);
	writel(0x183f8606, tgt_ana + SD10G65_SD10G65_IB_CFG7);
	writel(0x811f0, tgt_ana + SD10G65_SD10G65_IB_CFG8);
	writel(0x2a560, tgt_ana + SD10G65_SD10G65_IB_CFG4);
	writel(0x28294042, tgt_ana + SD10G65_SD10G65_IB_CFG3);
	writel(0x4c00080, tgt_ana + SD10G65_SD10G65_IB_CFG10);
	writel(0x7800, tgt_ana + SD10G65_SD10G65_IB_CFG11);
	writel(0x480, tgt_ana + SD10G65_SD10G65_MOEBDIV_CFG0);
	writel(0x6, tgt_ana + SD10G65_SD10G65_DES_CFG0);
	writel(0xa1e51d, tgt_ana + SD10G65_SD10G65_RX_RCPLL_CFG2);
	writel(0x2000021, tgt_ana + SD10G65_SD10G65_RX_RCPLL_CFG1);
	writel(0x20070, tgt_ana + SD10G65_SD10G65_RX_RCPLL_CFG0);
	mdelay(10);
	writel(0x20071, tgt_ana + SD10G65_SD10G65_RX_RCPLL_CFG0);
	writel(0x20031, tgt_ana + SD10G65_SD10G65_RX_RCPLL_CFG0);
	mdelay(2);
	val = readl(tgt_ana + SD10G65_SD10G65_RX_RCPLL_STAT0);
	if ((SD10G65_SD10G65_RX_RCPLL_STAT0_PLLF_LOCK_STAT & val) == 0)
		debug("Error: SD10G65::SD10G65_RX_RCPLL_STAT0.PLLF_LOCK_STAT is not 1!\n");
	val = readl(tgt_ana + SD10G65_SD10G65_RX_RCPLL_STAT1);
	if ((SD10G65_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT & val) != 13)
		debug("Error: SD10G65::SD10G65_RX_RCPLL_STAT1.PLLF_FSM_STAT is not 13!\n");
}

static int ram_init(u32 val, void __iomem *addr)
{
	writel(val, addr);

	if (wait_for_bit_le32(addr, BIT(1), false, 2000, false)) {
		printf("Timeout in memory reset, reg = 0x%08x\n", val);
		return 1;
	}

	return 0;
}

static int jr2_switch_init(struct jr2_private *priv)
{
	/* Initialize memories */
	ram_init(0x3, priv->regs[QSYS] + QSYS_RAM_CTRL_RAM_INIT);
	ram_init(0x3, priv->regs[ASM] + ASM_RAM_CTRL_RAM_INIT);
	ram_init(0x3, priv->regs[ANA_AC] + ANA_AC_RAM_CTRL_RAM_INIT);
	ram_init(0x3, priv->regs[REW] + REW_RAM_CTRL_RAM_INIT);

	/* Reset counters */
	writel(0x1, priv->regs[ANA_AC] + ANA_AC_STAT_GLOBAL_CFG_PORT_RESET);
	writel(0x1, priv->regs[ASM] + ASM_CFG_STAT_CFG);

	/* Enable switch-core and queue system */
	writel(0x1, priv->regs[QSYS] + QSYS_SYSTEM_RESET_CFG);

	return 0;
}

static void jr2_switch_config(struct jr2_private *priv)
{
	writel(0x55555555, priv->regs[QSYS] + QSYS_CALCFG_CAL_AUTO(0));
	writel(0x55555555, priv->regs[QSYS] + QSYS_CALCFG_CAL_AUTO(1));
	writel(0x55555555, priv->regs[QSYS] + QSYS_CALCFG_CAL_AUTO(2));
	writel(0x55555555, priv->regs[QSYS] + QSYS_CALCFG_CAL_AUTO(3));

	writel(readl(priv->regs[QSYS] + QSYS_CALCFG_CAL_CTRL) |
	       QSYS_CALCFG_CAL_CTRL_CAL_MODE(8),
	       priv->regs[QSYS] + QSYS_CALCFG_CAL_CTRL);
}

static int jr2_initialize(struct jr2_private *priv)
{
	int ret, i;

	/* Initialize switch memories, enable core */
	ret = jr2_switch_init(priv);
	if (ret)
		return ret;

	jr2_switch_config(priv);

	/*
	 * Disable port-to-port by switching
	 * Put front ports in "port isolation modes" - i.e. they can't send
	 * to other ports - via the PGID sorce masks.
	 */
	for (i = 0; i < MAX_PORT; i++) {
		writel(0, priv->regs[ANA_AC] + ANA_AC_SRC_CFG1(i));
		writel(0, priv->regs[ANA_AC] + ANA_AC_SRC_CFG2(i));
	}


	for (i = 0; i < MAX_PORT; i++)
		jr2_port_init(priv, i);

	jr2_cpu_capture_setup(priv);

	return 0;
}

static inline int jr2_vlant_wait_for_completion(struct jr2_private *priv)
{
	if (wait_for_bit_le32(priv->regs[LRN] + LRN_COMMON_ACCESS_CTRL,
			      LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT,
			      false, 2000, false))
		return -ETIMEDOUT;

	return 0;
}

static int jr2_mac_table_add(struct jr2_private *priv,
			     const unsigned char mac[ETH_ALEN], int pgid)
{
	u32 macl = 0, mach = 0;

	/*
	 * Set the MAC address to handle and the vlan associated in a format
	 * understood by the hardware.
	 */
	mach |= MAC_VID << 16;
	mach |= ((u32)mac[0]) << 8;
	mach |= ((u32)mac[1]) << 0;
	macl |= ((u32)mac[2]) << 24;
	macl |= ((u32)mac[3]) << 16;
	macl |= ((u32)mac[4]) << 8;
	macl |= ((u32)mac[5]) << 0;

	writel(mach, priv->regs[LRN] + LRN_COMMON_MAC_ACCESS_CFG0);
	writel(macl, priv->regs[LRN] + LRN_COMMON_MAC_ACCESS_CFG1);

	writel(LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_ADDR(pgid) |
	       LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_TYPE(0x3) |
	       LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_COPY |
	       LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_QU(0) |
	       LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_VLD |
	       LRN_COMMON_MAC_ACCESS_CFG2_MAC_ENTRY_LOCKED,
	       priv->regs[LRN] + LRN_COMMON_MAC_ACCESS_CFG2);

	writel(LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT,
	       priv->regs[LRN] + LRN_COMMON_ACCESS_CTRL);

	return jr2_vlant_wait_for_completion(priv);
}

static int jr2_write_hwaddr(struct udevice *dev)
{
	struct jr2_private *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_platdata(dev);

	return jr2_mac_table_add(priv, pdata->enetaddr, PGID_UNICAST);
}

static void serdes_setup(struct jr2_private *priv)
{
	size_t mask;
	int i = 0;

	for (i = 0; i < MAX_PORT; ++i) {
		if (!priv->ports[i].bus || priv->ports[i].serdes_index == 0xff)
			continue;

		mask = BIT(priv->ports[i].serdes_index);
		if (priv->ports[i].serdes_index < SERDES1G_MAX) {
			serdes1g_setup(priv->regs[HSIO], mask,
				       priv->ports[i].phy_mode);
		} else if (priv->ports[i].serdes_index < SERDES6G_MAX) {
			mask >>= SERDES6G(0);
			serdes6g_setup(priv->regs[HSIO], mask,
				       priv->ports[i].phy_mode);
		} else {
			serdes10g_setup(priv, i);
		}
	}
}

static int jr2_start(struct udevice *dev)
{
	struct jr2_private *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_platdata(dev);
	const unsigned char mac[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff,
		0xff };
	int ret;

	ret = jr2_initialize(priv);
	if (ret)
		return ret;

	/* Set MAC address tables entries for CPU redirection */
	ret = jr2_mac_table_add(priv, mac, PGID_BROADCAST);
	if (ret)
		return ret;

	ret = jr2_mac_table_add(priv, pdata->enetaddr, PGID_UNICAST);
	if (ret)
		return ret;

	serdes_setup(priv);

	return 0;
}

static void jr2_stop(struct udevice *dev)
{
}

static int jr2_send(struct udevice *dev, void *packet, int length)
{
	struct jr2_private *priv = dev_get_priv(dev);
	u32 ifh[IFH_LEN];
	u32 *buf = packet;

	memset(ifh, '\0', IFH_LEN);

	/* Set DST PORT_MASK */
	ifh[0] = htonl(0);
	ifh[1] = htonl(0x1FFFFF);
	ifh[2] = htonl(~0);
	/* Set DST_MODE to INJECT and UPDATE_FCS */
	ifh[5] = htonl(0x4c0);

	return mscc_send(priv->regs[QS], jr2_regs_qs,
			 ifh, IFH_LEN, buf, length);
}

static int jr2_recv(struct udevice *dev, int flags, uchar **packetp)
{
	struct jr2_private *priv = dev_get_priv(dev);
	u32 *rxbuf = (u32 *)net_rx_packets[0];
	int byte_cnt = 0;

	byte_cnt = mscc_recv(priv->regs[QS], jr2_regs_qs, rxbuf, IFH_LEN,
			     false);

	*packetp = net_rx_packets[0];

	return byte_cnt;
}

static struct mii_dev *get_mdiobus(phys_addr_t base, unsigned long size)
{
	int i = 0;

	for (i = 0; i < JR2_MIIM_BUS_COUNT; ++i)
		if (miim[i].miim_base == base && miim[i].miim_size == size)
			return miim[i].bus;

	return NULL;
}

static void add_port_entry(struct jr2_private *priv, size_t index,
			   size_t phy_addr, struct mii_dev *bus,
			   u8 serdes_index, u8 phy_mode)
{
	priv->ports[index].phy_addr = phy_addr;
	priv->ports[index].bus = bus;
	priv->ports[index].serdes_index = serdes_index;
	priv->ports[index].phy_mode = phy_mode;
}

static int jr2_probe(struct udevice *dev)
{
	struct jr2_private *priv = dev_get_priv(dev);
	int i;
	int ret;
	struct resource res;
	fdt32_t faddr;
	phys_addr_t addr_base;
	unsigned long addr_size;
	ofnode eth_node, node, mdio_node;
	size_t phy_addr;
	struct mii_dev *bus;
	struct ofnode_phandle_args phandle;
	struct phy_device *phy;
	u32 val;

	if (!priv)
		return -EINVAL;

	/* Get registers and map them to the private structure */
	for (i = 0; i < ARRAY_SIZE(regs_names); i++) {
		priv->regs[i] = dev_remap_addr_name(dev, regs_names[i]);
		if (!priv->regs[i]) {
			debug
			    ("Error can't get regs base addresses for %s\n",
			     regs_names[i]);
			return -ENOMEM;
		}
	}

	val = readl(priv->regs[ICPU] + ICPU_RESET);
	val |= ICPU_RESET_CORE_RST_PROTECT;
	writel(val, priv->regs[ICPU] + ICPU_RESET);

	val = readl(priv->regs[GCB] + PERF_SOFT_RST);
	val |= PERF_SOFT_RST_SOFT_SWC_RST;
	writel(val, priv->regs[GCB] + PERF_SOFT_RST);

	while (readl(priv->regs[GCB] + PERF_SOFT_RST) & PERF_SOFT_RST_SOFT_SWC_RST)
		;

	/* Initialize miim buses */
	memset(&miim, 0x0, sizeof(struct mscc_miim_dev) * JR2_MIIM_BUS_COUNT);

	/* iterate all the ports and find out on which bus they are */
	i = 0;
	eth_node = dev_read_first_subnode(dev);
	for (node = ofnode_first_subnode(eth_node);
	     ofnode_valid(node);
	     node = ofnode_next_subnode(node)) {
		if (ofnode_read_resource(node, 0, &res))
			return -ENOMEM;
		i = res.start;

		ret = ofnode_parse_phandle_with_args(node, "phy-handle", NULL,
						     0, 0, &phandle);
		if (ret)
			continue;

		/* Get phy address on mdio bus */
		if (ofnode_read_resource(phandle.node, 0, &res))
			return -ENOMEM;
		phy_addr = res.start;

		/* Get mdio node */
		mdio_node = ofnode_get_parent(phandle.node);

		if (ofnode_read_resource(mdio_node, 0, &res))
			return -ENOMEM;
		faddr = cpu_to_fdt32(res.start);

		addr_base = ofnode_translate_address(mdio_node, &faddr);
		addr_size = res.end - res.start;

		/* If the bus is new then create a new bus */
		bus = get_mdiobus(addr_base, addr_size);
		if (!bus) {
			bus = mscc_mdiobus_init(miim, miim_count, addr_base,
						addr_size);
			if (!bus)
				return -ENOMEM;
			priv->bus[miim_count++] = bus;
		}

		/* Get serdes info */
		ret = ofnode_parse_phandle_with_args(node, "phys", NULL,
						     3, 0, &phandle);
		if (ret)
			return -ENOMEM;

		add_port_entry(priv, i, phy_addr, bus, phandle.args[1],
			       phandle.args[2]);
	}

	for (i = 0; i < MAX_PORT; i++) {
		if (!priv->ports[i].bus)
			continue;

		phy = phy_connect(priv->ports[i].bus,
				  priv->ports[i].phy_addr, dev,
				  PHY_INTERFACE_MODE_NONE);
		if (phy) {
			if (i != NPI_PORT) {
				board_phy_config(phy);
			} else {
				phy_write(phy, 0, 23, 0xba20); /* Set SGMII mode */
				phy_write(phy, 0,  0, 0x9040); /* Reset */
				phy_write(phy, 0,  4, 0x0de1); /* Setup ANEG */
				phy_write(phy, 0,  9, 0x0200); /* Setup ANEG */
				phy_write(phy, 0,  0, 0x1240); /* Restart ANEG */
			}
		}
	}

	return 0;
}

static int jr2_remove(struct udevice *dev)
{
	struct jr2_private *priv = dev_get_priv(dev);
	int i;

	for (i = 0; i < JR2_MIIM_BUS_COUNT; i++) {
		mdio_unregister(priv->bus[i]);
		mdio_free(priv->bus[i]);
	}

	return 0;
}

static const struct eth_ops jr2_ops = {
	.start        = jr2_start,
	.stop         = jr2_stop,
	.send         = jr2_send,
	.recv         = jr2_recv,
	.write_hwaddr = jr2_write_hwaddr,
};

static const struct udevice_id mscc_jr2_ids[] = {
	{.compatible = "mscc,vsc7454-switch" },
	{ /* Sentinel */ }
};

U_BOOT_DRIVER(jr2) = {
	.name				= "jr2-switch",
	.id				= UCLASS_ETH,
	.of_match			= mscc_jr2_ids,
	.probe				= jr2_probe,
	.remove				= jr2_remove,
	.ops				= &jr2_ops,
	.priv_auto_alloc_size		= sizeof(struct jr2_private),
	.platdata_auto_alloc_size	= sizeof(struct eth_pdata),
};
