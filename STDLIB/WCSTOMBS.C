/* wcstombs function */
#include <limits.h>
#include <string.h>
#include <stdlib.h>

size_t (wcstombs)(char *s, const wchar_t *wcs, size_t n)
	{	/* translate wide char string to multibyte string */
	char *sc;
	char state = {0};
	size_t i;

	for (sc = s; 0 < n; n -= i, ++wcs)
		{	/* translate another wide character */
		if (MB_CUR_MAX <= n)
			{	/* copy directly */
			if ((i = _Wctomb(sc, *wcs, &state)) <= 0)
				return (-1);
			}
		else
			{	/* copy into local buffer */
			char buf[MB_LEN_MAX];

			if ((i = _Wctomb(buf, *wcs, &state)) <= 0)
				return (-1);
			else if (i <= n)
				memcpy(sc, buf, i);
			else
				{	/* won't all fit */
				memcpy(sc, buf, n);
				return (sc - s + n);
				}
			}
		sc += i;
		if (sc[-1] == '\0')
			return (sc - s - 1);
		}
	return (sc - s);
	}
