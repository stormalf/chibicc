#include "test.h"

typedef int int4 __attribute__((vector_size(16)));

int4 sub_int_vectors(int4 a, int4 b) {
    return a - b;
}

int main() {
    int4 a = {100, 200, 300, 400};
    int4 b = {10, 20, 30, 40};
    int4 c;
    c = sub_int_vectors(a, b);

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %d\n", i, c[i]);
    }
    ASSERT(90, c[0]);
    ASSERT(180, c[1]);
    ASSERT(270, c[2]);
    ASSERT(360, c[3]);
}
