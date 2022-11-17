// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Microsemi Corporation
 */
//#define READ_DEBUG
//#define WRITE_DEBUG
//#define READ_STATUS_REGISTERS

#include <common.h>
#include <asm/io.h>
#include <debug_uart.h>
#include <command.h>

#include "ddr.h"

#define VTSS_IOREG(t,o)      ((void*)(VTSS_IOADDR(t,o)))
#include "vtss_fireant_regs_ddr_umctl2.h"
#include "vtss_fireant_regs_ddr_phy.h"
#include "vtss_fireant_regs_cpu.h"
#include "vtss_fireant_regs_clkgen.h"

#include "reg_acc_primitives.h"

#define ROUND_VAL(x) ((uint32_t)((x)+0.5))
#define FLOOR_VAL(x) ((uint32_t)(x))
#define CEIL_VAL(x)  ((uint32_t)((x)+0.999999))

inline static uint8_t PHY_initialization(void);
inline static uint8_t DRAM_initialization_by_pub(void);
inline static uint8_t DRAM_initialization_by_memctrl(void);
inline static uint32_t DATA_training(void);
inline static void config_PHY_initialization_reg(void);
inline static void config_DRAMinit_and_DATAtraining_reg(void);
inline static void config_ddr34_memory_controller_reg(void);

#define params_2T_mode 1
#define params_clk_div   CONFIG_DDR_FIREANT_CLK_DIV
#undef  params_ecc_mode
#define params_ecc_mode 4

/* Enforce 16-bit mode if configured */
#if defined(CONFIG_DDR_FIREANT_16BIT)
#undef params_ecc_mode
#undef params_dq_bits_used
#define params_ecc_mode		0
#define params_dq_bits_used	16
#endif

#define __x(s)   #s
#define mkstr(x) __x(x)
#define DDR_TYPE "DDR" mkstr(params_mem_type)

#define CPU_CLK_NS 1

#define DW_APB_LOAD_VAL		(VTSS_TO_TIMERS + (0*4))
#define DW_APB_CURR_VAL		(VTSS_TO_TIMERS + (1*4))
#define DW_APB_CTRL		(VTSS_TO_TIMERS + (2*4))
#define DW_APB_EOI		(VTSS_TO_TIMERS + (3*4))
#define DW_APB_INTSTAT		(VTSS_TO_TIMERS + (4*4))

#define CLOC_SPEED	(250 * 1000000) /* 250Mhz */
#define NS_PER_TICK	(1000000000/CLOC_SPEED) /* ns = (10 ** 9), ns/tick = 4 */
#define usec2ns(x)	(x * 1000)

static inline void my_wait(u32 t_nsec, const uint16_t msg)
{
#if defined(DEBUG)
	my_print(WAIT_START, msg);
#endif
	/* init timer */
	t_nsec /= NS_PER_TICK;
	writel(t_nsec, DW_APB_LOAD_VAL);
	writel(0xffffffff, DW_APB_CURR_VAL);
	setbits_le32(DW_APB_CTRL, 0x3);
	while (readl(DW_APB_INTSTAT) == 0)
		;
	clrbits_le32(DW_APB_CTRL, 0x3);
	(void) readl(DW_APB_EOI);
#if defined(DEBUG)
	my_print(WAIT_FINISH, msg);
#endif
}

