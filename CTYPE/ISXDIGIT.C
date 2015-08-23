/* isxdigit function */
#include <ctype.h>

int (isxdigit)(int c)
	{	/* test for hexadecimal digit */
	return (_Ctype[c] & _XD);
	}
