// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/*
 * Microsemi SoCs pinctrl driver
 *
 * Author: <lars.povlsen@microchip.com>
 * Copyright (c) 2018 Microsemi Corporation
 */

#include <common.h>
#include <config.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/pinctrl.h>
#include <dm/root.h>
#include <errno.h>
#include <fdtdec.h>
#include <linux/io.h>
#include <asm/gpio.h>
#include <asm/system.h>
#include "mscc-common.h"

enum {
	FUNC_NONE,
	FUNC_GPIO,
	FUNC_IRQ0_IN,
	FUNC_IRQ0_OUT,
	FUNC_IRQ1_IN,
	FUNC_IRQ1_OUT,
	FUNC_MIIM1,
	FUNC_MIIM2,
	FUNC_MIIM3,
	FUNC_PCI_WAKE,
	FUNC_PTP0,
	FUNC_PTP1,
	FUNC_PTP2,
	FUNC_PTP3,
	FUNC_PWM,
	FUNC_RECO_CLK,
	FUNC_SFP,
	FUNC_SIO,
	FUNC_SIO1,
	FUNC_SIO2,
	FUNC_SPI,
	FUNC_SPI2,
	FUNC_TACHO,
	FUNC_TWI,
	FUNC_TWI2,
	FUNC_TWI3,
	FUNC_TWI_SCL_M,
	FUNC_UART,
	FUNC_UART2,
	FUNC_UART3,
	FUNC_PLL_STAT,
	FUNC_EMMC,
	FUNC_MAX
};

char *fireant_function_names[] = {
	[FUNC_NONE]		= "none",
	[FUNC_GPIO]		= "gpio",
	[FUNC_IRQ0_IN]		= "irq0_in",
	[FUNC_IRQ0_OUT]		= "irq0_out",
	[FUNC_IRQ1_IN]		= "irq1_in",
	[FUNC_IRQ1_OUT]		= "irq1_out",
	[FUNC_MIIM1]		= "miim1",
	[FUNC_MIIM2]		= "miim2",
	[FUNC_MIIM3]		= "miim3",
	[FUNC_PCI_WAKE]		= "pci_wake",
	[FUNC_PTP0]		= "ptp0",
	[FUNC_PTP1]		= "ptp1",
	[FUNC_PTP2]		= "ptp2",
	[FUNC_PTP3]		= "ptp3",
	[FUNC_PWM]		= "pwm",
	[FUNC_RECO_CLK]		= "reco_clk",
	[FUNC_SFP]		= "sfp",
	[FUNC_SIO]		= "sio",
	[FUNC_SIO1]		= "sio1",
	[FUNC_SIO2]		= "sio2",
	[FUNC_SPI]		= "spi",
	[FUNC_SPI2]		= "spi2",
	[FUNC_TACHO]		= "tacho",
	[FUNC_TWI]		= "twi",
	[FUNC_TWI2]		= "twi2",
	[FUNC_TWI3]		= "twi3",
	[FUNC_TWI_SCL_M]	= "twi_scl_m",
	[FUNC_UART]		= "uart",
	[FUNC_UART2]		= "uart2",
	[FUNC_UART3]		= "uart3",
	[FUNC_PLL_STAT]		= "pll_stat",
	[FUNC_EMMC]		= "emmc",
};

