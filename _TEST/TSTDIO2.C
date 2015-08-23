/* test stdio functions, part 2 */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main()
	{	/* test basic workings of stdio functions */
	char buf[32], tname[L_tmpnam], *tn;
	FILE *pf;
	static int macs[] = {
		_IOFBF, _IOLBF, _IONBF, BUFSIZ, EOF, FILENAME_MAX,
		FOPEN_MAX, TMP_MAX, SEEK_CUR, SEEK_END, SEEK_SET};

	assert(256 <= BUFSIZ && EOF < 0);
	assert(8 <= FOPEN_MAX && 25 <= TMP_MAX);
	assert(tmpnam(tname) == tname && strlen(tname) < L_tmpnam);
	assert((tn = tmpnam(NULL)) != NULL
		&& strcmp(tn, tname) != 0);
	pf = fopen(tname, "w");
	assert(pf != NULL
		&& pf != stdin && pf != stdout && pf != stderr);
	assert(feof(pf) == 0 && ferror(pf) == 0);
	assert(fgetc(pf) == EOF
		&& feof(pf) == 0 && ferror(pf) != 0);
	clearerr(pf);
	assert(ferror(pf) == 0);
	assert(fputc('a', pf) == 'a' && putc('b', pf) == 'b');
	assert(0 <= fputs("cde\n", pf));
	assert(0 <= fputs("fghij\n", pf));
	assert(fflush(pf) == 0);
	assert(fwrite("klmnopq\n", 2, 4, pf) == 4);
	assert(fclose(pf) == 0);
	assert(freopen(tname, "r", stdin) == stdin);
	assert(fgetc(stdin) == 'a' && getc(stdin) == 'b');
	assert(getchar() == 'c');
	assert(fgets(buf, sizeof (buf), stdin) == buf
		&& strcmp(buf, "de\n") == 0);
	assert(ungetc('x', stdin) == 'x');
	assert(gets(buf) == buf && strcmp(buf, "xfghij") == 0);
	assert(fread(buf, 2, 4, stdin) == 4
		&& strncmp(buf, "klmnopq\n", 8) == 0);
	assert(getchar() == EOF && feof(stdin) != 0);
	remove(tn);
	assert(rename(tname, tn) == 0
		&& fopen(tname, "r") == NULL);
	assert((pf = fopen(tn, "r")) != NULL && fclose(pf) == 0);
	assert(remove(tn) == 0 && fopen(tn, "r") == NULL);
	assert((pf = tmpfile()) != NULL && fputc('x', pf) == 'x');
	errno = EDOM;
	perror("Domain error reported as");
	putchar('S'), puts("UCCESS testing <stdio.h>, part 2");
	return (0);
	}
