
#include "video_driver.h"
#include "emu86.h"
#include "assert.h"

VIDEO_DRIVER_INTERFACE(vesa);

static struct emu86_state state;

u8 init(void)
{
	// TODO
	*(u8 *)0x7c00 = 0xF4;	// hlt
	CS(state) = 0x07c0;
	DS(state) = 0x07c0;
	SS(state) = 0x07c0;
	IP(state) = 0;
	SP(state).a = 0x100;
	AX(state).a = 0x4F00;
	emu86_int (&state, 0x10);
	emu86_exec(&state);

	return 1;	// failed
}

void free(void)
{
}

void get_resolution(u32 * w, u32 * h)
{
	assert(!"TODO");
}

void set_cursor_pos(u32 x, u32 y)
{
	assert(!"TODO");
}

void get_cursor_pos(u32 * x, u32 * y)
{
	assert(!"TODO");
}

void putchar(u16 ch_with_attr, u32 x, u32 y)
{
	assert(!"TODO");
}

u16 getchar(u32 x, u32 y)
{
	assert(!"TODO");
	return 0;
}

void putpixel(u32 x, u32 y, u32 color)
{
	assert(!"TODO");
}

