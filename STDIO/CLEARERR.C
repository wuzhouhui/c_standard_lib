/* clearerr function */
#include "xstdio.h"

void (clearerr)(FILE *str)
	{	/* clear EOF and error indicators for a stream */
	if (str->_Mode & (_MOPENR|_MOPENW))
		str->_Mode &= ~(_MEOF|_MERR);
	}
