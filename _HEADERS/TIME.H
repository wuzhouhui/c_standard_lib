/* time.h standard header */
#ifndef _TIME
#define _TIME
#ifndef _YVALS
#include <yvals.h>
#endif
		/* macros */
#define NULL	_NULL
#define CLOCKS_PER_SEC	_CPS
		/* type definitions */
#ifndef _SIZET
#define _SIZET
typedef _Sizet size_t;
#endif
typedef unsigned int clock_t;
typedef unsigned long time_t;
struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	};
		/* declarations */
char *asctime(const struct tm *);
clock_t clock(void);
char *ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *);
size_t strftime(char *, size_t, const char *,
	const struct tm *);
time_t time(time_t *);
#endif
