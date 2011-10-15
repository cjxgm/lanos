
#include "app.h"
#include "stdio.h"
#include "string.h"
#include "monitor.h"

APP_INTERFACE(cls);

u8 main(const char * cmdline)
{
	if (startswith(cmdline, "--help")) {
		printf("\n\e%ccls - CLear Screen\e%c\n", H|R|G|B, R|G|B);
		printf("\tJust as it may sound, it will clear the screen"
			" and relocate the cursor to\n\tthe left-upper"
			" corner of the screen.\n\n");
		return 0;
	}

	clear_screen();

	return 0;
}

