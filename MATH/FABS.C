/* fabs function */
#include "xmath.h"

double (fabs)(double x)
	{	/* compute fabs */
	switch (_Dtest(&x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		return (x);
	case INF:
		errno = ERANGE;
		return (_Inf._D);
	case 0:
		return (0.0);
	default:	/* finite */
		return (x < 0.0 ? -x : x);
		}
	}
