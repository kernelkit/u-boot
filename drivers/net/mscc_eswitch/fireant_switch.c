// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Microsemi Corporation
 */

//#define DEBUG

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
#include <command.h>

#include "mscc_xfer.h"
#include "mscc_miim.h"

#include "mscc_fa_regs_cpu.h"
#include "mscc_fa_regs_devcpu_gcb.h"

#include <dt-bindings/mscc/fireant_data.h>

#if defined(CONFIG_DDR_FIREANT_PCB134)
/* Gross hack to enable Cupper SFPs */
#include "mscc_fa_regs_devcpu_gcb.h"
#endif

#define FIREANT_MIIM_BUS_COUNT 4

static struct mscc_miim_dev miim[FIREANT_MIIM_BUS_COUNT];
static int miim_count;
static struct fireant_private *dev_priv;

#define MAX_PORT		65
#define NPI_PORT		(MAX_PORT-1)
#define CPU_PORT		MAX_PORT
#define MAC_VID			1 /* Also = FID 1 */
#define PGID_L2_UC		(MAX_PORT + 0)
#define PGID_L2_MC		(MAX_PORT + 1)
#define PGID_BASE         	(MAX_PORT + 10)
#define PGID_BROADCAST		(PGID_BASE + 0)
#define PGID_HOST		(PGID_BASE + 1)
#define ETH_ALEN		6
#define IFH_LEN			9 /* 36 bytes */

static const char * const regs_names[] = {
	"port0", "port1", "port2", "port3", "port4", "port5", "port6",
	"port7", "port8", "port9", "port10", "port11", "port12", "port13",
	"port14", "port15", "port16", "port17", "port18", "port19", "port20",
	"port21", "port22", "port23", "port24", "port25", "port26", "port27",
	"port28", "port29", "port30", "port31", "port32", "port33", "port34",
	"port35", "port36", "port37", "port38", "port39", "port40", "port41",
	"port42", "port43", "port44", "port45", "port46", "port47", "port48",
	"port49", "port50", "port51", "port52", "port53", "port54", "port55",
	"port56", "port57", "port58", "port59", "port60", "port61", "port62",
	"port63", "port64",
	"ana_ac", "ana_cl", "ana_l2", "ana_l3", "asm", "lrn",
	"qfwd", "qs", "qsys", "rew",
	"vop", "dsm", "eacl", "vcap_super", "hsch", "port_conf",
};

#define REGS_NAMES_COUNT ARRAY_SIZE(regs_names) + 1

enum fireant_ctrl_regs {
	ANA_AC = MAX_PORT,
	ANA_CL,
	ANA_L2,
	ANA_L3,
	ASM,
	LRN,
	QFWD,
	QS,
	QSYS,
	REW,
	VOP,
	DSM,
	EACL,
	VCAP_SUPER,
	HSCH,
	PORT_CONF,
};

#define SWITCHREG(base, roff)             (base + (4*(roff)))
#define SWITCHREG_IX(t, o, g, gw, r, ro)  SWITCHREG(t, (o) + ((g) * (gw)) + (ro) + (r))

/* RAM init regs */
#define ANA_AC_RAM_INIT(base)        SWITCHREG(base, 0x33371)
#define QSYS_RAM_INIT(base)          SWITCHREG(base, 0x24a)
#define ASM_RAM_INIT(base)           SWITCHREG(base, 0x2204)
#define REW_RAM_INIT(base)           SWITCHREG(base, 0x171d2)
#define DSM_RAM_INIT(base)           SWITCHREG(base, 0x0)
#define EACL_RAM_INIT(base)          SWITCHREG(base, 0x73f4)
#define VCAP_SUPER_RAM_INIT(base)    SWITCHREG(base, 0x118)
#define VOP_RAM_INIT(base)           SWITCHREG(base, 0x110a2)

