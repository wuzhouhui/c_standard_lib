/* strncat function */
#include <string.h>

char *(strncat)(char *s1, const char *s2, size_t n)
	{	/* copy char s2[max n] to end of s1[] */
	char *s;

	for (s = s1; *s != '\0'; ++s)
		;	/* find end of s1[] */
	for (; 0 < n && *s2 != '\0'; --n)
		*s++ = *s2++;	/* copy at most n chars from s2[] */
	*s = '\0';
	return (s1);
	}
