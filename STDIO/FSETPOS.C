/* fsetpos function */
#include "xstdio.h"

int (fsetpos)(FILE *str, const fpos_t *p)
	{	/* set file position indicator for stream */
	return (_Fspos(str, p, 0L, SEEK_SET));
	}
