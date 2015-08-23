/* _Files data object */
#include "xstdio.h"

/* standard error buffer */
static unsigned char ebuf[80];

/* the standard streams */
static FILE sin = {	/* standard input */
	_MOPENR, 0,
	NULL, NULL, &sin._Cbuf,
	&sin._Cbuf, NULL, &sin._Cbuf, };
static FILE sout = {	/* standard output */
	_MOPENW, 1,
	NULL, NULL, &sout._Cbuf,
	&sout._Cbuf, NULL, &sout._Cbuf, };
static FILE serr = {	/* standard error */
	_MOPENW|_MNBF, 2,
	ebuf, ebuf + sizeof (ebuf), ebuf,
	ebuf, NULL, ebuf, };

/* the array of stream pointers */
FILE *_Files[FOPEN_MAX] = {&sin, &sout, &serr};
