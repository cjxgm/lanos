
#include "common.h"
#include "monitor.h"
#include "printf.h"
#include "desc_table.h"

// colors
// usage: printf("\e%c", R|G|B);
#define H			(1<<3)
#define R			(1<<2)
#define G			(1<<1)
#define B			(1<<0)
#define BG(CLR)		((CLR) << 4)

struct mboot_info
{
	u32	flags;
	u32	low_mem;
	u32	high_mem;
};

int main(struct mboot_info * mb_header)
{
	monitor_clear();
	monitor_write("=== kernel main begins ===\n\n");

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

	printf("\n\e%cinitializing GDT... ", H|R|G|B);
	init_gdt();
	printf("\e%c[done]\n", H|R);

	printf("\n\e%cinitializing IDT... ", H|R|G|B);
	init_idt();
	printf("\e%c[done]\n", H|G);

	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

	monitor_write("\e\x07\n\n===  kernel main ends  ===\n");
    return 0;
}

