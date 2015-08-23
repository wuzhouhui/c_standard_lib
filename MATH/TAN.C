/* tan function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 9 */
static const double p[3] = {
	-0.17861707342254426711e-4,
	 0.34248878235890589960e-2,
	-0.13338350006421960681e+0};
static const double q[4] = {
	 0.49819433993786512270e-6,
	-0.31181531907010027307e-3,
	 0.25663832289440112864e-1,
	-0.46671683339755294240e+0};
static const double c1 = 3294198.0 / 2097152.0;
static const double c2 = 3.139164786504813217e-7;
static const double twobypi = 0.63661977236758134308;
static const double twopi = 6.28318530717958647693;

double (tan)(double x)
	{	/* compute tan(x) */
	double g, gd;
	long quad;

	switch (_Dtest(&x))
		{
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		errno = EDOM;
		return (_Nan._D);
	case 0:
		return (0.0);
	default:	/* finite */
		if (x < -HUGE_RAD || HUGE_RAD < x)
			{	/* x huge, sauve qui peut */
			g = x / twopi;
			_Dint(&g, 0);
			x -= g * twopi;
			}
		g = x * twobypi;
		quad = (long)(0 < g ? g + 0.5 : g - 0.5);
		g = (double)quad;
		g = (x - g * c1) - g * c2;
		gd = 1.0;
		if (_Rteps._D < (g < 0.0 ? -g : g))
			{	/* g*g worth computing */
			double y = g * g;
	
			gd += (((q[0] * y + q[1]) * y + q[2]) * y + q[3]) * y;
			g += ((p[0] * y + p[1]) * y + p[2]) * y * g;
			}
		return ((unsigned int)quad & 0x1 ? -gd / g : g / gd);
		}
	}
