/* yvals.h values header -- Turbo C++ version */
#define _YVALS
		/* errno properties */
#define _EDOM	33
#define _ERANGE	34
#define _EFPOS	35
#define _ERRMAX	36
		/* float properties */
#define _D0		3
#define _DBIAS	0x3fe
#define _DLONG	1
#define _DOFF	4
#define _FBIAS	0x7e
#define _FOFF	7
#define _FRND	1
#define _LBIAS	0x3ffe
#define _LOFF	15
		/* integer properties */
#define _C2		1
#define _CSIGN	1
#define _ILONG	0
#define _MBMAX	8
typedef unsigned short _Wchart;
		/* pointer properties */
#define _NULL	(void *)0
typedef int _Ptrdifft;
typedef unsigned int _Sizet;
		/* setjmp properties */
#define _NSETJMP	10
#define _Setjmp(env)	setjmp(env)
#ifdef __cplusplus
extern "C" int setjmp(int *);
#else
int setjmp(int *);
#endif
		/* signal properties */
#define _SIGABRT	22
#define _SIGMAX		32
		/* stdio properties */
#define _FNAMAX	64
#define _FOPMAX	16
#define _TNAMAX	16
		/* stdlib properties */
#define _EXFAIL	1
		/* storage alignment properties */
#define _AUPBND	1U
#define _ADNBND	1U
#define _MEMBND	1U
		/* time properties */
#define _CPS	1
#define _TBIAS	((70 * 365LU + 17) * 86400)
