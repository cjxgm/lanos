
#include "malloc.h"
#include "stdio.h"
#include "monitor.h"
#include "assert.h"

static struct alloc_info * alloc_info;
static void * alloc_start_addr;
static u32    max_block_cnt;

void init_malloc(u32 start, u32 size)
{
	alloc_info = (void *)start;
	max_block_cnt = size / (512 + sizeof(struct alloc_info));

	struct alloc_info * p = alloc_info;
	u32 i;
	for (i=0; i<max_block_cnt; i++) {
		p->used = 0;
		p = p->next = p + 1;
	}
	(p - 1)->next = NULL;
	alloc_start_addr = p;
}

void * malloc(u32 size)
{
	if (!size) return NULL;

	u32 b = (size + 512 - 1) >> 9;	// block_cnt
	assert(b < max_block_cnt && "No such large memory available!");

	struct alloc_info * p = alloc_info;
	struct alloc_info * a = NULL;
	u32 cnt = 0;

	for (; p; p=p->next) {
		if (!p->used) {
			if (!a) a = p;
			cnt++;
			if (cnt == b) {	// found enough memory!
				a->next = p->next;
				a->used = 1;
				return ((a - alloc_info) << 9) + alloc_start_addr;
			}
		}
		else {
			a = NULL;
			cnt = 0;
		}
	}

	return NULL;
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

void free(void * a)
{
	assert(a >= alloc_start_addr && "Where did you get the address?");

	a = (void *)(a - alloc_start_addr);
	assert((u32)a < max_block_cnt<<9 && "Where did you get the address?");

	struct alloc_info * p = &alloc_info[(u32)a>>9];
	assert(p->used && "It's a freed memory, why do you free it again?");

	p->next = p + 1;
	p->used = 0;
}
