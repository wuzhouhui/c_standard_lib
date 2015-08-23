/* mbtowc function */
#include <stdlib.h>

		/* static data */
_Mbsave _Mbxtowc = {0};

int (mbtowc)(wchar_t *pwc, const char *s, size_t n)
	{	/*	determine next multibyte code */
	return (_Mbtowc(pwc, s, n, &_Mbxtowc));
	}
