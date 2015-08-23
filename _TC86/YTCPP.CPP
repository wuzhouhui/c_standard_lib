void abort(void);	/* C++ declarations */
void exit(int);

extern "C" {	/* C definitions */
void abort(int junk)
	{abort(); }
void exit(int status, int junk)
	{exit(status); }

unsigned int clock(int);	/* C declarations */
int _close(int, int);
void _exit(int, int);
char *getenv(const char *, int);
void longjmp(char *, int);
long lseek(int, long, int, int);
int open(const char *, unsigned int, unsigned int, int);
int read(int, unsigned char *, int, int);
int rename(const char *, const char *, int);
void *sbrk(int, int);
int system(const char *, int);
unsigned long time(unsigned long *, int);
int unlink(const char *, int);
int write(int, const unsigned char *, int, int);
}

unsigned int clock(void)	/* C++ definitions */
	{return (clock(0)); }
int _close(int fd)
	{return (_close(fd, 0)); }
void _exit(int status)
	{_exit(status, 0); }
char *getenv(const char *name)
	{return (getenv(name, 0)); }
void longjmp(int *env, int val)
	{longjmp((char *)env, val); }
long lseek(int fd, long off, int way)
	{return (lseek(fd, off, way, 0)); }
int open(const char *name, unsigned int mode, unsigned int mod)
	{return (open(name, mode, mod, 0)); }
int read(int fd, unsigned char *buf, int size)
	{return (read(fd, buf, size, 0)); }
int rename(const char *oldnm, const char *newnm)
	{return (rename(oldnm, newnm, 0)); }
void *sbrk(int size)
	{return (sbrk(size, 0)); }
int system(const char *cmd)
	{return (system(cmd, 0)); }
unsigned long time(unsigned long *pt)
	{return (time(pt, 0)); }
int unlink(const char *name)
	{return (unlink(name, 0)); }
int write(int fd, const unsigned char *buf, int size)
	{return (write(fd, buf, size, 0)); }
