#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a     = (v2si){-1024, 2048};
    v2si count = (v2si){2, 3}; // shift each lane by respective value

    v2si result = __builtin_ia32_psrad(a, count);

    printf("%d %d\n", result[0], result[1]); 

    ASSERT(-1024, a[0]);
    ASSERT(2048, a[1]);
    ASSERT(2, count[0]);
    ASSERT(3, count[1]);
    ASSERT(-1, result[0]);
    ASSERT(0, result[1]);
    printf("OK\n");
    return 0;
}
