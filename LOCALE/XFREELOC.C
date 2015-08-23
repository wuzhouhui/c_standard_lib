/* _Freeloc function */
#include "xlocale.h"

void _Freeloc(_Linfo *p)
	{	/* free all storage */
	_Locitem *q;

	for (q = _Loctab; q->_Name; ++q)
		switch (q->_Code)
			{	/* free all pointers */
		case L_STATE:
			 {	/* free all state entries */
			int i;
			unsigned short **pt
				= &ADDR(p, q, unsigned short *);

			for (i = _NSTATE; 0 <= --i; ++pt)
				if (*pt && (*pt)[-1] != 0)
					free(&(*pt)[-1]);
			 }
			break;
		case L_TABLE:
			if (NEWADDR(p, q, short *))
				free(ADDR(p, q, short *) - 1);
			break;
		case L_GSTRING:
		case L_NAME:
		case L_STRING:
			if (NEWADDR(p, q, char *))
				free(ADDR(p, q, char *));
			}
	}
