/* _Dscale function -- IEEE 754 version */
#include "xmath.h"

short _Dscale(double *px, short xexp)
	{	/* scale *px by 2^xexp with checking */
	long lexp;
	unsigned short *ps = (unsigned short *)px;
	short xchar = (ps[_D0] & _DMASK) >> _DOFF;

	if (xchar == _DMAX)	/* NaN or INF */
		return (ps[_D0] & _DFRAC || ps[_D1]
			|| ps[_D2] || ps[_D3] ? NAN : INF);
	else if (0 < xchar)
		;	/* finite */
	else if (0 < (xchar = _Dnorm(ps)))
		return (0);	/* zero */
	lexp = (long)xexp + xchar;
	if (_DMAX <= lexp)
		{	/* overflow, return +/-INF */
		*px = ps[_D0] & _DSIGN ? -_Inf._D : _Inf._D;
		return (INF);
		}
	else if (0 < lexp)
		{	/* finite result, repack */
		ps[_D0] = ps[_D0] & ~_DMASK | (short)lexp << _DOFF;
		return (FINITE);
		}
	else
		{	/* denormalized, scale */
		unsigned short sign = ps[_D0] & _DSIGN;

		ps[_D0] = 1 << _DOFF | ps[_D0] & _DFRAC;
		if (--lexp < -(48+_DOFF))
			{	/* underflow, return +/-0 */
			ps[_D0] = sign, ps[_D1] = 0;
			ps[_D2] = 0, ps[_D3] = 0;
			return (0);
			}
		else
			{	/* nonzero, align fraction */
			for (xexp = lexp; xexp <= -16; xexp += 16)
				{	/* scale by words */
				ps[_D3] = ps[_D2], ps[_D2] = ps[_D1];
				ps[_D1] = ps[_D0], ps[_D0] = 0;
				}
			if ((xexp = -xexp) != 0)
				{	/* scale by bits */
				ps[_D3] = ps[_D3] >> xexp
					| ps[_D2] << 16 - xexp;
				ps[_D2] = ps[_D2] >> xexp
					| ps[_D1] << 16 - xexp;
				ps[_D1] = ps[_D1] >> xexp
					| ps[_D0] << 16 - xexp;
				ps[_D0] >>= xexp;
				}
			ps[_D0] |= sign;
			return (FINITE);
			}
		}
	}
