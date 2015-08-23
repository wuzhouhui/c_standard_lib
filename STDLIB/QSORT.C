/* qsort function */
#include <stdlib.h>
#include <string.h>

		/* macros */
#define MAX_BUF	256		/* chunk to copy on swap */

void (qsort)(void *base, size_t n, size_t size, _Cmpfun *cmp)
	{	/* sort (char base[size])[n] using quicksort */
	while (1 < n)
		{	/* worth sorting */
		size_t i = 0;
		size_t j = n - 1;
		char *qi = (char *)base;
		char *qj = qi + size * j;
		char *qp = qj;

		while (i < j)
			{	/* partition about pivot */
			while (i < j && (*cmp)(qi, qp) <= 0)
				++i, qi += size;
			while (i < j && (*cmp)(qp, qj) <= 0)
				--j, qj -= size;
			if (i < j)
				{	/* swap elements i and j */
				char buf[MAX_BUF];
				char *q1 = qi;
				char *q2 = qj;
				size_t m, ms;

				for (ms = size; 0 < ms;
					ms -= m, q1 += m, q2 += m)
					{	/* swap as many as possible */
					m = ms < sizeof (buf) ? ms : sizeof (buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
					}
				++i, qi += size;
				}
			}
		if (qi != qp)
			{	/* swap elements i and pivot */
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qp;
			size_t m, ms;

			for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m)
				{	/* swap as many as possible */
				m = ms < sizeof (buf) ? ms : sizeof (buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
				}
			}
		j = n - i - 1, qi += size;
		if (j < i)
			{	/* recurse on smaller partition */
			if (1 < j)
				qsort(qi, j, size, cmp);
			n = i;
			}
		else
			{	/* lower partition is smaller */
			if (1 < i)
				qsort(base, i, size, cmp);
			base = qi;
			n = j;
			}
		}
	}
