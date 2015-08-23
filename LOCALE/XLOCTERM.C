/* _Locterm and _Locvar functions */
#include <ctype.h>
#include <string.h>
#include "xlocale.h"

		/* static data */
static const char dollars[] = {	/* PLUS $@ and $$ */
	"^abfnrtv"		/* character codes */
	"01234567"		/* state values */
	"ACDHLMPSUW"	/* ctype codes */
	"#FIOR"};		/* state commands */
static const unsigned short dolvals[] = {
	CHAR_MAX, '\a', '\b', '\f', '\n', '\r', '\t', '\v',
	0x000, 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700,
	_XA, _BB, _DI, _XD, _LO, _CN, _PU, _SP, _UP, _XS,
	UCHAR_MAX, ST_FOLD, ST_INPUT, ST_OUTPUT, ST_ROTATE};
static const char uppers[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static short vars[sizeof (uppers) - 1] = {0};

int _Locvar(char ch, short val)
	{	/* set a $ variable */
	const char *s = strchr(uppers, ch);

	if (s == NULL)
		return (0);
	vars[s - uppers] = val;
	return (1);
	}

 int _Locterm(const char **ps, unsigned short *ans)
	{	/* evaluate a term on a locale file line */
	const char *s = *ps;
	const char *s1;
	int mi;

	for (mi = 0; *s == '+' || *s == '-'; s = _Skip(s))
		mi = *s == '-' ? !mi : mi;
	if (isdigit(s[0]))
		*ans = strtol(s, (char **)&s, 0);
	else if (s[0] == '\'' && s[1] != '\0' && s[2] == '\'')
		*ans = ((unsigned char *)s)[1], s += 3;
	else if (s[0] && (s1 = strchr(uppers, s[0])) != NULL)
		*ans = vars[s1 - uppers], ++s;
	else if (s[0] == '$' && s[1]
		&& (s1 = strchr(dollars, s[1])) != NULL)
		*ans = dolvals[s1 - dollars], s += 2;
	else
		return (0);
	if (mi)
		*ans = -*ans;
	*ps = _Skip(s - 1);
	return (1);
	}
