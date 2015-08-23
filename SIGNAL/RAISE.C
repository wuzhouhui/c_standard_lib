/* raise function -- simple version */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

		/* static data */
_Sigfun *_Sigtable[_NSIG] = {0};	/* handler table */

int (raise)(int sig)
	{	/* raise a signal */
	_Sigfun *s;

	if (sig <= 0 || _NSIG <= sig)
		return (-1);	/* bad signal */
	if ((s = _Sigtable[sig]) != SIG_IGN && s != SIG_DFL)
		{	/* revert and call handler */
		_Sigtable[sig] = SIG_DFL;
		(*s)(sig);
		}
	else if (s == SIG_DFL)
		{	/* default handling */
		char ac[10], *p;

		switch (sig)
			{	/* print known signals by name */
		case SIGABRT:
			p = "abort";
			break;
		case SIGFPE:
			p = "arithmetic error";
			break;
		case SIGILL:
			p = "invalid executable code";
			break;
		case SIGINT:
			p = "interruption";
			break;
		case SIGSEGV:
			p = "invalid storage access";
			break;
		case SIGTERM:
			p = "termination request";
			break;
		default:
			*(p = &ac[(sizeof ac) - 1]) = '\0';
			do *--p = sig % 10 + '0';
				while ((sig /= 10) != 0);
			fputs("signal #", stderr);
			}
		fputs(p, stderr);
		fputs(" -- terminating\n", stderr);
		exit(EXIT_FAILURE);
		}
	return (0);
	}
