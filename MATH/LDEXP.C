/* ldexp function */
#include "xmath.h"

double (ldexp)(double x, int xexp)
	{	/* compute ldexp(x, xexp) */
	switch (_Dtest(&x))
		{	/* test for special codes */
	case NAN:
		errno = EDOM;
		break;
	case INF:
		errno = ERANGE;
		break;
	case 0:
		break;
	default:	/* finite */
		if (0 <= _Dscale(&x, xexp))
			errno = ERANGE;
		}
	return (x);
	}