MSCC_P(0,  SIO,       PLL_STAT,  NONE);
MSCC_P(1,  SIO,       NONE,      NONE);
MSCC_P(2,  SIO,       NONE,      NONE);
MSCC_P(3,  SIO,       NONE,      NONE);
MSCC_P(4,  SIO1,      NONE,      NONE);
MSCC_P(5,  SIO1,      NONE,      NONE);
MSCC_P(6,  IRQ0_IN,   IRQ0_OUT,  SFP);
MSCC_P(7,  IRQ1_IN,   IRQ1_OUT,  SFP);
MSCC_P(8,  PTP0,      NONE,      SFP);
MSCC_P(9,  PTP1,      SFP,       TWI_SCL_M);
MSCC_P(10, UART,      NONE,      NONE);
MSCC_P(11, UART,      NONE,      NONE);
MSCC_P(12, SIO1,      NONE,      NONE);
MSCC_P(13, SIO1,      NONE,      NONE);
MSCC_P(14, TWI,       TWI_SCL_M, NONE);
MSCC_P(15, TWI,       NONE,      NONE);
MSCC_P(16, SPI,       TWI_SCL_M, SFP);
MSCC_P(17, SPI,       TWI_SCL_M, SFP);
MSCC_P(18, SPI,       TWI_SCL_M, SFP);
MSCC_P(19, PCI_WAKE,  TWI_SCL_M, SFP);
MSCC_P(20, IRQ0_OUT,  TWI_SCL_M, SFP);
MSCC_P(21, IRQ1_OUT,  TACHO,     SFP);
MSCC_P(22, TACHO,     IRQ0_OUT,  TWI_SCL_M);
MSCC_P(23, PWM,       UART3,     TWI_SCL_M);
MSCC_P(24, PTP2,      UART3,     TWI_SCL_M);
MSCC_P(25, PTP3,      SPI,       TWI_SCL_M);
MSCC_P(26, UART2,     SPI,       TWI_SCL_M);
MSCC_P(27, UART2,     SPI,       TWI_SCL_M);
MSCC_P(28, TWI2,      SPI,       SFP);
MSCC_P(29, TWI2,      SPI,       SFP);
MSCC_P(30, SIO2,      SPI,       PWM);
MSCC_P(31, SIO2,      SPI,       TWI_SCL_M);
MSCC_P(32, SIO2,      SPI,       TWI_SCL_M);
MSCC_P(33, SIO2,      SPI,       SFP);
MSCC_P(34, NONE,      TWI_SCL_M, EMMC);
MSCC_P(35, SFP,       TWI_SCL_M, EMMC);
MSCC_P(36, SFP,       TWI_SCL_M, EMMC);
MSCC_P(37, SFP,       NONE,      EMMC);
MSCC_P(38, NONE,      TWI_SCL_M, EMMC);
MSCC_P(39, SPI2,      TWI_SCL_M, EMMC);
MSCC_P(40, SPI2,      TWI_SCL_M, EMMC);
MSCC_P(41, SPI2,      TWI_SCL_M, EMMC);
MSCC_P(42, SPI2,      TWI_SCL_M, EMMC);
MSCC_P(43, SPI2,      TWI_SCL_M, EMMC);
MSCC_P(44, SPI,       SFP,       EMMC);
MSCC_P(45, SPI,       SFP,       EMMC);
MSCC_P(46, NONE,      SFP,       EMMC);
MSCC_P(47, NONE,      SFP,       EMMC);
MSCC_P(48, TWI3,      SPI,       SFP);
MSCC_P(49, TWI3,      NONE,      SFP);
MSCC_P(50, SFP,       NONE,      TWI_SCL_M);
MSCC_P(51, SFP,       SPI,       TWI_SCL_M);
MSCC_P(52, SFP,       MIIM3,     TWI_SCL_M);
MSCC_P(53, SFP,       MIIM3,     TWI_SCL_M);
MSCC_P(54, SFP,       PTP2,      TWI_SCL_M);
MSCC_P(55, SFP,       PTP3,      PCI_WAKE);
MSCC_P(56, MIIM1,     SFP,       TWI_SCL_M);
MSCC_P(57, MIIM1,     SFP,       TWI_SCL_M);
MSCC_P(58, MIIM2,     SFP,       TWI_SCL_M);
MSCC_P(59, MIIM2,     SFP,       NONE);
MSCC_P(60, RECO_CLK,  NONE,      NONE);
MSCC_P(61, RECO_CLK,  NONE,      NONE);
MSCC_P(62, RECO_CLK,  PLL_STAT,  NONE);
MSCC_P(63, RECO_CLK,  NONE,      NONE);

#define FIREANT_PIN(n) {					\
	.name = "GPIO_"#n,					\
	.drv_data = &mscc_pin_##n				\
}

