
#include "app.h"
#include "video_driver.h"
#include "monitor.h"
#include "keyboard.h"
#include "timer.h"
#include "assert.h"
#include "math.h"

u8 app_anim(void)
{
	u32 w, h;
	get_video_driver(0)->get_resolution(&w, &h);

	s8 d = 1;
	s16 contrast = 0;

	while (!inkey(0x01)) {
		contrast += d*4;
		// draw to screen
		u8 cx = w >> 1;
		u8 cy = h >> 1;
		int x, y;
		for (y=0; y<h; y++) {
			for (x=0; x<w; x++) {
				s32 clr = sqrt((x-cx)*(x-cx)/4 + (y-cy)*(y-cy)) * 255 / h * 2;
				clr = 255 - clr;
				if (clr < 0) clr = 0;
				clr = clr * contrast / 255;
				clr = clr << 16;
				get_video_driver(0)->putpixel(x, y, clr);
			}
		}

		if (d == 1 && contrast >= 0xFF) d = -1;
		if (d == -1 && contrast <= 0) d = 1;

		// wait
		u32 t = get_ticks();
		while ((get_ticks() - t) * 1000 / TICKS_PER_SEC < 10);
	}

	clear_screen();
	return 0;
}
