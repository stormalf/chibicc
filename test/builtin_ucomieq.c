
#include "test.h"
typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 5.0f, 3.0f, 0.0f};
    int res = __builtin_ia32_ucomieq(a, b);
    printf("ucomieq result: %d\n", res);  // Should print 1 if lowest floats are equal
    ASSERT(1, res);
    printf("OK\n");
    return 0;
}
