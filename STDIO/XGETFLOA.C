/* _Getfloat function */
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "xstdio.h"

int _Getfloat(_Sft *px)
	{	/* get a floating point value for _Scanf */
	char *p;
	int ch;
	char ac[FMAX+1];
	char seendig = 0;

	px->nget = px->width <= 0
		|| FMAX < px->width ? FMAX : px->width;
	p = ac, ch = GETN(px);
	if (ch == '+' || ch == '-')
		*p++ = ch, ch = GETN(px);
	for (; 0 <= ch && isdigit(ch); seendig = 1)
		*p++ = ch, ch = GETN(px);
	if (ch == localeconv()->decimal_point[0])
		*p++ = ch, ch = GETN(px);
	for (; 0 <= ch && isdigit(ch); seendig = 1)
		*p++ = ch, ch = GETN(px);
	if ((ch == 'e' || ch == 'E') && seendig)
		{	/* parse exponent */
		*p++ = ch, ch = GETN(px);
		if (ch == '+' || ch == '-')
			*p++ = ch, ch = GETN(px);
		for (seendig = 0; 0 <= ch && isdigit(ch); seendig = 1)
			*p++ = ch, ch = GETN(px);
		}
	UNGETN(px, ch);
	if (!seendig)
		return (p == ac && ch < 0 ? EOF : 0);
	*p = '\0';
	if (!px->noconv)
		{	/* convert and store */
		double dval = strtod(ac, NULL);

		px->stored = 1;
		if (px->qual == 'l')
			*va_arg(px->ap, double *) = dval;
		else if (px->qual != 'L')
			*va_arg(px->ap, float *) = dval;
		else
			*va_arg(px->ap, long double *) = dval;
		}
	return (1);
	}
