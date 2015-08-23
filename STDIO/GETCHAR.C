/* getchar function */
#include "xstdio.h"

int (getchar)(void)
	{	/* get a character from stdin */
	return (fgetc(stdin));
	}
