
#include "app.h"
#include "lanosgl.h"
#include "monitor.h"
#include "timer.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

APP_INTERFACE(logo);

static u32 time_begin = 0;

static void reset_time(void);
static u32  get_time(void);

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

	gl_persp(45, (float)screen_w / screen_h);

	reset_time();

	while (1) {
		if (get_time() > 2000) break;

		gl_clear();

		gl_begin(GL_LINE_LOOP);
		gl_color3(1.0f, 1.0f, 1.0f);
		gl_vert( 10, 0, 10);
		gl_vert( 0,  5, 10);
		gl_vert(-10, 0, 10);
		gl_end();

		gl_line(0, 0, 0,
				gl_map(get_time(), 0, 2000, 0, screen_w * 2), screen_h, 0,
				0xFFFFFFFF, 0xFF000000);
		gl_line(screen_w, 0, 0,
				gl_map(get_time(), 0, 2000, screen_w, -(s32)screen_w),
				screen_h, 0,
				0xFFFFFFFF, 0xFF000000);

		gl_swap();
	}

	gl_free();
	clear_screen();

	return 0;
}

void reset_time(void)
{
	time_begin = clock();
}

u32 get_time(void)
{
	return (clock() - time_begin) * 1000 / CLOCKS_PER_SEC;
}

