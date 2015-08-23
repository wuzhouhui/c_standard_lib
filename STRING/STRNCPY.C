/* strncpy function */
#include <string.h>

char *(strncpy)(char *s1, const char *s2, size_t n)
	{	/* copy char s2[max n] to s1[n] */
	char *s;

	for (s = s1; 0 < n && *s2 != '\0'; --n)
		*s++ = *s2++;	/* copy at most n chars from s2[] */
	for (; 0 < n; --n)
		*s++ = '\0';
	return (s1);
	}
