// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Microsemi Corporation
 */
#include "vtss_fireant_regs_sd_cmu_term_target.h"
#include "vtss_fireant_regs_sd_lane_target.h"
#include "vtss_fireant_regs_sd10g_cmu_target.h"
#include "vtss_fireant_regs_sd10g_lane_target.h"

typedef struct vtss_state * vtss_state_t;
typedef int vtss_rc;
typedef int vtss_port_no_t;

#define VTSS_RC_OK 0
#define VTSS_RC_ERROR -1

#define VTSS_E printf
#define VTSS_D debug

#define VTSS_TO_SD_CMU(x)        ((void *)vtss_to_sd_cmu(x))
#define VTSS_TO_SD_CMU_CFG(x)    ((void *)vtss_to_sd_cmu_cfg(x))
#define VTSS_TO_SD6G_LANE(indx)  ((void *)vtss_to_sd6g_lane(indx))
#define VTSS_TO_SD_LANE(indx)    ((void *)vtss_to_sd_lane(indx))
#define VTSS_TO_SD10G_LANE(indx) ((void *)vtss_to_sd10g_lane(indx))

#define VTSS_SERDES_10G_START 13
#define VTSS_SERDES_25G_START 25

/** \brief return values of setup function */
typedef struct {
    u8 cmu_sel[1];
    //u8 is_6g[1];
    u8 skip_cmu_cfg[1];
    u8 cfg_lane_reserve_7_0[1]     ;  // LSB:
    u8 cfg_ssc_rtl_clk_sel[1]     ;  // MSB:
    u8 cfg_lane_reserve_15_8[1]    ; //Bit 9 controls Duty cycle; Silicon Dependend this needs to be corrected

    //r_DwidthCtrl_from_hwt related signals
    //TX and RX rate selection towards network interface
    u8 cfg_txrate_1_0[1];
    u8 cfg_rxrate_1_0[1];

    //UDL interface configuration bitwidth, tx and rx clock selection, phymode selection
    u8 r_DwidthCtrl_2_0[1];
    u8 cfg_pma_tx_ck_bitwidth_2_0[1];
    u8 cfg_rxdiv_sel_2_0[1]         ;

    u8 r_pcs2pma_phymode_4_0[1];

    u8 cfg_lane_id_2_0[1];//  Bias Trace Selection

    //r_reg_manual related signals
    u8 cfg_cdrck_en[1]         ;
    u8 cfg_dfeck_en[1]         ;
    u8 cfg_dfe_pd[1]           ;
    u8 cfg_dfetap_en_5_1[1]    ;
    u8 cfg_erramp_pd[1]        ;
    u8 cfg_pi_DFE_en[1]       ;
    u8 cfg_pi_en[1]           ;
    u8 cfg_pd_ctle[1]         ;
    u8 cfg_summer_en[1]        ;
    u8 cfg_pd_rx_cktree[1]     ;
    u8 cfg_pd_clk[1]           ;
    u8 cfg_pd_cml[1]           ;
    u8 cfg_pd_driver[1]        ;
    u8 cfg_rx_reg_pu[1]        ;
    u8 cfg_Dcdr_pd[1]          ;
    u8 cfg_pd_sq[1]            ;
    u8 cfg_rxdet_en[1]         ;
    u8 cfg_rxdet_str[1]        ;
    u8 r_multi_lane_mode[1]    ;

    //r_txeq_reg related signals
    u8 cfg_en_adv[1]     ;
    u8 cfg_en_main[1]    ;
    u8 cfg_en_dly[1]     ;
    u8 cfg_tap_adv_3_0[1];
    u8 cfg_tap_main[1]   ;
    u8 cfg_tap_dly_4_0[1];

    //r_rxeq_reg related signals there are for SR and DFE needs to be enabled for LR/MR
    //DFE is enabled for 10G
    u8 cfg_vga_ctrl_3_0[1]   ;
    u8 cfg_vga_cp_2_0[1]     ;
    u8 cfg_eq_res_3_0[1];    //CTLE gain control.
    u8 cfg_eqR_byp[1]        ;
    u8 cfg_eqC_force_3_0[1]  ;
    u8 cfg_en_dfedig[1]      ;
    u8 cfg_sum_setcm_en[1]   ;

    //r_misc_reg
    u8 cfg_en_preemph[1];   //Unused in current IP as per Tony 08/29/2018.
    u8 cfg_itx_ippreemp_base_1_0[1]; //Unused in current IP as per Tony 08/29/2018.

    //r_swing_reg;
    u8 cfg_itx_ipdriver_base_2_0[1]           ;
    u8 cfg_ibias_tune_reserve_5_0[1]          ;
    u8 cfg_txswing_half[1]                    ;

    //r_cdr_from_hwt this is cfg controlled.
    u8 cfg_dis_2ndOrder[1]      ;              //  2nd order CDR disable signal.
    u8 cfg_rx_ssc_lh[1]         ;              //  CDR operation rate selection
    u8 cfg_pi_floop_steps_1_0[1] ;             //  Frequency loop PI step selection
    u8 cfg_pi_ext_dac_23_16[1]  ;     //  2nd order CDR digital lowpass filter select
    u8 cfg_pi_ext_dac_15_8[1]     ;   //  2nd order CDR digital lowpass filter select
    u8 cfg_iscan_ext_dac_7_0[1]  ;     //CDR clock phase tuning parameter; Silicon Dependend;

    //RX CDR  and TX driver register Settings
    u8 cfg_cdr_kf_gen1_2_0[1]  ;   //CDR 1st order Gain Adjust GEN1
    u8 cfg_cdr_kf_gen2_2_0[1]  ;   //CDR 1st order Gain Adjust GEN2
    u8 cfg_cdr_kf_gen3_2_0[1]  ;   //CDR 1st order Gain Adjust GEN3
    u8 cfg_cdr_kf_gen4_2_0[1]  ;   //CDR 1st order Gain Adjust GEN4
    u8 r_cdr_m_gen1_7_0[1]     ;   //CDR 1st order LP filter select GEN1
    u8 cfg_pi_bw_gen1_3_0[1]   ;   //CDR PI BW Adj. GEN1 Silicon Dependend
    u8 cfg_pi_bw_gen2[1]      ;    //CDR PI BW Adj. GEN2
    u8 cfg_pi_bw_gen3[1]      ;    //CDR PI BW Adj. GEN3
    u8 cfg_pi_bw_gen4[1]      ;    //CDR PI BW Adj. GEN4
    //u8 cfg_iscan_ext_dac_7_0[1];   //Already configured
    u8 cfg_pi_ext_dac_7_0[1]   ;   //DFE clock phase tuning parameter; Silicon Dependend;
    u8 cfg_pi_steps[1]            ;
    u8 cfg_mp_max_3_0[1]          ;
    u8 cfg_rstn_dfedig[1]     ;    // DFE Reset; it is reset automatically after assert and release of pclk_gating

    u8 cfg_alos_thr_3_0[1]     ;             //Voltage threshold for squelch detection

    u8 cfg_predrv_slewrate_1_0[1] ;          // ??
    u8 cfg_itx_ipcml_base_1_0[1]  ;          // predriver current setting in TX
    u8 cfg_ip_pre_base_1_0[1]     ;          // ??

    u8 r_cdr_m_gen2_7_0[1]        ;  //  CDR 1st order LP filter select GEN2
    u8 r_cdr_m_gen3_7_0[1]        ;  //  CDR 1st order LP filter select GEN3
    u8 r_cdr_m_gen4_7_0[1]        ;  //  CDR 1st order LP filter select GEN4

    u8 r_en_auto_cdr_rstn[1]     ;           //  Lane CDR auto reset function enable

    u8 cfg_oscal_afe[1]          ;
    u8 cfg_pd_osdac_afe[1]       ;
    u8 cfg_resetb_oscal_afe[2]   ;

    // TX SSC
    u8 cfg_center_spreading[1] ;  //  Lane SSC type selection
    u8 cfg_McntMaxVal_4_0[1]    ; //  Lane SSC spreading range contrl
    u8 cfg_ncntMaxVal_7_0[1]   ;
    u8 cfg_ncntMaxVal_10_8[1]   ;
    u8 cfg_ssc_en[1]          ;    //  Lane SSC Enable

    u8 cfg_tx2rx_lp_en[1];    //LM1
    u8 cfg_txlb_en[1]    ;


    u8 cfg_rx2tx_lp_en[1];     //LSx
    u8 cfg_rxlb_en[1]    ;
    u8 r_tx_pol_inv[1];
    u8 r_rx_pol_inv[1];
} vtss_sd10g28_setup_struct_t;

