/* rename function -- UNIX version */
#include "xstdio.h"

		/* UNIX system calls */
int _Link(const char *, const char *);
int _Unlink(const char *);

int (rename)(const char *oldnm, const char *newnm)
	{	/* rename a file */
	return (_Link(oldnm, newnm) ? -1 : _Unlink(oldnm));
	}
