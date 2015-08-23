/* isupper function */
#include <ctype.h>

int (isupper)(int c)
	{	/* test for uppercase character */
	return (_Ctype[c] & _UP);
	}
