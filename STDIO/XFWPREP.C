/* _Fwprep function */
#include <stdlib.h>
#include "xstdio.h"

int _Fwprep(FILE *str)
	{	/* prepare stream for writing */
	if (str->_Next < str->_Wend)
		return (0);
	else if (str->_Mode & _MWRITE)
		return (fflush(str));
	else if ((str->_Mode & (_MOPENW|_MREAD)) != _MOPENW)
		{	/* can't write after read */
		str->_Mode |= _MERR;
		return (-1);
		}
	if (str->_Buf)
		;
	else if ((str->_Buf = (unsigned char *)malloc(BUFSIZ))
		== NULL)
		{	/* use 1-char _Cbuf */
		str->_Buf = &str->_Cbuf;
		str->_Bend = str->_Buf + 1;
		}
	else
		{	/* use allocated buffer */
		str->_Mode |= _MALBUF;
		str->_Bend = str->_Buf + BUFSIZ;
		}
	str->_Next = str->_Buf;
	str->_Rend = str->_Buf;
	str->_Wend = str->_Bend;
	str->_Mode |= _MWRITE;
	return (0);
	}
