// SPDX-License-Identifier: GPL-2.0
/*
 * BPI-R3 / BPI-R3-mini / Acer Connect Vero W board variant detection
 */

#include <env.h>
#include <fdt_support.h>
#include <image.h>
#include <asm/cache.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/sizes.h>
#include <linux/string.h>

DECLARE_GLOBAL_DATA_PTR;

enum bpir3_variant {
	BPIR3,
	BPIR3_MINI,
	ASUS_VERO_W,
};

/*
 * Acer Connect Vero W ships with 1 GiB DDR; BPI-R3 and BPI-R3-mini
 * both ship with 2 GiB. Probe the +1 GiB mark with patterns that are
 * distinct from a parallel write at the DRAM base, so an aliased
 * (wrap-around) address is detected as such instead of returning a
 * false positive when the DDR controller mirrors the high address
 * onto base RAM.
 *
 * MT7986 DRAM base is 0x40000000. NOTE: when this board file is
 * chain-loaded via "go" from a previous U-Boot, the dcache is
 * already enabled. We must flush after writes and invalidate before
 * reads so the test actually exercises the AXI/DDR bus instead of
 * giving a false positive from cache hits at +1 GiB.
 */
#define MT7986_DRAM_BASE	0x40000000UL
#define PROBE_BASE_ADDR		MT7986_DRAM_BASE
#define PROBE_HIGH_ADDR		(MT7986_DRAM_BASE + SZ_1G)
#define PROBE_LINE_BYTES	64	/* worst-case ARMv8 cacheline */

static void probe_flush(unsigned long addr)
{
	flush_dcache_range(addr, addr + PROBE_LINE_BYTES);
}

static void probe_invalidate(unsigned long addr)
{
	invalidate_dcache_range(addr, addr + PROBE_LINE_BYTES);
}

static u32 probe_read(unsigned long addr)
{
	probe_invalidate(addr);
	return *(volatile u32 *)addr;
}

static void probe_write(unsigned long addr, u32 val)
{
	*(volatile u32 *)addr = val;
	probe_flush(addr);
}

static bool ram_above_1g_present(void)
{
	u32 sb, sp, b1, p1, b2, p2;

	sb = probe_read(PROBE_BASE_ADDR);
	sp = probe_read(PROBE_HIGH_ADDR);

	probe_write(PROBE_BASE_ADDR, 0x12345678);
	probe_write(PROBE_HIGH_ADDR, 0xdeadbeef);
	b1 = probe_read(PROBE_BASE_ADDR);
	p1 = probe_read(PROBE_HIGH_ADDR);

	probe_write(PROBE_BASE_ADDR, 0xa5a5a5a5);
	probe_write(PROBE_HIGH_ADDR, 0x5a5a5a5a);
	b2 = probe_read(PROBE_BASE_ADDR);
	p2 = probe_read(PROBE_HIGH_ADDR);

	probe_write(PROBE_BASE_ADDR, sb);
	probe_write(PROBE_HIGH_ADDR, sp);

	return b1 == 0x12345678 && p1 == 0xdeadbeef &&
	       b2 == 0xa5a5a5a5 && p2 == 0x5a5a5a5a;
}

/*
 * Detect BPI-R3 vs BPI-R3-mini by probing for the Airoha EN8811H PHY.
 *
 * BPI-R3-mini: EN8811H is directly on the MDIO bus at addr 14.
 *              GPIO49 (active-low) is its reset; PHYSID1 = 0x03a2.
 * BPI-R3:      MT7531AE switch via SGMII; nothing at MDIO addr 14 → 0xffff.
 *
 * NOTE: I2C 0x50 is NOT usable — BPI-R3 SFP cage EEPROMs occupy 0x50–0x5b.
 */

/*
 * MT7986 GPIO — gpio_base = 0x1001f000
 *
 * DIR  register: base + 0x000 + (pin/32)*0x10,  1 bit/pin  (1=output)
 * DOUT register: base + 0x100 + (pin/32)*0x10,  1 bit/pin
 * MODE register: base + 0x300 + (pin*4/32)*0x10, 4 bits/pin (0=GPIO, 1=eth…)
 */
