/* isprint function */
#include <ctype.h>

int (isprint)(int c)
	{	/* test for printable character */
	return (_Ctype[c] & (_DI|_LO|_PU|_SP|_UP|_XA));
	}
