/* _Setloc function */
#include <ctype.h>
#include "xlocale.h"

_Linfo *_Setloc(int cat, _Linfo *p)
	{	/* set category for locale */
	switch (cat)
		{	/* set a category */
	case LC_COLLATE:
		_Costate = p->_Costate;
		break;
	case LC_CTYPE:
		_Ctype = p->_Ctype;
		_Tolower = p->_Tolower;
		_Toupper = p->_Toupper;
		_Mbcurmax = p->_Mbcurmax <= MB_LEN_MAX
			? p->_Mbcurmax : MB_LEN_MAX;
		_Mbstate = p->_Mbstate;
		_Wcstate = p->_Wcstate;
		break;
	case LC_MONETARY:
		_Locale.currency_symbol = p->_Lc.currency_symbol;
		_Locale.int_curr_symbol = p->_Lc.int_curr_symbol;
		_Locale.mon_decimal_point = p->_Lc.mon_decimal_point;
		_Locale.mon_grouping = p->_Lc.mon_grouping;
		_Locale.mon_thousands_sep = p->_Lc.mon_thousands_sep;
		_Locale.negative_sign = p->_Lc.negative_sign;
		_Locale.positive_sign = p->_Lc.positive_sign;
		_Locale.frac_digits = p->_Lc.frac_digits;
		_Locale.int_frac_digits = p->_Lc.int_frac_digits;
		_Locale.n_cs_precedes = p->_Lc.n_cs_precedes;
		_Locale.n_sep_by_space = p->_Lc.n_sep_by_space;
		_Locale.n_sign_posn = p->_Lc.n_sign_posn;
		_Locale.p_cs_precedes = p->_Lc.p_cs_precedes;
		_Locale.p_sep_by_space = p->_Lc.p_sep_by_space;
		_Locale.p_sign_posn = p->_Lc.p_sign_posn;
		break;
	case LC_NUMERIC:
		_Locale.decimal_point = p->_Lc.decimal_point[0] != '\0'
			? p->_Lc.decimal_point : ".";
		_Locale.grouping = p->_Lc.grouping;
		_Locale.thousands_sep = p->_Lc.thousands_sep;
		break;
	case LC_TIME:
		_Times = p->_Times;
		break;
		}
	return (p);
	}
