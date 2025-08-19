
#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {2.0f, 2.0f, 3.0f, 4.0f};

    v4sf c = __builtin_ia32_cmpneqss(a, b);

    printf("cmpneqss result: %x %x %x %x\n",
        ((unsigned int*)&c)[0], ((unsigned int*)&c)[1],
        ((unsigned int*)&c)[2], ((unsigned int*)&c)[3]);
    // Expected: lowest uint is 0xFFFFFFFF (true), rest are 0
    ASSERT(-2147483648, c[0]);
    ASSERT(2, c[1]);
    ASSERT(3, c[2]);
    ASSERT(4, c[3]);
    printf("OK\n");
    return 0;
}
