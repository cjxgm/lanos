
#include "app.h"
#include "video_driver.h"
#include "keyboard.h"
#include "timer.h"
#include "assert.h"
#include "math.h"

#define MAP_W	60
#define MAP_H	20

u8 app_anim(void)
{
	u8 map[MAP_W*MAP_H][4];
	int x, y;

	float cx = 0.0f;
	float cy = 0.0f;

	while (!inkey(0x01)) {

		for (y=0; y<MAP_H; y++)
			for (x=0; x<MAP_W; x++) {
				float d = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));
				map[y*MAP_W+x][1] = 255 - d * 255 / MAP_W;
				map[y*MAP_W+x][2] = d * 255 / MAP_H;
			}

		// draw to screen
		for (y=0; y<MAP_H; y++)
			for (x=0; x<MAP_W; x++)
				get_video_driver(0)->putpixel(x, y,
						*(u32 *)map[y*MAP_W+x]);

		// wait
		u32 t = get_ticks();
		while ((get_ticks() - t) * 1000 / TICKS_PER_SEC < 34);

		// calculate
		cx += 0.6;
		cy += 0.4;
		if (cx > MAP_W) cx = 0;
		if (cy > MAP_H) cy = 0;
	}

	return 0;
}
