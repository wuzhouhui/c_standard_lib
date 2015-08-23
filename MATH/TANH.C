/* tanh function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 13 */
static const double p[3] = {
	-0.96437492777225469787e+0,
	-0.99225929672236083313e+2,
	-0.16134119023996228053e+4};
static const double q[4] = {
	0.10000000000000000000e+1,
	0.11274474380534949335e+3,
	0.22337720718962312926e+4,
	0.48402357071988688686e+4};
static const double ln3by2 = 0.54930614433405484570;

double (tanh)(double x)
	{	/* compute tanh(x) */
	switch (_Dtest(&x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		return (DSIGN(x) ? -1.0 : 1.0);
	case 0:
		return (0.0);
	default:	/* finite */
		 {	/* compute tanh(finite) */
		short neg;

		if (x < 0.0)
			x = -x, neg = 1;
		else
			neg = 0;
		if (x < _Rteps._D)
			;	/* x tiny */
		else if (x < ln3by2)
			{	/* |x| < ln(3)/2 */
			const double g = x * x;

			x += x * g * ((p[0] * g + p[1]) * g + p[2])
				/ (((q[0] * g + q[1]) * g + q[2]) * g + q[3]);
			}
		else if (_Exp(&x, 0) < 0)
			x = 1.0 - 2.0 / (x * x + 1.0);
		else
			x = 1.0;	/* x large */
		return (neg ? -x : x);
		 }
		}
	}
