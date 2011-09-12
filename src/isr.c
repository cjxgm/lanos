
#include "isr.h"
#include "printf.h"

static const char * err_msgs[] = {
	"Division by zero exception",
	"Debug exception",
	"Non maskable interrupt",
	"Breakpoint exception",
	"Into detected overflow",
	"Out of bounds exception",
	"Invalid opcode exception",
	"No coprocessor exception",
	"Double fault *",
	"Coprocessor segment overrun",
	"Bad TSS *",
	"Segment not present *",
	"Stack fault *",
	"General protection fault *",
	"Page fault *",
	"Unknown interrupt exception",
	"Coprocessor fault",
	"Alignment check exception",
	"Machine check exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

// this gets called from interrupt.s
void isr_handler(regs_t regs)
{
	if (regs.int_no < 32) {
		printf("\e%c>>> KERNEL PANIC <<<\e%c\t%d\t%X\t%s\n",
				BG(H|R), H|R|G|B, regs.int_no, regs.err_code,
				err_msgs[regs.int_no]);
		while (1);
	}
}

