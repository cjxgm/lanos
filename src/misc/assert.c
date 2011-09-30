
#include "assert.h"
#include "printf.h"

void assert_handler(const char * file,
					int          line,
					const char * err)
{
	asm volatile ("cli");
	printf("\e%cAssertion Failure: "
			"\e%c%s: \e%c%u\n"
			"\t\e%c%s\n",
			H|R|G|B,
			H|R|G, file, H|R|B, line,
			H|R, err);
	while (1);
}

