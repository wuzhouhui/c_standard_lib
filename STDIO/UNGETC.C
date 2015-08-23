/* ungetc function */
#include "xstdio.h"

int (ungetc)(int c, FILE *str)
	{	/* push character back on stream */
	if (c == EOF
		|| sizeof (str->_Back) <= str->_Nback
		|| (str->_Mode & (_MOPENR|_MWRITE)) != _MOPENR)
		return (EOF);
	str->_Mode = str->_Mode & ~_MEOF | _MREAD;
	if (str->_Nback == 0)
		{	/* disable buffering */
		str->_Rsave = str->_Rend;
		str->_Rend = str->_Buf;
		}
	str->_Back[str->_Nback++] = c;
	return ((unsigned char)c);
	}
