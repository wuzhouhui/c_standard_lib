/* fwrite function */
#include <string.h>
#include "xstdio.h"

size_t (fwrite)(const void *ptr, size_t size,
	size_t nelem, FILE *str)
	{	/* write to stream from array */
	char *s = (char *)ptr;
	size_t ns = size * nelem;

	if (ns == 0)
		return (0);
	while (0 < ns)
		{	/* ensure room in buffer */
		if (str->_Next < str->_Wend)
			;
		else if (_Fwprep(str) < 0)
			break;
		 {	/* copy in as many as possible */
		char *s1 = str->_Mode & _MLBF
			? (char *)memchr(s, '\n', ns) : NULL;
		size_t m = s1 ? s1 - s + 1 : ns;
		size_t n = str->_Wend - str->_Next;

		if (n < m)
			s1 = NULL, m = n;
		memcpy(str->_Next, s, m);
		s += m, ns -= m;
		str->_Next += m;
		if (s1 && fflush(str))
			{	/* disable macros on failure */
			str->_Wend = str->_Buf;
			break;
			}
		 }
		}
	if (str->_Mode & _MNBF)
		{	/* disable and drain */
		str->_Wend = str->_Buf;
		fflush(str);
		}
	return ((size * nelem - ns) / size);
	}
