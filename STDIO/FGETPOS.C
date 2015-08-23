/* fgetpos function */
#include "xstdio.h"

int (fgetpos)(FILE *str, fpos_t *p)
	{	/* get file position indicator for stream */
	return (_Fgpos(str, p));
	}
