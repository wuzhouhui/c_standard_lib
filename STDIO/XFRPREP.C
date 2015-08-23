/* _Frprep function */
#include <stdlib.h>
#include "xstdio.h"
#include "yfuns.h"

int _Frprep(FILE *str)
	{	/* prepare stream for reading */
	if (str->_Next < str->_Rend)
		return (1);
	else if (str->_Mode & _MEOF)
		return (0);
	else if ((str->_Mode & (_MOPENR|_MWRITE)) != _MOPENR)
		{	/*can't read after write */
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
		{	/* set up allocated buffer */
		str->_Mode |= _MALBUF;
		str->_Bend = str->_Buf + BUFSIZ;
		}
	str->_Next = str->_Buf;
	str->_Rend = str->_Buf;
	str->_Wend = str->_Buf;
	 {	/* try to read into buffer */
	int n = _Fread(str, str->_Buf, str->_Bend - str->_Buf);

	if (n < 0)
		{	/* report error and fail */
		str->_Mode |= _MERR;
		return (-1);
		}
	else if (n == 0)
		{	/* report end of file */
		str->_Mode = (str->_Mode & ~_MREAD) | _MEOF;
		return (0);
		}
	else
		{	/* set up data read */
		str->_Mode |= _MREAD;
		str->_Rend += n;
		return (1);
		}
	 }
	}
