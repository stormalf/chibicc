#include "test.h"

// Define a 2-element vector of int (32-bit)
typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = {1, 2};
    v2si count = {1, 2};

    // Perform packed shift left logical on 2x 32-bit integers
    v2si result = __builtin_ia32_pslld(a, count);

    printf("%d %d\n", result[0], result[1]);  // Expect: 2 8

    ASSERT(1, a[0]);
    ASSERT(2, a[1]);

    ASSERT(1, count[0]);
    ASSERT(2, count[1]);

    ASSERT(0, result[0]);
    ASSERT(0, result[1]);
    printf("OK\n");

    return 0;
}
