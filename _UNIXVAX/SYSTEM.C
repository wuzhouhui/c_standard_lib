/* system function -- UNIX version */
#include <stdlib.h>

		/* UNIX system calls */
int _Execl(const char *, const char *, ...);
int _Fork(void);
int _Wait (int *);

int (system)(const char *s)
	{	/* send text to system command line processor */
	if (s)
		{	/* not just a test */
		int pid = _Fork();

		if (pid < 0)
			;	/* fork failed */
		else if (pid == 0)
			{	/* continue here as child */
			_Execl("/bin/sh", "sh", "-c", s, NULL);
			exit(EXIT_FAILURE);
			}
		else	/* continue here as parent */
			while (_Wait(NULL) != pid)
				;	/* wait for child */
		}
	return (-1);
	}
