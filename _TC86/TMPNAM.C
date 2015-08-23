/* tmpnam function -- Turbo C++ version */
#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

#if L_tmpnam < 13
#error BAD ASSUMPTION ABOUT L_tmpnam
#endif

char *(tmpnam)(char *s)
	{	/* create a temporary file name */
	char *p;
	int i;
	unsigned short t;
	static char buf[L_tmpnam];
	static char *root = NULL;
	static unsigned short seed = 0;

	if (s == NULL)
		s = buf;
	if (root)
		;
	else if ((p = getenv("TEMP")) == NULL
		|| L_tmpnam < strlen(p) + 14
		|| (root = (char *)malloc(strlen(p) + 5)) == NULL)
		root = "ctm";
	else
		{	/* setup root directory */
		strcpy(root, p);
		strcat(root, "/ctm");
		}
	++seed;
	strcpy(s, root);
	i = 5;
	p = s + strlen(s) + i;
	strcpy(p, ".tmp");
	for (t = seed; 0 <= --i; t >>= 3)
		*--p = '0' + (t & 07);
	return (s);
	}
