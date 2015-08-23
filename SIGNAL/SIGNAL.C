/* signal function -- simple version */
#include <signal.h>

		/* external declarations */
extern _Sigfun *_Sigtable[_NSIG];

_Sigfun *(signal)(int sig, _Sigfun *fun)
	{	/* specify handling for a signal */
	_Sigfun *s;

	if (sig <= 0 || _NSIG <= sig || fun == SIG_ERR)
		return (SIG_ERR);	/* bad signal */
	/* add machine-dependent handling here */
	s = _Sigtable[sig], _Sigtable[sig] = fun;
	return (s);
	}
