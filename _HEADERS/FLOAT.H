/* float.h standard header -- IEEE 754 version */
#ifndef _FLOAT
#define _FLOAT
#ifndef _YVALS
#include <yvals.h>
#endif
		/* type definitions */
typedef struct {
	int _Ddig, _Dmdig, _Dmax10e, _Dmaxe, _Dmin10e, _Dmine;
	union {
		unsigned short _Us[5];
		float _F;
		double _D;
		long double _Ld;
		} _Deps, _Dmax, _Dmin;
	} _Dvals;
		/* declarations */
extern _Dvals _Dbl, _Flt, _Ldbl;
		/* double properties */
#define DBL_DIG			_Dbl._Ddig
#define DBL_EPSILON		_Dbl._Deps._D
#define DBL_MANT_DIG	_Dbl._Dmdig
#define DBL_MAX			_Dbl._Dmax._D
#define DBL_MAX_10_EXP	_Dbl._Dmax10e
#define DBL_MAX_EXP		_Dbl._Dmaxe
#define DBL_MIN			_Dbl._Dmin._D
#define DBL_MIN_10_EXP	_Dbl._Dmin10e
#define DBL_MIN_EXP		_Dbl._Dmine
		/* float properties */
#define FLT_DIG			_Flt._Ddig
#define FLT_EPSILON		_Flt._Deps._F
#define FLT_MANT_DIG	_Flt._Dmdig
#define FLT_MAX			_Flt._Dmax._F
#define FLT_MAX_10_EXP	_Flt._Dmax10e
#define FLT_MAX_EXP		_Flt._Dmaxe
#define FLT_MIN			_Flt._Dmin._F
#define FLT_MIN_10_EXP	_Flt._Dmin10e
#define FLT_MIN_EXP		_Flt._Dmine
		/* common properties */
#define FLT_RADIX		2
#define FLT_ROUNDS		_FRND
		/* long double properties */
#define LDBL_DIG		_Ldbl._Ddig
#define LDBL_EPSILON	_Ldbl._Deps._Ld
#define LDBL_MANT_DIG	_Ldbl._Dmdig
#define LDBL_MAX		_Ldbl._Dmax._Ld
#define LDBL_MAX_10_EXP	_Ldbl._Dmax10e
#define LDBL_MAX_EXP	_Ldbl._Dmaxe
#define LDBL_MIN		_Ldbl._Dmin._Ld
#define LDBL_MIN_10_EXP	_Ldbl._Dmin10e
#define LDBL_MIN_EXP	_Ldbl._Dmine
#endif
