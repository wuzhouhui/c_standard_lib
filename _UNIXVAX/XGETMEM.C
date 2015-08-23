/* _Getmem function -- UNIX version */
#include "xalloc.h"

		/* UNIX system call */
void *_Sbrk(int);

void *_Getmem(size_t size)
	{	/* allocate raw storage */
	void *p;
	int isize = size;

	return (isize <= 0 || (p = _Sbrk(isize)) == (void *)-1
		? NULL : p);
	}
