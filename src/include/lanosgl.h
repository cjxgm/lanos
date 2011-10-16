
#ifndef __LANOSGL__
#define __LANOSGL__

#include "common.h"

/** high level API **/

/******** in gl.c ********/

// draw_what
#define GL_LINES		0
#define GL_LINE_STRIP	1
#define GL_LINE_LOOP	2

u8 gl_init(u32 x, u32 y, u32 w, u32 h);
void gl_free(void);
void gl_view(u32 x, u32 y, u32 w, u32 h);
void gl_clear(void);
void gl_swap(void);
void gl_persp(float persp_param, float aspect_ratio);

void gl_begin(u32 draw_what);
void gl_end(void);
void gl_color(float r, float g, float b, float a);
#define gl_color3(r, g, b)	gl_color(r, g, b, 1.0f)
void gl_vert(float x, float y, float z);
#define gl_vert2(x, y) gl_vert(x, y, 0.0f)

// map Value ranged [SrcFrom, SrcTo] to [DstFrom, DstTo] linearly.
#define gl_map(v, sf, st, df, dt) \
	(((float)(v)-(float)(sf)) \
		* ((float)(dt)-(float)(df)) \
		/ ((float)(st)-(float)(sf)) \
		+ (float)(df))

/******** in matrix.c ********/
typedef float matrix_t[16];

matrix_t * gl_mult_matrix(matrix_t * dst, matrix_t * src);

/** low level API **/

void gl_plot(float x, float y, float z, u32 color);
u32  gl_mix_color(u32 c1, u32 c2);
void gl_line(float x0, float y0, float z0,
			 float x1, float y1, float z1,
			 u32 color1, u32 color2);

#endif

