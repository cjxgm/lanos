
#include "stdio.h"
#include "monitor.h"
#include "common.h"
#include "assert.h"

/********** printf **********/

static void print_bin_32(u32 data);
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
					case 'B':	// I'm lazy...
					case 'b':
						print_bin_32(*(u32 *)p);
						p += 4;
						break;
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

void print_bin_32(u32 data)
{
	int i;
	for (i=31; i>=0; i--)
		monitor_put('0' + ((data >> i) & 1));
}

void print_hex_32(u32 data)
{
	int i;
	for (i=32-8; i>=0; i-=8)
		print_hex_8(data >> i);
}

void print_hex_8(u8 data)
{
	static const char hex_digits[] = "0123456789ABCDEF";

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

/********** scanf **********/

void scanf(const char * fmt, ...)
{
	const void * p = (void *)&fmt + 4;
	char ch;
	char tmp;
	char * s;

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
						assert(!"TODO");
						p += 4;
						break;
					case 'D':	// I'm lazy...
					case 'd':
						assert(!"TODO");
						p += 4;
						break;
					case 'U':	// I'm lazy...
					case 'u':
						assert(!"TODO");
						p += 4;
						break;
					case 'C':	// I'm lazy...
					case 'c':
						tmp = getchar();
						if (tmp != '\b') monitor_put(tmp);
						**(char **)p = tmp;
						p += 4;
						break;
					case 'S':	// I'm lazy...
					case 's':
						s = *(char **)p;

						while ((tmp = getchar()) == ' ' || tmp == '\n')
							monitor_put(tmp);
						ungetchar(tmp);

						while ((tmp = getchar()) != ' ' && tmp != '\n') {
							if (tmp == '\b') continue;
							monitor_put(tmp);
							*s++ = tmp;
						}
						*s = 0;

						p += 4;
						break;
					default:
						assert(!"What did you fucking do to scanf??");
				}
				break;
			default:
				assert(!"What did you fucking do to scanf??");
		}
	}
_end:
	return;
}

/********** readline **********/

// CAUTION: <size> does NOT counts the terminal zero!
void readline(char * buf, u32 size)
{
	char * p = buf;
	while (p - buf < size) {
		char ch = getchar();
		if (ch == '\t') continue;	// ignore tab, or may cause problem
		if (ch == '\b') {
			if (p == buf) continue;
			printf("\b \b");
			p--;
		}
		else {
			monitor_put(ch);
			if (ch == '\n') break;
			*p++ = ch;
		}
	}
	*p = 0;
}

