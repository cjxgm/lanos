
#include "app/lush.h"
#include "stdio.h"
#include "keyboard.h"

u8 app_lush(void)
{
	char buf[256];
	while (1) {
		printf("\e%clush\e%c$ \e%c", H|G, H|R|G|B, R|G|B);
		/*
		while (!inkey(0x1C));	// wait for '\n' down
		while (inkey(0x1C));	// wait for '\n' up
		*/
		readline(buf, 256);
		printf("\e\xf%s\e\x7\n", buf);
	}
	return 0;
}

