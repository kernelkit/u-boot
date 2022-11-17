/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef _VTSS_FIREANT_REGS_DDR_UMCTL2_H_
#define _VTSS_FIREANT_REGS_DDR_UMCTL2_H_

#include "vtss_fireant_regs_common.h"

/***********************************************************************
 *
 * Target: \a DDR_UMCTL2
 *
 * DWC_ddr_umctl2 Memory Map
 *
 ***********************************************************************/

/**
 * Register Group: \a DDR_UMCTL2:UMCTL2_REGS
 *
 * uMCTL2 DDRC Registers
 */


/** 
 * \brief Master Register0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MSTR
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR     VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x0)

/** 
 * \brief
 * Select DDR3 SDRAM
 *  - 1 - DDR3 SDRAM device in use
 *  - 0 - non-DDR3 SDRAM device in use
 * Only present in designs that support DDR3.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . DDR3
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_DDR3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_DDR3  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_DDR3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Select LPDDR2 SDRAM
 *  - 1 - LPDDR2 SDRAM device in use.
 *  - 0 - non-LPDDR2 device in use
 * Present only in designs configured to support LPDDR2.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . LPDDR2
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_LPDDR2(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_LPDDR2  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_LPDDR2(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Select LPDDR3 SDRAM
 *  - 1 - LPDDR3 SDRAM device in use.
 *  - 0 - non-LPDDR3 device in use
 * Present only in designs configured to support LPDDR3.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . LPDDR3
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_LPDDR3(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_LPDDR3  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_LPDDR3(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select DDR4 SDRAM
 *  - 1 - DDR4 SDRAM device in use.
 *  - 0 - non-DDR4 device in use
 * Present only in designs configured to support DDR4.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . DDR4
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_DDR4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_DDR4  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_DDR4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * When set, enable burst-chop (BC4 or 8 on-the-fly) in DDR3/DDR4. Burst
 * Chop for Reads is exercised only in HIF configurations (UMCTL2_INCL_ARB
 * not set) and if in full bus width mode (MSTR.data_bus_width = 00) and if
 * MEMC_BURST_LENGTH=8 or 16. Burst Chop for Writes is exercised only if
 * Partial Writes enabled (UMCTL2_PARTIAL_WR=1) and if CRC is disabled
 * (CRCPARCTL1.crc_enable = 0). If DDR4 CRC/parity retry is enabled
 * (CRCPARCTL1.crc_parity_retry_enable = 1), burst chop is not supported,
 * and this bit must be set to '0'. BC4 (fixed) mode is not supported.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . BURSTCHOP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_BURSTCHOP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_BURSTCHOP  VTSS_BIT(9)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_BURSTCHOP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * If 1, then uMCTL2 uses 2T timing. Otherwise, uses 1T timing. In 2T
 * timing, all command signals (except chip select) are held for 2 clocks
 * on the SDRAM bus. Chip select is asserted on the second cycle of the
 * command
 * Note: 2T timing is not supported in LPDDR2/LPDDR3/LPDDR4 mode
 * Note: 2T timing is not supported if the configuration parameter
 * MEMC_CMD_RTN2IDLE is set
 * Note: 2T timing is not supported in DDR4 geardown mode.
 * Note: 2T timing is not supported in Shared-AC dual channel mode and the
 * register value is don't care.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . EN_2T_TIMING_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_EN_2T_TIMING_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_EN_2T_TIMING_MODE  VTSS_BIT(10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_EN_2T_TIMING_MODE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * 1 indicates put the DRAM in geardown mode (2N) and 0 indicates put the
 * DRAM in normal mode (1N). This register can be changed, only when the
 * Controller is in self-refresh mode.
 * This signal must be set the same value as MR3 bit A3.
 * Note: Geardown mode is not supported if the configuration parameter
 * MEMC_CMD_RTN2IDLE is set
 * Note: Geardown mode is not supported if the configuration parameter
 * UMCTL2_SHARED_AC is set (in Shared-AC mode) and the register value is
 * don't care
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . GEARDOWN_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_GEARDOWN_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_GEARDOWN_MODE  VTSS_BIT(11)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_GEARDOWN_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Selects proportion of DQ bus width that is used by the SDRAM
 *  - 00 - Full DQ bus width to SDRAM
 *  - 01 - Half DQ bus width to SDRAM
 *  - 10 - Quarter DQ bus width to SDRAM
 *  - 11 - Reserved.
 * Note that half bus width mode is only supported when the SDRAM bus width
 * is a multiple of 16, and quarter bus width mode is only supported when
 * the SDRAM bus width is a multiple of 32 and the configuration parameter
 * MEMC_QBUS_SUPPORT is set. Bus width refers to DQ bus width (excluding
 * any ECC width).
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . DATA_BUS_WIDTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_DATA_BUS_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_DATA_BUS_WIDTH     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_DATA_BUS_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Set to 1 when the uMCTL2 and DRAM has to be put in DLL-off mode for low
 * frequency operation.
 * 
 * Set to 0 to put uMCTL2 and DRAM in DLL-on mode for normal frequency
 * operation.
 * 
 * If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable
 * = 1), dll_off_mode is not supported, and this bit must be set to '0'.
 * 
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . DLL_OFF_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_DLL_OFF_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_DLL_OFF_MODE  VTSS_BIT(15)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_DLL_OFF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * SDRAM burst length used:
 *  - 0001 - Burst length of 2 (only supported for mDDR)
 *  - 0010 - Burst length of 4
 *  - 0100 - Burst length of 8
 *  - 1000 - Burst length of 16 (only supported for mDDR, LPDDR2, and
 * LPDDR4)
 *  All other values are reserved.
 * This controls the burst size used to access the SDRAM. This must match
 * the burst length mode register setting in the SDRAM. (For BC4/8
 * on-the-fly mode of DDR3 and DDR4, set this field to 0x0100) Burst length
 * of 2 is not supported with AXI ports when MEMC_BURST_LENGTH is 8.
 * 
 *  Burst length of 2 is only supported when the controller is operating in
 * 1:1 frequency mode. 
 * 
 *  For DDR3, DDR4 and LPDDR3, this must be set to 0x0100 (BL8). 
 * 
 *  For LPDDR4, this must be set to 0x1000 (BL16).
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . BURST_RDWR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_BURST_RDWR(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_BURST_RDWR     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_BURST_RDWR(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Only present for multi-rank configurations.
 * Each bit represents one rank. For two-rank configurations, only
 * bits[25:24] are present.
 *  - 1 - populated
 *  - 0 - unpopulated
 * LSB is the lowest rank number.
 * 
 * For 2 ranks following combinations are legal:
 *  - 01 - One rank
 *  - 11 - Two ranks
 *  - Others - Reserved.
 * For 4 ranks following combinations are legal:
 *  - 0001 - One rank
 *  - 0011 - Two ranks
 *  - 0111 - Three ranks
 *  - 1111 - Four ranks
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . ACTIVE_RANKS
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_ACTIVE_RANKS(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_ACTIVE_RANKS     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_ACTIVE_RANKS(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Indicates the configuration of the device used in the system.
 *  - 00 - x4 device
 *  - 01 - x8 device
 *  - 10 - x16 device
 *  - 11 - x32 device
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MSTR . DEVICE_CONFIG
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MSTR_DEVICE_CONFIG(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MSTR_DEVICE_CONFIG     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MSTR_DEVICE_CONFIG(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/** 
 * \brief Operating Mode Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:STAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_STAT     VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1)

/** 
 * \brief
 * Operating mode. This is 3-bits wide in configurations with
 * mDDR/LPDDR2/LPDDR3/LPDDR4/DDR4 support and 2-bits in all other
 * configurations.
 * non-mDDR/LPDDR2/LPDDR3/LPDDR4 and non-DDR4 designs:
 *  - 00 - Init
 *  - 01 - Normal
 *  - 10 - Power-down
 *  - 11 - Self refresh
 * mDDR/LPDDR2/LPDDR3 or DDR4 designs:
 *  - 000 - Init
 *  - 001 - Normal
 *  - 010 - Power-down
 *  - 011 - Self refresh
 *  - 1XX - Deep power-down / Maximum Power Saving Mode
 * LPDDR4 designs:
 *  - 000 - Init
 *  - 001 - Normal
 *  - 010 - Power-down
 *  - 011 - Self refresh / Self refresh power-down
 * 
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_STAT . OPERATING_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_STAT_OPERATING_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_STAT_OPERATING_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_STAT_OPERATING_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Flags if Self Refresh (except LPDDR4) or SR-Powerdown (LPDDR4) is
 * entered and if it was under Automatic Self Refresh control only or not. 
 *   
 *  - 00 - SDRAM is not in Self Refresh (except LPDDR4) or SR-Powerdown
 * (LPDDR4). If retry is enabled by CRCPARCTRL1.crc_parity_retry_enable,
 * this also indicates SRE command is still in parity error window or retry
 * is in-progress.
 *  - 11 - SDRAM is in Self Refresh (except LPDDR4) or SR-Powerdown
 * (LPDDR4), which was caused by Automatic Self Refresh only. If retry is
 * enabled, this guarantees SRE command is executed correctly without
 * parity error.
 *  - 10 - SDRAM is in Self Refresh (except LPDDR4) or SR-Powerdown
 * (LPDDR4), which was not caused solely under Automatic Self Refresh
 * control. It could have been caused by Hardware Low Power Interface
 * and/or Software (PWRCTL.selfref_sw). If retry is enabled, this
 * guarantees SRE command is executed correctly without parity error.
 *  - 01 - SDRAM is in Self Refresh, which was caused by PHY Master
 * Request.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_STAT . SELFREF_TYPE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_STAT_SELFREF_TYPE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_STAT_SELFREF_TYPE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_STAT_SELFREF_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Self refresh with CAMs not empty. Set to 1 when Self Refresh is entered
 * but CAMs are not drained. Cleared after exiting Self Refresh.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_STAT . SELFREF_CAM_NOT_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_STAT_SELFREF_CAM_NOT_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_STAT_SELFREF_CAM_NOT_EMPTY  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_STAT_SELFREF_CAM_NOT_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief Mode Register Read/Write Control Register 0.

Note: Do not enable more than one of the following fields simultaneously:

- sw_init_int

- pda_en

- mpr_en
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRCTRL0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4)

/** 
 * \brief
 * Indicates whether the mode register operation is read or write. Only
 * used for LPDDR2/LPDDR3/LPDDR4/DDR4.
 *  - 0 - Write
 *  - 1 - Read
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . MR_TYPE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_TYPE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Indicates whether the mode register operation is MRS or WR/RD for MPR
 * (only supported for DDR4)
 *  - 0 - MRS
 *  - 1 - WR/RD for MPR
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . MPR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MPR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MPR_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MPR_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Indicates whether the mode register operation is MRS in PDA mode or not
 *  - 0 - MRS
 *  - 1 - MRS in Per DRAM Addressability mode
 * Note that when pba_mode=1, PBA access is initiated instead of PDA
 * access.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . PDA_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_PDA_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_PDA_EN  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_PDA_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Indicates whether Software intervention is allowed via MRCTRL0/MRCTRL1
 * before automatic SDRAM initialization routine or not.
 * For DDR4, this bit can be used to initialize the DDR4 RCD (MR7) before
 * automatic SDRAM initialization.
 * For LPDDR4, this bit can be used to program additional mode registers
 * before automatic SDRAM initialization if necessary.
 * In LPDDR4 dual channel mode, note that this must be programmed to both
 * channels beforehand.
 * Note that this must be cleared to 0 after completing Software operation.
 * Otherwise, SDRAM initialization routine will not re-start.
 *  - 0 - Software intervention is not allowed
 *  - 1 - Software intervention is allowed
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . SW_INIT_INT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_SW_INIT_INT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_SW_INIT_INT  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_SW_INIT_INT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Controls which rank is accessed by MRCTRL0.mr_wr. Normally, it is
 * desired to access all ranks, so all bits should be set to 1. However,
 * for multi-rank UDIMMs/RDIMMs/LRDIMMs which implement address mirroring,
 * it may be necessary to access ranks individually.
 * Examples (assume uMCTL2 is configured for 4 ranks):
 *     - 0x1 - select rank 0 only
 *     - 0x2 - select rank 1 only
 *     - 0x5 - select ranks 0 and 2
 *     - 0xA - select ranks 1 and 3
 *     - 0xF - select ranks 0, 1, 2 and 3
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . MR_RANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_RANK(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_RANK     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_RANK(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Address of the mode register that is to be written to.
 *  - 0000 - MR0
 *  - 0001 - MR1
 *  - 0010 - MR2
 *  - 0011 - MR3
 *  - 0100 - MR4
 *  - 0101 - MR5
 *  - 0110 - MR6
 *  - 0111 - MR7
 * Don't Care for LPDDR2/LPDDR3/LPDDR4 (see MRCTRL1.mr_data for mode
 * register addressing in LPDDR2/LPDDR3/LPDDR4)
 * 
 * This signal is also used for writing to control words of the register
 * chip on RDIMMs/LRDIMMs. In that case, it corresponds to the bank address
 * bits sent to the RDIMM/LRDIMM
 * 
 * In case of DDR4, the bit[3:2] corresponds to the bank group bits.
 * Therefore, the bit[3] as well as the bit[2:0] must be set to an
 * appropriate value which is considered both the Address Mirroring of
 * UDIMMs/RDIMMs/LRDIMMs and the Output Inversion of RDIMMs/LRDIMMs.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . MR_ADDR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_ADDR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_ADDR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Indicates whether PBA access is executed. When setting this bit to 1
 * along with setting pda_en to 1, uMCTL2 initiates PBA access instead of
 * PDA access.
 *  - 0 - Per DRAM Addressability mode
 *  - 1 - Per Buffer Addressability mode
 * The completion of PBA access is confirmed by MRSTAT.pda_done in the same
 * way as PDA.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . PBA_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_PBA_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_PBA_MODE  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_PBA_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Setting this register bit to 1 triggers a mode register read or write
 * operation. When the MR operation is complete, the uMCTL2 automatically
 * clears this bit. The other register fields of this register must be
 * written in a separate APB transaction, before setting this mr_wr bit. It
 * is recommended NOT to set this signal if in Init, Deep power-down or
 * MPSM operating modes.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0 . MR_WR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_WR(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_WR  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL0_MR_WR(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/** 
 * \brief Mode Register Read/Write Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRCTRL1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x5)

/** 
 * \brief
 * Mode register write data for all non-LPDDR2/non-LPDDR3/non-LPDDR4 modes.
 * For LPDDR2/LPDDR3/LPDDR4, MRCTRL1[15:0] are interpreted as
 * [15:8] MR Address
 * [7:0] MR data for writes, don't care for reads. This is 18-bits wide in
 * configurations with DDR4 support and 16-bits in all other
 * configurations.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL1 . MR_DATA
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL1_MR_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL1_MR_DATA     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL1_MR_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/** 
 * \brief Mode Register Read/Write Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_MRSTAT   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6)

/** 
 * \brief
 * The SoC core may initiate a MR write operation only if this signal is
 * low. This signal goes high in the clock after the uMCTL2 accepts the
 * MRW/MRR request. It goes low when the MRW/MRR command is issued to the
 * SDRAM. It is recommended not to perform MRW/MRR commands when
 * 'MRSTAT.mr_wr_busy' is high.
 *  - 0 - Indicates that the SoC core can initiate a mode register write
 * operation
 *  - 1 - Indicates that mode register write operation is in progress
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRSTAT . MR_WR_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRSTAT_MR_WR_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRSTAT_MR_WR_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRSTAT_MR_WR_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * The SoC core may initiate a MR write operation in PDA/PBA mode only if
 * this signal is low. This signal goes high when three consecutive MRS
 * commands related to the PDA/PBA mode are issued to the SDRAM. This
 * signal goes low when MRCTRL0.pda_en becomes 0. Therefore, it is
 * recommended to write MRCTRL0.pda_en to 0 after this signal goes high in
 * order to prepare to perform PDA operation next time.
 *  - 0 - Indicates that mode register write operation related to PDA/PBA
 * is in progress or has not started yet.
 *  - 1 - Indicates that mode register write operation related to PDA/PBA
 * has competed.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRSTAT . PDA_DONE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRSTAT_PDA_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRSTAT_PDA_DONE  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRSTAT_PDA_DONE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/** 
 * \brief Mode Register Read/Write Control Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:MRCTRL2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x7)

/** 
 * \brief
 * Indicates the device(s) to be selected during the MRS that happens in
 * PDA mode. Each bit is associated with one device. For example, bit[0]
 * corresponds to Device 0, bit[1] to Device 1 etc.
 * A '1' should be programmed to indicate that the MRS command should be
 * applied to that device.
 *  A '0' indicates that the MRS commands should be skipped for that
 * device.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_MRCTRL2 . MR_DEVICE_SEL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_MRCTRL2_MR_DEVICE_SEL(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_MRCTRL2_MR_DEVICE_SEL     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_MRCTRL2_MR_DEVICE_SEL(x)  (x)


/** 
 * \brief Temperature Derate Enable Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DERATEEN
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DERATEEN  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x8)

/** 
 * \brief
 * Enables derating
 *  - 0 - Timing parameter derating is disabled
 *  - 1 - Timing parameter derating is enabled using MR4 read value.
 * Present only in designs configured to support LPDDR2/LPDDR3/LPDDR4
 * 
 * This field must be set to '0' for non-LPDDR2/LPDDR3/LPDDR4 mode.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DERATEEN . DERATE_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_ENABLE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Derate value
 *  - 0 - Derating uses +1.
 *  - 1 - Derating uses +2.
 * Present only in designs configured to support LPDDR2/LPDDR3/LPDDR4
 * 
 * Set to 0 for all LPDDR2 speed grades as derating value of +1.875 ns is
 * less than a core_ddrc_core_clk period.
 * For LPDDR3/4, if the period of core_ddrc_core_clk is less than 1.875ns,
 * this register field should be set to 1; otherwise it should be set to 0.
 * 
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DERATEEN . DERATE_VALUE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_VALUE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_VALUE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Derate byte
 * Present only in designs configured to support LPDDR2/LPDDR3/LPDDR4
 * 
 * Indicates which byte of the MRR data is used for derating. The maximum
 * valid value depends
 * on MEMC_DRAM_TOTAL_DATA_WIDTH.
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DERATEEN . DERATE_BYTE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_BYTE(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_BYTE     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DERATEEN_DERATE_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief Temperature Derate Interval Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DERATEINT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DERATEINT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x9)

/** 
 * \brief
 * Interval between two MR4 reads, used to derate the timing parameters.
 * Present only in designs configured to support LPDDR2/LPDDR3/LPDDR4. This
 * register must not be set to zero.
 * Unit: DFI clock cycle.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DERATEINT . MR4_READ_INTERVAL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DERATEINT_MR4_READ_INTERVAL(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DERATEINT_MR4_READ_INTERVAL     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DERATEINT_MR4_READ_INTERVAL(x)  (x)


/** 
 * \brief Low Power Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PWRCTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc)

/** 
 * \brief
 * If true then the uMCTL2 puts the SDRAM into Self Refresh after a
 * programmable number of cycles "maximum idle clocks before Self Refresh
 * (PWRTMG.selfref_to_x32)". This register bit may be re-programmed during
 * the course of normal operation.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . SELFREF_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_SELFREF_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_SELFREF_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_SELFREF_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * If true then the uMCTL2 goes into power-down after a programmable number
 * of cycles "maximum idle clocks before power down"
 * (PWRTMG.powerdown_to_x32).
 * This register bit may be re-programmed during the course of normal
 * operation.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . POWERDOWN_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_POWERDOWN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_POWERDOWN_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_POWERDOWN_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When this is 1, uMCTL2 puts the SDRAM into deep power-down mode when the
 * transaction store is empty.
 * This register must be reset to '0' to bring uMCTL2 out of deep
 * power-down mode. Controller performs automatic SDRAM initialization on
 * deep power-down exit.
 * Present only in designs configured to support mDDR or LPDDR2 or LPDDR3.
 * For non-mDDR/non-LPDDR2/non-LPDDR3, this register should not be set to
 * 1.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . DEEPPOWERDOWN_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_DEEPPOWERDOWN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_DEEPPOWERDOWN_EN  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_DEEPPOWERDOWN_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable the assertion of dfi_dram_clk_disable whenever a clock is not
 * required by the SDRAM.
 * 
 * If set to 0, dfi_dram_clk_disable is never asserted.
 * 
 * Assertion of dfi_dram_clk_disable is as follows:
 * 
 * In DDR2/DDR3, can only be asserted in Self Refresh.
 * 
 * In DDR4, can be asserted in following:
 *   - in Self Refresh.
 *   - in Maximum Power Saving Mode
 * In mDDR/LPDDR2/LPDDR3, can be asserted in following:
 *   - in Self Refresh
 *   - in Power Down
 *   - in Deep Power Down
 *   - during Normal operation (Clock Stop)
 * In LPDDR4, can be asserted in following:
 *   - in Self Refresh Power Down
 *   - in Power Down
 *   - during Normal operation (Clock Stop)
 * 
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . EN_DFI_DRAM_CLK_DISABLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_EN_DFI_DRAM_CLK_DISABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_EN_DFI_DRAM_CLK_DISABLE  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_EN_DFI_DRAM_CLK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * When this is 1, the uMCTL2 puts the SDRAM into maximum power saving mode
 * when the transaction store is empty.
 * This register must be reset to '0' to bring uMCTL2 out of maximum power
 * saving mode.
 * Present only in designs configured to support DDR4. For non-DDR4, this
 * register should not be set to 1.
 * Note that MPSM is not supported when using a Synopsys DWC DDR PHY, if
 * the PHY parameter DWC_AC_CS_USE is disabled, as the MPSM exit sequence
 * requires the chip-select signal to toggle.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . MPSM_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_MPSM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_MPSM_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_MPSM_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * A value of 1 to this register causes system to move to Self Refresh
 * state immediately, as long as it is not in INIT or DPD/MPSM
 * operating_mode. This is referred to as Software Entry/Exit to Self
 * Refresh.
 *   - 1 - Software Entry to Self Refresh
 *   - 0 - Software Exit from Self Refresh
 * 
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . SELFREF_SW
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_SELFREF_SW(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_SELFREF_SW  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_SELFREF_SW(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Indicates whether skipping CAM draining is allowed when entering
 * Self-Refresh.
 * This register field cannot be modified while PWRCTL.selfref_sw==1.
 *   - 0 - CAMs must be empty before entering SR
 *   - 1 - CAMs are not emptied before entering SR
 * 
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRCTL . DIS_CAM_DRAIN_SELFREF
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_DIS_CAM_DRAIN_SELFREF(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_DIS_CAM_DRAIN_SELFREF  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRCTL_DIS_CAM_DRAIN_SELFREF(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief Low Power Timing Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PWRTMG
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRTMG   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xd)

/** 
 * \brief
 * After this many clocks of the DDRC command channel being idle the uMCTL2
 * automatically puts the SDRAM into power-down. The DDRC command channel
 * is considered idle when there are no HIF commands outstanding. This must
 * be enabled in the PWRCTL.powerdown_en.
 * Unit: Multiples of 32 DFI clocks
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRTMG . POWERDOWN_TO_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_POWERDOWN_TO_X32(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_POWERDOWN_TO_X32     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_POWERDOWN_TO_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * Minimum deep power-down time.
 * For mDDR, value from the JEDEC specification is 0 as mDDR exits from
 * deep power-down mode immediately after PWRCTL.deeppowerdown_en is
 * de-asserted.
 * For LPDDR2/LPDDR3, value from the JEDEC specification is 500us.
 * Unit: Multiples of 4096 DFI clocks.
 * Present only in designs configured to support mDDR, LPDDR2 or LPDDR3.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRTMG . T_DPD_X4096
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_T_DPD_X4096(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_T_DPD_X4096     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_T_DPD_X4096(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * After this many clocks of the DDRC command channel being idle the uMCTL2
 * automatically puts the SDRAM into Self Refresh. The DDRC command channel
 * is considered idle when there are no HIF commands outstanding. This must
 * be enabled in the PWRCTL.selfref_en.
 * Unit: Multiples of 32 DFI clocks.
 * FOR PERFORMANCE ONLY.
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PWRTMG . SELFREF_TO_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_SELFREF_TO_X32(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_SELFREF_TO_X32     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PWRTMG_SELFREF_TO_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


/** 
 * \brief Hardware Low Power Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:HWLPCTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xe)

/** 
 * \brief
 * Enable for Hardware Low Power Interface.
 * 
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL . HW_LP_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When this bit is programmed to 1 the cactive_in_ddrc pin of the DDRC can
 * be used to exit from the automatic clock stop, automatic power down or
 * automatic self-refresh modes. Note, it will not cause exit of
 * Self-Refresh that was caused by Hardware Low Power Interface and/or
 * Software (PWRCTL.selfref_sw).
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL . HW_LP_EXIT_IDLE_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_EXIT_IDLE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_EXIT_IDLE_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_EXIT_IDLE_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Hardware idle period. The cactive_ddrc output is driven low if the DDRC
 * command channel is idle for hw_lp_idle * 32 cycles if not in INIT or
 * DPD/MPSM operating_mode. The DDRC command channel is considered idle
 * when there are no HIF commands outstanding. The hardware idle function
 * is disabled when hw_lp_idle_x32=0.
 * Unit: Multiples of 32 DFI clocks.
 * FOR PERFORMANCE ONLY.
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL . HW_LP_IDLE_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_IDLE_X32(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_IDLE_X32     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_HWLPCTL_HW_LP_IDLE_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/** 
 * \brief Refresh Control Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHCTL0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x14)

/** 
 * \brief
 * 
 *  - 1 - Per bank refresh;
 *  - 0 - All bank refresh.
 * Per bank refresh allows traffic to flow to other banks. Per bank refresh
 * is not supported by all LPDDR2 devices but should be supported by all
 * LPDDR3/LPDDR4 devices. Present only in designs configured to support
 * LPDDR2/LPDDR3/LPDDR4
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0 . PER_BANK_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_PER_BANK_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_PER_BANK_REFRESH  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_PER_BANK_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The programmed value + 1 is the number of refresh timeouts that is
 * allowed to accumulate before traffic is blocked and the refreshes are
 * forced to execute. Closing pages to perform a refresh is a one-time
 * penalty that must be paid for each group of refreshes. Therefore,
 * performing refreshes in a burst reduces the per-refresh penalty of these
 * page closings. Higher numbers for RFSHCTL.refresh_burst slightly
 * increases utilization; lower numbers decreases the worst-case latency
 * associated with refreshes.
 *  - 0 - single refresh
 *  - 1 - burst-of-2 refresh
 *  - 7 - burst-of-8 refresh
 * For information on burst refresh feature refer to section 3.9 of DDR2
 * JEDEC specification - JESD79-2F.pdf.
 * For DDR2/3, the refresh is always per-rank and not per-bank. The rank
 * refresh can be accumulated over 8*tREFI cycles using the burst refresh
 * feature.
 * In DDR4 mode, according to Fine Granularity feature, 8 refreshes can be
 * postponed in 1X mode, 16 refreshes in 2X mode and 32 refreshes in 4X
 * mode. If using PHY-initiated updates, care must be taken in the setting
 * of RFSHCTL0.refresh_burst, to ensure that tRFCmax is not violated due to
 * a PHY-initiated update occurring shortly before a refresh burst was due.
 * In this situation, the refresh burst will be delayed until the
 * PHY-initiated update is complete.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0 . REFRESH_BURST
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_BURST(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_BURST     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_BURST(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * If the refresh timer (tRFCnom, also known as tREFI) has expired at least
 * once, but it has not expired (RFSHCTL0.refresh_burst+1) times yet, then
 * a speculative refresh may be performed. A speculative refresh is a
 * refresh performed at a time when refresh would be useful, but before it
 * is absolutely required. When the SDRAM bus is idle for a period of time
 * determined by this RFSHCTL0.refresh_to_x32 and the refresh timer has
 * expired at least once since the last refresh, then a speculative refresh
 * is performed. Speculative refreshes continues successively until there
 * are no refreshes pending or until new reads or writes are issued to the
 * uMCTL2.
 * FOR PERFORMANCE ONLY. 
 * Unit: Multiples of 32 DFI clocks.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0 . REFRESH_TO_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_TO_X32(x)  VTSS_ENCODE_BITFIELD(x,12,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_TO_X32     VTSS_ENCODE_BITMASK(12,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_TO_X32(x)  VTSS_EXTRACT_BITFIELD(x,12,5)

/** 
 * \brief
 * Threshold value in number of DFI clock cycles before the critical
 * refresh or page timer expires. A critical refresh is to be issued before
 * this threshold is reached. It is recommended that this not be changed
 * from the default value, currently shown as 0x2. It must always be less
 * than internally used t_rfc_nom_x32. Note that, in LPDDR2/LPDDR3/LPDDR4,
 * internally used t_rfc_nom_x32 may be equal to RFSHTMG.t_rfc_nom_x32>>2
 * if derating is enabled (DERATEEN.derate_enable=1). Otherwise, internally
 * used t_rfc_nom_x32 will be equal to RFSHTMG.t_rfc_nom_x32. 
 * Unit: Multiples of 32 DFI clocks.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0 . REFRESH_MARGIN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_MARGIN(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_MARGIN     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL0_REFRESH_MARGIN(x)  VTSS_EXTRACT_BITFIELD(x,20,4)


/** 
 * \brief Refresh Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHCTL1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x15)

/** 
 * \brief
 * Refresh timer start for rank 0 (only present in multi-rank
 * configurations). This is useful in staggering the refreshes to multiple
 * ranks to help traffic to proceed. This is explained in Refresh Controls
 * section of architecture chapter.
 * Unit: Multiples of 32 DFI clock cycles.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1 . REFRESH_TIMER0_START_VALUE_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Refresh timer start for rank 1 (only present in multi-rank
 * configurations). This is useful in staggering the refreshes to multiple
 * ranks to help traffic to proceed. This is explained in Refresh Controls
 * section of architecture chapter.
 * Unit: Multiples of 32 DFI clock cycles.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1 . REFRESH_TIMER1_START_VALUE_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/** 
 * \brief Refresh Control Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHCTL3
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x18)

/** 
 * \brief
 * When '1', disable auto-refresh generated by the uMCTL2. When
 * auto-refresh is disabled, the SoC core must generate refreshes using the
 * registers DBGCMD.rankn_refresh.
 * When dis_auto_refresh transitions from 0 to 1, any pending refreshes are
 * immediately scheduled by the uMCTL2.
 * If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable
 * = 1), disable auto-refresh is not supported, and this bit must be set to
 * '0'.
 * (DDR4 only) If FGR mode is enabled (RFSHCTL3.refresh_mode > 0), disable
 * auto-refresh is not supported, and this bit must be set to '0'.
 * This register field is changeable on the fly.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3 . DIS_AUTO_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_DIS_AUTO_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_DIS_AUTO_REFRESH  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_DIS_AUTO_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Toggle this signal (either from 0 to 1 or from 1 to 0) to indicate that
 * the refresh register(s) have been updated.
 * refresh_update_level must not be toggled when the DDRC is in reset
 * (core_ddrc_rstn = 0).
 * The refresh register(s) are automatically updated when exiting reset.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3 . REFRESH_UPDATE_LEVEL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_REFRESH_UPDATE_LEVEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_REFRESH_UPDATE_LEVEL  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_REFRESH_UPDATE_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Fine Granularity Refresh Mode
 *   - 000 - Fixed 1x (Normal mode)
 *   - 001 - Fixed 2x
 *   - 010 - Fixed 4x
 *   - 101 - Enable on the fly 2x (not supported)
 *   - 110 - Enable on the fly 4x (not supported)
 *   - Everything else - reserved
 * Note: Only Fixed 1x mode is supported if RFSHCTL3.dis_auto_refresh = 1.
 * Note: The on-the-fly modes are not supported in this version of the
 * uMCTL2.
 * Note: This must be set up while the Controller is in reset or while the
 * Controller is in self-refresh mode. Changing this during normal
 * operation is not allowed. Making this a dynamic register will be
 * supported in future version of the uMCTL2.
 * Note: This register field has effect only if a DDR4 SDRAM device is in
 * use (MSTR.ddr4 = 1).
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3 . REFRESH_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_REFRESH_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_REFRESH_MODE     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHCTL3_REFRESH_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief Refresh Timing Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RFSHTMG
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x19)

/** 
 * \brief
 * tRFC (min): Minimum time from refresh to refresh or activate.
 * 
 * When the controller is operating in 1:1 mode, t_rfc_min should be set to
 * RoundUp(tRFCmin/tCK).
 * 
 * When the controller is operating in 1:2 mode, t_rfc_min should be set to
 * RoundUp(RoundUp(tRFCmin/tCK)/2).
 * 
 * In LPDDR2/LPDDR3/LPDDR4 mode:
 *   - if using all-bank refreshes, the tRFCmin value in the above
 * equations is equal to tRFCab
 *   - if using per-bank refreshes, the tRFCmin value in the above
 * equations is equal to tRFCpb
 * In DDR4 mode, the tRFCmin value in the above equations is different
 * depending on the refresh mode (fixed 1X,2X,4X) and the device density.
 * The user should program the appropriate value from the spec based on the
 * 'refresh_mode' and the device density that is used.
 * 
 * Unit: Clocks.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG . T_RFC_MIN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_T_RFC_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_T_RFC_MIN     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_T_RFC_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * Used only when LPDDR3 memory type is connected. Should only be changed
 * when uMCTL2 is in reset. Specifies whether to use the tREFBW parameter
 * (required by some LPDDR3 devices which comply with earlier versions of
 * the LPDDR3 JEDEC specification) or not:
 *    - 0 - tREFBW parameter not used
 *    - 1 - tREFBW parameter used
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG . LPDDR3_TREFBW_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_LPDDR3_TREFBW_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_LPDDR3_TREFBW_EN  VTSS_BIT(15)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_LPDDR3_TREFBW_EN(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * tREFI: Average time interval between refreshes per rank (Specification:
 * 7.8us for DDR2, DDR3 and DDR4. See JEDEC specification for mDDR, LPDDR2,
 * LPDDR3 and LPDDR4).
 * For LPDDR2/LPDDR3/LPDDR4:
 *   - if using all-bank refreshes (RFSHCTL0.per_bank_refresh = 0), this
 * register should be set to tREFIab
 *   - if using per-bank refreshes (RFSHCTL0.per_bank_refresh = 1), this
 * register should be set to tREFIpb
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tREFI/2), no rounding up.
 * 
 * In DDR4 mode, tREFI value is different depending on the refresh mode.
 * The user should program the appropriate value from the spec based on the
 * value programmed in the refresh mode register.
 * Note that RFSHTMG.t_rfc_nom_x32 * 32 must be greater than
 * RFSHTMG.t_rfc_min, and RFSHTMG.t_rfc_nom_x32 must be greater than 0x1.
 * 
 *   - Non-DDR4 or DDR4 Fixed 1x mode: RFSHTMG.t_rfc_nom_x32 must be less
 * than or equal to 0xFFE.
 *   - DDR4 Fixed 2x mode: RFSHTMG.t_rfc_nom_x32 must be less than or equal
 * to 0x7FF.
 *   - DDR4 Fixed 4x mode: RFSHTMG.t_rfc_nom_x32 must be less than or equal
 * to 0x3FF.
 * Unit: Multiples of 32 clocks.
 * Programming Mode: Dynamic - Refresh Related
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG . T_RFC_NOM_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_T_RFC_NOM_X32(x)  VTSS_ENCODE_BITFIELD(x,16,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_T_RFC_NOM_X32     VTSS_ENCODE_BITMASK(16,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RFSHTMG_T_RFC_NOM_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,12)


/** 
 * \brief ECC Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCFG0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1c)

/** 
 * \brief
 * ECC mode indicator
 *  - 000 - ECC disabled
 *  - 100 - ECC enabled - SEC/DED over 1 beat
 *  - 101 - ECC enabled - Advanced ECC
 *  - all other settings are reserved for future use
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0 . ECC_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0_ECC_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0_ECC_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0_ECC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Disable ECC scrubs. Valid only when ECCCFG0.ecc_mode = 3'b100 or 3'b101
 * and MEMC_USE_RMW is defined.
 * 
 *	Note: Scrub is not supported in inline ECC mode and the register
 * value is don't care.
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0 . DIS_SCRUB
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0_DIS_SCRUB(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0_DIS_SCRUB  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCFG0_DIS_SCRUB(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief ECC Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCFG1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1d)

/** 
 * \brief
 * Enable ECC data poisoning - introduces ECC errors on writes to address
 * specified by the ECCPOISONADDR0/1 registers
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1 . DATA_POISON_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1_DATA_POISON_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1_DATA_POISON_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1_DATA_POISON_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Selects whether to poison 1 or 2 bits - if 0 -> 2-bit (uncorrectable)
 * data poisoning, if 1 -> 1-bit (correctable) data poisoning, if
 * ECCCFG1.data_poison_en=1.
 * Valid only when MEMC_ECC_SUPPORT==1 (SECDED ECC mode)
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1 . DATA_POISON_BIT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1_DATA_POISON_BIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1_DATA_POISON_BIT  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCFG1_DATA_POISON_BIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief SECDED ECC Status Register (Valid only in MEMC_ECC_SUPPORT==1 (SECDED ECC mode))
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1e)

/** 
 * \brief
 * Bit number corrected by single-bit ECC error. See ECC section of
 * architecture chapter for encoding of this field. If more than one data
 * lane has an error, the lower data lane is selected. This register is 7
 * bits wide in order to handle 72 bits of the data present in a single
 * lane.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT . ECC_CORRECTED_BIT_NUM
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_CORRECTED_BIT_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_CORRECTED_BIT_NUM     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_CORRECTED_BIT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/** 
 * \brief
 * Single-bit error indicators.
 * 
 *	In sideband ECC mode, 1 bit per ECC lane. When the controller is
 * operating in 1:1 frequency ratio mode, there are only two lanes, so only
 * the lower two bits are used.
 * 
 *	In inline ECC mode, the register always is 1 bit to indicate
 * correctable error on any lane.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT . ECC_CORRECTED_ERR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_CORRECTED_ERR(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_CORRECTED_ERR     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_CORRECTED_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Double-bit error indicators.
 * 
 *	In sideband ECC mode, 1 bit per ECC lane. When the controller is
 * operating in 1:1 frequency ratio mode, there are only two lanes, so only
 * the lower two bits are used.
 * 
 *	In inline ECC mode, the register always is 1 bit to indicate
 * uncorrectable error on any lane.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT . ECC_UNCORRECTED_ERR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_UNCORRECTED_ERR(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_UNCORRECTED_ERR     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCSTAT_ECC_UNCORRECTED_ERR(x)  VTSS_EXTRACT_BITFIELD(x,16,4)


/** 
 * \brief ECC Clear Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCLR
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCLR   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x1f)

/** 
 * \brief
 * Setting this register bit to 1 clears the currently stored corrected ECC
 * error. The ECCSTAT.ecc_corrected_err, ECCSTAT.ecc_corrected_bit_num,
 * ADVECCSTAT.advecc_corrected_err, ADVECCSTAT.advecc_num_err_symbol,
 * ADVECCSTAT.advecc_err_symbol_pos, ADVECCSTAT.advecc_err_symbol_bits,
 * ECCCADDR0, ECCCADDR1, ECCCSYN0, ECCCSYN1, ECCCSYN2, ECCBITMASK0,
 * ECCBITMASK1 and ECCBITMASK2 registers are cleared by this operation.
 * When the clear operation is complete, the uMCTL2 automatically clears
 * this bit.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCLR . ECC_CLR_CORR_ERR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_CORR_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_CORR_ERR  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_CORR_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Setting this register bit to 1 clears the currently stored uncorrected
 * ECC error. The ECCSTAT.ecc_uncorrected_err,
 * ADVECCSTAT.advecc_uncorrected_err, ECCUADDR0, ECCUADDR1, ECCUSYN0,
 * ECCUSYN1 and ECCUSYN2 registers are cleared by this operation. When the
 * clear operation is complete, the uMCTL2 automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCLR . ECC_CLR_UNCORR_ERR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_UNCORR_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_UNCORR_ERR  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_UNCORR_ERR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Setting this register bit to 1 clears the currently stored corrected ECC
 * error count. The ECCERRCNT.ecc_corr_err_cnt register is cleared by this
 * operation. When the clear operation is complete, the uMCTL2
 * automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCLR . ECC_CLR_CORR_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_CORR_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_CORR_ERR_CNT  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_CORR_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Setting this register bit to 1 clears the currently stored uncorrected
 * ECC error count. The ECCERRCNT.ecc_uncorr_err_cnt register is cleared by
 * this operation. When the clear operation is complete, the uMCTL2
 * automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCLR . ECC_CLR_UNCORR_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_UNCORR_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_UNCORR_ERR_CNT  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCLR_ECC_CLR_UNCORR_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief ECC Error Counter Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCERRCNT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x20)

/** 
 * \brief
 * Number of correctable ECC errors detected.
 * Note that the saturation behavior of this register is different,
 * depending on whether SECDED ECC or advanced ECC is enabled.	For
 * advanced ECC, it saturates at 0xFFFF, while for SECDED ECC, it saturates
 * at 0xFFFC or above.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT . ECC_CORR_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT_ECC_CORR_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT_ECC_CORR_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT_ECC_CORR_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Number of uncorrectable ECC errors detected.
 * Note that the saturation behavior of this register is different,
 * depending on whether SECDED ECC or advanced ECC is enabled.	For
 * advanced ECC, it saturates at 0xFFFF, while for SECDED ECC, it saturates
 * at 0xFFFC or above.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT . ECC_UNCORR_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT_ECC_UNCORR_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT_ECC_UNCORR_ERR_CNT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCERRCNT_ECC_UNCORR_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief ECC Corrected Error Address Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCADDR0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x21)

/** 
 * \brief
 * Page/row number of a read resulting in a corrected ECC error. This is
 * 18-bits wide in configurations with DDR4 support and 16-bits in all
 * other configurations.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0 . ECC_CORR_ROW
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0_ECC_CORR_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0_ECC_CORR_ROW     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0_ECC_CORR_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/** 
 * \brief
 * Rank number of a read resulting in a corrected ECC error
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0 . ECC_CORR_RANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0_ECC_CORR_RANK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0_ECC_CORR_RANK  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR0_ECC_CORR_RANK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/** 
 * \brief ECC Corrected Error Address Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCADDR1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x22)

/** 
 * \brief
 * Block number of a read resulting in a corrected ECC error (lowest bit
 * not assigned here)
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1 . ECC_CORR_COL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_COL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_COL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Bank number of a read resulting in a corrected ECC error
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1 . ECC_CORR_BANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_BANK(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_BANK     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_BANK(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Bank Group number of a read resulting in a corrected ECC error
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1 . ECC_CORR_BG
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_BG(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_BG     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCADDR1_ECC_CORR_BG(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/** 
 * \brief ECC Corrected Syndrome Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCSYN0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x23)

/** 
 * \brief
 * Data pattern that resulted in a corrected error. For 16-bit ECC, only
 * bits [15:0] are used
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN0 . ECC_CORR_SYNDROMES_31_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN0_ECC_CORR_SYNDROMES_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN0_ECC_CORR_SYNDROMES_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN0_ECC_CORR_SYNDROMES_31_0(x)  (x)


/** 
 * \brief ECC Corrected Syndrome Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCCSYN2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x25)

/** 
 * \brief
 * Data pattern that resulted in a corrected error one for each ECC lane,
 * all concatenated together
 * This register refers to the ECC byte, which is bits [71:64] for 64-bit
 * ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN2 . ECC_CORR_SYNDROMES_71_64
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN2_ECC_CORR_SYNDROMES_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN2_ECC_CORR_SYNDROMES_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCCSYN2_ECC_CORR_SYNDROMES_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ECC Corrected Data Bit Mask Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCBITMASK0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x26)

/** 
 * \brief
 * Mask for the corrected data portion
 *     - 1 on any bit indicates that the bit has been corrected by the ECC
 * logic
 *     - 0 on any bit indicates that the bit has not been corrected by the
 * ECC logic
 * This register accumulates data over multiple ECC errors, to give an
 * overall indication of which bits are being fixed. It is cleared by
 * writing a 1 to ECCCLR.ecc_clr_corr_err.
 * For 16-bit ECC, only bits [15:0] are used
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK0 . ECC_CORR_BIT_MASK_31_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK0_ECC_CORR_BIT_MASK_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK0_ECC_CORR_BIT_MASK_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK0_ECC_CORR_BIT_MASK_31_0(x)  (x)


/** 
 * \brief ECC Corrected Data Bit Mask Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCBITMASK2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x28)

/** 
 * \brief
 * Mask for the corrected data portion
 *     - 1 on any bit indicates that the bit has been corrected by the ECC
 * logic
 *     - 0 on any bit indicates that the bit has not been corrected by the
 * ECC logic
 * This register accumulates data over multiple ECC errors, to give an
 * overall indication of which bits are being fixed. It is cleared by
 * writing a 1 to ECCCLR.ecc_clr_corr_err.
 * This register refers to the ECC byte, which is bits [71:64] for 64-bit
 * ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK2 . ECC_CORR_BIT_MASK_71_64
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK2_ECC_CORR_BIT_MASK_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK2_ECC_CORR_BIT_MASK_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCBITMASK2_ECC_CORR_BIT_MASK_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ECC Uncorrected Error Address Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUADDR0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x29)

/** 
 * \brief
 * Page/row number of a read resulting in an uncorrected ECC error. This is
 * 18-bits wide in configurations with DDR4 support and 16-bits in all
 * other configurations.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0 . ECC_UNCORR_ROW
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0_ECC_UNCORR_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0_ECC_UNCORR_ROW     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0_ECC_UNCORR_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/** 
 * \brief
 * Rank number of a read resulting in an uncorrected ECC error
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0 . ECC_UNCORR_RANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0_ECC_UNCORR_RANK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0_ECC_UNCORR_RANK  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR0_ECC_UNCORR_RANK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/** 
 * \brief ECC Uncorrected Error Address Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUADDR1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2a)

/** 
 * \brief
 * Block number of a read resulting in an uncorrected ECC error (lowest bit
 * not assigned here)
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1 . ECC_UNCORR_COL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_COL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_COL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Bank number of a read resulting in an uncorrected ECC error
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1 . ECC_UNCORR_BANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_BANK(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_BANK     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_BANK(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Bank Group number of a read resulting in an uncorrected ECC error
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1 . ECC_UNCORR_BG
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_BG(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_BG     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUADDR1_ECC_UNCORR_BG(x)  VTSS_EXTRACT_BITFIELD(x,24,2)


/** 
 * \brief ECC Uncorrected Syndrome Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUSYN0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2b)

/** 
 * \brief
 * Data pattern that resulted in an uncorrected error, one for each ECC
 * lane, all concatenated together. For 16-bit ECC, only bits [15:0] are
 * used
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN0 . ECC_UNCORR_SYNDROMES_31_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN0_ECC_UNCORR_SYNDROMES_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN0_ECC_UNCORR_SYNDROMES_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN0_ECC_UNCORR_SYNDROMES_31_0(x)  (x)


/** 
 * \brief ECC Uncorrected Syndrome Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCUSYN2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2d)

/** 
 * \brief
 * Data pattern that resulted in an uncorrected error one for each ECC
 * lane, all concatenated together.
 * This register refers to the ECC byte, which is bits [71:64] for 64-bit
 * ECC, [39:32] for 32-bit ECC, or [23:16] for 16-bit ECC
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN2 . ECC_UNCORR_SYNDROMES_71_64
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN2_ECC_UNCORR_SYNDROMES_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN2_ECC_UNCORR_SYNDROMES_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCUSYN2_ECC_UNCORR_SYNDROMES_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ECC Data Poisoning Address Register 0. If a HIF write data beat matches the address specified in this register, an ECC error will be introduced on that transaction (write/RMW), if ECCCFG1.data_poison_en=1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONADDR0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2e)

/** 
 * \brief
 * Column address for ECC poisoning. Note that this column address must be
 * burst aligned:
 * - In full bus width mode, ecc_poison_col[2:0] must be set to 0
 * - In half bus width mode, ecc_poison_col[3:0] must be set to 0
 * - In quarter bus width mode, ecc_poison_col[4:0] must be set to 0
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0 . ECC_POISON_COL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0_ECC_POISON_COL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0_ECC_POISON_COL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0_ECC_POISON_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Rank address for ECC poisoning
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0 . ECC_POISON_RANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0_ECC_POISON_RANK(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0_ECC_POISON_RANK  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR0_ECC_POISON_RANK(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/** 
 * \brief ECC Data Poisoning Address Register 1. If a HIF write data beat matches the address specified in this register, an ECC error will be introduced on that transaction (write/RMW), if ECCCFG1.data_poison_en=1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONADDR1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x2f)

/** 
 * \brief
 * Row address for ECC poisoning. This is 18-bits wide in configurations
 * with DDR4 support and 16-bits in all other configurations.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1 . ECC_POISON_ROW
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_ROW     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/** 
 * \brief
 * Bank address for ECC poisoning
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1 . ECC_POISON_BANK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_BANK(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_BANK     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_BANK(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Bank Group address for ECC poisoning
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1 . ECC_POISON_BG
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_BG(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_BG     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONADDR1_ECC_POISON_BG(x)  VTSS_EXTRACT_BITFIELD(x,28,2)


/** 
 * \brief CRC Parity Control Register0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:CRCPARCTL0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x30)

/** 
 * \brief
 * Interrupt enable bit for DFI alert error. If this bit is set, any
 * parity/CRC error detected on the dfi_alert_n input will result in an
 * interrupt being set on CRCPARSTAT.dfi_alert_err_int.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0 . DFI_ALERT_ERR_INT_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_INT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_INT_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_INT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Interrupt clear bit for DFI alert error. If this bit is set, the alert
 * error interrupt on CRCPARSTAT.dfi_alert_err_int will be cleared. When
 * the clear operation is complete, the uMCTL2 automatically clears this
 * bit.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0 . DFI_ALERT_ERR_INT_CLR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * DFI alert error count clear. Clear bit for DFI alert error counter.
 * Asserting this bit will clear the DFI alert error counter,
 * CRCPARSTAT.dfi_alert_err_cnt. When the clear operation is complete, the
 * uMCTL2 automatically clears this bit.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0 . DFI_ALERT_ERR_CNT_CLR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief CRC Parity Control Register1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:CRCPARCTL1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x31)

/** 
 * \brief
 * C/A Parity enable register
 * 
 *     - 1: Enable generation of C/A parity and detection of C/A parity
 * error
 * 
 *     - 0: Disable generation of C/A parity and disable detection of C/A
 * parity error
 * 
 *     If RCD's parity error detection or SDRAM's parity detection is
 * enabled, this register should be 1.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1 . PARITY_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_PARITY_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_PARITY_ENABLE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_PARITY_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * CRC enable Register
 * 
 *     - 1: Enable generation of CRC
 * 
 *     - 0: Disable generation of CRC
 * 
 * The setting of this register should match the CRC mode register setting
 * in the DRAM.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1 . CRC_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CRC_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CRC_ENABLE  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CRC_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * CRC Calculation setting register
 * 
 *     - 1: CRC includes DM signal
 * 
 *     - 0: CRC not includes DM signal
 * 
 * Present only in designs configured to support DDR4.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1 . CRC_INC_DM
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CRC_INC_DM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CRC_INC_DM  VTSS_BIT(7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CRC_INC_DM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * If DDR4-SDRAM's CA parity is enabled by INIT6.mr5[2:0]!=0 and this
 * register is set to 1, CA parity is automatically disabled before
 * Self-Refresh entry and enabled after Self-Refresh exit by issuing MR5.
 * 
 *     - 1: CA parity is disabled before Self-Refresh entry
 * 
 *     - 0: CA parity is not disabled before Self-Refresh entry
 * 
 * If Geardown is used by MSTR.geardown_mode=1, this register must be set
 * to 1.
 * 
 * If this register set to 0, DRAMTMG5.t_ckesr and DRAMTMG5.t_cksre must be
 * increased by PL(Parity latency)
 * 
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1 . CAPARITY_DISABLE_BEFORE_SR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CAPARITY_DISABLE_BEFORE_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CAPARITY_DISABLE_BEFORE_SR  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARCTL1_CAPARITY_DISABLE_BEFORE_SR(x)  VTSS_EXTRACT_BITFIELD(x,12,1)


/** 
 * \brief CRC Parity Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:CRCPARSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x33)

/** 
 * \brief
 * DFI alert error count.
 *   If a parity/CRC error is detected on dfi_alert_n, this counter be
 * incremented.  This is independent of the setting of
 * CRCPARCTL0.dfi_alert_err_int_en.  It will saturate at 0xFFFF, and can be
 * cleared by asserting CRCPARCTL0.dfi_alert_err_cnt_clr.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT . DFI_ALERT_ERR_CNT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT_DFI_ALERT_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT_DFI_ALERT_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT_DFI_ALERT_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * DFI alert error interrupt.
 *   If a parity/CRC error is detected on dfi_alert_n, and the interrupt is
 * enabled by CRCPARCTL0.dfi_alert_err_int_en, this interrupt bit will be
 * set.  It will remain set until cleared by
 * CRCPARCTL0.dfi_alert_err_int_clr
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT . DFI_ALERT_ERR_INT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT_DFI_ALERT_ERR_INT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT_DFI_ALERT_ERR_INT  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_CRCPARSTAT_DFI_ALERT_ERR_INT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/** 
 * \brief SDRAM Initialization Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT0    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x34)

/** 
 * \brief
 * Cycles to wait after reset before driving CKE high to start the SDRAM
 * initialization sequence.
 * Unit: 1024 DFI clock cycles.
 * DDR2 specifications typically require this to be programmed for a delay
 * of >= 200 us.
 * LPDDR2/LPDDR3: tINIT1 of 100 ns (min) 
 * LPDDR4: tINIT3 of 2 ms (min) 
 *  When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * For DDR3/DDR4 RDIMMs, this should include the time needed to satisfy
 * tSTAB
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT0 . PRE_CKE_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT0_PRE_CKE_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT0_PRE_CKE_X1024     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT0_PRE_CKE_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/** 
 * \brief
 * Cycles to wait after driving CKE high to start the SDRAM initialization
 * sequence.
 * Unit: 1024 DFI clock cycles.
 * DDR2 typically requires a 400 ns delay, requiring this value to be
 * programmed to 2 at all clock speeds.
 * LPDDR2/LPDDR3 typically requires this to be programmed for a delay of
 * 200 us.
 * LPDDR4 typically requires this to be programmed for a delay of 2 us.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT0 . POST_CKE_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT0_POST_CKE_X1024(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT0_POST_CKE_X1024     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT0_POST_CKE_X1024(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * If lower bit is enabled the SDRAM initialization routine is skipped. The
 * upper bit decides what state the controller starts up in when reset is
 * removed  
 *  - 00 - SDRAM Intialization routine is run after power-up
 *  - 01 - SDRAM Intialization routine is skipped after power-up.
 * Controller starts up in Normal Mode
 *  - 11 - SDRAM Intialization routine is skipped after power-up.
 * Controller starts up in Self-refresh Mode
 *  - 10 - SDRAM Intialization routine is run after power-up.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT0 . SKIP_DRAM_INIT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT0_SKIP_DRAM_INIT(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT0_SKIP_DRAM_INIT     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT0_SKIP_DRAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,30,2)


/** 
 * \brief SDRAM Initialization Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT1    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x35)

/** 
 * \brief
 * Wait period before driving the OCD complete command to SDRAM.
 * Unit: Counts of a global timer that pulses every 32 DFI clock cycles.
 * There is no known specific requirement for this; it may be set to zero.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT1 . PRE_OCD_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT1_PRE_OCD_X32(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT1_PRE_OCD_X32     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT1_PRE_OCD_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Number of cycles to assert SDRAM reset signal during init sequence.
 * This is only present for designs supporting DDR3, DDR4 or LPDDR4
 * devices. For use with a Synopsys DDR PHY, this should be set to a
 * minimum of 1.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: 1024 DFI clock cycles.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT1 . DRAM_RSTN_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT1_DRAM_RSTN_X1024(x)  VTSS_ENCODE_BITFIELD(x,16,9)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT1_DRAM_RSTN_X1024     VTSS_ENCODE_BITMASK(16,9)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT1_DRAM_RSTN_X1024(x)  VTSS_EXTRACT_BITFIELD(x,16,9)


/** 
 * \brief SDRAM Initialization Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT2    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x36)

/** 
 * \brief
 * Time to wait after the first CKE high, tINIT2. Present only in designs
 * configured to support LPDDR2/LPDDR3.
 * LPDDR2/LPDDR3 typically requires 5 x tCK delay.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: DFI clock cycles.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT2 . MIN_STABLE_CLOCK_X1
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT2_MIN_STABLE_CLOCK_X1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT2_MIN_STABLE_CLOCK_X1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT2_MIN_STABLE_CLOCK_X1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Idle time after the reset command, tINIT4. Present only in designs
 * configured to support LPDDR2.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: 32 DFI clock cycles.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT2 . IDLE_AFTER_RESET_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT2_IDLE_AFTER_RESET_X32(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT2_IDLE_AFTER_RESET_X32     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT2_IDLE_AFTER_RESET_X32(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief SDRAM Initialization Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT3
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT3    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x37)

/** 
 * \brief
 * DDR2: Value to write to EMR register. Bits 9:7 are for OCD and the
 * setting in this register is ignored. The uMCTL2 sets those bits
 * appropriately.
 * DDR3/DDR4: Value to write to MR1 register  Set bit 7 to 0.  If
 * PHY-evaluation mode training is enabled, this bit is set appropriately
 * by the uMCTL2 during write leveling.
 *  mDDR: Value to write to EMR register.
 * LPDDR2/LPDDR3/LPDDR4 - Value to write to MR2 register
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT3 . EMR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT3_EMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT3_EMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT3_EMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * DDR2: Value to write to MR register. Bit 8 is for DLL and the setting
 * here is ignored. The uMCTL2 sets this bit appropriately.
 * DDR3/DDR4: Value loaded into MR0 register.
 * mDDR: Value to write to MR register.
 * LPDDR2/LPDDR3/LPDDR4 - Value to write to MR1 register
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT3 . MR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT3_MR(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT3_MR     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT3_MR(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief SDRAM Initialization Register 4
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT4
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT4    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x38)

/** 
 * \brief
 * DDR2: Value to write to EMR3 register.
 * DDR3/DDR4: Value to write to MR3 register
 * mDDR/LPDDR2/LPDDR3: Unused
 * LPDDR4: Value to write to MR13 register
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT4 . EMR3
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT4_EMR3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT4_EMR3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT4_EMR3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * DDR2: Value to write to EMR2 register.
 * DDR3/DDR4: Value to write to MR2 register
 * LPDDR2/LPDDR3/LPDDR4: Value to write to MR3 register
 * mDDR: Unused
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT4 . EMR2
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT4_EMR2(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT4_EMR2     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT4_EMR2(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief SDRAM Initialization Register 5
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT5
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT5    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x39)

/** 
 * \brief
 * Maximum duration of the auto initialization, tINIT5. Present only in
 * designs configured to support LPDDR2/LPDDR3.
 * LPDDR2/LPDDR3 typically requires 10 us.
 * Unit: 1024 DFI clock cycles.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT5 . MAX_AUTO_INIT_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT5_MAX_AUTO_INIT_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT5_MAX_AUTO_INIT_X1024     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT5_MAX_AUTO_INIT_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * ZQ initial calibration, tZQINIT. Present only in designs configured to
 * support DDR3 or DDR4 or LPDDR2/LPDDR3.
 * DDR3 typically requires 512 SDRAM clock cycles.
 * DDR4 requires 1024 SDRAM clock cycles.
 * LPDDR2/LPDDR3 requires 1 us.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to JEDEC spec value divided by 2, and round it up to the next
 * integer value.
 * Unit: 32 DFI clock cycles.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT5 . DEV_ZQINIT_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT5_DEV_ZQINIT_X32(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT5_DEV_ZQINIT_X32     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT5_DEV_ZQINIT_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


/** 
 * \brief SDRAM Initialization Register 6
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT6
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT6    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3a)

/** 
 * \brief
 * DDR4- Value to be loaded into SDRAM MR5 registers.
 * LPDDR4- Value to be loaded into SDRAM MR12 registers.
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT6 . MR5
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT6_MR5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT6_MR5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT6_MR5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * DDR4- Value to be loaded into SDRAM MR4 registers.
 * LPDDR4- Value to be loaded into SDRAM MR11 registers.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT6 . MR4
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT6_MR4(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT6_MR4     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT6_MR4(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief SDRAM Initialization Register 7
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:INIT7
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT7    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3b)

/** 
 * \brief
 * DDR4- Value to be loaded into SDRAM MR6 registers.
 * LPDDR4- Value to be loaded into SDRAM MR14 registers.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_INIT7 . MR6
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_INIT7_MR6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_INIT7_MR6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_INIT7_MR6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DIMM Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DIMMCTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3c)

/** 
 * \brief
 * Staggering enable for multi-rank accesses (for multi-rank UDIMM, RDIMM
 * and LRDIMM implementations only).  This is not supported for mDDR,
 * LPDDR2, LPDDR3 or LPDDR4 SDRAMs.
 * Note: Even if this bit is set it does not take care of software driven
 * MR commands (via MRCTRL0/MRCTRL1), where software is responsible to send
 * them to seperate ranks as appropriate.
 *     - 1 - (DDR4) Send MRS commands to each ranks seperately
 *     - 1 - (non-DDR4) Send all commands to even and odd ranks seperately
 *     - 0 - Do not stagger accesses
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . DIMM_STAGGER_CS_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_STAGGER_CS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_STAGGER_CS_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_STAGGER_CS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Address Mirroring Enable (for multi-rank UDIMM implementations and
 * multi-rank DDR4 RDIMM/LRDIMM implementations).
 * Some UDIMMs and DDR4 RDIMMs/LRDIMMs implement address mirroring for odd
 * ranks, which means that the following address, bank address and bank
 * group bits are swapped: (A3, A4), (A5, A6), (A7, A8), (BA0, BA1) and
 * also (A11, A13), (BG0, BG1) for the DDR4. Setting this bit ensures that,
 * for mode register accesses during the automatic initialization routine,
 * these bits are swapped within the uMCTL2 to compensate for this
 * UDIMM/RDIMM/LRDIMM swapping. In addition to the automatic initialization
 * routine, in case of DDR4 UDIMM/RDIMM/LRDIMM, they are swapped during the
 * automatic MRS access to enable/disable of a particular DDR4 feature.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 * This is not supported for mDDR, LPDDR2, LPDDR3 or LPDDR4 SDRAMs.
 * Note: In case of x16 DDR4 DIMMs, BG1 output of MRS for the odd ranks is
 * same as BG0 because BG1 is invalid, hence dimm_dis_bg_mirroring register
 * must be set to 1.
 *     - 1 - For odd ranks, implement address mirroring for MRS commands to
 * during initialization and for any automatic DDR4 MRS commands (to be
 * used if UDIMM/RDIMM/LRDIMM implements address mirroring)
 *     - 0 - Do not implement address mirroring
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . DIMM_ADDR_MIRR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_ADDR_MIRR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_ADDR_MIRR_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_ADDR_MIRR_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Output Inversion Enable (for DDR4 RDIMM/LRDIMM implementations only).
 * DDR4 RDIMM/LRDIMM implements the Output Inversion feature by default,
 * which means that the following address, bank address and bank group bits
 * of B-side DRAMs are inverted: A3-A9, A11, A13, A17, BA0-BA1, BG0-BG1.
 * Setting this bit ensures that, for mode register accesses generated by
 * the uMCTL2 during the automatic initialization routine and enabling of a
 * particular DDR4 feature, separate A-side and B-side mode register
 * accesses are generated. For B-side mode register accesses, these bits
 * are inverted within the uMCTL2 to compensate for this RDIMM/LRDIMM
 * inversion.  It is recommended to set this bit always, if using DDR4
 * RDIMMs/LRDIMMs.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 *     - 1 - Implement output inversion for B-side DRAMs.
 *     - 0 - Do not implement output inversion for B-side DRAMs.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . DIMM_OUTPUT_INV_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_OUTPUT_INV_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_OUTPUT_INV_EN  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_OUTPUT_INV_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable for A17 bit of MRS command.
 * A17 bit of the mode register address is specified as RFU (Reserved for
 * Future Use) and must be programmed to 0 during MRS. In case where DRAMs
 * which do not have A17 are attached and the Output Inversion are enabled,
 * this must be set to 0, so that the calculation of CA parity will not
 * include A17 bit.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 *     - 1 - Enabled
 *     - 0 - Disabled
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . MRS_A17_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_MRS_A17_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_MRS_A17_EN  VTSS_BIT(3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_MRS_A17_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable for BG1 bit of MRS command.
 * BG1 bit of the mode register address is specified as RFU (Reserved for
 * Future Use) and must be programmed to 0 during MRS. In case where DRAMs
 * which do not have BG1 are attached and both the CA parity and the Output
 * Inversion are enabled, this must be set to 0, so that the calculation of
 * CA parity will not include BG1 bit.
 * Note: This has no effect on the address of any other memory accesses, or
 * of software-driven mode register accesses.
 * If address mirroring is enabled, this is applied to BG1 of even ranks
 * and BG0 of odd ranks.
 *     - 1 - Enabled
 *     - 0 - Disabled
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . MRS_BG1_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_MRS_BG1_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_MRS_BG1_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_MRS_BG1_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Disabling Address Mirroring for BG bits. When this is set to 1, BG0 and
 * BG1 are NOT swapped even if Address Mirroring is enabled. This will be
 * required for DDR4 DIMMs with x16 devices.
 *     - 1 - BG0 and BG1 are NOT swapped.
 *     - 0 - BG0 and BG1 are swapped if address mirroring is enabled.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . DIMM_DIS_BG_MIRRORING
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_DIS_BG_MIRRORING(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_DIS_BG_MIRRORING  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_DIMM_DIS_BG_MIRRORING(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Protects the timing restrictions (tBCW/tMRC) between consecutive BCOM
 * commands defined in the Data Buffer specification. When using DDR4
 * LRDIMM, this bit must be set to 1. Otherwise, this bit must be set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL . LRDIMM_BCOM_CMD_PROT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_LRDIMM_BCOM_CMD_PROT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_LRDIMM_BCOM_CMD_PROT  VTSS_BIT(6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DIMMCTL_LRDIMM_BCOM_CMD_PROT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief Rank Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:RANKCTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_RANKCTL  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3d)

/** 
 * \brief
 * Only present for multi-rank configurations.
 * Background: Reads to the same rank can be performed back-to-back. Reads
 * to different ranks require additional gap dictated by the register
 * RANKCTL.diff_rank_rd_gap. This is to avoid possible data bus contention
 * as well as to give PHY enough time to switch the delay when changing
 * ranks. The uMCTL2 arbitrates for bus access on a cycle-by-cycle basis;
 * therefore after a read is scheduled, there are few clock cycles
 * (determined by the value on RANKCTL.diff_rank_rd_gap register) in which
 * only reads from the same rank are eligible to be scheduled. This
 * prevents reads from other ranks from having fair access to the data bus.
 * This parameter represents the maximum number of reads that can be
 * scheduled consecutively to the same rank. After this number is reached,
 * a delay equal to RANKCTL.diff_rank_rd_gap is inserted by the scheduler
 * to allow all ranks a fair opportunity to be scheduled. Higher numbers
 * increase bandwidth utilization, lower numbers increase fairness.
 * This feature can be DISABLED by setting this register to 0. When set to
 * 0, the Controller will stay on the same rank as long as commands are
 * available for it.
 * Minimum programmable value is 0 (feature disabled) and maximum
 * programmable value is 0xF.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RANKCTL . MAX_RANK_RD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_MAX_RANK_RD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_MAX_RANK_RD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_MAX_RANK_RD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Only present for multi-rank configurations.
 * Indicates the number of clocks of gap in data responses when performing
 * consecutive reads to different ranks.
 * This is used to switch the delays in the PHY to match the rank
 * requirements.
 * This value should consider both PHY requirement and ODT requirement.
 *     - PHY requirement:
 * 
 *	   tphy_rdcsgap (see PHY databook for value of tphy_rdcsgap)
 * 
 *	   If read preamble is set to 2tCK(DDR4 only), should be increased
 * by 1.
 * 
 *	   If read postamble is set to 1.5tCK(LPDDR4 only), should be
 * increased by 1.
 * 
 *     - ODT requirement:
 * 
 *	   The value programmed in this register takes care of the ODT
 * switch off timing requirement when switching ranks during reads.
 * 
 * When the controller is operating in 1:1 mode, program this to the larger
 * of PHY requirement or ODT requirement.
 * 
 * When the controller is operating in 1:2 mode, program this to the larger
 * value divided by two and round it up to the next integer.
 * 
 * Note that, if using DDR4-LRDIMM, refer to TRDRD timing requirements in
 * JEDEC DDR4 Data Buffer (DDR4DB01) Specification.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RANKCTL . DIFF_RANK_RD_GAP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_DIFF_RANK_RD_GAP(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_DIFF_RANK_RD_GAP     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_DIFF_RANK_RD_GAP(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Only present for multi-rank configurations.
 * Indicates the number of clocks of gap in data responses when performing
 * consecutive writes to different ranks.
 * This is used to switch the delays in the PHY to match the rank
 * requirements.
 *     This value should consider both PHY requirement and ODT requirement.
 *     - PHY requirement:
 * 
 *	   tphy_wrcsgap (see PHY databook for value of tphy_wrcsgap)
 * 
 *	   If CRC feature is enabled, should be increased by 1.
 * 
 *	   If write preamble is set to 2tCK(DDR4 only), should be increased
 * by 1.
 * 
 *	   If write postamble is set to 1.5tCK(LPDDR4 only), should be
 * increased by 1.
 * 
 *     - ODT requirement:
 * 
 *	   The value programmed in this register takes care of the ODT
 * switch off timing requirement when switching ranks during writes.
 * 
 *	   For LPDDR4, the requirement is ODTLoff - ODTLon - BL/2 + 1
 * 
 * When the controller is operating in 1:1 mode, program this to the larger
 * of PHY requirement or ODT requirement.
 * 
 * When the controller is operating in 1:2 mode, program this to the larger
 * value divided by two and round it up to the next integer.
 * 
 * Note that, if using DDR4-LRDIMM, refer to TWRWR timing requirements in
 * JEDEC DDR4 Data Buffer (DDR4DB01) Specification.
 * Programming Mode: Quasi-dynamic Group 2
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_RANKCTL . DIFF_RANK_WR_GAP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_DIFF_RANK_WR_GAP(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_DIFF_RANK_WR_GAP     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_RANKCTL_DIFF_RANK_WR_GAP(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/** 
 * \brief SDRAM Timing Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x40)

/** 
 * \brief
 * tRAS(min):  Minimum time between activate and precharge to the same
 * bank.
 * When the controller is operating in 1:2 frequency mode, 1T mode, program
 * this to tRAS(min)/2. No rounding up.
 * When the controller is operating in 1:2 frequency ratio mode, 2T mode or
 * LPDDR4 mode, program this to (tRAS(min)/2) and round it up to the next
 * integer value.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0 . T_RAS_MIN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_RAS_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_RAS_MIN     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_RAS_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * tRAS(max):  Maximum time between activate and precharge to same bank.
 * This is the maximum time that a page can be kept open
 * Minimum value of this register is 1. Zero is invalid.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRAS(max)-1)/2. No rounding up. 
 * Unit: Multiples of 1024 clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0 . T_RAS_MAX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_RAS_MAX(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_RAS_MAX     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_RAS_MAX(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * tFAW Valid only when 8 or more banks(or banks x bank groups) are
 * present.
 * In 8-bank design, at most 4 banks must be activated in a rolling window
 * of tFAW cycles.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tFAW/2) and round up to next integer value.
 * In a 4-bank design, set this register to 0x1 independent of the 1:1/1:2
 * frequency mode.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0 . T_FAW
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_FAW(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_FAW     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_T_FAW(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * 
 * Minimum time between write and precharge to same bank.  
 * Unit: Clocks
 * Specifications: WL + BL/2 + tWR = approximately 8 cycles + 15 ns = 14
 * clocks @400MHz and less for lower frequencies
 * where:
 *  - WL = write latency
 *  - BL = burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM. BST (burst terminate) is not
 * supported at present.
 *  - tWR = Write recovery time. This comes directly from the SDRAM
 * specification. 
 * Add one extra cycle for LPDDR2/LPDDR3/LPDDR4 for this parameter.
 * When the controller is operating in 1:2 frequency ratio mode, 1T mode,
 * divide the above value by 2. No rounding up.
 * When the controller is operating in 1:2 frequency ratio mode, 2T mode or
 * LPDDR4 mode, divide the above value by 2 and round it up to the next
 * integer value.
 * 
 * Note that, depending on the PHY, if using LRDIMM, it may be necessary to
 * adjust the value of this parameter to compensate for the extra cycle of
 * latency through the LRDIMM.
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0 . WR2PRE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_WR2PRE(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_WR2PRE     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG0_WR2PRE(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/** 
 * \brief SDRAM Timing Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x41)

/** 
 * \brief
 * tRC:  Minimum time between activates to same bank.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRC/2) and round up to next integer value.
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1 . T_RC
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_T_RC(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_T_RC     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_T_RC(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/** 
 * \brief
 * tRTP:  Minimum time from read to precharge of same bank.
 *  - DDR2: tAL + BL/2 + max(tRTP, 2) - 2
 *  - DDR3: tAL + max (tRTP, 4)
 *  - DDR4: Max of following two equations:
 *	      tAL + max (tRTP, 4) or, 
 *	      RL + BL/2 - tRP (*).
 *  - mDDR: BL/2
 *  - LPDDR2: Depends on if it's LPDDR2-S2 or LPDDR2-S4:
 *	      LPDDR2-S2: BL/2 + tRTP - 1.
 *	      LPDDR2-S4: BL/2 + max(tRTP,2) - 2.
 *  - LPDDR3: BL/2 +  max(tRTP,4) - 4
 *  - LPDDR4: BL/2 + max(tRTP,8) - 8
 * (*) When both DDR4 SDRAM and ST-MRAM are used simultaneously, use
 * SDRAM's tRP value for calculation.
 * 
 * When the controller is operating in 1:2 mode, 1T mode, divide the above
 * value by 2. No rounding up. 
 * When the controller is operating in 1:2 mode, 2T mode or LPDDR4 mode,
 * divide the above value by 2 and round it up to the next integer value. 
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1 . RD2PRE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_RD2PRE(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_RD2PRE     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_RD2PRE(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * tXP: Minimum time after power-down exit to any operation.  For DDR3,
 * this should be programmed to tXPDLL if slow powerdown exit is selected
 * in MR0[12].	
 * If C/A parity for DDR4 is used, set to (tXP+PL) instead. 
 * If LPDDR4 is selected and its spec has tCKELPD parameter, set to the
 * larger of tXP and tCKELPD instead.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tXP/2) and round it up to the next integer value.
 * Units: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1 . T_XP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_T_XP(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_T_XP     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG1_T_XP(x)  VTSS_EXTRACT_BITFIELD(x,16,5)


/** 
 * \brief SDRAM Timing Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x42)

/** 
 * \brief
 * 
 * DDR4: CWL + PL + BL/2 + tWTR_L
 * LPDDR2/3/4: WL + BL/2 + tWTR + 1
 * Others: CWL + BL/2 + tWTR
 * In DDR4, minimum time from write command to read command for same bank
 * group. In others, minimum time from write command to read command.
 * Includes time for bus turnaround, recovery times, and all per-bank,
 * per-rank, and global constraints.  
 * Unit: Clocks.
 * Where:
 *  - CWL = CAS write latency
 *  - WL = Write latency
 *  - PL = Parity latency
 *  - BL = burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM
 *  - tWTR_L = internal write to read command delay for same bank group.
 * This comes directly from the SDRAM specification. 
 *  - tWTR = internal write to read command delay. This comes directly from
 * the SDRAM specification. 
 * Add one extra cycle for LPDDR2/LPDDR3/LPDDR4 operation. 
 * When the controller is operating in 1:2 mode, divide the value
 * calculated using the above equation by 2, and round it up to next
 * integer.
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2 . WR2RD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_WR2RD(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_WR2RD     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_WR2RD(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * 
 * 
 * DDR2/3/mDDR: RL + BL/2 + 2 - WL
 * 
 * DDR4: RL + BL/2 + 1 + WR_PREAMBLE - WL
 * 
 * LPDDR2/LPDDR3: RL + BL/2 + RU(tDQSCKmax/tCK) + 1 - WL
 * 
 * LPDDR4(DQ ODT is Disabled): RL + BL/2 + RU(tDQSCKmax/tCK) + WR_PREAMBLE
 * + RD_POSTAMBLE - WL
 * 
 * LPDDR4(DQ ODT is Enabled) : RL + BL/2 + RU(tDQSCKmax/tCK) + RD_POSTAMBLE
 * - ODTLon - RU(tODTon(min)/tCK)
 * 
 * Minimum time from read command to write command. Include time for bus
 * turnaround and all per-bank, per-rank, and global constraints.  Please
 * see the relevant PHY databook for details of what should be included
 * here.
 * Unit: Clocks.
 * Where:
 *  - WL = write latency
 *  - BL = burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM
 *  - RL = read latency = CAS latency
 *  - WR_PREAMBLE = write preamble. This is unique to DDR4 and LPDDR4.
 *  - RD_POSTAMBLE = read postamble. This is unique to LPDDR4.
 * For LPDDR2/LPDDR3/LPDDR4, if derating is enabled
 * (DERATEEN.derate_enable=1), derated tDQSCKmax should be used.
 * 
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the above equation by 2, and round it up to next
 * integer.
 * 
 * Note that, depending on the PHY, if using LRDIMM, it may be necessary to
 * adjust the value of this parameter to compensate for the extra cycle of
 * latency through the LRDIMM.
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2 . RD2WR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_RD2WR(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_RD2WR     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_RD2WR(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Set to RL
 * Time from read command to read data on SDRAM interface. This must be set
 * to RL.
 * Note that, depending on the PHY, if using RDIMM/LRDIMM, it may be
 * necessary to adjust the value of RL to compensate for the extra cycle of
 * latency through the RDIMM/LRDIMM.
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the above equation by 2, and round it up to next
 * integer.
 * This register field is not required for DDR2 and DDR3 (except if
 * MEMC_TRAINING is set), as the DFI read and write latencies defined in
 * DFITMG0 and DFITMG1 are sufficient for those protocols
 * Unit: clocks
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2 . READ_LATENCY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_READ_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_READ_LATENCY     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_READ_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Set to WL
 * Time from write command to write data on SDRAM interface. This must be
 * set to WL.
 * For mDDR, it should normally be set to 1.
 * Note that, depending on the PHY, if using RDIMM/LRDIMM, it may be
 * necessary to adjust the value of WL to compensate for the extra cycle of
 * latency through the RDIMM/LRDIMM.
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the above equation by 2, and round it up to next
 * integer.
 * This register field is not required for DDR2 and DDR3 (except if
 * MEMC_TRAINING is set), as the DFI read and write latencies defined in
 * DFITMG0 and DFITMG1 are sufficient for those protocols
 * Unit: clocks
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2 . WRITE_LATENCY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_WRITE_LATENCY(x)  VTSS_ENCODE_BITFIELD(x,24,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_WRITE_LATENCY     VTSS_ENCODE_BITMASK(24,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG2_WRITE_LATENCY(x)  VTSS_EXTRACT_BITFIELD(x,24,6)


/** 
 * \brief SDRAM Timing Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG3
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x43)

/** 
 * \brief
 * tMOD: Parameter used only in DDR3 and DDR4. Cycles between load mode
 * command and following non-load mode command.
 * If C/A parity for DDR4 is used, set to tMOD_PAR(tMOD+PL) instead.
 * If MPR writes for DDR4 are used, set to tMOD + AL (or tMPD_PAR + AL if
 * C/A parity is also used).
 * Set to tMOD if controller is operating in 1:1 frequency ratio mode, or
 * tMOD/2 (rounded up to next integer) if controller is operating in 1:2
 * frequency ratio mode. Note that if using RDIMM/LRDIMM, depending on the
 * PHY, it may be necessary to adjust the value of this parameter to
 * compensate for the extra cycle of latency applied to mode register
 * writes by the RDIMM/LRDIMM chip.
 * Also note that if using LRDIMM, the minimum value of this register is
 * tMRD_L2 if controller is operating in 1:1 frequency ratio mode, or
 * tMRD_L2/2 (rounded up to next integer) if controller is operating in 1:2
 * frequency ratio mode.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3 . T_MOD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MOD(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MOD     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MOD(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * tMRD: Cycles to wait after a mode register write or read. Depending on
 * the connected SDRAM, tMRD represents:
 * DDR2/mDDR: Time from MRS to any command
 * DDR3/4: Time from MRS to MRS command
 * LPDDR2: not used
 * LPDDR3/4: Time from MRS to non-MRS command.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tMRD/2) and round it up to the next integer value.
 * If C/A parity for DDR4 is used, set to tMRD_PAR(tMOD+PL) instead.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3 . T_MRD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MRD(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MRD     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MRD(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Time to wait after a mode register write or read (MRW or MRR).
 * Present only in designs configured to support LPDDR2, LPDDR3 or LPDDR4.
 * LPDDR2 typically requires value of 5.
 * LPDDR3 typically requires value of 10.
 * LPDDR4: Set this to the larger of tMRW and tMRWCKEL.
 * For LPDDR2, this register is used for the time from a MRW/MRR to all
 * other commands.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the above values divided by 2 and round it up to the next
 * integer value.
 * For LDPDR3, this register is used for the time from a MRW/MRR to a
 * MRW/MRR.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3 . T_MRW
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MRW(x)  VTSS_ENCODE_BITFIELD(x,20,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MRW     VTSS_ENCODE_BITMASK(20,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG3_T_MRW(x)  VTSS_EXTRACT_BITFIELD(x,20,10)


/** 
 * \brief SDRAM Timing Register 4
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG4
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x44)

/** 
 * \brief
 * tRP:  Minimum time from precharge to activate of same bank.
 * 
 *     When the controller is operating in 1:1 frequency ratio mode, t_rp
 * should be set to RoundUp(tRP/tCK).
 * 
 *     When the controller is operating in 1:2 frequency ratio mode, t_rp
 * should be set to RoundDown(RoundUp(tRP/tCK)/2) + 1.
 * 
 *     When the controller is operating in 1:2 frequency ratio mode in
 * LPDDR4, t_rp should be set to RoundUp(RoundUp(tRP/tCK)/2).
 * 
 *     
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4 . T_RP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RP(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RP     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RP(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * DDR4: tRRD_L: Minimum time between activates from bank "a" to bank "b"
 * for same bank group.
 * Others: tRRD: Minimum time between activates from bank "a" to bank "b"
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRRD_L/2 or tRRD/2) and round it up to the next integer value.
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4 . T_RRD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RRD(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RRD     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RRD(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * DDR4: tCCD_L: This is the minimum time between two reads or two writes
 * for same bank group.
 * Others: tCCD: This is the minimum time between two reads or two writes.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tCCD_L/2 or tCCD/2) and round it up to the next integer value.
 * Unit: clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4 . T_CCD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_CCD(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_CCD     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_CCD(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * tRCD - tAL: Minimum time from activate to read or write command to same
 * bank.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to ((tRCD - tAL)/2) and round it up to the next integer value. 
 * Minimum value allowed for this register is 1, which implies minimum
 * (tRCD - tAL) value to be 2 when the controller is operating in 1:2
 * frequency ratio mode. 
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4 . T_RCD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RCD(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RCD     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG4_T_RCD(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/** 
 * \brief SDRAM Timing Register 5
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG5
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x45)

/** 
 * \brief
 * Minimum number of cycles of CKE HIGH/LOW during power-down and self
 * refresh.
 *  - LPDDR2/LPDDR3 mode: Set this to the larger of tCKE or tCKESR
 *  - LPDDR4 mode: Set this to the larger of tCKE or tSR.
 *  - Non-LPDDR2/non-LPDDR3/non-LPDDR4 designs: Set this to tCKE value.
 *  When the controller is operating in 1:2 frequency ratio mode, program
 * this to (value described above)/2 and round it up to the next integer
 * value. 
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5 . T_CKE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * Minimum CKE low width for Self refresh or Self refresh power down entry
 * to exit timing in memory clock cycles. 
 * 
 * Recommended settings:
 *     - mDDR: tRFC
 *     - LPDDR2: tCKESR
 *     - LPDDR3: tCKESR
 *     - LPDDR4: max(tCKE, tSR)
 *     - DDR2: tCKE 
 *     - DDR3: tCKE + 1  
 *     - DDR4: tCKE + 1 (+ PL(parity latency)(*)) 
 * (*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register should
 * be increased by PL.
 * 
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5 . T_CKESR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKESR(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKESR     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKESR(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * This is the time after Self Refresh Down Entry that CK is maintained as
 * a valid clock. Specifies the clock disable delay after SRE. 
 * 
 *    Recommended settings:
 *     - mDDR: 0
 *     - LPDDR2: 2
 *     - LPDDR3: 2
 *     - LPDDR4: tCKELCK
 *     - DDR2: 1 
 *     - DDR3: max (10 ns, 5 tCK)
 *     - DDR4: max (10 ns, 5 tCK) (+ PL(parity latency)(*))
 * (*)Only if CRCPARCTL1.caparity_disable_before_sr=0, this register should
 * be increased by PL.
 * 
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5 . T_CKSRE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKSRE(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKSRE     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKSRE(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * This is the time before Self Refresh Exit that CK is maintained as a
 * valid clock before issuing SRX. Specifies the clock stable time before
 * SRX. 
 * 
 *     Recommended settings:
 *     - mDDR: 1
 *     - LPDDR2: 2
 *     - LPDDR3: 2
 *     - LPDDR4: tCKCKEH
 *     - DDR2: 1  
 *     - DDR3: tCKSRX 
 *     - DDR4: tCKSRX 
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5 . T_CKSRX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKSRX(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKSRX     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG5_T_CKSRX(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief SDRAM Timing Register 6
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG6
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x46)

/** 
 * \brief
 * This is the time before Clock Stop Exit that CK is maintained as a valid
 * clock before issuing Clock Stop Exit. Specifies the clock stable time
 * before next command after Clock Stop Exit. 
 * 
 *     Recommended settings:
 *     - mDDR: 1
 *     - LPDDR2: tXP + 2
 *     - LPDDR3: tXP + 2
 *     - LPDDR4: tXP + 2
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer. 
 * 
 * This is only present for designs supporting mDDR or LPDDR2/LPDDR3/LPDDR4
 * devices.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6 . T_CKCSX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKCSX(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKCSX     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKCSX(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * This is the time before Deep Power Down Exit that CK is maintained as a
 * valid clock before issuing DPDX. Specifies the clock stable time before
 * DPDX. 
 * 
 *     Recommended settings:
 *     - mDDR: 1
 *     - LPDDR2: 2
 *     - LPDDR3: 2
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer. 
 * 
 * This is only present for designs supporting mDDR or LPDDR2 devices.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6 . T_CKDPDX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKDPDX(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKDPDX     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKDPDX(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * This is the time after Deep Power Down Entry that CK is maintained as a
 * valid clock. Specifies the clock disable delay after DPDE. 
 * 
 * Recommended settings:
 *     - mDDR: 0
 *     - LPDDR2: 2
 *     - LPDDR3: 2
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer. 
 * 
 * This is only present for designs supporting mDDR or LPDDR2/LPDDR3
 * devices.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6 . T_CKDPDE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKDPDE(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKDPDE     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG6_T_CKDPDE(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief SDRAM Timing Register 7
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG7
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x47)

/** 
 * \brief
 * This is the time before Power Down Exit that CK is maintained as a valid
 * clock before issuing PDX. Specifies the clock stable time before PDX. 
 * 
 *     Recommended settings:
 *     - mDDR: 0
 *     - LPDDR2: 2
 *     - LPDDR3: 2
 *     - LPDDR4: 2
 * When using DDR2/3/4 SDRAM, this register should be set to the same value
 * as DRAMTMG5.t_cksrx.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer. 
 * 
 * This is only present for designs supporting mDDR or LPDDR2/LPDDR3/LPDDR4
 * devices.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7 . T_CKPDX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7_T_CKPDX(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7_T_CKPDX     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7_T_CKPDX(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * This is the time after Power Down Entry that CK is maintained as a valid
 * clock. Specifies the clock disable delay after PDE. 
 * 
 *     Recommended settings:
 *     - mDDR: 0
 *     - LPDDR2: 2
 *     - LPDDR3: 2
 *     - LPDDR4: tCKELCK
 * When using DDR2/3/4 SDRAM, this register should be set to the same value
 * as DRAMTMG5.t_cksre.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer. 
 * 
 * This is only present for designs supporting mDDR or LPDDR2/LPDDR3/LPDDR4
 * devices.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7 . T_CKPDE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7_T_CKPDE(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7_T_CKPDE     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG7_T_CKPDE(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/** 
 * \brief SDRAM Timing Register 8
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG8
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x48)

/** 
 * \brief
 * tXS: Exit Self Refresh to commands not requiring a locked DLL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the above value divided by 2 and round up to next integer value.
 * Unit: Multiples of 32 clocks.
 * Note: Used only for DDR2, DDR3 and DDR4 SDRAMs.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8 . T_XS_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_X32(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_X32     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/** 
 * \brief
 * tXSDLL: Exit Self Refresh to commands requiring a locked DLL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the above value divided by 2 and round up to next integer value.
 * Unit: Multiples of 32 clocks.
 * Note: Used only for DDR2, DDR3 and DDR4 SDRAMs.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8 . T_XS_DLL_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_DLL_X32(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_DLL_X32     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_DLL_X32(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * tXS_ABORT: Exit Self Refresh to commands not requiring a locked DLL in
 * Self Refresh Abort.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the above value divided by 2 and round up to next integer value.
 * Unit: Multiples of 32 clocks.
 * Note: Ensure this is less than or equal to t_xs_x32.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8 . T_XS_ABORT_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_ABORT_X32(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_ABORT_X32     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_ABORT_X32(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * tXS_FAST: Exit Self Refresh to ZQCL, ZQCS and MRS (only CL, WR, RTP and
 * Geardown mode).
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the above value divided by 2 and round up to next integer value.
 * Unit: Multiples of 32 clocks.
 * Note: This is applicable to only ZQCL/ZQCS commands. 
 * Note: Ensure this is less than or equal to t_xs_x32.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8 . T_XS_FAST_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_FAST_X32(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_FAST_X32     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG8_T_XS_FAST_X32(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/** 
 * \brief SDRAM Timing Register 9
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG9
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x49)

/** 
 * \brief
 * 
 * CWL + PL + BL/2 + tWTR_S
 * Minimum time from write command to read command for different bank
 * group. Includes time for bus turnaround, recovery times, and all
 * per-bank, per-rank, and global constraints.
 * Present only in designs configured to support DDR4.
 * Unit: Clocks.
 * Where:
 *  - CWL = CAS write latency
 *  - PL = Parity latency
 *  - BL = burst length. This must match the value programmed in the BL bit
 * of the mode register to the SDRAM
 *  - tWTR_S = internal write to read command delay for different bank
 * group. This comes directly from the SDRAM specification.
 * When the controller is operating in 1:2 mode, divide the value
 * calculated using the above equation by 2, and round it up to next
 * integer.
 * Programming Mode: Quasi-dynamic Group 1 and Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9 . WR2RD_S
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_WR2RD_S(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_WR2RD_S     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_WR2RD_S(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * tRRD_S: Minimum time between activates from bank "a" to bank "b" for
 * different bank group.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tRRD_S/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9 . T_RRD_S
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_T_RRD_S(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_T_RRD_S     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_T_RRD_S(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * tCCD_S: This is the minimum time between two reads or two writes for
 * different bank group. For bank switching (from bank "a" to bank "b"),
 * the minimum time is this value + 1.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tCCD_S/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9 . T_CCD_S
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_T_CCD_S(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_T_CCD_S     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_T_CCD_S(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * DDR4 Write preamble mode
 *   - 0: 1tCK preamble
 *   - 1: 2tCK preamble
 * Present only with MEMC_FREQ_RATIO=2
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9 . DDR4_WR_PREAMBLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_DDR4_WR_PREAMBLE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_DDR4_WR_PREAMBLE  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG9_DDR4_WR_PREAMBLE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)


/** 
 * \brief SDRAM Timing Register 10
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG10
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4a)

/** 
 * \brief
 * Geardown hold time.
 * Minimum value of this register is 1. Zero is invalid.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as 2 clks
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tGEAR_hold/2) and round it up to the next integer value.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10 . T_GEAR_HOLD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_GEAR_HOLD(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_GEAR_HOLD     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_GEAR_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Geardown setup time.
 * Minimum value of this register is 1. Zero is invalid.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as 2 clks
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tGEAR_setup/2) and round it up to the next integer value.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10 . T_GEAR_SETUP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_GEAR_SETUP(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_GEAR_SETUP     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_GEAR_SETUP(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Sync pulse to first valid command.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as tMOD(min)
 * tMOD(min) is greater of 24nCK or 15ns
 * 15ns / .625ns = 24
 * Max value for this register is 24
 * When the controller is operating in 1:2 mode, program this to
 * (tCMD_GEAR/2) and round it up to the next integer value.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10 . T_CMD_GEAR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_CMD_GEAR(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_CMD_GEAR     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_CMD_GEAR(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Indicates the time between MRS command and the sync pulse time.
 * This must be even number of clocks.
 * For DDR4-2666 and DDR4-3200, this parameter is defined as tMOD(min)+4nCK
 * tMOD(min) is greater of 24nCK or 15ns
 * 15ns / .625ns = 24
 * Max value for this register is 24+4 = 28
 * When the controller is operating in 1:2 mode, program this to
 * (tSYNC_GEAR/2) and round it up to the next integer value.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10 . T_SYNC_GEAR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_SYNC_GEAR(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_SYNC_GEAR     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG10_T_SYNC_GEAR(x)  VTSS_EXTRACT_BITFIELD(x,16,5)


/** 
 * \brief SDRAM Timing Register 11
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG11
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4b)

/** 
 * \brief
 * tCKMPE: Minimum valid clock requirement after MPSM entry.
 * Present only in designs configured to support DDR4.
 * Unit: Clocks.
 * 
 * When the controller is operating in 1:2 frequency ratio mode, divide the
 * value calculated using the above equation by 2, and round it up to next
 * integer.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11 . T_CKMPE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_CKMPE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_CKMPE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_CKMPE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * tMPX_S:  Minimum time CS setup time to CKE.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tMPX_S/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: Clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11 . T_MPX_S
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_MPX_S(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_MPX_S     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_MPX_S(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * tMPX_LH:  This is the minimum CS_n Low hold time to CKE rising edge.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to RoundUp(tMPX_LH/2)+1.
 * Present only in designs configured to support DDR4.
 * Unit: clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11 . T_MPX_LH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_MPX_LH(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_MPX_LH     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_T_MPX_LH(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * tXMPDLL:  This is the minimum Exit MPSM to commands requiring a locked
 * DLL.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tXMPDLL/2) and round it up to the next integer value.
 * Present only in designs configured to support DDR4.
 * Unit: Multiples of 32 clocks.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11 . POST_MPSM_GAP_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_POST_MPSM_GAP_X32(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_POST_MPSM_GAP_X32     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG11_POST_MPSM_GAP_X32(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/** 
 * \brief SDRAM Timing Register 12
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG12
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG12  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4c)

/** 
 * \brief
 * tMRD_PDA:  This is the Mode Register Set command cycle time in PDA mode.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tMRD_PDA/2) and round it up to the next integer value.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG12 . T_MRD_PDA
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG12_T_MRD_PDA(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG12_T_MRD_PDA     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG12_T_MRD_PDA(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SDRAM Timing Register 14
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG14
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG14  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4e)

/** 
 * \brief
 * tXSR: Exit Self Refresh to any command.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to the above value divided by 2 and round up to next integer value.
 * Note: Used only for mDDR/LPDDR2/LPDDR3/LPDDR4 mode.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG14 . T_XSR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG14_T_XSR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG14_T_XSR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG14_T_XSR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief SDRAM Timing Register 15
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DRAMTMG15
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x4f)

/** 
 * \brief
 * tSTAB: Stabilization time.
 * It is required in the following two cases for DDR3/DDR4 RDIMM : 
 *    - when exiting power saving mode, if the clock was stopped, after
 * re-enabling it the clock must be stable for a time specified by tSTAB
 *    - in the case of input clock frequency change (DDR4)
 *    - after issuing control words that refers to clock timing
 *   (Specification: 6us for DDR3, 5us for DDR4)
 * 
 *   When the controller is operating in 1:2 frequency ratio mode, program
 * this to recommended value divided by two and round it up to next
 * integer.
 * Unit: Multiples of 32 clock cycles.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15 . T_STAB_X32
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15_T_STAB_X32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15_T_STAB_X32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15_T_STAB_X32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * 
 *   - 1 - Enable using tSTAB when exiting DFI LP. Needs to be set when the
 * PHY is stopping the clock during DFI LP to save maximum power.
 *   - 0 - Disable using tSTAB when exiting DFI LP
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15 . EN_DFI_LP_T_STAB
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15_EN_DFI_LP_T_STAB(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15_EN_DFI_LP_T_STAB  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DRAMTMG15_EN_DFI_LP_T_STAB(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/** 
 * \brief ZQ Control Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ZQCTL0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x60)

/** 
 * \brief
 * tZQCS for DDR3/DD4/LPDDR2/LPDDR3, tZQLAT for LPDDR4: Number of DFI clock
 * cycles of NOP required after a ZQCS (ZQ calibration short)/MPC(ZQ Latch)
 * command is issued to SDRAM.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to tZQCS/2 and round it up to the next integer value.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0 . T_ZQ_SHORT_NOP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_T_ZQ_SHORT_NOP(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_T_ZQ_SHORT_NOP     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_T_ZQ_SHORT_NOP(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * tZQoper for DDR3/DDR4, tZQCL for LPDDR2/LPDDR3, tZQCAL for LPDDR4:
 * Number of DFI clock cycles of NOP required after a ZQCL (ZQ calibration
 * long)/MPC(ZQ Start) command is issued to SDRAM.
 * When the controller is operating in 1:2 frequency ratio mode:
 * DDR3/DDR4: program this to tZQoper/2 and round it up to the next integer
 * value.
 * LPDDR2/LPDDR3: program this to tZQCL/2 and round it up to the next
 * integer value.
 * LPDDR4: program this to tZQCAL/2 and round it up to the next integer
 * value.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0 . T_ZQ_LONG_NOP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_T_ZQ_LONG_NOP(x)  VTSS_ENCODE_BITFIELD(x,16,11)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_T_ZQ_LONG_NOP     VTSS_ENCODE_BITMASK(16,11)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_T_ZQ_LONG_NOP(x)  VTSS_EXTRACT_BITFIELD(x,16,11)

/** 
 * \brief
 * 
 *  - 1 - Disable issuing of ZQCL command at Maximum Power Saving Mode
 * exit. Only applicable when run in DDR4 mode.
 *  - 0 - Enable issuing of ZQCL command at Maximum Power Saving Mode exit.
 * Only applicable when run in DDR4 mode.
 * This is only present for designs supporting DDR4 devices.
 * Note: Do not issue ZQCL command at Maximum Power Save Mode exit if the
 * UMCTL2_SHARED_AC configuration parameter is set. Program it to 1'b1. The
 * software can send ZQCS after exiting MPSM mode.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0 . DIS_MPSMX_ZQCL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_MPSMX_ZQCL(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_MPSMX_ZQCL  VTSS_BIT(28)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_MPSMX_ZQCL(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * 
 *  - 1 - Denotes that ZQ resistor is shared between ranks. Means
 * ZQinit/ZQCL/ZQCS/MPC(ZQ calibration) commands are sent to one rank at a
 * time with tZQinit/tZQCL/tZQCS/tZQCAL/tZQLAT timing met between commands
 * so that commands to different ranks do not overlap. 
 *  - 0 - ZQ resistor is not shared.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0 . ZQ_RESISTOR_SHARED
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_ZQ_RESISTOR_SHARED(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_ZQ_RESISTOR_SHARED  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_ZQ_RESISTOR_SHARED(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * 
 *  - 1 - Disable issuing of ZQCL/MPC(ZQ calibration) command at
 * Self-Refresh/SR-Powerdown exit. Only applicable when run in DDR3 or DDR4
 * or LPDDR2 or LPDDR3 or LPDDR4 mode.
 *  - 0 - Enable issuing of ZQCL/MPC(ZQ calibration) command at
 * Self-Refresh/SR-Powerdown exit. Only applicable when run in DDR3 or DDR4
 * or LPDDR2 or LPDDR3 or LPDDR4 mode.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0 . DIS_SRX_ZQCL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_SRX_ZQCL(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_SRX_ZQCL  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_SRX_ZQCL(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * 
 *  - 1 - Disable uMCTL2 generation of ZQCS/MPC(ZQ calibration) command. 
 * Register DBGCMD.zq_calib_short can be used instead to issue ZQ
 * calibration request from APB module.
 *  - 0 - Internally generate ZQCS/MPC(ZQ calibration) commands based on
 * ZQCTL1.t_zq_short_interval_x1024.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0 . DIS_AUTO_ZQ
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_AUTO_ZQ(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_AUTO_ZQ  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL0_DIS_AUTO_ZQ(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/** 
 * \brief ZQ Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ZQCTL1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x61)

/** 
 * \brief
 * Average interval to wait between automatically issuing ZQCS (ZQ
 * calibration short)/MPC(ZQ calibration) commands to
 * DDR3/DDR4/LPDDR2/LPDDR3/LPDDR4 devices.
 * Meaningless, if ZQCTL0.dis_auto_zq=1.
 * Unit: 1024 DFI clock cycles.
 * This is only present for designs supporting DDR3/DDR4 or
 * LPDDR2/LPDDR3/LPDDR4 devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1 . T_ZQ_SHORT_INTERVAL_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

/** 
 * \brief
 * tZQReset: Number of DFI clock cycles of NOP required after a ZQReset (ZQ
 * calibration Reset) command is issued to SDRAM.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to tZQReset/2 and round it up to the next integer value.
 * This is only present for designs supporting LPDDR2/LPDDR3/LPDDR4
 * devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1 . T_ZQ_RESET_NOP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1_T_ZQ_RESET_NOP(x)  VTSS_ENCODE_BITFIELD(x,20,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1_T_ZQ_RESET_NOP     VTSS_ENCODE_BITMASK(20,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL1_T_ZQ_RESET_NOP(x)  VTSS_EXTRACT_BITFIELD(x,20,10)


/** 
 * \brief ZQ Control Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ZQCTL2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL2   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x62)

/** 
 * \brief
 * 
 * Setting this register bit to 1 triggers a ZQ Reset operation. When the
 * ZQ Reset operation is complete, the uMCTL2 automatically clears this
 * bit. It is recommended NOT to set this signal if in Init,
 * Self-Refresh(except LPDDR4) or SR-Powerdown(LPDDR4) or Deep power-down
 * operating modes.
 * This is only present for designs supporting LPDDR2/LPDDR3/LPDDR4
 * devices.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQCTL2 . ZQ_RESET
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQCTL2_ZQ_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQCTL2_ZQ_RESET  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQCTL2_ZQ_RESET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief ZQ Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ZQSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQSTAT   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x63)

/** 
 * \brief
 * SoC core may initiate a ZQ Reset operation only if this signal is low.
 * This signal goes high in the clock after the uMCTL2 accepts the ZQ Reset
 * request. It goes low when the ZQ Reset command is issued to the SDRAM
 * and the associated NOP period is over. It is recommended not to perform
 * ZQ Reset commands when this signal is high.
 *  - 0 - Indicates that the SoC core can initiate a ZQ Reset operation
 *  - 1 - Indicates that ZQ Reset operation is in progress
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ZQSTAT . ZQ_RESET_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ZQSTAT_ZQ_RESET_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ZQSTAT_ZQ_RESET_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ZQSTAT_ZQ_RESET_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DFI Timing Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFITMG0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x64)

/** 
 * \brief
 * Write latency
 * Number of clocks from the write command to write data enable
 * (dfi_wrdata_en).  This corresponds to the DFI timing parameter
 * tphy_wrlat.
 * Refer to PHY specification for correct value.Note that, depending on the
 * PHY, if using RDIMM/LRDIMM, it may be necessary to use the adjusted
 * value of CL in the calculation of tphy_wrlat. This is to compensate for
 * the extra cycle(s) of latency through the RDIMM/LRDIMM.
 * For LPDDR4, dfi_tphy_wrlat>60 is not supported.
 * Unit: DFI clock cycles or DFI PHY clock cycles, depending on
 * DFITMG0.dfi_wrdata_use_dfi_phy_clk.
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0 . DFI_TPHY_WRLAT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_TPHY_WRLAT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_TPHY_WRLAT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_TPHY_WRLAT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Specifies the number of clock cycles between when dfi_wrdata_en is
 * asserted to when the associated write data is driven on the dfi_wrdata
 * signal.  This corresponds to the DFI timing parameter tphy_wrdata. 
 * Refer to PHY specification for correct value. Note, max supported value
 * is 8.
 * Unit: DFI clock cycles or DFI PHY clock cycles, depending on
 * DFITMG0.dfi_wrdata_use_dfi_phy_clk.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0 . DFI_TPHY_WRDATA
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_TPHY_WRDATA(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_TPHY_WRDATA     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_TPHY_WRDATA(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Defines whether dfi_wrdata_en/dfi_wrdata/dfi_wrdata_mask is generated
 * using HDR (DFI clock) or SDR (DFI PHY clock) values
 * Selects whether value in DFITMG0.dfi_tphy_wrlat  is in terms of HDR (DFI
 * clock) or SDR (DFI PHY clock) cycles
 * Selects whether value in DFITMG0.dfi_tphy_wrdata is in terms of HDR (DFI
 * clock) or SDR (DFI PHY clock) cycles
 *  - 0 in terms of HDR (DFI clock) cycles
 *  - 1 in terms of SDR (DFI PHY clock) cycles
 * Refer to PHY specification for correct value.
 * If using a Synopsys DWC DDR3/2 PHY, DWC DDR2/3-Lite/mDDR PHY, DWC DDR
 * multiPHY or DWC Gen2 DDR multiPHY, this field must be set to 0;
 * otherwise:
 *  - If MEMC_PROG_FREQ_RATIO=1 and MSTR.frequency_ratio=1, this field
 * should be set to 0
 *  - Else, it must be set to 1
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0 . DFI_WRDATA_USE_DFI_PHY_CLK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_WRDATA_USE_DFI_PHY_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_WRDATA_USE_DFI_PHY_CLK  VTSS_BIT(15)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_WRDATA_USE_DFI_PHY_CLK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Time from the assertion of a read command on the DFI interface to the
 * assertion of the dfi_rddata_en signal.
 * Refer to PHY specification for correct value.
 * This corresponds to the DFI parameter trddata_en. Note that, depending
 * on the PHY, if using RDIMM/LRDIMM, it may be necessary to use the
 * adjusted value of CL in the calculation of trddata_en. This is to
 * compensate for the extra cycle(s) of latency through the RDIMM/LRDIMM.
 * Unit: DFI clock cycles or DFI PHY clock cycles, depending on
 * DFITMG0.dfi_rddata_use_dfi_phy_clk.
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0 . DFI_T_RDDATA_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_T_RDDATA_EN(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_T_RDDATA_EN     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_T_RDDATA_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Defines whether dfi_rddata_en/dfi_rddata/dfi_rddata_valid is generated
 * using HDR (DFI clock) or SDR (DFI PHY clock) values.  
 * Selects whether value in DFITMG0.dfi_t_rddata_en is in terms of HDR (DFI
 * clock) or SDR (DFI PHY clock) cycles:
 *  - 0 in terms of HDR (DFI clock) cycles
 *  - 1 in terms of SDR (DFI PHY clock) cycles
 * Refer to PHY specification for correct value.
 * If using a Synopsys DWC DDR3/2 PHY, DWC DDR2/3-Lite/mDDR PHY, DWC DDR
 * multiPHY or DWC Gen2 DDR multiPHY, this field must be set to 0;
 * otherwise:
 *  - If MEMC_PROG_FREQ_RATIO=1 and MSTR.frequency_ratio=1, this field
 * should be set to 0
 *  - Else, it must be set to 1
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0 . DFI_RDDATA_USE_DFI_PHY_CLK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_RDDATA_USE_DFI_PHY_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_RDDATA_USE_DFI_PHY_CLK  VTSS_BIT(23)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_RDDATA_USE_DFI_PHY_CLK(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Specifies the number of DFI clock cycles after an assertion or
 * de-assertion of the DFI control signals that the control signals at the
 * PHY-DRAM interface reflect the assertion or de-assertion. If the DFI
 * clock and the memory clock are not phase-aligned, this timing parameter
 * should be rounded up to the next integer value. Note that if using
 * RDIMM/LRDIMM, it is necessary to increment this parameter by
 * RDIMM's/LRDIMM's extra cycle of latency in terms of DFI clock.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG0 . DFI_T_CTRL_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_T_CTRL_DELAY(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_T_CTRL_DELAY     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG0_DFI_T_CTRL_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/** 
 * \brief DFI Timing Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFITMG1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x65)

/** 
 * \brief
 * Specifies the number of DFI clock cycles from the de-assertion of the
 * dfi_dram_clk_disable signal on the DFI until the first valid rising edge
 * of the clock to the DRAM memory devices, at the PHY-DRAM boundary. If
 * the DFI clock and the memory clock are not phase aligned, this timing
 * parameter should be rounded up to the next integer value.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG1 . DFI_T_DRAM_CLK_ENABLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_DRAM_CLK_ENABLE(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_DRAM_CLK_ENABLE     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_DRAM_CLK_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * Specifies the number of DFI clock cycles from the assertion of the
 * dfi_dram_clk_disable signal on the DFI until the clock to the DRAM
 * memory devices, at the PHY-DRAM boundary, maintains a low value. If the
 * DFI clock and the memory clock are not phase aligned, this timing
 * parameter should be rounded up to the next integer value.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG1 . DFI_T_DRAM_CLK_DISABLE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_DRAM_CLK_DISABLE(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_DRAM_CLK_DISABLE     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_DRAM_CLK_DISABLE(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Specifies the number of DFI clock cycles between when the dfi_wrdata_en
 * signal is asserted and when the corresponding write data transfer is
 * completed on the DRAM bus. 
 * This corresponds to the DFI timing parameter twrdata_delay.	Refer to
 * PHY specification for correct value. 
 * For DFI 3.0 PHY, set to twrdata_delay, a new timing parameter introduced
 * in DFI 3.0.
 * For DFI 2.1 PHY, set to tphy_wrdata + (delay of DFI write data to the
 * DRAM). 
 * Value to be programmed is in terms of DFI clocks, not PHY clocks.
 * In FREQ_RATIO=2, divide PHY's value by 2 and round up to next integer.
 * If using DFITMG0.dfi_wrdata_use_dfi_phy_clk=1, add 1 to the value.
 * Unit: Clocks
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG1 . DFI_T_WRDATA_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_WRDATA_DELAY(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_WRDATA_DELAY     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_WRDATA_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Specifies the number of DFI PHY clock cycles between when the dfi_cs
 * signal is asserted and when the associated dfi_parity_in signal is
 * driven.
 * Programming Mode: Quasi-dynamic Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG1 . DFI_T_PARIN_LAT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_PARIN_LAT(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_PARIN_LAT     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_PARIN_LAT(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Specifies the number of DFI PHY clock cycles between when the dfi_cs
 * signal is asserted and when the associated command is driven.
 * This field is used for CAL mode, should be set to '0' or the value which
 * matches the CAL mode register setting in the DRAM.
 * 
 * If the PHY can add the latency for CAL mode, this should be set to '0'.
 * Valid Range: 0, 3, 4, 5, 6, and 8
 * Programming Mode: Quasi-dynamic Group 2 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG1 . DFI_T_CMD_LAT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_CMD_LAT(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_CMD_LAT     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG1_DFI_T_CMD_LAT(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/** 
 * \brief DFI Low Power Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFILPCFG0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x66)

/** 
 * \brief
 * Enables DFI Low Power interface handshaking during Power Down
 * Entry/Exit.
 *   - 0 - Disabled 
 *   - 1 - Enabled
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_LP_EN_PD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_PD  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Value in DFI clock cycles to drive on dfi_lp_wakeup signal when Power
 * Down mode is entered. 
 * Determines the DFI's tlp_wakeup time:
 *   - 0x0 - 16 cycles
 *   - 0x1 - 32 cycles
 *   - 0x2 - 64 cycles
 *   - 0x3 - 128 cycles
 *   - 0x4 - 256 cycles
 *   - 0x5 - 512 cycles
 *   - 0x6 - 1024 cycles
 *   - 0x7 - 2048 cycles
 *   - 0x8 - 4096 cycles
 *   - 0x9 - 8192 cycles
 *   - 0xA - 16384 cycles
 *   - 0xB - 32768 cycles
 *   - 0xC - 65536 cycles
 *   - 0xD - 131072 cycles
 *   - 0xE - 262144 cycles
 *   - 0xF - Unlimited
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_LP_WAKEUP_PD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_PD(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_PD     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Enables DFI Low Power interface handshaking during Self Refresh
 * Entry/Exit.
 *   - 0 - Disabled 
 *   - 1 - Enabled
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_LP_EN_SR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_SR  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_SR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Value in DFI clpck cycles to drive on dfi_lp_wakeup signal when Self
 * Refresh mode is entered. 
 * Determines the DFI's tlp_wakeup time:
 *   - 0x0 - 16 cycles
 *   - 0x1 - 32 cycles
 *   - 0x2 - 64 cycles
 *   - 0x3 - 128 cycles
 *   - 0x4 - 256 cycles
 *   - 0x5 - 512 cycles
 *   - 0x6 - 1024 cycles
 *   - 0x7 - 2048 cycles
 *   - 0x8 - 4096 cycles
 *   - 0x9 - 8192 cycles
 *   - 0xA - 16384 cycles
 *   - 0xB - 32768 cycles
 *   - 0xC - 65536 cycles
 *   - 0xD - 131072 cycles
 *   - 0xE - 262144 cycles
 *   - 0xF - Unlimited
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_LP_WAKEUP_SR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_SR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_SR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_SR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Enables DFI Low Power interface handshaking during Deep Power Down
 * Entry/Exit.
 *   - 0 - Disabled 
 *   - 1 - Enabled 
 * This is only present for designs supporting mDDR or LPDDR2/LPDDR3
 * devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_LP_EN_DPD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_DPD(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_DPD  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_EN_DPD(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Value in DFI clock cycles to drive on dfi_lp_wakeup signal when Deep
 * Power Down mode is entered. 
 * Determines the DFI's tlp_wakeup time:
 *   - 0x0 - 16 cycles
 *   - 0x1 - 32 cycles
 *   - 0x2 - 64 cycles
 *   - 0x3 - 128 cycles
 *   - 0x4 - 256 cycles
 *   - 0x5 - 512 cycles
 *   - 0x6 - 1024 cycles
 *   - 0x7 - 2048 cycles
 *   - 0x8 - 4096 cycles
 *   - 0x9 - 8192 cycles
 *   - 0xA - 16384 cycles
 *   - 0xB - 32768 cycles
 *   - 0xC - 65536 cycles
 *   - 0xD - 131072 cycles
 *   - 0xE - 262144 cycles
 *   - 0xF - Unlimited
 * This is only present for designs supporting mDDR or LPDDR2/LPDDR3
 * devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_LP_WAKEUP_DPD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_DPD(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_DPD     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_LP_WAKEUP_DPD(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Setting in DFI clock cycles for DFI's tlp_resp time. 
 * Same value is used for both Power Down, Self Refresh, Deep Power Down
 * and Maximum Power Saving modes. 
 * DFI 2.1 specification onwards, recommends using a fixed value of 7
 * always.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0 . DFI_TLP_RESP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_TLP_RESP(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_TLP_RESP     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG0_DFI_TLP_RESP(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/** 
 * \brief DFI Low Power Configuration Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFILPCFG1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x67)

/** 
 * \brief
 * Enables DFI Low Power interface handshaking during Maximum Power Saving
 * Mode Entry/Exit.
 *   - 0 - Disabled 
 *   - 1 - Enabled
 * This is only present for designs supporting DDR4 devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1 . DFI_LP_EN_MPSM
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1_DFI_LP_EN_MPSM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1_DFI_LP_EN_MPSM  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1_DFI_LP_EN_MPSM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Value in DFI clock cycles to drive on dfi_lp_wakeup signal when Maximum
 * Power Saving Mode is entered. 
 * Determines the DFI's tlp_wakeup time:
 *   - 0x0 - 16 cycles
 *   - 0x1 - 32 cycles
 *   - 0x2 - 64 cycles
 *   - 0x3 - 128 cycles
 *   - 0x4 - 256 cycles
 *   - 0x5 - 512 cycles
 *   - 0x6 - 1024 cycles
 *   - 0x7 - 2048 cycles
 *   - 0x8 - 4096 cycles
 *   - 0x9 - 8192 cycles
 *   - 0xA - 16384 cycles
 *   - 0xB - 32768 cycles
 *   - 0xC - 65536 cycles
 *   - 0xD - 131072 cycles
 *   - 0xE - 262144 cycles
 *   - 0xF - Unlimited
 * This is only present for designs supporting DDR4 devices.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1 . DFI_LP_WAKEUP_MPSM
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1_DFI_LP_WAKEUP_MPSM(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1_DFI_LP_WAKEUP_MPSM     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFILPCFG1_DFI_LP_WAKEUP_MPSM(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief DFI Update Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIUPD0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x68)

/** 
 * \brief
 * Specifies the minimum number of DFI clock cycles that the
 * dfi_ctrlupd_req signal must be asserted. The uMCTL2 expects the PHY to
 * respond within this time.  If the PHY does not respond, the uMCTL2 will
 * de-assert dfi_ctrlupd_req after dfi_t_ctrlup_min + 2 cycles.  Lowest
 * value to assign to this variable is 0x3.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0 . DFI_T_CTRLUP_MIN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DFI_T_CTRLUP_MIN(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DFI_T_CTRLUP_MIN     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DFI_T_CTRLUP_MIN(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * Specifies the maximum number of DFI clock cycles that the
 * dfi_ctrlupd_req signal can assert. Lowest value to assign to this
 * variable is 0x40.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0 . DFI_T_CTRLUP_MAX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DFI_T_CTRLUP_MAX(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DFI_T_CTRLUP_MAX     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DFI_T_CTRLUP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Selects dfi_ctrlupd_req requirements at SRX:
 *   - 0 : send ctrlupd after SRX
 *   - 1 : send ctrlupd before SRX
 *   If DFIUPD0.dis_auto_ctrlupd_srx=1, this register has no impact,
 * because no dfi_ctrlupd_req will be issued when SRX.
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0 . CTRLUPD_PRE_SRX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_CTRLUPD_PRE_SRX(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_CTRLUPD_PRE_SRX  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_CTRLUPD_PRE_SRX(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * When '1', disable the automatic dfi_ctrlupd_req generation by the uMCTL2
 * at self-refresh exit.
 * When '0', uMCTL2 issues a dfi_ctrlupd_req before or after exiting
 * self-refresh,  depending on DFIUPD0.ctrlupd_pre_srx.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0 . DIS_AUTO_CTRLUPD_SRX
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DIS_AUTO_CTRLUPD_SRX(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DIS_AUTO_CTRLUPD_SRX  VTSS_BIT(30)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DIS_AUTO_CTRLUPD_SRX(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * When '1', disable the automatic dfi_ctrlupd_req generation by the
 * uMCTL2. The core must issue the dfi_ctrlupd_req signal using register
 * DBGCMD.ctrlupd.
 * When '0', uMCTL2 issues dfi_ctrlupd_req periodically.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0 . DIS_AUTO_CTRLUPD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DIS_AUTO_CTRLUPD(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DIS_AUTO_CTRLUPD  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD0_DIS_AUTO_CTRLUPD(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/** 
 * \brief DFI Update Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIUPD1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x69)

/** 
 * \brief
 * This is the maximum amount of time between uMCTL2 initiated DFI update
 * requests. This timer resets with each update request; when the timer
 * expires dfi_ctrlupd_req is sent and traffic is blocked until the
 * dfi_ctrlupd_ackx is received. PHY can use this idle time to recalibrate
 * the delay lines to the DLLs. The DFI controller update is also used to
 * reset PHY FIFO pointers in case of data capture errors. Updates are
 * required to maintain calibration over PVT, but frequent updates may
 * impact performance. Minimum allowed value for this field is 1.
 * Note: Value programmed for DFIUPD1.dfi_t_ctrlupd_interval_max_x1024 must
 * be greater than DFIUPD1.dfi_t_ctrlupd_interval_min_x1024.
 * Unit: 1024 DFI clock cycles
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1 . DFI_T_CTRLUPD_INTERVAL_MAX_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * This is the minimum amount of time between uMCTL2 initiated DFI update
 * requests (which is executed whenever the uMCTL2 is idle). Set this
 * number higher to reduce the frequency of update requests, which can have
 * a small impact on the latency of the first read request when the uMCTL2
 * is idle. Minimum allowed value for this field is 1.
 * Unit: 1024 DFI clock cycles
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1 . DFI_T_CTRLUPD_INTERVAL_MIN_X1024
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


/** 
 * \brief DFI Update Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIUPD2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6a)

/** 
 * \brief
 * Enables the support for acknowledging PHY-initiated updates:
 *     - 0 - Disabled
 *     - 1 - Enabled
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIUPD2 . DFI_PHYUPD_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIUPD2_DFI_PHYUPD_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIUPD2_DFI_PHYUPD_EN  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIUPD2_DFI_PHYUPD_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/** 
 * \brief DFI Miscellaneous Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIMISC
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIMISC  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6c)

/** 
 * \brief
 * PHY initialization complete enable signal.
 * When asserted the dfi_init_complete signal can be used to trigger SDRAM
 * initialisation
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIMISC . DFI_INIT_COMPLETE_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_INIT_COMPLETE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_INIT_COMPLETE_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_INIT_COMPLETE_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * DBI implemented in DDRC or PHY.
 *   - 0 - DDRC implements DBI functionality.
 *   - 1 - PHY implements DBI functionality.
 *   Present only in designs configured to support DDR4 and LPDDR4.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIMISC . PHY_DBI_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_PHY_DBI_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_PHY_DBI_MODE  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_PHY_DBI_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables support of ctl_idle signal, which is non-DFI related pin
 * specific to certain Synopsys PHYs. See signal description of ctl_idle
 * signal for further details of ctl_idle functionality. 
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIMISC . CTL_IDLE_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_CTL_IDLE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_CTL_IDLE_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_CTL_IDLE_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * PHY init start request signal.When asserted it triggers the PHY init
 * start request
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIMISC . DFI_INIT_START
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_INIT_START(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_INIT_START  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_INIT_START(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Indicates the operating frequency of the system. The number of supported
 * frequencies and the mapping of signal values to clock frequencies are
 * defined by the PHY.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIMISC . DFI_FREQUENCY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_FREQUENCY(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_FREQUENCY     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIMISC_DFI_FREQUENCY(x)  VTSS_EXTRACT_BITFIELD(x,8,5)


/** 
 * \brief DFI Timing Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFITMG3
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG3  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6e)

/** 
 * \brief
 * The delay from dfi_geardown_en assertion to the time of the PHY being
 * ready to receive commands.
 * Refer to PHY specification for correct value.
 * When the controller is operating in 1:2 frequency ratio mode, program
 * this to (tgeardown_delay/2) and round it up to the next integer value.
 * Unit: Clocks
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFITMG3 . DFI_T_GEARDOWN_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFITMG3_DFI_T_GEARDOWN_DELAY(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFITMG3_DFI_T_GEARDOWN_DELAY     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFITMG3_DFI_T_GEARDOWN_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief DFI Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFISTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFISTAT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x6f)

/** 
 * \brief
 * The status flag register which announces when the DFI initialization has
 * been completed. The DFI INIT triggered by dfi_init_start signal and then
 * the dfi_init_complete flag is polled to know when the initialization is
 * done.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFISTAT . DFI_INIT_COMPLETE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFISTAT_DFI_INIT_COMPLETE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFISTAT_DFI_INIT_COMPLETE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFISTAT_DFI_INIT_COMPLETE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Stores the value of the dfi_lp_ack input to the controller.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFISTAT . DFI_LP_ACK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFISTAT_DFI_LP_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFISTAT_DFI_LP_ACK  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFISTAT_DFI_LP_ACK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief DM/DBI Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBICTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DBICTL   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x70)

/** 
 * \brief
 * DM enable signal in DDRC.
 *   - 0 - DM is disabled.
 *   - 1 - DM is enabled.
 * This signal must be set the same logical value as DRAM's mode register.
 *   - DDR4:   Set this to same value as MR5 bit A10. When x4 devices are
 * used, this signal must be set to 0.
 *   - LPDDR4: Set this to inverted value of MR13[5] which is opposite
 * polarity from this signal
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBICTL . DM_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBICTL_DM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBICTL_DM_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBICTL_DM_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Write DBI enable signal in DDRC.
 *   - 0 - Write DBI is disabled.
 *   - 1 - Write DBI is enabled.
 * This signal must be set the same value as DRAM's mode register.
 *   - DDR4:   MR5 bit A11. When x4 devices are used, this signal must be
 * set to 0.
 *   - LPDDR4: MR3[7]
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBICTL . WR_DBI_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBICTL_WR_DBI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBICTL_WR_DBI_EN  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBICTL_WR_DBI_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Read DBI enable signal in DDRC.
 *   - 0 - Read DBI is disabled.
 *   - 1 - Read DBI is enabled.
 * This signal must be set the same value as DRAM's mode register.
 *   - DDR4:   MR5 bit A12. When x4 devices are used, this signal must be
 * set to 0.
 *   - LPDDR4: MR3[6]
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBICTL . RD_DBI_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBICTL_RD_DBI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBICTL_RD_DBI_EN  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBICTL_RD_DBI_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief DFI PHY Master
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DFIPHYMSTR
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIPHYMSTR  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x71)

/** 
 * \brief
 * Enables the PHY Master Interface:
 *     - 0 - Disabled
 *     - 1 - Enabled
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DFIPHYMSTR . DFI_PHYMSTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DFIPHYMSTR_DFI_PHYMSTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DFIPHYMSTR_DFI_PHYMSTR_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DFIPHYMSTR_DFI_PHYMSTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Address Map Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x80)

/** 
 * \brief
 * Selects the HIF address bit used as rank address bit 0.
 * Valid Range: 0 to 29, and 31
 * Internal Base: 6
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then rank address bit 0 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP0 . ADDRMAP_CS_BIT0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP0_ADDRMAP_CS_BIT0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP0_ADDRMAP_CS_BIT0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP0_ADDRMAP_CS_BIT0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Address Map Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x81)

/** 
 * \brief
 * Selects the HIF address bits used as bank address bit 0.
 * Valid Range: 0 to 32 and 63
 * Internal Base: 2
 * The selected HIF address bit for each of the bank address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank address bit 0 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1 . ADDRMAP_BANK_B0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Selects the HIF address bits used as bank address bit 1.
 * Valid Range: 0 to 32 and 63
 * Internal Base: 3
 * The selected HIF address bit for each of the bank address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank address bit 1 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1 . ADDRMAP_BANK_B1
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B1(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B1     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B1(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Selects the HIF address bit used as bank address bit 2.
 * Valid Range: 0 to 31 and 63
 * Internal Base: 4
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 63 and then bank address bit 2 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1 . ADDRMAP_BANK_B2
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B2(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B2     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP1_ADDRMAP_BANK_B2(x)  VTSS_EXTRACT_BITFIELD(x,16,6)


/** 
 * \brief Address Map Register 2
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x82)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 2.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 3.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 4.
 * Valid Range: 0 to 7
 * Internal Base: 2
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field. 
 * 
 * Note, if UMCTL2_INCL_ARB=1 and MEMC_BURST_LENGTH=8, it is required to
 * program this to 0 unless:
 *   - in Half or Quarter bus width (MSTR.data_bus_width!=00) and
 *   - PCCFG.bl_exp_mode==1 and either
 *   - In DDR4	 and ADDRMAP8.addrmap_bg_b0==0 or
 *   - In LPDDR4 and ADDRMAP1.addrmap_bank_b0==0
 * 
 * 
 * If UMCTL2_INCL_ARB=1 and MEMC_BURST_LENGTH=16, it is required to program
 * this to 0 unless:
 *   - in Half or Quarter bus width (MSTR.data_bus_width!=00) and 
 *   - PCCFG.bl_exp_mode==1 and
 *   - In DDR4 and ADDRMAP8.addrmap_bg_b0==0
 * 
 * Otherwise, if MEMC_BURST_LENGTH=8 and Full Bus Width
 * (MSTR.data_bus_width==00), it is recommended to program this to 0 so
 * that HIF[2] maps to column address bit 2.
 * 
 * If MEMC_BURST_LENGTH=16 and Full Bus Width (MSTR.data_bus_width==00), it
 * is recommended to program this to 0 so that HIF[2] maps to column
 * address bit 2.
 * 
 * If MEMC_BURST_LENGTH=16 and Half Bus Width (MSTR.data_bus_width==01), it
 * is recommended to program this to 0 so that HIF[2] maps to column
 * address bit 3.
 * 
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2 . ADDRMAP_COL_B2
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 3. 
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 4.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 5.
 * Valid Range: 0 to 7
 * Internal Base: 3
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * 
 * 
 * Note, if UMCTL2_INCL_ARB=1, MEMC_BURST_LENGTH=16, Full bus width
 * (MSTR.data_bus_width=00) and BL16 (MSTR.burst_rdwr=1000), it is
 * recommended to program this to 0.
 * 
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2 . ADDRMAP_COL_B3
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 4.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 5.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 6.
 * Valid Range: 0 to 7, and 15
 * Internal Base: 4
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field. If unused, set to 15 and then this column
 * address bit is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2 . ADDRMAP_COL_B4
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B4(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B4     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B4(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 5.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 6.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 7 .
 * Valid Range: 0 to 7, and 15
 * Internal Base: 5
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field. If unused, set to 15 and then this column
 * address bit is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2 . ADDRMAP_COL_B5
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B5(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B5     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP2_ADDRMAP_COL_B5(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief Address Map Register 3
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP3
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x83)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 6.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 7.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 8.
 * Valid Range: 0 to 7, and 15
 * Internal Base: 6
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field. If unused, set to 15 and then this column
 * address bit is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3 . ADDRMAP_COL_B6
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B6(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B6     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B6(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 7.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 8.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 9.
 * Valid Range: 0 to 7, x, and 31. x indicate a valid value in inline ECC
 * configuration.
 * Internal Base: 7 
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field. If unused, set to 31 and then this column
 * address bit is set to 0.
 * 
 *   In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled
 * (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the
 * highest 3 valid HIF address bits.
 * 
 *   If column bit 7 is the third highest column address bit, it must map
 * to the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * 
 *   if it is unused, set to 31.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3 . ADDRMAP_COL_B7
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B7(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B7     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B7(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 8.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 9.
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 11 (10 in LPDDR2/LPDDR3 mode).
 * Valid Range: 0 to 7, x, and 31. x indicate a valid value in inline ECC
 * configuration.
 * Internal Base: 8
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * 
 *   In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled
 * (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the
 * highest 3 valid HIF address bits.
 * 
 *   If column bit 8 is the second highest column address bit, it must map
 * to the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * 
 *   If column bit 8 is the third highest column address bit, it must map
 * to the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * 
 *   if it is unused, set to 31.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3 . ADDRMAP_COL_B8
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B8(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B8     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B8(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 9.
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 11 (10 in LPDDR2/LPDDR3 mode).
 * 
 *   - Quarter bus width mode: Selects the HIF address bit used as column
 * address bit 13 (11 in LPDDR2/LPDDR3 mode).
 * Valid Range: 0 to 7, x, and 31. x indicate a valid value in inline ECC
 * configuration.
 * Internal Base: 9
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * 
 *   In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled
 * (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the
 * highest 3 valid HIF address bits.
 * 
 *   If column bit 9 is the highest column address bit, it must map to the
 * highest valid HIF address bit. (x = the highest valid HIF address bit -
 * internal base)
 * 
 *   If column bit 9 is the second highest column address bit, it must map
 * to the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * 
 *   If column bit 9 is the third highest column address bit, it must map
 * to the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * 
 *   if it is unused, set to 31.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3 . ADDRMAP_COL_B9
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B9(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B9     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP3_ADDRMAP_COL_B9(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/** 
 * \brief Address Map Register 4
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP4
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x84)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 11 (10 in LPDDR2/LPDDR3 mode).
 * 
 *   - Half bus width mode: Selects the HIF address bit used as column
 * address bit 13 (11 in LPDDR2/LPDDR3 mode).
 * 
 *   - Quarter bus width mode: UNUSED. To make it unused, this must be tied
 * to 4'hF.
 * Valid Range: 0 to 7, x, and 31. x indicate a valid value in inline ECC
 * configuration.
 * Internal Base: 10
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then this column address bit is set to 0. 
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * 
 *   In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled
 * (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the
 * highest 3 valid HIF address bits.
 * 
 *   If column bit 10 is the highest column address bit, it must map to the
 * highest valid HIF address bit. (x = the highest valid HIF address bit -
 * internal base)
 * 
 *   If column bit 10 is the second highest column address bit, it must map
 * to the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * 
 *   If column bit 10 is the third highest column address bit, it must map
 * to the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * 
 *   if it is unused, set to 31.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4 . ADDRMAP_COL_B10
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4_ADDRMAP_COL_B10(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4_ADDRMAP_COL_B10     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4_ADDRMAP_COL_B10(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * 
 *   - Full bus width mode: Selects the HIF address bit used as column
 * address bit 13 (11 in LPDDR2/LPDDR3 mode).
 * 
 *   - Half bus width mode: Unused. To make it unused, this should be tied
 * to 4'hF.
 * 
 *   - Quarter bus width mode: Unused. To make it unused, this must be tied
 * to 4'hF.
 * Valid Range: 0 to 7, x, and 31. x indicate a valid value in inline ECC
 * configuration.
 * Internal Base: 11
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 31 and then this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is
 * reserved for indicating auto-precharge, and hence no source address bit
 * can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto-precharge in the CA
 * bus and hence column bit 10 is used.
 * 
 *   In Inline ECC configuration (MEMC_INLINE_ECC=1) and ECC is enabled
 * (ECCCFG0.ecc_mode>0), the highest 3 column address bits must map to the
 * highest 3 valid HIF address bits.
 * 
 *   If column bit 11 is the highest column address bit, it must map to the
 * highest valid HIF address bit. (x = the highest valid HIF address bit -
 * internal base)
 * 
 *   If column bit 11 is the second highest column address bit, it must map
 * to the second highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 1 - internal base)
 * 
 *   If column bit 11 is the third highest column address bit, it must map
 * to the third highest valid HIF address bit. (x = the highest valid HIF
 * address bit - 2 - internal base)
 * 
 *   if it is unused, set to 31.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4 . ADDRMAP_COL_B11
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4_ADDRMAP_COL_B11(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4_ADDRMAP_COL_B11     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP4_ADDRMAP_COL_B11(x)  VTSS_EXTRACT_BITFIELD(x,8,5)


/** 
 * \brief Address Map Register 5
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP5
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x85)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 0.
 * Valid Range: 0 to 11
 * Internal Base: 6
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5 . ADDRMAP_ROW_B0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 1.
 * Valid Range: 0 to 11
 * Internal Base: 7
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5 . ADDRMAP_ROW_B1
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B1(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B1     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B1(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bits 2 to 10.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 8 (for row address bit 2), 9 (for row address bit 3), 10
 * (for row address bit 4) etc increasing to 16 (for row address bit 10)
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. When
 * value 15 is used the values of row address bits 2 to 10 are defined by
 * registers ADDRMAP9, ADDRMAP10, ADDRMAP11.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5 . ADDRMAP_ROW_B2_10
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B2_10(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B2_10     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B2_10(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 11.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 17
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 11 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5 . ADDRMAP_ROW_B11
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B11(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B11     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP5_ADDRMAP_ROW_B11(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief Address Map Register 6
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP6
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x86)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 12.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 18
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 12 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6 . ADDRMAP_ROW_B12
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B12(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B12     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B12(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 13.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 19
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 13 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6 . ADDRMAP_ROW_B13
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B13(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B13     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B13(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 14.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 20
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 14 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6 . ADDRMAP_ROW_B14
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B14(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B14     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B14(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 15.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 21
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 15 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6 . ADDRMAP_ROW_B15
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B15(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B15     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_ADDRMAP_ROW_B15(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * 
 *  Set this to 1 if there is an LPDDR3 SDRAM 6Gb or 12Gb device in use.
 *  - 1 - LPDDR3 SDRAM 6Gb/12Gb device in use. Every address having
 * row[14:13]==2'b11 is considered as invalid
 *  - 0 - non-LPDDR3 6Gb/12Gb device in use. All addresses are valid
 * Present only in designs configured to support LPDDR3.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6 . LPDDR3_6GB_12GB
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_LPDDR3_6GB_12GB(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_LPDDR3_6GB_12GB  VTSS_BIT(31)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP6_LPDDR3_6GB_12GB(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/** 
 * \brief Address Map Register 7
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP7
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x87)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 16.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 22
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 16 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7 . ADDRMAP_ROW_B16
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7_ADDRMAP_ROW_B16(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7_ADDRMAP_ROW_B16     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7_ADDRMAP_ROW_B16(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Selects the HIF address bit used as row address bit 17.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 23
 * The selected HIF address bit is determined by adding the internal base
 * to the value of this field.
 * If unused, set to 15 and then row address bit 17 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7 . ADDRMAP_ROW_B17
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7_ADDRMAP_ROW_B17(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7_ADDRMAP_ROW_B17     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP7_ADDRMAP_ROW_B17(x)  VTSS_EXTRACT_BITFIELD(x,8,4)


/** 
 * \brief Address Map Register 8
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP8
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x88)

/** 
 * \brief
 * Selects the HIF address bits used as bank group address bit 0.
 * Valid Range: 0 to 32 and 63
 * Internal Base: 2
 * The selected HIF address bit for each of the bank group address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank group address bit 0 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8 . ADDRMAP_BG_B0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8_ADDRMAP_BG_B0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8_ADDRMAP_BG_B0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8_ADDRMAP_BG_B0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Selects the HIF address bits used as bank group address bit 1.
 * Valid Range: 0 to 32, and 63
 * Internal Base: 3
 * The selected HIF address bit for each of the bank group address bits is
 * determined by adding the internal base to the value of this field.
 * If unused, set to 63 and then bank group address bit 1 is set to 0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8 . ADDRMAP_BG_B1
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8_ADDRMAP_BG_B1(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8_ADDRMAP_BG_B1     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP8_ADDRMAP_BG_B1(x)  VTSS_EXTRACT_BITFIELD(x,8,6)


/** 
 * \brief Address Map Register 9
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP9
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x89)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 2.
 * Valid Range: 0 to 11
 * Internal Base: 8
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9 . ADDRMAP_ROW_B2
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 3.
 * Valid Range: 0 to 11
 * Internal Base: 9
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9 . ADDRMAP_ROW_B3
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B3(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B3     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B3(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 4.
 * Valid Range: 0 to 11
 * Internal Base: 10
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9 . ADDRMAP_ROW_B4
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B4(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B4     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B4(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 5.
 * Valid Range: 0 to 11
 * Internal Base: 11
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9 . ADDRMAP_ROW_B5
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B5(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B5     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP9_ADDRMAP_ROW_B5(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief Address Map Register 10
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP10
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x8a)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 6.
 * Valid Range: 0 to 11
 * Internal Base: 12
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10 . ADDRMAP_ROW_B6
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B6(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B6     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B6(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 7.
 * Valid Range: 0 to 11
 * Internal Base: 13
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10 . ADDRMAP_ROW_B7
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B7(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B7     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B7(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 8.
 * Valid Range: 0 to 11
 * Internal Base: 14
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10 . ADDRMAP_ROW_B8
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B8(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B8     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B8(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 9.
 * Valid Range: 0 to 11
 * Internal Base: 15
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10 . ADDRMAP_ROW_B9
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B9(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B9     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP10_ADDRMAP_ROW_B9(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief Address Map Register 11
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADDRMAP11
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP11  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x8b)

/** 
 * \brief
 * Selects the HIF address bits used as row address bit 10.
 * Valid Range: 0 to 11
 * Internal Base: 16
 * The selected HIF address bit for each of the row address bits is
 * determined by adding the internal base to the value of this field. This
 * register field is used only when ADDRMAP5.addrmap_row_b2_10 is set to
 * value 15.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP11 . ADDRMAP_ROW_B10
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP11_ADDRMAP_ROW_B10(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP11_ADDRMAP_ROW_B10     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADDRMAP11_ADDRMAP_ROW_B10(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief ODT Configuration Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ODTCFG
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTCFG   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x90)

/** 
 * \brief
 * 
 * The delay, in DFI PHY clock cycles, from issuing a read command to
 * setting ODT values associated with that command. ODT setting must remain
 * constant for the entire time that DQS is driven by the uMCTL2.
 * 
 * Recommended values:
 * 
 *  DDR2:
 *  - CL + AL - 4 (not DDR2-1066),  CL + AL - 5 (DDR2-1066)
 * 
 *    If (CL + AL - 4 < 0),  uMCTL2 does not support ODT for read
 * operation.
 * 
 *  DDR3:
 *  - CL - CWL
 *  DDR4:
 *  - CL - CWL - RD_PREAMBLE + WR_PREAMBLE + DFITMG1.dfi_t_cmd_lat (to
 * adjust for CAL mode)
 * 
 *    WR_PREAMBLE = 1 (1tCK write preamble),  2 (2tCK write preamble)
 * 
 *    RD_PREAMBLE = 1 (1tCK write preamble),  2 (2tCK write preamble)
 * 
 *    If (CL - CWL - RD_PREAMBLE + WR_PREAMBLE) < 0,  uMCTL2 does not
 * support ODT for read operation.
 * 
 *  LPDDR3:
 *  - RL + RD(tDQSCK(min)/tCK) - 1 - RU(tODTon(max)/tCK)
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTCFG . RD_ODT_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_RD_ODT_DELAY(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_RD_ODT_DELAY     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_RD_ODT_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * 
 * DFI PHY clock cycles to hold ODT for a read command. The minimum
 * supported value is 2.
 * 
 * Recommended values:
 * 
 *  DDR2:
 *  - BL8: 0x6 (not DDR2-1066),  0x7 (DDR2-1066)
 *  - BL4: 0x4 (not DDR2-1066),  0x5 (DDR2-1066)
 *  DDR3:
 *  - BL8 - 0x6
 *  DDR4:
 *  - BL8: 5 + RD_PREAMBLE
 * 
 *    RD_PREAMBLE = 1 (1tCK write preamble),  2 (2tCK write preamble)
 * 
 *  LPDDR3:
 *  - BL8:  5 + RU(tDQSCK(max)/tCK) - RD(tDQSCK(min)/tCK) +
 * RU(tODTon(max)/tCK)
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTCFG . RD_ODT_HOLD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_RD_ODT_HOLD(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_RD_ODT_HOLD     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_RD_ODT_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * 
 * The delay, in DFI PHY clock cycles, from issuing a write command to
 * setting ODT values associated with that command. ODT setting must remain
 * constant for the entire time that DQS is driven by the uMCTL2.
 * 
 * Recommended values:
 * 
 *  DDR2:
 *  - CWL + AL - 3 (DDR2-400/533/667),	CWL + AL - 4 (DDR2-800),  CWL + AL
 * - 5 (DDR2-1066)
 * 
 *    If (CWL + AL - 3	< 0),  uMCTL2 does not support ODT for write
 * operation.
 * 
 *  DDR3:
 *  - 0x0
 *  DDR4:
 *  - DFITMG1.dfi_t_cmd_lat (to adjust for CAL mode) 
 *  LPDDR3:
 *  - WL - 1 - RU(tODTon(max)/tCK))
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTCFG . WR_ODT_DELAY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_WR_ODT_DELAY(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_WR_ODT_DELAY     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_WR_ODT_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * 
 * DFI PHY clock cycles to hold ODT for a write command. The minimum
 * supported value is 2.
 * 
 * Recommended values:
 * 
 *  DDR2:
 *  - BL8:  0x5 (DDR2-400/533/667),  0x6 (DDR2-800),  0x7 (DDR2-1066)
 *  - BL4:  0x3 (DDR2-400/533/667),  0x4 (DDR2-800),  0x5 (DDR2-1066)
 *  DDR3:
 *  - BL8: 0x6
 *  DDR4: 
 *  - BL8: 5 + WR_PREAMBLE + CRC_MODE
 * 
 *    WR_PREAMBLE = 1 (1tCK write preamble),  2 (2tCK write preamble)
 * 
 *    CRC_MODE = 0 (not CRC mode),  1 (CRC mode)
 * 
 *  LPDDR3:
 *  - BL8: 7 + RU(tODTon(max)/tCK)
 * Programming Mode: Quasi-dynamic Group 1 and Group 4
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTCFG . WR_ODT_HOLD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_WR_ODT_HOLD(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_WR_ODT_HOLD     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTCFG_WR_ODT_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,24,4)


/** 
 * \brief ODT/Rank Map Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ODTMAP
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTMAP   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x91)

/** 
 * \brief
 * Indicates which remote ODTs must be turned on during a write to rank 0.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTMAP . RANK0_WR_ODT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK0_WR_ODT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK0_WR_ODT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK0_WR_ODT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Indicates which remote ODTs must be turned on during a read from rank 0.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTMAP . RANK0_RD_ODT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK0_RD_ODT(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK0_RD_ODT     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK0_RD_ODT(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Indicates which remote ODTs must be turned on during a write to rank 1.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Present only in configurations that have 2 or more ranks
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTMAP . RANK1_WR_ODT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK1_WR_ODT(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK1_WR_ODT     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK1_WR_ODT(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Indicates which remote ODTs must be turned on during a read from rank 1.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by
 * setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the
 * LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Present only in configurations that have 2 or more ranks
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ODTMAP . RANK1_RD_ODT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK1_RD_ODT(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK1_RD_ODT     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ODTMAP_RANK1_RD_ODT(x)  VTSS_EXTRACT_BITFIELD(x,12,2)


/** 
 * \brief Scheduler Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SCHED
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x94)

/** 
 * \brief
 * Active low signal. When asserted ('0'), all incoming transactions are
 * forced to low priority. This implies that all High Priority Read (HPR)
 * and Variable Priority Read commands (VPR) will be treated as Low
 * Priority Read (LPR) commands. On the write side, all Variable Priority
 * Write (VPW) commands will be treated as Normal Priority Write (NPW)
 * commands. Forcing the incoming transactions to low priority implicitly
 * turns off Bypass path for read commands.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED . FORCE_LOW_PRI_N
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED_FORCE_LOW_PRI_N(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED_FORCE_LOW_PRI_N  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED_FORCE_LOW_PRI_N(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * If set then the bank selector prefers writes over reads.
 * FOR DEBUG ONLY.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED . PREFER_WRITE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED_PREFER_WRITE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED_PREFER_WRITE  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED_PREFER_WRITE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If true, bank is kept open only while there are page hit transactions
 * available in the CAM to that bank. The last read or write command in the
 * CAM with a bank and page hit will be executed with auto-precharge if
 * SCHED1.pageclose_timer=0. Even if this register set to 1 and
 * SCHED1.pageclose_timer is set to 0, explicit precharge (and not
 * auto-precharge) may be issued in some cases where there is a mode switch
 * between Write and Read or between LPR and HPR. The Read and Write
 * commands that are executed as part of the ECC scrub requests are also
 * executed without auto-precharge.
 * 
 * If false, the bank remains open until there is a need to close it (to
 * open a different page, or for page timeout or refresh timeout) - also
 * known as open page policy. The open page policy can be overridden by
 * setting the per-command-autopre bit on the HIF interface
 * (hif_cmd_autopre).
 * The pageclose feature provids a midway between Open and Close page
 * policies.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED . PAGECLOSE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED_PAGECLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED_PAGECLOSE  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED_PAGECLOSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Number of entries in the low priority transaction store is this value +
 * 1.
 * (MEMC_NO_OF_ENTRY - (SCHED.lpr_num_entries + 1)) is the number of
 * entries available for the high priority transaction store.
 * Setting this to maximum value allocates all entries to low priority
 * transaction store.
 * Setting this to 0 allocates 1 entry to low priority transaction store
 * and the rest to high priority transaction store.
 * Note: In ECC configurations, the numbers of write and low priority read
 * credits issued is one less than in the non-ECC case.  One entry each is
 * reserved in the write and low-priority read CAMs for storing the RMW
 * requests arising out of single bit error correction RMW operation.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED . LPR_NUM_ENTRIES
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED_LPR_NUM_ENTRIES(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED_LPR_NUM_ENTRIES     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED_LPR_NUM_ENTRIES(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * UNUSED
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED . GO2CRITICAL_HYSTERESIS
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED_GO2CRITICAL_HYSTERESIS(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED_GO2CRITICAL_HYSTERESIS     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED_GO2CRITICAL_HYSTERESIS(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * When the preferred transaction store is empty for these many clock
 * cycles, switch to the alternate transaction store if it is non-empty.
 * The read transaction store (both high and low priority) is the default
 * preferred transaction store and the write transaction store is the
 * alternative store.
 * When prefer write over read is set this is reversed.
 * 0x0 is a legal value for this register. When set to 0x0, the transaction
 * store switching will happen immediately when the switching conditions
 * become true.
 * FOR PERFORMANCE ONLY
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED . RDWR_IDLE_GAP
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED_RDWR_IDLE_GAP(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED_RDWR_IDLE_GAP     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED_RDWR_IDLE_GAP(x)  VTSS_EXTRACT_BITFIELD(x,24,7)


/** 
 * \brief Scheduler Control Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SCHED1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED1   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x95)

/** 
 * \brief
 * This field works in conjunction with SCHED.pageclose.
 * It only has meaning if SCHED.pageclose==1.
 * 
 * If SCHED.pageclose==1 and pageclose_timer==0, then an auto-precharge may
 * be scheduled for last read 
 * or write command in the CAM with a bank and page hit. 
 * Note, sometimes an explicit precharge is scheduled instead of the
 * auto-precharge. See SCHED.pageclose for details of when this may happen.
 * 
 * If SCHED.pageclose==1 and pageclose_timer>0, then an auto-precharge is
 * not scheduled for last read
 * or write command in the CAM with a bank and page hit.
 * Instead, a timer is started, with pageclose_timer as the initial value.
 * There is a timer on a per bank basis.
 * The timer decrements unless the next read or write in the CAM to a bank
 * is a page hit.
 * It gets reset to pageclose_timer value if the next read or write in the
 * CAM to a bank is a page hit.
 * Once the timer has reached zero, an explcit precharge will be attempted
 * to be scheduled.
 * 
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SCHED1 . PAGECLOSE_TIMER
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SCHED1_PAGECLOSE_TIMER(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SCHED1_PAGECLOSE_TIMER     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SCHED1_PAGECLOSE_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief High Priority Read CAM Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PERFHPR1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x97)

/** 
 * \brief
 * Number of DFI clocks that the HPR queue can be starved before it goes
 * critical. The minimum valid functional value for this register is 0x1.
 * Programming it to 0x0 will disable the starvation functionality; during
 * normal operation, this function should not be disabled as it will cause
 * excessive latencies.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1 . HPR_MAX_STARVE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1_HPR_MAX_STARVE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1_HPR_MAX_STARVE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1_HPR_MAX_STARVE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * 
 * Number of transactions that are serviced once the HPR queue goes
 * critical is the smaller of:
 *  - (a) This number
 *  - (b) Number of transactions available.  
 *  Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1 . HPR_XACT_RUN_LENGTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1_HPR_XACT_RUN_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1_HPR_XACT_RUN_LENGTH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PERFHPR1_HPR_XACT_RUN_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Low Priority Read CAM Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PERFLPR1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x99)

/** 
 * \brief
 * Number of DFI clocks that the LPR queue can be starved before it goes
 * critical. The minimum valid functional value for this register is 0x1.
 * Programming it to 0x0 will disable the starvation functionality; during
 * normal operation, this function should not be disabled as it will cause
 * excessive latencies.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1 . LPR_MAX_STARVE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1_LPR_MAX_STARVE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1_LPR_MAX_STARVE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1_LPR_MAX_STARVE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * 
 * Number of transactions that are serviced once the LPR queue goes
 * critical is the smaller of:
 *  - (a) This number
 *  - (b) Number of transactions available.
 * Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1 . LPR_XACT_RUN_LENGTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1_LPR_XACT_RUN_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1_LPR_XACT_RUN_LENGTH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PERFLPR1_LPR_XACT_RUN_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Write CAM Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:PERFWR1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFWR1  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x9b)

/** 
 * \brief
 * Number of DFI clocks that the WR queue can be starved before it goes
 * critical. The minimum valid functional value for this register is 0x1.
 * Programming it to 0x0 will disable the starvation functionality; during
 * normal operation, this function should not be disabled as it will cause
 * excessive latencies.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFWR1 . W_MAX_STARVE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PERFWR1_W_MAX_STARVE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PERFWR1_W_MAX_STARVE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PERFWR1_W_MAX_STARVE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * 
 * Number of transactions that are serviced once the WR queue goes critical
 * is the smaller of:
 *  - (a) This number 
 *  - (b) Number of transactions available.
 * Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_PERFWR1 . W_XACT_RUN_LENGTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_PERFWR1_W_XACT_RUN_LENGTH(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_PERFWR1_W_XACT_RUN_LENGTH     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_PERFWR1_W_XACT_RUN_LENGTH(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Debug Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBG0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DBG0     VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc0)

/** 
 * \brief
 * When 1, disable write combine.
 * FOR DEBUG ONLY
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBG0 . DIS_WC
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBG0_DIS_WC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBG0_DIS_WC  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBG0_DIS_WC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When this is set to '0', auto-precharge is disabled for the flushed
 * command in a collision case. Collision cases are write followed by read
 * to same address, read followed by write to same address, or write
 * followed by write to same address with DBG0.dis_wc bit = 1 (where same
 * address comparisons exclude the two address bits representing critical
 * word).
 * FOR DEBUG ONLY.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBG0 . DIS_COLLISION_PAGE_OPT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBG0_DIS_COLLISION_PAGE_OPT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBG0_DIS_COLLISION_PAGE_OPT  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBG0_DIS_COLLISION_PAGE_OPT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief Debug Register 1
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBG1
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DBG1     VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc1)

/** 
 * \brief
 * When 1, uMCTL2 will not de-queue any transactions from the CAM. Bypass
 * is also disabled. All transactions are queued in the CAM. No reads or
 * writes are issued to SDRAM as long as this is asserted.
 * This bit may be used to prevent reads or writes being issued by the
 * uMCTL2, which makes it safe to modify certain register fields associated
 * with reads and writes (see User Guide for details).	After setting this
 * bit, it is strongly recommended to poll DBGCAM.wr_data_pipeline_empty
 * and DBGCAM.rd_data_pipeline_empty, before making changes to any
 * registers which affect reads and writes.  This will ensure that the
 * relevant logic in the DDRC is idle.
 * This bit is intended to be switched on-the-fly.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBG1 . DIS_DQ
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBG1_DIS_DQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBG1_DIS_DQ  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBG1_DIS_DQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * When 1, uMCTL2 asserts the HIF command signal hif_cmd_stall. uMCTL2 will
 * ignore the hif_cmd_valid and all other associated request signals.
 * This bit is intended to be switched on-the-fly.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBG1 . DIS_HIF
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBG1_DIS_HIF(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBG1_DIS_HIF  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBG1_DIS_HIF(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CAM Debug Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGCAM
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc2)

/** 
 * \brief
 * High priority read queue depth
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . DBG_HPR_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_HPR_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_HPR_Q_DEPTH     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_HPR_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * Low priority read queue depth
 * The last entry of Lpr queue is reserved for ECC SCRUB operation. This
 * entry is not included in the calculation of the queue depth.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . DBG_LPR_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_LPR_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_LPR_Q_DEPTH     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_LPR_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Write queue depth
 * The last entry of WR queue is reserved for ECC SCRUB operation. This
 * entry is not included in the calculation of the queue depth.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . DBG_W_Q_DEPTH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_W_Q_DEPTH(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_W_Q_DEPTH     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_W_Q_DEPTH(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Stall
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . DBG_STALL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_STALL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_STALL  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_STALL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * When 1, all the Read command queues and Read data buffers inside DDRC
 * are empty. This register is to be used for debug purpose. 
 * An example use-case scenario: When Controller enters Self-Refresh using
 * the Low-Power entry sequence, Controller is expected to have executed
 * all the commands in its queues and the write and read data drained.
 * Hence this register should be 1 at that time.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . DBG_RD_Q_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_RD_Q_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_RD_Q_EMPTY  VTSS_BIT(25)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_RD_Q_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * When 1, all the Write command queues and Write data buffers inside DDRC
 * are empty. This register is to be used for debug purpose. 
 * An example use-case scenario: When Controller enters Self-Refresh using
 * the Low-Power entry sequence, Controller is expected to have executed
 * all the commands in its queues and the write and read data drained.
 * Hence this register should be 1 at that time.
 * FOR DEBUG ONLY
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . DBG_WR_Q_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_WR_Q_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_WR_Q_EMPTY  VTSS_BIT(26)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_DBG_WR_Q_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * This bit indicates that the read data pipeline on the DFI interface is
 * empty.  This register is intended to be polled at least twice after
 * setting DBG1.dis_dq, to ensure that all remaining commands/data have
 * completed.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . RD_DATA_PIPELINE_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_RD_DATA_PIPELINE_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_RD_DATA_PIPELINE_EMPTY  VTSS_BIT(28)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_RD_DATA_PIPELINE_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * This bit indicates that the write data pipeline on the DFI interface is
 * empty.  This register is intended to be polled at least twice after
 * setting DBG1.dis_dq, to ensure that all remaining commands/data have
 * completed.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCAM . WR_DATA_PIPELINE_EMPTY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_WR_DATA_PIPELINE_EMPTY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_WR_DATA_PIPELINE_EMPTY  VTSS_BIT(29)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCAM_WR_DATA_PIPELINE_EMPTY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)


/** 
 * \brief Command Debug Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGCMD
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCMD   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc3)

/** 
 * \brief
 * 
 * Setting this register bit to 1 indicates to the uMCTL2 to issue a
 * refresh to rank 0. Writing to this bit causes DBGSTAT.rank0_refresh_busy
 * to be set. When DBGSTAT.rank0_refresh_busy is cleared, the command has
 * been stored in uMCTL2. 
 *  For 3DS configuration, refresh is sent to rank index 0. 
 *  This operation can be performed only when RFSHCTL3.dis_auto_refresh=1.
 * It is recommended NOT to set this register bit if in Init or Deep
 * power-down operating modes or Maximum Power Saving Mode.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCMD . RANK0_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_RANK0_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_RANK0_REFRESH  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_RANK0_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 
 * Setting this register bit to 1 indicates to the uMCTL2 to issue a
 * refresh to rank 1. Writing to this bit causes DBGSTAT.rank1_refresh_busy
 * to be set. When DBGSTAT.rank1_refresh_busy is cleared, the command has
 * been stored in uMCTL2. 
 *  For 3DS configuration, refresh is sent to rank index 1. 
 *  This operation can be performed only when RFSHCTL3.dis_auto_refresh=1.
 * It is recommended NOT to set this register bit if in Init or Deep
 * power-down operating modes or Maximum Power Saving Mode.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCMD . RANK1_REFRESH
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_RANK1_REFRESH(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_RANK1_REFRESH  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_RANK1_REFRESH(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * 
 * Setting this register bit to 1 indicates to the uMCTL2 to issue a ZQCS
 * (ZQ calibration short)/MPC(ZQ calibration) command to the SDRAM.  When
 * this request is stored in the uMCTL2, the bit is automatically cleared.
 * This operation can be performed only when ZQCTL0.dis_auto_zq=1. It is
 * recommended NOT to set this register bit if in Init operating mode. This
 * register bit is ignored when in Self-Refresh(except LPDDR4) and
 * SR-Powerdown(LPDDR4) and Deep power-down operating modes and Maximum
 * Power Saving Mode.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCMD . ZQ_CALIB_SHORT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_ZQ_CALIB_SHORT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_ZQ_CALIB_SHORT  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_ZQ_CALIB_SHORT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * 
 * Setting this register bit to 1 indicates to the uMCTL2 to issue a
 * dfi_ctrlupd_req to the PHY.	When this request is stored in the uMCTL2,
 * the bit is automatically cleared. This operation must only be performed
 * when DFIUPD0.dis_auto_ctrlupd=1.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGCMD . CTRLUPD
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_CTRLUPD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_CTRLUPD  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGCMD_CTRLUPD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief Status Debug Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:DBGSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc4)

/** 
 * \brief
 * SoC core may initiate a rank0_refresh operation (refresh operation to
 * rank 0) only if this signal is low. This signal goes high in the clock
 * after DBGCMD.rank0_refresh is set to one. It goes low when the
 * rank0_refresh operation is stored in the uMCTL2. It is recommended not
 * to perform rank0_refresh operations when this signal is high.
 *  - 0 - Indicates that the SoC core can initiate a rank0_refresh
 * operation
 *  - 1 - Indicates that rank0_refresh operation has not been stored yet in
 * the uMCTL2
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT . RANK0_REFRESH_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_RANK0_REFRESH_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_RANK0_REFRESH_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_RANK0_REFRESH_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * SoC core may initiate a rank1_refresh operation (refresh operation to
 * rank 1) only if this signal is low. This signal goes high in the clock
 * after DBGCMD.rank1_refresh is set to one. It goes low when the
 * rank1_refresh operation is stored in the uMCTL2. It is recommended not
 * to perform rank1_refresh operations when this signal is high.
 *  - 0 - Indicates that the SoC core can initiate a rank1_refresh
 * operation
 *  - 1 - Indicates that rank1_refresh operation has not been stored yet in
 * the uMCTL2
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT . RANK1_REFRESH_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_RANK1_REFRESH_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_RANK1_REFRESH_BUSY  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_RANK1_REFRESH_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * SoC core may initiate a ZQCS (ZQ calibration short) operation only if
 * this signal is low. This signal goes high in the clock after the uMCTL2
 * accepts the ZQCS request. It goes low when the ZQCS operation is
 * initiated in the uMCTL2. It is recommended not to perform ZQCS
 * operations when this signal is high.
 *  - 0 - Indicates that the SoC core can initiate a ZQCS operation
 *  - 1 - Indicates that ZQCS operation has not been initiated yet in the
 * uMCTL2
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT . ZQ_CALIB_SHORT_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_ZQ_CALIB_SHORT_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_ZQ_CALIB_SHORT_BUSY  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_ZQ_CALIB_SHORT_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * SoC core may initiate a ctrlupd operation only if this signal is low.
 * This signal goes high in the clock after the uMCTL2 accepts the ctrlupd
 * request. It goes low when the ctrlupd operation is initiated in the
 * uMCTL2. It is recommended not to perform ctrlupd operations when this
 * signal is high.
 *  - 0 - Indicates that the SoC core can initiate a ctrlupd operation
 *  - 1 - Indicates that ctrlupd operation has not been initiated yet in
 * the uMCTL2
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT . CTRLUPD_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_CTRLUPD_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_CTRLUPD_BUSY  VTSS_BIT(5)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_DBGSTAT_CTRLUPD_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief Software Register Programming Control Enable
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SWCTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_SWCTL    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc8)

/** 
 * \brief
 * Enable quasi-dynamic register programming outside reset. Program
 * register to 0 to enable quasi-dynamic programming. Set back register to
 * 1 once programming is done.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SWCTL . SW_DONE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SWCTL_SW_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SWCTL_SW_DONE  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SWCTL_SW_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Software Register Programming Control Status
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:SWSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_SWSTAT   VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xc9)

/** 
 * \brief
 * Register programming done. This register is the echo of SWCTL.sw_done.
 * Wait for sw_done value 1 to propagate to sw_done_ack at the end of the
 * programming sequence to ensure that the correct registers values are
 * propagated to the destination clock domains.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_SWSTAT . SW_DONE_ACK
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_SWSTAT_SW_DONE_ACK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_SWSTAT_SW_DONE_ACK  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_SWSTAT_SW_DONE_ACK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief AXI Poison Configuration Register. Common for all AXI ports
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:POISONCFG
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdb)

/** 
 * \brief
 * If set to 1, enables SLVERR response for write transaction poisoning
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG . WR_POISON_SLVERR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_SLVERR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_SLVERR_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_SLVERR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * If set to 1, enables interrupts for write transaction poisoning
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG . WR_POISON_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_INTR_EN  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Interrupt clear for write transaction poisoning. Allow 2/3 clock cycles
 * for correct value to propagate to core logic and clear the interrupts.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG . WR_POISON_INTR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_INTR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_INTR_CLR  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_WR_POISON_INTR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * If set to 1, enables SLVERR response for read transaction poisoning
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG . RD_POISON_SLVERR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_SLVERR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_SLVERR_EN  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_SLVERR_EN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * If set to 1, enables interrupts for read transaction poisoning
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG . RD_POISON_INTR_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_INTR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_INTR_EN  VTSS_BIT(20)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_INTR_EN(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Interrupt clear for read transaction poisoning.  Allow 2/3 clock cycles
 * for correct value to propagate to core logic and clear the interrupts.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONCFG . RD_POISON_INTR_CLR
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_INTR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_INTR_CLR  VTSS_BIT(24)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONCFG_RD_POISON_INTR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


/** 
 * \brief AXI Poison Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:POISONSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdc)

/** 
 * \brief
 * Write transaction poisoning error interrupt for port 0. This register is
 * a APB clock copy (double register synchronizer) of the interrupt
 * asserted when a transaction is poisoned on the corresponding AXI port's
 * write address channel. Bit 0 corresponds to Port 0, and so on. Interrupt
 * is cleared by register wr_poison_intr_clr, then value propagated to APB
 * clock.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT . WR_POISON_INTR_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT_WR_POISON_INTR_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT_WR_POISON_INTR_0  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT_WR_POISON_INTR_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Read transaction poisoning error interrupt for port 0. This register is
 * a APB clock copy (double register synchronizer) of the interrupt
 * asserted when a transaction is poisoned on the corresponding AXI port's
 * read address channel. Bit 0 corresponds to Port 0, and so on. Interrupt
 * is cleared by register rd_poison_intr_clr, then value propagated to APB
 * clock.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT . RD_POISON_INTR_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT_RD_POISON_INTR_0(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT_RD_POISON_INTR_0  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_POISONSTAT_RD_POISON_INTR_0(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/** 
 * \brief Advanced ECC Index Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ADVECCINDEX
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdd)

/** 
 * \brief
 * Selector of which DRAM beat data output to ECCCSYN0/1/2 as well as
 * ECCUCSYN.
 * 
 *   In Advanced ECC, the syndrome consist of number of DRAM beats. This
 * register select which beats of data will be output to ECCCSYN0/1/2 and
 * ECCUCSYN0/1/2 registers.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX . ECC_SYNDROME_SEL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_SYNDROME_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_SYNDROME_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_SYNDROME_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Selector of which error symbol's status output to
 * ADVECCSTAT.advecc_err_symbol_pos and advecc_err_symbol_bits. The default
 * is first error symbol.
 * 
 *   The value should be less than ADVECCSTAT.advecc_num_err_symbol.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX . ECC_ERR_SYMBOL_SEL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_ERR_SYMBOL_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_ERR_SYMBOL_SEL     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_ERR_SYMBOL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Selector of which DRAM beat's poison pattern will be set by
 * ECCPOISONPAT0/1/2 registers. 
 *  
 *   For frequency ratio 1:1 mode, 2 DRAM beats can be poisoned. Set
 * ecc_poison_beats_sel to 0 and given ECCPOISONPAT0/1/2 to set 1st beat's
 * poison pattern; set ecc_poison_beats_sel to 1 and given
 * ECCPOISONPAT0/1/2 to set 2nd beat's poison pattern.
 * 
 *   For frequency ratio 1:2 mode, 4 DRAM beats can be poisoned. Set
 * ecc_poison_beats_sel from 0~3 to set 1st to 4th beat's poison pattern.
 * 
 *   The other value is reserved.
 * Programming Mode: Quasi-dynamic Group 1
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX . ECC_POISON_BEATS_SEL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_POISON_BEATS_SEL(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_POISON_BEATS_SEL     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ADVECCINDEX_ECC_POISON_BEATS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,4)


/** 
 * \brief ECC Poison Pattern 0 Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONPAT0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xdf)

/** 
 * \brief
 * Poison pattern for DRAM data[31:0].
 *   Only bit is set to 1 indicate poison (invert) corresponding DRAM bit.
 * 
 *   It is indirect register. Selector is ADVECCINDEX.ecc_poison_beats_sel.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT0 . ECC_POISON_DATA_31_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT0_ECC_POISON_DATA_31_0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT0_ECC_POISON_DATA_31_0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT0_ECC_POISON_DATA_31_0(x)  (x)


/** 
 * \brief ECC Poison Pattern 2 Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_REGS:ECCPOISONPAT2
 */
