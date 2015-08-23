/* _Strxfrm function */
#include <limits.h>
#include "xstrxfrm.h"

size_t _Strxfrm(char *sout, const unsigned char **psin,
	size_t size, _Cosave *ps)
	{	/* translate string to collatable form */
	unsigned char state = ps->_State;
	int leave = 0;
	int limit = 0;
	int nout = 0;
	const unsigned char *sin = *psin;
	unsigned short wc = ps->_Wchar;

	for (; ; )
		{	/* perform a state transformation */
		unsigned short code;
		const unsigned short *stab;

		if (_NSTATE <= state
			|| (stab = _Costate._Tab[state]) == NULL
			|| (_NSTATE*UCHAR_MAX) <= ++limit
			|| (code = stab[*sin]) == 0)
			break;
		state = (code & ST_STATE) >> ST_STOFF;
		if (code & ST_FOLD)
			wc = wc & ~UCHAR_MAX | code & ST_CH;
		if (code & ST_ROTATE)
			wc = wc >> CHAR_BIT & UCHAR_MAX | wc << CHAR_BIT;
		if (code & ST_OUTPUT && ((sout[nout++]
			= code & ST_CH ? code : wc) == '\0'
			|| size <= nout))
			leave = 1;
		if (code & ST_INPUT)
			if (*sin != '\0')
				++sin, limit = 0;
			else
				leave = 1;
		if (leave)
			{	/* return for now */
			*psin = sin;
			ps->_State = state;
			ps->_Wchar = wc;
			return (nout);
			}
		}
	sout[nout++] = '\0';	/* error return */
	*psin = sin;
	ps->_State = _NSTATE;
	return (nout);
	}
