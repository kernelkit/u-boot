// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2019 Microsemi Corporation
 */

#include <common.h>
#include <clk-uclass.h>
#include <div64.h>
#include <dm.h>
#include <regmap.h>
#include <spl.h>
#include <syscon.h>
#include <linux/io.h>
#include <linux/iopoll.h>
#include <dt-bindings/clk/mchp,fireant.h>

#define PLL_DIV_MASK		GENMASK(7, 0)
#define PLL_PRE_DIV_MASK	GENMASK(10, 8)
#define PLL_PRE_DIV_SHIFT	8
#define PLL_ROT_DIR		BIT(11)
#define PLL_ROT_SEL_MASK	GENMASK(13, 12)
#define PLL_ROT_SEL_SHIFT	12
#define PLL_ROT_ENA		BIT(14)
#define PLL_CLK_ENA		BIT(15)

#define MAX_SEL 4
#define MAX_PRE BIT(3)

#define KHZ 1000
#define MHZ (KHZ*KHZ)

#define BASE_CLOCK (2500UL*MHZ)

static u8 sel_rates[MAX_SEL] = { 0, 2*8, 2*4, 2*2 };

static const char *clk_names[N_CLOCKS] = {
	"core", "ddr", "cpu2", "arm2",
	"aux1", "aux2", "aux3", "aux4",
	"synce",
};

struct fireant_clk_priv {
	void *base;
};

struct pll_conf {
	int freq;
	u8 div;
	bool rot_ena;
	u8 rot_sel;
	u8 rot_dir;
	u8 pre_div;
};

unsigned long calc_freq(const struct pll_conf *pdata)
{
	unsigned long rate = BASE_CLOCK / pdata->div;

	if (pdata->rot_ena) {
		unsigned long base = BASE_CLOCK / pdata->div;
		int sign = pdata->rot_dir ? -1 : 1;
		int divt = sel_rates[pdata->rot_sel] * (1 + pdata->pre_div);
		int divb = divt + sign;

		rate = mult_frac(base, divt, divb);
		rate = roundup(rate, 1000);
	}

	return rate;
}

static unsigned long clk_calc_params(unsigned long rate,
				     struct pll_conf *conf)
{
	memset(conf, 0, sizeof(*conf));

	conf->div = DIV_ROUND_CLOSEST_ULL(BASE_CLOCK, rate);

	if (BASE_CLOCK % rate) {
		struct pll_conf best;
		ulong cur_offset, best_offset = rate;
		int i, j;

		/* Enable fractional rotation */
		conf->rot_ena = true;

		if ((BASE_CLOCK / rate) != conf->div) {
			/* Overshoot, adjust other direction */
			conf->rot_dir = 1;
		}

		/* Brute force search over MAX_PRE * (MAX_SEL - 1) = 24 */
		for (i = 0; i < MAX_PRE; i++) {
			conf->pre_div = i;
			for (j = 1; j < MAX_SEL; j++) {
				conf->rot_sel = j;
				conf->freq = calc_freq(conf);
				cur_offset = abs(rate - conf->freq);
				if (cur_offset == 0)
					/* Perfect fit */
					goto done;
				if (cur_offset < best_offset) {
					/* Better fit found */
					best_offset = cur_offset;
					best = *conf;
				}
			}
		}
		/* Best match */
		*conf = best;
	}

done:
	return conf->freq;
}

static void* fireant_clk_get_id(struct fireant_clk_priv *priv, u8 id)
{
	if (id >= N_CLOCKS)
		return NULL;

	return priv->base + (id * sizeof(u32));;
}

static int fireant_clk_enable(struct clk *clk)
{
	struct fireant_clk_priv *priv = dev_get_priv(clk->dev);
	void *pllreg = fireant_clk_get_id(priv, clk->id);
	int ret = 0;

	if (pllreg) {
		setbits_le32(pllreg, PLL_CLK_ENA);
		debug("%s: id clock %d has been enabled\n", __func__, (u32)clk->id);
	} else {
		ret = -EINVAL;
	}

	return ret;
}

static int fireant_clk_disable(struct clk *clk)
{
	struct fireant_clk_priv *priv = dev_get_priv(clk->dev);
	void *pllreg = fireant_clk_get_id(priv, clk->id);
	int ret = 0;

	if (pllreg) {
		clrbits_le32(pllreg, PLL_CLK_ENA);
		debug("%s: id clock %d has been disabled\n", __func__, (u32)clk->id);
	} else {
		ret = -EINVAL;
	}

	return ret;
}

static ulong fireant_clk_set_rate(struct clk *clk, unsigned long clk_rate)
{
	struct fireant_clk_priv *priv = dev_get_priv(clk->dev);
	void *pllreg = fireant_clk_get_id(priv, clk->id);

	if (pllreg) {
		struct pll_conf conf;
		ulong eff_rate = clk_calc_params(clk_rate, &conf);

		if (eff_rate == clk_rate) {
			u32 val;

			val = readl(pllreg) & PLL_CLK_ENA;
			val |= PLL_DIV_MASK & conf.div;
			if (conf.rot_ena) {
				val |= (PLL_ROT_ENA |
					(PLL_ROT_SEL_MASK &
					 (conf.rot_sel << PLL_ROT_SEL_SHIFT)) |
					(PLL_PRE_DIV_MASK &
					 (conf.pre_div << PLL_PRE_DIV_SHIFT)));
				if (conf.rot_dir)
					val |= PLL_ROT_DIR;
			}

			debug("%s: Rate %ld (eff %ld) >= 0x%04x\n",
			      clk_names[clk->id], eff_rate, clk_rate, val);

			writel(val, pllreg);

			return eff_rate;
		}
	}

	return 0;
}

static int fireant_clk_probe(struct udevice *dev)
{
	struct fireant_clk_priv *priv = dev_get_priv(dev);

	debug("Probing\n");

	priv->base = dev_remap_addr(dev);
	if (!priv->base) {
		dev_err(&dev->dev, "No base reg\n");
		return -EINVAL;
	}

	return 0;
}

static const struct clk_ops fireant_clk_ops = {
	.enable = fireant_clk_enable,
	.disable = fireant_clk_disable,
	.set_rate = fireant_clk_set_rate,
};

static const struct udevice_id fireant_clk_ids[] = {
	{ .compatible = "mchp,fireant-clock" },
	{ },
};

U_BOOT_DRIVER(fireant_clock) = {
	.name = "fireant_clk",
	.id = UCLASS_CLK,
	.ops = &fireant_clk_ops,
	.of_match = fireant_clk_ids,
	.priv_auto_alloc_size = sizeof(struct fireant_clk_priv),
	.probe = fireant_clk_probe,
};
