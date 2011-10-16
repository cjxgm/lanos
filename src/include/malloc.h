
#ifndef __MALLOC__
#define __MALLOC__

#include "common.h"

#define NULL ((void *)0)

struct alloc_info
{
	struct alloc_info * next;
	u32 used;
};

void   init_malloc(u32 start, u32 size);

void * malloc(u32 size);
void * calloc(u32 size, u32 count);
void   free(void * mem_ptr);

#endif

