#include "test.h"

typedef float __v4sf __attribute__((vector_size(16)));

int main() {
    __v4sf a = {7.0f, 5.0f, 3.0f, 1.0f};
    __v4sf b = {7.0f, 4.0f, 2.0f, 0.0f};

    // Compare: returns int (from low float)
    int res = __builtin_ia32_comile(a, b);

    printf("Result: %d\n", res); 
    ASSERT(1, res);
    printf("OK\n");
    return 0;
}
