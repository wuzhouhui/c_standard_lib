/* _Loctab data object */
#include <stddef.h>
#include "xlocale.h"

		/* macros */
#define OFF(member)		offsetof(_Linfo, member)
		/* static data */
_Locitem _Loctab[] = {	/* locale file info */
	{"LOCALE", OFF(_Name), L_NAME},
	{"NOTE", 0, L_NOTE},
	{"SET", 0, L_SET},
		/* controlled by LC_COLLATE */
	{"collate", OFF(_Costate._Tab), L_STATE},
		/* controlled by LC_CTYPE */
	{"ctype", OFF(_Ctype), L_TABLE},
	{"tolower", OFF(_Tolower), L_TABLE},
	{"toupper", OFF(_Toupper), L_TABLE},
	{"mb_cur_max", OFF(_Mbcurmax), L_VALUE},
	{"mbtowc", OFF(_Mbstate._Tab), L_STATE},
	{"wctomb", OFF(_Wcstate._Tab), L_STATE},
		/* controlled by LC_MONETARY */
	{"currency_symbol", OFF(_Lc.currency_symbol), L_STRING},
	{"int_curr_symbol", OFF(_Lc.int_curr_symbol), L_STRING},
	{"mon_decimal_point", OFF(_Lc.mon_decimal_point), L_STRING},
	{"mon_grouping", OFF(_Lc.mon_grouping), L_GSTRING},
	{"mon_thousands_sep", OFF(_Lc.mon_thousands_sep), L_STRING},
	{"negative_sign", OFF(_Lc.negative_sign), L_STRING},
	{"positive_sign", OFF(_Lc.positive_sign), L_STRING},
	{"frac_digits", OFF(_Lc.frac_digits), L_VALUE},
	{"int_frac_digits", OFF(_Lc.int_frac_digits), L_VALUE},
	{"n_cs_precedes", OFF(_Lc.n_cs_precedes), L_VALUE},
	{"n_sep_by_space", OFF(_Lc.n_sep_by_space), L_VALUE},
	{"n_sign_posn", OFF(_Lc.n_sign_posn), L_VALUE},
	{"p_cs_precedes", OFF(_Lc.p_cs_precedes), L_VALUE},
	{"p_sep_by_space", OFF(_Lc.p_sep_by_space), L_VALUE},
	{"p_sign_posn", OFF(_Lc.p_sign_posn), L_VALUE},
		/* controlled by LC_NUMERIC */
	{"decimal_point", OFF(_Lc.decimal_point), L_STRING},
	{"grouping", OFF(_Lc.grouping), L_GSTRING},
	{"thousands_sep", OFF(_Lc.thousands_sep), L_STRING},
		/* controlled by LC_TIME */
	{"am_pm", OFF(_Times._Ampm), L_STRING},
	{"days", OFF(_Times._Days), L_STRING},
	{"dst_rules", OFF(_Times._Isdst), L_STRING},
	{"time_formats", OFF(_Times._Formats), L_STRING},
	{"months", OFF(_Times._Months), L_STRING},
	{"time_zone", OFF(_Times._Tzone), L_STRING},
	{NULL}};
