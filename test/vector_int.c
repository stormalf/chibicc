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
    printf("c = %d %d %d %d\n", c[0], c[1], c[2], c[3]);
    ASSERT(11, c[0]);
    ASSERT(22, c[1]);
    ASSERT(33, c[2]);
    ASSERT(44, c[3]);
}
