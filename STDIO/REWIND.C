/* rewind function */
#include "xstdio.h"

void (rewind)(FILE *str)
	{	/* rewind stream */
	_Fspos(str, NULL, 0L, SEEK_SET);
	str->_Mode &= ~_MERR;
	}
