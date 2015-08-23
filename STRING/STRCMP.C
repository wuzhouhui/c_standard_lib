/* strcmp function */
#include <string.h>

int (strcmp)(const char *s1, const char *s2)
	{	/* compare unsigned char s1[], s2[] */
	for (; *s1 == *s2; ++s1, ++s2)
		if (*s1 == '\0')
			return (0);
	return (*(unsigned char *)s1 < *(unsigned char *)s2
		? -1 : +1);
	}
