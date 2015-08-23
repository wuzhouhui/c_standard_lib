/* xlocale.h internal header */
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "xstate.h"
#include "xtinfo.h"

		/* macros for _Getloc and friends */
#define ADDR(p, q, ty)	(*(ty *)((char *)p + q->_Offset))
#define NEWADDR(p, q, ty)	\
	(ADDR(p, q, ty) != ADDR(&_Clocale, q, ty))
#define MAXLIN	256
#define TABSIZ	((UCHAR_MAX + 2) * sizeof (short))
		/* type definitions */
enum _Lcode {
	L_GSTRING, L_NAME, L_NOTE, L_SET,
	L_STATE, L_STRING, L_TABLE, L_VALUE
	};
typedef const struct {
	const char *_Name;
	size_t _Offset;
	enum _Lcode _Code;
	} _Locitem;
typedef struct _Linfo {
	const char *_Name;	/* must be first */
	struct _Linfo *_Next;
		/* controlled by LC_COLLATE */
	_Statab _Costate;
		/* controlled by LC_CTYPE */
	const short *_Ctype;
	const short *_Tolower;
	const short *_Toupper;
	unsigned char _Mbcurmax;
	_Statab _Mbstate;
	_Statab _Wcstate;
		/* controlled by LC_MONETARY and LC_NUMERIC */
	struct lconv _Lc;
		/* controlled by LC_TIME */
	_Tinfo _Times;
	} _Linfo;
		/* declarations */
const char *_Defloc(void);
void _Freeloc(_Linfo *);
_Linfo *_Getloc(const char *, const char *);
int _Locterm(const char **, unsigned short *);
int _Locvar(char, short);
int _Makeloc(FILE *, char *, _Linfo *);
_Locitem *_Readloc(FILE *, char *, const char **);
_Linfo *_Setloc(int, _Linfo *);
const char *_Skip(const char *);
extern _Linfo _Clocale;
extern _Locitem _Loctab[];
