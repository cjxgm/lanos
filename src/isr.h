
#ifndef __ISR__
#define __ISR__

#include "common.h"

typedef struct registers
{
	u32 ds;
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32 int_no, err_code;
	u32 eip, cs, eflags, useresp, ss;
} regs_t;

#endif

