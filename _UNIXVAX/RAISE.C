/* raise function -- UNIX version */
#include <signal.h>

		/* UNIX system calls */
int _Getpid(void);
int _Kill(int, int);

int (raise)(int sig)
	{	/* raise a signal */
	return (_Kill(_Getpid(), sig));
	}
