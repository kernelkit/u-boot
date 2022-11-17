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

#ifndef _SYMREG_H_
#define _SYMREG_H_

/** \brief Symbolic descriptiopn of a register. */
typedef struct {
	const char      *name;       /**< Name of register */
	unsigned long   addr;        /**< Address of register */
	u32             repl_cnt;    /**< Replication count of register */
	u32             repl_width;  /**< Replication width of register */
} vtss_symreg_reg_t;

/** \brief Symbolic descriptiopn of a register group. */
typedef struct {
	const char         *name;       /**< Name of register group */
	unsigned long      base_addr;   /**< Base address of register group */
	u32                repl_cnt;    /**< Replication count of register group */
	u32                repl_width;  /**< Replication width of register group */
	vtss_symreg_reg_t const *regs;  /**< Pointer to symbolic registers (null terminated) */
} vtss_symreg_reggrp_t;

/** \brief Symbolic descriptiopn of a register target. */
typedef struct {
	const char            *name;          /**< Name of register target */
	int                   repl_number;    /**< Target instance number */
	u32                   tgt_id;         /**< Target ID */
	unsigned long         base_addr;      /**< Base address */
	vtss_symreg_reggrp_t const *reggrps;  /**< Pointer to symbolic register groups (null terminated) */
} vtss_symreg_target_t;

extern int symreg_targets_cnt;
extern const vtss_symreg_target_t vtss_symreg_targets[];

#endif /* _SYMREG_H_ */
