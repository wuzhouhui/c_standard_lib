/* getc function */
#include "xstdio.h"

int (getc)(FILE *str)
	{	/* get a character from stream */
	return (fgetc(str));
	}
