#include <stddef.h>
#include "test.h"

typedef struct S {
    __attribute__((aligned(32)))
    char data[32];
} S;

void print7(S a, S b, S c, S d, S e, S f, S g) {
    printf("%d %d %d %d %d %d %d\n", a.data[0], b.data[0], c.data[0],
                                     d.data[0], e.data[0], f.data[0], g.data[0]);
    ASSERT(1, a.data[0]);
    ASSERT(2, b.data[0]);
    ASSERT(3, c.data[0]);
    ASSERT(4, d.data[0]);
    ASSERT(5, e.data[0]);
    ASSERT(6, f.data[0]);
    ASSERT(7, g.data[0]);                          
}

int main() {
    S s1 = {.data = {1}};
    S s2 = {.data = {2}};
    S s3 = {.data = {3}};
    S s4 = {.data = {4}};
    S s5 = {.data = {5}};
    S s6 = {.data = {6}};
    S s7 = {.data = {7}};

    print7(s1, s2, s3, s4, s5, s6, s7);
    return 0;
}
