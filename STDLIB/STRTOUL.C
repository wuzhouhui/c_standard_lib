/* strtoul function */
#include <stdlib.h>

unsigned long (strtoul)(const char *s, char **endptr, int base)
	{	/* convert string to unsigned long, with checking */
	return (_Stoul(s, endptr, base));
	}
