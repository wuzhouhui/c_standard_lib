/* strtod function */
#include <stdlib.h>

double (strtod)(const char *s, char **endptr)
	{	/* convert string to double, with checking */
	return (_Stod(s, endptr));
	}
