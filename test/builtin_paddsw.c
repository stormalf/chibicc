#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {30000, -30000, 20000, -20000};
    v4hi b = {10000, 10000, -10000, -10000};

    v4hi result = (v4hi) __builtin_ia32_paddsw(a, b);

    for (int i = 0; i < 4; i++)
        printf("%d ", result[i]);

    ASSERT(30000, a[0]);
    ASSERT(-30000, a[1]);
    ASSERT(20000, a[2]);
    ASSERT(-20000, a[3]);
    ASSERT(10000, b[0]);
    ASSERT(10000, b[1]);
    ASSERT(-10000, b[2]);
    ASSERT(-10000, b[3]);

    ASSERT(32767, result[0]);
    ASSERT(-20000, result[1]);
    ASSERT(10000, result[2]);
    ASSERT(-30000, result[3]);
    printf("OK\n");
}
