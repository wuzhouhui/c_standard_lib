/* fflush function */
#include "xstdio.h"
#include "yfuns.h"

int (fflush)(FILE *str)
	{	/* flush an output stream */
	int n;
	unsigned char *s;

	if (str == NULL)
		{	/* recurse on all streams */
		int nf, stat;

		for (stat = 0, nf = 0; nf < FOPEN_MAX; ++nf)
			if (_Files[nf] && fflush(_Files[nf]) < 0)
				stat = EOF;
		return (stat);
		}
	if (!(str->_Mode & _MWRITE))
		return (0);
	for (s = str->_Buf; s < str->_Next; s += n)
		{	/* try to write buffer */
		n = _Fwrite(str, s, str->_Next - s);
		if (n <= 0)
			{	/* report error and fail */
			str->_Next = str->_Buf;
			str->_Wend = str->_Buf;
			str->_Mode |= _MERR;
			return (EOF);
			}
		}
	str->_Next = str->_Buf;
	str->_Wend = str->_Bend;
	return (0);
	}
