
#include "video_driver.h"
#include "emu86.h"
#include "assert.h"

VIDEO_DRIVER_INTERFACE(vesa);

static struct emu86_state state;

u8 _init(void)
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

void _free(void)
{
}

void _get_resolution(u32 * w, u32 * h)
{
	assert(!"TODO");
}

void _set_cursor_pos(u32 x, u32 y)
{
	assert(!"TODO");
}

void _get_cursor_pos(u32 * x, u32 * y)
{
	assert(!"TODO");
}

void _putchar(u16 ch_with_attr, u32 x, u32 y)
{
	assert(!"TODO");
}

u16 _getchar(u32 x, u32 y)
{
	assert(!"TODO");
	return 0;
}

void _putpixel(u32 x, u32 y, u32 color)
{
	assert(!"TODO");
}

