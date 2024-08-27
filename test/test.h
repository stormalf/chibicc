#define ASSERT(x, y) assert(x, y, #y)
void assert(int expected, int actual, char *code);

#define ASSERT128(x, y) assert128(x, y, #y, __FILE__, __LINE__)
void assert128(__int128, __int128, char *, char *, int);

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
