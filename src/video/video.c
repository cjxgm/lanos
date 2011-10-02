
#include "emu86.h"
#include "assert.h"

static struct emu86_state state;

void init_video(void)
{
	*(u8 *)0x7c00 = 0xFF;	// execution end signature
	CS(state) = 0x07c0;
	DS(state) = 0x07c0;
	SS(state) = 0x07c0;
	IP(state) = 0;
	SP(state).a = 0x100;
	AX(state).a = 0x4F00;
	emu86_int(&state, 0x10);
	emu86_execute(&state);
}

