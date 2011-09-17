
#ifndef __MONITOR__
#define __MONITOR__

#include "common.h"

// write a single character out to the screen.
void monitor_put(char c);

// clear the screen to all black.
void monitor_clear(void);

// output a null-terminated ASCII string to the monitor.
void monitor_write(const char * str);

void monitor_get_cursor_pos(u8 * x, u8 * y);
void monitor_set_cursor_pos(u8   x, u8   y);

#endif

