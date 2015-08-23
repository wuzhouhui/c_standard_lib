/* rename function -- UNIX version */
#include "xstdio.h"

		/* UNIX system calls */
int link(const char *, const char *);
int unlink(const char *);

int (rename)(const char *oldnm, const char *newnm)
	{	/* rename a file */
	return (link(oldnm, newnm) ? -1 : unlink(oldnm));
	}
