
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

typedef void (*irq_handler_t)(regs_t);

void register_irq_handler(u8 n, irq_handler_t handler);

#define IRQ_TIMER	0

#endif

