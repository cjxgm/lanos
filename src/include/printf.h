
#ifndef __PRINTF__
#define __PRINTF__

void printf(const char * fmt, ...);

// colors
// usage: printf("\e%c", R|G|B);
#define H			(1<<3)
#define R			(1<<2)
#define G			(1<<1)
#define B			(1<<0)
#define BG(CLR)		((CLR) << 4)

#endif

