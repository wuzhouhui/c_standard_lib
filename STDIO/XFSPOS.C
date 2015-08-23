/* _Fspos function -- Turbo C++ version */
#include <errno.h>
#include "xstdio.h"

		/* macros */
#define NNL(str, m1, m2)	((str)->_Mode & _MBIN ? 0 \
	: _Nnl((str)->m1, (str)->m2))

long lseek(int, long, int);	/* Turbo C++ system call */
int _Nnl(const unsigned char *, const unsigned char *);

int _Fspos(FILE *str, const fpos_t *ptr, long loff, int way)
	{	/* position a file */
	if (!(str->_Mode & (_MOPENR|_MOPENW)) || fflush(str))
		{	/* not-open or write error */
		errno = EFPOS;
		return (EOF);
		}
	if (ptr)
		loff += ptr->_Off;	/* fsetpos */
	if (way == SEEK_CUR && str->_Mode & _MREAD)
		loff -= str->_Nback
			? str->_Rsave - str->_Next + str->_Nback
				+ NNL(str, _Next, _Rsave)
			: str->_Rend - str->_Next + NNL(str, _Next, _Rend);
	if (way == SEEK_CUR && loff != 0
		|| way != SEEK_SET || loff != -1)
		loff = lseek(str->_Handle, loff, way);
	if (loff == -1)
		{	/* request failed */
		errno = EFPOS;
		return (EOF);
		}
	else
		{	/* success */
		if (str->_Mode & (_MREAD|_MWRITE))
			{	/* empty buffer */
			str->_Next = str->_Buf;
			str->_Rend = str->_Buf;
			str->_Wend = str->_Buf;
			str->_Nback = 0;
			}
		str->_Mode &= ~(_MEOF|_MREAD|_MWRITE);
		return (0);
		}
	}
