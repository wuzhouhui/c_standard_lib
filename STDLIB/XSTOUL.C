/* _Stoul function */
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>

		/* macros */
#define BASE_MAX	36	/* largest valid base */
		/* static data */
static const char digits[] = {	/* valid digits */
	"0123456789abcdefghijklmnopqrstuvwxyz"};
static const char ndigs[BASE_MAX+1] = {	/* 32-bits! */
	0, 0, 33, 21, 17, 14, 13, 12, 11, 11,
	10, 10, 9, 9, 9, 9, 9, 8, 8, 8,
	8, 8, 8, 8, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7,};

unsigned long _Stoul(const char *s, char **endptr, int base)
	{	/* convert string to unsigned long, with checking */
	const char *sc, *sd;
	const char *s1, *s2;
	char dig, sign;
	ptrdiff_t n;
	unsigned long x, y;

	for (sc = s; isspace(*sc); ++sc)
		;
	sign = *sc == '-' || *sc == '+' ? *sc++ : '+';
	if (base < 0 || base == 1 || BASE_MAX < base)
		{	/* silly base */
		if (endptr)
			*endptr = (char *)s;
		return (0);
		}
	else if (0 < base)
		{	/* strip 0x or 0X */
		if (base == 16 && *sc == '0'
			&& (sc[1] == 'x' || sc[1] == 'X'))
			sc += 2;
		}
	else if (*sc != '0')
		base = 10;
	else if (sc[1] == 'x' || sc[1] == 'X')
		base = 16, sc += 2;
	else
		base = 8;
	for (s1 = sc; *sc == '0'; ++sc)
		;	/* skip leading zeros */
	x = 0;
	for (s2 = sc; (sd = (char *)memchr(digits,
		tolower(*sc), base)) != NULL; ++sc)
		{	/* accumulate digits */
		y = x, dig = sd - digits;	/* for overflow checking */
		x = x * base + dig;
		}
	if (s1 == sc)
		{	/* check string validity */
		if (endptr)
			*endptr = (char *)s;
		return (0);
		}
	n = sc - s2 - ndigs[base];
	if (n < 0)
		;
	else if (0 < n || x < x - dig
		|| (x - dig) / base != y)
		{	/* overflow */
		errno = ERANGE;
		sc = s, x = ULONG_MAX, sign = '+';
		}
	if (sign == '-')	/* get final value */
		x = -x;
	if (endptr)
		*endptr = (char *)sc;
	return (x);
	}
