/* cosh function */
#include "xmath.h"

double (cosh)(double x)
	{	/* compute cosh(x) */
	switch (_Dtest(&x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		errno = ERANGE;
		return (_Inf._D);
	case 0:
		return (1.0);
	default:	/* finite */
		if (x < 0.0)
			x = -x;
		if (0 <= _Exp(&x, -1))
			errno = ERANGE;	/* x large */
		else if (x < _Xbig._D)
			x += 0.25 / x;
		return (x);
		}
	}
