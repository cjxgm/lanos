
#include "isr.h"
#include "printf.h"

// this gets called from interrupt.s
void isr_handler(regs_t regs)
{
	printf("recieved interrupt: %d\n", regs.int_no);
}

