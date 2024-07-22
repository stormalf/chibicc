


/* Does the compiler advertise C89 conformance?
    Do not test the value of __STDC__, because some compilers set it to 0
    while being otherwise adequately conformant. */
#if !defined __STDC__
# error "Compiler does not advertise C89 conformance"
#endif

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>

struct stat;
/* Most of the following tests are stolen from RCS 5.7 src/conf.sh.  */
struct buf { int x; };
struct buf * (*rcsopen) (struct buf *, struct stat *, int);
static char *e (p, i)
    char **p;
    int i;
{
return p[i];
}
static char *f (char * (*g) (char **, int), char **p, ...)
{
char *s;
va_list v;
va_start (v,p);
s = g (p, va_arg (v,int));
va_end (v);
return s;
}

int main()    {
    int i = 1;
    char *hello = "hello";
    char *name = "world";
    char *array[2] = { hello, name };
    char **p = &(array[0]);
    *(p+1) = array[1];
    char *p2= e (array, i);
    printf("%s\n", p2);
    return 0;
}