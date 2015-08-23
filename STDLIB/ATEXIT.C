/* atexit function */
#include <stdlib.h>

		/* external declarations */
extern void (*_Atfuns[])(void);
extern size_t _Atcount;

int (atexit)(void (*func)(void))
	{	/* function to call at exit */
	if (_Atcount == 0)
		return (-1);	/* list is full */
	_Atfuns[--_Atcount] = func;
	return (0);
	}
