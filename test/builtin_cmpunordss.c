
#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {0.0f / 0.0f, 5.0f, 6.0f, 7.0f}; // b[0] = NaN

    // cmpunordss returns all bits set in lowest float if unordered (NaN involved)
    v4sf res = __builtin_ia32_cmpunordss(a, b);

    unsigned int *p = (unsigned int*)&res;

    printf("cmpunordss result (lowest float mask): 0x%x\n", p[0]);
    // Expected:
    // p[0] == 0xffffffff since b[0] is NaN
    // Other lanes are undefined (only lowest lane is relevant)

    ASSERT(-2147483648, res[0]);
    ASSERT(2, res[1]);
    ASSERT(3, res[2]);
    ASSERT(4, res[3]);
    printf("OK\n");
    return 0;
}
