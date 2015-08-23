/* yfuns.h functions header -- UNIX version */
#ifndef _YFUNS
#define _YFUNS
		/* macros */
#define _Envp	(*_Environ)
#define _Fclose(str)	_Close((str)->_Handle)
#define _Fread(str, buf, cnt)	_Read((str)->_Handle, buf, cnt)
#define _Fwrite(str, buf, cnt)	_Write((str)->_Handle, buf, cnt)
		/* interface declarations */
extern const char **_Environ;
int _Close(int);
void _Exit(int);
int _Read(int, unsigned char *, int);
int _Write(int, const unsigned char *, int);
#endif
