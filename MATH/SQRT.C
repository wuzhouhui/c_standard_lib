/* sqrt function */
#include <limits.h>
#include "xmath.h"

double (sqrt)(double x)
	{	/* compute sqrt(x) */
	short xexp;

	switch (_Dunscale(&xexp, &x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		if (DSIGN(x))
			{	/* -INF */
			errno = EDOM;
			return (_Nan._D);
			}
		else
			{	/* +INF */
			errno = ERANGE;
			return (_Inf._D);
			}
	case 0:
		return (0.0);
	default:	/* finite */
		if (x < 0.0)
			{	/* sqrt undefined for reals */
			errno = EDOM;
			return (_Nan._D);
			}
		 {	/* 0 < x, compute sqrt(x) */
		double y;
		static const double sqrt2 = 1.41421356237309505;

		y = (-0.1984742 * x + 0.8804894) * x + 0.3176687;
		y = 0.5 * (y + x / y);
		y += x / y;
		x = 0.25 * y + x / y;
		if ((unsigned int)xexp & 1)
			x *= sqrt2, --xexp;
		_Dscale(&x, xexp / 2);
		return (x);
		 }
		}
	}
