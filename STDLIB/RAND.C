/* rand function */
#include <stdlib.h>

/* the seed */
unsigned long _Randseed = 1;

int (rand)(void)
	{	/* compute pseudo-random value */
	_Randseed = _Randseed * 1103515245 + 12345;
	return ((unsigned int)(_Randseed >> 16) & RAND_MAX);
	}
