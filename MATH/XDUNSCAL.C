/* _Dunscale function -- IEEE 754 version */
#include "xmath.h"

short _Dunscale(short *pex, double *px)
	{	/* separate *px to 1/2 <= |frac| < 1 and 2^*pex */
	unsigned short *ps = (unsigned short *)px;
	short xchar = (ps[_D0] & _DMASK) >> _DOFF;

	if (xchar == _DMAX)
		{	/* NaN or INF */
		*pex = 0;
		return (ps[_D0] & _DFRAC || ps[_D1]
			|| ps[_D2] || ps[_D3] ? NAN : INF);
		}
	else if (0 < xchar || (xchar = _Dnorm(ps)) <= 0)
		{	/* finite, reduce to [1/2, 1) */
		ps[_D0] = ps[_D0] & ~_DMASK | _DBIAS << _DOFF;
		*pex = xchar - _DBIAS;
		return (FINITE);
		}
	else
		{	/* zero */
		*pex = 0;
		return (0);
		}
	}
