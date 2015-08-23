/* difftime function */
#include <time.h>

double (difftime)(time_t t1, time_t t0)
	{	/* compute difference in times */
	t0 -= _TBIAS, t1 -= _TBIAS;
	return (t0 <= t1 ? (double)(t1 - t0) : -(double)(t0 - t1));
	}
