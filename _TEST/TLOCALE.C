/* test locales */
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

static void testclocale(struct lconv *p)
	{	/* test properties of "C" locale */
	assert(strcmp(p->currency_symbol, "") == 0);
	assert(strcmp(p->decimal_point, ".") == 0);
	assert(strcmp(p->grouping, "") == 0);
	assert(strcmp(p->int_curr_symbol, "") == 0);
	assert(strcmp(p->mon_decimal_point, "") == 0);
	assert(strcmp(p->mon_grouping, "") == 0);
	assert(strcmp(p->mon_thousands_sep, "") == 0);
	assert(strcmp(p->negative_sign, "") == 0);
	assert(strcmp(p->positive_sign, "") == 0);
	assert(strcmp(p->thousands_sep, "") == 0);
	assert(p->frac_digits == CHAR_MAX);
	assert(p->int_frac_digits == CHAR_MAX);
	assert(p->n_cs_precedes == CHAR_MAX);
	assert(p->n_sep_by_space == CHAR_MAX);
	assert(p->n_sign_posn == CHAR_MAX);
	assert(p->p_cs_precedes == CHAR_MAX);
	assert(p->p_sep_by_space == CHAR_MAX);
	assert(p->p_sign_posn == CHAR_MAX);
	}

int main()
	{	/* test basic properties of locales */
	static int cats[] = {LC_ALL, LC_COLLATE, LC_CTYPE,
		LC_MONETARY, LC_NUMERIC, LC_TIME};
	struct lconv *p = NULL;
	char buf[32], *s;

	assert((p = localeconv()) != NULL);
	testclocale(p);
	assert((s = setlocale(LC_ALL, NULL)) != NULL);
	assert(strlen(s) < sizeof (buf));	/* OK if longer */
	strcpy(buf, s);	/* but not safe for this program */
	assert(setlocale(LC_ALL, "") != NULL);
	assert(localeconv() != NULL);
	assert((s = setlocale(LC_MONETARY, "C")) != NULL);
	puts(strcmp(s, "C") ? "Native locale differs from \"C\""
		: "Native locale same as \"C\"");
	assert(setlocale(LC_NUMERIC, "C") != NULL);
	assert((p = localeconv()) != NULL);
	testclocale(p);
	assert(setlocale(LC_ALL, buf) != NULL);
	assert((p = localeconv()) != NULL);
	testclocale(p);
	puts("SUCCESS testing <locale.h>");
	return (0);
	}
