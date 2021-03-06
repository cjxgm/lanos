
#include "timer.h"
#include "isr.h"

static u32 clocks = 0;

static void timer_cb(regs_t regs)
{
	clocks++;
}

void init_timer(void)
{
	register_irq_handler(IRQ_TIMER, &timer_cb);

	u32 divisor = 1193180 / CLOCKS_PER_SEC;

	// send the command byte.
	outb(0x43, 0x36);

	// divisor has to be sent byte-wise,
	// so split here into higher/lower bytes.
	u8 l = (divisor & 0xFF);
	u8 h = ((divisor>>8) & 0xFF);

	// send the frequency divisor.
	outb(0x40, l);
	outb(0x40, h);
}

u32 clock(void)
{
	return clocks;
}
