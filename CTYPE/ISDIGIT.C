/* isdigit function */
#include <ctype.h>

int (isdigit)(int c)
	{	/* test for digit */
	return (_Ctype[c] & _DI);
	}
