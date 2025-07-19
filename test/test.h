#if defined(__slimcc__) || defined(__chibicc__)
#define ASSERT(x, y) assert(x, y, #y)
#define DASSERT(x) static_assert(x); ASSERT(1, x)
#define EASSERT(x,y) static_assert((x) == (y)); ASSERT(x, y)

void assert(int expected, int actual, char *code);

int printf(char *fmt, ...);
int sprintf(char *buf, char *fmt, ...);
int vsprintf(char *buf, char *fmt, void *ap);
int strcmp(char *p, char *q);
int strncmp(char *p, char *q, long n);
int memcmp(char *p, char *q, long n);
void exit(int n);
int vsprintf();
long strlen(char *s);
void *memcpy(void *dest, void *src, long n);
void *memset(void *s, int c, long n);
#else
#include <stdio.h>
#include <string.h>
extern void assert(int expected, int actual, char *code);
#endif
