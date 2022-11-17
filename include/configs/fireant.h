/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2018 Microsemi Corporation
 */

#ifndef __INCL_INCLUDE_CONFIGS_FIREANT__
#define __INCL_INCLUDE_CONFIGS_FIREANT__

#include <linux/sizes.h>

#if defined(CONFIG_ARMV8_MULTIENTRY)
#define CONFIG_ARCH_MISC_INIT	/* Enabling 2nd core */
#endif

//#define CONFIG_ARMV8_SWITCH_TO_EL1

/* 32-bit register interface */
#define CONFIG_SYS_NS16550_MEM32

#define CONFIG_SYS_CBSIZE               SZ_1K
#define CONFIG_ENV_SIZE                 SZ_8K

#if defined(CONFIG_ENV_IS_IN_SPI_FLASH) && !defined(CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET               SZ_1M
#define CONFIG_ENV_SECT_SIZE		SZ_256K

#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET_REDUND        (CONFIG_ENV_OFFSET + CONFIG_ENV_SECT_SIZE)
#endif

#define PHYS_SPI			0x000000000
#define PHYS_NAND			0x400000000
#define PHYS_DEVICE_REG			0x600000000
#define PHYS_DDR			0x700000000
#define VIRT_DDR			0x700000000 /* 1:1 */
#define PHYS_SDRAM_1_SIZE		CONFIG_SYS_SDRAM_SIZE
#define PHYS_PCIE_TARGET		0x900000000

#define PHYS_SDRAM_1                    PHYS_DDR
#define VIRT_SDRAM_1                    VIRT_DDR
#define CONFIG_SYS_SDRAM_BASE		VIRT_SDRAM_1
#define CONFIG_SYS_LOAD_ADDR		(VIRT_SDRAM_1 + (PHYS_SDRAM_1_SIZE/2))

#define CONFIG_SYS_INIT_SP_ADDR         (PHYS_DDR + SZ_128M)

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + SZ_8M)

#if defined(CONFIG_CMD_MEMTEST)
/* Allow first 128M for memory test */
#define CONFIG_SYS_MEMTEST_START	VIRT_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(VIRT_SDRAM_1 + PHYS_SDRAM_1_SIZE - SZ_16M)
#define CONFIG_SYS_MEMTEST_SCRATCH	(CONFIG_SYS_MEMTEST_END + 64)
#endif

#define CONFIG_GICV3
#ifdef CONFIG_GICV3
#define GICD_BASE                       (0x600300000)
#define GICR_BASE                       (0x600340000)
#endif

#define COUNTER_FREQUENCY		(0xFA00000)	/* 250MHz */

#define CONFIG_BOARD_TYPES

#define PHYS_SRAM_ADDR			0x630000000
#define PHYS_SRAM_SIZE			SZ_64K
#define CONFIG_ENABLE_ARM_SOC_BOOT0_HOOK
#define BOOT0_SP_ADDR			(PHYS_SRAM_ADDR + PHYS_SRAM_SIZE)

#if defined(CONFIG_MTDIDS_DEFAULT) && defined(CONFIG_MTDPARTS_DEFAULT)
#define FIREANT_DEFAULT_MTD_ENV			      \
	"mtdparts="CONFIG_MTDPARTS_DEFAULT"\0"	      \
	"mtdids="CONFIG_MTDIDS_DEFAULT"\0"
#else
#define FIREANT_DEFAULT_MTD_ENV    /* Go away */
#endif

#if defined(CONFIG_MMC_SDHCI)
#define PCB_SUFFIX "_emmc"
#define FIREANT_MTD_SUPPORT_ENV						\
	"mmcaddr=760000000\0"						\
	"mmc_cur=1\0"							\
	"mmc_bak=2\0"							\
	"mmc_dev=mmc 0\0"						\
	"mmc_image=new.ext4.gz\0"					\
	"mmc_format=gpt guid ${mmc_dev} mmc_guid"			\
	";gpt write ${mmc_dev} ${mmc_part}; env save\0"			\
	"mmc_swap=env set mmc_cur ${mmc_bak}; env save\0"		\
	"mmc_dlup=dhcp ${mmc_image};unzip ${fileaddr} ${mmcaddr};run mmc_update\0" \
	"mmc_update=run mmcgetoffset"					\
	";mmc write ${mmcaddr} ${mmc_start} ${filesize_512}\0"		\
	"mmc_boot=run mmc_tryboot;env set mmc_cur ${mmc_bak}"		\
	";run mmc_tryboot\0"						\
	"mmc_tryboot=run mmcload"					\
	";setenv mtdroot root_next=/dev/mmcblk0p${mmc_cur}; run ramboot\0" \
	"mmcgetoffset=part start ${mmc_dev} ${mmc_cur} mmc_start\0"	\
	"mmcload=ext4load ${mmc_dev}:${mmc_cur} ${loadaddr} Image.itb\0" \
	"mmc_part=uuid_disk=${mmc_guid};"				\
	"name=Boot0,size=1024MiB,type=linux;"				\
	"name=Boot1,size=1024MiB,type=linux;"				\
	"name=Data,size=1536MiB,type=linux\0"
