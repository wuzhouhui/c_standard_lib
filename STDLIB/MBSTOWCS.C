/* mbstowcs function */
#include <stdlib.h>

size_t (mbstowcs)(wchar_t *wcs, const char *s, size_t n)
	{	/* translate multibyte string to wide char string */
	int i;
	wchar_t *pwc;
	_Mbsave state = {0};

	for (pwc = wcs; 0 < n; ++pwc, --n)
		{	/* make another wide character */
		i = _Mbtowc(pwc, s, MB_CUR_MAX, &state);
		if (i == -1)
			return (-1);
		else if (i == 0 || *pwc == 0)
			return (pwc - wcs);
		s += i;
		}
	return (pwc - wcs);
	}
