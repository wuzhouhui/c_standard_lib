/* iscntrl function */
#include <ctype.h>

int (iscntrl)(int c)
	{	/* test for control character */
	return (_Ctype[c] & (_BB|_CN));
	}
