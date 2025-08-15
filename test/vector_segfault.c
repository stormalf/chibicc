#include "test.h"

typedef double __m128d __attribute__ ((__vector_size__ (16)));

void test_case(__m128d a, __m128d b, const char *desc) {
    int result = __builtin_ia32_comisdeq(a, b);
    printf("%-30s -> %d\n", desc, result);
    ASSERT(result,  __builtin_ia32_comisdeq(a, b));

}

int main(void) {
    __m128d v1 = {2.0, 1.0};    // [2.0, 1.0]
    __m128d v2 = {3.0, 1.0};    // [3.0, 1.0]
    __m128d v3 = {4.0, 2.0};    // [4.0, 2.0]
    __m128d vnan = {9.0, 0.0/0.0}; // NaN in low element

    // Only low element (index 0) is compared!

    test_case(v1, v2, "Equal low elements (1.0 == 1.0)");
    test_case(v1, v3, "Unequal low elements (1.0 != 2.0)");
    test_case(vnan, v1, "NaN vs normal");
    test_case(v1, vnan, "Normal vs NaN");
    test_case(vnan, vnan, "NaN vs NaN");

    return 0;
}
