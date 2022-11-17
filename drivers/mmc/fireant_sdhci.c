// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2019 Microsemi Corporation
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <malloc.h>
#include <sdhci.h>
#include <asm/arch/clk.h>
#include <asm/io.h>

#define KHZ(x) (x * 1000)
#define MHZ(x) (x * KHZ(1000))

/* 400KHz is max freq for card ID etc. Use that as min */
#define FIREANT_SDHC_MIN_FREQ	KHZ(400)
#define FIREANT_EMMC_DEF_CLK	MHZ(50)
#define FIREANT_EMMC_MAX_CLK	MHZ(100)

#define CPU_REGS_GENERAL_CTRL   (0x22 * 4)
#define  MSHC_DLY_CC_MASK       GENMASK(16, 13)
#define  MSHC_DLY_CC_SHIFT      13
#define  MSHC_DLY_CC_MAX        15

#define CPU_REGS_PROC_CTRL      (0x2C * 4)
#define  ACP_CACHE_FORCE_ENA    BIT(4)
#define  ACP_AWCACHE            BIT(3)
#define  ACP_ARCACHE            BIT(2)
#define  ACP_CACHE_MASK         GENMASK(4, 2)

#define MSHC2_VERSION                   0x500   /* Off 0x140, reg 0x0 */
#define MSHC2_TYPE                      0x504   /* Off 0x140, reg 0x1 */
#define MSHC2_EMMC_CTRL                 0x52c   /* Off 0x140, reg 0xB */
#define  MSHC2_EMMC_CTRL_EMMC_RST_N     BIT(2)
#define  MSHC2_EMMC_CTRL_IS_EMMC        BIT(0)

struct fireant_sdhci_plat {
	struct mmc_config cfg;
	struct mmc mmc;
	void *cpuregs;
	u32 delay_cc;
};

static void fireant_set_cacheable(struct udevice *dev, u32 value)
{
	struct fireant_sdhci_plat *plat = dev_get_platdata(dev);

	debug("%s: Set Cacheable = 0x%x\n", __func__, value);

	/* Update ACP caching attributes in HW */
	clrsetbits_le32(plat->cpuregs + CPU_REGS_PROC_CTRL,
			ACP_CACHE_MASK, value);
}

static void fireant_set_delay(struct udevice *dev, u8 value)
{
	struct fireant_sdhci_plat *plat = dev_get_platdata(dev);

	debug("%s: Set DLY_CC = %u\n", __func__, value);

	/* Update DLY_CC in HW */
	clrsetbits_le32(plat->cpuregs + CPU_REGS_GENERAL_CTRL,
			MSHC_DLY_CC_MASK,
			(value << MSHC_DLY_CC_SHIFT));
}

static inline void _sdhci_writeb(struct sdhci_host *host, u8 val, int reg)
{
	debug("$$$ writeb(%02x, 0x%02x)\n", val, reg);
	writeb(val, host->ioaddr + reg);
}

static inline void _sdhci_writew(struct sdhci_host *host, u16 val, int reg)
{
	debug("$$$ writew(%04x, 0x%02x)\n", val, reg);
	writew(val, host->ioaddr + reg);
}

static inline void _sdhci_writel(struct sdhci_host *host, u32 val, int reg)
{
	debug("$$$ writel(%08x, 0x%02x)\n", val, reg);
	writel(val, host->ioaddr + reg);
}

static void sdhci_fireant_set_emmc(struct sdhci_host *host)
{
	u8 value;

	value = sdhci_readb(host, MSHC2_EMMC_CTRL);
	if (!(value & MSHC2_EMMC_CTRL_IS_EMMC)) {
		//debug("Get EMMC_CTRL: 0x%08x\n", value);
		value |= MSHC2_EMMC_CTRL_IS_EMMC;
		debug("Set EMMC_CTRL: 0x%08x\n", value);
		_sdhci_writeb(host, value, MSHC2_EMMC_CTRL);
	}
}

