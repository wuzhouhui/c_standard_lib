/* fgets function */
#include <string.h>
#include "xstdio.h"

char *(fgets)(char *buf, int n, FILE *str)
	{	/* get a line from stream */
	unsigned char *s;

	if (n <= 1)
		return (NULL);
	for (s = (unsigned char *)buf; 0 < --n && str->_Nback; )
		{	/* deliver pushed back chars */
		*s = str->_Back[--str->_Nback];
		if (str->_Nback == 0)
			str->_Rend = str->_Rsave;
		if (*s++ == '\n')
			{	/* terminate full line */
			*s = '\0';
			return (buf);
			}
		}
	while (0 < n)
		{	/* ensure buffer has chars */
		if (str->_Next < str->_Rend)
			;
		else if (_Frprep(str) < 0)
			return (NULL);
		else if (str->_Mode & _MEOF)
			break;
		 {	/* copy as many as possible */
		unsigned char *s1 = (unsigned char *)memchr(str->_Next,
			'\n', str->_Rend - str->_Next);
		size_t m = (s1 ? s1 + 1 : str->_Rend) - str->_Next;

		if (n < m)
			s1 = NULL, m = n;
		memcpy(s, str->_Next, m);
		s += m, n -= m;
		str->_Next += m;
		if (s1)
			{	/* terminate full line */
			*s = '\0';
			return (buf);
			}
		 }
		}
	if (s == (unsigned char *)buf)
		return (NULL);
	else
		{	/* terminate partial line */
		*s = '\0';
		return (buf);
		}
	}
