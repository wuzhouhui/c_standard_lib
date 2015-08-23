/* _Putfld function */
#include <string.h>
#include "xstdio.h"

		/* macros */
#if _DLONG
#define LDSIGN(x)	\
	(((unsigned short *)&(x))[_D0 ? 4 : 0] & 0x8000)
#else
#define LDSIGN(x)	(((unsigned short *)&(x))[_D0] & 0x8000)
#endif

void _Putfld(_Pft *px, va_list *pap, char code, char *ac)
	{	/* convert a field for _Printf */
	px->n0 = px->nz0 = px->n1 = px->nz1 = px->n2 = px->nz2 = 0;
	switch (code)
		{	/* switch on conversion specifier */
	case 'c':	/* convert a single character */
		ac[px->n0++] = va_arg(*pap, int);
		break;
	case 'd': case 'i':	/* convert a signed decimal integer */
		px->v.li = px->qual == 'l' ?
			va_arg(*pap, long) : va_arg(*pap, int);
		if (px->qual == 'h')
			px->v.li = (short)px->v.li;
		if (px->v.li < 0)	/* negate safely in _Litob */
			ac[px->n0++] = '-';
		else if (px->flags & _FPL)
			ac[px->n0++] = '+';
		else if (px->flags & _FSP)
			ac[px->n0++] = ' ';
		px->s = &ac[px->n0];
		_Litob(px, code);
		break;
	case 'o': case 'u':
	case 'x': case 'X':	/* convert unsigned */
		px->v.li = px->qual == 'l' ?
			va_arg(*pap, long) : va_arg(*pap, int);
		if (px->qual == 'h')
			px->v.li = (unsigned short)px->v.li;
		else if (px->qual == '\0')
			px->v.li = (unsigned int)px->v.li;
		if (px->flags & _FNO && px->v.li != 0)
			{	/* indicate base with prefix */
			ac[px->n0++] = '0';
			if (code == 'x' || code == 'X')
				ac[px->n0++] = code;
			}
		px->s = &ac[px->n0];
		_Litob(px, code);
		break;
	case 'e': case 'E': case 'f':	/* convert floating */
	case 'g': case 'G':
		px->v.ld = px->qual == 'L' ?
			va_arg(*pap, long double) : va_arg(*pap, double);
		if (LDSIGN(px->v.ld))
			ac[px->n0++] = '-';
		else if (px->flags & _FPL)
			ac[px->n0++] = '+';
		else if (px->flags & _FSP)
			ac[px->n0++] = ' ';
		px->s = &ac[px->n0];
		_Ldtob(px, code);
		break;
	case 'n':	/* return output count */
		if (px->qual == 'h')
			*va_arg(*pap, short *) = px->nchar;
		else if (px->qual != 'l')
			*va_arg(*pap, int *) = px->nchar;
		else
			*va_arg(*pap, long *) = px->nchar;
		break;
	case 'p':	/* convert a pointer, hex long version */
		px->v.li = (long)va_arg(*pap, void *);
		px->s = &ac[px->n0];
		_Litob(px, 'x');
		break;
	case 's':	/* convert a string */
		px->s = va_arg(*pap, char *);
		px->n1 = strlen(px->s);
		if (0 <= px->prec && px->prec < px->n1)
			px->n1 = px->prec;
		break;
	case '%':	/* put a '%' */
		ac[px->n0++] = '%';
		break;
	default:	/* undefined specifier, print it out */
		ac[px->n0++] = code;
		}
	}