#define MT7986_GPIO_BASE	0x1001f000UL
#define GPIO_DIR_REG(p)		(MT7986_GPIO_BASE + 0x000 + ((p) / 32) * 0x10)
#define GPIO_DOUT_REG(p)	(MT7986_GPIO_BASE + 0x100 + ((p) / 32) * 0x10)
#define GPIO_MODE_REG(p)	(MT7986_GPIO_BASE + 0x300 + (((p) * 4) / 32) * 0x10)
#define GPIO_MODE_SHIFT(p)	(((p) * 4) % 32)

/* EN8811H PHY reset: GPIO49, active-low */
#define EN8811H_RST_GPIO	49
/* EN8811H power control lines: active-low enables on some BPI-R3-mini dts */
#define EN8811H_PWR_A_GPIO	11
#define EN8811H_PWR_B_GPIO	12
/* Alternative EN8811H power control lines used by other mini trees */
#define EN8811H_PWR2_A_GPIO	16
#define EN8811H_PWR2_B_GPIO	17

/* MDC/MDIO pins: GPIO67 = MDC, GPIO68 = MDIO, both on function 1 ("eth") */
#define MDC_GPIO		67
#define MDIO_GPIO		68

/*
 * MT7986 Frame Engine: ethernet@15100000, GMAC at +0x10000
 *
 * PPSC (+0x0000): MDC clock config — bits[29:24] = divider, bit[4] = turbo
 * PIAC (+0x0004): PHY indirect access — write then poll PHY_ACS_ST clear
 */
#define GMAC_BASE		0x15110000UL
#define GMAC_PPSC		(GMAC_BASE + 0x0000)
#define GMAC_PIAC		(GMAC_BASE + 0x0004)

#define PPSC_MDC_CFG_MASK	GENMASK(29, 24)
#define PPSC_MDC_CFG(d)		(((d) & 0x3f) << 24)
#define PPSC_MDC_TURBO		BIT(4)
/* divider = 10 → MDC ≈ 2.5 MHz from 25 MHz reference */
#define MDC_DIVIDER		10

#define PIAC_ACS_ST		BIT(31)
#define PIAC_REG_S		25
#define PIAC_PHY_S		20
#define PIAC_CMD_S		18
#define PIAC_ST_S		16
#define PIAC_DATA_MASK		0xffffU
#define PIAC_CMD_READ		2
#define PIAC_ST_C22		1

/* EN8811H PHY ID register values */
#define EN8811H_PHYSID1		0x03a2
#define EN8811H_PHYSID2_MASK	0xfff0
#define EN8811H_PHYSID2		0xa410
#define MII_PHYSID1		0x02	/* IEEE MII register 2 */
#define MII_PHYSID2		0x03	/* IEEE MII register 3 */

/* Set a GPIO pin's mode field (0 = GPIO, 1 = eth function, …) */
static void gpio_set_mode(unsigned int pin, unsigned int func)
{
	clrsetbits_le32(GPIO_MODE_REG(pin),
			0xf << GPIO_MODE_SHIFT(pin),
			(func & 0xf) << GPIO_MODE_SHIFT(pin));
}

/* Configure a GPIO pin as output and drive it high or low */
static void gpio_out(unsigned int pin, int val)
{
	setbits_le32(GPIO_DIR_REG(pin), BIT(pin % 32));
	if (val)
		setbits_le32(GPIO_DOUT_REG(pin), BIT(pin % 32));
	else
		clrbits_le32(GPIO_DOUT_REG(pin), BIT(pin % 32));
}

/*
 * Clause-22 MDIO read via the MT7986 GMAC PHY indirect access register.
 * Returns the 16-bit register value, or -1 on timeout.
 */
static int mdio_read_c22(unsigned int phy, unsigned int reg)
{
	u32 val;
	int i;

	val = (PIAC_ST_C22   << PIAC_ST_S)  |
	      (PIAC_CMD_READ << PIAC_CMD_S) |
	      (phy           << PIAC_PHY_S) |
	      (reg           << PIAC_REG_S);
	writel(val | PIAC_ACS_ST, GMAC_PIAC);

	for (i = 0; i < 5000; i++) {
		val = readl(GMAC_PIAC);
		if (!(val & PIAC_ACS_ST))
			return (int)(val & PIAC_DATA_MASK);
		udelay(1);
	}

	return -1; /* timeout */
}

