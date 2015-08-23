/* gmtime function */
#include "xtime.h"

struct tm *(gmtime)(const time_t *tod)
	{	/* convert to Greenwich Mean Time (UTC) */
	return (_Ttotm(NULL, *tod, 0));
	}
