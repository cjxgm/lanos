
#include "string.h"
#include "stdio.h"

// is dst starts with src ?
// if so, return the matched size.
// if not, return 0
u32 startswith(const char * dst, const char * src)
{
	const char * p = dst;
	while (*p++ == *src)
		if (*src++ == 0) return p - dst - 1;
	if (*--p == ' ')
		return p - dst;
	return 0;
}

s8 strcmp(const char * a, const char * b)
{
	while (1) {
		if (*a < *b) return -1;
		if (*a > *b) return +1;
		if (!*a && !*b) return 0;
		a++;
		b++;
	}
}

