/* setvbuf function */
#include <limits.h>
#include <stdlib.h>
#include "xstdio.h"

int (setvbuf)(FILE *str, char *abuf, int smode, size_t size)
	{	/* set up buffer for a stream */
	int mode;
	unsigned char *buf = (unsigned char *)abuf;

	if (str->_Mode & (_MREAD|_MWRITE))
		return (-1);
	mode = smode == _IOFBF ? 0
		: smode == _IOLBF ? _MLBF
		: smode == _IONBF ? _MNBF : -1;
	if (mode == -1)
		return (-1);
	if (size == 0)
		buf = &str->_Cbuf, size = 1;
	else if (INT_MAX < size)
		size = INT_MAX;
	if (buf)
		;
	else if ((buf = (unsigned char *)malloc(size)) == NULL)
		return (-1);
	else
		mode |= _MALBUF;
	if (str->_Mode & _MALBUF)
		free(str->_Buf), str->_Mode &= ~_MALBUF;
	str->_Mode |= mode;
	str->_Buf = buf;
	str->_Bend = buf + size;
	str->_Next = buf;
	str->_Rend = buf;
	str->_Wend = buf;
	return (0);
	}
