#include "test.h"

typedef float float4 __attribute__((vector_size(16)));
typedef int int4 __attribute__((vector_size(16)));

int main(void) {
    float4 a = {1.2f, 2.8f, -3.5f, 4.7f};
    
    // Convert float4 to int4 (truncate)
    int4 b = __builtin_ia32_cvttps2dq(a);

    printf("a = {%.1f, %.1f, %.1f, %.1f}\n", a[0], a[1], a[2], a[3]);
    printf("b = {%d, %d, %d, %d}\n", b[0], b[1], b[2], b[3]);

    ASSERT(1, b[0]);
    ASSERT(2, b[1]);
    ASSERT(-3, b[2]);
    ASSERT(4, b[3]);
    printf("OK\n");
    return 0;
}
