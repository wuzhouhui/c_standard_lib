/* setbuf function */
#include "xstdio.h"

void (setbuf)(FILE *str, char *buf)
	{	/* set up buffer for a stream */
	setvbuf(str, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
	}
