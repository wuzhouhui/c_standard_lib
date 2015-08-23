/* _Dtest function -- IEEE 754 version */
#include "xmath.h"

short _Dtest(double *px)
	{	/* categorize *px */
	unsigned short *ps = (unsigned short *)px;
	short xchar = (ps[_D0] & _DMASK) >> _DOFF;

	if (xchar == _DMAX)	/* NaN or INF */
		return (ps[_D0] & _DFRAC || ps[_D1]
			|| ps[_D2] || ps[_D3] ? NAN : INF);
	else if (0 < xchar || ps[_D0] & _DFRAC
		|| ps[_D1] || ps[_D2] || ps[_D3])
		return (FINITE);	/* finite */
	else
		return (0);	/* zero */
	}
