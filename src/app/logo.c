
#include "app.h"
#include "lanosgl.h"
#include "monitor.h"
#include "timer.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

APP_INTERFACE(logo);

u8 main(const char * cmdline)
{
	if (startswith(cmdline, "--help")) {
		printf("\n\e%clogo\e%c\n", H|R|G|B, R|G|B);
		printf("\tShow the startup logo animation.\n"
				"\tCool, isn't it?\n\n");
		return 0;
	}

	u32 screen_w, screen_h;
	get_pixel_resolution(&screen_w, &screen_h);

	gl_init(0, 0, screen_w, screen_h);
	gl_view(0, 0, screen_w, screen_h);

	float t = 0;
	while (1) {
		gl_clear();
		gl_line(0, 0, 0,
				2*t, screen_h, 0,
				0xFFFFFFFF, 0xFF000000);
		gl_line(screen_w, 0, 0,
				screen_w - 2*t, screen_h, 0,
				0xFFFFFFFF, 0xFF000000);
		gl_swap();

		t += 0.2;
		if (t > screen_w) break;

		wait(10);
	}

	gl_free();
	clear_screen();

	return 0;
}