#define CONFIG_ENV_CALLBACK_LIST_STATIC "filesize:filesize,mmc_cur:mmc_cur,"
#define BOOTCMD_DEFAULT "mmc_boot"
#else
#define PCB_SUFFIX ""
#define FIREANT_MTD_SUPPORT_ENV						\
	"nand_cur=0\0"							\
	"nand_bak=1\0"							\
	"nand_image=new.ubifs\0"					\
	"nand_mtdroot=root=ubi0:rootfs ro rootfstype=ubifs\0"		\
	"nand_swap=env set nand_cur ${nand_bak}; env save\0"		\
	"nand_dlup=dhcp ${nand_image};run nand_update\0"		\
	"nand_update=sf probe;mtd erase Boot${nand_cur};ubi part Boot${nand_cur}" \
	";ubi create rootfs -;ubi write ${fileaddr} rootfs ${filesize}\0" \
	"nandload=sf probe;ubi part Boot${nand_cur};ubifsmount ubi0:rootfs" \
	";ubifsload - /Image.itb\0"					\
	"nand_boot=run nand_tryboot;env set nand_cur ${nand_bak}"	\
	";run nand_tryboot\0"						\
	"nand_tryboot=run nandload"					\
	";setenv mtdroot ubi.mtd=Boot${nand_cur},2048 ${nand_mtdroot}"	\
	";run ramboot\0"
#define CONFIG_ENV_CALLBACK_LIST_STATIC "nand_cur:nand_cur,"
#define BOOTCMD_DEFAULT "nand_boot"
#endif

#if defined (CONFIG_DDR_FIREANT_PCB125)
#define FIREANT_PCB "pcb125" PCB_SUFFIX
#elif defined (CONFIG_DDR_FIREANT_PCB134)
#define FIREANT_PCB "pcb134" PCB_SUFFIX
#elif defined (CONFIG_DDR_FIREANT_PCB135)
#define FIREANT_PCB "pcb135" PCB_SUFFIX
#else
#error Unknown board type
#endif

#define CONFIG_EXTRA_ENV_SETTINGS					\
	FIREANT_DEFAULT_MTD_ENV						\
	FIREANT_MTD_SUPPORT_ENV						\
	"bootargs_extra=loglevel=4\0"					\
	"bootcmd=run " BOOTCMD_DEFAULT "\0"				\
	"bootdelay=3\0"							\
	"loadaddr=740000000\0"						\
	"console=ttyS0,115200n8\0"					\
	"pcb=" FIREANT_PCB "\0"						\
	"ramboot=run setup; bootm #${pcb}\0"				\
	"rootargs=root=/dev/ram0 rw rootfstype=squashfs\0"		\
	"setup=setenv bootargs console=${console} ${mtdparts}"		\
	" ${rootargs} ${mtdroot} fis_act=${active} ${bootargs_extra}\0" \
        "nor_boot=sf probe"                                             \
	"; env set active linux; run nor_tryboot"			\
	"; env set active linux.bk; run nor_tryboot\0"			\
        "nor_tryboot=mtd read ${active} ${loadaddr}; run ramboot\0"	\
	"nor_image=new.itb\0"						\
	"nor_dlup=dhcp ${nor_image}; run nor_update\0"			\
	"nor_update=sf probe; sf update ${fileaddr} linux ${filesize}\0" \
	"nor_parts=spi0.0:1m(UBoot),256k(Env),256k(Env.bk),"		\
	"20m(linux),20m(linux.bk),32m(rootfs_data)\0"			\
	"nor_only=env set mtdparts mtdparts=${nor_parts}"		\
	";env set bootcmd run nor_boot;env save\0"			\
	"ubupdate=sf probe; sf update ${fileaddr} 0 ${filesize}\0"	\
	"ramboot=run setup; bootm #${pcb}\0"				\
	"bootdelay=3\0"

#define CONFIG_ENV_FLAGS_LIST_STATIC "pcb:sc,pcb_rev:do"

/* Need writeb */
#define CONFIG_MMC_SDHCI_IO_ACCESSORS

#define CONFIG_OF_BOARD_SETUP	/* Need to inject misc board stuff */

#define CONFIG_SYS_BOOTMAPSZ	SZ_64M	/* Initial map for Linux*/
#define CONFIG_SYS_BOOTM_LEN	SZ_64M	/* Increase max gunzip size */

#endif	/* __INCL_INCLUDE_CONFIGS_FIREANT__ */
