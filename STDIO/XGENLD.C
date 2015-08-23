/* _Genld function */
#include <locale.h>
#include <string.h>
#include "xstdio.h"

void _Genld(_Pft *px, char code, char *p, short nsig,
	short xexp)
	{	/* generate long double text */
	const char point = localeconv()->decimal_point[0];

	if (nsig <= 0)
		nsig = 1, p = "0";
	if (code == 'f' || (code == 'g' || code == 'G')
		&& -4 <= xexp && xexp < px->prec)
		{	/* 'f' format */
		++xexp;	/* change to leading digit count */
		if (code != 'f')
			{	/* fixup for 'g' */
			if (!(px->flags & _FNO) && nsig < px->prec)
				px->prec = nsig;
			if ((px->prec -= xexp) < 0)
				px->prec = 0;
			}
		if (xexp <= 0)
			{	/* digits only to right of point */
			px->s[px->n1++] = '0';
			if (0 < px->prec || px->flags & _FNO)
				px->s[px->n1++] = point;
			if (px->prec < -xexp)
				xexp = -px->prec;
			px->nz1 = -xexp;
			px->prec += xexp;
			if (px->prec < nsig)
				nsig = px->prec;
			memcpy(&px->s[px->n1], p, px->n2 = nsig);
			px->nz2 = px->prec - nsig;
			}
		else if (nsig < xexp)
			{	/* zeros before point */
			memcpy(&px->s[px->n1], p, nsig);
			px->n1 += nsig;
			px->nz1 = xexp - nsig;
			if (0 < px->prec || px->flags & _FNO)
				px->s[px->n1] = point, ++px->n2;
			px->nz2 = px->prec;
			}
		else
			{	/* enough digits before point */
			memcpy(&px->s[px->n1], p, xexp);
			px->n1 += xexp;
			nsig -= xexp;
			if (0 < px->prec || px->flags & _FNO)
				px->s[px->n1++] = point;
			if (px->prec < nsig)
				nsig = px->prec;
			memcpy(&px->s[px->n1], p + xexp, nsig);
			px->n1 += nsig;
			px->nz1 = px->prec - nsig;
			}
		}
	else
		{	/* 'e' format */
		if (code == 'g' || code == 'G')
			{	/* fixup for 'g' */
			if (nsig < px->prec && !(px->flags & _FNO))
				px->prec = nsig;
			if (--px->prec < 0)
				px->prec = 0;
			code = code == 'g' ? 'e' : 'E';
			}
		px->s[px->n1++] = *p++;
		if (0 < px->prec || px->flags & _FNO)
			px->s[px->n1++] = point;
		if (0 < px->prec)
			{	/* put fraction digits */
			if (px->prec < --nsig)
				nsig = px->prec;
			memcpy(&px->s[px->n1], p, nsig);
			px->n1 += nsig;
			px->nz1 = px->prec - nsig;
			}
		p = &px->s[px->n1];	/* put exponent */
		*p++ = code;
		if (0 <= xexp)
			*p++ = '+';
		else
			{	/* negative exponent */
			*p++ = '-';
			xexp = -xexp;
			}
		if (100 <= xexp)
			{	/* put oversize exponent */
			if (1000 <= xexp)
				*p++ = xexp / 1000 + '0', xexp %= 1000;
			*p++ = xexp / 100 + '0', xexp %= 100;
			}
		*p++ = xexp / 10 + '0', xexp %= 10;
		*p++ = xexp + '0';
		px->n2 = p - &px->s[px->n1];
		}
	if ((px->flags & (_FMI|_FZE)) == _FZE)
		{	/* pad with leading zeros */
		int n = px->n0 + px->n1 + px->nz1 + px->n2 + px->nz2;

		if (n < px->width)
			px->nz0 = px->width - n;
		}
	}
