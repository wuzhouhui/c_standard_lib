/* islower function */
#include <ctype.h>

int (islower)(int c)
	{	/* test for lowercase character */
	return (_Ctype[c] & _LO);
	}