uint8_t DDR_initialization(void) {
  uint32_t var;
  // Check if already booting from DDR therefore DDR is initialized
  if (rd_fld_r(CPU, CPU_REGS, GENERAL_CTRL, BOOT_MODE_ENA) == 0) {
    return 1;
  }

  if (_DDR_DUMMY) {
    return 1;
  } else {
    // After power-up:
    // 1. Assert the resets (presetn, core_ddrc_rstn, aresetn_n)
    // 2. Start the clocks (pclk, core_ddrc_core_clk, aclk_n)
    // 3. Deassert presetn once the clocks are active and stable
    // 4. Allow 10 cycles for synchronization of presetn to core_ddrc_core_clk and aclk domains and to permit
    // initialization of end logic.
    // 5. Initialize the registers
    // 6. Deassert the resets (core_ddrc_rstn and aresetn_n)

    // Assert resets
    var = wr_fld_r_s (      CPU,DDRCTRL, DDRCTRL_RST, DDRC_RST      , 1);
    var = wr_fld_s_s ( var, CPU,DDRCTRL, DDRCTRL_RST, DDR_AXI_RST   , 1);
    var = wr_fld_s_s ( var, CPU,DDRCTRL, DDRCTRL_RST, DDR_APB_RST   , 1);
    var = wr_fld_s_s ( var, CPU,DDRCTRL, DDRCTRL_RST, DDRPHY_CTL_RST, 1);
    wr_fld_s_r       ( var, CPU,DDRCTRL, DDRCTRL_RST, DDRPHY_APB_RST, 1);

    // Start the clocks
    var = wr_fld_r_s (      CPU, DDRCTRL, DDRCTRL_CLK, DDR_CLK_ENA       , 1);
    var = wr_fld_s_s ( var, CPU, DDRCTRL, DDRCTRL_CLK, DDR_AXI_CLK_ENA   , 1);
    var = wr_fld_s_s ( var, CPU, DDRCTRL, DDRCTRL_CLK, DDR_APB_CLK_ENA   , 1);
    var = wr_fld_s_s ( var, CPU, DDRCTRL, DDRCTRL_CLK, DDRPHY_CTL_CLK_ENA, 1);
    wr_fld_s_r       ( var, CPU, DDRCTRL, DDRCTRL_CLK, DDRPHY_APB_CLK_ENA, 1);

    my_wait(100,0xA0);

    // Deassert presetn once the clocks are active and stable
    wr_fld_r_r (CPU, DDRCTRL, DDRCTRL_RST, DDR_APB_RST, 0);

    my_wait(50,0xA1);

    config_ddr34_memory_controller_reg(); //## Configure Memory Controller Register for DDR3/4

    my_wait(200,0xA2);

    wr_fld_r_r (CPU, CPU_REGS, RESET, MEM_RST, 0); // ## Deassert the core_ddrc_rstn reset

    var = wr_fld_r_s (      CPU, DDRCTRL, DDRCTRL_RST, DDRC_RST   , 0  );
    wr_reg           (      CPU, DDRCTRL, DDRCTRL_RST,              var);
    var = wr_fld_s_s ( var, CPU, DDRCTRL, DDRCTRL_RST, DDR_AXI_RST, 0  );
    wr_reg           (      CPU, DDRCTRL, DDRCTRL_RST,              var);

    my_wait(100,0xA3);

    var = wr_fld_s_s ( var, CPU, DDRCTRL, DDRCTRL_RST, DDRPHY_APB_RST, 0  );
    wr_reg           (      CPU, DDRCTRL, DDRCTRL_RST,                 var);
    var = wr_fld_s_s ( var, CPU, DDRCTRL, DDRCTRL_RST, DDRPHY_CTL_RST, 0  );
    wr_reg           (      CPU, DDRCTRL, DDRCTRL_RST,                 var);

    my_wait(100,0xA4);

    if (params_PHY_init) {

      config_PHY_initialization_reg();              // ## Configure PUB/PHY register for initialization

      //################ SDRAM Initialization  ###########################
      if (PHY_initialization()) {           // ## check PHY initialization status
         my_wait(CEIL_VAL(32*params_ctl_clk_period),0xA5);  // ## wait atleast 32 ctrl_clk cycle
        if (init_by_pub) {
            if (DRAM_initialization_by_pub() == 0) {
                my_print(ERROR_MSG,2);
                return 0;
            }
        } else {
            if (DRAM_initialization_by_memctrl() == 0) {
                my_print(ERROR_MSG,3);
                return 0;
            }
        }
      } else {
          my_print(ERROR_MSG,1);
          return 0;
      }
    }

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              0  );
    wr_reg           (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,                         var);
    if (!params_PHY_init) {
      wr_fld_r_r       (      DDR_UMCTL2, UMCTL2_REGS, DFIMISC, DFI_INIT_START,       1  );
    }
    wr_fld_r_r       (      DDR_UMCTL2, UMCTL2_REGS, DFIMISC, DFI_INIT_COMPLETE_EN, 1  );
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              1  );

    // wait for SWSTAT.sw_done_ack to become '1'
    uint32_t timeout = 10;
    while (rd_fld_r(DDR_UMCTL2, UMCTL2_REGS, SWSTAT, SW_DONE_ACK)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
             my_print(TIMEOUT,6);
             return 0;
        }
        my_wait(100,0xB0);
    }

    timeout = 1000;
    // wait for STAT.operating_mode to become "normal"
    while (rd_fld_r(DDR_UMCTL2, UMCTL2_REGS, STAT, OPERATING_MODE)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
            my_print(TIMEOUT,7);
            return 0;
        }
        my_wait(1000,0xB1);
    }

    //################ DATA training  ###########################
    if (params_PHY_init) {
      if (data_training) {

          wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, RFSHCTL3, DIS_AUTO_REFRESH,     1);
          wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, PWRCTL,   POWERDOWN_EN,         0);

          var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              0  );
          wr_reg           (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,                         var);
          wr_fld_r_r       (      DDR_UMCTL2, UMCTL2_REGS, DFIMISC, DFI_INIT_COMPLETE_EN, 0  );
          wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              1  );

          // wait for SWSTAT.sw_done_ack to become '1'
          uint32_t timeout = 10;
          while (rd_fld_r(DDR_UMCTL2, UMCTL2_REGS, SWSTAT, SW_DONE_ACK)==0 && timeout > 0) {
              timeout -= 1;
              if (timeout == 0) {
                   my_print(TIMEOUT,8);
                   return 0;
              }
              my_wait(100,0xB0);
          }

          if (params_mem_type == DDR4) {
            if (DATA_training() != 0x80006fff) {
                //Failure, write sth to gpr to monitor in simulation
                my_print(ERROR_MSG,0xbad);
                return 0;
            } else {
                //Success, write sth to gpr to monitor in simulation
                my_print(SUCCESS,0xeeee);
            }
          } else if (params_mem_type == DDR3) {
            if (DATA_training() != 0x80002fff) {
                //Failure, write sth to gpr to monitor in simulation
                my_print(ERROR_MSG,0xbad);
                return 0;
            } else {
                //Success, write sth to gpr to monitor in simulation
                my_print(SUCCESS,0xeeee);
            }
          }

          wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, RFSHCTL3, DIS_AUTO_REFRESH,     0);
          wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, PWRCTL,   POWERDOWN_EN,         0);

          var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              0  );
          wr_reg           (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,                         var);
          wr_fld_r_r       (      DDR_UMCTL2, UMCTL2_REGS, DFIMISC, DFI_INIT_COMPLETE_EN, 1  );
          wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              1  );

          // wait for SWSTAT.sw_done_ack to become '1'
          timeout = 10;
          while (rd_fld_r(DDR_UMCTL2, UMCTL2_REGS, SWSTAT, SW_DONE_ACK)==0 && timeout > 0) {
              timeout -= 1;
              if (timeout == 0) {
                   my_print(TIMEOUT,9);
                   return 0;
              }
              my_wait(100,0xB0);
          }
      }
    } else {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, RFSHCTL3, DIS_AUTO_REFRESH,     1);
    }

    // Reenabling uMCTL2 initiated update request after executing DDR initization
    // Reference: DDR4 MultiPHY PUB databook (3.11a) PIR.INIT description (pg no. 114)
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              0  );
    wr_reg           (      DDR_UMCTL2, UMCTL2_REGS, SWCTL,                         var);
    wr_fld_r_r       (      DDR_UMCTL2, UMCTL2_REGS, DFIUPD0, DIS_AUTO_CTRLUPD,     0  );
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, SWCTL,   SW_DONE,              1  );

    // wait for SWSTAT.sw_done_ack to become '1'
    timeout = 10;
    while (rd_fld_r(DDR_UMCTL2, UMCTL2_REGS, SWSTAT, SW_DONE_ACK)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
             my_print(TIMEOUT,10);
             return 0;
        }
        my_wait(100,0xB0);
    }

    // Reenabling PHY update Request after executing DDR initization
    // Reference: DDR4 MultiPHY PUB databook (3.11a) PIR.INIT description (pg no. 114)
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DSGCR, PUREN, 1);


    // Enable AXI port
    wr_fld_r_r ( DDR_UMCTL2, UMCTL2_MP, PCTRL_0, PORT_EN, 1);
    my_wait(1000,0xB2);
    return 1;
  }
}

//################################################################################################
//## PHY_initialization procedure : This can be used for DDR3 and DDR4.
//################################################################################################

inline static uint8_t PHY_initialization(void) {
    uint32_t timeout = 200;

    // # write PHY initialization register for PLL initialization, Delay line calibration, PHY reset and Impedence Calibration
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, PIR, 0x00000073);

    //> Waiting for PHY initialization done."

    config_DRAMinit_and_DATAtraining_reg(); //    ## Configure PUB/PHY register for SDRAM initialization and DATA training

    // #read PHY general status register 0
    while (rd_fld_r(DDR_PHY, DWC_DDRPHY_PUB, PGSR0, IDONE)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
            my_print(TIMEOUT,1);
            return 0;
        }
        my_wait(1000,0xB3);
    }

#if defined(READ_STATUS_REGISTERS)
    (void) rd_reg ( DDR_PHY, DWC_DDRPHY_PUB, ZQ0SR);
    (void) rd_reg ( DDR_PHY, DWC_DDRPHY_PUB, ZQ1SR);
    (void) rd_reg ( DDR_PHY, DWC_DDRPHY_PUB, ZQ2SR);
#endif

    return 1;
}

inline static uint8_t DRAM_initialization_by_pub(void) {
    uint8_t timeout = 200;
    //# write PHY initialization register for SDRAM initialization
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, PIR, 0x00000181);

    // echo "> Waiting for DRAM initialization done by PUB."
    //#read PHY general status register 0
    while (rd_fld_r(DDR_PHY, DWC_DDRPHY_PUB, PGSR0, DIDONE)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
            my_print(TIMEOUT,2);
            return 0;
        }
        my_wait(usec2ns(5),0xB4);
    }
    return 1;
}

