
#include "app.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "math.h"
#include "timer.h"

APP_INTERFACE(debug);

static void pf(float f);

u8 main(const char * cmdline)
{
	if (startswith(cmdline, "--help")) {
		printf("\n\e%cdebug\e%c\n", H|R|G|B, R|G|B);
		printf("\tRun the debugging code for lanos.\n\n");
		return 0;
	}

	void * a, * b, * c;
	a = malloc(1<<20);
	b = malloc(100<<10);
	printf("%X\t%X\n", a, b);
	free(a);
	a = malloc(100<<10);
	c = malloc(100<<10);
	printf("%X\t%x\n", a, c);
	free(a);
	free(b);
	free(c);

	float i;
	for (i=-2*PI; i<2*PI; i+=0.1) {
		//pf(sin(i));
		printf("%g\n", sin(i));
		wait(100);
	}

	return 0;
}

void pf(float f)
{
	if (f < 0) {
		printf("-");
		f = -f;
	}
	s32 s = f;
	printf("%d.", s);
	f -= s;

	if (f == 0.0f) {
		printf("0");
		return;
	}

	while (f != 0.0f) {
		f *= 10;
		s  = f;
		f -= s;
		printf("%d", s);
	}
}

