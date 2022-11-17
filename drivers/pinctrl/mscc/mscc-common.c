// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/*
 * Microsemi SoCs pinctrl driver
 *
 * Author: <alexandre.belloni@free-electrons.com>
 * Author: <gregory.clement@bootlin.com>
 * License: Dual MIT/GPL
 * Copyright (c) 2017 Microsemi Corporation
 */

#include <asm/gpio.h>
#include <asm/system.h>
#include <common.h>
#include <config.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/pinctrl.h>
#include <dm/root.h>
#include <errno.h>
#include <linux/io.h>
#include "mscc-common.h"

/* PINCONFIG bits */
#define BIAS_PD_BIT BIT(4)
#define BIAS_PU_BIT BIT(3)
#define BIAS_BITS   (BIAS_PD_BIT|BIAS_PU_BIT)
#define SCHMITT_BIT BIT(2)
#define DRIVE_MASK  GENMASK(1, 0)

static inline void __iomem *mscc_regaddr(const struct mscc_pinctrl *info, u8 regno)
{
	return info->regs + info->mscc_gpios[regno];
}

static void mscc_writel(u32 offset, void *addr)
{
	if (offset < 32)
		writel(BIT(offset), addr);
	else
		writel(BIT(offset % 32), addr + 4);
}

static u32 mscc_readl(u32 offset, void *addr)
{
	if (offset < 32)
		return readl(addr);
	else
		return readl(addr + 4);
}

static void mscc_setbits(unsigned int offset, void *addr)
{
	if (offset < 32)
		writel(readl(addr) | BIT(offset), addr);
	else
		writel(readl(addr + 4) | BIT(offset % 32), addr + 4);
}

static void mscc_clrbits(unsigned int offset, void *addr)
{
	if (offset < 32)
		writel(readl(addr) & ~BIT(offset), addr);
	else
		writel(readl(addr + 4) & ~BIT(offset % 32), addr + 4);
}

static int mscc_get_functions_count(struct udevice *dev)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);

	return info->num_func;
}

static const char *mscc_get_function_name(struct udevice *dev,
					  unsigned int function)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);

	return info->function_names[function];
}

static int mscc_pin_function_idx(unsigned int pin, unsigned int function,
				 const struct mscc_pin_data *mscc_pins)
{
	struct mscc_pin_caps *p = mscc_pins[pin].drv_data;
	int i;

	for (i = 0; i < MSCC_FUNC_PER_PIN; i++) {
		if (function == p->functions[i])
			return i;
	}

	return -1;
}

static int mscc_pinmux_set_mux(struct udevice *dev,
			       unsigned int pin_selector, unsigned int selector)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);
	struct mscc_pin_caps *pin = info->mscc_pins[pin_selector].drv_data;
	int f, offset, regoff;

	f = mscc_pin_function_idx(pin_selector, selector, info->mscc_pins);
	if (f < 0)
		return -EINVAL;
	/*
	 * f is encoded on two bits.
	 * bit 0 of f goes in BIT(pin) of ALT0, bit 1 of f goes in BIT(pin) of
	 * ALT1
	 * This is racy because both registers can't be updated at the same time
	 * but it doesn't matter much for now.
	 */
	offset = pin->pin;
	regoff = info->mscc_gpios[MSCC_GPIO_ALT0];
	if (offset >= 32) {
		offset = offset % 32;
		regoff = info->mscc_gpios[MSCC_GPIO_ALT1];
	}

	debug("%s: GPIO%d set alt func %d\n", __func__, pin_selector, f);

	if (f & BIT(0))
		mscc_setbits(offset, info->regs + regoff);
	else
		mscc_clrbits(offset, info->regs + regoff);

	if (f & BIT(1))
		mscc_setbits(offset, info->regs + regoff + 4);
	else
		mscc_clrbits(offset, info->regs + regoff + 4);

	return 0;
}

static int mscc_pctl_get_groups_count(struct udevice *dev)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);

	return info->num_pins;
}

static const char *mscc_pctl_get_group_name(struct udevice *dev,
					    unsigned int group)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);

	return info->mscc_pins[group].name;
}

