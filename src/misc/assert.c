
#include "assert.h"
#include "printf.h"

void assert_handler(const char * err)
{
	printf("\e%c>>> KERNEL PANIC <<<\e%c Assertion Error:\e%c %s\n",
			BG(H|R), H|R|G|B, R|G|B, err);
	while (1);
}