/* Switch registers */
#define ANA_AC_STAT_PORT_STAT_RESET(base) SWITCHREG(base, 0x33f9c)
#define ANA_AC_PGID_CFG(base, gi)         SWITCHREG_IX(base,0x30000,gi,4,0,0)
#define ANA_AC_PGID_CFG1(base, gi)        SWITCHREG_IX(base,0x30000,gi,4,0,1)
#define ANA_AC_PGID_CFG2(base, gi)        SWITCHREG_IX(base,0x30000,gi,4,0,2)
#define ANA_AC_PGID_MISC_CFG(base, gi)    SWITCHREG_IX(base,0x30000,gi,4,0,3)
#define ANA_AC_SRC_CFG0(base, gi)	  SWITCHREG_IX(base,0x33e00,gi,4,0,0)
#define ANA_AC_SRC_CFG1(base, gi)	  SWITCHREG_IX(base,0x33e00,gi,4,0,1)
#define ANA_AC_SRC_CFG2(base, gi)	  SWITCHREG_IX(base,0x33e00,gi,4,0,2)
#define ASM_STAT_CFG(base)                SWITCHREG(base, 0x2080)
#define QSYS_CAL_AUTO(base, ri)           SWITCHREG(base, 0x240 + (ri))
#define QSYS_CAL_CTRL(base)               SWITCHREG(base, 0x249)
#define  QSYS_CAL_CTRL_CAL_MODE(x)               (GENMASK(14,11) & ((x) << 11))
#define  QSYS_CAL_CTRL_CAL_MODE_MASK             GENMASK(14,11)
#define ASM_PORT_CFG(base, ri)            SWITCHREG(base, 0x2107 + (ri))
#define  ASM_PORT_CFG_PAD_ENA		         BIT(6)
#define  ASM_PORT_CFG_NO_PREAMBLE_ENA            BIT(9)
#define  ASM_PORT_CFG_INJ_FORMAT_CFG(x)          (GENMASK(3,2) & ((x) << 2))
#define QS_INJ_GRP_CFG(base, ri)          SWITCHREG(base, 0x9 + (ri))
#define QS_XTR_GRP_CFG(base, ri)          SWITCHREG(base, 0x0 + (ri))
#define QFWD_SWITCH_PORT_MODE(base, ri)   SWITCHREG(base, 0x0 + (ri))
#define  QFWD_SWITCH_PORT_MODE_PORT_ENA          BIT(19)
#define ANA_L2_FWD_CFG(base)              SWITCHREG(base, 0x228c2)
#define  ANA_L2_FWD_CFG_CPU_DMAC_COPY_ENA        BIT(6)
#define ANA_L2_LRN_CFG(base)              SWITCHREG(base, 0x228c3)
#define  ANA_L2_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA BIT(16)
#define DEV1G_PCS1G_CFG(target)           SWITCHREG(target, 0x16)
#define  DEV1G_PCS1G_CFG_PCS_ENA                 BIT(0)
#define DEV1G_USXGMII_PCS_SD_CFG(target)  SWITCHREG(target, 0xb)
#define DEV1G_MAC_ENA_CFG(target)         SWITCHREG(target, 0xd)
#define  DEV1G_MAC_ENA_CFG_TX_ENA                BIT(0)
#define  DEV1G_MAC_ENA_CFG_RX_ENA                BIT(4)
#define DEV1G_PCS1G_MODE_CFG(target)      SWITCHREG(target, 0x17)
#define  DEV1G_PCS1G_MODE_CFG_SGMII_MODE_ENA     BIT(0)
#define DEV1G_PCS1G_ANEG_CFG(target)      SWITCHREG(target, 0x19)
#define  DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(x)     (GENMASK(31,16) & ((x) << 16))
#define  DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA        BIT(8)
#define  DEV1G_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT BIT(1)
#define  DEV1G_PCS1G_ANEG_CFG_ANEG_ENA              BIT(0)
#define DEV1G_PCS1G_ANEG_STATUS(target)   SWITCHREG(target, 0x1e)
#define  DEV1G_PCS1G_ANEG_STATUS_ANEG_COMPLETE	    BIT(0)
#define DEV1G_PCS1G_LINK_STATUS(target)	  SWITCHREG(target,0x20)
#define  DEV1G_PCS1G_LINK_STATUS_LINK_UP	    BIT(4)
#define DEV1G_MAC_IFG_CFG(target)         SWITCHREG(target, 0x13)
#define  DEV1G_MAC_IFG_CFG_TX_IFG(x)             (GENMASK(12,8) & ((x) << 8))
#define  DEV1G_MAC_IFG_CFG_RX_IFG2(x)            (GENMASK(7,4) & ((x) << 4))
#define  DEV1G_MAC_IFG_CFG_RX_IFG1(x)            (GENMASK(3,0) & ((x) << 0))
#define DEV1G_DEV_RST_CTRL(target)        SWITCHREG(target, 0x0)
#define  DEV1G_DEV_RST_CTRL_SPEED_SEL(x)         (GENMASK(22,20) & ((x) << 20))
#define  DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST       BIT(17)
#define  DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST       BIT(16)
#define ANA_CL_VLAN_CTRL(base, gi)        SWITCHREG_IX(base,0x8000,gi,128,0,8)
#define  ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA         BIT(19)
#define  ANA_CL_VLAN_CTRL_VLAN_POP_CNT(x)        (GENMASK(18,17) & ((x) << 17))
#define ANA_CL_CAPTURE_BPDU_CFG(target, gi) SWITCHREG_IX(target,0x8000,gi,128,0,49)
#define ANA_CL_FILTER_CTRL(target, gi)      SWITCHREG_IX(target,0x8000,gi,128,0,1)
#define  ANA_CL_FILTER_CTRL_FORCE_FCS_UPDATE_ENA BIT(0)
#define LRN_COMMON_ACCESS_CTRL(base)      SWITCHREG(base, 0x0)
#define  LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(x)  (GENMASK(4,1) & ((x) << 1))
#define  LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT     BIT(0)
#define LRN_MAC_ACCESS_CFG0(base)         SWITCHREG(base, 0x1)
#define LRN_MAC_ACCESS_CFG1(base)         SWITCHREG(base, 0x2)
#define LRN_MAC_ACCESS_CFG2(base)         SWITCHREG(base, 0x3)
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_ADDR(x)     (GENMASK(11,0) & ((x) << 0))
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_ADDR_MASK   GENMASK(11,0)
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_TYPE(x)     (GENMASK(14,12) & ((x) << 12))
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_VLD         BIT(15)
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_LOCKED      BIT(16)
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_COPY    BIT(23)
#define  LRN_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_QU(x)   (GENMASK(26,24) & ((x) << 24))
#define LRN_SCAN_NEXT_CFG(base)           SWITCHREG(base, 0x5)
#define  LRN_SCAN_NEXT_CFG_UNTIL_FOUND_ENA         BIT(10)
#define  LRN_SCAN_NEXT_CFG_IGNORE_LOCKED_ENA	   BIT(7)
#define HSCH_RESET_CFG(base)              SWITCHREG(base, 0x9e92)
#define PORT_CONF_DEV5G_MODES(base)       SWITCHREG(base, 0x0)
#define  PORT_CONF_DEV5G_MODES_P64_SGMII           BIT(12)
#define  PORT_CONF_DEV5G_MODES_P0_11		   GENMASK(11,0)
#define PORT_CONF_DEV10G_MODES(base)      SWITCHREG(base, 0x1)
#define DSM_DEV_TX_STOP_WM_CFG(base, ri)  SWITCHREG(base, 0x159 + (ri))
#define  DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA  BIT(8)
#define ANA_L3_VLAN_CTRL(base)            SWITCHREG(base, 0x1e211)
#define ANA_L3_VLAN_CFG(base, gi)         SWITCHREG_IX(base,0x0,gi,16,0,2)

