/* test math functions -- part 1 */
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static double eps;

static int approx(double d1, double d2)
	{	/* test for approximate equality */
	if (d2 != 0)
		return (fabs((d2 - d1) / d2) < eps);
	else
		return (fabs(d1) < eps);
	}

int main()
	{	/* test basic workings of math functions */
	double huge_val, x;
	int xexp;

	huge_val = HUGE_VAL;
	eps = DBL_EPSILON * 4.0;
	assert(ceil(-5.1) == -5.0);
	assert(ceil(-5.0) == -5.0);
	assert(ceil(-4.9) == -4.0);
	assert(ceil(0.0) == 0.0);
	assert(ceil(4.9) == 5.0);
	assert(ceil(5.0) == 5.0);
	assert(ceil(5.1) == 6.0);
	assert(fabs(-5.0) == 5.0);
	assert(fabs(0.0) == 0.0);
	assert(fabs(5.0) == 5.0);
	assert(floor(-5.1) == -6.0);
	assert(floor(-5.0) == -5.0);
	assert(floor(-4.9) == -5.0);
	assert(floor(0.0) == 0.0);
	assert(floor(4.9) == 4.0);
	assert(floor(5.0) == 5.0);
	assert(floor(5.1) == 5.0);
	assert(fmod(-7.0, 3.0) == -1.0);
	assert(fmod(-3.0, 3.0) == 0.0);
	assert(fmod(-2.0, 3.0) == -2.0);
	assert(fmod(0.0, 3.0) == 0.0);
	assert(fmod(2.0, 3.0) == 2.0);
	assert(fmod(3.0, 3.0) == 0.0);
	assert(fmod(7.0, 3.0) == 1.0);
	assert(approx(frexp(-3.0, &xexp), -0.75) && xexp == 2);
	assert(approx(frexp(-0.5, &xexp), -0.5) && xexp == 0);
	assert(frexp(0.0, &xexp) == 0.0 && xexp == 0);
	assert(approx(frexp(0.33, &xexp), 0.66) && xexp == -1);
	assert(approx(frexp(0.66, &xexp), 0.66) && xexp == 0);
	assert(approx(frexp(96.0, &xexp), 0.75) && xexp == 7);
	assert(ldexp(-3.0, 4) == -48.0);
	assert(ldexp(-0.5, 0) == -0.5);
	assert(ldexp(0.0, 36) == 0.0);
	assert(approx(ldexp(0.66, -1), 0.33));
	assert(ldexp(96, -3) == 12.0);
	assert(approx(modf(-11.7, &x), -11.7 + 11.0)
		&& x == -11.0);
	assert(modf(-0.5, &x) == -0.5 && x == 0.0);
	assert(modf(0.0, &x) == 0.0 && x == 0.0);
	assert(modf(0.6, &x) == 0.6 && x == 0.0);
	assert(modf(12.0, &x) == 0.0 && x == 12.0);
	printf("HUGE_VAL prints as %.16e\n", huge_val);
	puts("SUCCESS testing <math.h>, part 1");
	return (0);
	}
