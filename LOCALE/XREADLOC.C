/* _Readloc function */
#include <string.h>
#include "xlocale.h"

		/* static data */
static const char kc[] =	/* keyword chars */
	"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

_Locitem *_Readloc(FILE *lf, char *buf, const char **ps)
	{	/*	get a line from locale file */
	for (; ; )
		{	/* loop until EOF or full line */
		size_t n;

		for (buf[0] = ' ', n = 1; ; n -= 2)
			if (fgets(buf + n, MAXLIN - n, lf) == NULL
				|| buf[(n += strlen(buf + n)) - 1] != '\n')
				return (NULL);	/* EOF or line too long */
			else if (n <= 1 || buf[n - 2] != '\\')
				break;	/* continue only if ends in \ */
		buf[n - 1] = '\0';	/* overwrite newline */
		 {	/* look for keyword on line */
		const char *s = _Skip(buf);
		_Locitem *q;
	
		if (0 < (n = strspn(s, kc)))
			for (q = _Loctab; q->_Name; ++q)
				if (strncmp(q->_Name, s, n) == 0
					&& strlen(q->_Name) == n)
					{	/* found a match */
					*ps = _Skip(s + n - 1);
					return (q);
					}
		return (NULL);	/* unknown or missing keyword */
		 }
		}
	}
