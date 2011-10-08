
#ifndef __MONITOR__
#define __MONITOR__

#include "common.h"

void init_monitor(void);
void clear_screen(void);
void putchar(char ch);
void putpixel(u32 x, u32 y, u32 color);
void get_text_resolution (u32 * w, u32 * h);
void get_pixel_resolution(u32 * w, u32 * h);
void get_cursor_pos(u32 * x, u32 * y);
void set_cursor_pos(u32   x, u32   y);

#endif

