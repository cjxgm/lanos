
#ifndef __ASSERT__
#define __ASSERT__

#define assert(X) do { \
	if (!(X)) assert_handler(__FILE__, __LINE__, #X); \
} while (0)

void assert_handler(const char * file,
					int          line,
					const char * err);

#ifdef __DEBUG__
#define __(...)		__VA_ARGS__;
#else
#define __(...)
#endif

#endif

