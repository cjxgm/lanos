
#include "string.h"

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