static inline void VTSS_MSLEEP(int n)
{
	udelay(n * 1000);
}

#define REG_RD(i, p) _reg_rd(i, p)
static inline void _reg_rd(void *io, u32 *valp)
{
	u32 val = readl(io);
	//printf("REG_RD(%p) = 0x%08x\n", io, val);
	*valp = val;
}

#define REG_WRM(i, v, m) _reg_wrm(i, v, m)
static inline void _reg_wrm(void *io, u32 v, u32 m)
{
	u32 val = readl(io);
	val = (val & ~m) | (v & m);
	//printf("writel(0x%09llx, 0x%08x)\n", (u64) io, val);
	writel(val, io);
}

static inline u64 vtss_to_sd_cmu(u32 indx)
{
	switch (indx) {
	case 0: return VTSS_TO_SD_CMU_0;
	case 1: return VTSS_TO_SD_CMU_1;
	case 2: return VTSS_TO_SD_CMU_2;
	case 3: return VTSS_TO_SD_CMU_3;
	case 4: return VTSS_TO_SD_CMU_4;
	case 5: return VTSS_TO_SD_CMU_5;
	case 6: return VTSS_TO_SD_CMU_6;
	case 7: return VTSS_TO_SD_CMU_7;
	case 8: return VTSS_TO_SD_CMU_8;
	case 9: return VTSS_TO_SD_CMU_9;
	case 10: return VTSS_TO_SD_CMU_10;
	case 11: return VTSS_TO_SD_CMU_11;
	case 12: return VTSS_TO_SD_CMU_12;
	case 13: return VTSS_TO_SD_CMU_13;
	default:
		VTSS_E("illegal sd_cmu index %d",indx);
		return 0;
	}
}

