/* _Gentime function */
#include "xtime.h"

		/* macros */
#define SUNDAY	0	/* codes for tm_wday */
#define MONDAY	1

static char *getval(char *s, int val, int n)
	{	/* convert a decimal value */
	if (val < 0)
		val = 0;
	for (s += n, *s = '\0'; 0 <= --n; val /= 10)
		*--s = val % 10 + '0';
	return (s);
	}

static int wkyr(int wstart, int wday, int yday)
	{	/* find week of year */
	wday = (wday + 7 - wstart) % 7;
	return (yday + 7 - wday) / 7;
	}

const char *_Gentime(const struct tm *t, _Tinfo *tin,
	char code, int *pn, char *ac)
	{	/* format a time field */
	const char *p;

	switch (code)
		{	/* switch on conversion specifier */
	case 'a':	/* put short weekday name */
		p = _Gettime(tin->_Days, t->tm_wday << 1, pn);
		break;
	case 'A':	/* put full weekday name */
		p = _Gettime(tin->_Days, (t->tm_wday << 1) + 1, pn);
		break;
	case 'b':	/* put short month name */
		p = _Gettime(tin->_Months, t->tm_mon << 1, pn);
		break;
	case 'B':	/* put full month name */
		p = _Gettime(tin->_Months, (t->tm_mon << 1) + 1, pn);
		break;
	case 'c':	/* put date and time */
		p = _Gettime(tin->_Formats, 0, pn), *pn = -*pn;
		break;
	case 'd':	/* put day of month, from 01 */
		p = getval(ac, t->tm_mday, *pn = 2);
		break;
	case 'D':	/* put day of month, from 1 */
		p = getval(ac, t->tm_mday, *pn = 2);
		if (ac[0] == '0')
			ac[0] = ' ';
		break;
	case 'H':	/* put hour of 24-hour day */
		p = getval(ac, t->tm_hour, *pn = 2);
		break;
	case 'I':	/* put hour of 12-hour day */
		p = getval(ac, (t->tm_hour + 11) % 12 + 1, *pn = 2);
		break;
	case 'j':	/* put day of year, from 001 */
		p = getval(ac, t->tm_yday + 1, *pn = 3);
		break;
	case 'm':	/* put month of year, from 01 */
		p = getval(ac, t->tm_mon + 1, *pn = 2);
		break;
	case 'M':	/* put minutes after the hour */
		p = getval(ac, t->tm_min, *pn = 2);
		break;
	case 'p':	/* put AM/PM */
		p = _Gettime(tin->_Ampm, 12 <= t->tm_hour, pn);
		break;
	case 'S':	/* put seconds after the minute */
		p = getval(ac, t->tm_sec, *pn = 2);
		break;
	case 'U':	/* put Sunday week of the year */
		p = getval(ac,
			wkyr(SUNDAY, t->tm_wday, t->tm_yday), *pn = 2);
		break;
	case 'w':	/* put day of week, from Sunday */
		p = getval(ac, t->tm_wday, *pn = 1);
		break;
	case 'W':	/* put Monday week of the year */
		p = getval(ac,
			wkyr(MONDAY, t->tm_wday, t->tm_yday), *pn = 2);
		break;
	case 'x':	/* put date */
		p = _Gettime(tin->_Formats, 1, pn), *pn = -*pn;
		break;
	case 'X':	/* put time */
		p = _Gettime(tin->_Formats, 2, pn), *pn = -*pn;
		break;
	case 'y':	/* put year of the century */
		p = getval(ac, t->tm_year % 100, *pn = 2);
		break;
	case 'Y':	/* put year */
		p = getval(ac, t->tm_year + 1900, *pn = 4);
		break;
	case 'Z':	/* put time zone name */
		if (tin->_Tzone[0] == '\0')
			tin->_Tzone = _Getzone();	/* adapt zone */
		p = _Gettime(tin->_Tzone, 0 < t->tm_isdst, pn);
		break;
	case '%':	/* put "%" */
		p = "%", *pn = 1;
		break;
	default:	/* unknown field, print it */
		ac[0] = code, ac[1] = '\0';
		p = ac, *pn = 2;
		}
	return (p);
	}
