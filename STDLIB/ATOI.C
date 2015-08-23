/* atoi function */
#include <stdlib.h>

int (atoi)(const char *s)
	{	/* convert string to int */
	return ((int)_Stoul(s, NULL, 10));
	}
