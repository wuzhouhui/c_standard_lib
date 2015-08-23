/* _Fgpos function -- UNIX version */
#include <errno.h>
#include "xstdio.h"

		/* UNIX system call */
long lseek(int, long, int);

long _Fgpos(FILE *str, fpos_t *ptr)
	{	/* get file position */
	long loff = lseek(str->_Handle, 0L, 1);

	if (loff == -1)
		{	/* query failed */
		errno = EFPOS;
		return (EOF);
		}
	if (str->_Mode & _MWRITE)
		loff += str->_Next - str->_Buf;
	else if (str->_Mode & _MREAD)
		loff -= str->_Nback
			? str->_Rsave - str->_Next + str->_Nback
			: str->_Rend - str->_Next;
	if (ptr == NULL)
		return (loff);	/* ftell */
	else
		{	/* fgetpos */
		ptr->_Off = loff;
		return (0);
		}
	}
