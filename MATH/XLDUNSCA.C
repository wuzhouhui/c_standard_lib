/* _Ldunscale function -- IEEE 754 version */
#include "xmath.h"

#if _DLONG	/* 10-byte IEEE format */
#define _LMASK	0x7fff
#define _LMAX	0x7fff
#define _LSIGN	0x8000
#if _D0==3
#define _L0		4	/* little-endian order */
#define _L1		3
#define _L2		2
#define _L3		1
#define _L4		0
#else
#define _L0		0	/* big-endian order */
#define _L1		1
#define _L2		2
#define _L3		3
#define _L4		4
#endif

static short dnorm(unsigned short *ps)
	{	/* normalize long double fraction */
	short xchar;

	for (xchar = 0; ps[_L1] == 0; xchar -= 16)
		{	/* shift left by 16 */
		ps[_L1] = ps[_L2], ps[_L2] = ps[_L3];
		ps[_L3] = ps[_L4], ps[_L4] = 0;
		}
	for (; ps[_L1] < 1U<<_LOFF; --xchar)
		{	/* shift left by 1 */
		ps[_L1] = ps[_L1] << 1 | ps[_L2] >> 15;
		ps[_L2] = ps[_L2] << 1 | ps[_L3] >> 15;
		ps[_L3] = ps[_L3] << 1 | ps[_L4] >> 15;
		ps[_L4] <<= 1;
		}
	return (xchar);
	}

short _Ldunscale(short *pex, long double *px)
	{	/* separate *px to |frac| < 1/2 and 2^*pex */
	unsigned short *ps = (unsigned short *)px;
	short xchar = ps[_L0] & _LMASK;

	if (xchar == _LMAX)
		{	/* NaN or INF */
		*pex = 0;
		return (ps[_L1] & 0x7fff || ps[_L2]
			|| ps[_L3] || ps[_L4] ? NAN : INF);
		}
	else if (ps[_L1] == 0 && ps[_L2] == 0
		&& ps[_L3] == 0 && ps[_L4] == 0)
		{	/* zero */
		*pex = 0;
		return (0);
		}
	else
		{	/* finite, reduce to [1/2, 1) */
		xchar += dnorm(ps);
		ps[_L0] = ps[_L0] & _LSIGN | _LBIAS;
		*pex = xchar - _LBIAS;
		return (FINITE);
		}
	}
#else	/* long double same as double */
short _Ldunscale(short *pex, long double *px)
	{	/* separate *px to |frac| < 1/2 and 2^*pex */
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
#endif
