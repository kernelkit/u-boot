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

#ifndef _MSCC_FA_REGS_COMMON_H_
#define _MSCC_FA_REGS_COMMON_H_


#ifndef MSCC_IO_ORIGIN1_OFFSET
#define MSCC_IO_ORIGIN1_OFFSET 0x610000000UL /*! default region*/
#endif
#ifndef MSCC_IO_ORIGIN1_SIZE
#define MSCC_IO_ORIGIN1_SIZE 0x010000000
#endif
#ifndef MSCC_IO_OFFSET1
#define MSCC_IO_OFFSET1(offset) (MSCC_IO_ORIGIN1_OFFSET + offset)
#endif
#ifndef MSCC_IO_ORIGIN2_OFFSET
#define MSCC_IO_ORIGIN2_OFFSET 0x600000000UL /*! amba_top region*/
#endif
#ifndef MSCC_IO_ORIGIN2_SIZE
#define MSCC_IO_ORIGIN2_SIZE 0x010000000
#endif
#ifndef MSCC_IO_OFFSET2
#define MSCC_IO_OFFSET2(offset) (MSCC_IO_ORIGIN2_OFFSET + offset)
#endif
#ifndef MSCC_IO_ORIGIN3_OFFSET
#define MSCC_IO_ORIGIN3_OFFSET 0x630000000UL /*! subcpu_sys region*/
#endif
#ifndef MSCC_IO_ORIGIN3_SIZE
#define MSCC_IO_ORIGIN3_SIZE 0x010000000
#endif
#ifndef MSCC_IO_OFFSET3
#define MSCC_IO_OFFSET3(offset) (MSCC_IO_ORIGIN3_OFFSET + offset)
#endif
#define MSCC_TO_AFI             MSCC_IO_OFFSET1(0x01240000) /*!< Base offset for target AFI */
#define MSCC_TO_ANA_AC          MSCC_IO_OFFSET1(0x01900000) /*!< Base offset for target ANA_AC */
#define MSCC_TO_ANA_AC_OAM_MOD  MSCC_IO_OFFSET1(0x01070000) /*!< Base offset for target ANA_AC_OAM_MOD */
#define MSCC_TO_ANA_AC_POL      MSCC_IO_OFFSET1(0x01200000) /*!< Base offset for target ANA_AC_POL */
#define MSCC_TO_ANA_AC_SDLB     MSCC_IO_OFFSET1(0x01500000) /*!< Base offset for target ANA_AC_SDLB */
#define MSCC_TO_ANA_ACL         MSCC_IO_OFFSET1(0x01050000) /*!< Base offset for target ANA_ACL */
#define MSCC_TO_ANA_CL          MSCC_IO_OFFSET1(0x01400000) /*!< Base offset for target ANA_CL */
#define MSCC_TO_ANA_L2          MSCC_IO_OFFSET1(0x01800000) /*!< Base offset for target ANA_L2 */
#define MSCC_TO_ANA_L3          MSCC_IO_OFFSET1(0x01480000) /*!< Base offset for target ANA_L3 */
#define MSCC_TO_ASM             MSCC_IO_OFFSET1(0x00600000) /*!< Base offset for target ASM */
#define MSCC_TO_CHIP_TOP        MSCC_IO_OFFSET1(0x01020000) /*!< Base offset for target CHIP_TOP */
#define MSCC_TO_CLKGEN          MSCC_IO_OFFSET1(0x01100000) /*!< Base offset for target CLKGEN */
#define MSCC_TO_CPU             MSCC_IO_OFFSET2(0x00000000) /*!< Base offset for target CPU */
#define MSCC_TO_DDR_PHY         MSCC_IO_OFFSET2(0x00108000) /*!< Base offset for target DDR_PHY */
#define MSCC_TO_DDR_UMCTL2      MSCC_IO_OFFSET2(0x00107000) /*!< Base offset for target DDR_UMCTL2 */
#define MSCC_TO_DEV10G_0        MSCC_IO_OFFSET1(0x00074000) /*!< Base offset for target DEV10G_0 */
#define MSCC_TO_DEV10G_1        MSCC_IO_OFFSET1(0x0042c000) /*!< Base offset for target DEV10G_1 */
#define MSCC_TO_DEV10G_2        MSCC_IO_OFFSET1(0x00080000) /*!< Base offset for target DEV10G_2 */
#define MSCC_TO_DEV10G_3        MSCC_IO_OFFSET1(0x0008c000) /*!< Base offset for target DEV10G_3 */
#define MSCC_TO_DEV10G_4        MSCC_IO_OFFSET1(0x00458000) /*!< Base offset for target DEV10G_4 */
#define MSCC_TO_DEV10G_5        MSCC_IO_OFFSET1(0x00464000) /*!< Base offset for target DEV10G_5 */
#define MSCC_TO_DEV10G_6        MSCC_IO_OFFSET1(0x00470000) /*!< Base offset for target DEV10G_6 */
#define MSCC_TO_DEV10G_7        MSCC_IO_OFFSET1(0x0047c000) /*!< Base offset for target DEV10G_7 */
#define MSCC_TO_DEV10G_8        MSCC_IO_OFFSET1(0x00488000) /*!< Base offset for target DEV10G_8 */
#define MSCC_TO_DEV10G_9        MSCC_IO_OFFSET1(0x00494000) /*!< Base offset for target DEV10G_9 */
#define MSCC_TO_DEV10G_10       MSCC_IO_OFFSET1(0x004a0000) /*!< Base offset for target DEV10G_10 */
#define MSCC_TO_DEV10G_11       MSCC_IO_OFFSET1(0x004ac000) /*!< Base offset for target DEV10G_11 */
#define MSCC_TO_DEV25G_0        MSCC_IO_OFFSET1(0x004b8000) /*!< Base offset for target DEV25G_0 */
#define MSCC_TO_DEV25G_1        MSCC_IO_OFFSET1(0x000f8000) /*!< Base offset for target DEV25G_1 */
#define MSCC_TO_DEV25G_2        MSCC_IO_OFFSET1(0x004c8000) /*!< Base offset for target DEV25G_2 */
#define MSCC_TO_DEV25G_3        MSCC_IO_OFFSET1(0x00108000) /*!< Base offset for target DEV25G_3 */
#define MSCC_TO_DEV25G_4        MSCC_IO_OFFSET1(0x00118000) /*!< Base offset for target DEV25G_4 */
#define MSCC_TO_DEV25G_5        MSCC_IO_OFFSET1(0x004d8000) /*!< Base offset for target DEV25G_5 */
#define MSCC_TO_DEV25G_6        MSCC_IO_OFFSET1(0x004e8000) /*!< Base offset for target DEV25G_6 */
#define MSCC_TO_DEV25G_7        MSCC_IO_OFFSET1(0x004f8000) /*!< Base offset for target DEV25G_7 */
#define MSCC_TO_DEV2G5_0        MSCC_IO_OFFSET1(0x00004000) /*!< Base offset for target DEV2G5_0 */
#define MSCC_TO_DEV2G5_1        MSCC_IO_OFFSET1(0x00010000) /*!< Base offset for target DEV2G5_1 */
#define MSCC_TO_DEV2G5_2        MSCC_IO_OFFSET1(0x0001c000) /*!< Base offset for target DEV2G5_2 */
#define MSCC_TO_DEV2G5_3        MSCC_IO_OFFSET1(0x00404000) /*!< Base offset for target DEV2G5_3 */
#define MSCC_TO_DEV2G5_4        MSCC_IO_OFFSET1(0x00410000) /*!< Base offset for target DEV2G5_4 */
#define MSCC_TO_DEV2G5_5        MSCC_IO_OFFSET1(0x0041c000) /*!< Base offset for target DEV2G5_5 */
#define MSCC_TO_DEV2G5_6        MSCC_IO_OFFSET1(0x00028000) /*!< Base offset for target DEV2G5_6 */
#define MSCC_TO_DEV2G5_7        MSCC_IO_OFFSET1(0x00034000) /*!< Base offset for target DEV2G5_7 */
#define MSCC_TO_DEV2G5_8        MSCC_IO_OFFSET1(0x00040000) /*!< Base offset for target DEV2G5_8 */
#define MSCC_TO_DEV2G5_9        MSCC_IO_OFFSET1(0x0004c000) /*!< Base offset for target DEV2G5_9 */
#define MSCC_TO_DEV2G5_10       MSCC_IO_OFFSET1(0x00058000) /*!< Base offset for target DEV2G5_10 */
#define MSCC_TO_DEV2G5_11       MSCC_IO_OFFSET1(0x00064000) /*!< Base offset for target DEV2G5_11 */
#define MSCC_TO_DEV2G5_12       MSCC_IO_OFFSET1(0x00070000) /*!< Base offset for target DEV2G5_12 */
#define MSCC_TO_DEV2G5_13       MSCC_IO_OFFSET1(0x00428000) /*!< Base offset for target DEV2G5_13 */
#define MSCC_TO_DEV2G5_14       MSCC_IO_OFFSET1(0x0007c000) /*!< Base offset for target DEV2G5_14 */
#define MSCC_TO_DEV2G5_15       MSCC_IO_OFFSET1(0x00088000) /*!< Base offset for target DEV2G5_15 */
#define MSCC_TO_DEV2G5_16       MSCC_IO_OFFSET1(0x00094000) /*!< Base offset for target DEV2G5_16 */
#define MSCC_TO_DEV2G5_17       MSCC_IO_OFFSET1(0x00098000) /*!< Base offset for target DEV2G5_17 */
#define MSCC_TO_DEV2G5_18       MSCC_IO_OFFSET1(0x0009c000) /*!< Base offset for target DEV2G5_18 */
#define MSCC_TO_DEV2G5_19       MSCC_IO_OFFSET1(0x000a0000) /*!< Base offset for target DEV2G5_19 */
#define MSCC_TO_DEV2G5_20       MSCC_IO_OFFSET1(0x000a4000) /*!< Base offset for target DEV2G5_20 */
#define MSCC_TO_DEV2G5_21       MSCC_IO_OFFSET1(0x000a8000) /*!< Base offset for target DEV2G5_21 */
#define MSCC_TO_DEV2G5_22       MSCC_IO_OFFSET1(0x000ac000) /*!< Base offset for target DEV2G5_22 */
#define MSCC_TO_DEV2G5_23       MSCC_IO_OFFSET1(0x000b0000) /*!< Base offset for target DEV2G5_23 */
#define MSCC_TO_DEV2G5_24       MSCC_IO_OFFSET1(0x00434000) /*!< Base offset for target DEV2G5_24 */
#define MSCC_TO_DEV2G5_25       MSCC_IO_OFFSET1(0x00438000) /*!< Base offset for target DEV2G5_25 */
#define MSCC_TO_DEV2G5_26       MSCC_IO_OFFSET1(0x0043c000) /*!< Base offset for target DEV2G5_26 */
#define MSCC_TO_DEV2G5_27       MSCC_IO_OFFSET1(0x00440000) /*!< Base offset for target DEV2G5_27 */
#define MSCC_TO_DEV2G5_28       MSCC_IO_OFFSET1(0x00444000) /*!< Base offset for target DEV2G5_28 */
#define MSCC_TO_DEV2G5_29       MSCC_IO_OFFSET1(0x00448000) /*!< Base offset for target DEV2G5_29 */
#define MSCC_TO_DEV2G5_30       MSCC_IO_OFFSET1(0x0044c000) /*!< Base offset for target DEV2G5_30 */
#define MSCC_TO_DEV2G5_31       MSCC_IO_OFFSET1(0x00450000) /*!< Base offset for target DEV2G5_31 */
#define MSCC_TO_DEV2G5_32       MSCC_IO_OFFSET1(0x000b4000) /*!< Base offset for target DEV2G5_32 */
#define MSCC_TO_DEV2G5_33       MSCC_IO_OFFSET1(0x000b8000) /*!< Base offset for target DEV2G5_33 */
#define MSCC_TO_DEV2G5_34       MSCC_IO_OFFSET1(0x000bc000) /*!< Base offset for target DEV2G5_34 */
#define MSCC_TO_DEV2G5_35       MSCC_IO_OFFSET1(0x000c0000) /*!< Base offset for target DEV2G5_35 */
#define MSCC_TO_DEV2G5_36       MSCC_IO_OFFSET1(0x000c4000) /*!< Base offset for target DEV2G5_36 */
#define MSCC_TO_DEV2G5_37       MSCC_IO_OFFSET1(0x000c8000) /*!< Base offset for target DEV2G5_37 */
#define MSCC_TO_DEV2G5_38       MSCC_IO_OFFSET1(0x000cc000) /*!< Base offset for target DEV2G5_38 */
#define MSCC_TO_DEV2G5_39       MSCC_IO_OFFSET1(0x000d0000) /*!< Base offset for target DEV2G5_39 */
#define MSCC_TO_DEV2G5_40       MSCC_IO_OFFSET1(0x000d4000) /*!< Base offset for target DEV2G5_40 */
#define MSCC_TO_DEV2G5_41       MSCC_IO_OFFSET1(0x000d8000) /*!< Base offset for target DEV2G5_41 */
#define MSCC_TO_DEV2G5_42       MSCC_IO_OFFSET1(0x000dc000) /*!< Base offset for target DEV2G5_42 */
#define MSCC_TO_DEV2G5_43       MSCC_IO_OFFSET1(0x000e0000) /*!< Base offset for target DEV2G5_43 */
#define MSCC_TO_DEV2G5_44       MSCC_IO_OFFSET1(0x000e4000) /*!< Base offset for target DEV2G5_44 */
#define MSCC_TO_DEV2G5_45       MSCC_IO_OFFSET1(0x000e8000) /*!< Base offset for target DEV2G5_45 */
#define MSCC_TO_DEV2G5_46       MSCC_IO_OFFSET1(0x000ec000) /*!< Base offset for target DEV2G5_46 */
#define MSCC_TO_DEV2G5_47       MSCC_IO_OFFSET1(0x000f0000) /*!< Base offset for target DEV2G5_47 */
#define MSCC_TO_DEV2G5_48       MSCC_IO_OFFSET1(0x00454000) /*!< Base offset for target DEV2G5_48 */
#define MSCC_TO_DEV2G5_49       MSCC_IO_OFFSET1(0x00460000) /*!< Base offset for target DEV2G5_49 */
#define MSCC_TO_DEV2G5_50       MSCC_IO_OFFSET1(0x0046c000) /*!< Base offset for target DEV2G5_50 */
#define MSCC_TO_DEV2G5_51       MSCC_IO_OFFSET1(0x00478000) /*!< Base offset for target DEV2G5_51 */
#define MSCC_TO_DEV2G5_52       MSCC_IO_OFFSET1(0x00484000) /*!< Base offset for target DEV2G5_52 */
#define MSCC_TO_DEV2G5_53       MSCC_IO_OFFSET1(0x00490000) /*!< Base offset for target DEV2G5_53 */
#define MSCC_TO_DEV2G5_54       MSCC_IO_OFFSET1(0x0049c000) /*!< Base offset for target DEV2G5_54 */
#define MSCC_TO_DEV2G5_55       MSCC_IO_OFFSET1(0x004a8000) /*!< Base offset for target DEV2G5_55 */
#define MSCC_TO_DEV2G5_56       MSCC_IO_OFFSET1(0x004b4000) /*!< Base offset for target DEV2G5_56 */
#define MSCC_TO_DEV2G5_57       MSCC_IO_OFFSET1(0x000f4000) /*!< Base offset for target DEV2G5_57 */
#define MSCC_TO_DEV2G5_58       MSCC_IO_OFFSET1(0x004c4000) /*!< Base offset for target DEV2G5_58 */
#define MSCC_TO_DEV2G5_59       MSCC_IO_OFFSET1(0x00104000) /*!< Base offset for target DEV2G5_59 */
#define MSCC_TO_DEV2G5_60       MSCC_IO_OFFSET1(0x00114000) /*!< Base offset for target DEV2G5_60 */
#define MSCC_TO_DEV2G5_61       MSCC_IO_OFFSET1(0x004d4000) /*!< Base offset for target DEV2G5_61 */
#define MSCC_TO_DEV2G5_62       MSCC_IO_OFFSET1(0x004e4000) /*!< Base offset for target DEV2G5_62 */
#define MSCC_TO_DEV2G5_63       MSCC_IO_OFFSET1(0x004f4000) /*!< Base offset for target DEV2G5_63 */
#define MSCC_TO_DEV2G5_64       MSCC_IO_OFFSET1(0x00124000) /*!< Base offset for target DEV2G5_64 */
#define MSCC_TO_DEV5G_0         MSCC_IO_OFFSET1(0x00008000) /*!< Base offset for target DEV5G_0 */
#define MSCC_TO_DEV5G_1         MSCC_IO_OFFSET1(0x00014000) /*!< Base offset for target DEV5G_1 */
#define MSCC_TO_DEV5G_2         MSCC_IO_OFFSET1(0x00020000) /*!< Base offset for target DEV5G_2 */
#define MSCC_TO_DEV5G_3         MSCC_IO_OFFSET1(0x00408000) /*!< Base offset for target DEV5G_3 */
#define MSCC_TO_DEV5G_4         MSCC_IO_OFFSET1(0x00414000) /*!< Base offset for target DEV5G_4 */
#define MSCC_TO_DEV5G_5         MSCC_IO_OFFSET1(0x00420000) /*!< Base offset for target DEV5G_5 */
#define MSCC_TO_DEV5G_6         MSCC_IO_OFFSET1(0x0002c000) /*!< Base offset for target DEV5G_6 */
#define MSCC_TO_DEV5G_7         MSCC_IO_OFFSET1(0x00038000) /*!< Base offset for target DEV5G_7 */
#define MSCC_TO_DEV5G_8         MSCC_IO_OFFSET1(0x00044000) /*!< Base offset for target DEV5G_8 */
#define MSCC_TO_DEV5G_9         MSCC_IO_OFFSET1(0x00050000) /*!< Base offset for target DEV5G_9 */
#define MSCC_TO_DEV5G_10        MSCC_IO_OFFSET1(0x0005c000) /*!< Base offset for target DEV5G_10 */
#define MSCC_TO_DEV5G_11        MSCC_IO_OFFSET1(0x00068000) /*!< Base offset for target DEV5G_11 */
#define MSCC_TO_DEV5G_64        MSCC_IO_OFFSET1(0x00128000) /*!< Base offset for target DEV5G_64 */
#define MSCC_TO_DEVCPU_GCB      MSCC_IO_OFFSET1(0x01010000) /*!< Base offset for target DEVCPU_GCB */
#define MSCC_TO_DEVCPU_ORG0     MSCC_IO_OFFSET1(0x00000000) /*!< Base offset for target DEVCPU_ORG0 */
#define MSCC_TO_DEVCPU_ORG1     MSCC_IO_OFFSET1(0x00400000) /*!< Base offset for target DEVCPU_ORG1 */
#define MSCC_TO_DEVCPU_ORG2     MSCC_IO_OFFSET1(0x00800000) /*!< Base offset for target DEVCPU_ORG2 */
#define MSCC_TO_DEVCPU_ORG3     MSCC_IO_OFFSET1(0x00c00000) /*!< Base offset for target DEVCPU_ORG3 */
#define MSCC_TO_DEVCPU_ORG4     MSCC_IO_OFFSET1(0x01000000) /*!< Base offset for target DEVCPU_ORG4 */
#define MSCC_TO_DEVCPU_PTP      MSCC_IO_OFFSET1(0x01040000) /*!< Base offset for target DEVCPU_PTP */
#define MSCC_TO_DEVCPU_QS       MSCC_IO_OFFSET1(0x01030000) /*!< Base offset for target DEVCPU_QS */
#define MSCC_TO_DSM             MSCC_IO_OFFSET1(0x00504000) /*!< Base offset for target DSM */
#define MSCC_TO_EACL            MSCC_IO_OFFSET1(0x012c0000) /*!< Base offset for target EACL */
#define MSCC_TO_FDMA            MSCC_IO_OFFSET2(0x00080000) /*!< Base offset for target FDMA */
#define MSCC_TO_HSCH            MSCC_IO_OFFSET1(0x01580000) /*!< Base offset for target HSCH */
#define MSCC_TO_HSIO_WRAP       MSCC_IO_OFFSET1(0x00508000) /*!< Base offset for target HSIO_WRAP */
#define MSCC_TO_LCPLL28_1       MSCC_IO_OFFSET1(0x010f0000) /*!< Base offset for target LCPLL28_1 */
#define MSCC_TO_LRN             MSCC_IO_OFFSET1(0x01060000) /*!< Base offset for target LRN */
#define MSCC_TO_MSHC            MSCC_IO_OFFSET2(0x00800000) /*!< Base offset for target MSHC */
#define MSCC_TO_PCIE_DM_EP      MSCC_IO_OFFSET2(0x00400000) /*!< Base offset for target PCIE_DM_EP */
#define MSCC_TO_PCIE_DM_RC      MSCC_IO_OFFSET2(0x00400000) /*!< Base offset for target PCIE_DM_RC */
#define MSCC_TO_PCIE_PHY_WRAP   MSCC_IO_OFFSET1(0x00dd8000) /*!< Base offset for target PCIE_PHY_WRAP */
#define MSCC_TO_PCS10G_BR_0     MSCC_IO_OFFSET1(0x00078000) /*!< Base offset for target PCS10G_BR_0 */
#define MSCC_TO_PCS10G_BR_1     MSCC_IO_OFFSET1(0x00430000) /*!< Base offset for target PCS10G_BR_1 */
#define MSCC_TO_PCS10G_BR_2     MSCC_IO_OFFSET1(0x00084000) /*!< Base offset for target PCS10G_BR_2 */
#define MSCC_TO_PCS10G_BR_3     MSCC_IO_OFFSET1(0x00090000) /*!< Base offset for target PCS10G_BR_3 */
#define MSCC_TO_PCS10G_BR_4     MSCC_IO_OFFSET1(0x0045c000) /*!< Base offset for target PCS10G_BR_4 */
#define MSCC_TO_PCS10G_BR_5     MSCC_IO_OFFSET1(0x00468000) /*!< Base offset for target PCS10G_BR_5 */
#define MSCC_TO_PCS10G_BR_6     MSCC_IO_OFFSET1(0x00474000) /*!< Base offset for target PCS10G_BR_6 */
#define MSCC_TO_PCS10G_BR_7     MSCC_IO_OFFSET1(0x00480000) /*!< Base offset for target PCS10G_BR_7 */
#define MSCC_TO_PCS10G_BR_8     MSCC_IO_OFFSET1(0x0048c000) /*!< Base offset for target PCS10G_BR_8 */
#define MSCC_TO_PCS10G_BR_9     MSCC_IO_OFFSET1(0x00498000) /*!< Base offset for target PCS10G_BR_9 */
#define MSCC_TO_PCS10G_BR_10    MSCC_IO_OFFSET1(0x004a4000) /*!< Base offset for target PCS10G_BR_10 */
#define MSCC_TO_PCS10G_BR_11    MSCC_IO_OFFSET1(0x004b0000) /*!< Base offset for target PCS10G_BR_11 */
#define MSCC_TO_PCS25G_BR_0     MSCC_IO_OFFSET1(0x004bc000) /*!< Base offset for target PCS25G_BR_0 */
#define MSCC_TO_PCS25G_BR_1     MSCC_IO_OFFSET1(0x000fc000) /*!< Base offset for target PCS25G_BR_1 */
#define MSCC_TO_PCS25G_BR_2     MSCC_IO_OFFSET1(0x004cc000) /*!< Base offset for target PCS25G_BR_2 */
#define MSCC_TO_PCS25G_BR_3     MSCC_IO_OFFSET1(0x0010c000) /*!< Base offset for target PCS25G_BR_3 */
#define MSCC_TO_PCS25G_BR_4     MSCC_IO_OFFSET1(0x0011c000) /*!< Base offset for target PCS25G_BR_4 */
#define MSCC_TO_PCS25G_BR_5     MSCC_IO_OFFSET1(0x004dc000) /*!< Base offset for target PCS25G_BR_5 */
#define MSCC_TO_PCS25G_BR_6     MSCC_IO_OFFSET1(0x004ec000) /*!< Base offset for target PCS25G_BR_6 */
#define MSCC_TO_PCS25G_BR_7     MSCC_IO_OFFSET1(0x004fc000) /*!< Base offset for target PCS25G_BR_7 */
#define MSCC_TO_PCS25G_RSFEC_0  MSCC_IO_OFFSET1(0x004c0000) /*!< Base offset for target PCS25G_RSFEC_0 */
#define MSCC_TO_PCS25G_RSFEC_1  MSCC_IO_OFFSET1(0x00100000) /*!< Base offset for target PCS25G_RSFEC_1 */
#define MSCC_TO_PCS25G_RSFEC_2  MSCC_IO_OFFSET1(0x004d0000) /*!< Base offset for target PCS25G_RSFEC_2 */
#define MSCC_TO_PCS25G_RSFEC_3  MSCC_IO_OFFSET1(0x00110000) /*!< Base offset for target PCS25G_RSFEC_3 */
#define MSCC_TO_PCS25G_RSFEC_4  MSCC_IO_OFFSET1(0x00120000) /*!< Base offset for target PCS25G_RSFEC_4 */
#define MSCC_TO_PCS25G_RSFEC_5  MSCC_IO_OFFSET1(0x004e0000) /*!< Base offset for target PCS25G_RSFEC_5 */
#define MSCC_TO_PCS25G_RSFEC_6  MSCC_IO_OFFSET1(0x004f0000) /*!< Base offset for target PCS25G_RSFEC_6 */
#define MSCC_TO_PCS25G_RSFEC_7  MSCC_IO_OFFSET1(0x00500000) /*!< Base offset for target PCS25G_RSFEC_7 */
#define MSCC_TO_PCS5G_BR_0      MSCC_IO_OFFSET1(0x0000c000) /*!< Base offset for target PCS5G_BR_0 */
#define MSCC_TO_PCS5G_BR_1      MSCC_IO_OFFSET1(0x00018000) /*!< Base offset for target PCS5G_BR_1 */
#define MSCC_TO_PCS5G_BR_2      MSCC_IO_OFFSET1(0x00024000) /*!< Base offset for target PCS5G_BR_2 */
#define MSCC_TO_PCS5G_BR_3      MSCC_IO_OFFSET1(0x0040c000) /*!< Base offset for target PCS5G_BR_3 */
#define MSCC_TO_PCS5G_BR_4      MSCC_IO_OFFSET1(0x00418000) /*!< Base offset for target PCS5G_BR_4 */
#define MSCC_TO_PCS5G_BR_5      MSCC_IO_OFFSET1(0x00424000) /*!< Base offset for target PCS5G_BR_5 */
#define MSCC_TO_PCS5G_BR_6      MSCC_IO_OFFSET1(0x00030000) /*!< Base offset for target PCS5G_BR_6 */
#define MSCC_TO_PCS5G_BR_7      MSCC_IO_OFFSET1(0x0003c000) /*!< Base offset for target PCS5G_BR_7 */
#define MSCC_TO_PCS5G_BR_8      MSCC_IO_OFFSET1(0x00048000) /*!< Base offset for target PCS5G_BR_8 */
#define MSCC_TO_PCS5G_BR_9      MSCC_IO_OFFSET1(0x00054000) /*!< Base offset for target PCS5G_BR_9 */
#define MSCC_TO_PCS5G_BR_10     MSCC_IO_OFFSET1(0x00060000) /*!< Base offset for target PCS5G_BR_10 */
#define MSCC_TO_PCS5G_BR_11     MSCC_IO_OFFSET1(0x0006c000) /*!< Base offset for target PCS5G_BR_11 */
#define MSCC_TO_PCS5G_BR_64     MSCC_IO_OFFSET1(0x0012c000) /*!< Base offset for target PCS5G_BR_64 */
#define MSCC_TO_PORT_CONF       MSCC_IO_OFFSET1(0x00130000) /*!< Base offset for target PORT_CONF */
#define MSCC_TO_QFWD            MSCC_IO_OFFSET1(0x010b0000) /*!< Base offset for target QFWD */
#define MSCC_TO_QRES            MSCC_IO_OFFSET1(0x01280000) /*!< Base offset for target QRES */
#define MSCC_TO_QSYS            MSCC_IO_OFFSET1(0x010a0000) /*!< Base offset for target QSYS */
#define MSCC_TO_REW             MSCC_IO_OFFSET1(0x01600000) /*!< Base offset for target REW */
#define MSCC_TO_SD_CMU_0        MSCC_IO_OFFSET1(0x00808000) /*!< Base offset for target SD_CMU_0 */
#define MSCC_TO_SD_CMU_CFG_0    MSCC_IO_OFFSET1(0x00850000) /*!< Base offset for target SD_CMU_CFG_0 */
#define MSCC_TO_SD_CMU_1        MSCC_IO_OFFSET1(0x00810000) /*!< Base offset for target SD_CMU_1 */
#define MSCC_TO_SD_CMU_CFG_1    MSCC_IO_OFFSET1(0x00858000) /*!< Base offset for target SD_CMU_CFG_1 */
#define MSCC_TO_SD_CMU_2        MSCC_IO_OFFSET1(0x00818000) /*!< Base offset for target SD_CMU_2 */
#define MSCC_TO_SD_CMU_CFG_2    MSCC_IO_OFFSET1(0x00860000) /*!< Base offset for target SD_CMU_CFG_2 */
#define MSCC_TO_SD_CMU_3        MSCC_IO_OFFSET1(0x00820000) /*!< Base offset for target SD_CMU_3 */
#define MSCC_TO_SD_CMU_CFG_3    MSCC_IO_OFFSET1(0x00868000) /*!< Base offset for target SD_CMU_CFG_3 */
#define MSCC_TO_SD_CMU_4        MSCC_IO_OFFSET1(0x00828000) /*!< Base offset for target SD_CMU_4 */
#define MSCC_TO_SD_CMU_CFG_4    MSCC_IO_OFFSET1(0x00870000) /*!< Base offset for target SD_CMU_CFG_4 */
#define MSCC_TO_SD_CMU_5        MSCC_IO_OFFSET1(0x00830000) /*!< Base offset for target SD_CMU_5 */
#define MSCC_TO_SD_CMU_CFG_5    MSCC_IO_OFFSET1(0x00878000) /*!< Base offset for target SD_CMU_CFG_5 */
#define MSCC_TO_SD_CMU_6        MSCC_IO_OFFSET1(0x00838000) /*!< Base offset for target SD_CMU_6 */
#define MSCC_TO_SD_CMU_CFG_6    MSCC_IO_OFFSET1(0x00880000) /*!< Base offset for target SD_CMU_CFG_6 */
#define MSCC_TO_SD_CMU_7        MSCC_IO_OFFSET1(0x00840000) /*!< Base offset for target SD_CMU_7 */
#define MSCC_TO_SD_CMU_CFG_7    MSCC_IO_OFFSET1(0x00888000) /*!< Base offset for target SD_CMU_CFG_7 */
#define MSCC_TO_SD_CMU_8        MSCC_IO_OFFSET1(0x00848000) /*!< Base offset for target SD_CMU_8 */
#define MSCC_TO_SD_CMU_CFG_8    MSCC_IO_OFFSET1(0x00890000) /*!< Base offset for target SD_CMU_CFG_8 */
#define MSCC_TO_SD_CMU_9        MSCC_IO_OFFSET1(0x00c08000) /*!< Base offset for target SD_CMU_9 */
#define MSCC_TO_SD_CMU_CFG_9    MSCC_IO_OFFSET1(0x00c30000) /*!< Base offset for target SD_CMU_CFG_9 */
#define MSCC_TO_SD_CMU_10       MSCC_IO_OFFSET1(0x00c10000) /*!< Base offset for target SD_CMU_10 */
#define MSCC_TO_SD_CMU_CFG_10   MSCC_IO_OFFSET1(0x00c38000) /*!< Base offset for target SD_CMU_CFG_10 */
#define MSCC_TO_SD_CMU_11       MSCC_IO_OFFSET1(0x00c18000) /*!< Base offset for target SD_CMU_11 */
#define MSCC_TO_SD_CMU_CFG_11   MSCC_IO_OFFSET1(0x00c40000) /*!< Base offset for target SD_CMU_CFG_11 */
#define MSCC_TO_SD_CMU_12       MSCC_IO_OFFSET1(0x00c20000) /*!< Base offset for target SD_CMU_12 */
#define MSCC_TO_SD_CMU_CFG_12   MSCC_IO_OFFSET1(0x00c48000) /*!< Base offset for target SD_CMU_CFG_12 */
#define MSCC_TO_SD_CMU_13       MSCC_IO_OFFSET1(0x00c28000) /*!< Base offset for target SD_CMU_13 */
#define MSCC_TO_SD_CMU_CFG_13   MSCC_IO_OFFSET1(0x00c50000) /*!< Base offset for target SD_CMU_CFG_13 */
#define MSCC_TO_SD6G_LANE_0     MSCC_IO_OFFSET1(0x00898000) /*!< Base offset for target SD6G_LANE_0 */
#define MSCC_TO_SD6G_LANE_1     MSCC_IO_OFFSET1(0x008a0000) /*!< Base offset for target SD6G_LANE_1 */
#define MSCC_TO_SD6G_LANE_2     MSCC_IO_OFFSET1(0x008a8000) /*!< Base offset for target SD6G_LANE_2 */
#define MSCC_TO_SD6G_LANE_3     MSCC_IO_OFFSET1(0x008b0000) /*!< Base offset for target SD6G_LANE_3 */
#define MSCC_TO_SD6G_LANE_4     MSCC_IO_OFFSET1(0x008b8000) /*!< Base offset for target SD6G_LANE_4 */
#define MSCC_TO_SD6G_LANE_5     MSCC_IO_OFFSET1(0x008c0000) /*!< Base offset for target SD6G_LANE_5 */
#define MSCC_TO_SD6G_LANE_6     MSCC_IO_OFFSET1(0x008c8000) /*!< Base offset for target SD6G_LANE_6 */
#define MSCC_TO_SD6G_LANE_7     MSCC_IO_OFFSET1(0x008d0000) /*!< Base offset for target SD6G_LANE_7 */
#define MSCC_TO_SD6G_LANE_8     MSCC_IO_OFFSET1(0x008d8000) /*!< Base offset for target SD6G_LANE_8 */
#define MSCC_TO_SD6G_LANE_9     MSCC_IO_OFFSET1(0x008e0000) /*!< Base offset for target SD6G_LANE_9 */
#define MSCC_TO_SD6G_LANE_10    MSCC_IO_OFFSET1(0x008e8000) /*!< Base offset for target SD6G_LANE_10 */
#define MSCC_TO_SD6G_LANE_11    MSCC_IO_OFFSET1(0x008f0000) /*!< Base offset for target SD6G_LANE_11 */
#define MSCC_TO_SD6G_LANE_12    MSCC_IO_OFFSET1(0x008f8000) /*!< Base offset for target SD6G_LANE_12 */
#define MSCC_TO_SD10G_LANE_0    MSCC_IO_OFFSET1(0x00900000) /*!< Base offset for target SD10G_LANE_0 */
#define MSCC_TO_SD10G_LANE_1    MSCC_IO_OFFSET1(0x00908000) /*!< Base offset for target SD10G_LANE_1 */
#define MSCC_TO_SD10G_LANE_2    MSCC_IO_OFFSET1(0x00910000) /*!< Base offset for target SD10G_LANE_2 */
#define MSCC_TO_SD10G_LANE_3    MSCC_IO_OFFSET1(0x00918000) /*!< Base offset for target SD10G_LANE_3 */
#define MSCC_TO_SD6G_KR_0       MSCC_IO_OFFSET1(0x00920000) /*!< Base offset for target SD6G_KR_0 */
#define MSCC_TO_SD6G_KR_1       MSCC_IO_OFFSET1(0x00928000) /*!< Base offset for target SD6G_KR_1 */
#define MSCC_TO_SD6G_KR_2       MSCC_IO_OFFSET1(0x00930000) /*!< Base offset for target SD6G_KR_2 */
#define MSCC_TO_SD6G_KR_3       MSCC_IO_OFFSET1(0x00938000) /*!< Base offset for target SD6G_KR_3 */
#define MSCC_TO_SD6G_KR_4       MSCC_IO_OFFSET1(0x00940000) /*!< Base offset for target SD6G_KR_4 */
#define MSCC_TO_SD6G_KR_5       MSCC_IO_OFFSET1(0x00948000) /*!< Base offset for target SD6G_KR_5 */
#define MSCC_TO_SD6G_KR_6       MSCC_IO_OFFSET1(0x00950000) /*!< Base offset for target SD6G_KR_6 */
#define MSCC_TO_SD6G_KR_7       MSCC_IO_OFFSET1(0x00958000) /*!< Base offset for target SD6G_KR_7 */
#define MSCC_TO_SD6G_KR_8       MSCC_IO_OFFSET1(0x00960000) /*!< Base offset for target SD6G_KR_8 */
#define MSCC_TO_SD6G_KR_9       MSCC_IO_OFFSET1(0x00968000) /*!< Base offset for target SD6G_KR_9 */
#define MSCC_TO_SD6G_KR_10      MSCC_IO_OFFSET1(0x00970000) /*!< Base offset for target SD6G_KR_10 */
#define MSCC_TO_SD6G_KR_11      MSCC_IO_OFFSET1(0x00978000) /*!< Base offset for target SD6G_KR_11 */
#define MSCC_TO_SD6G_KR_12      MSCC_IO_OFFSET1(0x00980000) /*!< Base offset for target SD6G_KR_12 */
#define MSCC_TO_SD10G_KR_0      MSCC_IO_OFFSET1(0x00988000) /*!< Base offset for target SD10G_KR_0 */
#define MSCC_TO_SD10G_KR_1      MSCC_IO_OFFSET1(0x00990000) /*!< Base offset for target SD10G_KR_1 */
#define MSCC_TO_SD10G_KR_2      MSCC_IO_OFFSET1(0x00998000) /*!< Base offset for target SD10G_KR_2 */
#define MSCC_TO_SD10G_KR_3      MSCC_IO_OFFSET1(0x009a0000) /*!< Base offset for target SD10G_KR_3 */
#define MSCC_TO_SD_LANE_0       MSCC_IO_OFFSET1(0x009a8000) /*!< Base offset for target SD_LANE_0 */
#define MSCC_TO_SD_LANE_1       MSCC_IO_OFFSET1(0x009b0000) /*!< Base offset for target SD_LANE_1 */
#define MSCC_TO_SD_LANE_2       MSCC_IO_OFFSET1(0x009b8000) /*!< Base offset for target SD_LANE_2 */
#define MSCC_TO_SD_LANE_3       MSCC_IO_OFFSET1(0x009c0000) /*!< Base offset for target SD_LANE_3 */
#define MSCC_TO_SD_LANE_4       MSCC_IO_OFFSET1(0x009c8000) /*!< Base offset for target SD_LANE_4 */
#define MSCC_TO_SD_LANE_5       MSCC_IO_OFFSET1(0x009d0000) /*!< Base offset for target SD_LANE_5 */
#define MSCC_TO_SD_LANE_6       MSCC_IO_OFFSET1(0x009d8000) /*!< Base offset for target SD_LANE_6 */
#define MSCC_TO_SD_LANE_7       MSCC_IO_OFFSET1(0x009e0000) /*!< Base offset for target SD_LANE_7 */
#define MSCC_TO_SD_LANE_8       MSCC_IO_OFFSET1(0x009e8000) /*!< Base offset for target SD_LANE_8 */
#define MSCC_TO_SD_LANE_9       MSCC_IO_OFFSET1(0x009f0000) /*!< Base offset for target SD_LANE_9 */
#define MSCC_TO_SD_LANE_10      MSCC_IO_OFFSET1(0x009f8000) /*!< Base offset for target SD_LANE_10 */
#define MSCC_TO_SD_LANE_11      MSCC_IO_OFFSET1(0x00a00000) /*!< Base offset for target SD_LANE_11 */
#define MSCC_TO_SD_LANE_12      MSCC_IO_OFFSET1(0x00a08000) /*!< Base offset for target SD_LANE_12 */
#define MSCC_TO_SD_LANE_13      MSCC_IO_OFFSET1(0x00a10000) /*!< Base offset for target SD_LANE_13 */
#define MSCC_TO_SD_LANE_14      MSCC_IO_OFFSET1(0x00a18000) /*!< Base offset for target SD_LANE_14 */
#define MSCC_TO_SD_LANE_15      MSCC_IO_OFFSET1(0x00a20000) /*!< Base offset for target SD_LANE_15 */
#define MSCC_TO_SD_LANE_16      MSCC_IO_OFFSET1(0x00a28000) /*!< Base offset for target SD_LANE_16 */
#define MSCC_TO_SD10G_LANE_4    MSCC_IO_OFFSET1(0x00c58000) /*!< Base offset for target SD10G_LANE_4 */
#define MSCC_TO_SD10G_LANE_5    MSCC_IO_OFFSET1(0x00c60000) /*!< Base offset for target SD10G_LANE_5 */
#define MSCC_TO_SD10G_LANE_6    MSCC_IO_OFFSET1(0x00c68000) /*!< Base offset for target SD10G_LANE_6 */
#define MSCC_TO_SD10G_LANE_7    MSCC_IO_OFFSET1(0x00c70000) /*!< Base offset for target SD10G_LANE_7 */
#define MSCC_TO_SD10G_LANE_8    MSCC_IO_OFFSET1(0x00c78000) /*!< Base offset for target SD10G_LANE_8 */
#define MSCC_TO_SD10G_LANE_9    MSCC_IO_OFFSET1(0x00c80000) /*!< Base offset for target SD10G_LANE_9 */
#define MSCC_TO_SD10G_LANE_10   MSCC_IO_OFFSET1(0x00c88000) /*!< Base offset for target SD10G_LANE_10 */
#define MSCC_TO_SD10G_LANE_11   MSCC_IO_OFFSET1(0x00c90000) /*!< Base offset for target SD10G_LANE_11 */
#define MSCC_TO_SD10G_KR_4      MSCC_IO_OFFSET1(0x00cd8000) /*!< Base offset for target SD10G_KR_4 */
#define MSCC_TO_SD10G_KR_5      MSCC_IO_OFFSET1(0x00ce0000) /*!< Base offset for target SD10G_KR_5 */
#define MSCC_TO_SD10G_KR_6      MSCC_IO_OFFSET1(0x00ce8000) /*!< Base offset for target SD10G_KR_6 */
#define MSCC_TO_SD10G_KR_7      MSCC_IO_OFFSET1(0x00cf0000) /*!< Base offset for target SD10G_KR_7 */
#define MSCC_TO_SD10G_KR_8      MSCC_IO_OFFSET1(0x00cf8000) /*!< Base offset for target SD10G_KR_8 */
#define MSCC_TO_SD10G_KR_9      MSCC_IO_OFFSET1(0x00d00000) /*!< Base offset for target SD10G_KR_9 */
#define MSCC_TO_SD10G_KR_10     MSCC_IO_OFFSET1(0x00d08000) /*!< Base offset for target SD10G_KR_10 */
#define MSCC_TO_SD10G_KR_11     MSCC_IO_OFFSET1(0x00d10000) /*!< Base offset for target SD10G_KR_11 */
#define MSCC_TO_SD_LANE_17      MSCC_IO_OFFSET1(0x00d58000) /*!< Base offset for target SD_LANE_17 */
#define MSCC_TO_SD_LANE_18      MSCC_IO_OFFSET1(0x00d60000) /*!< Base offset for target SD_LANE_18 */
#define MSCC_TO_SD_LANE_19      MSCC_IO_OFFSET1(0x00d68000) /*!< Base offset for target SD_LANE_19 */
#define MSCC_TO_SD_LANE_20      MSCC_IO_OFFSET1(0x00d70000) /*!< Base offset for target SD_LANE_20 */
#define MSCC_TO_SD_LANE_21      MSCC_IO_OFFSET1(0x00d78000) /*!< Base offset for target SD_LANE_21 */
#define MSCC_TO_SD_LANE_22      MSCC_IO_OFFSET1(0x00d80000) /*!< Base offset for target SD_LANE_22 */
#define MSCC_TO_SD_LANE_23      MSCC_IO_OFFSET1(0x00d88000) /*!< Base offset for target SD_LANE_23 */
#define MSCC_TO_SD_LANE_24      MSCC_IO_OFFSET1(0x00d90000) /*!< Base offset for target SD_LANE_24 */
#define MSCC_TO_SD25G_LANE_0    MSCC_IO_OFFSET1(0x00c98000) /*!< Base offset for target SD25G_LANE_0 */
#define MSCC_TO_SD25G_LANE_1    MSCC_IO_OFFSET1(0x00ca0000) /*!< Base offset for target SD25G_LANE_1 */
#define MSCC_TO_SD25G_LANE_2    MSCC_IO_OFFSET1(0x00ca8000) /*!< Base offset for target SD25G_LANE_2 */
#define MSCC_TO_SD25G_LANE_3    MSCC_IO_OFFSET1(0x00cb0000) /*!< Base offset for target SD25G_LANE_3 */
#define MSCC_TO_SD25G_LANE_4    MSCC_IO_OFFSET1(0x00cb8000) /*!< Base offset for target SD25G_LANE_4 */
#define MSCC_TO_SD25G_LANE_5    MSCC_IO_OFFSET1(0x00cc0000) /*!< Base offset for target SD25G_LANE_5 */
#define MSCC_TO_SD25G_LANE_6    MSCC_IO_OFFSET1(0x00cc8000) /*!< Base offset for target SD25G_LANE_6 */
#define MSCC_TO_SD25G_LANE_7    MSCC_IO_OFFSET1(0x00cd0000) /*!< Base offset for target SD25G_LANE_7 */
#define MSCC_TO_SD10G_KR_12     MSCC_IO_OFFSET1(0x00d18000) /*!< Base offset for target SD10G_KR_12 */
#define MSCC_TO_SD10G_KR_13     MSCC_IO_OFFSET1(0x00d20000) /*!< Base offset for target SD10G_KR_13 */
#define MSCC_TO_SD10G_KR_14     MSCC_IO_OFFSET1(0x00d28000) /*!< Base offset for target SD10G_KR_14 */
#define MSCC_TO_SD10G_KR_15     MSCC_IO_OFFSET1(0x00d30000) /*!< Base offset for target SD10G_KR_15 */
#define MSCC_TO_SD10G_KR_16     MSCC_IO_OFFSET1(0x00d38000) /*!< Base offset for target SD10G_KR_16 */
#define MSCC_TO_SD10G_KR_17     MSCC_IO_OFFSET1(0x00d40000) /*!< Base offset for target SD10G_KR_17 */
#define MSCC_TO_SD10G_KR_18     MSCC_IO_OFFSET1(0x00d48000) /*!< Base offset for target SD10G_KR_18 */
#define MSCC_TO_SD10G_KR_19     MSCC_IO_OFFSET1(0x00d50000) /*!< Base offset for target SD10G_KR_19 */
#define MSCC_TO_SD_LANE_25      MSCC_IO_OFFSET1(0x00d98000) /*!< Base offset for target SD_LANE_25 */
#define MSCC_TO_SD_LANE_26      MSCC_IO_OFFSET1(0x00da0000) /*!< Base offset for target SD_LANE_26 */
#define MSCC_TO_SD_LANE_27      MSCC_IO_OFFSET1(0x00da8000) /*!< Base offset for target SD_LANE_27 */
#define MSCC_TO_SD_LANE_28      MSCC_IO_OFFSET1(0x00db0000) /*!< Base offset for target SD_LANE_28 */
#define MSCC_TO_SD_LANE_29      MSCC_IO_OFFSET1(0x00db8000) /*!< Base offset for target SD_LANE_29 */
#define MSCC_TO_SD_LANE_30      MSCC_IO_OFFSET1(0x00dc0000) /*!< Base offset for target SD_LANE_30 */
#define MSCC_TO_SD_LANE_31      MSCC_IO_OFFSET1(0x00dc8000) /*!< Base offset for target SD_LANE_31 */
#define MSCC_TO_SD_LANE_32      MSCC_IO_OFFSET1(0x00dd0000) /*!< Base offset for target SD_LANE_32 */
#define MSCC_TO_SDPCIE_PHY      MSCC_IO_OFFSET2(0x0010b000) /*!< Base offset for target SDPCIE_PHY */
#define MSCC_TO_SDPCIE_PMA      MSCC_IO_OFFSET1(0x00de0000) /*!< Base offset for target SDPCIE_PMA */
#define MSCC_TO_SIMC            MSCC_IO_OFFSET2(0x00104000) /*!< Base offset for target SIMC */
#define MSCC_TO_SUBCPU          MSCC_IO_OFFSET3(0x00030000) /*!< Base offset for target SUBCPU */
#define MSCC_TO_SUBCPU_SIMC     MSCC_IO_OFFSET3(0x00010800) /*!< Base offset for target SUBCPU_SIMC */
#define MSCC_TO_SUBCPU_SIMC2    MSCC_IO_OFFSET3(0x00011400) /*!< Base offset for target SUBCPU_SIMC2 */
#define MSCC_TO_SUBCPU_TIMERS   MSCC_IO_OFFSET3(0x00010c00) /*!< Base offset for target SUBCPU_TIMERS */
#define MSCC_TO_SUBCPU_TWI      MSCC_IO_OFFSET3(0x00010400) /*!< Base offset for target SUBCPU_TWI */
#define MSCC_TO_SUBCPU_UART     MSCC_IO_OFFSET3(0x00010000) /*!< Base offset for target SUBCPU_UART */
#define MSCC_TO_SUBCPU_WDT      MSCC_IO_OFFSET3(0x00011000) /*!< Base offset for target SUBCPU_WDT */
#define MSCC_TO_TIMERS          MSCC_IO_OFFSET2(0x00105000) /*!< Base offset for target TIMERS */
#define MSCC_TO_TRNG            MSCC_IO_OFFSET2(0x0010c000) /*!< Base offset for target TRNG */
#define MSCC_TO_TWI             MSCC_IO_OFFSET2(0x00101000) /*!< Base offset for target TWI */
#define MSCC_TO_TWI2            MSCC_IO_OFFSET2(0x00103000) /*!< Base offset for target TWI2 */
#define MSCC_TO_UART            MSCC_IO_OFFSET2(0x00100000) /*!< Base offset for target UART */
#define MSCC_TO_UART2           MSCC_IO_OFFSET2(0x00102000) /*!< Base offset for target UART2 */
#define MSCC_TO_VCAP_ES0        MSCC_IO_OFFSET1(0x010e0000) /*!< Base offset for target VCAP_ES0 */
#define MSCC_TO_VCAP_ES2        MSCC_IO_OFFSET1(0x010d0000) /*!< Base offset for target VCAP_ES2 */
#define MSCC_TO_VCAP_IP6PFX     MSCC_IO_OFFSET1(0x01090000) /*!< Base offset for target VCAP_IP6PFX */
#define MSCC_TO_VCAP_SUPER      MSCC_IO_OFFSET1(0x01080000) /*!< Base offset for target VCAP_SUPER */
#define MSCC_TO_VOP             MSCC_IO_OFFSET1(0x01a00000) /*!< Base offset for target VOP */
#define MSCC_TO_VOP_L3          MSCC_IO_OFFSET1(0x01b00000) /*!< Base offset for target VOP_L3 */
#define MSCC_TO_VOP_MPLS        MSCC_IO_OFFSET1(0x01680000) /*!< Base offset for target VOP_MPLS */
#define MSCC_TO_XQS             MSCC_IO_OFFSET1(0x010c0000) /*!< Base offset for target XQS */

/* IO address mapping macro - may be changed for platform */
#if !defined(MSCC_IOADDR)
#define MSCC_IOADDR(t,o)        ((t) + ((o) << 2))
#endif

/* IO register access macro - may be changed for platform */
#if !defined(MSCC_IOREG)
/**
 * @param t - target base offset
 * @param o - subtarget offset
 */
#define MSCC_IOREG(t,o)      ((void*) ( MSCC_IOADDR(t,o)))
#endif

/* IO indexed register access macro - may be changed for platform */
#if !defined(MSCC_IOREG_IX)
/**
 * @param t  - target base offset
 * @param o  - subtarget offset
 * @param g  - group instance,
 * @param gw - group width
 * @param ro - register offset,
 * @param r  - register (instance) number
 */
#define MSCC_IOREG_IX(t,o,g,gw,r,ro)   MSCC_IOREG(t,(o) + ((g) * (gw)) + (ro) + (r))
#endif

#endif /* _MSCC_FA_REGS_COMMON_H_ */
