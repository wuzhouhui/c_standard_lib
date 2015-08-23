/* longjmp function */
#include <setjmp.h>
#include <string.h>

static void dummy(int a, int b, int c, int d, int e,
	int f, int g, int h, int i, int j)
	{	/* threaten to use arguments */
	}

static void setfp(int fp)
	{	/* set frame pointer of caller */
	int arg;

	(&arg)[_JBFP] = fp;
	}

static int dojmp(jmp_buf env)
	{	/* do the actual dirty business */
	memcpy((char *)env[1] + _JBOFF, (char *)&env[2], _JBMOV);
	setfp(env[1]);
	return (env[0]);
	}

void longjmp(jmp_buf env, int val)
	{	/* re-return from setjmp */
	register int a = 0, b = 0, c = 0, d = 0, e = 0;
	register int f = 0, g = 0, h = 0, i = 0, j = 0;

	if (a)	/* try to outsmart optimizer */
		dummy(a, b, c, d, e, f, g, h, i, j);
	env[0] = val ? val : 1;
	dojmp(env);
	}