static inline u64 vtss_to_sd_cmu_cfg(u32 indx)
{
	switch (indx) {
	case 0: return VTSS_TO_SD_CMU_CFG_0;
	case 1: return VTSS_TO_SD_CMU_CFG_1;
	case 2: return VTSS_TO_SD_CMU_CFG_2;
	case 3: return VTSS_TO_SD_CMU_CFG_3;
	case 4: return VTSS_TO_SD_CMU_CFG_4;
	case 5: return VTSS_TO_SD_CMU_CFG_5;
	case 6: return VTSS_TO_SD_CMU_CFG_6;
	case 7: return VTSS_TO_SD_CMU_CFG_7;
	case 8: return VTSS_TO_SD_CMU_CFG_8;
	case 9: return VTSS_TO_SD_CMU_CFG_9;
	case 10: return VTSS_TO_SD_CMU_CFG_10;
	case 11: return VTSS_TO_SD_CMU_CFG_11;
	case 12: return VTSS_TO_SD_CMU_CFG_12;
	case 13: return VTSS_TO_SD_CMU_CFG_13;
	default:
		VTSS_E("illegal sd_cmu index %d",indx);
		return 0;
	}
}

u64 vtss_to_sd6g_lane(u32 indx)
{
    switch (indx) {
    case 0:  return VTSS_TO_SD6G_LANE_0;
    case 1:  return VTSS_TO_SD6G_LANE_1;
    case 2:  return VTSS_TO_SD6G_LANE_2;
    case 3:  return VTSS_TO_SD6G_LANE_3;
    case 4:  return VTSS_TO_SD6G_LANE_4;
    case 5:  return VTSS_TO_SD6G_LANE_5;
    case 6:  return VTSS_TO_SD6G_LANE_6;
    case 7:  return VTSS_TO_SD6G_LANE_7;
    case 8:  return VTSS_TO_SD6G_LANE_8;
    case 9:  return VTSS_TO_SD6G_LANE_9;
    case 10: return VTSS_TO_SD6G_LANE_10;
    case 11: return VTSS_TO_SD6G_LANE_11;
    case 12: return VTSS_TO_SD6G_LANE_12;
    default:
        VTSS_E("illegal 6G_lane index %d",indx);
        return 0;
    }
}

