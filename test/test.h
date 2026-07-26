#if defined(__slimcc__) || defined(__chibicc__)
#include <stdio.h>
#undef assert
#define ASSERT(x, y) assert(x, y, #y)
#define DASSERT(x) _Static_assert((x), ""); ASSERT(1, x)
#define EASSERT(x, y) _Static_assert((x) == (y), ""); ASSERT(x, y)
#define LASSERT(x, y) assert64(x, y, #y)
#define SASSERT(x) _Static_assert(x,"")
#define RASSERT(x) assert(1, x, #x) 
#define ASSERT128(x, y) assert128(x, y, #y, __FILE__, __LINE__)
void assert128(__int128, __int128, char *, char *, int);

void assert(int expected, int actual, char *code);
void assert64(long long expected, long long actual, char *code);

int printf(const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list ap);
int strcmp(const char *p, const char *q);
int strncmp(const char *p, const char *q, size_t n);
int memcmp(const void *p, const void *q, size_t n);
void exit(int n);
size_t strlen(const char *s);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
#else
#include <stdio.h>
#include <string.h>
#undef assert
extern void assert(int expected, int actual, char *code);
extern void assert128(__int128, __int128, char *, char *, int);
#define ASSERT(x, y) assert(x, y, #y)
#define LASSERT(x, y) assert(x, y, #y)
#define DASSERT(x) _Static_assert((x), ""); ASSERT(1, x)
#define EASSERT(x, y) _Static_assert((x) == (y), ""); ASSERT(x, y)
#define SASSERT(x) _Static_assert(x,"")
#define ASSERT128(x, y) assert128(x, y, #y, __FILE__, __LINE__)
#define RASSERT(x) assert(1, x, #x) 
#endif