static const unsigned long fireant_regs_qs[] = {
	[MSCC_QS_XTR_RD] = 0x8,
	[MSCC_QS_XTR_FLUSH] = 0x18,
	[MSCC_QS_XTR_DATA_PRESENT] = 0x1c,
	[MSCC_QS_INJ_WR] = 0x2c,
	[MSCC_QS_INJ_CTRL] = 0x34,
};

#define IFH_FMT_NONE  0		/* No IFH */
#define IFH_FMT_IFH   1		/* Only IFH */
#define IFH_FMT_SHORT 2		/* MAC encap, IFH */

#define CONFIG_IFH_FMT     IFH_FMT_NONE
#define CONFIG_VLAN_ENABLE
//#define CONFIG_CPU_PGID_ENA
//#define CONFIG_CPU_BPDU_ENA
#define CONFIG_CPU_MACENTRY_ENA

#define IFH_ID_FIREANT			0x0b
static u8 ifh_fireant[] =
{
#if (CONFIG_IFH_FMT == IFH_FMT_SHORT)
	/* MAC (long) encapsulation (MAC_ENCAP_LEN) */
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x88, 0x80, 0x00, IFH_ID_FIREANT,
#endif
	/* IFH start */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* v-rsv1 = 1 */
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* f-update-fcs 1 f-src-port 66 m-pipeline-act 2 */
	0x00, 0x00, 0x00, 0x08, 0x00, 0x10, 0x88, 0x00,
	0x00, 0x00, 0x00, 0x00,
	/* Ethernet hdr hereafter */
};

enum {
	SERDES_ARG_MAC_TYPE,
	SERDES_ARG_SERDES,
	SERDES_ARG_SER_IDX,
	SERDES_ARG_MAX,
};

struct fireant_phy_port {
	bool active;
	struct mii_dev *bus;
	u8 phy_addr;
	u32 serdes_args[SERDES_ARG_MAX];
	struct phy_device *phy;
};

struct fireant_private {
	void __iomem *regs[REGS_NAMES_COUNT];
	struct mii_dev *bus[FIREANT_MIIM_BUS_COUNT];
	struct fireant_phy_port ports[MAX_PORT];
};

extern void fireant_serdes_port_init(int port,
				     u32 mac_type,
				     u32 serdes_type,
				     u32 serdes_idx);

extern void fireant_serdes_cmu_init(void);

