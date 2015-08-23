/* modf function */
#include "xmath.h"

double (modf)(double x, double *pint)
	{	/* compute modf(x, &intpart) */
	*pint = x;
	switch (_Dint(pint, 0))
		{	/* test for special codes */
	case NAN:
		return (x);
	case INF:
	case 0:
		return (0.0);
	default:	/* finite */
		return (x - *pint);
		}
	}