static int mscc_create_group_func_map(struct udevice *dev,
				      struct mscc_pinctrl *info)
{
	u16 pins[info->num_pins];
	int f, npins, i;

	for (f = 0; f < info->num_func; f++) {
		for (npins = 0, i = 0; i < info->num_pins; i++) {
			if (mscc_pin_function_idx(i, f, info->mscc_pins) >= 0)
				pins[npins++] = i;
		}

		info->func[f].ngroups = npins;
		info->func[f].groups = devm_kzalloc(dev, npins * sizeof(char *),
						    GFP_KERNEL);
		if (!info->func[f].groups)
			return -ENOMEM;

		for (i = 0; i < npins; i++)
			info->func[f].groups[i] = info->mscc_pins[pins[i]].name;
	}

	return 0;
}

static int mscc_pinctrl_register(struct udevice *dev, struct mscc_pinctrl *info)
{
	int ret;

	ret = mscc_create_group_func_map(dev, info);
	if (ret) {
		dev_err(dev, "Unable to create group func map.\n");
		return ret;
	}

	return 0;
}

static int mscc_gpio_get(struct udevice *dev, unsigned int offset)
{
	struct mscc_pinctrl *info = dev_get_priv(dev->parent);
	u32 val, mask = BIT(offset % 32);

	if (mscc_readl(offset, mscc_regaddr(info, MSCC_GPIO_OE)) & mask)
		val = mscc_readl(offset, mscc_regaddr(info, MSCC_GPIO_OUT));
	else
		val = mscc_readl(offset, mscc_regaddr(info, MSCC_GPIO_IN));

	return !!(val & mask);
}

static int mscc_gpio_set(struct udevice *dev, unsigned int offset, int value)
{
	struct mscc_pinctrl *info = dev_get_priv(dev->parent);

	if (value)
		mscc_writel(offset, mscc_regaddr(info, MSCC_GPIO_OUT_SET));
	else
		mscc_writel(offset, mscc_regaddr(info, MSCC_GPIO_OUT_CLR));

	return 0;
}

static int mscc_gpio_get_direction(struct udevice *dev, unsigned int offset)
{
	struct mscc_pinctrl *info = dev_get_priv(dev->parent);
	u32 val;

	val = mscc_readl(offset, mscc_regaddr(info, MSCC_GPIO_OE));

	return (val & BIT(offset % 32)) ? GPIOF_OUTPUT : GPIOF_INPUT;
}

static int mscc_gpio_direction_input(struct udevice *dev, unsigned int offset)
{
	struct mscc_pinctrl *info = dev_get_priv(dev->parent);

	mscc_clrbits(offset, mscc_regaddr(info, MSCC_GPIO_OE));

	return 0;
}

static int mscc_gpio_direction_output(struct udevice *dev,
				      unsigned int offset, int value)
{
	struct mscc_pinctrl *info = dev_get_priv(dev->parent);

	mscc_setbits(offset, mscc_regaddr(info, MSCC_GPIO_OE));

	return mscc_gpio_set(dev, offset, value);
}

#if CONFIG_IS_ENABLED(PINCONF)
static const struct pinconf_param mscc_conf_params[] = {
	{ "bias-disable",          PIN_CONFIG_BIAS_DISABLE, 0 },
	{ "bias-pull-up",          PIN_CONFIG_BIAS_PULL_UP, BIAS_PU_BIT },
	{ "bias-pull-down",        PIN_CONFIG_BIAS_PULL_DOWN, BIAS_PD_BIT },
	{ "input-schmitt-enable",  PIN_CONFIG_INPUT_SCHMITT_ENABLE, SCHMITT_BIT },
	{ "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 },
	{ "input-enable",          PIN_CONFIG_INPUT_ENABLE, 1 },
	{ "output-high",           PIN_CONFIG_OUTPUT, 1, },
	{ "output-low",            PIN_CONFIG_OUTPUT, 0, },
	{ "drive-strength",        PIN_CONFIG_DRIVE_STRENGTH, 0 },
};

int mscc_pinconf_set_param(struct udevice *dev, u32 pin, u32 param,  u32 arg)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);
	void __iomem *reg_addr = info->regs_cfg + (pin * sizeof(u32));
	int err = 0;

	switch (param) {
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_DOWN:
		debug("%s: GPIO%d set bias 0x%x\n", __func__, pin, arg);
		clrsetbits_le32(reg_addr, BIAS_BITS, arg);
		break;

	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		debug("%s: GPIO%d schmitt 0x%x\n", __func__, pin, arg);
		clrsetbits_le32(reg_addr, SCHMITT_BIT, arg);
		break;

	case PIN_CONFIG_DRIVE_STRENGTH:
		debug("%s: GPIO%d drive-strength 0x%x\n", __func__, pin, arg);
		clrsetbits_le32(reg_addr, DRIVE_MASK, arg);
		break;

	default:
		err = -ENOTSUPP;
	}

	return err;
}

