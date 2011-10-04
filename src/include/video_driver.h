
#ifndef __VIDEO_DRIVER__
#define __VIDEO_DRIVER__

#include "common.h"

struct video_driver
{
	const char * name;

	// return 0 when succeed.
	u8   (*init)(void);
	void (*free)(void);
	void (*get_resolution)(u32 * w, u32 * h);

	void (*set_cursor_pos)(u32 x, u32 y);
	void (*get_cursor_pos)(u32 * x, u32 * y);

	void (*putchar)(u16 ch_with_attr, u32 x, u32 y);
	u16  (*getchar)(u32 x, u32 y);

	// color is formatted in ARGB
	void (*putpixel)(u32 x, u32 y, u32 color);
	// TODO: u32  (*getpixel)(u32 x, u32 y);
};

// return NULL if id is invalid.
struct video_driver * get_video_driver(u32 id);

#define VIDEO_DRIVER_INTERFACE(NAME) \
	static u8   init(void);\
	static void free(void);\
	static void get_resolution(u32 * w, u32 * h);\
	static void set_cursor_pos(u32 x, u32 y);\
	static void get_cursor_pos(u32 * x, u32 * y);\
	static void putchar(u16 ch_with_attr, u32 x, u32 y);\
	static u16  getchar(u32 x, u32 y);\
	static void putpixel(u32 x, u32 y, u32 color);\
	struct video_driver video_driver_ ## NAME = {\
		.name = #NAME,\
		.init = &init,\
		.free = &free,\
		.get_resolution = &get_resolution,\
		.set_cursor_pos = &set_cursor_pos,\
		.get_cursor_pos = &get_cursor_pos,\
		.putchar = &putchar,\
		.getchar = &getchar,\
		.putpixel = &putpixel,\
	};

#endif

