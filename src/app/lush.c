
#include "app/lush.h"
#include "stdio.h"
#include "keyboard.h"

u8 app_lush(void)
{
	while (1) {
		printf("\e%clush\e%c$ \e%c", H|G, H|R|G|B, R|G|B);
		/*
		while (!inkey(0x1C));	// wait for '\n' down
		while (inkey(0x1C));	// wait for '\n' up
		*/
		while (1) {
			char ch;
			scanf("%c", &ch);
			if (ch == '\n') break;
		}
	}
	return 0;
}

