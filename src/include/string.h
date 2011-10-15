
#ifndef __STRING__
#define __STRING__

#include "common.h"

u32 startswith(const char * dst, const char * src);
s8  strcmp    (const char * a,   const char * b);
#define streq(a, b)		(!strcmp(a, b))

#endif

