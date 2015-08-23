/* _Fgpos function -- Turbo C++ version */
#include <errno.h>
#include "xstdio.h"

		/* macros */
#define NNL(str, m1, m2)	((str)->_Mode & _MBIN ? 0 \
	: _Nnl((str)->m1, (str)->m2))

long lseek(int, long, int);	/* Turbo C++ system call */

int _Nnl(const unsigned char *p1, const unsigned char *p2)
	{	/* count newlines in a buffer */
	int n;

	for (n = 0; p1 < p2; ++p1)
		if (*p1 == '\n')
			++n;
	return (n);
	}

long _Fgpos(FILE *str, fpos_t *ptr)
	{	/* get file position */
	long loff = lseek(str->_Handle, 0L, 1);

	if (!(str->_Mode & (_MOPENR|_MOPENW)) || loff == -1)
		{	/* query failed */
		errno = EFPOS;
		return (EOF);
		}
	if (str->_Mode & _MWRITE)
		loff += str->_Next - str->_Buf + NNL(str, _Buf, _Next);
	else if (str->_Mode & _MREAD)
		loff -= str->_Nback
			? str->_Rsave - str->_Next + str->_Nback
				+ NNL(str, _Next, _Rsave)
			: str->_Rend - str->_Next + NNL(str, _Next, _Rend);
	if (ptr == NULL)
		return (loff);	/* ftell */
	else
		{	/* fgetpos */
		((fpos_t *)ptr)->_Off = loff;
		return (0);
		}
	}