inline uint8_t DRAM_initialization_by_memctrl(void) {
    uint32_t timeout = 200;

    //# write PHY initialization register for SDRAM initialization
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, PIR, 0x00040001);

    //echo "> Waiting for DRAM initialization done by Memory Controller."
    //#read PHY general status register 0
    while(rd_fld_r(DDR_PHY, DWC_DDRPHY_PUB, PGSR0, IDONE)==0 && timeout > 0) {
      timeout -= 1;
      if (timeout == 0) {
        my_print(TIMEOUT,3);
      }
      my_wait(usec2ns(5),0xB5);
    }
    return rd_fld_r(DDR_PHY, DWC_DDRPHY_PUB, PGSR0, DIDONE);
}

inline uint32_t DATA_training(void) {
    uint32_t timeout;
    uint32_t var, var2;
    // # Write leveling, DQS gate training, Write_latency adjustment must be executed in
    // # asynchronous read mode. After these training are finished, then static read mode
    // # can be set and rest of the training can be executed with a second PIR register.
    //
    // ##########################################################
    // # Write leveling, DQS gate training, Write_latency adjustment is performed in
    // # asynchronous read mode.
    // # By default asynchronous read mode is set : PGCR3.RDMODE = 2'b00

    // As per PUB databook (page no. 601), it is recommended to seed appropriate group of BDLs with a value of
    // x4 or x8 prior to the execution of the data training

    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR0, 0x08080808);
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR1, 0x08080808);
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR2, 0x080808);
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR0, 0x08080808);
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR1, 0x08080808);
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR2, 0x080808);
    if (params_dq_bits_used == 32 || params_dq_bits_used == 40) {
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR0, 0x08080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR1, 0x08080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR2, 0x080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR0, 0x08080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR1, 0x08080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR2, 0x080808);
    }
    if (params_dq_bits_used == 40) {
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR0, 0x08080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR1, 0x08080808);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR2, 0x080808);
    }


    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PGCR0, PHYFRST, 0  );
    wr_reg           (      DDR_PHY, DWC_DDRPHY_PUB, PGCR0,          var);
    my_wait(20,0xA6);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PGCR0, PHYFRST, 1  );

    // # write PHY initialization register for Write leveling, DQS gate training, Write_latency adjustment.
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, PIR, 0x00000E01);
    // echo "> Waiting for Write leveling, DQS gate training, Write_latency adjustment done."
    // #read PHY general status register 0
    timeout = 2000;
    while(rd_fld_r(DDR_PHY, DWC_DDRPHY_PUB, PGSR0, IDONE)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
            my_print(TIMEOUT,4);
            return 0;
        }
        my_wait(10000,0xB6);
    }

    // ##########################################################
    // # Static read training must be performed in static read mode.
    // # read/write bit Deskew, read/write Eye Centering training, VREF training
    // # can be performed in static read mode or asynchronous read mode.
    //
    // # Set static read mode : PGCR3.RDMODE = 2'b011
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, PGCR3, RDMODE, 1);

    if (params_mem_type == DDR4) {
    // # write PHY initialization register for Static read training, read/write bit Deskew, read/write Eye Centering training and VREF training
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, PIR, 0x0003F001);
    } else if (params_mem_type == DDR3) {
    wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, PIR, 0x0001F001);
    }
    // echo "> Waiting for DATA training done."
    // #read PHY general status register 0
    timeout = 2000;

    while (rd_fld_r(DDR_PHY, DWC_DDRPHY_PUB, PGSR0, IDONE)==0 && timeout > 0) {
        timeout -= 1;
        if (timeout == 0) {
            my_print(TIMEOUT,5);
            return 0;
        }
        my_wait(10000,0xB7);
    }

    var2 = rd_reg ( DDR_PHY, DWC_DDRPHY_PUB, PGSR0);

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PGCR0, PHYFRST, 0  );
    wr_reg           (      DDR_PHY, DWC_DDRPHY_PUB, PGCR0,          var);
    my_wait(20,0xA7);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PGCR0, PHYFRST, 1  );

#if defined(READ_STATUS_REGISTERS)
    // Reading DQS gating training status for each data lane
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0RSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1RSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2RSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3RSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4RSR0            );

    // Reading read leveling training status for each data lane
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0RSR1            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1RSR1            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2RSR1            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3RSR1            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4RSR1            );

    // Reading write leveling Adjument training status (Warning) for each data lane
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0RSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1RSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2RSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3RSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4RSR2            );

    // Reading write leveling Adjument training status (Error) for each data lane
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0RSR3            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1RSR3            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2RSR3            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3RSR3            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4RSR3            );

    // Reading write leveling training status (Error) for each data lane
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0GSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1GSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2GSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3GSR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4GSR0            );

    // Reading warning and error status flags for each of the eye training algorithms
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0GSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1GSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2GSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3GSR2            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4GSR2            );

    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, RANKIDR, RANKRID, 0);

    // Reading various timing settings for each byte lane
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0GTR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1GTR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2GTR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3GTR0            );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4GTR0            );

    // Reading the status of Write Levelling Delay (WLD)
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR0        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR0        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR0        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR0        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR0        );

    // Reading the status of Write Data Delay (WDQD)
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR1        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR1        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR1        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR1        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR1        );

    // Reading the status of DQS Gating Delay (DQSGD)
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR2        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR2        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR2        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR2        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR2        );

    // Reading the status of Read DQS Delay (RDQSD)
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR3        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR3        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR3        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR3        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR3        );

    // Reading the status of Read DQSN Delay (RDQSND)
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR4        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR4        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR4        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR4        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR4        );

    // Reading the status of DQS Gate Status Delay (DQSGSD)
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR5        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR5        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR5        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR5        );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR5        );

    // Reading the status of DX0 bit delay line in the write data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR0         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR1         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR2         );

    // Reading the status of DX1 bit delay line in the write data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR0         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR1         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR2         );

    // Reading the status of DX2 bit delay line in the write data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR0         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR1         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR2         );

    // Reading the status of DX3 bit delay line in the write data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR0         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR1         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR2         );

    // Reading the status of DX4 bit delay line in the write data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR0         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR1         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR2         );

    // Reading the status of DX0 bit delay line in the read data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR3         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX0BDLR4         );

    // Reading the status of DX1 bit delay line in the read data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR3         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX1BDLR4         );

    // Reading the status of DX2 bit delay line in the read data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR3         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX2BDLR4         );

    // Reading the status of DX3 bit delay line in the read data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR3         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX3BDLR4         );

    // Reading the status of DX4 bit delay line in the read data path
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR3         );
    (void) rd_reg    (      DDR_PHY, DWC_DDRPHY_PUB, DX4BDLR4         );
#endif

    return var2;
}

