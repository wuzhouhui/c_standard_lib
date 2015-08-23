/* strchr function */
#include <string.h>

char *(strchr)(const char *s, int c)
	{	/* find first occurrence of c in char s[] */
	const char ch = c;

	for (; *s != ch; ++s)
		if (*s == '\0')
			return (NULL);
	return ((char *)s);
	}
