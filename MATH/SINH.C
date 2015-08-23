/* sinh function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 12 */
static const double p[4] = {
	-0.78966127417357099479e+0,
	-0.16375798202630751372e+3,
	-0.11563521196851768270e+5,
	-0.35181283430177117881e+6};
static const double q[4] = {
	 1.0,
	-0.27773523119650701667e+3,
	 0.36162723109421836460e+5,
	-0.21108770058106271242e+7};

double (sinh)(double x)
	{	/* compute sinh(x) */
	switch (_Dtest(&x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		errno = ERANGE;
		return (DSIGN(x) ? -_Inf._D : _Inf._D);
	case 0:
		return (0.0);
	default:	/* finite */
		 {	/* compute sinh(finite) */
		short neg;

		if (x < 0.0)
			x = -x, neg = 1;
		else
			neg = 0;
		if (x < _Rteps._D)
			;	/* x tiny */
		else if (x < 1.0)
			{	/* |x| < 1 */
			const double y = x * x;

			x += x * y
				* (((p[0] * y + p[1]) * y + p[2]) * y + p[3])
				/ (((q[0] * y + q[1]) * y + q[2]) * y + q[3]);
			}
		else if (0 <= _Exp(&x, -1))
			errno = ERANGE;	/* x large */
		else if (x < _Xbig._D)
			x -= 0.25 / x;
		return (neg ? -x : x);
		 }
		}
	}
