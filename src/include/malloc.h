
#ifndef __MALLOC__
#define __MALLOC__

#include "common.h"

void * malloc(u32 size);
void * calloc(u32 size, u32 count);
void   free(void * mem_ptr);

#endif

