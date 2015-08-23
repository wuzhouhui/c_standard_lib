/* _Getfld function */
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "xstdio.h"

int _Getfld(_Sft *px)
	{	/* convert a field */
	char seen = 0;
	int ch;
	char *p;

	px->stored = 0;
	switch (*px->s)
		{	/* switch on conversion specifier */
	case 'c':	/* convert an array of chars */
		if (px->width == 0)
			px->width = 1;
		p = px->noconv ? NULL : va_arg(px->ap, char *);
		for (; 0 < px->width; --px->width, seen = 1)
			if ((ch = GET(px)) < 0)
				return (!seen ? EOF : 1);
			else if (p != NULL)
				*p++ = ch, px->stored = 1;
		return (seen);
	case 'p':	/* convert a pointer */
	case 'd': case 'i': case 'o':
	case 'u': case 'x': case 'X':
		return (_Getint(px));	/* convert an integer */
	case 'e': case 'E': case 'f':
	case 'g': case 'G':
		return (_Getfloat(px));	/* convert a floating */
	case 'n':	/* return input count */
		if (px->noconv)
			;
		else if (px->qual == 'h')
			*va_arg(px->ap, short *) = px->nchar;
		else if (px->qual != 'l')
			*va_arg(px->ap, int *) = px->nchar;
		else
			*va_arg(px->ap, long *) = px->nchar;
		return (1);
	case 's':	/* convert a string */
		px->nget = px->width <= 0 ? INT_MAX : px->width;
		p = px->noconv ? NULL : va_arg(px->ap, char *);
		for (; 0 <= (ch = GETN(px)) && !isspace(ch); seen = 1)
			if (p != NULL)
				*p++ = ch;
		UNGETN(px, ch);
		if (!seen)
			return (ch < 0 ? EOF : 0);
		if (!px->noconv)
			*p++ = '\0', px->stored = 1;
		return (1);
	case '%':	/* match a '%' */
		if ((ch = GET(px)) == '%')
			return (1);
		UNGETN(px, ch);
		return (ch < 0 ? EOF : 0);
	case '[':
		 {	/* convert a scan set */
		char comp = *++px->s == '^' ? *px->s++ : '\0';
		const char * const t = strchr(*px->s == ']'
			? px->s + 1 : px->s, ']');
		size_t n;

		if (t == NULL)
			return (0);	/* undefined */
		px->nget = px->width <= 0 ? INT_MAX : px->width;
		p = px->noconv ? NULL : va_arg(px->ap, char *);
		for (n = t - px->s; 0 <= (ch = GETN(px)); seen = 1)
			if (!comp && !memchr(px->s, ch, n)
				|| comp && memchr(px->s, ch, n))
				break;
			else if (p != NULL)
				*p++ = ch;
		UNGETN(px, ch);
		if (!seen)
			return (ch < 0 ? EOF : 0);
		if (!px->noconv)
			*p++ = '\0', px->stored = 1;
		px->s = t;
		 }
		return (1);
	default:	/* undefined specifier, quit */
		return (0);
		}
	}
