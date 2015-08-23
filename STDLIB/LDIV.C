/* ldiv function */
#include <stdlib.h>

ldiv_t (ldiv)(long numer, long denom)
	{	/* compute long quotient and remainder */
	ldiv_t val;

	val.quot = numer / denom;
	val.rem = numer - denom * val.quot;
	if (val.quot < 0 && 0 < val.rem)
		{	/* fix remainder with wrong sign */
		val.quot += 1;
		val.rem -= denom;
		}
	return (val);
	}
