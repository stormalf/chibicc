
#include "test.h"

typedef double __v2df __attribute__((vector_size(16)));

int main(void) {
    __v2df a = { 3.14, 2.71 };
    __v2df b = { 3.14, 5.0 };

    // Compare the low double elements of a and b (unordered compare equal)
    int res = __builtin_ia32_ucomisdeq(a, b);

    printf("Result = %d\n", res); // Expected 1 because 3.14 == 3.14

    ASSERT(1, res);
    return 0;
}
