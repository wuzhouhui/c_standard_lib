/* time function -- UNIX version */
#include <time.h>

		/* UNIX system call */
time_t time(time_t *);

time_t (time)(time_t *tod)
	{	/* return calendar time */
	time_t t = time(NULL) + (70*365LU+17)*86400;

	if (tod)
		*tod = t;
	return (t);
	}
