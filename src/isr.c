
#include "isr.h"
#include "printf.h"

// this gets called from interrupt.s
void isr_handler(regs_t regs)
{
	if (regs.int_no < 32) {
		printf("\e%c>>> KERNEL PANIC <<<\e%c %d %X\n",
				BG(H|R), H|R|G|B, regs.int_no, regs.err_code);
	}
}

