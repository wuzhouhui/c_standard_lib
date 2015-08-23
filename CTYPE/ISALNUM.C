/* isalnum function */
#include <ctype.h>

int (isalnum)(int c)
	{	/* test for alphanumeric character */
	return (_Ctype[c] & (_DI|_LO|_UP|_XA));
	}
