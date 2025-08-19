#include "test.h"

typedef int v2si __attribute__((vector_size(8)));
typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v2si a = {30000, -30000};
    v2si b = {1000, -1000};

    ASSERT(30000, a[0]);
    ASSERT(-30000, a[1]);
    ASSERT(1000, b[0]);
    ASSERT(-1000, b[1]);
    v4hi result = (v4hi) __builtin_ia32_packssdw(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", (int)result[i]);
    }
    ASSERT(30000, result[0]);
    ASSERT(-30000, result[1]);
    ASSERT(1000, result[2]);
    ASSERT(-1000, result[3]);
    printf("OK\n");
    return 0;
}
