#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {30000, -30000, 100, -100};
    v4hi b = {1000, 1000, 500, 500};

    v4hi result = __builtin_ia32_psubsw(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", (int)result[i]);
    }
    ASSERT(30000, a[0]);
    ASSERT(-30000, a[1]);
    ASSERT(100, a[2]);
    ASSERT(-100, a[3]);
    ASSERT(1000, b[0]);
    ASSERT(1000, b[1]);
    ASSERT(500, b[2]);
    ASSERT(500, b[3]);

    ASSERT(29000, (int) result[0]);
    ASSERT(-31000, (int) result[1]);
    ASSERT(-400, (int) result[2]);
    ASSERT(-600, (int) result[3]);
    printf("\n");
    printf("OK\n");

    return 0;
}
