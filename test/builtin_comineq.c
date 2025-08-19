#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 3.0f, 3.0f, 5.0f};
    v4sf c = {0.0f, 2.0f, 0.0f, 4.0f};

    // Compare a and b: expect 0 for equal (index 0 and 2), 1 for not equal (index 1 and 3)
    int res1 = __builtin_ia32_comineq(a, b);
    printf("comineq(a, b) = %d (expected non-zero because a != b)\n", res1);

    // Compare a and c: expect non-zero because many elements differ
    int res2 = __builtin_ia32_comineq(a, c);
    printf("comineq(a, c) = %d (expected non-zero)\n", res2);

    // Compare a and a: expect zero because they are equal
    int res3 = __builtin_ia32_comineq(a, a);
    printf("comineq(a, a) = %d (expected zero)\n", res3);
    ASSERT(0, res1);
    ASSERT(1, res2);
    ASSERT(0, res3);
    printf("OK\n");
    
    return 0;
}
