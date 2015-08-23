/* test assert macro */
#define NDEBUG
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

		/* static data */
static int val = 0;

static void field_abort(int sig)
	{	/* handle SIGABRT */
	if (val == 1)
		{	/* expected result */
		puts("SUCCESS testing <assert.h>");
		exit(EXIT_SUCCESS);
		}
	else
		{	/* unexpected result */
		puts("FAILURE testing <assert.h>");
		exit(EXIT_FAILURE);
		}
	}

static void dummy()
	{	/* test dummy assert macro */
	int i = 0;

	assert(i == 0);
	assert(i == 1);
	}

#undef NDEBUG
#include <assert.h>

int main()
	{	/* test both dummy and working forms */
	assert(signal(SIGABRT, &field_abort) != SIG_ERR);
	dummy();
	assert(val == 0);	/* should not abort */
	++val;
	fputs("Sample assertion failure message --\n", stderr);
	assert(val == 0);	/* should abort */
	puts("FAILURE testing <assert.h>");
	return (EXIT_FAILURE);
	}
