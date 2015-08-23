/* _Isdst function */
#include <stdlib.h>
#include "xtime.h"

int _Isdst(const struct tm *t)
	{	/* test whether Daylight Savings Time in effect */
	Dstrule *pr;
	static const char *olddst = NULL;
	static Dstrule *rules = NULL;

	if (olddst != _Times._Isdst)
		{	/* find current dst_rules */
		if (_Times._Isdst[0] == '\0')
			{	/* look beyond time_zone info */
			int n;

			if (_Times._Tzone[0] == '\0')
				_Times._Tzone = _Getzone();
			_Times._Isdst = _Gettime(_Times._Tzone, 3, &n);
			if (_Times._Isdst[0] != '\0')
				--_Times._Isdst;	/* point to delimiter */
			}
		if ((pr = _Getdst(_Times._Isdst)) == NULL)
			return (-1);
		free(rules);
		rules = pr;
		olddst = _Times._Isdst;
		}
	 {	/* check time against rules */
	int ans = 0;
	const int d0 = _Daysto(t->tm_year, 0);
	const int hour = t->tm_hour + 24 * t->tm_yday;
	const int wd0 = (365L * t->tm_year + d0 + WDAY) % 7 + 14;

	for (pr = rules; pr->wday != (unsigned char)-1; ++pr)
		if (pr->year <= t->tm_year)
			{	/* found early enough year */
			int rday = _Daysto(t->tm_year, pr->mon) - d0
				 + pr->day;

			if (0 < pr->wday)
				{	/* shift to specific weekday */
				int wd = (rday + wd0 - pr->wday) % 7;

				rday += wd == 0 ? 0 : 7 - wd;
				if (pr->wday <= 7)
					rday -= 7;	/* strictly before */
				}
			if (hour < rday * 24 + pr->hour)
				return (ans);
			ans = pr->year == (pr + 1)->year ? !ans : 0;
			}
	return (ans);
	 }
	}
