/* strxfrm function */
#include "xstrxfrm.h"

size_t (strxfrm)(char *s1, const char *s2, size_t n)
	{	/* transform s2[] to s1[] by locale-dependent rule */
	size_t nx = 0;
	const unsigned char *s = (const unsigned char *)s2;
	_Cosave state = {0};

	while (nx < n)
		{	/* translate and deliver */
		size_t i = _Strxfrm(s1, &s, n - nx, &state);

		s1 += i, nx += i;
		if (0 < i && s1[-1] == '\0')
			return (nx - 1);
		else if (*s == '\0')
			s = (const unsigned char *)s2;	/* rescan */
		}
	for (; ; )
		{	/* translate and count */
		char buf[32];
		size_t i = _Strxfrm(buf, &s, sizeof (buf), &state);

		nx += i;
		if (0 < i && buf[i - 1] == '\0')
			return (nx - 1);
		else if (*s == '\0')
			s = (const unsigned char *)s2;	/* rescan */
		}
	}
