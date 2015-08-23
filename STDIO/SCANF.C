/* scanf function */
#include "xstdio.h"

static int scin(void *str, int ch)
	{	/* get or put a character */
	if (ch == _WANT)
		return (fgetc((FILE *)str));
	else if (0 <= ch)
		return (ungetc(ch, (FILE *)str));
	else
		return (ch);
	}

int (scanf)(const char *fmt, ...)
	{	/* read formatted from stdin */
	int ans;
	va_list ap;

	va_start(ap, fmt);
	ans = _Scanf(&scin, stdin, fmt, ap);
	va_end(ap);
	return (ans);
	}
