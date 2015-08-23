/* xstate.h internal header */
		/* macros for finite state machines */
#define ST_CH		0x00ff
#define ST_STATE	0x0f00
#define ST_STOFF	8
#define ST_FOLD		0x8000
#define ST_INPUT	0x4000
#define ST_OUTPUT	0x2000
#define ST_ROTATE	0x1000
#define _NSTATE		16
		/* type definitions */
typedef struct {
	const unsigned short *_Tab[_NSTATE];
	} _Statab;
		/* declarations */
extern _Statab _Costate, _Mbstate, _Wcstate;
