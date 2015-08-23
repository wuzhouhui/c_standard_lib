/* isalpha function */
#include <ctype.h>

int (isalpha)(int c)
	{	/* test for alphabetic character */
	return (_Ctype[c] & (_LO|_UP|_XA));
	}
