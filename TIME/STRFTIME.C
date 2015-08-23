/* strftime function */
#include "xtime.h"

size_t (strftime)(char *s, size_t n, const char *fmt,
	const struct tm *t)
	{	/* format time to string */
	return (_Strftime(s, n, fmt, t, &_Times));
	}
