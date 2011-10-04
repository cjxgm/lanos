
#include "math.h"

// I got the algorithm from wikipedia.
// It's amazing fast!
float sqrt(float x)
{
	union
	{
		float x;
		int i;
	} u;

	u.x = x;
	u.i = 0x5f3759df - (u.i >> 1);
	x = u.x * (1.5f - 0.5f * x * u.x * u.x);

	return 1.0f / x;
}

