/* localtime function */
#include <stdlib.h>
#include "xtime.h"

time_t _Tzoff(void)
	{	/* determine local time offset */
	static const char *oldzone = NULL;
	static long tzoff = 0;
	static const long maxtz = 60*13;

	if (oldzone != _Times._Tzone)
		{	/* determine time zone offset (East is +) */
		const char *p, *pe;
		int n;

		if (_Times._Tzone[0] == '\0')
			_Times._Tzone = _Getzone();
		p = _Gettime(_Times._Tzone, 2, &n);
		tzoff = strtol(p, (char **)&pe, 10);
		if (pe - p != n
			|| tzoff <= -maxtz || maxtz <= tzoff)
			tzoff = 0;
		oldzone = _Times._Tzone;
		}
	return (-tzoff * 60);
	}

struct tm *(localtime)(const time_t *tod)
	{	/* convert to local time structure */
	return (_Ttotm(NULL, *tod + _Tzoff(), -1));
	}
