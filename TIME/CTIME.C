/* ctime function */
#include <time.h>

char *(ctime)(const time_t *tod)
	{	/* convert calendar time to local text */
	return (asctime(localtime(tod)));
	}
