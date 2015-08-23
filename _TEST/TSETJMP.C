/* test setjmp functions */
#include <assert.h>
#include <setjmp.h>
#include <stdio.h>

		/* static data */
static int ctr;
static jmp_buf b0;

static void jmpto(int n)
	{	/* jump on static buffer */
	longjmp(b0, n);
	}

static char *stackptr(void)
	{	/* test for stack creep */
	char ch;

	return (&ch);
	}

static int tryit(void)
	{	/* exercise jumps */
	jmp_buf b1;
	char *sp = stackptr();

	ctr = 0;
	switch (setjmp(b0))
		{	/* jump among cases */
	case 0:
		assert(sp == stackptr());
		assert(ctr == 0);
		++ctr;
		jmpto(0);	/* should return 1 */
		break;
	case 1:
		assert(sp == stackptr());
		assert(ctr == 1);
		++ctr;
		jmpto(2);
		break;
	case 2:
		assert(sp == stackptr());
		assert(ctr == 2);
		++ctr;
		switch (setjmp(b1))
			{	/* test nesting */
		case 0:
			assert(sp == stackptr());
			assert(ctr == 3);
			++ctr;
			longjmp(b1, -7);
			break;
		case -7:
			assert(sp == stackptr());
			assert(ctr == 4);
			++ctr;
			jmpto(3);
		case 5:
			return (13);
		default:
			return (0);
			}
	case 3:
		longjmp(b1, 5);
		break;
		}
	return (-1);
	}

int main()
	{	/* test basic workings of setjmp functions */
	assert(tryit() == 13);
	printf("sizeof (jmp_buf) = %u\n", sizeof (jmp_buf));
	puts("SUCCESS testing <setjmp.h>");
	return (0);
	}
