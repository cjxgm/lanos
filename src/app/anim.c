
#include "app.h"
#include "monitor.h"
#include "keyboard.h"
#include "timer.h"
#include "assert.h"
#include "math.h"

static void line(s32 x0, s32 y0, s32 x1, s32 y1, u32 color);

u8 app_anim(void)
{
	u32 w, h;
	get_pixel_resolution(&w, &h);

	s8 d = 1;
	s16 contrast = 0;

	while (!inkey(0x01)) {	// 0x01 --> ESC
		contrast += d*4;

		// draw to screen
		u8 cx = w >> 1;
		u8 cy = h >> 1;
		int x, y;
		for (y=0; y<h; y++) {
			for (x=0; x<w; x++) {
				s32 clr = sqrt((x-cx)*(x-cx)/4
						+ (y-cy)*(y-cy)) * 255 / h * 2;
				clr = 255 - clr;
				if (clr < 0) clr = 0;
				clr = clr * contrast / 255;
				clr = clr << 8;
				putpixel(x, y, clr);
			}
		}

		// the line
		line(2, 10, contrast * 80 / 0xFF, 14, contrast);
		line(72, 20, 4, contrast * 25 / 0xFF,
			(0xFF-contrast)|((0xFF-contrast)<<8));
		line(40, 0, contrast * 80 / 0xFF, 20, 0xFFFFFF);

		// calculate
		if (d == 1 && contrast >= 0xFF) d = -1;
		if (d == -1 && contrast <= 0) d = 1;

		// wait
		u32 t = get_ticks();
		while ((get_ticks() - t) * 1000 / TICKS_PER_SEC < 10);
	}

	clear_screen();
	return 0;
}

void line(s32 x0, s32 y0, s32 x1, s32 y1, u32 color)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float d  = sqrt(dx*dx + dy*dy);
	float c  = dx / d;
	float s  = dy / d;

	int i;
	for (i=0; i<=d; i++) {
		float x = i*c + x0;
		float y = i*s + y0;
		if (x<0 || y<0) continue;
		putpixel(x, y, color);
	}
}
