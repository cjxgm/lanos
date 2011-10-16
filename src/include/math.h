
#ifndef __MATH__
#define __MATH__

#include "common.h"

// all the math functions must be declared here.

#define PI 3.1415927f

float sqrt(float x);
float sin(float a);
#define cos(a)	sin((a) + PI/2)
#define tan(a)	(sin(a)/cos(a))

#endif

