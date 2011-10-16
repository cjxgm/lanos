
#include "malloc.h"

/* TODO: give it a better algorithm */

static void * mem = (void *)0x1000000;

void * malloc(u32 size)
{
	void * p = mem;
	mem += size;
	return p;
}

void * calloc(u32 size, u32 count)
{
	size *= count;
	u8 * p = malloc(size);
	int i;
	for (i=0; i<size; i++)
		p[i] = 0;
	return p;
}

void free(void * mem_ptr)
{
	// do nothing for this kind of algorithm.
}
