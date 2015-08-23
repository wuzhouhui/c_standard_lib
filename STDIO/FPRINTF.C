/* fprintf function */
#include "xstdio.h"

static void *prout(void *str, const char *buf, size_t n)
	{	/* write to file */
	return (fwrite(buf, 1, n, (FILE *)str) == n ? str : NULL);
	}

int (fprintf)(FILE *str, const char *fmt, ...)
	{	/* print formatted to stream */
	int ans;
	va_list ap;

	va_start(ap, fmt);
	ans = _Printf(&prout, str, fmt, ap);
	va_end(ap);
	return (ans);
	}
