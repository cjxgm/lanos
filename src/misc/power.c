
#include "power.h"
#include "common.h"
#include "assert.h"

void power_off(void)
{
	assert(!"You can shutdown the computer safely.");
}

void power_reboot(void)
{
	// clear keyboard buffer
	while (inb(0x64) & 2)
		inb(0x60);
	
	// Use the 8042 keyboard controller to pulse the CPU's RESET pin
	outb(0x64, 0xFE);
	// if that didn't work, halt the CPU
	asm volatile ("hlt");
}

