
#include "video_driver.h"
#include "assert.h"
#include "math.h"

VIDEO_DRIVER_INTERFACE(normal);

u16 * vid_mem = (u16 *)0xb8000;
u8 cursor_x = 0;
u8 cursor_y = 0;

u8 init(void)
{
	return 0;
}

void free(void)
{
}

void get_resolution(u32 * w, u32 * h)
{
	*w = 80;
	*h = 25;
}

void set_cursor_pos(u32 x, u32 y)
{
	u32 w, h;
	get_resolution(&w, &h);

	cursor_x = x;
	cursor_y = y;

	u16 cursor_pos = cursor_y * w + cursor_x;

	// tell the VGA board we are setting the high cursor byte.
	outb(0x3D4, 14);
	// Send the high cursor byte.
	outb(0x3D5, cursor_pos >> 8);

	// tell the VGA board we are setting the low cursor byte.
	outb(0x3D4, 15);
	// Send the low cursor byte.
	outb(0x3D5, cursor_pos);
}

void get_cursor_pos(u32 * x, u32 * y)
{
	*x = cursor_x;
	*y = cursor_y;
}

void putchar(u16 ch_with_attr, u32 x, u32 y)
{
	u32 w, h;
	get_resolution(&w, &h);
	vid_mem[y * w + x] = ch_with_attr;
}

u16 getchar(u32 x, u32 y)
{
	u32 w, h;
	get_resolution(&w, &h);
	return vid_mem[y * w + x];
}

void putpixel(u32 x, u32 y, u32 color)
{
	u32 w, h;
	get_resolution(&w, &h);

	if (x >= w || y >= h) return;

	u8 clr[4];
	*(u32 *)clr = color;

	// TODO: float a = (float)clr[0] / 255.0f;
	float r = (float)clr[1] / 255.0f;
	float g = (float)clr[2] / 255.0f;
	float b = (float)clr[3] / 255.0f;
	float brightness = sqrt(0.241f * r * r
			+ 0.691f * g * g
			+ 0.068f * b * b);

	char br_hi[] = "00011";
	char br_ch[] = "-=#=#";

	u16 t = 0;
	t |= (b > 0.2f) << 0;
	t |= (g > 0.2f) << 1;
	t |= (r > 0.2f) << 2;
	t |= (br_hi[(int)(brightness * (sizeof(br_hi) - 1))] - '0') << 3;
	t <<= 8;
	t |= br_ch[(int)(brightness * (sizeof(br_ch) - 1))];

	putchar(t, x, y);
}