#define VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT2  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xe1)

/** 
 * \brief
 * Poison pattern for DRAM data[71:64]. 
 *   Only bit is set to 1 indicate poison (invert) corresponding DRAM bit.
 * 
 *   It is indirect register. Selector is ADVECCINDEX.ecc_poison_beats_sel.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT2 . ECC_POISON_DATA_71_64
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT2_ECC_POISON_DATA_71_64(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT2_ECC_POISON_DATA_71_64     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_REGS_ECCPOISONPAT2_ECC_POISON_DATA_71_64(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a DDR_UMCTL2:UMCTL2_MP
 *
 * uMCTL2 Multi-Port Registers
 */


/** 
 * \brief Port Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_PSTAT      VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0xff)

/** 
 * \brief
 * Indicates if there are outstanding reads for AXI port 0.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PSTAT . RD_PORT_BUSY_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PSTAT_RD_PORT_BUSY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PSTAT_RD_PORT_BUSY_0  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PSTAT_RD_PORT_BUSY_0(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Indicates if there are outstanding writes for AXI port 0.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PSTAT . WR_PORT_BUSY_0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PSTAT_WR_PORT_BUSY_0(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PSTAT_WR_PORT_BUSY_0  VTSS_BIT(16)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PSTAT_WR_PORT_BUSY_0(x)  VTSS_EXTRACT_BITFIELD(x,16,1)


/** 
 * \brief Port Common Configuration Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCCFG
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_PCCFG      VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x100)

/** 
 * \brief
 * If set to 1 (enabled), sets co_gs_go2critical_wr and
 * co_gs_go2critical_lpr/co_gs_go2critical_hpr signals going to DDRC based
 * on	  urgent input (awurgent, arurgent) coming from AXI master. If set
 * to 0 (disabled), co_gs_go2critical_wr and	
 * co_gs_go2critical_lpr/co_gs_go2critical_hpr signals at DDRC are driven
 * to 1b'0.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCCFG . GO2CRITICAL_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCCFG_GO2CRITICAL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCCFG_GO2CRITICAL_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCCFG_GO2CRITICAL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Page match four limit. If set to 1, limits the number of consecutive
 * same page DDRC transactions that can be granted by the Port Arbiter to
 * four when Page Match feature is enabled.	  If set to 0, there is no
 * limit imposed on number of consecutive same page DDRC transactions.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCCFG . PAGEMATCH_LIMIT
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCCFG_PAGEMATCH_LIMIT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCCFG_PAGEMATCH_LIMIT  VTSS_BIT(4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCCFG_PAGEMATCH_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Burst length expansion mode. By default (i.e. bl_exp_mode==0) XPI
 * expands every AXI burst into multiple HIF commands, using the memory
 * burst length as a unit. If set to 1, then XPI will use half of the
 * memory burst length as a unit. 
 *     This applies to both reads and writes. When MSTR.data_bus_width==00,
 * setting bl_exp_mode to 1 has no effect.
 *     
 * This can be used in cases where Partial Writes is enabled
 * (UMCTL2_PARTIAL_WR=1), in order to avoid or minimize t_ccd_l penalty in
 * DDR4 and t_ccd_mw penalty in LPDDR4. Hence, bl_exp_mode=1 is only
 * recommended if DDR4 or LPDDR4.
 *     
 * Note that if DBICTL.dm_en=0, functionality is not supported in the
 * following cases:
 *     - UMCTL2_PARTIAL_WR=0
 *     - UMCTL2_PARTIAL_WR=1, MSTR.data_bus_width=01, MEMC_BURST_LENGTH=8
 * and MSTR.burst_rdwr=1000 (LPDDR4 only)
 *     - UMCTL2_PARTIAL_WR=1, MSTR.data_bus_width=01, MEMC_BURST_LENGTH=4
 * and MSTR.burst_rdwr=0100 (DDR4 only), with either MSTR.burstchop=0 or
 * CRCPARCTL1.crc_enable=1
 *     
 * Functionality is also not supported if Data Channel Interleave is
 * enabled
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCCFG . BL_EXP_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCCFG_BL_EXP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCCFG_BL_EXP_MODE  VTSS_BIT(8)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCCFG_BL_EXP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/** 
 * \brief Port n Configuration Read Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGR_0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGR_0    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x101)

/** 
 * \brief
 * Determines the initial load value of read aging counters.	    These
 * counters will be parallel loaded after reset, or after each grant to the
 * corresponding port.	    The aging counters down-count every clock cycle
 * where the port is requesting but not    granted. The higher significant
 * 5-bits of the read aging counter sets the priority of the	      read
 * channel of a given port.	   Port's priority will increase as the
 * higher significant 5-bits of the counter starts to decrease.       When
 * the aging counter becomes 0, the corresponding port channel will have
 * the highest priority level (timeout condition - Priority0).	For
 * multi-port configurations, the aging counters cannot be used to set port
 * priorities when external dynamic priority	      inputs (arqos) are
 * enabled (timeout is still applicable).	For single port
 * configurations, the aging counters are only used when they timeout
 * (become 0) to force read-write direction switching.	In this case,
 * external dynamic priority input, arqos (for reads only) can still be
 * used to set the DDRC read priority	(2 priority levels: low priority
 * read - LPR, high priority read - HPR) on a command by command basis.   
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGR_0 . RD_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * If set to 1, enables aging function for the read channel of the port.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGR_0 . RD_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * If set to 1, enables the AXI urgent sideband signal (arurgent). When
 * enabled and arurgent        is asserted by the master, that port becomes
 * the highest priority and co_gs_go2critical_lpr/co_gs_go2critical_hpr
 * signal to	 DDRC is asserted if enabled in PCCFG.go2critical_en
 * register. Note that arurgent signal can be	       asserted anytime and
 * as long as required which is independent of address handshaking (it is
 * not	       associated with any particular command).
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGR_0 . RD_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * If set to 1, enables the Page Match feature. If enabled, once a
 * requesting port is granted,	    the port is continued to be granted if
 * the following immediate commands are to the same	    memory page
 * (same bank and same row). See also related PCCFG.pagematch_limit
 * register.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGR_0 . RD_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGR_0_RD_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/** 
 * \brief Port n Configuration Write Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGW_0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGW_0    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x102)

/** 
 * \brief
 * Determines the initial load value of write aging counters.	    These
 * counters will be parallel loaded after reset, or after each grant to the
 * corresponding port.	    The aging counters down-count every clock cycle
 * where the port is requesting but not    granted. The higher significant
 * 5-bits of the write aging counter sets the initial priority of the	   
 *    write channel of a given port.	  Port's priority will increase as
 * the higher significant 5-bits of the counter starts to decrease. When
 * the aging counter becomes 0, the corresponding port channel will have
 * the highest priority level.	      
 * For multi-port configurations, the aging counters cannot be used to set
 * port priorities when external dynamic priority   inputs (awqos) are
 * enabled (timeout is still applicable).	
 * For single port configurations, the aging counters are only used when
 * they timeout (become 0) to force read-write direction switching.   
 * Note: The two LSBs of this register field are tied internally to 2'b00.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGW_0 . WR_PORT_PRIORITY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_PRIORITY(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_PRIORITY     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_PRIORITY(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/** 
 * \brief
 * If set to 1, enables aging function for the write channel of the port.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGW_0 . WR_PORT_AGING_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_AGING_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_AGING_EN  VTSS_BIT(12)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_AGING_EN(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * If set to 1, enables the AXI urgent sideband signal (awurgent). When
 * enabled and awurgent        is asserted by the master, that port becomes
 * the highest priority and co_gs_go2critical_wr signal to    DDRC is
 * asserted if enabled in PCCFG.go2critical_en register.
 *  Note that awurgent signal can be	    asserted anytime and as long as
 * required which is independent of address handshaking (it is not	  
 * associated with any particular command).
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGW_0 . WR_PORT_URGENT_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_URGENT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_URGENT_EN  VTSS_BIT(13)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_URGENT_EN(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * If set to 1, enables the Page Match feature. If enabled, once a
 * requesting port is granted,	    the port is continued to be granted if
 * the following immediate commands are to the same	    memory page
 * (same bank and same row). See also related PCCFG.pagematch_limit
 * register.
 * Programming Mode: Static
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGW_0 . WR_PORT_PAGEMATCH_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_PAGEMATCH_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_PAGEMATCH_EN  VTSS_BIT(14)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGW_0_WR_PORT_PAGEMATCH_EN(x)  VTSS_EXTRACT_BITFIELD(x,14,1)


/** 
 * \brief Port n Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCTRL_0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_PCTRL_0    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x124)

/** 
 * \brief
 * Enables AXI port n.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCTRL_0 . PORT_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCTRL_0_PORT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCTRL_0_PORT_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCTRL_0_PORT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Port n Read QoS Configuration Register 0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:PCFGQOS0_0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x125)

/** 
 * \brief
 * Separation level1 indicating the end of region0 mapping; start of
 * region0 is 0. Possible values for level1 are 0 to 13 (for dual RAQ) or 0
 * to 14 (for single RAQ) which corresponds to arqos.	       
 * Note that for PA, arqos values are used directly as port priorities,
 * where the higher the value corresponds to higher port priority.
 *  All of the map_level* registers must be set to distinct values.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0 . RQOS_MAP_LEVEL1
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_LEVEL1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_LEVEL1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_LEVEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * This bitfield indicates the traffic class of region 0.
 *  Valid values are:
 *  0: LPR, 1: VPR, 2: HPR.
 *  For dual address queue configurations, region 0 maps to the blue
 * address queue.
 *  In this case, valid values are: 
 * 0: LPR and 1: VPR only.
 *  When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region0 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0 . RQOS_MAP_REGION0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_REGION0(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_REGION0     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_REGION0(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * This bitfield indicates the traffic class of region 1.
 *  Valid values are:
 * 0 : LPR, 1: VPR, 2: HPR.
 *  For dual address queue configurations, region1 maps to the blue address
 * queue.
 *  In this case, valid values are 
 * 0: LPR and 1: VPR only.
 *  When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of
 * region 1 is set to 1 (VPR), VPR traffic is aliased to LPR traffic.
 * Programming Mode: Quasi-dynamic Group 3
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0 . RQOS_MAP_REGION1
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_REGION1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_REGION1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_PCFGQOS0_0_RQOS_MAP_REGION1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)


/** 
 * \brief Scrubber Control Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRCTL
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_SBRCTL     VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3c9)

/** 
 * \brief
 * Enable ECC scrubber. 
 * If set to 1, enables the scrubber to generate background read commands
 * after the memories are initialized.
 *  If set to 0, disables the scrubber, resets the address generator to 0 
 *	and clears the scrubber status.
 *  This bitfield must be accessed separately from the other bitfields in
 * this register.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRCTL . SCRUB_EN
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_EN  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Continue scrubbing during low power.
 *  If set to 1, burst of scrubs will be issued in HW controlled low power
 * modes. There are two such modes: automatically initiated by idleness or
 * initiated by Hardware low power interface.
 *  If set to 0, the scrubber will not attempt to send commands while the
 * DDRC is in HW controlled low power modes. In this case, the scrubber
 * will remember the last address issued and will automatically continue
 * from there when the DDRC exits the LP mode.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRCTL . SCRUB_DURING_LOWPOWER
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_DURING_LOWPOWER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_DURING_LOWPOWER  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_DURING_LOWPOWER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * scrub_mode:0 ECC scrubber will perform reads 
 *  scrub_mode:1 ECC scrubber will perform writes
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRCTL . SCRUB_MODE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_MODE  VTSS_BIT(2)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Scrub burst count. Determines the number of back-to-back scrub read
 * commands that can be issued together
 *	when the controller is in one of the HW controlled low power modes
 * with Sideband ECC, both normal operation mode and low-power mode with
 * Inline ECC. During these modes, the period of the scrub burst
 *	becomes "scrub_burst*scrub_interval" cycles. During normal
 * operation mode of the controller with Sideband ECC (not in power-down
 *	or self refresh), scrub_burst is ignored and only one scrub command
 * is generated.
 *  Valid values are (Sideband ECC): 1: 1 read, 2: 4 reads, 3: 16 reads, 4:
 * 64 reads, 5: 256 reads, 6: 1024 reads. (Inline ECC): 1: 8 reads, 2: 16
 * reads, 3: 32 reads.
 *	New programmed value will take effect only after scrubber is
 * disabled by programming scrub_en to 0.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRCTL . SCRUB_BURST
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_BURST(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_BURST     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_BURST(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Scrub interval. (512 x scrub_interval) number of clock cycles between
 * two scrub read commands. If set to 0, scrub commands are issued
 * back-to-back. This mode of operation (scrub_interval=0) can typically be
 * used for scrubbing the full range of memory at once before or after SW
 * controlled low power operations. After completing the full range of
 * scrub while scrub_interval=0, scrub_done register is set and
 * sbr_done_intr interrupt signal is asserted. 
 *	This mode can't be used with Inline ECC: If MEMC_INLINE_ECC is 1
 * and scrub_interval is programme to 0, then RMW logic inside scrubber is
 * disabled.
 *	New programmed value will take effect only after scrubber is
 * disabled by programming scrub_en to 0.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRCTL . SCRUB_INTERVAL
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,8,13)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_INTERVAL     VTSS_ENCODE_BITMASK(8,13)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRCTL_SCRUB_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,8,13)


/** 
 * \brief Scrubber Status Register
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRSTAT
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_SBRSTAT    VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3ca)

/** 
 * \brief
 * Scrubber busy. Controller sets this bit to 1 when the scrubber logic has
 * outstanding read commands being executed. Cleared when there are no
 * active outstanding scrub reads in the system.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRSTAT . SCRUB_BUSY
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRSTAT_SCRUB_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRSTAT_SCRUB_BUSY  VTSS_BIT(0)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRSTAT_SCRUB_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Scrubber done. Controller sets this bit to 1, after full range of
 * addresses are scrubbed once while scrub_interval is set to 0. Cleared if
 * scrub_en is set to 0 (scrubber disabled) or scrub_interval is set to a
 * non-zero value for normal scrub operation. The interrupt signal,
 * sbr_done_intr, is equivalent to this status bitfield.
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRSTAT . SCRUB_DONE
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRSTAT_SCRUB_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRSTAT_SCRUB_DONE  VTSS_BIT(1)
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRSTAT_SCRUB_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief Scrubber Write Data Pattern0
 *
 * \details
 * Register: \a DDR_UMCTL2:UMCTL2_MP:SBRWDATA0
 */
#define VTSS_DDR_UMCTL2_UMCTL2_MP_SBRWDATA0  VTSS_IOREG(VTSS_TO_DDR_UMCTL2,0x3cb)

/** 
 * \brief
 * ECC Scrubber write data pattern for data bus[31:0]
 * Programming Mode: Dynamic
 *
 * \details 
 * Field: ::VTSS_DDR_UMCTL2_UMCTL2_MP_SBRWDATA0 . SCRUB_PATTERN0
 */
#define  VTSS_F_DDR_UMCTL2_UMCTL2_MP_SBRWDATA0_SCRUB_PATTERN0(x)  (x)
#define  VTSS_M_DDR_UMCTL2_UMCTL2_MP_SBRWDATA0_SCRUB_PATTERN0     0xffffffff
#define  VTSS_X_DDR_UMCTL2_UMCTL2_MP_SBRWDATA0_SCRUB_PATTERN0(x)  (x)


#endif /* _VTSS_FIREANT_REGS_DDR_UMCTL2_H_ */
