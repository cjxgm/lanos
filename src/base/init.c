
#include "common.h"
#include "monitor.h"
#include "stdio.h"
#include "desc_table.h"
#include "timer.h"
#include "keyboard.h"
#include "app.h"
#include "version.h"

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

int init(struct mboot_info * mb_info)
{
	init_gdt();
	init_idt();
	init_timer();
	init_keyboard();
	init_monitor();

	clear_screen();
	printf("\n\n\e%cWelcome to lanos %s\n"
		   "\e%cbuilt on %s at %s\e%c\n\n",
		   H|G, LANOS_VERSION, H|G|B, __DATE__, __TIME__, R|G|B);

	app_lush();

    return 0;
}

