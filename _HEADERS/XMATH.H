/* xmath.h internal header -- IEEE 754 version */
#include <errno.h>
#include <math.h>
#include <stddef.h>
#ifndef _YVALS
#include <yvals.h>
#endif
		/* IEEE 754 properties */
#define _DFRAC	((1<<_DOFF)-1)
#define _DMASK	(0x7fff&~_DFRAC)
#define _DMAX	((1<<(15-_DOFF))-1)
#define _DNAN	(0x8000|_DMAX<<_DOFF|1<<(_DOFF-1))
#define _DSIGN	0x8000
#define DSIGN(x)	(((unsigned short *)&(x))[_D0] & _DSIGN)
#define HUGE_EXP	(int)(_DMAX * 900L / 1000)
#define HUGE_RAD	3.37e9
#define SAFE_EXP	(_DMAX>>1)
		/* word offsets within double */
#if _D0==3
#define _D1		2	/* little-endian order */
#define _D2		1
#define _D3		0
#else
#define _D1		1	/* big-endian order */
#define _D2		2
#define _D3		3
#endif
		/* return values for _D functions */
#define FINITE	-1
#define INF		1
#define NAN		2
		/* declarations */
double _Atan(double, unsigned short);
short _Dint(double *, short);
short _Dnorm(unsigned short *);
short _Dscale(double *, short);
double _Dtento(double, short);
short _Dtest(double *);
short _Dunscale(short *, double *);
short _Exp(double *, short);
short _Ldunscale(short *, long double *);
double _Poly(double, const double *, int);
extern _Dconst _Inf, _Nan, _Rteps, _Xbig;