static void enable_mini_power_lines(unsigned int gpio_a, unsigned int gpio_b)
{
	gpio_set_mode(gpio_a, 0);	/* mode 0 = GPIO */
	gpio_set_mode(gpio_b, 0);	/* mode 0 = GPIO */
	gpio_out(gpio_a, 0);		/* active-low enable */
	gpio_out(gpio_b, 0);		/* active-low enable */
}

static void pulse_mini_phy_reset(void)
{
	gpio_set_mode(EN8811H_RST_GPIO, 0);	/* mode 0 = GPIO */
	gpio_out(EN8811H_RST_GPIO, 0);		/* assert reset */
	mdelay(10);
	gpio_out(EN8811H_RST_GPIO, 1);		/* deassert reset */
	mdelay(20);
}

static bool is_en8811_id(int id1, int id2)
{
	return id1 == EN8811H_PHYSID1 &&
	       (id2 & EN8811H_PHYSID2_MASK) == EN8811H_PHYSID2;
}

static int probe_en8811_addr(unsigned int phy_addr)
{
	int id1, id2;

	id1 = mdio_read_c22(phy_addr, MII_PHYSID1);
	id2 = mdio_read_c22(phy_addr, MII_PHYSID2);

	if (id1 < 0 || id2 < 0)
		return 0;

	return is_en8811_id(id1, id2);
}

static enum bpir3_variant detect_bpir3_variant(void)
{
	unsigned int pwr_a[] = { EN8811H_PWR_A_GPIO, EN8811H_PWR2_A_GPIO };
	unsigned int pwr_b[] = { EN8811H_PWR_B_GPIO, EN8811H_PWR2_B_GPIO };
	unsigned int i;

	/* 1 GiB DDR → Acer Connect Vero W; skip MDIO probe entirely. */
	if (!ram_above_1g_present())
		return ASUS_VERO_W;

	/* Switch GPIO67 (MDC) and GPIO68 (MDIO) to eth function */
	gpio_set_mode(MDC_GPIO,  1);
	gpio_set_mode(MDIO_GPIO, 1);

	/* Configure MDC clock: enable turbo + set safe divider (~2.5 MHz) */
	setbits_le32(GMAC_PPSC, PPSC_MDC_TURBO);
	clrsetbits_le32(GMAC_PPSC, PPSC_MDC_CFG_MASK, PPSC_MDC_CFG(MDC_DIVIDER));

	/*
	 * Enable EN8811H power rails and probe; some mini boards use
	 * GPIO11/12, others GPIO16/17.
	 */
	for (i = 0; i < ARRAY_SIZE(pwr_a); i++) {
		enable_mini_power_lines(pwr_a[i], pwr_b[i]);
		pulse_mini_phy_reset();

		if (probe_en8811_addr(14) || probe_en8811_addr(15)) {
			/* Assert reset; DM eth-phy will deassert with proper delays */
			gpio_out(EN8811H_RST_GPIO, 0);
			return BPIR3_MINI;
		}
	}

	return BPIR3;
}

int board_fit_config_name_match(const char *name)
{
	static int variant = -1;

	if (variant < 0)
		variant = detect_bpir3_variant();

	switch (variant) {
	case BPIR3_MINI:
		return strcmp(name, "mt7986a-bpi-r3-mini") ? -1 : 0;
	case ASUS_VERO_W:
	return strcmp(name, "mt7986a-acer-connect-vero-w") ? -1 : 0;
	case BPIR3:
	default:
		/*
		 * Accept both sd and emmc variants of BPI-R3;
		 * storage type is determined by spl_boot_device(), not here.
		 */
		return (strcmp(name, "mt7986a-bpi-r3-sd") == 0 ||
			strcmp(name, "mt7986a-bpi-r3-emmc") == 0) ? 0 : -1;
	}
}

int board_late_init(void)
{
	const char *model = fdt_getprop(gd->fdt_blob, 0, "model", NULL);

	if (model && strstr(model, "Mini"))
		env_set("fdtfile", "mediatek/mt7986a-bananapi-bpi-r3-mini.dtb");
	else if (model && strstr(model, "Vero"))
	env_set("fdtfile", "mediatek/mt7986a-acer-connect-vero-w.dtb");

	return 0;
}
