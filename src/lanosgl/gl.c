
#include "lanosgl.h"
#include "monitor.h"
#include "malloc.h"
#include "math.h"
#include "assert.h"
#include "stdio.h"

static u32 win_x;
static u32 win_y;
static u32 win_w;
static u32 win_h;

static u32 view_x;
static u32 view_y;
static u32 view_w;
static u32 view_h;

static u32   * buf_color = NULL;
static float * buf_depth = NULL;

/** high level API **/

u8 gl_init(u32 x, u32 y, u32 w, u32 h)
{
	u32 sw, sh;
	get_pixel_resolution(&sw, &sh);
	assert(x+w <= sw && y+h <= sh);

	if (!(buf_color = malloc(w * h * sizeof(u32))))
		return 1;
	if (!(buf_depth = malloc(w * h * sizeof(float))))
		return 1;

	win_x = x;
	win_y = y;
	win_w = w;
	win_h = h;

	return 0;
}

void gl_free(void)
{
	free(buf_color);
	free(buf_depth);
}

void gl_view(u32 x, u32 y, u32 w, u32 h)
{
	assert(w <= win_w && h <= win_h && x < w && y < h);

	view_x = x;
	view_y = y;
	view_w = w;
	view_h = h;
}

void gl_clear(void)
{
	int i;
	for (i=0; i<win_w*win_h; i++) {
		buf_color[i] = 0;
		buf_depth[i] = 1000.0f;
	}
}

void gl_swap(void)
{
	u32 w, h;
	get_pixel_resolution(&w, &h);

	u32 x, y;
	for (y=0; y<win_h; y++)
		for (x=0; x<win_w; x++)
			putpixel(x+win_x, h-y-win_y-1, buf_color[y*win_w+x]);
}


/** low level API **/

void gl_plot(float x, float y, float z, u32 color)
{
	if (x < 0 || y < 0 || x >= view_w || y >= view_h)
		return;

	u32 pos = (y + view_y) * win_w + x + view_x;
	if (z < buf_depth[pos]) {
		buf_depth[pos] = z;
		buf_color[pos] = gl_mix_color(buf_color[pos], color);
	}
}

// return the result of c2 alpha over c1
u32 gl_mix_color(u32 c1, u32 c2)
{
	u8 clr1[4];
	u8 clr2[4];
	u8 clr3[4];
	
	*(u32 *)clr1 = c1;
	*(u32 *)clr2 = c2;

	clr3[0] = clr1[0]*(0xFF-clr2[3])/0xFF + clr2[0]*clr2[3]/0xFF;
	clr3[1] = clr1[1]*(0xFF-clr2[3])/0xFF + clr2[1]*clr2[3]/0xFF;
	clr3[2] = clr1[2]*(0xFF-clr2[3])/0xFF + clr2[2]*clr2[3]/0xFF;
	clr3[3] = 0xFF;

	return *(u32 *)clr3;
}

// X and Y must be transformed ones, and the Z is for depth buffer only.
void gl_line(float x0, float y0, float z0,
			 float x1, float y1, float z1,
			 u32 color1, u32 color2)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float d  = sqrt(dx*dx + dy*dy);
	float c  = dx / d;
	float s  = dy / d;

	int i;
	for (i=0; i<=d; i++) {
		float x = i*c + x0;
		float y = i*s + y0;
		float z = (z1 - z0) * i / d + z0;
		if (x<0 || y<0) continue;
		u32 color = gl_mix_color(color1,
								 (color2 & 0x00FFFFFF) | ((u8)(0xFF * i / d)<<24));
		gl_plot(x, y, z, color);
		//		printf("%X\n", color);
	}
}
