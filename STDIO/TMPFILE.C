/* tmpfile function */
#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

FILE *(tmpfile)(void)
	{	/* open a temporary file */
	FILE *str;
	char fn[L_tmpnam], *s;

	if ((str = fopen((const char *)tmpnam(fn), "wb+")) == NULL)
		;
	else if ((s = (char *)malloc(sizeof (fn) + 1)) == NULL)
		fclose(str), str = NULL;
	else
		str->_Tmpnam = strcpy(s, fn);
	return (str);
	}
