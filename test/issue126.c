#include <stddef.h>

#include <stdlib.h>
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
    size_t res;
    char *src = "hello";
    char *dst = calloc (20, sizeof(char));
    int siz = 6;
    res = strlcpy(dst, src, siz);
    printf("res=%ld dst=%s\n", res, dst);
    ASSERT(5, res);
    printf("OK\n");
    return 0;
}