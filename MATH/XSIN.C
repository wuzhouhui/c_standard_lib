/* _Sin function */
#include "xmath.h"

/* coefficients */
static const double c[8] = {
	-0.000000000011470879,
	 0.000000002087712071,
	-0.000000275573192202,
	 0.000024801587292937,
	-0.001388888888888893,
	 0.041666666666667325,
	-0.500000000000000000,
	 1.0};
static const double s[8] = {
	-0.000000000000764723,
	 0.000000000160592578,
	-0.000000025052108383,
	 0.000002755731921890,
	-0.000198412698412699,
	 0.008333333333333372,
	-0.166666666666666667,
	 1.0};
static const double c1 = 3294198.0 / 2097152.0;
static const double c2 = 3.139164786504813217e-7;
static const double twobypi = 0.63661977236758134308;
static const double twopi = 6.28318530717958647693;

double _Sin(double x, unsigned int qoff)
	{	/* compute sin(x) or cos(x) */
	switch (_Dtest(&x))
		{
	case NAN:
		errno = EDOM;
		return (x);
	case 0:
		return (qoff ? 1.0 : 0.0);
	case INF:
		errno = EDOM;
		return (_Nan._D);
	default:	/* finite */
		 {	/* compute sin/cos */
		double g;
		long quad;

		if (x < -HUGE_RAD || HUGE_RAD < x)
			{	/* x huge, sauve qui peut */
			g = x / twopi;
			_Dint(&g, 0);
			x -= g * twopi;
			}
		g = x * twobypi;
		quad = (long)(0 < g ? g + 0.5 : g - 0.5);
		qoff += (unsigned long)quad & 0x3;
		g = (double)quad;
		g = (x - g * c1) - g * c2;
		if ((g < 0.0 ? -g : g) < _Rteps._D)
			{	/* sin(tiny)==tiny, cos(tiny)==1 */
			if (qoff & 0x1)
				g = 1.0;	/* cos(tiny) */
			}
		else if (qoff & 0x1)
			g = _Poly(g * g, c, 7);
		else
			g *= _Poly(g * g, s, 7);
		return (qoff & 0x2 ? -g : g);
		 }
		}
	}
