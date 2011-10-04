
#include "monitor.h"
#include "video_driver.h"
#include "power.h"

static struct video_driver * vid_drv = NULL;
static u8 out_mode = 0;

void select_video_driver(void)
{
	int i = 0;
	struct video_driver * drv;

	while ((drv = get_video_driver(i++))) {
		if (drv->init())	// initialize failed
			continue;
		vid_drv = drv;
		break;
	}

	if (!vid_drv) reboot();
}

void putchar(char ch)
{
	static u16 attr = 7 << 8;

	u32 cursor_x;
	u32 cursor_y;
	get_cursor_pos(&cursor_x, &cursor_y);

	u32 w, h;
	vid_drv->get_resolution(&w, &h);

	// You can change attribute by using "\e\x??"
	if (out_mode == 1) {
		attr = ch << 8;
		out_mode = 0;
		return;
	}
	if (ch == '\033') {	// \033 = \e, change attribute
		out_mode = 1;
		return;
	}

	if (ch == '\032') {	// \032, clear whole screen
		clear_screen();
		cursor_x = cursor_y = 0;
	}

	else if (ch == '\031') {	// \031, clear current line
		int i;
		for (i=0; i<w; i++)
			vid_drv->putchar((7 << 8) | ' ', i, cursor_y);
		cursor_x = 0;
	}

	else if (ch == '\b' && cursor_x)
		cursor_x--;

	else if (ch == '\t')
		cursor_x = (cursor_x+4) & ~(4-1);

	else if (ch == '\r')
		cursor_x = 0;

	else if (ch == '\n') {
		cursor_x = 0;
		cursor_y++;
	}
	else if(ch >= ' ')	// other printable char.
		vid_drv->putchar(ch | attr, cursor_x++, cursor_y);

	if (cursor_x >= w) {	// reached end of screen
		cursor_x = 0;
		cursor_y++;
	}

	if (cursor_y >= h) {	// scroll the screen if needed.
		int x, y;

		// move up
		for (y=1; y<=h; y++)
			for (x=0; x<w; x++) {
				u16 t = vid_drv->getchar(x, y);
				vid_drv->putchar(t, x, y - 1);
			}

		// clear last line
		for (x=0; x<w; x++)
			vid_drv->putchar((7 << 8) | ' ', x, h - 1);

		cursor_y = h - 1;
	}

	set_cursor_pos(cursor_x, cursor_y);
}

void clear_screen(void)
{
	u32 w, h;
	vid_drv->get_resolution(&w, &h);

	int x, y;
	for (y=0; y<h; y++)
		for (x=0; x<w; x++)
			vid_drv->putchar((7 << 8) | ' ', x, y);
	
	set_cursor_pos(0, 0);
}

void get_cursor_pos(u32 * x, u32 * y)
{
	vid_drv->get_cursor_pos(x, y);
}

void set_cursor_pos(u32 x, u32 y)
{
	vid_drv->set_cursor_pos(x, y);
}

