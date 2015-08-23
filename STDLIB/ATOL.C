/* atol function */
#include <stdlib.h>

long (atol)(const char *s)
	{	/* convert string to long */
	return ((long)_Stoul(s, NULL, 10));
	}
