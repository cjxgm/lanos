
#include "video.h"
#include "common.h"

static void dispi_set_bpp   (u16 bpp   );
static void dispi_set_xres  (u16 xres  );
static void dispi_set_yres  (u16 xres  );
static void dispi_set_bank  (u16 bank  );
static void dispi_set_enable(u16 enable);

// FIXME: this may not work on a real machine!!!
static u32 * const video_mem = (u32*)0xe0000000;

void init_video(void)
{
	dispi_set_enable(VBE_DISPI_DISABLED);
	dispi_set_bpp(24);
	dispi_set_xres(1024);
	dispi_set_yres(768);
	dispi_set_bank(0);
	dispi_set_enable(VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
	//vga_compat_setup();
}

void draw_test(void)
{
	int x, y;
	for (y=0; y<400; y++)
		for (x=0; x<400; x++)
			video_mem[y*1024+x] = (((x * 255 / 400) << 16) & 0xFF)
								| (((y * 255 / 400) << 8 ) & 0xFF);
}

void dispi_set_bpp(u16 bpp)
{
	outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_BPP);
	outw(VBE_DISPI_IOPORT_DATA , bpp);
}

void dispi_set_xres(u16 xres)
{
	outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_XRES);
	outw(VBE_DISPI_IOPORT_DATA , xres);
}

void dispi_set_yres(u16 yres)
{
	outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_YRES);
	outw(VBE_DISPI_IOPORT_DATA , yres);
}

void dispi_set_bank(u16 bank)
{
	outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_BANK);
	outw(VBE_DISPI_IOPORT_DATA , bank);
}

void dispi_set_enable(u16 enable)
{
	outw(VBE_DISPI_IOPORT_INDEX, VBE_DISPI_INDEX_ENABLE);
	outw(VBE_DISPI_IOPORT_DATA , enable);
}

