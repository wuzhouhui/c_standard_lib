/* yfuns.h functions header -- UNIX version */
#ifndef _YFUNS
#define _YFUNS
		/* process control functions */
#define _Envp	(*environ)
#define _Exit(status)	_exit(status)
		/* stdio functions */
#define _Fclose(str)	close((str)->_Handle)
#define _Fread(str, buf, cnt)	read((str)->_Handle, buf, cnt)
#define _Fwrite(str, buf, cnt)	write((str)->_Handle, buf, cnt)
		/* interface declarations */
extern const char **environ;
int close(int);
void _exit(int);
int read(int, unsigned char *, int);
int write(int, const unsigned char *, int);
#endif
