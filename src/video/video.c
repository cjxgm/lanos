
#include "emu86.h"
#include "assert.h"

static struct emu86_state state;

void init_video(void)
{
	*(u8 *)0x7c00 = 0xFF;	// execution end signature
	state.cs = 0x07c0;
	state.ds = 0x07c0;
	state.ss = 0x07c0;
	state.ip = 0;
	state.sp = 0x100;
	state.ax.a = 0x4F00;
	emu86_int(&state, 0x10);
}

