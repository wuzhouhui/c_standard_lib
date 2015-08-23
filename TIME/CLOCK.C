/* clock function -- simple version */
#include <time.h>

clock_t (clock)(void)
	{	/* return CPU time */
	return ((clock_t)time(NULL));
	}
