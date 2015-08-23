/* _Asin function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 10 */
static const double p[5] = {
	-0.69674573447350646411e+0,
	 0.10152522233806463645e+2,
	-0.39688862997504877339e+2,
	 0.57208227877891731407e+2,
	-0.27368494524164255994e+2};
static const double q[6] = {
	 0.10000000000000000000e+1,
	-0.23823859153670238830e+2,
	 0.15095270841030604719e+3,
	-0.38186303361750149284e+3,
	 0.41714430248260412556e+3,
	-0.16421096714498560795e+3};
static const double piby2 = 1.57079632679489661923;
static const double piby4 = 0.78539816339744830962;

double _Asin(double x, int idx)
	{	/* compute asin(x) or acos(x) */
	double g, y;
	const short errx = _Dtest(&x);

	if (0 < errx)
		{	/* INF, NaN */
		errno = EDOM;
		return (errx == NAN ? x : _Nan._D);
		}
	if (x < 0.0)
		y = -x, idx |= 2;
	else
		y = x;
	if (y < _Rteps._D)
		;
	else if (y < 0.5)
		{	/* y*y worth computing */
		g = y * y;
		y += y * g * _Poly(g, p, 4) / _Poly(g, q, 5);
		}
	else if (y < 1.0)
		{	/* find 2*asin(sqrt((1-x)/2)) */
		idx |= 4;
		g = (1.0 - y) / 2.0;	/* NOT * 0.5! */
		y = sqrt(g);
		y += y;
		y += y * g * _Poly(g, p, 4) / _Poly(g, q, 5);
		}
	else if (y == 1.0)
		idx |= 4, y = 0.0;
	else
		{	/* 1.0 < |x|, undefined */
		errno = EDOM;
		return (_Nan._D);
		}
	switch (idx)
		{	/* flip and fold */
	default:	/* shouldn't happen */
	case 0:	/* asin, [0, 1/2) */
	case 5:	/* acos, [1/2, 1] */
		return (y);
	case 1:	/* acos, [0, 1/2) */
	case 4:	/* asin, [1/2, 1] */
		return ((piby4 - y) + piby4);
	case 2:	/* asin, (-1/2, 0) */
		return (-y);
	case 3:	/* acos, (-1/2, 0) */
		return ((piby4 + y) + piby4);
	case 6:	/* asin, [-1, -1/2] */
		return ((-piby4 + y) - piby4);
	case 7:	/* acos, [-1, -1/2] */
		return ((piby2 - y) + piby2);
		}
	}
