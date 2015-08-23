/* atan2 function */
#include "xmath.h"

double (atan2)(double y, double x)
	{	/* compute atan(y/x) */
	double z;
	const short errx = _Dtest(&x);
	const short erry = _Dtest(&y);
	unsigned short hex;

	if (errx <= 0 && erry <= 0)
		{	/* x & y both finite or 0 */
		if (y < 0.0)
			y = -y, hex = 0x8;
		else
			hex = 0x0;
		if (x < 0.0)
			x = -x, hex ^= 0x6;
		if (x < y)
			z = x / y, hex ^= 0x2;
		else if (0.0 < x)
			z = y / x;
		else
			return (0.0);	/* atan(0, 0) */
		}
	else if (errx == NAN || erry == NAN)
		{	/* return one of the NaNs */
		errno = EDOM;
		return (errx == NAN ? x : y);
		}
	else
		{	/* at least one INF */
		z = errx == erry ? 1.0 : 0.0;
		hex = DSIGN(y) ? 0x8 : 0x0;
		if (DSIGN(x))
			hex ^= 0x6;
		if (erry == INF)
			hex ^= 0x2;
		}
	return (_Atan(z, hex));
	}
