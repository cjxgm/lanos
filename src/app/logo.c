
#include "app.h"
#include "lanosgl.h"
#include "monitor.h"
#include "timer.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

APP_INTERFACE(logo);

static u32 time_begin = 0;
static u32 time;
static u32 screen_w, screen_h;

static void reset_time(void);
static u32  get_time(void);
static void draw_box(float box[4][3]);

u8 main(const char * cmdline)
{
	if (startswith(cmdline, "--help")) {
		printf("\n\e%clogo\e%c\n", H|R|G|B, R|G|B);
		printf("\tShow the startup logo animation.\n"
				"\tCool, isn't it?\n\n");
		return 0;
	}

	get_pixel_resolution(&screen_w, &screen_h);

	gl_init(0, 0, screen_w, screen_h);
	gl_view(0, 0, screen_w, screen_h);

	/* TODO:
	   gl_persp(45, (float)screen_w / screen_h);
	   */

	reset_time();

	while (1) {
		if ((time = get_time()) > 4000) break;

		gl_clear();

		/* TODO:
		   gl_begin(GL_LINE_LOOP);
		   gl_color3(1.0f, 1.0f, 1.0f);
		   gl_vert( 10, 0, 10);
		   gl_vert( 0,  5, 10);
		   gl_vert(-10, 0, 10);
		   gl_end();
		   */

		gl_line(0, 0, 100,
				gl_map(time, 0, 2000, 0, screen_w * 2), screen_h, 100,
				0xFFFFFFFF, 0xFF000000);
		gl_line(screen_w, 0, 100,
				gl_map(time, 0, 2000, screen_w, -(s32)screen_w),
				screen_h, 100,
				0xFFFFFFFF, 0xFF000000);

		static float box[4][4][3] = {
			{{-10,  4, -10},
			 {-10, -4, -10},
			 {-10, -4,  10},
			 {-10,  4,  10}},
			{{ 10,  4, -10},
			 { 10, -4, -10},
			 { 10, -4,  10},
			 { 10,  4,  10}},
			{{-10, -4, -10},
			 { 10, -4, -10},
			 { 10,  4, -10},
			 {-10,  4, -10}},
			{{-10, -4,  10},
			 { 10, -4,  10},
			 { 10,  4,  10},
			 {-10,  4,  10}},
		};
		draw_box(box[0]);
		draw_box(box[1]);
		draw_box(box[2]);
		draw_box(box[3]);

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

void draw_box(float box[4][3])
{
	int i;
	for (i=0; i<4; i++) {
		int j = (i+1) & 3;
		float a[3];
		float b[3];
		float tt = -gl_map(time, 0, 4000, 0, PI * 8);
		a[0] = box[i][0] * cos(tt) - box[i][2] * sin(tt);
		a[1] = box[i][1];
		a[2] = box[i][2] * cos(tt) + box[i][0] * sin(tt);
		b[0] = box[j][0] * cos(tt) - box[j][2] * sin(tt);
		b[1] = box[j][1];
		b[2] = box[j][2] * cos(tt) + box[j][0] * sin(tt);

		a[0] += gl_map(time, 0, 4000, -(s32)screen_w, screen_w);
		b[0] += gl_map(time, 0, 4000, -(s32)screen_w, screen_w);
		a[1] -= 5.5;
		b[1] -= 5.5;

		a[2] += 45.0f;
		a[0] /= a[2] / 45.0f;
		a[1] /= a[2] / 45.0f;

		b[2] += 45.0f;
		b[0] /= b[2] / 45.0f;
		b[1] /= b[2] / 45.0f;

		gl_line(a[0] + (screen_w>>1), a[1] + (screen_h>>1), a[2],
				b[0] + (screen_w>>1), b[1] + (screen_h>>1), b[2],
				0xFF00FF00, 0xFF00FF00);
	}
}

