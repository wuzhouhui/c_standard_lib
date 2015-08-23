/* ftell function */
#include "xstdio.h"

long (ftell)(FILE *str)
	{	/* get seek offset for stream */
	return (_Fgpos(str, NULL));
	}
