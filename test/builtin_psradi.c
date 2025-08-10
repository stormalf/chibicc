#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = (v2si){-1024, 2048};

    // Shift both lanes right by an immediate value of 2
    v2si result = __builtin_ia32_psradi(a, 2);

    printf("%d %d\n", result[0], result[1]); // Expect -256 and 512

    ASSERT(-1024, a[0]);
    ASSERT(2048, a[1]);

    ASSERT(-256, result[0]);
    ASSERT(512, result[1]);
    int count = 2;
    result = __builtin_ia32_psradi(a, count);
    ASSERT(-256, result[0]);
    ASSERT(512, result[1]);
    printf("OK\n");

    return 0;
}
