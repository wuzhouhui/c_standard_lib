/* _Dint function -- IEEE 754 version */
#include "xmath.h"

short _Dint(double *px, short xexp)
	{	/* test and drop (scaled) fraction bits */
	unsigned short *ps = (unsigned short *)px;
	unsigned short frac = ps[_D0] & _DFRAC
		|| ps[_D1] || ps[_D2] || ps[_D3];
	short xchar = (ps[_D0] & _DMASK) >> _DOFF;

	if (xchar == 0 && !frac)
		return (0);	/* zero */
	else if (xchar != _DMAX)
		;	/* finite */
	else if (!frac)
		return (INF);
	else
		{	/* NaN */
		errno = EDOM;
		return (NAN);
		}
	xchar = (_DBIAS+48+_DOFF+1) - xchar - xexp;
	if (xchar <= 0)
		return (0);	/* no frac bits to drop */
	else if ((48+_DOFF) < xchar)
		{	/* all frac bits */
		ps[_D0] = 0, ps[_D1] = 0;
		ps[_D2] = 0, ps[_D3] = 0;
		return (FINITE);
		}
	else
		{	/* strip out frac bits */
		static const unsigned short mask[] = {
			0x0000, 0x0001, 0x0003, 0x0007,
			0x000f, 0x001f, 0x003f, 0x007f,
			0x00ff, 0x01ff, 0x03ff, 0x07ff,
			0x0fff, 0x1fff, 0x3fff, 0x7fff};
		static const size_t sub[] = {_D3, _D2, _D1, _D0};

		frac = mask[xchar & 0xf];
		xchar >>= 4;
		frac &= ps[sub[xchar]];
		ps[sub[xchar]] ^= frac;
		switch (xchar)
			{	/* cascade through! */
		case 3:
			frac |= ps[_D1], ps[_D1] = 0;
		case 2:
			frac |= ps[_D2], ps[_D2] = 0;
		case 1:
			frac |= ps[_D3], ps[_D3] = 0;
			}
		return (frac ? FINITE : 0);
		}
	}
