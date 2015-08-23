/* _Wctomb function */
#include <limits.h>
#include <stdlib.h>
#include "xstate.h"

int _Wctomb(char *s, wchar_t wcin, char *ps)
	{	/* translate widechar to multibyte */
	static const char initial = 0;

	if (s == NULL)
		{	/* set initial state */
		*ps = initial;
		return (_Mbstate._Tab[0][0] & ST_STATE);
		}
	 {	/* run finite state machine */
	char state = *ps;
	int leave = 0;
	int limit = 0;
	int nout = 0;
	unsigned short wc = wcin;

	for (; ; )
		{	/* perform a state transformation */
		unsigned short code;
		const unsigned short *stab;

		if (_NSTATE <= state
			|| (stab = _Wcstate._Tab[state]) == NULL
			|| MB_CUR_MAX <= nout
			|| (_NSTATE*UCHAR_MAX) <= ++limit
			|| (code = stab[wc & UCHAR_MAX]) == 0)
			break;
		state = (code & ST_STATE) >> ST_STOFF;
		if (code & ST_FOLD)
			wc = wc & ~UCHAR_MAX | code & ST_CH;
		if (code & ST_ROTATE)
			wc = wc >> CHAR_BIT & UCHAR_MAX | wc << CHAR_BIT;
		if (code & ST_OUTPUT)
			{	/* produce an output char */
			if ((s[nout++] = code & ST_CH ? code : wc) == '\0')
				leave = 1;
			limit = 0;
			}
		if (code & ST_INPUT || leave)
			{	/* consume input */
			*ps = state;
			return (nout);
			}
		}
	*ps = _NSTATE;
	return (-1);
	 }
	}
