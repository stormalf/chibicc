#include "test.h"
#include <stdarg.h>

typedef float float4 __attribute__((vector_size(16)));

void print_vectors(int count, ...) {
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        float4 v = va_arg(ap, float4);
        printf("vec %d = %f %f %f %f\n", i, v[0], v[1], v[2], v[3]);
    }
    va_end(ap);
}

int main() {
    float4 a = {1,2,3,4};
    float4 b = {5,6,7,8};
    print_vectors(2, a, b);
}
