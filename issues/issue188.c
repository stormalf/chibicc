#include <stdio.h>
#include <stdint.h>

typedef struct internal_state {
    int x;
    int y;
    int w_size;
    int hash_size;
    char *head[10];
    char *prev[10];
} FAR deflate_state;



void slide_hash(s)    
deflate_state *s;
{
    unsigned n, m;
    char *p;
    uint64_t wsize = s->w_size;

    n = s->hash_size;
    p = &s->head[n];
    do {
        m = *--p;
        *p = (char *)(m >= wsize ? m - wsize : NULL);
    } while (--n);
    n = wsize;
#ifndef FASTEST
    p = &s->prev[n];
    do {
        m = *--p;
        *p = (char *)(m >= wsize ? m - wsize : NULL);
        /* If n is not on any hash chain, prev[n] is garbage but
         * its value will never be used.
         */
    } while (--n);
#endif
}

int main() {
    deflate_state s;
    s.x = 42;
    s.y = 17;

    printf("s.x = %d, s.y = %d\n", s.x, s.y);
    return 0;
}
