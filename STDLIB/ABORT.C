/* abort function */
#include <stdlib.h>
#include <signal.h>

void (abort)(void)
	{	/* terminate abruptly */
	raise(SIGABRT);
	exit(EXIT_FAILURE);
	}
