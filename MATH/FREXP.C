/* frexp function */
#include "xmath.h"

double (frexp)(double x, int *pexp)
	{	/* compute frexp(x, &i) */
	short binexp;

	switch (_Dunscale(&binexp, &x))
		{	/* test for special codes */
	case NAN:
	case INF:
		errno = EDOM;
		*pexp = 0;
		return (x);
	case 0:
		*pexp = 0;
		return (0.0);
	default:	/* finite */
		*pexp = binexp;
		return (x);
		}
	}
