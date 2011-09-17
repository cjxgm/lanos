
#ifndef __ASSERT__
#define __ASSERT__

#define assert(X) if (!(X)) assert_handler(__FILE__, __LINE__, #X)
void assert_handler(const char * file,
					int          line,
					const char * err);

#endif

