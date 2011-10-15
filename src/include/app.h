
#ifndef __APP__
#define __APP__

#include "common.h"

struct app
{
	const char * name;
	u8 (*run)(const char * cmdline);
};

#define APP_INTERFACE(NAME) \
	static u8 main(const char * cmdline); \
	struct app app_ ## NAME = { \
		.name = #NAME, \
		.run  = &main \
	};

struct app * get_app(u32 id);
u8 run_app(const char * name, const char * cmdline);

#endif

