// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Microsemi Corporation
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <console.h>

#include "symreg.h"

#define MAXNAME 1024

static bool ctlc;
static int maxlen = 40;

static size_t mk_target_name(const vtss_symreg_target_t *target,
			     char *buffer,
			     size_t buflen)
{
	char *p = buffer;
	size_t len = snprintf(p, buflen, "%s", target->name);
	buflen -= len, p += len;
	if (target->repl_number >= 0) {
		len = snprintf(p, buflen, "[%d]", target->repl_number);
		buflen -= len, p += len;
	}
	return p - buffer;
}

static size_t mk_reggrp_name(const vtss_symreg_reggrp_t *reggrp,
			     char *buffer,
			     size_t buflen,
			     int repl)
{
	char *p = buffer;
	size_t len = snprintf(p, buflen, "%s", reggrp->name);
	buflen -= len, p += len;
	if (reggrp->repl_cnt > 1) {
		len = snprintf(p, buflen, "[%d]", repl);
		buflen -= len, p += len;
	}
	return p - buffer;
}

static size_t mk_reg_name(const vtss_symreg_reg_t *reg,
			  char *buffer,
			  size_t buflen,
			  int repl)
{
	char *p = buffer;
	size_t len = snprintf(p, buflen, "%s", reg->name);
	buflen -= len, p += len;
	if (reg->repl_cnt > 1) {
		len = snprintf(p, buflen, "[%d]", repl);
		buflen -= len, p += len;
	}
	return p - buffer;
}

static size_t mk_regname(char *buffer,
			 size_t buflen,
			 const vtss_symreg_target_t *target,
			 const vtss_symreg_reggrp_t *reggrp,
			 int grpinst,
			 const vtss_symreg_reg_t *reg,
			 int reginst)
{
	char *p = buffer;
	size_t len;

	len = mk_target_name(target, p, buflen);
	buflen -= len, p += len;
	*p++ = ':', buflen--;
	len = mk_reggrp_name(reggrp, p, buflen, grpinst);
	buflen -= len, p += len;
	*p++ = ':', buflen--;
	len = mk_reg_name(reg, p, buflen, reginst);
	buflen -= len, p += len;

	return p - buffer;
}

static bool SYMREG_wildcmp(const char *w, const char *s)
{
	const char *cp = NULL, *mp = NULL;
	const char *wild = w, *string = s;

	while (*string && *wild != '*') {
		if (*wild != *string && *wild != '?') {
			return false;
		}

		wild++;
		string++;
	}

	while (*string) {
		if (*wild == '*') {
			if (!*++wild) {
				return true;
			}

			mp = wild;
			cp = string + 1;
		} else if ((*wild == *string) || (*wild == '?')) {
			wild++;
			string++;
		} else {
			if (cp == NULL) {
				printf("Error when matching wild = %s against string = %s", w, s);
				return false;
			}

			wild = mp;
			string = cp++;
		}
	}

	if (wild == NULL) {
		printf("Error when matching wild = %s against string = %s", w, s);
		return false;
	}

	while (*wild == '*') {
		wild++;
	}

	return !*wild;
}

static void print_reg_inst(const char *pattern,
			   const vtss_symreg_target_t *target,
			   const vtss_symreg_reggrp_t *reggrp,
			   int grpinst,
			   const vtss_symreg_reg_t *reg,
			   int reginst)
{
	char buffer[MAXNAME];
	size_t regnamelen;

	regnamelen = mk_regname(buffer, sizeof(buffer),
				target, reggrp, grpinst, reg, reginst);

	if (SYMREG_wildcmp(pattern, buffer)) {
		u64 addr = target->base_addr + 4*(reggrp->base_addr +
						  (reggrp->repl_width * grpinst) +
						  reg->addr + reginst);
		int j;
		u32 val;

		val = readl(addr);

		if (regnamelen > maxlen)
			maxlen = regnamelen;

		printf("%-*s: 0x%08llx = 0x%08x   ", maxlen, buffer, addr, val);
		for (j = 31; j >= 0; j--) {
			putc('0' + ((val >> j) & 1));
			if (j > 0 && (j % 4) == 0)
				putc('.');
		}
		putc('\n');
	}
}

static void print_reg(const char *pattern,
		      const vtss_symreg_target_t *target,
		      const vtss_symreg_reggrp_t *reggrp,
		      int grpinst,
		      const vtss_symreg_reg_t *reg)
{
	int i;
	for (i = 0; (!ctlc) && i < reg->repl_cnt; i++) {
		print_reg_inst(pattern, target, reggrp, grpinst, reg, i);
		if (ctrlc()) {
			puts("Abort\n");
			ctlc = true;
			return;
		}
	}
}

static void print_grp_inst(const char *pattern,
			   const vtss_symreg_target_t *target,
			   const vtss_symreg_reggrp_t *reggrp,
			   int grpinst)
{
	const vtss_symreg_reg_t *reg = reggrp->regs;
	while ((!ctlc) && reg->name) {
		print_reg(pattern, target, reggrp, grpinst, reg);
		reg++;
	}
}

static void print_grp(const char *pattern,
		      const vtss_symreg_target_t *target,
		      const vtss_symreg_reggrp_t *reggrp)
{
	int i;
	for (i = 0; (!ctlc) && i < reggrp->repl_cnt; i++) {
		print_grp_inst(pattern, target, reggrp, i);
	}
}

static void print_symreg(const char *pattern)
{
	int i;

	for (i = 0; i < symreg_targets_cnt; i++) {
		const vtss_symreg_target_t *target = &vtss_symreg_targets[i];
		const vtss_symreg_reggrp_t *reggrp = target->reggrps;
		while ((!ctlc) && reggrp->name) {
			print_grp(pattern, target, reggrp);
			reggrp++;
		}
	}
}

static int do_symreg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	--argc, argv++;

	ctlc = false;
	while ((!ctlc) && argc--) {
		print_symreg(*argv++);
	}

	return 0;
}

U_BOOT_CMD(
	symreg,	99,	1,	do_symreg,
	"print registers by symbolic names",
	""
);
