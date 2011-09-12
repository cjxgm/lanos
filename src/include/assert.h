
#ifndef __ASSERT__
#define __ASSERT__

#define assert(X) if (!(X)) assert_handler(#X)
void assert_handler(const char * err);

#endif