const struct mscc_pin_data fireant_pins[] = {
	FIREANT_PIN(0),
	FIREANT_PIN(1),
	FIREANT_PIN(2),
	FIREANT_PIN(3),
	FIREANT_PIN(4),
	FIREANT_PIN(5),
	FIREANT_PIN(6),
	FIREANT_PIN(7),
	FIREANT_PIN(8),
	FIREANT_PIN(9),
	FIREANT_PIN(10),
	FIREANT_PIN(11),
	FIREANT_PIN(12),
	FIREANT_PIN(13),
	FIREANT_PIN(14),
	FIREANT_PIN(15),
	FIREANT_PIN(16),
	FIREANT_PIN(17),
	FIREANT_PIN(18),
	FIREANT_PIN(19),
	FIREANT_PIN(20),
	FIREANT_PIN(21),
	FIREANT_PIN(22),
	FIREANT_PIN(23),
	FIREANT_PIN(24),
	FIREANT_PIN(25),
	FIREANT_PIN(26),
	FIREANT_PIN(27),
	FIREANT_PIN(28),
	FIREANT_PIN(29),
	FIREANT_PIN(30),
	FIREANT_PIN(31),
	FIREANT_PIN(32),
	FIREANT_PIN(33),
	FIREANT_PIN(34),
	FIREANT_PIN(35),
	FIREANT_PIN(36),
	FIREANT_PIN(37),
	FIREANT_PIN(38),
	FIREANT_PIN(39),
	FIREANT_PIN(40),
	FIREANT_PIN(41),
	FIREANT_PIN(42),
	FIREANT_PIN(43),
	FIREANT_PIN(44),
	FIREANT_PIN(45),
	FIREANT_PIN(46),
	FIREANT_PIN(47),
	FIREANT_PIN(48),
	FIREANT_PIN(49),
	FIREANT_PIN(50),
	FIREANT_PIN(51),
	FIREANT_PIN(52),
	FIREANT_PIN(53),
	FIREANT_PIN(54),
	FIREANT_PIN(55),
	FIREANT_PIN(56),
	FIREANT_PIN(57),
	FIREANT_PIN(58),
	FIREANT_PIN(59),
	FIREANT_PIN(60),
	FIREANT_PIN(61),
	FIREANT_PIN(62),
	FIREANT_PIN(63),
};

static int fireant_gpio_probe(struct udevice *dev)
{
	struct gpio_dev_priv *uc_priv;

	uc_priv = dev_get_uclass_priv(dev);
	uc_priv->bank_name = "fireant-gpio";
	uc_priv->gpio_count = ARRAY_SIZE(fireant_pins);

	return 0;
}

static struct driver fireant_gpio_driver = {
	.name	= "fireant-gpio",
	.id	= UCLASS_GPIO,
	.probe	= fireant_gpio_probe,
	.ops	= &mscc_gpio_ops,
};

static const unsigned long fireant_gpios[] = {
	[MSCC_GPIO_OUT_SET] = 0x00,
	[MSCC_GPIO_OUT_CLR] = 0x08,
	[MSCC_GPIO_OUT] = 0x10,
	[MSCC_GPIO_IN] = 0x18,
	[MSCC_GPIO_OE] = 0x20,
	[MSCC_GPIO_INTR] = 0x28,
	[MSCC_GPIO_INTR_ENA] = 0x30,
	[MSCC_GPIO_INTR_IDENT] = 0x38,
	[MSCC_GPIO_ALT0] = 0x40,
	[MSCC_GPIO_ALT1] = 0x48,
};

int fireant_pinctrl_probe(struct udevice *dev)
{
	int ret;

	ret = mscc_pinctrl_probe(dev, FUNC_MAX, fireant_pins,
				 ARRAY_SIZE(fireant_pins),
				 fireant_function_names,
				 fireant_gpios);

	if (ret)
		return ret;

	ret = device_bind(dev, &fireant_gpio_driver, "fireant-gpio", NULL,
			  dev_of_offset(dev), NULL);

	if (ret)
		return ret;

	return 0;
}

static const struct udevice_id fireant_pinctrl_of_match[] = {
	{ .compatible = "mscc,fireant-pinctrl" },
	{},
};

U_BOOT_DRIVER(fireant_pinctrl) = {
	.name = "fireant-pinctrl",
	.id = UCLASS_PINCTRL,
	.of_match = of_match_ptr(fireant_pinctrl_of_match),
	.probe = fireant_pinctrl_probe,
	.priv_auto_alloc_size = sizeof(struct mscc_pinctrl),
	.ops = &mscc_pinctrl_ops,
};
