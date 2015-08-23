/* putc function */
#include "xstdio.h"

int (putc)(int c, FILE *str)
	{	/* put character to stream */
	return (fputc(c, str));
	}
