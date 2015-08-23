/* printf function */
#include "xstdio.h"

static void *prout(void *str, const char *buf, size_t n)
	{	/* write to file */
	return (fwrite(buf, 1, n, (FILE *)str) == n ? str : NULL);
	}

int (printf)(const char *fmt, ...)
	{	/* print formatted to stdout */
	int ans;
	va_list ap;

	va_start(ap, fmt);
	ans = _Printf(&prout, stdout, fmt, ap);
	va_end(ap);
	return (ans);
	}
