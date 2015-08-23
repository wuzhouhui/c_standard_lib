/* _Getmem function -- UNIX version */
#include "xalloc.h"

		/* UNIX system call */
void *sbrk(int);

void *_Getmem(size_t size)
	{	/* allocate raw storage */
	void *p;
	int isize = size;

	return (isize <= 0 || (p = sbrk(isize)) == (void *)-1
		? NULL : p);
	}
