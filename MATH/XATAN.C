/* _Atan function */
#include "xmath.h"

/* coefficients, after Cody & Waite, Chapter 11 */
static const double a[8] = {
	0.0,
	0.52359877559829887308,
	1.57079632679489661923,
	1.04719755119659774615,
	1.57079632679489661923,
	2.09439510239319549231,
	3.14159265358979323846,
	2.61799387799149436538};
static const double p[4] = {
	-0.83758299368150059274e+0,
	-0.84946240351320683534e+1,
	-0.20505855195861651981e+2,
	-0.13688768894191926929e+2};
static const double q[5] = {
	0.10000000000000000000e+1,
	0.15024001160028576121e+2,
	0.59578436142597344465e+2,
	0.86157349597130242515e+2,
	0.41066306682575781263e+2};
static const double fold = 0.26794919243112270647;
static const double sqrt3 = 1.73205080756887729353;
static const double sqrt3m1 = 0.73205080756887729353;

double _Atan(double x, unsigned short idx)
	{	/* compute atan(x), 0 <= x <= 1.0 */
	if (fold < x)
		{	/* 2-sqrt(3) < x */
		x = (((sqrt3m1 * x - 0.5) - 0.5) + x) / (sqrt3 + x);
		idx |= 0x1;
		}
	if (x < -_Rteps._D || _Rteps._D < x)
		{	/* x*x worth computing */
		const double g = x * x;

		x += x * g / _Poly(g, q, 4)
			* (((p[0] * g + p[1]) * g + p[2]) * g + p[3]);
		}
	if (idx & 0x2)
		x = -x;
	x += a[idx & 07];
	return (idx & 0x8 ? -x : x);
	}
