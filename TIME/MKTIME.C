/* mktime function */
#include <limits.h>
#include "xtime.h"

time_t (mktime)(struct tm *t)
	{	/* convert local time structure to scalar time */
	double dsecs;
	int mon, year, ymon;
	time_t secs;

	ymon = t->tm_mon / 12;
	mon = t->tm_mon - ymon * 12;
	if (mon < 0)
		mon += 12, --ymon;
	if (ymon < 0 && t->tm_year < INT_MIN - ymon
		|| 0 < ymon && INT_MAX - ymon < t->tm_year)
		return ((time_t)(-1));
	year = t->tm_year + ymon;
	dsecs = 86400.0 * (_Daysto(year, mon) - 1)
		+ 31536000.0 * year + 86400.0 * t->tm_mday;
	dsecs += 3600.0 * t->tm_hour + 60.0 * t->tm_min
		+ (double)t->tm_sec;
	if (dsecs < 0.0 || (double)(time_t)(-1) <= dsecs)
		return ((time_t)(-1));
	secs = (time_t)(dsecs - _TBIAS);
	_Ttotm(t, secs, t->tm_isdst);
	if (0 < t->tm_isdst)
		secs -= 3600;
	return (secs - _Tzoff());
	}
