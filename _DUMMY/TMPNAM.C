/* tmpnam function -- dummy version */
#include <string.h>
#include "xstdio.h"

char *(tmpnam)(char *s)
	{	/* create a temporary file name */
	int i;
	char *p;
	unsigned short t;
	static char buf[L_tmpnam];
	static unsigned short seed = 0;

	if (s == NULL)
		s = buf;
	++seed;
	strcpy(s, "ctm");
	i = 5;
	p = s + strlen(s) + i;
	strcpy(p, ".tmp");
	for (t = seed; 0 <= --i; t >>= 3)
		*--p = '0' + (t & 07);
	return (s);
	}