static void hexdump(u8 *buf, int len)
{
#if 0
	int i;

	len = min(len, 60);
	for (i = 0; i < len; i++) {
		if ((i % 16) == 0)
			printf("%s%04x: ", i ? "\n" : "", i);
		printf("%02x ", buf[i]);
	}
	printf("\n");
#endif
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

static bool has_link(struct fireant_private *priv, int port)
{
	u32 mask, val;
	if (priv->ports[port].bus) {
		val = readl(DEV1G_PCS1G_LINK_STATUS(priv->regs[port]));
		mask = DEV1G_PCS1G_LINK_STATUS_LINK_UP;
	} else {
		val = readl(DEV1G_PCS1G_ANEG_STATUS(priv->regs[port]));
		mask = DEV1G_PCS1G_ANEG_STATUS_ANEG_COMPLETE;
	}
	return !!(val & mask);
}

static int fireant_switch_init(struct fireant_private *priv)
{
	debug("%s\n", __FUNCTION__);

	/* Initialize memories */
	ram_init(0x3, QSYS_RAM_INIT(priv->regs[QSYS]));
	ram_init(0x3, ASM_RAM_INIT(priv->regs[ASM]));
	ram_init(0x3, ANA_AC_RAM_INIT(priv->regs[ANA_AC]));
	ram_init(0x3, REW_RAM_INIT(priv->regs[REW]));
	ram_init(0x3, DSM_RAM_INIT(priv->regs[DSM]));
	ram_init(0x3, EACL_RAM_INIT(priv->regs[EACL]));
	ram_init(0x3, VCAP_SUPER_RAM_INIT(priv->regs[VCAP_SUPER]));
	ram_init(0x3, VOP_RAM_INIT(priv->regs[VOP]));

	/* Reset counters */
	writel(0x1, ANA_AC_STAT_PORT_STAT_RESET(priv->regs[ANA_AC]));
	writel(0x1, ASM_STAT_CFG(priv->regs[ASM]));

	return 0;
}

static void fireant_switch_config(struct fireant_private *priv)
{
	int i;

	debug("%s\n", __FUNCTION__);

	/* Halt the calendar while changing it */
	clrsetbits_le32(QSYS_CAL_CTRL(priv->regs[QSYS]),
			QSYS_CAL_CTRL_CAL_MODE_MASK,
			QSYS_CAL_CTRL_CAL_MODE(10));

	for (i = 0; i < 7; i++)
		/* All ports to '001' - 1Gb/s */
		writel(01111111111, QSYS_CAL_AUTO(priv->regs[QSYS], i));

	/* Enable Auto mode */
	clrsetbits_le32(QSYS_CAL_CTRL(priv->regs[QSYS]),
			QSYS_CAL_CTRL_CAL_MODE_MASK,
			QSYS_CAL_CTRL_CAL_MODE(8));

	/* Configure NPI port */
	if (priv->ports[NPI_PORT].serdes_args[SERDES_ARG_MAC_TYPE] == IF_SGMII)
		setbits_le32(PORT_CONF_DEV5G_MODES(priv->regs[PORT_CONF]),
			     PORT_CONF_DEV5G_MODES_P64_SGMII);
	else
		clrbits_le32(PORT_CONF_DEV5G_MODES(priv->regs[PORT_CONF]),
			     PORT_CONF_DEV5G_MODES_P64_SGMII);

	/* Enable all 10G ports */
	writel(0xFFF, PORT_CONF_DEV10G_MODES(priv->regs[PORT_CONF]));

	/* Enable shadow 10G interfaces */
	for (i = 0; i < MAX_PORT; i++) {
		struct fireant_phy_port *p = &priv->ports[i];
		if (p->active)
			setbits_le32(DSM_DEV_TX_STOP_WM_CFG(priv->regs[DSM], i),
				     DSM_DEV_TX_STOP_WM_CFG_DEV10G_SHADOW_ENA);
	}

	/* Init (all) CMUs */
	fireant_serdes_cmu_init();

#if defined(CONFIG_DDR_FIREANT_PCB134)
	/* SGPIO HACK */
	writel(0x00060051, MSCC_DEVCPU_GCB_SIO_CFG(2));
	writel(0x00001410, MSCC_DEVCPU_GCB_SIO_CLOCK(2));
	writel(0xfffff000, MSCC_DEVCPU_GCB_SIO_PORT_ENA(2));
	writel(0x00000fff, MSCC_DEVCPU_GCB_SIO_INTR_POL(2, 0));
	writel(0xffffffff, MSCC_DEVCPU_GCB_SIO_INTR_POL(2, 1));
	writel(0x00000fff, MSCC_DEVCPU_GCB_SIO_INTR_POL(2, 2));
	writel(0xffffffff, MSCC_DEVCPU_GCB_SIO_INTR_POL(2, 3));
	for (i = 12; i < 32; i++)
		writel(0x00049000, MSCC_DEVCPU_GCB_SIO_PORT_CFG(2, i));
#endif

	/* BCAST/CPU pgid */
	writel(0xffffffff, ANA_AC_PGID_CFG(priv->regs[ANA_AC], PGID_BROADCAST));
	writel(0xffffffff, ANA_AC_PGID_CFG1(priv->regs[ANA_AC], PGID_BROADCAST));
	writel(0x00000001, ANA_AC_PGID_CFG2(priv->regs[ANA_AC], PGID_BROADCAST));
	writel(0x00000000, ANA_AC_PGID_CFG(priv->regs[ANA_AC], PGID_HOST));
	writel(0x00000000, ANA_AC_PGID_CFG1(priv->regs[ANA_AC], PGID_HOST));
	writel(0x00000000, ANA_AC_PGID_CFG2(priv->regs[ANA_AC], PGID_HOST));

	/*
	 * Disable port-to-port by switching
	 * Put front ports in "port isolation modes" - i.e. they can't send
	 * to other ports - via the PGID sorce masks.
	 */
	for (i = 0; i < MAX_PORT; i++) {
		writel(0, ANA_AC_SRC_CFG0(priv->regs[ANA_AC], i));
		writel(0, ANA_AC_SRC_CFG1(priv->regs[ANA_AC], i));
		writel(0, ANA_AC_SRC_CFG2(priv->regs[ANA_AC], i));
	}

#if defined(CONFIG_CPU_PGID_ENA)
	/* CPU copy UC+MC:FLOOD */
	writel(1, ANA_AC_PGID_MISC_CFG(priv->regs[ANA_AC], PGID_L2_MC));
	writel(1, ANA_AC_PGID_MISC_CFG(priv->regs[ANA_AC], PGID_L2_UC));
#endif

	/* HACK: Convenience XQS XQS:SYSTEM:STAT_CFG */
	writel(CPU_PORT << 5, 0x6110c1dcc);

#if defined(CONFIG_VLAN_ENABLE)
	/* VLAN aware CPU port */
	writel(ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA |
	       ANA_CL_VLAN_CTRL_VLAN_POP_CNT(1) |
	       MAC_VID,
	       ANA_CL_VLAN_CTRL(priv->regs[ANA_CL], CPU_PORT));
	/* XXX: Map PVID = FID, DISABLE LEARNING  */
	writel((MAC_VID << 8) | BIT(3),
	       ANA_L3_VLAN_CFG(priv->regs[ANA_L3], MAC_VID));
	/* Enable VLANs */
	writel(1, ANA_L3_VLAN_CTRL(priv->regs[ANA_L3]));
#endif

	/* Enable switch-core and queue system */
	writel(0x1, HSCH_RESET_CFG(priv->regs[HSCH]));

	/* Flush queues */
	mscc_flush(priv->regs[QS], fireant_regs_qs);
}

static void fireant_cpu_capture_setup(struct fireant_private *priv)
{
	debug("%s\n", __FUNCTION__);

	/* ASM CPU port: No preamble/IFH, enable padding */
	writel(ASM_PORT_CFG_PAD_ENA |
	       ASM_PORT_CFG_NO_PREAMBLE_ENA |
	       ASM_PORT_CFG_INJ_FORMAT_CFG(CONFIG_IFH_FMT),
	       ASM_PORT_CFG(priv->regs[ASM], CPU_PORT));

	/* Set Manual injection via DEVCPU_QS registers for CPU queue 0 */
	writel(0x5, QS_INJ_GRP_CFG(priv->regs[QS], 0));

	/* Set Manual extraction via DEVCPU_QS registers for CPU queue 0 */
	writel(0x7, QS_XTR_GRP_CFG(priv->regs[QS], 0));

	/* Enable CPU port for any frame transfer */
	setbits_le32(QFWD_SWITCH_PORT_MODE(priv->regs[QFWD], CPU_PORT),
		     QFWD_SWITCH_PORT_MODE_PORT_ENA);

	/* Recalc injected frame FCS */
	setbits_le32(ANA_CL_FILTER_CTRL(priv->regs[ANA_CL], CPU_PORT),
		     ANA_CL_FILTER_CTRL_FORCE_FCS_UPDATE_ENA);

#if 0
	/* Enable basic learning mode */
	setbits_le32(ANA_L2_LRN_CFG(priv->regs[ANA_L2]),
		     ANA_L2_LRN_CFG_VSTAX_BASIC_LRN_MODE_ENA);
#endif

	/* Send a copy to CPU when found as forwarding entry */
	setbits_le32(ANA_L2_FWD_CFG(priv->regs[ANA_L2]),
		     ANA_L2_FWD_CFG_CPU_DMAC_COPY_ENA);
}

static void fireant_port_init(struct fireant_private *priv, int port, u32 mac_if)
{
	void __iomem *regs = priv->regs[port];
	u32 *serdes_args = priv->ports[port].serdes_args;

	debug("%s: port %d\n", __FUNCTION__, port);

	fireant_serdes_port_init(port,
				 serdes_args[SERDES_ARG_MAC_TYPE],
				 serdes_args[SERDES_ARG_SERDES],
				 serdes_args[SERDES_ARG_SER_IDX]);
	/* Enable PCS */
	writel(DEV1G_PCS1G_CFG_PCS_ENA, DEV1G_PCS1G_CFG(regs));

	/* Disable Signal Detect */
	writel(0, DEV1G_USXGMII_PCS_SD_CFG(regs));

	/* Enable MAC RX and TX */
	writel(DEV1G_MAC_ENA_CFG_TX_ENA |
	       DEV1G_MAC_ENA_CFG_RX_ENA,
	       DEV1G_MAC_ENA_CFG(regs));

	/* Enable sgmii_mode_ena */
	writel(DEV1G_PCS1G_MODE_CFG_SGMII_MODE_ENA, DEV1G_PCS1G_MODE_CFG(regs));

	if (mac_if == IF_SGMII) {
		/*
		 * Clear sw_resolve_ena(bit 0) and set adv_ability to
		 * something meaningful just in case
		 */
		writel(DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(0x20),
		       DEV1G_PCS1G_ANEG_CFG(regs));
	} else {
		/* IF_SGMII_CISCO */
		writel(DEV1G_PCS1G_ANEG_CFG_ADV_ABILITY(0x0001) |
		       DEV1G_PCS1G_ANEG_CFG_SW_RESOLVE_ENA |
		       DEV1G_PCS1G_ANEG_CFG_ANEG_ENA |
		       DEV1G_PCS1G_ANEG_CFG_ANEG_RESTART_ONE_SHOT,
		       DEV1G_PCS1G_ANEG_CFG(regs));
	}

	/* Set MAC IFG Gaps */
	writel(DEV1G_MAC_IFG_CFG_TX_IFG(4) |
	       DEV1G_MAC_IFG_CFG_RX_IFG1(5) |
	       DEV1G_MAC_IFG_CFG_RX_IFG2(1),
	       DEV1G_MAC_IFG_CFG(regs));

	/* Set link speed and release all resets but USX */
	writel(DEV1G_DEV_RST_CTRL_SPEED_SEL(2) |
	       DEV1G_DEV_RST_CTRL_USX_PCS_TX_RST |
	       DEV1G_DEV_RST_CTRL_USX_PCS_RX_RST,
	       DEV1G_DEV_RST_CTRL(regs));

#if defined(CONFIG_VLAN_ENABLE)
	/* Make VLAN aware for CPU traffic */
	writel(ANA_CL_VLAN_CTRL_VLAN_AWARE_ENA |
	       ANA_CL_VLAN_CTRL_VLAN_POP_CNT(1) |
	       MAC_VID,
	       ANA_CL_VLAN_CTRL(priv->regs[ANA_CL], port));
#endif

#if defined(CONFIG_CPU_BPDU_ENA)
	/* Enable BPDU redirect for debugging */
	writel(0x55555555, ANA_CL_CAPTURE_BPDU_CFG(priv->regs[ANA_CL], port));
#endif

	/* Enable CPU port for any frame transfer */
	setbits_le32(QFWD_SWITCH_PORT_MODE(priv->regs[QFWD], port),
		     QFWD_SWITCH_PORT_MODE_PORT_ENA);
}

static inline int fireant_vlant_wait_for_completion(struct fireant_private *priv)
{
	if (wait_for_bit_le32(LRN_COMMON_ACCESS_CTRL(priv->regs[LRN]),
			      LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT,
			      false, 2000, false))
		return -ETIMEDOUT;

	return 0;
}

static void mac_table_write_entry(struct fireant_private *priv,
				  const unsigned char *mac,
				  u16 vid)
{
	u32 macl = 0, mach = 0;

	/*
	 * Set the MAC address to handle and the vlan associated in a format
	 * understood by the hardware.
	 */
	mach |= vid << 16;
	mach |= ((u32)mac[0]) << 8;
	mach |= ((u32)mac[1]) << 0;
	macl |= ((u32)mac[2]) << 24;
	macl |= ((u32)mac[3]) << 16;
	macl |= ((u32)mac[4]) << 8;
	macl |= ((u32)mac[5]) << 0;

	writel(mach, LRN_MAC_ACCESS_CFG0(priv->regs[LRN]));
	writel(macl, LRN_MAC_ACCESS_CFG1(priv->regs[LRN]));
}

static int fireant_mac_table_add(struct fireant_private *priv,
				 const unsigned char *mac, int pgid)
{
#if defined(CONFIG_CPU_MACENTRY_ENA)
	debug("%s: Add %02x:%02x:%02x:%02x:%02x:%02x pgid %d\n",
	      __FUNCTION__,
	      mac[0], mac[1], mac[2],
	      mac[3], mac[4], mac[5], pgid);

	mac_table_write_entry(priv, mac, MAC_VID);

	writel(LRN_MAC_ACCESS_CFG2_MAC_ENTRY_ADDR(pgid - MAX_PORT) |
	       LRN_MAC_ACCESS_CFG2_MAC_ENTRY_TYPE(0x3) |
	       LRN_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_COPY |
	       LRN_MAC_ACCESS_CFG2_MAC_ENTRY_CPU_QU(0) |
	       LRN_MAC_ACCESS_CFG2_MAC_ENTRY_VLD |
	       LRN_MAC_ACCESS_CFG2_MAC_ENTRY_LOCKED,
	       LRN_MAC_ACCESS_CFG2(priv->regs[LRN]));

	writel(LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT,
	       LRN_COMMON_ACCESS_CTRL(priv->regs[LRN]));

	return fireant_vlant_wait_for_completion(priv);
#else
	return 0;
#endif
}

static int fireant_mac_table_getnext(struct fireant_private *priv,
				     unsigned char *mac,
				     int *addr,
				     u32 *pvid,
				     u32 *cfg0p,
				     u32 *cfg1p,
				     u32 *cfg2p)
{
	int ret;

	//debug("%s: start\n", __FUNCTION__);

	mac_table_write_entry(priv, mac, *pvid);

	writel(LRN_SCAN_NEXT_CFG_UNTIL_FOUND_ENA |
	       LRN_SCAN_NEXT_CFG_IGNORE_LOCKED_ENA,
	       LRN_SCAN_NEXT_CFG(priv->regs[LRN]));

	writel(LRN_COMMON_ACCESS_CTRL_CPU_ACCESS_CMD(6) |
	       LRN_COMMON_ACCESS_CTRL_MAC_TABLE_ACCESS_SHOT,
	       LRN_COMMON_ACCESS_CTRL(priv->regs[LRN]));

	ret = fireant_vlant_wait_for_completion(priv);

	if (ret == 0) {
		u32 cfg0, cfg1, cfg2;
		cfg2 = readl(LRN_MAC_ACCESS_CFG2(priv->regs[LRN]));
		if (cfg2 & LRN_MAC_ACCESS_CFG2_MAC_ENTRY_VLD) {
			cfg0 = readl(LRN_MAC_ACCESS_CFG0(priv->regs[LRN]));
			cfg1 = readl(LRN_MAC_ACCESS_CFG1(priv->regs[LRN]));
			mac[0] = ((cfg0 >> 8)  & 0xff);
			mac[1] = ((cfg0 >> 0)  & 0xff);
			mac[2] = ((cfg1 >> 24) & 0xff);
			mac[3] = ((cfg1 >> 16) & 0xff);
			mac[4] = ((cfg1 >> 8)  & 0xff);
			mac[5] = ((cfg1 >> 0)  & 0xff);
			*addr = LRN_MAC_ACCESS_CFG2_MAC_ENTRY_ADDR_MASK & cfg2;
			*pvid = cfg0 >> 16;
			*cfg0p = cfg0;
			*cfg1p = cfg1;
			*cfg2p = cfg2;
		} else {
			ret = 1;
		}
	}

	//debug("%s: ret %d\n", __FUNCTION__, ret);

	return ret;
}

static int fireant_initialize(struct fireant_private *priv)
{
	int ret, i;

	debug("%s\n", __FUNCTION__);

	/* Initialize switch memories, enable core */
	ret = fireant_switch_init(priv);
	if (ret)
		return ret;

	fireant_switch_config(priv);

	for (i = 0; i < MAX_PORT; i++)
		if (priv->ports[i].active)
			fireant_port_init(priv, i, priv->ports[i].serdes_args[SERDES_ARG_MAC_TYPE]);

	fireant_cpu_capture_setup(priv);

	return 0;
}

static int fireant_start(struct udevice *dev)
{
	struct fireant_private *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_platdata(dev);
	const u8 mac[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	int i, ret;

	debug("%s\n", __FUNCTION__);

	ret = fireant_initialize(priv);
	if (ret)
		return ret;

	/* Set MAC address tables entries for CPU redirection */
	ret = fireant_mac_table_add(priv, mac, PGID_BROADCAST);
	if (ret)
		return ret;

	ret = fireant_mac_table_add(priv, pdata->enetaddr, PGID_HOST);
	if (ret)
		return ret;

	for (i = 0; i < MAX_PORT; i++)
		if (priv->ports[i].active) {
			struct phy_device *phy = priv->ports[i].phy;

			if (phy) {
				/* Start up the PHY */
				ret = phy_startup(phy);
				if (ret) {
					printf("Could not initialize PHY %s\n",
					       phy->dev->name);
					return ret;
				}
			}

			if (i == NPI_PORT)
				printf("NPI Port: ");
			else
				printf("Port %3d: ", i);
			printf("%s\n", has_link(priv, i) ? "Up" : "Down");
		}

	return 0;
}

static void fireant_stop(struct udevice *dev)
{
	struct fireant_private *priv = dev_get_priv(dev);
	int i;

	debug("%s\n", __FUNCTION__);

	for (i = 0; i < MAX_PORT; i++) {
		struct phy_device *phy = priv->ports[i].phy;

		if (phy)
			phy_shutdown(phy);
	}

        /* Make sure the core is PROTECTED from reset */
	setbits_le32(MSCC_CPU_RESET_PROT_STAT,
		     MSCC_M_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE);

	/* Reset switch core */
	writel(MSCC_M_DEVCPU_GCB_SOFT_RST_SOFT_CHIP_RST, MSCC_DEVCPU_GCB_SOFT_RST);
}

static int fireant_send(struct udevice *dev, void *packet, int length)
{
	struct fireant_private *priv = dev_get_priv(dev);
	u32 *ifh;
	size_t ifh_len;

	//debug("%s: %d bytes\n", __FUNCTION__, length);
	hexdump(packet, length);

	if (CONFIG_IFH_FMT > IFH_FMT_NONE) {
		ifh = (u32*) ifh_fireant;
		ifh_len = sizeof(ifh_fireant)/sizeof(u32);
		debug("%s: Encap %zd bytes\n", __FUNCTION__, sizeof(ifh_fireant));
		hexdump(ifh_fireant, sizeof(ifh_fireant));
	} else {
		ifh = NULL;
		ifh_len = 0;
	}

	return mscc_send(priv->regs[QS], fireant_regs_qs,
			 ifh, ifh_len, packet, length);
}

static int fireant_recv(struct udevice *dev, int flags, uchar **packetp)
{
	struct fireant_private *priv = dev_get_priv(dev);
	u32 *rxbuf = (u32 *)net_rx_packets[0];
	int byte_cnt = 0;

	//debug("%s\n", __FUNCTION__);

	byte_cnt = mscc_recv(priv->regs[QS], fireant_regs_qs, rxbuf, IFH_LEN,
			     false);

	*packetp = net_rx_packets[0];

	if (byte_cnt > 0) {
		if (byte_cnt >= ETH_FCS_LEN) {
			byte_cnt -= ETH_FCS_LEN;
			//debug("%s: Got %d bytes\n", __FUNCTION__, byte_cnt);
			hexdump(*packetp, byte_cnt);
		} else {
			debug("%s: Got undersized frame = %d bytes\n",
			      __FUNCTION__, byte_cnt);
			byte_cnt = 0; /* Runt? */
		}
	}

	return byte_cnt;
}

static struct mii_dev *get_mdiobus(phys_addr_t base, unsigned long size)
{
	int i = 0;

	for (i = 0; i < FIREANT_MIIM_BUS_COUNT; ++i)
		if (miim[i].miim_base == base && miim[i].miim_size == size)
			return miim[i].bus;

	return NULL;
}

static void add_port_entry(struct fireant_private *priv, size_t index,
			   size_t phy_addr, struct mii_dev *bus,
			   u32 *serdes_args)
{
	debug("%s: Add port %zd bus %s addr %zd serdes %s serdes# %d\n", __FUNCTION__, index,
	      bus ? bus->name : "(none)", phy_addr,
	      serdes_args[SERDES_ARG_SERDES] == FA_SERDES_TYPE_6G ? "6g" : "10g",
	      serdes_args[SERDES_ARG_SER_IDX]);
	priv->ports[index].active = true;
	priv->ports[index].phy_addr = phy_addr;
	priv->ports[index].bus = bus;
	memcpy(priv->ports[index].serdes_args, serdes_args,
	       sizeof(priv->ports[index].serdes_args));
}

static int fireant_probe(struct udevice *dev)
{
	struct fireant_private *priv = dev_get_priv(dev);
	int i;
	int ret;
	struct resource res;
	phys_addr_t addr_base;
	unsigned long addr_size;
	ofnode eth_node, node, mdio_node;
	size_t phy_addr;
	struct mii_dev *bus;
	struct ofnode_phandle_args phandle;
	u32 serdes_args[SERDES_ARG_MAX];

	if (!priv)
		return -EINVAL;

	debug("%s\n", __FUNCTION__);

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

	/* Initialize miim buses */
	memset(&miim, 0x0, sizeof(struct mscc_miim_dev) * FIREANT_MIIM_BUS_COUNT);

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

		/* Do we have a PHY to worry about? */
		if (ret == 0) {
			/* Get phy address on mdio bus */
			if (ofnode_read_resource(phandle.node, 0, &res))
				return -ENOMEM;
			phy_addr = res.start;

			debug("%s: Port %d on phy %zd\n", __FUNCTION__, i, phy_addr);

			/* Get mdio node */
			mdio_node = ofnode_get_parent(phandle.node);

			if (ofnode_read_resource(mdio_node, 0, &res))
				return -ENOMEM;

			addr_base = res.start;
			addr_size = resource_size(&res);

			/* If the bus is new then create a new bus */
			bus = get_mdiobus(addr_base, addr_size);
			if (!bus) {
				bus = mscc_mdiobus_init(miim, miim_count, addr_base,
							addr_size);
				if (!bus)
					return -ENOMEM;
				priv->bus[miim_count++] = bus;
				mscc_mdiobus_pinctrl_apply(mdio_node);
			}
		} else {
			bus = NULL;
			phy_addr = -1;
		}

		/* Get serdes info */
		ret = ofnode_read_u32_array(node, "phys", serdes_args, SERDES_ARG_MAX);

		if (ret) {
			printf("%s: Port %d no 'phys' properties?\n", __FUNCTION__, i);
			return -ENOMEM;
		}

		add_port_entry(priv, i, phy_addr, bus, serdes_args);
	}

	for (i = 0; i < MAX_PORT; i++) {
		struct phy_device *phy;

		if (!priv->ports[i].bus)
			continue;

		debug("%s: Port %d on %s addr %d\n", __FUNCTION__,
		      i, priv->ports[i].bus->name, priv->ports[i].phy_addr);
		phy = phy_connect(priv->ports[i].bus,
				  priv->ports[i].phy_addr, dev,
				  PHY_INTERFACE_MODE_NONE);
		if (phy) {
			debug("%s: PHY %s %s\n", __FUNCTION__, phy->bus->name, phy->drv->name);
			priv->ports[i].phy = phy;
			board_phy_config(phy);
		} else
			debug("%s: No driver\n", __FUNCTION__);
	}

	dev_priv = priv;

	return 0;
}

static int fireant_remove(struct udevice *dev)
{
	struct fireant_private *priv = dev_get_priv(dev);
	int i;

	for (i = 0; i < FIREANT_MIIM_BUS_COUNT; i++) {
		mdio_unregister(priv->bus[i]);
		mdio_free(priv->bus[i]);
	}

	dev_priv = NULL;

	return 0;
}

static const struct eth_ops fireant_ops = {
	.start        = fireant_start,
	.stop         = fireant_stop,
	.send         = fireant_send,
	.recv         = fireant_recv,
};

static const struct udevice_id mscc_fireant_ids[] = {
	{.compatible = "mscc,vsc7558-switch" },
	{ /* Sentinel */ }
};

U_BOOT_DRIVER(fireant) = {
	.name				= "fireant-switch",
	.id				= UCLASS_ETH,
	.of_match			= mscc_fireant_ids,
	.probe				= fireant_probe,
	.remove				= fireant_remove,
	.ops				= &fireant_ops,
	.priv_auto_alloc_size		= sizeof(struct fireant_private),
	.platdata_auto_alloc_size	= sizeof(struct eth_pdata),
};

static int do_switch(cmd_tbl_t *cmdtp, int flag, int argc,
		       char * const argv[])
{
	struct fireant_private *priv = dev_priv;
	u8 mac[ETH_ALEN];
	int i, addr, cnt = 0;
	u32 cfg0, cfg1, cfg2;

	if (priv) {
		memset(mac, 0, sizeof(mac));
		u32 vid = 0;
		while (fireant_mac_table_getnext(priv, mac, &addr, &vid, &cfg0, &cfg1, &cfg2) == 0) {
			printf("%4d: %02x:%02x:%02x:%02x:%02x:%02x %d:%d 0x%08x 0x%08x 0x%08x\n",
			       cnt++,
			       mac[0], mac[1], mac[2],
			       mac[3], mac[4], mac[5], vid, addr, cfg0, cfg1, cfg2);
		}
		for (i = 0; i < MAX_PORT; i++)
			if (priv->ports[i].active) {
				u32 mask, val;
				if (priv->ports[i].bus) {
					val = readl(DEV1G_PCS1G_LINK_STATUS(priv->regs[i]));
					mask = DEV1G_PCS1G_LINK_STATUS_LINK_UP;
				} else {
					val = readl(DEV1G_PCS1G_ANEG_STATUS(priv->regs[i]));
					mask = DEV1G_PCS1G_ANEG_STATUS_ANEG_COMPLETE;
				}
				printf("%2d: Link %s (0x%08x)\n", i,
				       val & mask ? "Up" : "--",
				       val);
			}
	}

	return 0;
}

U_BOOT_CMD(
	switch,	3,	1,	do_switch,
	"display switch status",
	""
);
