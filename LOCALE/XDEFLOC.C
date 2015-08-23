/* _Defloc function */
#include <string.h>
#include "xlocale.h"

const char *_Defloc(void)
	{	/* find name of default locale */
	char *s;
	static char *defname = NULL;

	if (defname)
		;
	else if ((s = getenv("LOCALE")) != NULL
		&& (defname = (char *)malloc(strlen(s) + 1)) != NULL)
		strcpy(defname, s);
	else
		defname = "C";
	return (defname);
	}
