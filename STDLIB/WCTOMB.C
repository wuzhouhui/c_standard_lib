/* wctomb function */
#include <stdlib.h>

		/* static data */
char _Wcxtomb = {0};

int (wctomb)(char *s, wchar_t wchar)
	{	/* translate wide character to multibyte string */
	return (_Wctomb(s, wchar, &_Wcxtomb));
	}
