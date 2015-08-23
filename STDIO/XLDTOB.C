/* _Ldtob function */
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include "xmath.h"
#include "xstdio.h"

		/* macros */
#define NDIG	8

		/* static data */
static const long double pows[] = {
	1e1L, 1e2L, 1e4L, 1e8L, 1e16L, 1e32L,
#if 0x100 < _LBIAS	/* assume IEEE 754 8- or 10-byte */
	1e64L, 1e128L, 1e256L,
#if _DLONG			/* assume IEEE 754 10-byte */
	1e512L, 1e1024L, 1e2048L, 1e4096L,
#endif
#endif
	};

void _Ldtob(_Pft *px, char code)
	{	/* convert long double to text */
	char ac[32];
	char *p = ac;
	long double ldval = px->v.ld;
	short errx, nsig, xexp;

	if (px->prec < 0)
		px->prec = 6;
	else if (px->prec == 0 && (code == 'g' || code == 'G'))
		px->prec = 1;
	if (0 < (errx = _Ldunscale(&xexp, &px->v.ld)))
		{	/* x == NaN, x == INF */
		memcpy(px->s, errx == NAN ? "NaN" : "Inf", px->n1 = 3);
		return;
		}
	else if (0 == errx)	/* x == 0 */
		nsig = 0, xexp = 0;
	else
		{	/* 0 < |x|, convert it */
		 {	/* scale ldval to ~~10^(NDIG/2) */
		int i, n;

		if (ldval < 0.0)
			ldval = -ldval;
		if ((xexp = xexp * 30103L / 100000L - NDIG/2) < 0)
			{	/* scale up */
			n = (-xexp + (NDIG/2-1)) & ~(NDIG/2-1), xexp = -n;
			for (i = 0; 0 < n; n >>= 1, ++i)
				if (n & 1)
					ldval *= pows[i];
			}
		else if (0 < xexp)
			{	/* scale down */
			long double factor = 1.0;

			xexp &= ~(NDIG/2-1);
			for (n = xexp, i = 0; 0 < n; n >>= 1, ++i)
				if (n & 1)
					factor *= pows[i];
			ldval /= factor;
			}
		 }
		 {	/* convert significant digits */
		int gen = px->prec
			+ (code == 'f' ? xexp + 2+NDIG : 2+NDIG/2);

		if (LDBL_DIG+NDIG/2 < gen)
			gen = LDBL_DIG+NDIG/2;
		for (*p++ = '0'; 0 < gen && 0.0 < ldval; p += NDIG)
			{	/* convert NDIG at a time */
			int j;
			long lo = (long)ldval;

			if (0 < (gen -= NDIG))
				ldval = (ldval - (long double)lo) * 1e8L;
			for (p += NDIG, j = NDIG; 0 < lo && 0 <= --j; )
				{	/* convert NDIG digits */
				ldiv_t qr = ldiv(lo, 10);

				*--p = qr.rem + '0', lo = qr.quot;
				}
			while (0 <= --j)
				*--p = '0';
			}
		gen = p - &ac[1];
		for (p = &ac[1], xexp += NDIG-1; *p == '0'; ++p)
			--gen, --xexp;	/* correct xexp */
		nsig = px->prec + (code == 'f' ? xexp + 1
			: code == 'e' || code == 'E' ? 1 : 0);
		if (gen < nsig)
			nsig = gen;
		if (0 < nsig)
			{	/* round and strip trailing zeros */
			const char drop
				= nsig < gen && '5' <= p[nsig] ? '9' : '0';
			int n;

			for (n = nsig; p[--n] == drop; )
				--nsig;
			if (drop == '9')
				++p[n];
			if (n < 0)
				--p, ++nsig, ++xexp;
			}
		 }
		}
	_Genld(px, code, p, nsig, xexp);
	}
