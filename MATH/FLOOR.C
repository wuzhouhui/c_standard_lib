/* floor function */
#include "xmath.h"

double (floor)(double x)
	{	/* compute floor(x) */
	double y = x;

	return (_Dint(&y, 0) < 0 && x < 0.0 ? y - 1.0 : y);
	}