static int mscc_pinconf_set(struct udevice *dev, unsigned int pin,
			   unsigned int param, unsigned int arg)
{
	struct mscc_pinctrl *info = dev_get_priv(dev);
	int err = 0;

	switch (param) {
	case PIN_CONFIG_OUTPUT:
		debug("%s: GPIO%d set %s\n", __func__, pin, arg ? "ON" : "OFF");
		if (arg)
			mscc_writel(pin, mscc_regaddr(info, MSCC_GPIO_OUT_SET));
		else
			mscc_writel(pin, mscc_regaddr(info, MSCC_GPIO_OUT_CLR));
		mscc_setbits(pin, mscc_regaddr(info, MSCC_GPIO_OE));
		break;

	case PIN_CONFIG_INPUT_ENABLE:
		debug("%s: GPIO%d set as %sput\n", __func__, pin, arg ? "out" : "in");
		mscc_clrbits(pin, mscc_regaddr(info, MSCC_GPIO_OE));
		break;

	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
	case PIN_CONFIG_DRIVE_STRENGTH:
		if (info->regs_cfg == NULL)
			err = -ENOTSUPP;
		else
			err = mscc_pinconf_set_param(dev, pin, param, arg);
		break;

	default:
		err = -ENOTSUPP;
	}

	return err;
}
#endif

const struct dm_gpio_ops mscc_gpio_ops = {
	.set_value = mscc_gpio_set,
	.get_value = mscc_gpio_get,
	.get_function = mscc_gpio_get_direction,
	.direction_input = mscc_gpio_direction_input,
	.direction_output = mscc_gpio_direction_output,
};

const struct pinctrl_ops mscc_pinctrl_ops = {
	.get_pins_count = mscc_pctl_get_groups_count,
	.get_pin_name = mscc_pctl_get_group_name,
	.get_functions_count = mscc_get_functions_count,
	.get_function_name = mscc_get_function_name,
	.pinmux_set = mscc_pinmux_set_mux,
#if CONFIG_IS_ENABLED(PINCONF)
	.pinconf_num_params = ARRAY_SIZE(mscc_conf_params),
	.pinconf_params = mscc_conf_params,
	.pinconf_set = mscc_pinconf_set,
#endif
	.set_state = pinctrl_generic_set_state,
};

int mscc_pinctrl_probe(struct udevice *dev, int num_func,
		       const struct mscc_pin_data *mscc_pins, int num_pins,
		       char * const *function_names,
		       const unsigned long *mscc_gpios)
{
	struct mscc_pinctrl *priv = dev_get_priv(dev);

	priv->regs     = (void __iomem *)dev_remap_addr_index(dev, 0);
	priv->regs_cfg = (void __iomem *)dev_remap_addr_index(dev, 1);

	priv->func = devm_kzalloc(dev, num_func * sizeof(struct mscc_pmx_func),
				  GFP_KERNEL);
	priv->num_func = num_func;
	priv->mscc_pins = mscc_pins;
	priv->num_pins = num_pins;
	priv->function_names = function_names;
	priv->mscc_gpios = mscc_gpios;

	return mscc_pinctrl_register(dev, priv);
}
