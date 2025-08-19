#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {30000, -30000, 100, -100};
    v4hi b = {2, 3, 4, 5};

    v4hi result = __builtin_ia32_pmullw(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    ASSERT(30000, a[0]);
    ASSERT(-30000, a[1]);
    ASSERT(100, a[2]);
    ASSERT(-100, a[3]);

    ASSERT(2, b[0]);
    ASSERT(3, b[1]);
    ASSERT(4, b[2]);
    ASSERT(5, b[3]);

    ASSERT(-5536, result[0]);
    ASSERT(-24464, result[1]);
    ASSERT(400, result[2]);
    ASSERT(-500, result[3]);
    printf("OK\n");

    return 0;
}
