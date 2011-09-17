
#include "timer.h"
#include "isr.h"
#include "printf.h"
#include "monitor.h"

static u32 tick = 0;

static void timer_cb(regs_t regs)
{
	tick++;
	u8 x, y;
	monitor_get_cursor_pos(&x, &y);
	monitor_set_cursor_pos(0, 0);
	printf("\031\e%crunning \e%c%d\e%cs\n",
			H|R|B, H|R|G|B, tick / 50, R|G|B);
	monitor_set_cursor_pos(x, y);
}

void init_timer(u32 freq)
{
	register_irq_handler(IRQ_TIMER, &timer_cb);

	u32 divisor = 1193180 / freq;

	// send the command byte.
	outb(0x43, 0x36);

	// divisor has to be sent byte-wise,
	// so split here into higher/lower bytes.
	u8 l = (divisor & 0xFF);
	u8 h = ((divisor>>8) & 0xFF);

	// send the frequency divisor.
	outb(0x40, l);
	outb(0x40, h);

	// if not "sti", timer will not work!
	asm volatile ("sti");
}

