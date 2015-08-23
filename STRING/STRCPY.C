/* strcpy function */
#include <string.h>

char *(strcpy)(char *s1, const char *s2)
	{	/* copy char s2[] to s1[] */
	char *s = s1;

	for (s = s1; (*s++ = *s2++) != '\0'; )
		;
	return (s1);
	}
