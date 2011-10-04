
#include "common.h"
#include "monitor.h"
#include "stdio.h"
#include "desc_table.h"
#include "timer.h"
#include "keyboard.h"
#include "app.h"

struct mboot_info
{
	u32	flags;
	u32	low_mem;
	u32	high_mem;
	u32 reserved[14];
	u32 vbe_control_info;
	u32 vbe_mode_info;
	u32 vbe_mode;
};

int main(struct mboot_info * mb_info)
{
	select_video_driver();
	clear_screen();

	printf("\n\n\e%cWelcome to LANOS!\n"
		   "\e%cbuilt on %s at %s\e%c\n\n",
		   H|G, H|G|B, __DATE__, __TIME__, R|G|B);

	printf("\e%cmultiboot info: \e%c\n", H|B, R|G|B);
	printf("flags	:	\e%c%bh\e%c (%Xh)\n",
						H|R|G|B, mb_info->flags,
						R|G|B  , mb_info->flags);
	printf("low  mem:	\e%c%Xh\e%c (%u)\n",
						H|R|G|B, mb_info->low_mem,
						R|G|B,   mb_info->low_mem);
	printf("high mem:	\e%c%Xh\e%c (%u)\n",
						H|R|G|B, mb_info->high_mem,
						R|G|B,   mb_info->high_mem);
	printf("vbe info:	\e%c%d %d %d\e%c\n",
						H|R|G|B, mb_info->vbe_control_info,
								 mb_info->vbe_mode_info,
								 mb_info->vbe_mode,
						R|G|B);

#define INIT(X, ...) \
	printf("\e%cinitializing " #X "...\t", H|R|G|B); \
	init_##X(__VA_ARGS__);\
	printf("\e%c[done]\n", H|G);

	printf("\n");
	INIT(gdt);
	INIT(idt);
	INIT(timer);
	INIT(keyboard);
#undef INIT
	printf("\n\e%c========================================"
			"========================================\n", H|G|B);

	app_lush();
    return 0;
}

