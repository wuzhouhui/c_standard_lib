/* test stdio functions, part 1 */
#include <assert.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void vfp(const char *fmt, ...)
	{	/* test vfprintf */
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);
	}

static void vp(const char *fmt, ...)
	{	/* test vprintf */
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	}

static void vsp(char *s, const char *fmt, ...)
	{	/* test vsprintf */
	va_list ap;

	va_start(ap, fmt);
	vsprintf(s, fmt, ap);
	va_end(ap);
	}

int main()
	{	/* test basic workings of stdio functions */
	char buf[32], ch;
	double db;
	float fl;
	int in;
	long lo;
	long double ld;
	short sh;
	void *pv;

	assert(sprintf(buf, "%2c|%-4d|%.4o|%#lX",
		'a', -4, 8, 12L) == 16);
	assert(strcmp(buf, " a|-4  |0010|0XC") == 0);
	assert(sscanf(buf, " %c|%hd |%i|%lx",
		&ch, &sh, &in, &lo) == 4);
	assert(ch == 'a' && sh == -4 && in == 8 && lo == 12);
	assert(sprintf(buf, "%E|%.2f|%Lg",
		1.1e20, -3.346, .02L) == 23);
	assert(strcmp(buf, "1.100000E+20|-3.35|0.02") == 0);
	assert(sscanf(buf, "%e|%lg|%Lf", &fl, &db, &ld) == 3);
	assert(fabs(fl - 1.1e20) / 1.1e20 < 4 * FLT_EPSILON);
	assert(fabs(db + 3.35) / 3.35 < 4 * DBL_EPSILON);
	assert(fabs(ld - 0.02) / 0.02 < 4 * LDBL_EPSILON);
	assert(4 <= sprintf(buf, "|%%%n %p",
		&in, (void *)&ch) && in == 2);
	assert(sscanf(buf, "|%%%n %p", &in, &pv) == 1 && in == 2);
	 {	/* test formatted I/O */
	char buf[10];
	const char *tn = tmpnam(NULL);
	FILE *pf;
	fpos_t fp1, fp2;
	int in1, in2;
	long off;

	assert(tn != NULL && (pf = fopen(tn, "w+")) != NULL);
	setbuf(pf, NULL);
	assert(fprintf(pf, "123\n") == 4);
	assert((off = ftell(pf)) != -1);
	assert(fprintf(pf, "456\n") == 4);
	assert(fgetpos(pf, &fp1) == 0);
	assert(fprintf(pf, "789\n") == 4);
	rewind(pf);
	assert(fscanf(pf, "%i", &in1) == 1 && in1 == 123);
	assert(fsetpos(pf, &fp1) == 0);
	assert(fscanf(pf, "%i", &in1) == 1 && in1 == 789);
	assert(fseek(pf, off, SEEK_SET) == 0);
	assert(fscanf(pf, "%i", &in1) == 1 && in1 == 456);
	assert(fclose(pf) == 0
		&& freopen(tn, "r", stdin) == stdin);
	assert(setvbuf(stdin, buf, _IOLBF, sizeof (buf)) == 0);
	assert(scanf("%i", &in1) == 1 && in1 == 123);
	assert(fclose(stdin) == 0);
	assert((pf = fopen(tn, "w+b")) != NULL);
	 }
	printf("BUFSIZ = %u\n", BUFSIZ);
	printf("L_tmpnam = %u\n", L_tmpnam);
	printf("FILENAME_MAX = %u\n", FILENAME_MAX);
	printf("FOPEN_MAX = %u\n", FOPEN_MAX);
	printf("TMP_MAX = %u\n", TMP_MAX);
	vsp(buf, "SUC%c%s", 'C', "ESS");
	vfp("%s testing %s", buf, "<stdio.h>");
	vp(", part 1\n");
	return (0);
	}
