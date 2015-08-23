/* _Strftime function */
#include <stdlib.h>
#include <string.h>
#include "xtime.h"

		/* macros */
#define PUT(s, na)	(void)(nput = (na), \
	0 < nput && (nchar += nput) <= bufsize ? \
		(memcpy(buf, s, nput), buf += nput) : 0)

size_t _Strftime(char *buf, size_t bufsize, const char *fmt,
	const struct tm *t, _Tinfo *tin)
	{	/* format time information */
	const char *fmtsav, *s;
	size_t len, lensav, nput;
	size_t nchar = 0;

	for (s = fmt, len = strlen(fmt), fmtsav = NULL; ; fmt = s)
		{	/* parse format string */
		int n;
		wchar_t wc;
		_Mbsave state = {0};

		while (0 < (n = _Mbtowc(&wc, s, len, &state)))
			{	/* scan for '%' or '\0' */
			s += n, len -= n;
			if (wc == '%')
				break;
			}
		if (fmt < s)	/* copy any literal text */
			PUT(fmt, s - fmt - (0 < n ? 1 : 0));
		if (0 < n)
			{	/* do the conversion */
			char ac[20];
			int m;
			const char *p = _Gentime(t, tin, *s, &m, ac);

			++s, --len;
			if (0 <= m)
				PUT(p, m);
			else if (fmtsav == NULL)
				fmtsav = s, s = p, lensav = len, len = -m;
			}
		if (0 == len && fmtsav == NULL || n < 0)
			{	/* format end or bad multibyte char */
			PUT("", 1);	/* null termination */
			return (nchar <= bufsize ? nchar - 1 : 0);
			}
		else if (0 == len)
			s = fmtsav, fmtsav = NULL, len = lensav;
		}
	}
