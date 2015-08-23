/* _Litob function */
#include <stdlib.h>
#include <string.h>
#include "xmath.h"
#include "xstdio.h"

static char ldigs[] = "0123456789abcdef";
static char udigs[] = "0123456789ABCDEF";

void _Litob(_Pft *px, char code)
	{	/* convert unsigned long to text */
	char ac[24];	/* safe for 64-bit integers */
	char *digs = code == 'X' ? udigs : ldigs;
	int base = code == 'o' ? 8 :
		code != 'x' && code != 'X' ? 10 : 16;
	int i = sizeof (ac);
	unsigned long ulval = px->v.li;

	if ((code == 'd' || code == 'i') && px->v.li < 0)
		ulval = -ulval;	/* safe against overflow */
	if (ulval != 0 || px->prec != 0)
		ac[--i] = digs[ulval % base];
	px->v.li = ulval / base;
	while (0 < px->v.li && 0 < i)
		{ 	/* convert digits */
		ldiv_t qr = ldiv(px->v.li, base);

		px->v.li = qr.quot;
		ac[--i] = digs[qr.rem];
		}
	px->n1 = sizeof (ac) - i;
	memcpy(px->s, &ac[i], px->n1);
	if (px->n1 < px->prec)
		px->nz0 = px->prec - px->n1;
	if (px->prec < 0 && (px->flags & (_FMI|_FZE)) == _FZE
		&& 0 < (i = px->width - px->n0 - px->nz0 - px->n1))
		px->nz0 += i;
	}
