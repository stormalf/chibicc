#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
size_t
strlcpy(dst, src, siz)
char *dst;
const char *src;
size_t siz;
{
    register char *d = dst;
    register const char *s = src;
    register size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0 && --n != 0)
    {
        do
        {
            if ((*d++ = *s++) == 0)
                break;
        } while (--n != 0);
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0)
    {
        if (siz != 0)
            *d = '\0'; /* NUL-terminate dst */
        while (*s++)
            ;
    }

    return (s - src - 1); /* count does not include NUL */
}

int main(void)
{
    char *s = "Hello, World!";
    char *d = malloc(strlen(s));
    printf("s: %s\n", s);
    strlcpy(d, s, strlen(s) + 1);
    printf("d: %s\n", d);
    ASSERT(13, strlen(d));
    free(d);
    return 0;
}