/* _Makeloc function */
#include <string.h>
#include "xlocale.h"

static const char *getval(const char *s, unsigned short *ans)
	{	/* accumulate terms */
	unsigned short val;

	if (!_Locterm(&s, ans))
		return (NULL);
	while (_Locterm(&s, &val))
		*ans += val;
	return (s);
	}

int _Makeloc(FILE *lf, char *buf, _Linfo *p)
	{	/* construct locale from text file */
	const char *s;
	char *s1;
	_Locitem *q;
	unsigned short val;
	static const char gmap[] = "0123456789abcdef^";

	while ((q = _Readloc(lf, buf, &s)) != NULL)
		switch (q->_Code)
			{	/* process a line */
		case L_GSTRING:	/* alter a grouping string */
		case L_STRING:	/* alter a normal string */
			if (NEWADDR(p, q, char *))
				free(ADDR(p, q, char *));
			if (s[0] == '"'
				&& (s1 = strrchr(s + 1, '"')) != NULL
				&& *_Skip(s1) == '\0')
				*s1 = '\0', ++s;
			if ((s1 = (char *)malloc(strlen(s) + 1)) == NULL)
				return (0);
			ADDR(p, q, char *) = strcpy(s1, s);
			if (q->_Code == L_GSTRING)
				for (; *s1; ++s1)
					if ((s = strchr(gmap, *s1)) != NULL)
						*s1 = *s == '^' ? CHAR_MAX : s - gmap;
			break;
		case L_TABLE:	/* alter a translation table */
		case L_STATE:	/* alter a state table */
			 {	/* process tab[#,lo:hi] $x expr */
			int inc = 0;
			unsigned short hi, lo, stno, *usp, **uspp;

			if (*s != '['
				|| (s = getval(_Skip(s), &stno)) == NULL)
				return (0);
			if (*s != ',')
				lo = stno, stno = 0;
			else if (q->_Code != L_STATE || _NSTATE <= stno
				|| (s = getval(_Skip(s), &lo)) == NULL)
				return (0);
			lo = (unsigned char)lo;
			if (*s != ':')
				hi = lo;
			else if ((s = getval(_Skip(s), &hi)) == NULL)
				return (0);
			else
				hi = (unsigned char)hi;
			if (*s != ']')
				return (0);
			for (s = _Skip(s); s[0] == '$'; s = _Skip(s + 1))
				if (s[1] == '@' && (inc & 1) == 0)
					inc |= 1;
				else if (s[1] == '$' && (inc & 2) == 0)
					inc |= 2;
				else
					break;
			if ((s = getval(s, &val)) == NULL || *s != '\0')
				return (0);
			uspp = &ADDR(p, q, unsigned short *) + stno;
			if (q->_Code == L_TABLE)
				usp = NEWADDR(p, q, short *) ? *uspp : NULL;
			else
				usp = (*uspp)[-1] ? *uspp : NULL;
			if (usp == NULL)
				{	/* setup a new table */
				if ((usp = (unsigned short *)malloc(TABSIZ))
					== NULL)
					return (0);
				memcpy(usp, ADDR(p, q, short *) - 1, TABSIZ);
				if (q->_Code == L_STATE)
					usp[0] = 1;	/* allocation flag */
				*uspp = &usp[1];
				}
			for (; lo <= hi; ++lo)
				usp[lo] = val + (inc & 1 ? lo : 0)
					+ (inc & 2 ? usp[lo] : 0);
			 }
			break;
		case L_VALUE:	/* alter a numeric value */
			if ((s = getval(s, &val)) == NULL || *s != '\0')
				return (0);
			ADDR(p, q, char) = val;
			break;
		case L_SET:	/* assign to uppercase variable */
			if (*(s1 = (char *)_Skip(s)) == '\0'
				|| (s1 = (char *)getval(s1, &val)) == NULL
				|| *s1 != '\0' || _Locvar(*s, val) == 0)
				return (0);
			break;
		case L_NAME:	/* end happily with next LOCALE */
			return (1);
			}
	return (0);	/* fail on EOF or unknown keyword */
	}
