#include "test.h"

typedef short v4hi __attribute__((vector_size(8))); // 4 shorts, 64-bit vector

int main() {
    v4hi a = {100, 200, 300, 400};
    v4hi b = {10, 20, 30, 40};

    v4hi result = __builtin_ia32_punpcklwd(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }

    ASSERT(100, a[0]);
    ASSERT(200, a[1]);
    ASSERT(300, a[2]);
    ASSERT(400, a[3]);
    ASSERT(10, b[0]);
    ASSERT(20, b[1]);
    ASSERT(30, b[2]);
    ASSERT(40, b[3]);
    ASSERT(100, result[0]);
    ASSERT(10, result[1]);
    ASSERT(200, result[2]);
    ASSERT(20, result[3]);
    printf("OK\n");
    return 0;
}
