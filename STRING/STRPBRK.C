/* strpbrk function */
#include <string.h>

char *(strpbrk)(const char *s1, const char *s2)
	{	/* find index of first s1[i] that matches any s2[] */
	const char *sc1, *sc2;

	for (sc1 = s1; *sc1 != '\0'; ++sc1)
		for (sc2 = s2; *sc2 != '\0'; ++sc2)
			if (*sc1 == *sc2)
				return ((char *)sc1);
	return (NULL);	/* terminating nulls match */
	}
