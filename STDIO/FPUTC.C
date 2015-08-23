/* fputc function */
#include "xstdio.h"

int (fputc)(int ci, FILE *str)
	{	/* put a character to stream */
	unsigned char c = ci;

	if (str->_Next < str->_Wend)
		;
	else if (_Fwprep(str) < 0)
		return (EOF);
	*str->_Next++ = c;
	if (str->_Mode & (_MLBF|_MNBF))
		{	/* disable macros and drain */
		str->_Wend = str->_Buf;
		if ((str->_Mode & _MNBF || c == '\n') && fflush(str))
			return (EOF);
		}
	return (c);
	}
