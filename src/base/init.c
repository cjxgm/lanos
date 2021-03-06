
#include "common.h"
#include "boot.h"
#include "monitor.h"
#include "stdio.h"
#include "desc_table.h"
#include "timer.h"
#include "keyboard.h"
#include "malloc.h"
#include "app.h"
#include "version.h"

struct mboot_info
{
	u32	flags;
	u32	lower;
	u32	higher;
	u32 reserved[14];
	u32 vbe_control_info;
	u32 vbe_mode_info;
	u32 vbe_mode;
};

int init(struct mboot_info * mbi, u32 kstart, u32 kend)
{
	if (!(mbi->flags & 1)) boot_fail();
	init_gdt();
	init_idt();
	init_timer();
	init_keyboard();
	init_monitor();
	init_malloc(kend, (mbi->higher<<10) - kend);

	run_app("logo", "");

	clear_screen();
	printf("\n\e%cWelcome to Lanos %s!\n"
		   "\e%cbuilt on %s at %s\n\n",
		   H|G, LANOS_VERSION, H|G|B, __DATE__, __TIME__);

	printf("\e%c"
			"memory: %umb (%ukb-%umb)\n"
			"kernel: %ukb (%ukb-%ukb)\n\n", H|R|G,
			(mbi->higher - mbi->lower) >> 10,
			mbi->lower, mbi->higher >> 10,
			(kend - kstart)>>10, kstart>>10, kend>>10);

	printf("\e%ctype `\e%chelp\e%c' to get some help.\n",
			R|G, H|B, R|G);

	while (1) {
		printf("\n");
		run_app("lush", "");

		printf("\n\e%cYou exited the fucking shell!\n", H|R);
		wait(2000);

		printf("Don't you want to controll the sucking OS!??\n");
		wait(2500);

		printf("\e%cI hope you exited it by accident.\n", H|R|B);
		wait(2000);

		printf("\e%cI'm restarting it...\n", H|R|G);
		wait(2000);
	}

    return 0;
}

