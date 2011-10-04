
#ifndef __MONITOR__
#define __MONITOR__

#include "common.h"

void select_video_driver(void);
void putchar(char ch);
void clear_screen(void);
void get_cursor_pos(u32 * x, u32 * y);
void set_cursor_pos(u32   x, u32   y);

#endif

