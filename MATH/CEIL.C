/* ceil function */
#include "xmath.h"

double (ceil)(double x)
	{	/* compute ceil(x) */
	double y = x;

	return (_Dint(&y, 0) < 0 && 0.0 < x ? y + 1.0 : y);
	}
