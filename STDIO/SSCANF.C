/* sscanf function */
#include "xstdio.h"

static int scin(void *str, int ch)
	{	/* get or put a character */
	char *s = *(char **)str;

	if (ch == _WANT)
		if (*s == '\0')
			return (EOF);
		else
			{	/* deliver a character */
			*(char **)str = s + 1;
			return (*s);
			}
	else if (0 <= ch)
		*(char **)str = s - 1;
	return (ch);
	}

int (sscanf)(const char *buf, const char *fmt, ...)
	{	/* read formatted from string */
	int ans;
	va_list ap;

	va_start(ap, fmt);
	ans = _Scanf(&scin, (void **)&buf, fmt, ap);
	va_end(ap);
	return (ans);
	}
