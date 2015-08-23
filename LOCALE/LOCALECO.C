/* localeconv function */
#include <limits.h>
#include <locale.h>

		/* static data */
static char null[] = "";
struct lconv _Locale = {
		/* LC_MONETARY */
	null,					/* currency_symbol */
	null,					/* int_curr_symbol */
	null,					/* mon_decimal_point */
	null,					/* mon_grouping */
	null,					/* mon_thousands_sep */
	null,					/* negative_sign */
	null,					/* positive_sign */
	CHAR_MAX,				/* frac_digits */
	CHAR_MAX,				/* int_frac_digits */
	CHAR_MAX,				/* n_cs_precedes */
	CHAR_MAX,				/* n_sep_by_space */
	CHAR_MAX,				/* n_sign_posn */
	CHAR_MAX,				/* p_cs_precedes */
	CHAR_MAX,				/* p_sep_by_space */
	CHAR_MAX,				/* p_sign_posn */
		/* LC_NUMERIC */
	".",					/* decimal_point */
	null,					/* grouping */
	null};					/* thousands_sep */

struct lconv *(localeconv)(void)
	{	/* get pointer to current locale */
	return (&_Locale);
	}
