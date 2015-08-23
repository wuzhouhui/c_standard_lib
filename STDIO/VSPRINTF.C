/* vsprintf function */
#include <string.h>
#include "xstdio.h"

static void *prout(void *s, const char *buf, size_t n)
	{	/* write to string */
	return ((char *)memcpy(s, buf, n) + n);
	}

int (vsprintf)(char *s, const char *fmt, char *ap)
	{	/* print formatted to string from arg list */
	int ans = _Printf(&prout, s, fmt, ap);

	if (0 <= ans)
		s[ans] = '\0';
	return (ans);
	}
