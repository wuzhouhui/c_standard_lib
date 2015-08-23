/* div function */
#include <stdlib.h>

div_t (div)(int numer, int denom)
	{	/* compute int quotient and remainder */
	div_t val;

	val.quot = numer / denom;
	val.rem = numer - denom * val.quot;
	if (val.quot < 0 && 0 < val.rem)
		{	/* fix remainder with wrong sign */
		val.quot += 1;
		val.rem -= denom;
		}
	return (val);
	}
