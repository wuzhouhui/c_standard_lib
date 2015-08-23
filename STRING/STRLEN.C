/* strlen function */
#include <string.h>

size_t (strlen)(const char *s)
	{	/* find length of s[] */
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		;
	return (sc - s);
	}
