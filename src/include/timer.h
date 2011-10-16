
#ifndef __TIMER__
#define __TIMER__

#include "common.h"

#define CLOCKS_PER_SEC	1000

void init_timer(void);
u32  clock(void);

#define wait(ticks)    do { \
	u32 __t = clock(); \
	while (clock() - __t < (ticks) * CLOCKS_PER_SEC / 1000); \
} while (0)

#endif

