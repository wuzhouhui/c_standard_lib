/* strcoll function */
#include "xstrxfrm.h"

		/* type definitions */
typedef struct {
	char buf[32];
	const unsigned char *s1, *s2, *sout;
	_Cosave state;
	} Sctl;

static size_t getxfrm(Sctl *p)
	{	/* get transformed chars */
	size_t i;

	do	{	/* loop until chars delivered */
		p->sout = (const unsigned char *)p->buf;
		i = _Strxfrm(p->buf, &p->s1, sizeof (p->buf), &p->state);
		if (0 < i && p->buf[i - 1] == '\0')
			return (i - 1);
		else if (*p->s1 == '\0')
			p->s1 = p->s2;	/* rescan */
		} while (i == 0);
	return (i);
	}

int (strcoll)(const char *s1, const char *s2)
	{	/* compare s1[], s2[] using locale-dependent rule */
	size_t n1, n2;
	Sctl st1, st2;
	static const _Cosave initial = {0};

	st1.s1 = (const unsigned char *)s1;
	st1.s2 = (const unsigned char *)s1;
	st1.state = initial;
	st2.s1 = (const unsigned char *)s2;
	st2.s2 = (const unsigned char *)s2;
	st2.state = initial;
	for (n1 = n2 = 0; ; )
		{	/* compare transformed chars */
		int ans;
		size_t n;

		if (n1 == 0)
			n1 = getxfrm(&st1);
		if (n2 == 0)
			n2 = getxfrm(&st2);
		n = n1 < n2 ? n1 : n2;
		if (n == 0)
			return (n1 == n2 ? 0 : 0 < n2 ? -1 : +1);
		else if ((ans = memcmp(st1.sout, st2.sout, n)) != 0)
			return (ans);
		st1.sout += n, n1 -= n;
		st2.sout += n, n2 -= n;
		}
	}
