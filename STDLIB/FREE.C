/* free function */
#include "xalloc.h"

void (free)(void *ptr)
	{	/* free an allocated data object */
	_Cell *q;

	if (ptr == NULL)
		return;
	q = (_Cell *)((char *)ptr - CELL_OFF);
	if (q->_Size < SIZE_CELL || (q->_Size & _MEMBND) != 0)
		return;	/* erroneous call */
	_Aldata._Plast = 0;
	if (_Aldata._Head == NULL || q < _Aldata._Head)
		{	/* insert at head of list */
		q->_Next = _Aldata._Head;
		_Aldata._Head = q;
		}
	else
		{	/* scan for insertion point */
		_Cell *qp;
		char *qpp;

		for (qp = _Aldata._Head;
			qp->_Next != NULL && qp->_Next < q; )
			qp = qp->_Next;
		qpp = (char *)qp + CELL_OFF + qp->_Size;
		if ((char *)q < qpp)
			return;	/* erroneous call */
		else if ((char *)q == qpp)
			{	/* merge qp and q */
			qp->_Size += CELL_OFF + q->_Size;
			q = qp;
			}
		else
			{	/* splice q after qp and resume scan with q */
			q->_Next = qp->_Next;
			qp->_Next = q;
			_Aldata._Plast = &qp->_Next;
			}
		}
	if (q->_Next
		&& (char *)q + CELL_OFF + q->_Size == (char *)q->_Next)
		{	/* merge q and q->_Next */
		q->_Size += CELL_OFF + q->_Next->_Size;
		q->_Next = q->_Next->_Next;
		}
	}
