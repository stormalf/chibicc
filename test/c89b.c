#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static char *f (char * (*g) (char **, int), char **p, ...)
{
char *s;
va_list v;
va_start (v,p);
s = g (p, va_arg (v,int));
va_end (v);
return s;
}

static char *myfunc (char **p, int i)
{
return p[i];
}   

int main (void)
{

    char *hello = "hello";
    char *world = "world";
    char **phello = &hello;
    *(phello+1) = world;
    int i = 0;
   char *p = f (myfunc, phello,i);
    printf("%s\n", p);
    i = 1;
    p = f (myfunc, phello, i);
    printf("%s\n", p);
return 0;
}