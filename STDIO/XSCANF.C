/* _Scanf function */
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

int _Scanf(int (*pfn)(void *, int), void *arg,
	const char *fmt, va_list ap)
	{	/* read formatted */
	int nconv = 0;
	_Sft x;

	x.pfn = pfn;
	x.arg = arg;
	x.ap = ap;
	x.nchar = 0;
	for (x.s = fmt; ; ++x.s)
		{	/* parse format string */
		int ch;

		 {	/* match any literal or white-space */
		int n;
		wchar_t wc;
		_Mbsave state = {0};

		while (0 < (n = _Mbtowc(&wc, x.s, MB_CUR_MAX, &state)))
			{	/* check type of multibyte char */
			x.s += n;
			if (wc == '%')
				break;
			else if (wc <= UCHAR_MAX && isspace(wc))
				{	/* match any white-space */
				while (isspace(*x.s))
					++x.s;
				while (isspace(ch = GET(&x)))
					;
				UNGETN(&x, ch);
				}
			else	/* match literal text */
				for (x.s -= n; 0 <= --n; )
					if ((ch = GET(&x)) != *x.s++)
						{	/* bad match */
						UNGETN(&x, ch);
						return (nconv);
						}
			}
		if (*x.s == '\0')
			return (nconv);
		 }
		 {	/* process a conversion specifier */
		int code;

		x.noconv = *x.s == '*' ? *x.s++ : '\0';
		for (x.width = 0; isdigit(*x.s); ++x.s)
			if (x.width < _WMAX)
				x.width = x.width * 10 + *x.s - '0';
		x.qual = strchr("hlL", *x.s) ? *x.s++ : '\0';
		if (!strchr("cn[", *x.s))
			{	/* match leading white-space */
			while (isspace(ch = GET(&x)))
				;
			UNGETN(&x, ch);
			}
		if ((code = _Getfld(&x)) <= 0)
			return (nconv == 0 ? code : nconv);
		if (x.stored)
			++nconv;
		 }
		}
	}
