
#include "isr.h"
#include "stdio.h"
#include "assert.h"

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

static irq_handler_t irq_handlers[16] = { NULL };

// this gets called from interrupt.s
void isr_handler(regs_t regs)
{
	// error
	if (regs.int_no < 32) {
		printf("\e%c>>> KERNEL PANIC <<<\e%c\t%d\t%X\t%s\n",
				BG(H|R), H|R|G|B, regs.int_no, regs.err_code,
				err_msgs[regs.int_no]);
		while (1);
	}

	// irq
	if (regs.int_no < 32 + 16) {
		// send an EOI (end of interrupt) signal to the PICs.
		// if this interrupt involved the slave.
		if (regs.int_no >= 40)	// need send reset signal to slave.
			outb(0xA0, 0x20);
		// send reset signal to master.
		outb(0x20, 0x20);

		if (irq_handlers[regs.int_no - 32])
			irq_handlers[regs.int_no - 32](regs);
	}
}

void register_irq_handler(u8 n, irq_handler_t handler)
{
	assert(n >= 0 && n < 16);
	irq_handlers[n] = handler;
}

