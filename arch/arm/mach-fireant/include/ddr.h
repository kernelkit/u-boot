/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2018 Microsemi Corporation
 */

#define _DDR4_32_2X16_8GB_G6 0
#define _DDR4_EMU            1
#define _DDR4_VAL_BOARD      2
#define _DDR4_REF_BOARD      3
#define _DDR3_PCB135_BOARD   4

#include "tc_defines.h"

#if defined (CONFIG_DDR_FIREANT_PCB125)
#define _MODELNAME _DDR4_VAL_BOARD
#elif defined (CONFIG_DDR_FIREANT_PCB134)
#define _MODELNAME _DDR4_REF_BOARD
#elif defined (CONFIG_DDR_FIREANT_PCB135)
#define _MODELNAME _DDR3_PCB135_BOARD
#endif

#if _DDR_EMU == 1
#define _MODEL_NAME _DDR4_EMU
#endif

#ifndef _MODEL_NAME
#define _MODEL_NAME _DDR4_32_2X16_8GB_G6
#endif

#define DDR3 3
#define DDR4 4

#if   _MODELNAME == _DDR4_32_2X16_8GB_G6
#include "ddr4_32bit_two_X16_8Gb_each_config.h"
#elif _MODELNAME == _DDR4_EMU
#include "ddr4_emu_config.h"
#elif _MODELNAME == _DDR4_VAL_BOARD
#include "ddr4_val_board_config.h"
#define init_by_pub 0
#define params_zqdiv		0x2b	/* 40 ohms drive, 120 ohm ODT */
#define params_asym_drv_pd	0xf	/* 30 ohms */
#define params_asym_drv_pu	0xb	/* 40 ohms */
#elif _MODELNAME == _DDR4_REF_BOARD
#include "ddr4_ref_board_config.h"
#define init_by_pub 0
#define params_zqdiv		0x2b	/* 40 ohms drive, 120 ohm ODT */
#define params_asym_drv_pd	0xf	/* 30 ohms */
#define params_asym_drv_pu	0xb	/* 40 ohms */
#elif _MODELNAME == _DDR3_PCB135_BOARD
#include "ddr3_pcb135_board_config.h"
#define params_asym_drv_pd	0
#define params_asym_drv_pu	0
#define init_by_pub 0
#define params_zqdiv		0x2d	/* 40 ohms drive, 60 ohms ODT */
#endif

#ifndef data_training
#error Need data_training define
#endif

#ifndef init_by_pub
#error Need init_by_pub define
#endif
