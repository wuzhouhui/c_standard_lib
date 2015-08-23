/* realloc function */
#include <string.h>
#include "xalloc.h"

void *(realloc)(void *ptr, size_t size)
	{	/* reallocate a data object on the heap */
	_Cell *q;

	if (ptr == NULL)
		return (malloc(size));
	if (size < SIZE_CELL)	/* round up size */
		size = SIZE_CELL;
	else if ((size = (size + _MEMBND) & ~_MEMBND) == 0
		|| size + CELL_OFF < size)
		return (0);
	q = (_Cell *)((char *)ptr - CELL_OFF);
	if (q->_Size < SIZE_CELL || (q->_Size & _MEMBND) != 0)
		return (0);	/* erroneous call */
	if (size + CELL_OFF <= q->_Size - SIZE_CELL)
		{	/* free excess space */
		_Cell *const new_q = (_Cell *)((char *)ptr + size);

		new_q->_Size = q->_Size - CELL_OFF - size;
		q->_Size = size;
		free((char *)new_q + CELL_OFF);
		return (ptr);
		}
	else if (size <= q->_Size)
		return (ptr);	/* leave cell alone */
	else
		{	/* try to buy a larger cell */
		char *const new_p = (char *)malloc(size);

		if (new_p == NULL)
			return (NULL);
		memcpy(new_p, ptr, q->_Size);
		free(ptr);
		return (new_p);
		}
	}