inline static void config_PHY_initialization_reg(void)
{
  uint32_t var;

  wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, PGCR1, IODDRM, 0x01);
  wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, PGCR2, TREFPRD, ROUND_VAL(params_tRASc_max - 400));

  var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PTR0, TPLLGS, params_tpllgs);
  wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PTR0, TPLLPD, params_tpllpd );

  var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PTR1, TPLLLOCK, params_tplllock);
  wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PTR1, TPLLRST,  params_tpllrst );

  //## FIX ME : FIXED PGWAIT = 7 for ctl_clk > 467 MHz
  if ((params_tCK_min * 2) <= 2000) {
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, ZQCR, PGWAIT, 7);
  } else {
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, ZQCR, PGWAIT, 6);
  }

  wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, ZQ0PR, ZQ0PR_ZQDIV, params_zqdiv);
  wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, ZQ1PR, ZQ1PR_ZQDIV, params_zqdiv);
  wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, ZQ2PR, ZQ2PR_ZQDIV, params_zqdiv);

  if (params_asym_drv_pd && params_asym_drv_pu) {
    /* Set up asymmetric drive (DDR4) */
    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, ZQ0PR, ZQ0PR_ZPROG_ASYM_DRV_PU, params_asym_drv_pu);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, ZQ0PR, ZQ0PR_ZPROG_ASYM_DRV_PD, params_asym_drv_pd);

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, ZQ1PR, ZQ1PR_ZPROG_ASYM_DRV_PU, params_asym_drv_pu);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, ZQ1PR, ZQ1PR_ZPROG_ASYM_DRV_PD, params_asym_drv_pd);

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, ZQ2PR, ZQ2PR_ZPROG_ASYM_DRV_PU, params_asym_drv_pu);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, ZQ2PR, ZQ2PR_ZPROG_ASYM_DRV_PD, params_asym_drv_pd);

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, ZQCR,  PU_ODT_ONLY,      1);
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, ZQCR,  DIS_NON_LIN_COMP, 0);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, ZQCR,  ASYM_DRV_EN,      1);
  }
}

inline static void config_DRAMinit_and_DATAtraining_reg (void)
{
    // set DDRMD [expr {$mem_type == "DDR4"} ? 0x4 : 0x3];         # for DDR4 = 0x4 and DDR3 = 0x3
    // /## DRAM Configuration register
    uint32_t var;
    if (params_mem_type == DDR4) {
      wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DCR, DDRMD, 0x4);
    } else if (params_mem_type == DDR3) {
      wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DCR, DDRMD, 0x3);
    }

    // 2T mode
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DCR, DDR2T, params_2T_mode);

    if(params_active_ranks > 1) {
        wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, SCHCR1, ALLRANK, 1);
    }

    // ## MODE register
    if (params_mem_type == DDR4) {
      if(params_phy_dbi_en==1) {
          var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PGCR3, PGCR3_RDBI, params_read_dbi_en );
          wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PGCR3, PGCR3_WDBI, params_write_dbi_en);
      }

      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR0_DDR4, params_reg_ddrc_mr  );
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR1_DDR4, params_reg_ddrc_emr );
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR2_DDR4, params_reg_ddrc_emr2);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR3_DDR4, params_reg_ddrc_emr3);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR4_DDR4, params_reg_ddrc_mr4 );
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR5_DDR4, params_reg_ddrc_mr5 );
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR6_DDR4, params_reg_ddrc_mr6 );
    } else if (params_mem_type == DDR3) {
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR0, params_reg_ddrc_mr  );
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR1, params_reg_ddrc_emr );
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR2, params_reg_ddrc_emr2);
      wr_reg ( DDR_PHY, DWC_DDRPHY_PUB, MR3, params_reg_ddrc_emr3);
    }


    // ## DRAM timing parameter register
    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DTPR0, TRTP, params_tRTPc    );
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR0, TRP,  params_tRPc     );
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR0, TRAS, params_tRASc_min);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR0, TRRD, params_tRRDc    );

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DTPR1, TMRD,   params_tMRDc  );
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR1, TMOD,   params_tMOD   );
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR1, TFAW,   params_tFAWc  );
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR1, TWLMRD, params_tWLMRDc);


    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DTPR2, TXS,  params_tXS_tRFCc);
    if (params_mem_type == DDR4) {
      wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR2, TCKE, params_tCKEc    );
    } else if (params_mem_type == DDR3) {
      wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR2, TCKE, params_tCKEc + 1);
    }

    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DTPR3, TDLLK, params_tDLLKc);

    if (params_mem_type == DDR4) {
      var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DTPR4, TXP,  params_tXPc );
    } else if (params_mem_type == DDR3) {
      var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DTPR4, TXP,  params_tXPDLLc );
    }
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR4, TRFC, params_tRFCc);

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DTPR5, TWTR, params_tWTRc);
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR5, TRCD, params_tRCDc);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTPR5, TRC,  params_tRCc );

    // ## PHY timing register
    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PTR3, TDINIT0, params_tdinit0  );
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PTR3, TDINIT1, params_tXS_tRFCc);

    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, PTR4, TDINIT2, params_tdinit2 );
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, PTR4, TDINIT3, params_tZQinitc);


    // ## DATX8 command configuration register
    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DXCCR, DQSRES,  0x4);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DXCCR, DQSNRES, 0xC);

    // ## DDR system general configuration register
    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, DSGCR, CUAEN,   0x1);
    // Disabling PHY initiated update request during DDR initialization
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DSGCR, PUREN,   0x0);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DSGCR, SDRMODE, 0x0);

    var = wr_fld_r_s (       DDR_PHY, DWC_DDRPHY_PUB, DTCR0, DTRPTN, 15);
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTCR0, DTMPR,   1);
    if(params_read_dbi_en == 1) {
        var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, DTCR0, DTRDBITR, 0x3);
    }
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, DTCR0, RFSHDT,  2);

    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DTCR1, RANKEN, params_active_ranks);

    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, PGCR7, WRPSTEX, 0x1);

    // # Disable un-used byte lanes by writing DXnGCR0[0] = 1'b0 (DXEN).
    if (params_dq_bits_used == 32) {
      wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX4GCR0, DX4GCR0_DXEN, 0);
    } else if (params_dq_bits_used == 16) {
      wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX2GCR0, DX2GCR0_DXEN, 0);
      wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX3GCR0, DX3GCR0_DXEN, 0);
      wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX4GCR0, DX4GCR0_DXEN, 0);
    }

    //# To capture valid read data for rank0
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, RANKIDR, RANKWID, 0);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX0GTR0, DX0GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX1GTR0, DX1GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX2GTR0, DX2GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX3GTR0, DX3GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX4GTR0, DX4GTR0_DGSL, 0x2);

    //# To capture valid read data for rank1
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, RANKIDR, RANKWID, 1);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX0GTR0, DX0GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX1GTR0, DX1GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX2GTR0, DX2GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX3GTR0, DX3GTR0_DGSL, 0x2);
    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, DX4GTR0, DX4GTR0_DGSL, 0x2);

    // ## VREF IO control register
    var = wr_fld_r_s (      DDR_PHY, DWC_DDRPHY_PUB, IOVCR0, ACVREFIEN, 1);
    var = wr_fld_s_s ( var, DDR_PHY, DWC_DDRPHY_PUB, IOVCR0, ACVREFSEN, 1);
    wr_fld_s_r       ( var, DDR_PHY, DWC_DDRPHY_PUB, IOVCR0, ACVREFPEN, 0);

    wr_fld_r_r ( DDR_PHY, DWC_DDRPHY_PUB, IOVCR1, ZQVREFPEN, 1);
}

