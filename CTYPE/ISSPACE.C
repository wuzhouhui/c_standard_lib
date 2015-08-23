/* isspace function */
#include <ctype.h>

int (isspace)(int c)
	{	/* test for spacing character */
	return (_Ctype[c] & (_CN|_SP|_XS));
	}
