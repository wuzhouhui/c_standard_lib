/* asctime function */
#include "xtime.h"

		/* static data */
static const char ampm[] = {":AM:PM"};
static const char days[] = {
	":Sun:Sunday:Mon:Monday:Tue:Tuesday:Wed:Wednesday"
	":Thu:Thursday:Fri:Friday:Sat:Saturday"};
static const char fmts[] = {
	"|%b %D %H:%M:%S %Y|%b %D %Y|%H:%M:%S"};
static const char isdst[] = {""};
static const char mons[] = {
	":Jan:January:Feb:February:Mar:March"
	":Apr:April:May:May:Jun:June"
	":Jul:July:Aug:August:Sep:September"
	":Oct:October:Nov:November:Dec:December"};
static const char zone[] = {""};	/* adapt by default */
static _Tinfo ctinfo = {ampm, days, fmts, isdst, mons, zone};
_Tinfo _Times = {ampm, days, fmts, isdst, mons, zone};

char *(asctime)(const struct tm *t)
	{	/* format time as "Day Mon dd hh:mm:ss yyyy\n" */
	static char tbuf[] = "Day Mon dd hh:mm:ss yyyy\n";

	_Strftime(tbuf, sizeof (tbuf), "%a %c\n", t, &ctinfo);
	return (tbuf);
	}
