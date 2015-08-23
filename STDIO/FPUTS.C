/* fputs function */
#include <string.h>
#include "xstdio.h"

int (fputs)(const char *s, FILE *str)
	{	/* put a string to stream */
	while (*s)
		{	/* ensure room in buffer */
		if (str->_Next < str->_Wend)
			;
		else if (_Fwprep(str) < 0)
			return (EOF);
		 {	/* copy in as many as possible */
		const char *s1 = str->_Mode & _MLBF
			? strchr(s, '\n') : NULL;
		size_t m = s1 ? s1 - s + 1 : strlen(s);
		size_t n;

		n = str->_Wend - str->_Next;
		if (n < m)
			s1 = NULL, m = n;
		memcpy(str->_Next, s, m);
		s += m;
		str->_Next += m;
		if (s1 && fflush(str))
			{	/* fail on error */
			str->_Wend = str->_Buf;
			return (EOF);
			}
		 }
		}
	if (str->_Mode & _MNBF)
		{	/* disable macros and drain */
		str->_Wend = str->_Buf;
		if (fflush(str))
			return (EOF);
		}
	return (0);
	}
