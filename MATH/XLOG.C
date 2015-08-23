/* _Log function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 5 */
static const double p[3] = {
	-0.78956112887491257267e+0,
	 0.16383943563021534222e+2,
	-0.64124943423745581147e+2};
static const double q[3] = {
	-0.35667977739034646171e+2,
	 0.31203222091924532844e+3,
	-0.76949932108494879777e+3};
static const double c1 = 22713.0 / 32768.0;
static const double c2 = 1.428606820309417232e-6;
static const double loge = 0.43429448190325182765;
static const double rthalf = 0.70710678118654752440;

double _Log(double x, int decflag)
	{	/* compute ln(x) */
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
			{	/* INF */
			errno = ERANGE;
			return (_Inf._D);
			}
	case 0:
		errno = ERANGE;
		return (-_Inf._D);
	default:	/* finite */
		if (x < 0.0)
			{	/* ln(negative) undefined */
			errno = EDOM;
			return (_Nan._D);
			}
		else
			{	/* 1/2 <= x < 1 */
			double z = x - 0.5;
			double w;
	
			if (rthalf < x)
				z = (z - 0.5) / (x * 0.5 + 0.5);
			else
				{	/* x <= sqrt(1/2) */
				--xexp;
				z /= (z * 0.5 + 0.5);
				}
			w = z * z;
			z += z * w * ((p[0] * w + p[1]) * w + p[2])
				/ (((w + q[0]) * w + q[1]) * w + q[2]);
			if (xexp != 0)
				{	/* form z += ln2 * xexp safely */
				const double xn = (double)xexp;
	
				z = (xn * c2 + z) + xn * c1;
				}
			return (decflag ? loge * z : z);
			}
		}
	}
