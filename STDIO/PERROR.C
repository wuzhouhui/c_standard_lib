/* perror function */
#include <errno.h>
#include <string.h>
#include "xstdio.h"

void (perror)(const char *s)
	{	/* put error string to stderr */
	static char buf[] = {"error #xxx"};

	if (s)
		{	/* put user-supplied prefix */
		fputs(s, stderr);
		fputs(": ", stderr);
		}
	fputs(_Strerror(errno, buf), stderr);
	fputc('\n', stderr);
	}
