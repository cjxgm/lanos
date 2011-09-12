
#include "monitor.h"
#include "common.h"

static void move_cursor(void);
static void scroll(void);

static u16 * const video_memory = (u16 *)0xb8000;
static u8 cursor_x = 0;
static u8 cursor_y = 0;

static u8 out_mode = 0;

// writes a single character out to the screen.
void monitor_put(char c)
{
	static u16 attribute = 7 << 8; // 7: white text with black background.

	// You can change attribute by using "\e\x??"
	if (out_mode == 1) {
		attribute = c << 8;
		out_mode = 0;
		return;
	}
	if (c == '\033') {	// \033 = \e
		out_mode = 1;
		return;
	}

	// handle a backspace, by moving the cursor back one space
	if (c == 0x08 && cursor_x)
		cursor_x--;

	// handle a tab by increasing the cursor's X, but only to a point
	// where it is divisible by 4.
	else if (c == 0x09)
		cursor_x = (cursor_x+4) & ~(4-1);

	// handle carriage return
	else if (c == '\r')
		cursor_x = 0;

	// handle newline by moving cursor back to left and increasing the row
	else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	}
	// handle any other printable character.
	else if(c >= ' ') {
		video_memory[cursor_y * 80 + cursor_x] = c | attribute;
		cursor_x++;
	}

	// check if we need to insert a new line as we have reached
	// the end of the screen.
	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y ++;
	}

	// scroll the screen if needed.
	scroll();
	// move the hardware cursor.
	move_cursor();
}

// clear the screen, by copying lots of spaces to the framebuffer.
void monitor_clear(void)
{
	// make an attribute byte for the default colours
	u8  attribute = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16 blank     = 0x20 /* space */   | (attribute << 8);

	int i;
	for (i=0; i<80*25; i++)
		video_memory[i] = blank;

	// Move the hardware cursor back to the start.
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void monitor_write(const char * str)
{
	while (*str)
		monitor_put(*str++);
}

// updates the hardware cursor.
void move_cursor(void)
{
	// the screen is 80 characters wide, yet.
	u16 cursor_pos = cursor_y * 80 + cursor_x;

	// tell the VGA board we are setting the high cursor byte.
	outb(0x3D4, 14);
	// Send the high cursor byte.
	outb(0x3D5, cursor_pos >> 8);

	// tell the VGA board we are setting the low cursor byte.
	outb(0x3D4, 15);
	// Send the low cursor byte.
	outb(0x3D5, cursor_pos);
}

// scroll the text on the screen up by one line.
void scroll(void)
{
	// get a space character with the default colour attributes.
	u8  attribute = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16 blank     = 0x20 /* space */   | (attribute << 8);

	// row 25 is the end, this means we need to scroll up
	if(cursor_y >= 25)
	{
		// move the current text chunk that makes up the screen
		// back in the buffer by a line
		int i;
		for (i=0; i<24*80; i++)
			video_memory[i] = video_memory[i + 80];

		// the last line should now be blank.
		// do this by writing 80 spaces to it.
		for (i=24*80; i<25*80; i++)
			video_memory[i] = blank;

		// The cursor should now be on the last line.
		cursor_y = 24;
	}
}
