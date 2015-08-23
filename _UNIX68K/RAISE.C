/* raise function -- UNIX version */
#include <signal.h>

		/* UNIX system calls */
int getpid(void);
int kill(int, int);

int (raise)(int sig)
	{	/* raise a signal */
	return (kill(getpid(), sig));
	}
