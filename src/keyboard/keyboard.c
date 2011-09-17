
#include "keyboard.h"
#include "common.h"
#include "printf.h"
#include "isr.h"
#include "assert.h"

static void keyboard_handler(regs_t regs);

void init_keyboard(void)
{
	register_irq_handler(IRQ_KEYBOARD, &keyboard_handler);
}

void keyboard_handler(regs_t regs)
{
	u8 key = inb(0x60);

	// when press ESC, hang up the OS
	assert(key != 0x01 && "system hanged up");

	printf("Key hitted: %x (%d)\n", key, key);
}

