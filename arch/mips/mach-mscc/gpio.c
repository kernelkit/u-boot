// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2018 Microsemi Corporation
 */

#include <common.h>
#include <asm/io.h>

void mscc_gpio_set_alternate(int gpio, int mode)
{
	u32 mask = 0;
	u32 val0, val1;
	void __iomem *reg0, *reg1;

	if (gpio < 32) {
		mask = BIT(gpio);
		reg0 = BASE_DEVCPU_GCB + GPIO_ALT(0);
		reg1 = BASE_DEVCPU_GCB + GPIO_ALT(1);
	} else {
#if defined(CONFIG_SOC_JR2) || defined(CONFIG_SOC_SERVALT)
		gpio -= 32;
		mask = BIT(gpio);
		reg0 = BASE_DEVCPU_GCB + GPIO_ALT1(0);
		reg1 = BASE_DEVCPU_GCB + GPIO_ALT1(1);
#endif
	}
	val0 = readl(reg0);
	val1 = readl(reg1);
	if (mode == 1) {
		writel(val0 | mask, reg0);
		writel(val1 & ~mask, reg1);
	} else if (mode == 2) {
		writel(val0 & ~mask, reg0);
		writel(val1 | mask, reg1);
	} else if (mode == 3) {
		writel(val0 | mask, reg0);
		writel(val1 | mask, reg1);
	} else {
		writel(val0 & ~mask, reg0);
		writel(val1 & ~mask, reg1);
	}
}
