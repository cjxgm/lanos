
#ifndef __KEYBOARD__
#define __KEYBOARD__

#include "common.h"

void init_keyboard(void);
u8 inkey(u8 key);
u8 getchar(void);
void ungetchar(u8 ch);

#endif

