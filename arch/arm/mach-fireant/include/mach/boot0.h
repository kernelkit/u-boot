/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Special initialization for FireAnt SoC
 * - Does DDR init
 */

.extern boot0

#ifdef CONFIG_ARMV8_MULTIENTRY
	branch_if_master x0, x1, 2f
	/* Secondary: Already in RAM, relocated. Just goto reset. */
	b	reset
2:
#endif

	/* Establish stack to be able to call "C" */
	ldr	x0, =(BOOT0_SP_ADDR)
	bic	sp, x0, #0xf	/* 16-byte alignment for ABI compliance */

	/* Enable the "SRAM" / shared memory - MSCC_CPU_SUBCPU_SYS_CFG */
        dmb     sy
        mov     x0, #0x94
        movk    x0, #0x6, lsl #32
        mov     w1, #0x2
        str     w1, [x0]
        dmb     sy
        mov     w1, #0x3
        str     w1, [x0]
        dmb     sy

	/* "C" early boot init */
	bl	boot0

	b	reset
