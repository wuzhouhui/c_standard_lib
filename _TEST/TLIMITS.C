/* test limits macros */
#include <limits.h>
#include <stdio.h>

int main()
	{	/* test basic properties of limits.h macros */
	printf("CHAR_BIT = %2i   MB_LEN_MAX = %2i\n\n",
		CHAR_BIT, MB_LEN_MAX);
	printf(" CHAR_MAX = %10i   CHAR_MIN = %10i\n",
		CHAR_MAX, CHAR_MIN);
	printf("SCHAR_MAX = %10i  SCHAR_MIN = %10i\n",
		SCHAR_MAX, SCHAR_MIN);
	printf("UCHAR_MAX = %10u\n\n", UCHAR_MAX);
	printf(" SHRT_MAX = %10i   SHRT_MIN = %10i\n",
		SHRT_MAX, SHRT_MIN);
	printf("USHRT_MAX = %10u\n\n", USHRT_MAX);
	printf("  INT_MAX = %10i    INT_MIN = %10i\n",
		INT_MAX, INT_MIN);
	printf(" UINT_MAX = %10u\n\n", UINT_MAX);
	printf(" LONG_MAX = %10li   LONG_MIN = %10li\n",
		LONG_MAX, LONG_MIN);
	printf("ULONG_MAX = %10lu\n", ULONG_MAX);
#if CHAR_BIT < 8 || CHAR_MAX < 127 || 0 < CHAR_MIN \
	|| CHAR_MAX != SCHAR_MAX && CHAR_MAX != UCHAR_MAX
#error bad char properties
#endif
#if INT_MAX < 32767 || -32767 < INT_MIN || INT_MAX < SHRT_MAX
#error bad int properties
#endif
#if LONG_MAX < 2147483647 || -2147483647 < LONG_MIN \
	|| LONG_MAX < INT_MAX
#error bad long properties
#endif
#if MB_LEN_MAX < 1
#error bad MB_LEN_MAX
#endif
#if SCHAR_MAX < 127 || -127 < SCHAR_MIN
#error bad signed char properties
#endif
#if SHRT_MAX < 32767 || -32767 < SHRT_MIN \
	|| SHRT_MAX < SCHAR_MAX
#error bad short properties
#endif
#if UCHAR_MAX < 255 || UCHAR_MAX / 2 < SCHAR_MAX
#error bad unsigned char properties
#endif
#if UINT_MAX < 65535 || UINT_MAX / 2 < INT_MAX \
	|| UINT_MAX < USHRT_MAX
#error bad unsigned int properties
#endif
#if ULONG_MAX < 4294967295 || ULONG_MAX / 2 < LONG_MAX \
	|| ULONG_MAX < UINT_MAX
#error bad unsigned long properties
#endif
#if USHRT_MAX < 65535 || USHRT_MAX / 2 < SHRT_MAX \
	|| USHRT_MAX < UCHAR_MAX
#error bad unsigned short properties
#endif
	puts("SUCCESS testing <limits.h>");
	return (0);
	}
