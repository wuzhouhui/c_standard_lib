/* gets function */
#include <string.h>
#include "xstdio.h"

char *(gets)(char *buf)
	{	/* get a line from stdio */
	unsigned char *s;

	for (s = (unsigned char *)buf; 0 < stdin->_Nback; )
		{	/* deliver pushed back chars */
		*s = stdin->_Back[--stdin->_Nback];
		if (stdin->_Nback == 0)
			stdin->_Rend = stdin->_Rsave;
		if (*s++ == '\n')
			{	/* terminate full line */
			s[-1] = '\0';
			return (buf);
			}
		}
	for (; ; )
		{	/* ensure chars in buffer */
		if (stdin->_Next < stdin->_Rend)
			;
		else if (_Frprep(stdin) < 0)
			return (NULL);
		else if (stdin->_Mode & _MEOF)
			break;
		 {	/* deliver as many as possible */
		unsigned char *s1
			= (unsigned char *)memchr(stdin->_Next, '\n',
			stdin->_Rend - stdin->_Next);
		size_t m = (s1 ? s1 + 1 : stdin->_Rend)
			- stdin->_Next;

		memcpy(s, stdin->_Next, m);
		s += m; stdin->_Next += m;
		if (s1)
			{	/* terminate full line */
			s[-1] = '\0';
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
