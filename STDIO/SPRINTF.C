/* sprintf function */
#include <string.h>
#include "xstdio.h"

static void *prout(void *s, const char *buf, size_t n)
	{	/* write to string */
	return ((char *)memcpy(s, buf, n) + n);
	}

int (sprintf)(char *s, const char *fmt, ...)
	{	/* print formatted to string */
	int ans;
	va_list ap;

	va_start(ap, fmt);
	ans = _Printf(&prout, s, fmt, ap);
	if (0 <= ans)
		s[ans] = '\0';
	va_end(ap);
	return (ans);
	}
