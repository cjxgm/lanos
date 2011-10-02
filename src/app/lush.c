
#include "app/lush.h"
#include "stdio.h"
#include "string.h"

#define BUF_SIZE	255

u8 app_lush(void)
{
	char buf[BUF_SIZE+1];
	while (1) {
		printf("\e%clush\e%c$ \e%c", H|G, H|R|G|B, R|G|B);
		readline(buf, BUF_SIZE);

		u32 t;
		char * p = buf;

		if (!*p) continue;

		else if ((t = startswith(buf, "help"))) {
			printf("\thelp			show this help\n");
			//   one more tab here .-v-. is a must.
			printf("\tcls				clear screen\n");
			printf("\thello			show \"Hello, world\"\n");
			printf("\techo			show arguments of it\n");
		}

		else if ((t = startswith(buf, "cls")))
			printf("\032\n");	// '\n' skips the first timing line.

		else if ((t = startswith(buf, "hello")))
			printf("Hello, world!\n");

		else if ((t = startswith(buf, "echo"))) {
			p += t;
			if (*p) p++;
			printf("%s\n", p);
		}

		else printf("\e%cUnknown command: \e%c%s\e%c\n",
					H|R, H|R|B, buf, R|G|B);
	}
	return 0;
}

