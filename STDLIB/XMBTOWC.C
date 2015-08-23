/* _Mbtowc function */
#include <limits.h>
#include <stdlib.h>
#include "xstate.h"

int _Mbtowc(wchar_t *pwc, const char *s, size_t nin,
	_Mbsave *ps)
	{	/* translate multibyte to widechar */
	static const _Mbsave initial = {0};

	if (s == NULL)
		{	/* set initial state */
		*ps = initial;
		return (_Mbstate._Tab[0][0] & ST_STATE);
		}
	 {	/* run finite state machine */
	char state = ps->_State;
	int limit = 0;
	unsigned char *su = (unsigned char *)s;
	unsigned short wc = ps->_Wchar;

	if (MB_CUR_MAX < nin)
		nin = MB_CUR_MAX;
	for (; ; )
		{	/* perform a state transformation */
		unsigned short code;
		const unsigned short *stab;

		if (_NSTATE <= state
			|| (stab = _Mbstate._Tab[state]) == NULL
			|| nin == 0
			|| (_NSTATE*UCHAR_MAX) <= ++limit
			|| (code = stab[*su]) == 0)
			break;
		state = (code & ST_STATE) >> ST_STOFF;
		if (code & ST_FOLD)
			wc = wc & ~UCHAR_MAX | code & ST_CH;
		if (code & ST_ROTATE)
			wc = wc >> CHAR_BIT & UCHAR_MAX | wc << CHAR_BIT;
		if (code & ST_INPUT && *su != '\0')
			++su, --nin, limit = 0;
		if (code & ST_OUTPUT)
			{	/* produce an output wchar */
			if (pwc)
				*pwc = wc;
			ps->_State = state;
			ps->_Wchar = wc;
			return ((const char *)su - s);
			}
		}
	ps->_State = _NSTATE;	/* error return */
	return (-1);
	 }
	}