inline static void config_ddr34_memory_controller_reg(void)
{
    uint32_t bank_offset, row_offset;
    // Read the master register
    uint32_t var = rd_reg(DDR_UMCTL2, UMCTL2_REGS, MSTR);

    if (params_mem_type == DDR4) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, DDR3,          0                   );
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, DDR4,          1                   );
    } else {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, DDR3,          1                   );
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, DDR4,          0                   );
    }
    // 2T mode
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, EN_2T_TIMING_MODE, params_2T_mode  );
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, ACTIVE_RANKS,  params_active_ranks );

    if (params_dq_bits_used == 16) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, DATA_BUS_WIDTH,  1);
    }

    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, MSTR, DEVICE_CONFIG, params_device_config);

    //For optimum utilization of SDRAM, Burst length expansion mode is enabled in case of Half bus width mode and UMCTL2_PARTIAL_WR = 1,
    // as per recommendation given in the uMCTL2 data book v2.70a (pg. no. 122).
    if (params_dq_bits_used == 16 && params_mem_type == DDR4) {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_MP, PCCFG, BL_EXP_MODE, 1);
    }

    // ###### DDR3/4 INIT register ########################
    var = wr_fld_r_s   (      DDR_UMCTL2, UMCTL2_REGS, INIT0, PRE_CKE_X1024,  params_pre_cke_x1024 );
    if (init_by_pub) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, INIT0, SKIP_DRAM_INIT, 0x1                  );
    }
    wr_fld_s_r         ( var, DDR_UMCTL2, UMCTL2_REGS, INIT0, POST_CKE_X1024, params_post_cke_x1024);

    wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT1, DRAM_RSTN_X1024, params_dram_rstn_x1024);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, INIT3, MR,  params_reg_ddrc_mr );
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, INIT3, EMR, params_reg_ddrc_emr);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, INIT4, EMR3, params_reg_ddrc_emr3);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, INIT4, EMR2, params_reg_ddrc_emr2);

    // Updated value of ZQINIT field from 0x11 to 0x1 as Veloce DDR4 SM doesn't support ZQCL command
    if (_DDR_EMU) {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT5, DEV_ZQINIT_X32, 0x1                );
    } else {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT5, DEV_ZQINIT_X32, (CEIL_VAL((params_tZQinitc / 2.0) / 32) + 1));
    }

    if (params_mem_type == DDR4) {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT6, MR5, params_reg_ddrc_mr5);

      // Updated MR6 value from 0xC99 to 0xC00 as Veloce DDR4 SM doesn't support VrefDQ training
      if (_DDR_EMU) {
        wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT7, MR6, 0xC00              );
      } else {
        wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT7, MR6, params_reg_ddrc_mr6);
      }

      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, INIT6, MR4, params_reg_ddrc_mr4);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DBICTL, DM_EN,     params_dm_en    );
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DBICTL, WR_DBI_EN, params_wr_dbi_en);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DBICTL, RD_DBI_EN, params_rd_dbi_en);

      if (params_phy_dbi_en == 1) {
          wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, DFIMISC, PHY_DBI_MODE, params_phy_dbi_en);
      }
    }

    if (params_mem_type == DDR4) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ODTCFG, WR_ODT_HOLD,  5 + params_WR_PREAMBLE);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ODTCFG, WR_ODT_DELAY, params_tCAL           );
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ODTCFG, RD_ODT_HOLD,  5 + params_RD_PREAMBLE);
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ODTCFG, RD_ODT_DELAY, params_CLc - params_CWLc - params_RD_PREAMBLE + params_WR_PREAMBLE + params_tCAL);
    } else if (params_mem_type == DDR3) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ODTCFG, WR_ODT_HOLD,  6);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ODTCFG, WR_ODT_DELAY, 0);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ODTCFG, RD_ODT_HOLD,  6);
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ODTCFG, RD_ODT_DELAY, params_CLc - params_CWLc);
    }


