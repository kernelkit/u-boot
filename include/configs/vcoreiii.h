/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2018 Microsemi Corporation
 */

#ifndef __VCOREIII_H
#define __VCOREIII_H

#include <linux/sizes.h>

/* Onboard devices */

#define CONFIG_SYS_MALLOC_LEN		0x1F0000
#define CONFIG_SYS_LOAD_ADDR		0x00100000
#define CONFIG_SYS_INIT_SP_OFFSET       0x400000

#if defined(CONFIG_SOC_LUTON) || defined(CONFIG_SOC_SERVAL)
#define CPU_CLOCK_RATE			416666666 /* Clock for the MIPS core */
#define CONFIG_SYS_MIPS_TIMER_FREQ	208333333
#else
#define CPU_CLOCK_RATE			500000000 /* Clock for the MIPS core */
#define CONFIG_SYS_MIPS_TIMER_FREQ	(CPU_CLOCK_RATE / 2)
#endif
#define CONFIG_SYS_NS16550_CLK		CONFIG_SYS_MIPS_TIMER_FREQ

#define CONFIG_BOARD_TYPES

#if defined(CONFIG_ENV_IS_IN_SPI_FLASH) && !defined(CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET		(1024 * 1024)
#define CONFIG_ENV_SIZE			(8 * 1024)
#define CONFIG_ENV_SECT_SIZE		(256 * 1024)

#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET_REDUND      (CONFIG_ENV_OFFSET + CONFIG_ENV_SECT_SIZE)

#endif

#define CONFIG_SYS_SDRAM_BASE		0x80000000
#if defined(CONFIG_DDRTYPE_H5TQ1G63BFA) || defined(CONFIG_DDRTYPE_MT47H128M8HQ)
#define CONFIG_SYS_SDRAM_SIZE		(128 * SZ_1M)
#elif defined(CONFIG_DDRTYPE_MT41J128M16HA) || defined(CONFIG_DDRTYPE_MT41K128M16JT)
#define CONFIG_SYS_SDRAM_SIZE		(256 * SZ_1M)
#elif defined(CONFIG_DDRTYPE_H5TQ4G63MFR) || defined(CONFIG_DDRTYPE_MT41K256M16)
#define CONFIG_SYS_SDRAM_SIZE		(512 * SZ_1M)
#else
#error Unknown DDR size - please add!
#endif

#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SECT_SIZE)

#define CONFIG_CONS_INDEX		1

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + CONFIG_SYS_SDRAM_SIZE - SZ_4M)

#define CONFIG_SYS_MONITOR_BASE         CONFIG_SYS_TEXT_BASE

#define CONFIG_BOARD_EARLY_INIT_R
#if defined(CONFIG_MTDIDS_DEFAULT) && defined(CONFIG_MTDPARTS_DEFAULT)
#define VCOREIII_DEFAULT_MTD_ENV		    \
	"mtdparts="CONFIG_MTDPARTS_DEFAULT"\0"	    \
	"mtdids="CONFIG_MTDIDS_DEFAULT"\0"
#else
#define VCOREIII_DEFAULT_MTD_ENV    /* Go away */
#endif

#define CONFIG_SYS_BOOTM_LEN      (16 << 20)      /* Increase max gunzip size */

#define CONFIG_EXTRA_ENV_SETTINGS					\
	VCOREIII_DEFAULT_MTD_ENV					\
	"loadaddr=81000000\0"						\
	"console=ttyS0,115200\0"					\
	"setup=setenv bootargs console=${console} ${mtdparts}"		\
	" fis_act=${active} ${bootargs_extra}\0"			\
        "ramboot=run setup; bootm #${pcb}\0"                            \
	"netboot=dhcp; run ramboot\0"					\
	"nor_image=new.itb\0"						\
	"nor_dlup=dhcp ${nor_image}; run nor_update\0"			\
	"nor_update=sf probe;sf update ${fileaddr} linux ${filesize}\0" \
        "nor_boot=sf probe"                                             \
	"; env set active linux; run nor_tryboot"                       \
	"; env set active linux.bk; run nor_tryboot\0"                  \
	"nor_tryboot=mtd read ${active} ${loadaddr}; run ramboot\0"     \
	"ubupdate=sf probe;sf update ${fileaddr} UBoot ${filesize}\0"	\
	"bootcmd=run nor_boot\0"					\
	""

#define CONFIG_ENV_FLAGS_LIST_STATIC "pcb:sc,pcb_rev:do"

/* Env (pcb) is setup by board code */
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#define CONFIG_OF_BOARD_SETUP   /* Need to inject misc board stuff */

#endif				/* __VCOREIII_H */
