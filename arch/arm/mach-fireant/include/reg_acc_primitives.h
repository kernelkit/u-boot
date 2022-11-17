#ifndef _REG_ACC_PRIMITIVES
#define _REG_ACC_PRIMITIVES

#if !defined(__UBOOT__)
typedef enum {
    WAIT_START = 0x1,
    WAIT_FINISH,
    TIMEOUT,
    ERROR_MSG,
    SUCCESS,
} MSG_CODE;
#else
#define WAIT_START	"start"
#define WAIT_FINISH	"finish"
#define TIMEOUT		"timeout"
#define ERROR_MSG	"error"
#define SUCCESS		"sucess"
#endif

#if !defined(__UBOOT__)
static inline void my_print(const MSG_CODE val, const uint16_t msg)
{
	wr_reg(CPU, CPU_REGS, GPR(0), ((val << 16) | msg));
}
#else
static inline void my_print(const char *what, const uint16_t msg)
{
#if defined(DEBUG)
	printascii("print:");
	printascii(what);
	printch(',');
	printhex4(msg);
	printch('\n');
#endif
}
#endif

#if !defined(__UBOOT__)
inline void barrier()
{
  asm volatile("dsb sy");
  asm volatile("isb sy");
}
#endif

static inline u32 reg_read(void * addr)
{
	u32 val = readl(addr);
#if defined(READ_DEBUG)
	printch('R');
	printhex2(((u64)addr) >> 32);
	printhex8((ulong) addr);
	printch('=');
	printhex8(val);
	printch('\n');
#endif
	return val;
}

static inline void reg_write(u32 val, void * addr)
{
	writel(val, addr);
	dmb();
#if defined(WRITE_DEBUG)
	printch('W');
	printhex2(((u64)addr) >> 32);
	printhex8((ulong) addr);
	printch(',');
	printhex8(val);
	printch('\n');
#endif
}

// Macros used to make code easier to maintain and read
// Code looks similar to erf
// The macros below build expressions with the macros defined in the header files
// Support for replicated registers needs to be added

// read register
#define rd_reg(tgt,grp,reg) \
	reg_read(VTSS_##tgt##_##grp##_##reg)

// write register
#define wr_reg(tgt,grp,reg,val) \
	reg_write(val,VTSS_##tgt##_##grp##_##reg)

// write field, source shadow, destination shadow
#define wr_fld_s_s(shadow_val,tgt,grp,reg,fld,fld_val) \
    ((shadow_val & (~VTSS_M_##tgt##_##grp##_##reg##_##fld)) | VTSS_F_##tgt##_##grp##_##reg##_##fld(fld_val) )

// write field, source reg, destination shadow
#define wr_fld_r_s(tgt,grp,reg,fld,fld_val) \
    wr_fld_s_s(rd_reg(tgt,grp,reg),tgt,grp,reg,fld,fld_val)

// write field, source shadow, destination reg
#define wr_fld_s_r(shadow_val,tgt,grp,reg,fld,fld_val) \
    wr_reg(tgt,grp,reg,wr_fld_s_s(shadow_val,tgt,grp,reg,fld,fld_val))

// write field, source reg, destination reg
#define wr_fld_r_r(tgt,grp,reg,fld,fld_val) \
    wr_fld_s_r(rd_reg(tgt,grp,reg),tgt,grp,reg,fld,fld_val)

// read field, source shadow
#define rd_fld_s(shadow_val,tgt,grp,reg,fld) \
    VTSS_X_##tgt##_##grp##_##reg##_##fld(shadow_val)

// read field, source register
#define rd_fld_r(tgt,grp,reg,fld) \
    rd_fld_s(rd_reg(tgt,grp,reg),tgt,grp,reg,fld)

#endif
