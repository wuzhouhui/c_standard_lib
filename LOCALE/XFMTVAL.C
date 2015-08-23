/* _Fmtval function */
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

		/* macros */
#define FN_INT_CUR	-2
#define FN_LCL_CUR	-1

char *_Fmtval(char *buf, double d, int fdarg)
	{	/* format number by locale-specific rules */
	char *cur_sym, dec_pt, *grps, grp_sep, *sign;
	const char *fmt;
	int fd, neg;
	struct lconv *p = localeconv();

	if (0 <= d)
		neg = 0;
	else
		d = -d, neg = 1;
	if (fdarg == FN_INT_CUR)
		{	/* get international currency parameters */
		cur_sym = p->int_curr_symbol;
		dec_pt = p->mon_decimal_point[0];
		fmt = "$-V";
		fd = p->int_frac_digits;
		grps = p->mon_grouping;
		grp_sep = p->mon_thousands_sep[0];
		sign = neg ? p->negative_sign : p->positive_sign;
		}
	else if (fdarg == FN_LCL_CUR)
		{	/* get local currency parameters */
		static const char *ftab[2][2][5] = {
			{{"(V$)",  "-V$",  "V$-",  "V-$",  "V$-"},
			 {"($V)",  "-$V",  "$V-",  "-$V",  "$-V"}},
			{{"(V $)", "-V $", "V $-", "V- $", "V $-"},
			 {"($ V)", "-$ V", "$ V-", "-$ V", "$ -V"}}};

		cur_sym = p->currency_symbol;
		dec_pt = p->mon_decimal_point[0];
		if (neg)
			fmt = ftab[p->n_sep_by_space == 1]
				[p->n_cs_precedes == 1][p->n_sign_posn < 0
				|| 4 < p->n_sign_posn ? 0 : p->n_sign_posn];
		else
			fmt = ftab[p->p_sep_by_space == 1]
				[p->p_cs_precedes == 1][p->p_sign_posn < 0
				|| 4 < p->p_sign_posn ? 0 : p->p_sign_posn];
		fd = p->frac_digits;
		grps = p->mon_grouping;
		grp_sep = p->mon_thousands_sep[0];
		sign = neg ? p->negative_sign : p->positive_sign;
		}
	else
		{	/* get numeric parameters (cur_sym not used) */
		dec_pt = p->decimal_point[0];
		fmt = "-V";
		fd = fdarg;
		grps = p->grouping;
		grp_sep = p->thousands_sep[0];
		sign = neg ? "-" : "";
		}
	 {	/* build string in buf under control of fmt */
	char *end, *s;
	const char *g;
	size_t i, ns;

	for (s = buf; *fmt; ++fmt, s += strlen(s))
		switch (*fmt)
			{	/* process a format char */
		case '$':	/* insert currency symbol string */
			strcpy(s, cur_sym);
			break;
		case '-':	/* insert sign string */
			strcpy(s, sign);
			break;
		default:	/* insert literal format char */
			*s++ = *fmt, *s = '\0';
			break;
		case 'V':	/* insert formatted value */
			sprintf(s, "%#.*f",
				0 < fd && fd != CHAR_MAX ? fd : 0, d);
			end = strchr(s, p->decimal_point[0]);
			for (ns = 0, i = end - s, g = grps; 0 < i; ++ns)
				{	/* count separators to add */
				if (g[0] <= 0 || i <= g[0] || g[0] == CHAR_MAX)
					break;
				i -= g[0];
				if (g[1] != 0)
					++g;
				}
			memmove(end + ns, end, strlen(end) + 1);
			i = end - s, end += ns;
			*end = 0 <= fd && fd != CHAR_MAX ? dec_pt : '\0';
			for (g = grps; 0 < i; --ns)
				{	/* copy up and insert separators */
				if (g[0] <= 0 || i <= g[0] || g[0] == CHAR_MAX)
					break;
				i -= g[0], end -= g[0];
				memmove(end, end - ns, g[0]);
				*--end = grp_sep;
				if (g[1] != 0)
					++g;
				}
			}
	 }
	return (buf);
	}