//  ###### DDR3/4 DRAM Timing register ########################
    uint32_t val_rd2wr, val_wr2rd, val_tCCD, val_tRRD, wr2pre;

    if (params_mem_type == DDR4) {
      val_rd2wr = params_RL + FLOOR_VAL(params_BL / 2.0) + 1 + params_WR_PREAMBLE - params_WL;
      if (params_write_crc == 1 && params_dm_en == 1) {
          val_wr2rd = params_CWLc + params_tPLc + FLOOR_VAL(params_BL / 2.0) + params_tWTRc_L_CRC_DM + params_write_preamble;
      } else {
          val_wr2rd = params_CWLc + params_tPLc + FLOOR_VAL(params_BL / 2.0) + params_tWTRc + params_write_preamble;
      }

      val_tCCD  = CEIL_VAL(params_tCCDc_L / 2.0);
      val_tRRD  = CEIL_VAL(params_tRRDc_L / 2.0);
    } else if (params_mem_type == DDR3) {
      val_rd2wr = params_RL + FLOOR_VAL(params_BL / 2.0) + 2 - params_WL;
      val_wr2rd = params_CWLc + FLOOR_VAL(params_BL / 2.0) + params_tWTRc;
#if defined(params_tCCDc)
      val_tCCD  = CEIL_VAL(params_tCCDc / 2.0);
#endif
      val_tRRD  = CEIL_VAL(params_tRRDc / 2.0);
    }

    if (params_mem_type == DDR4) {
      if (params_write_preamble == 1) {
          wr2pre = FLOOR_VAL((params_WL + FLOOR_VAL(params_BL / 2.0) + params_tWRc + 2) / 2.0);
      } else {
          if (params_write_crc == 1 && params_dm_en == 1) {
              wr2pre = FLOOR_VAL((params_WL + FLOOR_VAL(params_BL / 2.0) + params_tWRc_CRC_DM) / 2.0);
          } else {
              wr2pre = FLOOR_VAL((params_WL + FLOOR_VAL(params_BL / 2.0) + params_tWRc) / 2.0);
          }
      }
    } else if (params_mem_type == DDR3) {
      wr2pre = FLOOR_VAL((params_WL + FLOOR_VAL(params_BL / 2.0) + params_tWRc) / 2.0);
    }
    // 2T mode
    wr2pre = wr2pre + params_2T_mode;
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG0, WR2PRE,    wr2pre              );


    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG0, T_FAW,     CEIL_VAL(params_tFAWc / 2.0));
    // 2T mode
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG0, T_RAS_MIN, (FLOOR_VAL(params_tRASc_min / 2.0) + params_2T_mode));
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG0, T_RAS_MAX, FLOOR_VAL((params_tRASc_max -1) / (2.0*1024)));

    uint32_t val_txp;
    if (params_mem_type == DDR4) {
      if (params_ca_parity_en == 0) {
         val_txp  = CEIL_VAL(params_tXPc / 2.0);
      } else {
         val_txp  = CEIL_VAL((params_tXPc+params_tPLc) / 2.0);
      }
    } else if (params_mem_type == DDR3) {
      val_txp  = CEIL_VAL(params_tXPc / 2.0);
    }
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG1, T_RC,   CEIL_VAL(params_tRCc / 2.0) );
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG1, T_XP,   val_txp                     );
    // 2T mode
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG1, RD2PRE, (FLOOR_VAL((params_AL + params_tRTPc) / 2.0) + params_2T_mode));

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG2, WR2RD,         CEIL_VAL(val_wr2rd / 2.0));
    if (params_mem_type == DDR4) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG2, WRITE_LATENCY, CEIL_VAL(params_WL / 2.0));
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG2, READ_LATENCY,  CEIL_VAL(params_RL / 2.0));
    }
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG2, RD2WR,         CEIL_VAL(val_rd2wr / 2.0));

    if (params_mem_type == DDR4) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG3, T_MRD, CEIL_VAL((params_tMRDc + params_tCAL) / 2.0));
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG3, T_MOD, CEIL_VAL((params_tWR_MPRc + params_tCAL) / 2.0));
    } else if (params_mem_type == DDR3) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG3, T_MRD, CEIL_VAL((params_tMRDc) / 2.0));
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG3, T_MOD, CEIL_VAL((params_tWR_MPRc) / 2.0));
    }
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG4, T_RCD, CEIL_VAL((params_tRCDc - params_AL) / 2.0));
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG4, T_RP,  FLOOR_VAL((FLOOR_VAL(params_tRPc / 2.0)) + 1));
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG4, T_CCD, val_tCCD                          );
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG4, T_RRD, val_tRRD                          );

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG5, T_CKSRX, CEIL_VAL(params_tCKSRXc / 2.0));
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG5, T_CKSRE, CEIL_VAL(params_tCKSREc / 2.0));
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG5, T_CKESR, CEIL_VAL((params_tCKEc + 1) / 2.0));
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG5, T_CKE,   CEIL_VAL(params_tCKEc / 2.0));

    if (params_mem_type == DDR4) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG8, T_XS_FAST_X32,  CEIL_VAL(params_tXS_tRFC4c / (2.0 * 32)) + 1);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG8, T_XS_ABORT_X32, CEIL_VAL(params_tXS_tRFC4c / (2.0 * 32)));
    }
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG8, T_XS_DLL_X32,   CEIL_VAL(params_tDLLKc / (2.0 * 32))    );
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG8, T_XS_X32,       CEIL_VAL(params_tXS_tRFCc / (2.0 * 32)) );

    if (params_mem_type == DDR4) {
      uint32_t wr2rd_s;
      if (params_write_crc == 1 && params_dm_en == 1) {
          wr2rd_s  = CEIL_VAL((params_CWLc + params_tPLc + FLOOR_VAL(params_BL / 2.0) + params_tWTRc_S_CRC_DM + params_write_preamble) / 2.0);
      } else {
          wr2rd_s  = CEIL_VAL((params_CWLc + params_tPLc + FLOOR_VAL(params_BL / 2.0) + params_tWTRc_S + params_write_preamble) / 2.0);
      }
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DRAMTMG9, DDR4_WR_PREAMBLE, params_write_preamble );
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG9, T_CCD_S,          CEIL_VAL((params_tCCDc_S + 1) / 2.0));
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG9, T_RRD_S,          CEIL_VAL(params_tRRDc_S / 2.0));
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DRAMTMG9, WR2RD_S,          wr2rd_s               );


      if (params_pda_en) {
          wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, DRAMTMG12, T_MRD_PDA, CEIL_VAL(params_tMRD_PDAc / 2.0));
      }
    }

    // ## Set DFI Timings register for AXI write/read operation
    // var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_TPHY_WRLAT,  FLOOR_VAL((params_WL + params_tCAL - 2) / 2.0));
    // var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_T_RDDATA_EN, FLOOR_VAL((params_RL + params_tCAL - 4) / 2.0));
    // var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_TPHY_WRDATA, 0x1                            );
    // wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_T_CTRL_DELAY, 0x2                           );

    // var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_DRAM_CLK_ENABLE,  0x1        );
    // var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_DRAM_CLK_DISABLE, 0x2        );
    // var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_CMD_LAT,          params_tCAL);
    // wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_WRDATA_DELAY,     0x3        );

    // 2T mode : changes to DFITMG0 and DFITMG1 registers.
    // Sailesh : New settings to specify applicable DFI timing params in terms of DFI PHY clocks (SDR) instead of DFI clocks (HDR)
    // This should work with both 1T and 2T mode
    // ## Set DFI Timings register for AXI write/read operation
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_WRDATA_USE_DFI_PHY_CLK,  1);
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_RDDATA_USE_DFI_PHY_CLK,  1);
    if (params_mem_type == DDR4) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_TPHY_WRLAT,  (params_WL + params_tCAL - 2));
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_T_RDDATA_EN, (params_RL + params_tCAL - 4));
    } else if (params_mem_type == DDR3) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_TPHY_WRLAT,  (params_WL - 2));
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_T_RDDATA_EN, (params_RL - 4));
    }

    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_TPHY_WRDATA, 0x2                            );
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG0, DFI_T_CTRL_DELAY, 0x3                           );

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_DRAM_CLK_ENABLE,  0x1        );
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_DRAM_CLK_DISABLE, 0x2        );
    if (params_mem_type == DDR4) {
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_CMD_LAT,          params_tCAL);
    }
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DFITMG1, DFI_T_WRDATA_DELAY,     0x4        );

    // Ignoring assertion of dfi_init_complete signal until completion of SDRAM initialization
    // and it also resolves the issue with init_by_pub = 0
    wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, DFIMISC, DFI_INIT_COMPLETE_EN, 0);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DFIUPD0, DIS_AUTO_CTRLUPD_SRX, 1);
    // Disabling update request initiated by DDR controller during DDR initialization
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DFIUPD0, DIS_AUTO_CTRLUPD,     1);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, DFIUPD1, DFI_T_CTRLUPD_INTERVAL_MIN_X1024, 0x40);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, DFIUPD1, DFI_T_CTRLUPD_INTERVAL_MAX_X1024, 0xFF);

    wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, RFSHCTL0, REFRESH_BURST, 1);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, RFSHTMG, T_RFC_NOM_X32, FLOOR_VAL(params_tREFIc / (2.0 * 32)));
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, RFSHTMG, T_RFC_MIN,     CEIL_VAL(params_tRFCc / 2.0));


    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, RFSHCTL1, REFRESH_TIMER0_START_VALUE_X32, 0x20);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, RFSHCTL1, REFRESH_TIMER1_START_VALUE_X32, 0x40);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, RANKCTL, DIFF_RANK_RD_GAP, 2);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, RANKCTL, DIFF_RANK_WR_GAP, 2);

    if (params_mem_type == DDR4) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, CRCPARCTL1, CRC_INC_DM,    params_write_crc   );
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, CRCPARCTL1, CRC_ENABLE,    params_write_crc   );
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, CRCPARCTL1, PARITY_ENABLE, params_ca_parity_en);
    }

