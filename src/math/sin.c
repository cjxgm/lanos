
#include "math.h"
#include "stdio.h"

static double _fac(double x);
static double _pow(double x, double y);

float sin(float x)
{
	while (x < -PI) x += 2*PI;
	while (x >= PI) x -= 2*PI;

	return x - _pow(x, 3) / _fac(3)
			 + _pow(x, 5) / _fac(5)
			 - _pow(x, 7) / _fac(7);
}

static double _fac(double x)
{
	double r = 1;
	while (x) r *= x--;
	return r;
}

static double _pow(double x, double y)
{
	double r = 1;
	while (y--) r *= x;
	return r;
}
