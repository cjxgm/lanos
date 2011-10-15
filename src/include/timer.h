
#ifndef __TIMER__
#define __TIMER__

#include "common.h"

#define CLOCKS_PER_SEC	1000

void init_timer(void);
u32  clock(void);         // CLOCKS_PRE_SEC clocks per sec

// 1000 ticks per sec
#define get_ticks()    (clock() * 1000 / CLOCKS_PER_SEC)
#define wait(ticks)    do { \
	u32 __t = get_ticks(); \
	while (get_ticks() - __t < (ticks)); \
} while (0)

#endif

