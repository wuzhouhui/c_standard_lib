/* remove function -- Turbo C++ version */
#include "xstdio.h"

		/* Turbo C++ system call */
int unlink(const char *);

int (remove)(const char *fname)
	{	/* remove a file */
	return (unlink(fname));
	}
