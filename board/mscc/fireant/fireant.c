// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2018 Microsemi Corporation
 */

#include <common.h>
#include <miiphy.h>
#include <asm/armv8/mmu.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <led.h>
#include <debug_uart.h>
#include <spi.h>
#include <asm/sections.h>
#include <env_internal.h>
#include <command.h>

#include "mscc_fa_regs_devcpu_gcb.h"
#include "mscc_fa_regs_cpu.h"
#include "mscc_fa_regs_subcpu_sys_cfg.h"

#include "fa_helpers.h"

DECLARE_GLOBAL_DATA_PTR;

enum {
	BOARD_TYPE_PCB125 = 0xAABBEE00,
	BOARD_TYPE_PCB134,
	BOARD_TYPE_PCB135,
};

static bool spi_cs_init;
static u32 spi2mask;

static struct mm_region fa_mem_map[] = {
	{
		.virt = VIRT_SDRAM_1,
		.phys = PHYS_SDRAM_1,
		.size = PHYS_SDRAM_1_SIZE,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		.virt = PHYS_SPI,
		.phys = PHYS_SPI,
		.size = 1UL * SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 (UL(3) << 6) | /* Read-only */
			 PTE_BLOCK_INNER_SHARE
	}, {
		.virt = PHYS_DEVICE_REG,
		.phys = PHYS_DEVICE_REG,
		.size = SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = fa_mem_map;

void reset_cpu(ulong ignore)
{
	/* Make sure the core is UN-protected from reset */
	clrbits_le32(MSCC_CPU_RESET_PROT_STAT,
		     MSCC_M_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE);

	writel(MSCC_M_DEVCPU_GCB_SOFT_RST_SOFT_CHIP_RST, MSCC_DEVCPU_GCB_SOFT_RST);
}

int board_phy_config(struct phy_device *phydev)
{
	if (gd->board_type == BOARD_TYPE_PCB134 ||
	    gd->board_type == BOARD_TYPE_PCB135) {
		debug("board_phy_config: phy_write(SGMII/CAT5)\n");
		/* reg 23 - PHY Control Register #1 */
		/* Setup skew and RX idle clock, datasheet table 36. */
		/* 15:12 - AC/Media Interface Mode Select:
		 * SGMII CAT5:
		 * Modified Clause 37 auto-negotiation disabled,
		 * 625MHz SCLK Clock Disabled
		 */
		phy_write(phydev, 0, 23, 0xba20); /* Set SGMII mode */
		phy_write(phydev, 0,  0, 0x9040); /* Reset */
		phy_write(phydev, 0,  4, 0x0de1); /* Setup ANEG */
		phy_write(phydev, 0,  9, 0x0200); /* Setup ANEG */
		phy_write(phydev, 0,  0, 0x1240); /* Restart ANEG */
	}

	return 0;
}

static inline void mscc_gpio_set_alternate_0(int gpio, int mode)
{
	u32 mask = BIT(gpio);
	u32 val0, val1;

	val0 = readl(MSCC_DEVCPU_GCB_GPIO_ALT(0));
	val1 = readl(MSCC_DEVCPU_GCB_GPIO_ALT(1));
	if (mode == 1) {
		val0 |= mask;
		val1 &= ~mask;
	} else if (mode == 2) {
		val0 &= ~mask;
		val1 |= mask;
	} else if (mode == 3) {
		val0 |= mask;
		val1 |= mask;
	} else {
		val0 &= ~mask;
		val1 &= ~mask;
	}
	writel(val0, MSCC_DEVCPU_GCB_GPIO_ALT(0));
	writel(val1, MSCC_DEVCPU_GCB_GPIO_ALT(1));
}

static inline void mscc_gpio_set_alternate_1(int gpio, int mode)
{
	u32 mask = BIT(gpio);
	u32 val0, val1;

	val0 = readl(MSCC_DEVCPU_GCB_GPIO_ALT1(0));
	val1 = readl(MSCC_DEVCPU_GCB_GPIO_ALT1(1));
	if (mode == 1) {
		val0 |= mask;
		val1 &= ~mask;
	} else if (mode == 2) {
		val0 &= ~mask;
		val1 |= mask;
	} else if (mode == 3) {
		val0 |= mask;
		val1 |= mask;
	} else {
		val0 &= ~mask;
		val1 &= ~mask;
	}
	writel(val0, MSCC_DEVCPU_GCB_GPIO_ALT1(0));
	writel(val1, MSCC_DEVCPU_GCB_GPIO_ALT1(1));
}

static inline void mscc_gpio_set_alternate(int gpio, int mode)
{
	if (gpio < 32)
		mscc_gpio_set_alternate_0(gpio, mode);
	else
		mscc_gpio_set_alternate_1(gpio - 32, mode);
}

#ifdef CONFIG_DEBUG_UART_BOARD_INIT
void board_debug_uart_init(void)
{
	mscc_gpio_set_alternate(10, 1);
	mscc_gpio_set_alternate(11, 1);
}
#endif

int print_cpuinfo(void)
{
	printf("CPU:   ARM A53\n");
	return 0;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	debug("gd: %08lx, Ram size %08llx\n", (unsigned long)gd, gd->ram_size);
	return 0;
}

#if defined(CONFIG_ARCH_MISC_INIT)
int arch_misc_init(void)
{
#if defined(CONFIG_ARMV8_MULTIENTRY)
	u64 r_start = (u64) _start;
	debug("Enable CPU1: Start at 0x%08llx\n", r_start);
	writel((u32) ((r_start >> 0) >> 2), MSCC_CPU_CPU1_RVBAR_LSB);
	writel((u32) ((r_start >> 32) >> 2), MSCC_CPU_CPU1_RVBAR_MSB);
	debug("Reset vector: 0x%08x:0x%08x\n",
	      readl(MSCC_CPU_CPU1_RVBAR_MSB),
	      readl(MSCC_CPU_CPU1_RVBAR_LSB));
	clrbits_le32(MSCC_CPU_RESET, MSCC_M_CPU_RESET_CPU_CORE_1_COLD_RST);
#endif
	return 0;
}
#endif

#if defined(CONFIG_DESIGNWARE_SPI)
#define SPI_OWNER_MASK				\
	MSCC_M_CPU_GENERAL_CTRL_IF_SI2_OWNER |	\
	MSCC_M_CPU_GENERAL_CTRL_IF_SI_OWNER

#define SPI_OWNER_SPI1_MASK			  \
	MSCC_F_CPU_GENERAL_CTRL_IF_SI2_OWNER(1) | \
	MSCC_F_CPU_GENERAL_CTRL_IF_SI_OWNER(2)

#define SPI_OWNER_SPI2_MASK			  \
	MSCC_F_CPU_GENERAL_CTRL_IF_SI2_OWNER(2) | \
	MSCC_F_CPU_GENERAL_CTRL_IF_SI_OWNER(1)

static inline void spi_set_owner(u32 cs)
{
	u32 owbits;
	if (spi2mask & BIT(cs)) {
		owbits = SPI_OWNER_SPI2_MASK;
	} else {
		owbits = SPI_OWNER_SPI1_MASK;
	}
	clrsetbits_le32(MSCC_CPU_GENERAL_CTRL,
			SPI_OWNER_MASK, owbits);
	udelay(1);
}

static void spi_manage_init(struct udevice *dev)
{
	struct udevice *paren = dev_get_parent(dev);
	spi2mask = dev_read_u32_default(paren, "interface-mapping-mask", 0);
	debug("spi2mask = %08x\n", spi2mask);
}

void external_cs_manage(struct udevice *dev, bool nen)
{
	bool enable = !nen;
	u32 cs = spi_chip_select(dev);
	if (!spi_cs_init) {
		spi_manage_init(dev);
		spi_cs_init = true;
	}
	if (enable) {
		u32 mask = ~BIT(cs); /* Active low */
		/* CS - start disabled */
		clrsetbits_le32(MSCC_CPU_SS_FORCE,
				MSCC_M_CPU_SS_FORCE_SS_FORCE,
				MSCC_F_CPU_SS_FORCE_SS_FORCE(0xffff));
		/* CS override drive enable */
		clrsetbits_le32(MSCC_CPU_SS_FORCE_ENA,
				MSCC_M_CPU_SS_FORCE_ENA_SS_FORCE_ENA,
				MSCC_F_CPU_SS_FORCE_ENA_SS_FORCE_ENA(true));
		udelay(1);
		/* Set owner */
		spi_set_owner(cs);
		/* CS - enable now */
		clrsetbits_le32(MSCC_CPU_SS_FORCE,
				MSCC_M_CPU_SS_FORCE_SS_FORCE,
				MSCC_F_CPU_SS_FORCE_SS_FORCE(mask));

	} else {
		/* CS value */
		clrsetbits_le32(MSCC_CPU_SS_FORCE,
				MSCC_M_CPU_SS_FORCE_SS_FORCE,
				MSCC_F_CPU_SS_FORCE_SS_FORCE(0xffff));
		udelay(1);
		/* CS override drive disable */
		clrsetbits_le32(MSCC_CPU_SS_FORCE_ENA,
				MSCC_M_CPU_SS_FORCE_ENA_SS_FORCE_ENA,
				MSCC_F_CPU_SS_FORCE_ENA_SS_FORCE_ENA(false));
		udelay(1);
		/* SI owner = SIBM */
		clrsetbits_le32(MSCC_CPU_GENERAL_CTRL,
				SPI_OWNER_MASK,
				MSCC_F_CPU_GENERAL_CTRL_IF_SI2_OWNER(2) |
				MSCC_F_CPU_GENERAL_CTRL_IF_SI_OWNER(1));
	}
}
#endif

static void do_board_detect(void)
{
	debug("ptr %p, val 0x%08lx\n",
	      &gd->board_type, gd->board_type);
#if defined (CONFIG_DDR_FIREANT_PCB125)
	gd->board_type = BOARD_TYPE_PCB125;
#elif defined (CONFIG_DDR_FIREANT_PCB134)
	gd->board_type = BOARD_TYPE_PCB134;
#elif defined (CONFIG_DDR_FIREANT_PCB135)
	gd->board_type = BOARD_TYPE_PCB135;
#else
#error Unknown board type
#endif
}

int board_init(void)
{
	debug("Board init\n");
	do_board_detect();

	/* CS0 alone on boot master region 0 - SPI NOR flash */
	writel((u16) ~BIT(0), MSCC_DEVCPU_GCB_SPI_MASTER_SS0_MASK);

        /* LED setup */
	if (IS_ENABLED(CONFIG_LED))
		led_default_state();

	return 0;
}

#define EARLY_CACHE
#if defined(EARLY_CACHE)
#define EARLY_PGTABLE_SIZE 0x5000
static inline void early_mmu_setup(void)
{
	unsigned int el = current_el();

	gd->arch.tlb_addr = PHYS_SRAM_ADDR;
	gd->arch.tlb_fillptr = gd->arch.tlb_addr;
	gd->arch.tlb_size = EARLY_PGTABLE_SIZE;

	/* Create early page tables */
	setup_pgtables();

	/* point TTBR to the new table */
	set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
			  get_tcr(el, NULL, NULL) &
			  ~(TCR_ORGN_MASK | TCR_IRGN_MASK),
			  MEMORY_ATTRIBUTES);

	set_sctlr(get_sctlr() | CR_M);
}
#endif

int arch_cpu_init(void)
{
	/*
	 * This function is called before U-Boot relocates itself to speed up
	 * on system running. It is not necessary to run if performance is not
	 * critical. Skip if MMU is already enabled by SPL or other means.
	 */
	printch('C');
#if defined(EARLY_CACHE)
	if (get_sctlr() & CR_M)
		return 0;

	printch('I');
	__asm_invalidate_dcache_all();
	__asm_invalidate_tlb_all();
	early_mmu_setup();
	printch('i');
	set_sctlr(get_sctlr() | CR_C);
	printch('c');
#endif

	/* Mysterious CTX init...  */
	writel(0, 0x600109008);	/* Low */
	writel(0, 0x60010900C);	/* Hi */
	writel(1, 0x600109000);	/* Enable */
	printch('t');

	return 0;
}

/*
 * The final tables are identical to early tables, but the tables are
 * in DDR memory instead of device SRAM (which is supposed to be used
 * by the PoE controller).
 */
static inline void final_mmu_setup(void)
{
	u64 tlb_addr_save;
	unsigned int el = current_el();

	/* Use allocated (board_f.c) memory for TLB */
	tlb_addr_save = gd->arch.tlb_addr;

	/* Reset the fill ptr */
	gd->arch.tlb_fillptr = gd->arch.tlb_addr;

	/* Create normal system page tables */
	setup_pgtables();

	/* Create emergency page tables */
	gd->arch.tlb_emerg = gd->arch.tlb_addr = gd->arch.tlb_fillptr;
	setup_pgtables();

	/* Restore normal TLB addr */
	gd->arch.tlb_addr = tlb_addr_save;

	/* Disable cache and MMU */
	dcache_disable();	/* TLBs are invalidated */
	invalidate_icache_all();

	/* point TTBR to the new table */
	set_ttbr_tcr_mair(el, gd->arch.tlb_addr, get_tcr(el, NULL, NULL),
			  MEMORY_ATTRIBUTES);

	set_sctlr(get_sctlr() | CR_M);
}

void enable_caches(void)
{
	final_mmu_setup();
	__asm_invalidate_tlb_all();
	icache_enable();
	dcache_enable();
}

#if defined(CONFIG_ENABLE_ARM_SOC_BOOT0_HOOK)
void boot0(void)
{
	/* Speed up Flash reads */
        clrsetbits_le32(MSCC_CPU_SPI_MST_CFG,
			MSCC_M_CPU_SPI_MST_CFG_CLK_DIV |
			MSCC_M_CPU_SPI_MST_CFG_FAST_READ_ENA,
			MSCC_F_CPU_SPI_MST_CFG_CLK_DIV(28) | /* 250Mhz/X */
			MSCC_F_CPU_SPI_MST_CFG_FAST_READ_ENA(1));

	/* Speed up instructions */
	icache_enable();

	debug_uart_init();

	printch('*');
	ddr_setup();

	/* Release GIC reset */
	clrbits_le32(MSCC_CPU_RESET, MSCC_M_CPU_RESET_GIC_RST);
}
#endif

// Helper for MMC update (512-byte blocks)
static int on_filesize(const char *name, const char *value, enum env_op op,
		       int flags)
{
	ulong file_size = simple_strtoul(value, NULL, 16);

	env_set_hex("filesize_512", DIV_ROUND_UP(file_size, 512));

	return 0;
}
U_BOOT_ENV_CALLBACK(filesize, on_filesize);

// Helper for MMC backup image
static int on_mmc_cur(const char *name, const char *value, enum env_op op,
		      int flags)
{
	ulong mmc_cur = simple_strtoul(value, NULL, 16);

	debug("%s is %s\n", name, value);

	env_set_ulong("mmc_bak", mmc_cur == 1 ? 2 : 1);

	return 0;
}
U_BOOT_ENV_CALLBACK(mmc_cur, on_mmc_cur);

// Helper for NAND backup image
static int on_nand_cur(const char *name, const char *value, enum env_op op,
		      int flags)
{
	ulong nand_cur = simple_strtoul(value, NULL, 16);

	debug("%s is %s\n", name, value);

	env_set_ulong("nand_bak", nand_cur == 0 ? 1 : 0);

	return 0;
}
U_BOOT_ENV_CALLBACK(nand_cur, on_nand_cur);

static void m3_download_boot(u32 *m3_image, size_t image_len)
{
	u32 *m3_code = (u32*) PHYS_SRAM_ADDR;
	int i, j;

	/* Download M3 */
	j = (3 + image_len) / 4;
	for (i = 0; i < j; i++)
		writel(m3_image[i], &m3_code[i]);
	clrsetbits_le32(MSCC_SUBCPU_SYS_CFG_GENERAL_CTRL,
			MSCC_M_SUBCPU_SYS_CFG_GENERAL_CTRL_BOOT_MODE_ENA,
			MSCC_X_SUBCPU_SYS_CFG_GENERAL_CTRL_BOOT_MODE_ENA(false));
	/* Read back to enable */
	(void) readl(MSCC_SUBCPU_SYS_CFG_GENERAL_CTRL);
	/* Enable M3 */
	writel(MSCC_F_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE_PROT_AMBA(true),
	       MSCC_CPU_SUBCPU_SYS_CFG);
}

static int m3_do_reset(cmd_tbl_t *cmdtp, int flag, int argc,
		       char *const argv[])
{
	/* Disable M3 */
	writel(MSCC_F_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE_PROT_AMBA(true) |
	       MSCC_F_CPU_SUBCPU_SYS_CFG_SUBCPU_SYS_RST_FORCE(true),
	       MSCC_CPU_SUBCPU_SYS_CFG);

	printf("M3 was reset\n");

	return CMD_RET_SUCCESS;
}

static int m3_get_env(const char *name, unsigned long *pval)
{
	char *strval;

	strval = env_get(name);
	if (!strval)
		return -ENOENT;

	return strict_strtoul(strval, 16, pval);
}

static int m3_do_boot(cmd_tbl_t *cmdtp, int flag, int argc,
		      char *const argv[])
{
	ulong mem_start, mem_size;

	if (m3_get_env("fileaddr", &mem_start) < 0 ||
	    m3_get_env("filesize", &mem_size) < 0) {
		printf("'fileaddr' and 'filesize' must be set. Start downloading firmware (dhcp)\n");
		return -ENOENT;
	}

	if (mem_size == 0UL || mem_size > (ulong) SZ_64K) {
		printf("Code size must be > 0 and 64K: %ld (%lx)\n", mem_size, mem_size);
		return CMD_RET_FAILURE;
	}

	m3_download_boot((u32*) mem_start, (size_t) mem_size);

	printf("M3 was booted\n");

	return CMD_RET_SUCCESS;
}

static char m3_help_text[] =
	"- M3 aux processor control\n\n"
	"m3\n"
	"m3 reset - Reset M3 processor\n"
	"m3 boot  - Boot M3 processor (do dhcp download firmware first)\n"
	"\n";

U_BOOT_CMD_WITH_SUBCMDS(m3, "m3", m3_help_text,
			U_BOOT_SUBCMD_MKENT(reset, 1, 0, m3_do_reset),
			U_BOOT_SUBCMD_MKENT(boot,  1, 0, m3_do_boot));
