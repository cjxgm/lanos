
#ifndef __STDIO__
#define __STDIO__

#include "keyboard.h"

// colors
// usage: printf("\e%c", R|G|B);
#define H			(1<<3)
#define R			(1<<2)
#define G			(1<<1)
#define B			(1<<0)
#define BG(CLR)		((CLR) << 4)

void printf(const char * fmt, ...);
void scanf (const char * fmt, ...);
void readline(char * buf, u32 size);

#endif

