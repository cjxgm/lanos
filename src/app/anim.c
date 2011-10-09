
#include "app.h"
#include "lanosgl.h"
#include "monitor.h"
#include "keyboard.h"
#include "timer.h"
#include "assert.h"
#include "math.h"

u8 app_anim(void)
{
	gl_init(1, 10, 40, 12);
	gl_view(2, 0, 30, 10);

	float t = 0;

	while (!inkey(0x01)) {	// 0x01 --> ESC
		gl_clear();
		//gl_plot(0, 0, 0, 0xFFFFFFFF);
		//gl_plot(4, 4, 10, 0xC00000FF);  // test alpha
		gl_line(0, 0, 0, 1, t, 10, 0xFFFFFFFF, 0xFFFF00FF);
		gl_swap();

		t += 0.1;
		if (t > 20) t = 0;

		// wait
		u32 t = get_ticks();
		while ((get_ticks() - t) * 1000 / TICKS_PER_SEC < 10);
	}

	gl_free();
	clear_screen();
	return 0;
}
