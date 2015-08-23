/* test float macros */
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

int main()
	{	/* test basic properties of float.h macros */
	double radlog;
	int digs;
	static int radix = FLT_RADIX;

	printf("FLT_RADIX = %i\n\n", FLT_RADIX);
	printf("DBL_DIG =        %5i   DBL_MANT_DIG =  %6i\n",
		DBL_DIG, DBL_MANT_DIG);
	printf("DBL_MAX_10_EXP = %5i   DBL_MAX_EXP =   %6i\n",
		DBL_MAX_10_EXP, DBL_MAX_EXP);
	printf("DBL_MIN_10_EXP = %5i   DBL_MIN_EXP =   %6i\n",
		DBL_MIN_10_EXP, DBL_MIN_EXP);
	printf("      DBL_EPSILON =  %le\n", DBL_EPSILON);
	printf("      DBL_MAX =      %le\n", DBL_MAX);
	printf("      DBL_MIN =      %le\n\n", DBL_MIN);
	printf("FLT_DIG =        %5i   FLT_MANT_DIG =  %6i\n",
		FLT_DIG, FLT_MANT_DIG);
	printf("FLT_MAX_10_EXP = %5i   FLT_MAX_EXP =   %6i\n",
		FLT_MAX_10_EXP, FLT_MAX_EXP);
	printf("FLT_MIN_10_EXP = %5i   FLT_MIN_EXP =   %6i\n",
		FLT_MIN_10_EXP, FLT_MIN_EXP);
	printf("      FLT_EPSILON =  %e\n", FLT_EPSILON);
	printf("      FLT_MAX =      %e\n", FLT_MAX);
	printf("      FLT_MIN =      %e\n\n", FLT_MIN);
	printf("LDBL_DIG =        %5i  LDBL_MANT_DIG = %6i\n",
		LDBL_DIG, LDBL_MANT_DIG);
	printf("LDBL_MAX_10_EXP = %5i  LDBL_MAX_EXP =  %6i\n",
		LDBL_MAX_10_EXP, LDBL_MAX_EXP);
	printf("LDBL_MIN_10_EXP = %5i  LDBL_MIN_EXP =  %6i\n",
		LDBL_MIN_10_EXP, LDBL_MIN_EXP);
	printf("      LDBL_EPSILON = %Le\n", LDBL_EPSILON);
	printf("      LDBL_MAX =     %Le\n", LDBL_MAX);
	printf("      LDBL_MIN =     %Le\n", LDBL_MIN);
	radlog = log10(radix);
		/* test double properties */
	assert(10 <= DBL_DIG && FLT_DIG <= DBL_DIG);
	assert(DBL_EPSILON <= 1e-9);
	digs = (DBL_MANT_DIG - 1) * radlog;
	assert(digs <= DBL_DIG && DBL_DIG <= digs + 1);
	assert(1e37 <= DBL_MAX);
	assert(37 <= DBL_MAX_10_EXP);
#if FLT_RADIX == 2
	assert(ldexp(1.0, DBL_MAX_EXP - 1) < DBL_MAX);
	assert(ldexp(1.0, DBL_MIN_EXP - 1) == DBL_MIN);
#endif
	assert(DBL_MIN <= 1e-37);
	assert(DBL_MIN_10_EXP <= -37);
		/* test float properties */
	assert(6 <= FLT_DIG);
	assert(FLT_EPSILON <= 1e-5);
	digs = (FLT_MANT_DIG - 1) * radlog;
	assert(digs <= FLT_DIG && FLT_DIG <= digs + 1);
	assert(1e37 <= FLT_MAX);
	assert(37 <= FLT_MAX_10_EXP);
#if FLT_RADIX == 2
	assert(ldexp(1.0, FLT_MAX_EXP - 1) < FLT_MAX);
	assert(ldexp(1.0, FLT_MIN_EXP - 1) == FLT_MIN);
#endif
	assert(FLT_MIN <= 1e-37);
	assert(FLT_MIN_10_EXP <= -37);
		/* test universal properties */
#if FLT_RADIX < 2
#error bad FLT_RADIX
#endif
	assert(-1 <= FLT_ROUNDS && FLT_ROUNDS <= 3);
		/* test long double properties */
	assert(10 <= LDBL_DIG && DBL_DIG <= LDBL_DIG);
	assert(LDBL_EPSILON <= 1e-9);
	digs = (LDBL_MANT_DIG - 1) * radlog;
	assert(digs <= LDBL_DIG && LDBL_DIG <= digs + 1);
	assert(1e37 <= LDBL_MAX);
	assert(37 <= LDBL_MAX_10_EXP);
#if FLT_RADIX == 2
	assert(DBL_MAX_EXP < LDBL_MAX_EXP
		|| ldexp(1.0, LDBL_MAX_EXP - 1) < LDBL_MAX);
	assert(LDBL_MIN_EXP < DBL_MIN_EXP
		|| ldexp(1.0, LDBL_MIN_EXP - 1) == LDBL_MIN);
#endif
	assert(LDBL_MIN <= 1e-37);
	assert(LDBL_MIN_10_EXP <= -37);
	puts("SUCCESS testing <float.h>");
	return (0);
	}
