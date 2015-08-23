/* xtime.h internal header */
#include <time.h>
#include "xtinfo.h"
		/* macros */
#define WDAY 	1	/* to get day of week right */
		/* type definitions */
typedef struct {
	unsigned char wday, hour, day, mon, year;
	} Dstrule;
		/* internal declarations */
int _Daysto(int, int);
const char *_Gentime(const struct tm *, _Tinfo *, char,
	int *, char *);
Dstrule *_Getdst(const char *);
const char *_Gettime(const char *, int, int *);
int _Isdst(const struct tm *);
const char *_Getzone(void);
size_t _Strftime(char *, size_t, const char *,
	const struct tm *, _Tinfo *);
struct tm *_Ttotm(struct tm *, time_t, int);
time_t _Tzoff(void);
