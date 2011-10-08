/* KeyBoard QUEUE */

#include "common.h"

#define KB_QUEUE_SIZE	32

static u8   kb_queue[KB_QUEUE_SIZE];
static u8 * head = kb_queue;
static u8 * tail = kb_queue;
static u8   cnt  = 0;

void kb_queue_append(u8 key)
{
	if (!key) return;
	if (cnt == KB_QUEUE_SIZE) return;

	*tail++ = key;
	if (tail == kb_queue + KB_QUEUE_SIZE)
		tail = kb_queue;
	cnt++;
}

void kb_queue_prepend(u8 key)
{
	if (!key) return;
	if (cnt == KB_QUEUE_SIZE) return;

	if (--head < kb_queue)
		head = kb_queue + KB_QUEUE_SIZE - 1;
	*head = key;
	cnt++;
}

u8 kb_queue_pop(void)
{
	while (!cnt);	// wait until kb_queue not empty

	u8 ch = *head++;
	if (head == kb_queue + KB_QUEUE_SIZE)
		head = kb_queue;
	cnt--;

	return ch;
}

