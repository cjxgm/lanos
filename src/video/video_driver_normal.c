
#include "video_driver.h"

VIDEO_DRIVER_INTERFACE(normal);

u16 * vid_mem = (u16 *)0xb8000;
u8 cursor_x = 0;
u8 cursor_y = 0;

u8 _init(void)
{
	return 0;
}

void _free(void)
{
}

void _get_text_resolution(u32 * w, u32 * h)
{
	*w = 80;
	*h = 25;
}

void _get_pixel_resolution(u32 * w, u32 * h)
{
	*w = 80;
	*h = 25;
}

void _set_cursor_pos(u32 x, u32 y)
{
	u32 w, h;
	_get_text_resolution(&w, &h);

	cursor_x = (x<w ? x : w-1);
	cursor_y = (y<h ? y : h-1);

	u16 cursor_pos = cursor_y * w + cursor_x;

	// high cursor byte.
	outb(0x3D4, 14);
	outb(0x3D5, cursor_pos >> 8);
	// low cursor byte.
	outb(0x3D4, 15);
	outb(0x3D5, cursor_pos);
}

void _get_cursor_pos(u32 * x, u32 * y)
{
	*x = cursor_x;
	*y = cursor_y;
}

void _putchar(u16 ch_with_attr, u32 x, u32 y)
{
	u32 w, h;
	_get_text_resolution(&w, &h);

	if (x >= w || y >= h) return;
	vid_mem[y*w + x] = ch_with_attr;
}

u16 _getchar(u32 x, u32 y)
{
	u32 w, h;
	_get_text_resolution(&w, &h);

	if (x >= w || y >= h) return 0;
	return vid_mem[y*w + x];
}

void _putpixel(u32 x, u32 y, u32 color)
{
	u32 w, h;
	_get_pixel_resolution(&w, &h);

	if (x >= w || y >= h) return;

	u8 clr[4];
	*(u32 *)clr = color;

	u8 max = clr[0];
	if (clr[1] > max) max = clr[1];
	if (clr[2] > max) max = clr[2];
	float brightness = max / 255.0f;

	static const u8 br_ch[] = " ..--==%*1IL&VG#@%*1IL&VG#@";
	static const u8 br_hi[] = "000000000000000001111111111";
	u8 ch = br_ch[(int)(brightness * (sizeof(br_ch) - 2))];
	u16 hi = br_hi[(int)(brightness * (sizeof(br_hi) - 2))] - '0';
	hi = ((hi << 3)
		| ((clr[0]>0) << 2)
		| ((clr[1]>0) << 1)
		| (clr[2]>0)) << 8;

	_putchar(hi | ch, x, y);
}

