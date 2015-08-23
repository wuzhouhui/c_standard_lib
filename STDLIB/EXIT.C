/* exit function */
#include <stdio.h>
#include <stdlib.h>
#include "yfuns.h"

		/* macros */
#define NATS	32
		/* static data */
void (*_Atfuns[NATS])(void) = {0};
size_t _Atcount = {NATS};

void (exit)(int status)
	{	/* tidy up and exit to system */
	while (_Atcount < NATS)
		(*_Atfuns[_Atcount++])();
	 {	/* close all files */
	size_t i;

	for (i = 0; i < FOPEN_MAX; ++i)
		if (_Files[i])
			fclose(_Files[i]);
	 }
	_Exit(status);
	}
