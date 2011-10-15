
#include "app.h"
#include "stdio.h"

APP_INTERFACE(help);

u8 main(const char * cmdline)
{
	printf("\n\e%ctype `\e%ccommand\e%c --help\e%c'"
			" to get the specific help.\n"
			"\e%cexisted commands:\e%c\n",
			R|G, H|B, H|R|G, R|G, R|B, H|B);
	struct app * a;
	int i = 0;
	while ((a = get_app(i++)))
		printf("\t%s\n", a->name);
	printf("\t\e%cexit\e%c\n\n", H|G|B, R|G|B);
	return 0;
}

