/* getenv function -- in-memory version */
#include <stdlib.h>
#include <string.h>
#include "yfuns.h"

char *(getenv)(const char *name)
	{	/* search environment list for named entry */
	const char *s;
	size_t n = strlen(name);

	for (s = _Envp; *s; s += strlen(s) + 1)
		{	/* look for name match */
		if (!strncmp(s, name, n) && s[n] == '=')
			return ((char *)&s[n + 1]);
		}
	return (NULL);
	}
