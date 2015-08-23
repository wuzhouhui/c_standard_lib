/* _Getint function */
#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

int _Getint(_Sft *px)
	{	/* get an integer value for _Scanf */
	char ac[FMAX+1], *p;
	char seendig = 0;
	int ch;
	static const char digits[]
		= "0123456789abcdefABCDEF";
	static const char flit[] = "diouxXp";
	static const char barr[] = {10, 0, 8, 10, 16, 16, 16};
	int base = barr[(const char *)strchr(flit, *px->s) - flit];
	int dlen;

	px->nget = px->width <= 0
		|| FMAX < px->width ? FMAX : px->width;
	p = ac, ch = GETN(px);
	if (ch == '+' || ch == '-')
		*p++ = ch, ch = GETN(px);
	if (ch == '0')
		{	/* match possible prefix */
		seendig = 1;
		*p++ = ch, ch = GETN(px);
		if ((ch == 'x' || ch == 'X')
			&& (base == 0 || base == 16))
			base = 16, *p++ = ch, ch = GETN(px);
		else if (base == 0)
			base = 8;
		}
	dlen = base == 0 || base == 10 ? 10 : base == 8 ? 8 : 16+6;
	for (; 0 <= ch && memchr(digits, ch, dlen); seendig = 1)
		*p++ = ch, ch = GETN(px);
	UNGETN(px, ch);
	if (!seendig)
		return (p == ac && ch < 0 ? EOF : 0);
	*p = '\0';
	if (px->noconv)
		;
	else if (*px->s == 'd' || *px->s == 'i')
		{	/* deliver a signed integer */
		long lval = strtol(ac, NULL, base);

		px->stored = 1;
		if (px->qual == 'h')
			*va_arg(px->ap, short *) = lval;
		else if (px->qual != 'l')
			*va_arg(px->ap, int *) = lval;
		else
			*va_arg(px->ap, long *) = lval;
		}
	else
		{	/* deliver an unsigned integer */
		unsigned long ulval = strtoul(ac, NULL, base);

		px->stored = 1;
		if (*px->s == 'p')
			*va_arg(px->ap, void **) = (void *)ulval;
		else if (px->qual == 'h')
			*va_arg(px->ap, unsigned short *) = ulval;
		else if (px->qual != 'l')
			*va_arg(px->ap, unsigned int *) = ulval;
		else
			*va_arg(px->ap, unsigned long *) = ulval;
		}
	return (1);
	}
