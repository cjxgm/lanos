
#include "app.h"
#include "stdio.h"
#include "string.h"

extern struct app app_logo;
extern struct app app_lush;
extern struct app app_help;
extern struct app app_cls;

struct app * app[] = {
	&app_logo,
	&app_lush,
	&app_help,
	&app_cls,
};

struct app * get_app(u32 id)
{
	if (id >= sizeof(app)/sizeof(app[0])) return NULL;
	return app[id];
}

u8 run_app(const char * name, const char * cmdline)
{
	struct app * a;
	int i = 0;
	while ((a = get_app(i++)))
		if (streq(a->name, name))
			return a->run(cmdline);
	printf("\e%capp not found: \e%c%s\e%c\n", H|R, H|R|G, name, R|G|B);
	return 0;
}
