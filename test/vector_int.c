#include "test.h"

typedef int int4 __attribute__((vector_size(16)));

int4 add_int4(int4 a, int4 b) {
    return a + b;
}

int main() {
    int4 a = {1, 2, 3, 4};
    int4 b = {10, 20, 30, 40};
    int4 c;
    c = add_int4(a, b);
    int4 d = add_int4(a, c);
    printf("c = %d %d %d %d\n", c[0], c[1], c[2], c[3]);
    ASSERT(11, c[0]);
    ASSERT(22, c[1]);
    ASSERT(33, c[2]);
    ASSERT(44, c[3]);
    printf("d = %d %d %d %d\n", d[0], d[1], d[2], d[3]);
    ASSERT(12, d[0]);
    ASSERT(24, d[1]);
    ASSERT(36, d[2]);
    ASSERT(48, d[3]);
    return 0;
}
