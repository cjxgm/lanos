
#include "printf.h"
#include "monitor.h"
#include "common.h"

static void print_hex_32(u32 data);
static void print_hex_8(u8 data);
static void print_dec_u32(u32 data);
static void print_dec_s32(s32 data);

void printf(const char * fmt, ...)
{
	const void * p = (void *)&fmt + 4;
	char ch;
	char * tmp;

	while ((ch = *fmt++)) {
		switch (ch) {
			case '%':
				if ((ch = *fmt++) == 0)
					goto _end;
				switch (ch) {
					case 'X':	// I'm lazy...
					case 'x':
					case 'P':
					case 'p':
						print_hex_32(*(u32 *)p);
						p += 4;
						break;
					case 'D':	// I'm lazy...
					case 'd':
						print_dec_s32(*(s32 *)p);
						p += 4;
						break;
					case 'U':	// I'm lazy...
					case 'u':
						print_dec_u32(*(u32 *)p);
						p += 4;
						break;
					case 'C':	// I'm lazy...
					case 'c':
						monitor_put(*(char *)p);
						p += 4;
						break;
					case 'S':	// I'm lazy...
					case 's':
						tmp = *(char **)p;
						while (*tmp)
							monitor_put(*tmp++);
						p += 4;
						break;
					default:
						monitor_put(ch);
				}
				break;
			default:
				monitor_put(ch);
		}
	}
_end:
	return;
}

void print_hex_32(u32 data)
{
	int i;
	for (i=32-8; i>=0; i-=8)
		print_hex_8(data >> i);
}

void print_hex_8(u8 data)
{
	static const char hex_digits[] = "0123456789abcdef";

	monitor_put(hex_digits[data >> 4]);
	monitor_put(hex_digits[data & 0xF]);
}

void print_dec_u32(u32 data)
{
	if (!data) {
		monitor_put('0');
		return;
	}

	char buf[12];
	char * p = buf;

	buf[0] = buf[11] = 0;

	while (data) {
		*p++ = (data % 10) + '0';
		data /= 10;
	}

	while (*--p)
		monitor_put(*p);
}

void print_dec_s32(s32 data)
{
	if (data < 0) {
		monitor_put('-');
		data = -data;
	}
	print_dec_u32(data);
}

