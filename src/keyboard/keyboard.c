
#include "keyboard.h"
#include "printf.h"
#include "isr.h"
#include "assert.h"
#include "video.h"

static void keyboard_handler(regs_t regs);

static u8 shift_pressed = 0;
static u8 caps_locked   = 0;
static u8 key_pressed[0x80] = {0};

static u8 keymap[0x80 * 2] = {
/* !shift  shift       what 	scan code(hex) */
	0,		0,		// none		 0
	27,		27,		// esc		 1
	'1',	'!',	//			 2
	'2',	'@',	//			 3
	'3',	'#',	//			 4
	'4',	'$', 	//			 5
	'5',	'%', 	//			 6
	'6',	'^', 	//			 7
	'7',	'&', 	//			 8
	'8',	'*', 	//			 9
	'9',	'(', 	//			 A
	'0',	')', 	//			 B
	'-',	'_', 	//			 C
	'=',	'+', 	//			 D
	'\b',	'\b',	//			 E
	'\t',	'\t',	//			 F
	'q',	'Q',	//			10
	'w',	'W', 	//			11
	'e',	'E', 	//			12
	'r',	'R', 	//			13
	't',	'T', 	//			14
	'y',	'Y', 	//			15
	'u',	'U', 	//			16
	'i',	'I', 	//			17
	'o',	'O', 	//			18
	'p',	'P', 	//			19
	'[',	'{', 	//			1A
	']',	'}', 	//			1B
	'\n',	'\n',	//			1C
	0,		0,		// CTRL_L	1D
	'a',	'A',
	's',	'S',
	'd',	'D',
	'f',	'F',
	'g',	'G',
	'h',	'H',
	'j',	'J',
	'k',	'K',
	'l',	'L',
	';',	':',
	'\'',	'"',
	'`',	'~',
	0,		0,		// SHIFT_L
	'\\',	'|',
	'z',	'Z',
	'x',	'X',
	'c',	'C',
	'v',	'V',
	'b',	'B',
	'n',	'N',
	'm',	'M',
	',',	'<',
	'.',	'>',
	'/',	'?',
	0,		0,		// SHIFT_R
	'*',	'*',
	0,		0,		// ALT_L
	' ',	' ',
	0,		0,		// CAPS_LOCK
};

void init_keyboard(void)
{
	register_irq_handler(IRQ_KEYBOARD, &keyboard_handler);
}

u8 inkey(u8 key)
{
	assert(key < 0x80);
	return key_pressed[key];
}

void keyboard_handler(regs_t regs)
{
	u8 key = inb(0x60);

	// when press ESC, hang up the OS
	assert(key != 0x01 && "system hangs up");

	if (key == 0x3B) {	// F1
		init_video();
	}

	if (key == 0xE0 || key == 0xE1)
		return;		// can not proccess this now

	u8 key_down = (key & 0x80 ? 0 : 1); // DO NOT USE 'key & 0x80' INSTEAD!
	key &= 0x7F;

	if (key == 0x2A || key == 0x36)		// shift
		shift_pressed = key_down;
	else if (key_down)
		printf("%c", keymap[key*2 + shift_pressed]);

	key_pressed[key] = key_down;
}