//    ## Address mapping
// columns
    if (params_dq_bits_used == 16) {
      // For optimum utilization of SDRAM, mapping HIF[9] to col_addr[3] in case of Half bus width mode and UMCTL2_PARTIAL_WR = 1,
      // as per recommendation given in the uMCTL2 data book v2.70a (pg. no. 122).
      if (params_mem_type == DDR4) {
        var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B2, 7);
      } else {
        var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B2, 0);
      }
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B3, 0);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B4, 0);
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B5, 0);

      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B6, 0);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B7, 0);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B8, 0);
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B9, 31);
    } else {
      const int column_offset = 0;
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B2, 2<params_addrmap_column_bits?column_offset:31);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B3, 3<params_addrmap_column_bits?column_offset:31);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B4, 4<params_addrmap_column_bits?column_offset:31);
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP2, ADDRMAP_COL_B5, 5<params_addrmap_column_bits?column_offset:31);

      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B6, 6<params_addrmap_column_bits?0:31);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B7, 7<params_addrmap_column_bits?0:31);
      var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B8, 8<params_addrmap_column_bits?0:31);
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP3, ADDRMAP_COL_B9, 9<params_addrmap_column_bits?0:31);
    }

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP4, ADDRMAP_COL_B10, 10<params_addrmap_column_bits?0:31);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP4, ADDRMAP_COL_B11, 11<params_addrmap_column_bits?0:31);


    // rows
    if (params_dq_bits_used == 16 && params_mem_type == DDR3) {
      row_offset = params_addrmap_column_bits-7;
    } else {
      row_offset = params_addrmap_column_bits-6;
    }
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP5, ADDRMAP_ROW_B0,    row_offset);
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP5, ADDRMAP_ROW_B1,    row_offset);
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP5, ADDRMAP_ROW_B2_10, row_offset);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP5, ADDRMAP_ROW_B11,   row_offset);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP6, ADDRMAP_ROW_B12, 12<params_addrmap_row_bits?row_offset:15);
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP6, ADDRMAP_ROW_B13, 13<params_addrmap_row_bits?row_offset:15);
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP6, ADDRMAP_ROW_B14, 14<params_addrmap_row_bits?row_offset:15);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP6, ADDRMAP_ROW_B15, 15<params_addrmap_row_bits?row_offset:15);

    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP7, ADDRMAP_ROW_B16, 16<params_addrmap_row_bits?row_offset:15);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP7, ADDRMAP_ROW_B17, 17<params_addrmap_row_bits?row_offset:15);

    // Banks
    if (params_dq_bits_used == 16 && params_mem_type == DDR3) {
      bank_offset = params_addrmap_column_bits+params_addrmap_row_bits-3;
    } else {
      bank_offset = params_addrmap_column_bits+params_addrmap_row_bits-2;
    }
    var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP1, ADDRMAP_BANK_B0, 0<params_addrmap_bank_bits?bank_offset:63);
    var = wr_fld_s_s ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP1, ADDRMAP_BANK_B1, 1<params_addrmap_bank_bits?bank_offset:63);
    wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP1, ADDRMAP_BANK_B2, 2<params_addrmap_bank_bits?bank_offset:63);

// Bank groups
#define bank_grp_offset params_addrmap_column_bits+params_addrmap_row_bits+params_addrmap_bank_bits-2
    if (params_dq_bits_used == 16 && params_mem_type == DDR4) {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP8, ADDRMAP_BG_B0, 0);
    } else {
      var = wr_fld_r_s (      DDR_UMCTL2, UMCTL2_REGS, ADDRMAP8, ADDRMAP_BG_B0, 0<params_addrmap_bank_group_bits?bank_grp_offset:63);
    }

    if (params_dq_bits_used == 16 && params_mem_type == DDR4 && params_DQ_BITS == 8) {
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP8, ADDRMAP_BG_B1, 1<params_addrmap_bank_group_bits?(bank_grp_offset-1):63);
    } else {
      wr_fld_s_r       ( var, DDR_UMCTL2, UMCTL2_REGS, ADDRMAP8, ADDRMAP_BG_B1, 1<params_addrmap_bank_group_bits?bank_grp_offset:63);
    }

// CS
#define cs_offset params_addrmap_column_bits+params_addrmap_row_bits+params_addrmap_bank_bits+params_addrmap_bank_group_bits-6
    if (params_active_ranks == 1) {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, ADDRMAP0, ADDRMAP_CS_BIT0, 31);
    } else if (params_dq_bits_used == 16 && params_mem_type == DDR4) {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, ADDRMAP0, ADDRMAP_CS_BIT0, cs_offset-1);
    } else {
      wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, ADDRMAP0, ADDRMAP_CS_BIT0, cs_offset);
    }

    // ECC
    wr_fld_r_r ( DDR_UMCTL2, UMCTL2_REGS, ECCCFG0, ECC_MODE, params_ecc_mode);
}

static void ecc_enable_scrubbing(void)
{
	printch('<');
	/* 1.  Disable AXI port. port_en = 0 */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, PCTRL_0, PORT_EN, 0);
	/* 2. scrub_mode = 1 */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_MODE, 1);
	/* 3. scrub_interval = 0 */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_INTERVAL, 0);
	/* 4. Data pattern = 0 */
	wr_reg     (DDR_UMCTL2, UMCTL2_MP, SBRWDATA0, 0);
	/* 5. (skip) */
	/* 6. Enable SBR programming */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_EN, 1);
	/* 7. Poll SBRSTAT.scrub_done */
	while (rd_fld_r(DDR_UMCTL2, UMCTL2_MP, SBRSTAT, SCRUB_DONE) == 0)
		;
	/* 8. Poll SBRSTAT.scrub_busy */
	while (rd_fld_r(DDR_UMCTL2, UMCTL2_MP, SBRSTAT, SCRUB_BUSY) == 1)
		;
	/* 9. Disable SBR programming */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_EN, 0);
#if 0
	/* 10. Normal scrub operation, mode = 0, interval = 100 */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_MODE, 0);
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_INTERVAL, 100);
	/* 11. Enable SBR progeramming again  */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, SBRCTL, SCRUB_EN, 1);
#endif
	/* 12. Enable AXI port */
	wr_fld_r_r (DDR_UMCTL2, UMCTL2_MP, PCTRL_0, PORT_EN, 1);
	printch('>');
}

static void simple_mem_test(u32 *start, u32 count)
{
	u32 i, val;
	volatile u32 *ptr;

	for (i = 0, ptr = (void*) start; i < count; i++, ptr++) {
		//printch(':');
		*ptr = ~i;
	}
	for (i = 0, ptr = (void*) start; i < count; i++, ptr++) {
		//printch('<');
		val = *ptr;
		if (val != ~i) {
			printascii("RDERR:");
			printhex8(((u64)ptr) >> 32);
			printhex8((u64)ptr);
			printascii(",");
			printhex8(val);
			printascii(",");
			printhex8(~i);
			printch('\n');
		}
	}
	for (i = 0, ptr = (void*) start; i < count; i++, ptr++) {
		//printch(';');
		*ptr = 0xBED0CAFE;
	}
}

