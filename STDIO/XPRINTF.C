/* _Printf function */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

#define MAX_PAD	(sizeof (spaces) - 1)
#define PAD(s, n)	if (0 < (n)) {int i, j = (n); \
	for (; 0 < j; j -= i) \
		{i = MAX_PAD < j ? MAX_PAD : j; PUT(s, i); } }
#define PUT(s, n)	\
	if (0 < (n)) {if ((arg = (*pfn)(arg, s, n)) != NULL) \
		x.nchar += (n); else return (EOF); }

static char spaces[] = "                                ";
static char zeroes[] = "00000000000000000000000000000000";

int _Printf(void *(*pfn)(void *, const char *, size_t),
	void *arg, const char *fmt, va_list ap)
	{	/* print formatted */
	_Pft x;

	for (x.nchar = 0; ; )
		{	/* scan format string */
		const char *s = fmt;

		 {	/* copy any literal text */
		int n;
		wchar_t wc;
		_Mbsave state = {0};

		while (0 < (n = _Mbtowc(&wc, s, MB_CUR_MAX, &state)))
			{	/* scan for '%' or '\0' */
			s += n;
			if (wc == '%')
				{	/* got a conversion specifier */
				--s;
				break;
				}
			}
		PUT(fmt, s - fmt);
		if (n <= 0)
			return (x.nchar);
		fmt = ++s;
		 }
		 {	/* parse a conversion specifier */
		const char *t;
		static const char fchar[] = {" +-#0"};
		static const unsigned int fbit[] = {
			_FSP, _FPL, _FMI, _FNO, _FZE, 0};

		for (x.flags = 0; (t = strchr(fchar, *s)) != NULL; ++s)
			x.flags |= fbit[t - fchar];
		if (*s == '*')
			{	/* get width argument */
			x.width = va_arg(ap, int);
			if (x.width < 0)
				{	/* same as '-' flag */
				x.width = -x.width;
				x.flags |= _FMI;
				}
			++s;
			}
		else	/* accumulate width digits */
			for (x.width = 0; isdigit(*s); ++s)
				if (x.width < _WMAX)
					x.width = x.width * 10 + *s - '0';
		if (*s != '.')
			x.prec = -1;
		else if (*++s == '*')
			{	/* get precision argument */
			x.prec = va_arg(ap, int);
			++s;	/* prepare for next interation */
			}
		else	/* accumulate precision digits */
			for (x.prec = 0; isdigit(*s); ++s)
				if (x.prec < _WMAX)
					x.prec = x.prec * 10 + *s - '0';
		x.qual = strchr("hlL", *s) ? *s++ : '\0';
		 }
		 {	/* do the conversion */
		char ac[32];

		_Putfld(&x, &ap, *s, ac);
		x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;
		if (!(x.flags & _FMI))
			PAD(spaces, x.width);
		PUT(ac, x.n0);
		PAD(zeroes, x.nz0);
		PUT(x.s, x.n1);
		PAD(zeroes, x.nz1);
		PUT(x.s + x.n1, x.n2);
		PAD(zeroes, x.nz2);
		if (x.flags & _FMI)
			PAD(spaces, x.width);
		 }
		fmt = s + 1;
		}
	}
