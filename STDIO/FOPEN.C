/* fopen function */
#include <stdlib.h>
#include "xstdio.h"

FILE *(fopen)(const char *name, const char *mods)
	{	/* open a file */
	FILE *str;
	size_t i;

	for (i = 0; i < FOPEN_MAX; ++i)
		if (_Files[i] == NULL)
			{	/* setup empty _Files[i] */
			str = (FILE *)malloc(sizeof (FILE));
			if (str == NULL)
				return (NULL);
			_Files[i] = str;
			str->_Mode = _MALFIL;
			break;
			}
		else if (_Files[i]->_Mode == 0)
			{	/* setup preallocated _Files[i] */
			str = _Files[i];
			break;
			}
	if (FOPEN_MAX <= i)
		return (NULL);
	return (_Foprep(name, mods, str));
	}
