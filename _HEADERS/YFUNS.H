/* yfuns.h functions header -- Turbo C++ version */
#ifndef _YFUNS
#define _YFUNS
		/* process control functions */
#define _Envp	(*_C0environ)
#define _Exit(status)	_exit(status)
		/* stdio functions */
#define _Fclose(str)	_close((str)->_Handle)
#define _Fread(str, buf, cnt)	read((str)->_Handle, buf, cnt)
#define _Fwrite(str, buf, cnt)	write((str)->_Handle, buf, cnt)
		/* interface declarations */
extern const char **_C0environ;
int _close(int);
void _exit(int);
int read(int, unsigned char *, int);
int write(int, const unsigned char *, int);
#endif
