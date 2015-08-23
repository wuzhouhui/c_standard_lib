/* isgraph function */
#include <ctype.h>

int (isgraph)(int c)
	{	/* test for graphic character */
	return (_Ctype[c] & (_DI|_LO|_PU|_UP|_XA));
	}
