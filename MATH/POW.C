/* pow function */
#include "xmath.h"

double (pow)(double x, double y)
	{	/* compute x^y */
	double yi = y;
	double yx, z;
	short n, xexp, zexp;
	short neg = 0;
	short errx = _Dunscale(&xexp, &x);
	const short erry = _Dint(&yi, 0);
	static const short shuge = HUGE_EXP;
	static const double dhuge = (double)HUGE_EXP;
	static const double ln2 = 0.69314718055994530942;
	static const double rthalf = 0.70710678118654752440;

	if (0 <= errx || 0 < erry)
		{	/* x == 0, INF, NAN; y == INF, NAN */
		z = _Nan._D;
		if (errx == NAN || erry == NAN)
			z = errx == NAN ? x : y, errx = NAN;
		else if (erry == INF)
			if (errx == INF)	/* INF^INF */
				errx = INF;
			else	/* 0^INF, finite^INF */
				errx = xexp <= 0 ? (DSIGN(y) ? INF : 0)
					: xexp == 1 && (x == 0.5 || x == -0.5) ? NAN
					: (DSIGN(y) ? 0 : INF);
		else if (y == 0.0)
			return (1.0);	/* x^0, x not a NaN */
		else if (errx == INF)
			{	/* INF^finite (NB: erry tests y fraction) */
			errx = y < 0.0 ? 0 : INF;
			neg = DSIGN(x) && erry == 0 && _Dint(&y, -1) < 0;
			}
		else	/* 0^finite */
			errx = y < 0.0 ? INF : 0;
		if (errx == 0)
			return (0.0);
		else if (errx == INF)
			{	/* return -INF or INF */
			errno = ERANGE;
			return (neg ? -_Inf._D : _Inf._D);
			}
		else
			{	/* return NaN */
			errno = EDOM;
			return (z);
			}
		}
	if (y == 0.0)
		return (1.0);
	if (0.0 < x)
		neg = 0;
	else if (erry < 0)
		{	/* negative^fractional */
		errno = EDOM;
		return (_Nan._D);
		}
	else
		x = -x, neg = _Dint(&yi, -1) < 0;
	if (x < rthalf)
		x *= 2.0, --xexp;	/* -sqrt(.5) <= x <= sqrt(.5) */
	n = 0, yx = 0.0;
	if (y <= -dhuge)
		zexp = xexp < 0 ? shuge : xexp == 0 ? 0 : -shuge;
	else if (dhuge <= y)
		zexp = xexp < 0 ? -shuge : xexp == 0 ? 0 : shuge;
	else
		{	/* y*log2(x) may be reasonable */
		double dexp = (double)xexp;
		long zl = (long)(yx = y * dexp);

		if (zl != 0)
			{	/* form yx = y*xexp-zl carefully */
			yx = y, _Dint(&yx, 16);
			yx = (yx * dexp - (double)zl) + (y - yx) * dexp;
			}
		yx *= ln2;
		zexp = zl <= -shuge ? -shuge : zl < shuge ? zl : shuge;
		if ((n = (short)y) < -SAFE_EXP || SAFE_EXP < n)
			n = 0;
		}
	 {	/* compute z = xfrac^n * 2^yx * 2^zexp */
	z = 1.0;
	if (x != 1.0)
		{	/* z *= xfrac^n */
		if ((yi = y - (double)n) != 0.0)
			yx += log(x) * yi;
		if (n < 0)
			n = -n;
		for (yi = x; ; yi *= yi)
			{	/* scale by x^2^n */
			if (n & 1)
				z *= yi;
			if ((n >>= 1) == 0)
				break;
			}
		if (y < 0.0)
			z = 1.0 / z;
		}
	if (yx != 0.0)	/* z *= 2^yx */
		z = _Exp(&yx, 0) < 0 ? z * yx : y < 0.0 ? 0.0 : _Inf._D;
	if (0 <= _Dscale(&z, zexp))	/* z *= 2^zexp */
		errno = ERANGE;	/* underflow or overflow */
	return (neg ? -z : z);
	 }
	}
