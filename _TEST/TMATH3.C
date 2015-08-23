/* test math functions -- part 3 */
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static double eps;

static int approx(double d1, double d2)
	{	/* test for approximate equality */
	return ((d2 ? fabs((d2 - d1) / d2) : fabs(d1)) < eps);
	}

int main()
	{	/* test basic workings of math functions */
	static double e = {2.71828182845904523536};
	static double ln2 = {0.69314718055994530942};
	static double rthalf = {0.70710678118654752440};

	eps = DBL_EPSILON * 4.0;
	assert(approx(cosh(-1.0), (e + 1.0 / e) / 2.0));
	assert(approx(cosh(0.0), 1.0));
	assert(approx(cosh(1.0), (e + 1.0 / e) / 2.0));
	assert(approx(exp(-1.0), 1.0 / e));
	assert(approx(exp(0.0), 1.0));
	assert(approx(exp(ln2), 2.0));
	assert(approx(exp(1.0), e));
	assert(approx(exp(3.0), e * e * e));
	assert(log(1.0) == 0.0);
	assert(approx(log(e), 1.0));
	assert(approx(log(e * e * e), 3.0));
	assert(approx(log10(1.0), 0.0));
	assert(approx(log10(5.0), 1.0 - log10(2.0)));
	assert(approx(log10(1e5), 5.0));
	assert(approx(pow(-2.5, 2.0), 6.25));
	assert(approx(pow(-2.0, -3.0), -0.125));
	assert(pow(0.0, 6.0) == 0.0);
	assert(approx(pow(2.0, -0.5), rthalf));
	assert(approx(pow(3.0, 4.0), 81.0));
	assert(approx(sinh(-1.0), -(e - 1.0 / e) / 2.0));
	assert(approx(sinh(0.0), 0.0));
	assert(approx(sinh(1.0), (e - 1.0 / e) / 2.0));
	assert(approx(sqrt(0.0), 0.0));
	assert(approx(sqrt(0.5), rthalf));
	assert(approx(sqrt(1.0), 1.0));
	assert(approx(sqrt(2.0), 1.0 / rthalf));
	assert(approx(sqrt(144.0), 12.0));
	assert(approx(tanh(-1.0), -(e * e - 1.0) / (e * e + 1.0)));
	assert(approx(tanh(0.0), 0.0));
	assert(approx(tanh(1.0), (e * e - 1.0) / (e * e + 1.0)));
	puts("SUCCESS testing <math.h>, part 3");
	return (0);
	}
