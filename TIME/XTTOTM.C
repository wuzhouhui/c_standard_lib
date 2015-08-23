/* _Ttotm and _Daysto functions */
#include "xtime.h"

		/* macros */
#define MONTAB(year)	\
	((year) & 03 || (year) == 0 ? mos : lmos)

		/* static data */
static const short lmos[] = {0, 31, 60, 91, 121, 152,
	 182, 213, 244, 274, 305, 335};
static const short mos[] = {0, 31, 59, 90, 120, 151,
	 181, 212, 243, 273, 304, 334};

int _Daysto(int year, int mon)
	{	/* compute extra days to start of month */
	int days;

	if (0 < year)	/* correct for leap year: 1801-2099 */
		days = (year - 1) / 4;
	else if (year <= -4)
		days = 1 + (4 - year) / 4;
	else
		days = 0;
	return (days + MONTAB(year)[mon]);
	}

struct tm *_Ttotm(struct tm *t, time_t secsarg, int isdst)
	{	/* convert scalar time to time structure */
	int year;
	long days;
	time_t secs;
	static struct tm ts;

	secsarg += _TBIAS;
	if (t == NULL)
		t = &ts;
	t->tm_isdst = isdst;
	for (secs = secsarg; ; secs = secsarg + 3600)
		{	/* loop to correct for DST */
		days = secs / 86400;
		t->tm_wday = (days + WDAY) % 7;
		 {	/* determine year */
		long i;
	
		for (year = days / 365;
			days < (i = _Daysto(year, 0) + 365L * year); )
			--year;	/* correct guess and recheck */
		days -= i;
		t->tm_year = year;
		t->tm_yday = days;
		 }
		 {	/* determine month */
		int mon;
		const short *pm = MONTAB(year);
	
		for (mon = 12; days < pm[--mon]; )
			;
		t->tm_mon = mon;
		t->tm_mday = days - pm[mon] + 1;
		 }
		secs %= 86400;
		t->tm_hour = secs / 3600;
		secs %= 3600;
		t->tm_min = secs / 60;
		t->tm_sec = secs % 60;
		if (0 <= t->tm_isdst || (t->tm_isdst = _Isdst(t)) <= 0)
			return (t);	/* loop only if <0 => 1 */
		}
	}
