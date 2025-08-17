#if defined(__slimcc__) || defined(__chibicc__)
#include <stdio.h>
#define ASSERT(x, y) assert(x, y, #y)
#define DASSERT(x) static_assert(x); ASSERT(1, x)
#define EASSERT(x,y) static_assert((x) == (y)); ASSERT(x, y)
#define LASSERT(x, y) assert64(x, y, #y)
#define ASSERT128(x, y) assert128(x, y, #y, __FILE__, __LINE__)
void assert128(__int128, __int128, char *, char *, int);

void assert(int expected, int actual, char *code);
void assert64(long long expected, long long actual, char *code);

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
extern void assert128(__int128, __int128, char *, char *, int);
#define ASSERT(x, y) assert(x, y, #y)
#define LASSERT(x, y) assert(x, y, #y)
#define ASSERT128(x, y) assert128(x, y, #y, __FILE__, __LINE__)
#endif
