/* atof function */
#include <stdlib.h>

double (atof)(const char *s)
	{	/* convert string to double */
	return (_Stod(s, NULL));
	}
