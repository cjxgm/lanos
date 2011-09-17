
#include "common.h"
#include "monitor.h"
#include "printf.h"
#include "desc_table.h"
#include "timer.h"
#include "keyboard.h"

struct mboot_info
{
	u32	flags;
	u32	low_mem;
	u32	high_mem;
};

int main(struct mboot_info * mb_header)
{
	monitor_clear();
	monitor_write("\n=== kernel initializing begins ===\n\n");

	printf("\e%cWelcome to LANOS!\e%c\n\n", H|G, R|G|B);

	printf("\e%cmultiboot info: \e%c\n", H|B, R|G|B);
	printf("flags	:	\e%c%bh\e%c (%Xh)\n",
						H|R|G|B, mb_header->flags,
						R|G|B  , mb_header->flags);
	printf("low  mem:	\e%c%Xh\e%c (%u)\n",
						H|R|G|B, mb_header->low_mem,
						R|G|B,   mb_header->low_mem);
	printf("high mem:	\e%c%Xh\e%c (%u)\n",
						H|R|G|B, mb_header->high_mem,
						R|G|B,   mb_header->high_mem);

#define INIT(X, ...) \
	printf("\e%cinitializing " #X "...\t", H|R|G|B); \
	init_##X(__VA_ARGS__);\
	printf("\e%c[done]\n", H|G);

	printf("\n");
	INIT(gdt);
	INIT(idt);
	INIT(timer, 50);
	INIT(keyboard);
#undef INIT

	monitor_write("\n\e\x07===  kernel initializing ends  ===\n");
    return 0;
}

