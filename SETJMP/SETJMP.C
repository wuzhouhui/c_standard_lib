/* setjmp function */
#include <setjmp.h>
#include <string.h>

static void dummy(int a, int b, int c, int d, int e,
	int f, int g, int h, int i, int j)
	{	/* threaten to use arguments */
	}

static int getfp(void)
	{	/* return frame pointer of caller */
	int arg;

	return ((int)(&arg + _JBFP));
	}

int setjmp(jmp_buf env)
	{	/* save environment for re-return */
	register int a = 0, b = 0, c = 0, d = 0, e = 0;
	register int f = 0, g = 0, h = 0, i = 0, j = 0;

	if (a)	/* try to outsmart optimizer */
		dummy(a, b, c, d, e, f, g, h, i, j);
	env[1] = getfp();
	memcpy((char *)&env[2], (char *)env[1] + _JBOFF, _JBMOV);
	return (0);
	}
