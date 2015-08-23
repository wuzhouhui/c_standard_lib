/* freopen function */
#include <stdlib.h>
#include "xstdio.h"

FILE *(freopen)(const char *name, const char *mods, FILE *str)
	{	/* reopen a file */
	unsigned short mode = str->_Mode & _MALFIL;

	str->_Mode &= ~_MALFIL;
	fclose(str);
	str->_Mode = mode;
	return (_Foprep(name, mods, str));
	}
