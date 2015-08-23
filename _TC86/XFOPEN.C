/* _Fopen function -- Turbo C++ version */
#include <assert.h>
#include "xstdio.h"

		/* Turbo C++ system call */
int open(const char *, unsigned int, unsigned int);

int _Fopen(const char *path, unsigned int smode,
	const char *mods)
	{	/* open a file */
	unsigned int acc;
	static const unsigned int rwacc[] = { 0, 1, 2, 4};

	assert((_MOPENR|_MOPENW) == 0x03);
	acc = rwacc[smode & 0x03];
	if (smode & _MOPENA)
		acc |= 0x0800;
	if (smode & _MTRUNC)
		acc |= 0x0200;
	if (smode & _MCREAT)
		acc |= 0x0100;
	if (smode & _MBIN)
		acc |= 0x8000;
	else
		acc |= 0x4000;
	return (open(path, acc, 0x180));
	}
