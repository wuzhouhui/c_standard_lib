/* ispunct function */
#include <ctype.h>

int (ispunct)(int c)
	{	/* test for punctuation character */
	return (_Ctype[c] & _PU);
	}