#define SIMPLE_MEMTEST_COUNT 1024
void ddr_setup(void)
{
	int res;
	if (params_ecc_mode == 0) {
		printascii(DDR_TYPE " initializing, ECC off");
	} else {
		printascii(DDR_TYPE " initializing, ECC mode=");
		printch('0' + params_ecc_mode);
	}
	printascii(", clk_div=");
	printhex2(params_clk_div);
	printascii(", dq_bits=");
	printhex2(params_dq_bits_used);
	printascii(params_2T_mode ? ", 2T=on" : ", 2T=off");
	printascii(" init_by_pub=" mkstr(init_by_pub));
	printch('\n');
	// Set DDR clock frequency
	wr_fld_r_r (CLKGEN, LCPLL1, LCPLL1_DDR_CLK_CFG, DDR_CLK_DIV, params_clk_div);
	my_wait(usec2ns(10),0xFF);
	res = DDR_initialization();
	if (res != 0) {
		if (params_ecc_mode != 0) {
			ecc_enable_scrubbing();
		}
		simple_mem_test((void*)PHYS_DDR, SIMPLE_MEMTEST_COUNT);
		simple_mem_test((void*)(PHYS_DDR + PHYS_SDRAM_1_SIZE - SZ_1M), SIMPLE_MEMTEST_COUNT);
		printascii(DDR_TYPE " up\n");
	} else {
		printascii(DDR_TYPE " failure.\n");
		while(1)
			;
	}
}

static int print_ddr_stat(cmd_tbl_t *cmdtp, int flag, int argc,
			  char *const argv[])
{
	printf(DDR_TYPE " status:\n");
	wr_reg(DDR_PHY, DWC_DDRPHY_PUB, RANKIDR, 0);
	/* DX0LCDLR0 */
	printf("%s: 0x%08x\n", "DX0LCDLR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR0));
	printf("%s: 0x%08x\n", "DX0LCDLR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR1));
	printf("%s: 0x%08x\n", "DX0LCDLR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR2));
	printf("%s: 0x%08x\n", "DX0LCDLR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR3));
	printf("%s: 0x%08x\n", "DX0LCDLR4", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0LCDLR4));
	/* DX1LCDLR0 */
	printf("%s: 0x%08x\n", "DX1LCDLR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR0));
	printf("%s: 0x%08x\n", "DX1LCDLR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR1));
	printf("%s: 0x%08x\n", "DX1LCDLR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR2));
	printf("%s: 0x%08x\n", "DX1LCDLR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR3));
	printf("%s: 0x%08x\n", "DX1LCDLR4", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1LCDLR4));
	/* DX2LCDLR0 */
	printf("%s: 0x%08x\n", "DX2LCDLR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR0));
	printf("%s: 0x%08x\n", "DX2LCDLR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR1));
	printf("%s: 0x%08x\n", "DX2LCDLR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR2));
	printf("%s: 0x%08x\n", "DX2LCDLR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR3));
	printf("%s: 0x%08x\n", "DX2LCDLR4", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2LCDLR4));
	/* DX3LCDLR0 */
	printf("%s: 0x%08x\n", "DX3LCDLR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR0));
	printf("%s: 0x%08x\n", "DX3LCDLR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR1));
	printf("%s: 0x%08x\n", "DX3LCDLR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR2));
	printf("%s: 0x%08x\n", "DX3LCDLR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR3));
	printf("%s: 0x%08x\n", "DX3LCDLR4", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3LCDLR4));
	if (params_ecc_mode != 0) {
		/* DX4LCDLR0 */
		printf("%s: 0x%08x\n", "DX4LCDLR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR0));
		printf("%s: 0x%08x\n", "DX4LCDLR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR1));
		printf("%s: 0x%08x\n", "DX4LCDLR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR2));
		printf("%s: 0x%08x\n", "DX4LCDLR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR3));
		printf("%s: 0x%08x\n", "DX4LCDLR4", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4LCDLR4));
	}
	/* DXnGTR0 */
	printf("%s: 0x%08x\n", "DX0GTR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0GTR0));
	printf("%s: 0x%08x\n", "DX1GTR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1GTR0));
	printf("%s: 0x%08x\n", "DX2GTR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2GTR0));
	printf("%s: 0x%08x\n", "DX3GTR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3GTR0));
	printf("%s: 0x%08x\n", "DX4GTR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4GTR0));
	/* DX0GSR0-3 */
	printf("%s: 0x%08x\n", "DX0GSR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0GSR0));
	printf("%s: 0x%08x\n", "DX0GSR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0GSR1));
	printf("%s: 0x%08x\n", "DX0GSR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0GSR2));
	printf("%s: 0x%08x\n", "DX0GSR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX0GSR3));
	/* DX1GSR0-3 */
	printf("%s: 0x%08x\n", "DX1GSR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1GSR0));
	printf("%s: 0x%08x\n", "DX1GSR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1GSR1));
	printf("%s: 0x%08x\n", "DX1GSR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1GSR2));
	printf("%s: 0x%08x\n", "DX1GSR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX1GSR3));
	/* DX2GSR0-3 */
	printf("%s: 0x%08x\n", "DX2GSR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2GSR0));
	printf("%s: 0x%08x\n", "DX2GSR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2GSR1));
	printf("%s: 0x%08x\n", "DX2GSR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2GSR2));
	printf("%s: 0x%08x\n", "DX2GSR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX2GSR3));
	/* DX3GSR0-3 */
	printf("%s: 0x%08x\n", "DX3GSR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3GSR0));
	printf("%s: 0x%08x\n", "DX3GSR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3GSR1));
	printf("%s: 0x%08x\n", "DX3GSR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3GSR2));
	printf("%s: 0x%08x\n", "DX3GSR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX3GSR3));
	if (params_ecc_mode != 0) {
		/* DX4GSR0-3 */
		printf("%s: 0x%08x\n", "DX4GSR0", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4GSR0));
		printf("%s: 0x%08x\n", "DX4GSR1", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4GSR1));
		printf("%s: 0x%08x\n", "DX4GSR2", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4GSR2));
		printf("%s: 0x%08x\n", "DX4GSR3", rd_reg(DDR_PHY, DWC_DDRPHY_PUB, DX4GSR3));
	}
	return CMD_RET_SUCCESS;
}

static int print_ddr_ecc(cmd_tbl_t *cmdtp, int flag, int argc,
			  char *const argv[])
{
	printf(DDR_TYPE " ECC status:\n");
	printf("%s: 0x%08x\n", "ECCSTAT",   rd_reg(DDR_UMCTL2, UMCTL2_REGS, ECCSTAT));
	printf("%s: 0x%08x\n", "ECCERRCNT", rd_reg(DDR_UMCTL2, UMCTL2_REGS, ECCERRCNT));
	return CMD_RET_SUCCESS;
}

static char ddr_help_text[] =
	"stats - List DDR stats\n"
	"ddr ecc - List DDR ECC status\n";

U_BOOT_CMD_WITH_SUBCMDS(ddr, "DDR status", ddr_help_text,
	U_BOOT_SUBCMD_MKENT(stats, 1, 1, print_ddr_stat),
	U_BOOT_SUBCMD_MKENT(ecc,   1, 1, print_ddr_ecc));
