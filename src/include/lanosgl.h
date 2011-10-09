
#ifndef __LANOSGL__
#define __LANOSGL__

#include "common.h"

/** high level API **/

u8 gl_init(u32 x, u32 y, u32 w, u32 h);
void gl_free(void);
void gl_view(u32 x, u32 y, u32 w, u32 h);
void gl_clear(void);
void gl_swap(void);

/** low level API **/

void gl_plot(float x, float y, float z, u32 color);
u32  gl_mix_color(u32 c1, u32 c2);
void gl_line(float x0, float y0, float z0,
			 float x1, float y1, float z1,
			 u32 color1, u32 color2);

#endif

