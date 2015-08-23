/* _Getdst function */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "xtime.h"

static int getint(const char *s, int n)
	{	/* accumulate digits */
	int value;

	for (value = 0; 0 <= --n && isdigit(*s); ++s)
		value = value * 10 + *s - '0';
	return (0 <= n ? -1 : value);
	}

Dstrule *_Getdst(const char *s)
	{	/* parse DST rules */
	const char delim = *s++;
	Dstrule *pr, *rules;

	if (delim == '\0')
		return (NULL);
	 {	/* buy space for rules */
	const char *s1, *s2;
	int i;

	for (s1 = s, i = 2; (s2 = strchr(s1, delim)) != NULL; ++i)
			s1 = s2 + 1;
	if ((rules = (Dstrule *)malloc(sizeof (Dstrule) * i))
		== NULL)
		return (NULL);
	 }
	 {	/* parse rules */
	int year = 0;

	for (pr = rules; ; ++pr, ++s)
		{	/* parse next rule */
		if (*s == '(')
			{	/* got a year qualifier */
			year = getint(s + 1, 4) - 1900;
			if (year < 0 || s[5] != ')')
				break;	/* invalid year */
			s += 6;
			}
		pr->year = year;
		pr->mon = getint(s, 2) - 1, s += 2;
		pr->day = getint(s, 2) - 1, s += 2;
		if (isdigit(*s))
			pr->hour = getint(s, 2), s += 2;
		else
			pr->hour = 0;
		if (12 <= pr->mon || 99 < pr->day || 99 < pr->hour)
			break;	/* invalid month, day, or hour */
		if (*s != '+' && *s != '-')
			pr->wday = 0;
		else if (s[1] < '0' || '6' < s[1])
			break;	/* invalid week day */
		else
			{	/* compute week day field */
			pr->wday = s[1] == '0' ? 7 : s[1] - '0';
			if (*s == '+')	/* '-': strictly before */
				pr->wday += 7;	/* '+': on or after */
			s += 2;
			}
		if (*s == '\0')
			{	/* done, terminate list */
			(pr + 1)->wday = (unsigned char)-1;
			(pr + 1)->year = year;
			return (rules);
			}
		else if (*s != delim)
			break;
		}
	free(rules);
	return (NULL);
	 }
	}
