/* fclose function */
#include <stdlib.h>
#include "xstdio.h"
#include "yfuns.h"

int (fclose)(FILE *str)
	{	/* close a stream */
	int alfil = str->_Mode & _MALFIL;
	int stat = fflush(str);

	if (str->_Mode & _MALBUF)
		free(str->_Buf);
	str->_Buf = NULL;
	if (0 <= str->_Handle && _Fclose(str))
		stat = EOF;
	if (str->_Tmpnam)
		{	/* remove temp file */
		if (remove(str->_Tmpnam))
			stat = EOF;
		free(str->_Tmpnam), str->_Tmpnam = NULL;
		}
	str->_Mode = 0;
	str->_Next = &str->_Cbuf;
	str->_Rend = &str->_Cbuf;
	str->_Wend = &str->_Cbuf;
	str->_Nback = 0;
	if (alfil)
		{	/* find _Files[i] entry and free */
		size_t i;

		for (i = 0; i < FOPEN_MAX; ++i)
			if (_Files[i] == str)
				{	/* found entry */
				_Files[i] = NULL;
				break;
				}
		free(str);
		}
	return (stat);
	}
