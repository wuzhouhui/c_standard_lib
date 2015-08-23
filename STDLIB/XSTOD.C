/* _Stod function */
#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include "xmath.h"

	/* macros */
#define SIG_MAX	32

double _Stod(const char *s, char **endptr)
	{	/* convert string to double, with checking */
	const char point = localeconv()->decimal_point[0];
	const char *sc;
	char buf[SIG_MAX], sign;
	double x;
	int ndigit, nsig, nzero, olead, opoint;

	for (sc = s; isspace(*sc); ++sc)
		;
	sign = *sc == '-' || *sc == '+' ? *sc++ : '+';
	olead = -1, opoint = -1;
	for (ndigit = 0, nsig = 0, nzero = 0; ; ++sc)
		if (*sc == point)
			if (0 <= opoint)
				break;	/* already seen point */
			else
				opoint = ndigit;
		else if (*sc == '0')
			++nzero, ++ndigit;
		else if (!isdigit(*sc))
			break;
		else
			{	/* got a nonzero digit */
			if (olead < 0)
				olead = nzero, nzero = 0, ndigit = 0;
			else	/* deliver zeros */
				for (; 0 < nzero && nsig < SIG_MAX; --nzero)
					buf[nsig++] = 0;
			++ndigit;
			if (nsig < SIG_MAX)	/* deliver digit */
				buf[nsig++] = *sc - '0';
			}
	if (ndigit == 0)
		{	/* set endptr */
		if (endptr)
			*endptr = (char *)s;
		return (0.0);
		}
	for (; 0 < nsig && buf[nsig - 1] == 0; --nsig)
		;	/* skip trailing digits */
	 {	/* compute significand */
	const char *pc = buf;
	int n;
	long lo[SIG_MAX/8+1];
	long *pl = &lo[nsig >> 3];
	static double fac[] = {0, 1e8, 1e16, 1e24, 1e32};

	for (*pl = 0, n = nsig; 0 < n; --n)
		if ((n & 07) == 0)	/* start new sum */
			*--pl = *pc++;
		else
			*pl = *pl * 10 + *pc++;
	for (x = (double)lo[0], n = 0; ++n <= (nsig >> 3); )
		if (lo[n] != 0)
			x += fac[n] * (double)lo[n];
	 }
	 {	/* fold in any explicit exponent */
	long lexp = 0;
	short sexp;

	if (*sc == 'e' || *sc == 'E')
		{	/* parse exponent */
		const char *scsav = sc;
		const char esign = *++sc == '+' || *sc == '-'
			? *sc++ : '+';

		if (!isdigit(*sc))
			sc = scsav;	/* ill-formed exponent */
		else
			{	/* exponent looks valid */
			for (; isdigit(*sc); ++sc)
				if (lexp < 100000)	/* else overflow */
					lexp = lexp * 10 + *sc - '0';
			if (esign == '-')
				lexp = -lexp;
			}
		}
	if (endptr)
		*endptr = (char *)sc;
	if (opoint < 0)
		lexp += ndigit - nsig;
	else
		lexp += opoint - olead - nsig;
	sexp = lexp < SHRT_MIN ? SHRT_MIN : lexp < SHRT_MAX
		? (short)lexp : SHRT_MAX;
	x = _Dtento(x, sexp);
	return (sign == '-' ? -x : x);
	 }
	}
