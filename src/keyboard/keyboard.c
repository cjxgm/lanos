
#include "keyboard.h"
#include "stdio.h"
#include "isr.h"
#include "assert.h"

// in kb_queue.c
void kb_queue_append (u8 key);
void kb_queue_prepend(u8 key);
u8   kb_queue_pop    (void  );

static void keyboard_handler(regs_t regs);

static u8 shift_pressed = 0;
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

	// clear keyboard buffer
	while (inb(0x64) & 2)
		inb(0x60);
}

u8 inkey(u8 key)
{
	assert(key < 0x80);
	return key_pressed[key];
}

u8 getchar(void)
{
	return kb_queue_pop();
}

void ungetchar(u8 ch)
{
	kb_queue_prepend(ch);
}

void keyboard_handler(regs_t regs)
{
	u8 key = inb(0x60);

	if (key == 0xE0 || key == 0xE1)
		return;		// can not proccess this now

	u8 key_down = (key & 0x80 ? 0 : 1); // DO NOT USE 'key & 0x80' INSTEAD!
	key &= 0x7F;

	if (key == 0x2A || key == 0x36)		// shift
		shift_pressed = key_down;
	else if (key_down)
		kb_queue_append(keymap[key*2 + shift_pressed]);

	key_pressed[key] = key_down;
}