u64 vtss_to_sd_lane(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_LANE_0;
    case 1: return VTSS_TO_SD_LANE_1;
    case 2: return VTSS_TO_SD_LANE_2;
    case 3: return VTSS_TO_SD_LANE_3;
    case 4: return VTSS_TO_SD_LANE_4;
    case 5: return VTSS_TO_SD_LANE_5;
    case 6: return VTSS_TO_SD_LANE_6;
    case 7: return VTSS_TO_SD_LANE_7;
    case 8: return VTSS_TO_SD_LANE_8;
    case 9: return VTSS_TO_SD_LANE_9;
    case 10: return VTSS_TO_SD_LANE_10;
    case 11: return VTSS_TO_SD_LANE_11;
    case 12: return VTSS_TO_SD_LANE_12;
    case 13: return VTSS_TO_SD_LANE_13;
    case 14: return VTSS_TO_SD_LANE_14;
    case 15: return VTSS_TO_SD_LANE_15;
    case 16: return VTSS_TO_SD_LANE_16;
    case 17: return VTSS_TO_SD_LANE_17;
    case 18: return VTSS_TO_SD_LANE_18;
    case 19: return VTSS_TO_SD_LANE_19;
    case 20: return VTSS_TO_SD_LANE_20;
    case 21: return VTSS_TO_SD_LANE_21;
    case 22: return VTSS_TO_SD_LANE_22;
    case 23: return VTSS_TO_SD_LANE_23;
    case 24: return VTSS_TO_SD_LANE_24;
    case 25: return VTSS_TO_SD_LANE_25;
    case 26: return VTSS_TO_SD_LANE_26;
    case 27: return VTSS_TO_SD_LANE_27;
    case 28: return VTSS_TO_SD_LANE_28;
    case 29: return VTSS_TO_SD_LANE_29;
    case 30: return VTSS_TO_SD_LANE_30;
    case 31: return VTSS_TO_SD_LANE_31;
    case 32: return VTSS_TO_SD_LANE_32;
    default:
        VTSS_E("illegal sd_lane index %d",indx);
        return 0;
    }
}

u64 vtss_to_sd10g_lane(u32 indx)
{
    switch (indx) {
    case 0:  return VTSS_TO_SD10G_LANE_0;
    case 1:  return VTSS_TO_SD10G_LANE_1;
    case 2:  return VTSS_TO_SD10G_LANE_2;
    case 3:  return VTSS_TO_SD10G_LANE_3;
    case 4:  return VTSS_TO_SD10G_LANE_4;
    case 5:  return VTSS_TO_SD10G_LANE_5;
    case 6:  return VTSS_TO_SD10G_LANE_6;
    case 7:  return VTSS_TO_SD10G_LANE_7;
    case 8:  return VTSS_TO_SD10G_LANE_8;
    case 9:  return VTSS_TO_SD10G_LANE_9;
    case 10: return VTSS_TO_SD10G_LANE_10;
    case 11: return VTSS_TO_SD10G_LANE_11;
    default:
        VTSS_E("illegal 10G_lane index %d",indx);
        return 0;
    }

}
