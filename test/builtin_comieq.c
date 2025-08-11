

#include "test.h"

typedef float __v4sf __attribute__((vector_size(16)));


int main(void) {
    __v4sf a = {4.0f, 3.0f, 2.0f, 1.0f};
    __v4sf b = {4.0f, 3.0f, 2.0f, 1.0f};

    // Compare the lowest float elements of a and b for equality
    int result = __builtin_ia32_comieq((__v4sf)a, (__v4sf)b);

    printf("Lowest elements are equal? %s\n", result ? "Yes" : "No");
    ASSERT(1, result);
    printf("OK\n");
    return 0;
}