static inline void fireant_sdhci_writeb(struct sdhci_host *host, u8 val, int reg)
{
	_sdhci_writeb(host, val, reg);
	if (reg == SDHCI_SOFTWARE_RESET && (val & SDHCI_RESET_ALL))
		sdhci_fireant_set_emmc(host);
}

static inline u32 fireant_sdhci_readl(struct sdhci_host *host, int reg)
{
	u32 val = readl(host->ioaddr + reg);
	if (reg == SDHCI_INT_STATUS && (val & SDHCI_INT_ERROR)) {
		printf("eMMC: INT_STATUS = %08x\n", val);
	}
	return val;
}

static const struct sdhci_ops fireant_sdhci_ops = {
	.write_b = fireant_sdhci_writeb,
	.write_w = _sdhci_writew,
	.write_l = _sdhci_writel,
	.read_l = fireant_sdhci_readl,
};

static int fireant_sdhci_probe(struct udevice *dev)
{
	struct mmc_uclass_priv *upriv = dev_get_uclass_priv(dev);
	struct fireant_sdhci_plat *plat = dev_get_platdata(dev);
	struct sdhci_host *host = dev_get_priv(dev);
	u32 max_clk;
	struct clk clk;
	int ret;

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret)
		return ret;

	ret = clk_enable(&clk);
	if (ret)
		return ret;

	host->name = dev->name;
	host->ioaddr = (void *)devfdt_get_addr(dev);

	/* Add writeb ops to hook reset */
	host->ops = &fireant_sdhci_ops;

	host->quirks = SDHCI_QUIRK_WAIT_SEND_CMD | SDHCI_QUIRK_NO_1_8_V;
	host->bus_width	= fdtdec_get_int(gd->fdt_blob, dev_of_offset(dev),
					 "bus-width", 8);

	plat->cpuregs = devfdt_remap_addr_index(dev, 1);
	plat->delay_cc = fdtdec_get_int(gd->fdt_blob, dev_of_offset(dev),
					"mscc,clock-delay", 8);
	fireant_set_delay(dev, plat->delay_cc);

	/* Set EMMC */
	sdhci_fireant_set_emmc(host);

	if (CONFIG_IS_ENABLED(MMC_SDHCI_ADMA))
		/* Set ACP bus master to use un-cached access (for ADMA) */
		fireant_set_cacheable(dev, ACP_CACHE_FORCE_ENA);

	max_clk = fdtdec_get_int(gd->fdt_blob, dev_of_offset(dev),
				 "max-frequency", FIREANT_EMMC_DEF_CLK);
	if (!max_clk)
		return -EINVAL;

	host->max_clk = FIREANT_EMMC_MAX_CLK;
	if (host->bus_width == 8)
		host->host_caps |= MMC_MODE_8BIT;

	host->mmc = &plat->mmc;
	host->mmc->dev = dev;

	ret = sdhci_setup_cfg(&plat->cfg, host, max_clk, FIREANT_SDHC_MIN_FREQ);
	if (ret)
		return ret;

	host->mmc->priv = host;
	upriv->mmc = host->mmc;

	debug("SDHC version: 0x%08x\n", sdhci_readl(host, MSHC2_VERSION));
	debug("SDHC type:    0x%08x\n", sdhci_readl(host, MSHC2_TYPE));

	clk_free(&clk);

	return sdhci_probe(dev);
}

static int fireant_sdhci_bind(struct udevice *dev)
{
	struct fireant_sdhci_plat *plat = dev_get_platdata(dev);

	return sdhci_bind(dev, &plat->mmc, &plat->cfg);
}

static const struct udevice_id fireant_sdhci_ids[] = {
	{ .compatible = "mscc,fireant-sdhci" },
	{ }
};

U_BOOT_DRIVER(fireant_sdhci_drv) = {
	.name		= "fireant_sdhci",
	.id		= UCLASS_MMC,
	.of_match	= fireant_sdhci_ids,
	.ops		= &sdhci_ops,
	.bind		= fireant_sdhci_bind,
	.probe		= fireant_sdhci_probe,
	.priv_auto_alloc_size = sizeof(struct sdhci_host),
	.platdata_auto_alloc_size = sizeof(struct fireant_sdhci_plat),
};
