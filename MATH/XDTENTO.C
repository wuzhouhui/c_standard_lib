/* _Dtento function -- IEEE 754 version */
#include <errno.h>
#include <float.h>
#include "xmath.h"

		/* macros */
#define NPOWS	(sizeof pows / sizeof pows[0] - 1)
		/* static data */
static const double pows[] = {
	1e1, 1e2, 1e4, 1e8, 1e16, 1e32,
#if 0x100 < _DBIAS	/* assume IEEE 754 8-byte */
	1e64, 1e128, 1e256,
#endif
	};
static const size_t npows = NPOWS;

static short dmul(double *px, double y)
	{	/* multiply y by *px with checking */
	short xexp;

	_Dunscale(&xexp, px);
	*px *= y;
	return (_Dscale(px, xexp));
	}

double _Dtento(double x, short n)
	{	/* compute x * 10**n */
	double factor;
	short errx;
	size_t i;

	if (n == 0 || x == 0.0)
		return (x);
	factor = 1.0;
	if (n < 0)
		{	/* scale down */
		unsigned int nu = -(unsigned int)n;

		for (i = 0; 0 < nu && i < npows; nu >>= 1, ++i)
			if (nu & 1)
				factor *= pows[i];
		errx = dmul(&x, 1.0 / factor);
		if (errx < 0 && 0 < nu)
			for (factor = 1.0 / pows[npows]; 0 < nu; --nu)
				if (0 <= (errx = dmul(&x, factor)))
					break;
		}
	else if (0 < n)
		{	/* scale up */
		for (i = 0; 0 < n && i < npows; n >>= 1, ++i)
			if (n & 1)
				factor *= pows[i];
		errx = dmul(&x, factor);
		if (errx < 0 && 0 < n)
			for (factor = pows[npows]; 0 < n; --n)
				if (0 <= (errx = dmul(&x, factor)))
					break;
		}
	if (0 <= errx)
		errno = ERANGE;
	return (x);
	}
