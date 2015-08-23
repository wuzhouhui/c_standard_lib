/* calloc function */
#include <stdlib.h>
#include <string.h>

void *(calloc)(size_t nelem, size_t size)
	{	/* allocate a data object on the heap and clear it */
	const size_t n = nelem * size;
	char *p = (char *)malloc(n);

	if (p)
		memset(p, '\0', n);
	return (p);
	}
