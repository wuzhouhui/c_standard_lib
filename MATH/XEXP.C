/* _Exp function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 6 */
static const double p[3] = {
	0.31555192765684646356e-4,
	0.75753180159422776666e-2,
	0.25000000000000000000e+0};
static const double q[4] = {
	0.75104028399870046114e-6,
	0.63121894374398503557e-3,
	0.56817302698551221787e-1,
	0.50000000000000000000e+0};
static const double c1 = 22713.0 / 32768.0;
static const double c2 = 1.428606820309417232e-6;
static const double hugexp = (double)HUGE_EXP;
static const double invln2 = 1.4426950408889634074;

short _Exp(double *px, short eoff)
	{	/* compute e^(*px)*2^eoff, x finite */
	int neg;

	if (*px < 0)
		*px = -*px, neg = 1;
	else
		neg = 0;
	if (hugexp < *px)
		{	/* certain underflow or overflow */
		*px = neg ? 0.0 : _Inf._D;
		return (neg ? 0 : INF);
		}
	else
		{	/* xexp won't overflow */
		double g = *px * invln2;
		short xexp = (short)(g + 0.5);

		g = (double)xexp;
		g = (*px - g * c1) - g * c2;
		if (-_Rteps._D < g && g < _Rteps._D)
			*px = 1.0;
		else
			{	/* g*g worth computing */
			const double y = g * g;

			g *= (p[0] * y + p[1]) * y + p[2];
			*px = 0.5 + g / (((q[0] * y + q[1]) * y + q[2]) * y
				+ q[3] - g);
			++xexp;
			}
		if (neg)
			*px = 1.0 / *px, xexp = -xexp;
		return (_Dscale(px, eoff + xexp));
		}
	}
