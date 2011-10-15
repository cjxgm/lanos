
#include "app.h"
#include "stdio.h"
#include "string.h"

APP_INTERFACE(lush);

#define BUF_SIZE	255

u8 main(const char * cmdline)
{
	if (startswith(cmdline, "--help")) {
		printf("\n\e%clush - Lanos Ugly SHell\e%c\n", H|R|G|B, R|G|B);
		printf("\tI think you are using it, right?\n\n");
		return 0;
	}

	char buf[BUF_SIZE+1];
	while (1) {
		printf("\e%clush\e%c$ \e%c", H|G, H|R|G|B, R|G|B);
		readline(buf, BUF_SIZE);

		if (!*buf) continue;

		if (startswith(buf, "exit"))
			return 0;

		struct app * a;
		u32 i = 0;
		u32 t;
		while ((a = get_app(i++)))
			if ((t = startswith(buf, a->name))) {
				char * name    = buf;
				char * cmdline = buf + t;
				if (*cmdline) *cmdline++ = 0;
				if ((t = run_app(name, cmdline)))
					printf("app returned %d\n", t);
				goto _app_found;
			}

		// app not found
		printf("\e%cinvalid command: \e%c%s\e%c\n", H|R, H|R|G, buf, R|G|B);

_app_found:
		get_app(0);	// nop

/*
		else if ((t = startswith(buf, "help"))) {
			struct app * a;
			int i = 0;
		}

		else if ((t = startswith(buf, "cls")))
			printf("\032");

		else if ((t = startswith(buf, "hello")))
			printf("Hello, world!\n");

		else if ((t = startswith(buf, "echo"))) {
			p += t;
			if (*p) p++;
			printf("%s\n", p);
		}

		else if ((t = startswith(buf, "video"))) {
			//init_video();
			assert(!"TODO");
		}

		else if ((t = startswith(buf, "anim")))
			app_anim();

		else if ((t = startswith(buf, "reboot")))
			reboot();

		else if ((t = startswith(buf, "poweroff")))
			poweroff();

		else printf("\e%cUnknown command: \e%c%s\e%c\n",
				H|R, H|R|B, buf, R|G|B);
	*/
	}
	return 0;
}

