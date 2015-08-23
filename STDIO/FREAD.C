/* fread function */
#include <string.h>
#include "xstdio.h"

size_t (fread)(void *ptr, size_t size, size_t nelem, FILE *str)
	{	/* read into array from stream */
	size_t ns = size * nelem;
	unsigned char *s = (unsigned char *)ptr;

	if (ns == 0)
		return (0);
	if (0 < str->_Nback)
		{	/* deliver pushed back chars */
		for (; 0 < ns && 0 < str->_Nback; --ns)
			*s++ = str->_Back[--str->_Nback];
		if (str->_Nback == 0)
			str->_Rend = str->_Rsave;
		}
	while (0 < ns)
		{	/* ensure chars in buffer */
		if (str->_Next < str->_Rend)
			;
		else if (_Frprep(str) <= 0)
			break;
		 {	/* deliver as many as possible */
		size_t m = str->_Rend - str->_Next;

		if (ns < m)
			m = ns;
		memcpy(s, str->_Next, m);
		s += m, ns -= m;
		str->_Next += m;
		 }
		}
	return ((size * nelem - ns) / size);
	}
