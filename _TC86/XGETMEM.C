/* _Getmem function -- Turbo C++ version */
#include "xalloc.h"

		/* Turbo C++ system call */
void *sbrk(int);

void *_Getmem(size_t size)
	{	/* allocate raw storage */
	void *p;
	int isize = size;

	return (isize <= 0 || (p = sbrk(isize)) == (void *)-1
		? NULL : p);
	}
