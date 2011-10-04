
#include "video_driver.h"

extern struct video_driver video_driver_normal;
extern struct video_driver video_driver_vesa;

struct video_driver * drvs[] = {
	&video_driver_normal,		// this must be the first one!
	&video_driver_vesa,
};

struct video_driver * get_video_driver(u32 id)
{
	if (id >= sizeof(drvs)/sizeof(drvs[0]))
		return NULL;
	return drvs[id];
}

