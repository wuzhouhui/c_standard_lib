/* system function -- UNIX version */
#include <stdlib.h>

		/* UNIX system calls */
int execl(const char *, const char *, ...);
int fork(void);
int wait (int *);

int (system)(const char *s)
	{	/* send text to system command line processor */
	if (s)
		{	/* not just a test */
		int pid = fork();

		if (pid < 0)
			;	/* fork failed */
		else if (pid == 0)
			{	/* continue here as child */
			execl("/bin/sh", "sh", "-c", s, NULL);
			exit(EXIT_FAILURE);
			}
		else	/* continue here as parent */
			while (wait(NULL) != pid)
				;	/* wait for child */
		}
	return (-1);
	}
