#include "test.h"

typedef double float2 __attribute__((vector_size(16)));
typedef float  float4 __attribute__((vector_size(16)));

int main(void) {
    float2 src = {3.14159, 2.71828};    // 2 doubles
    float4 dst = {0.0f, 1.0f, 2.0f, 3.0f}; // 4 floats

    // Convert lowest double of src to float in lowest element of dst
    dst = __builtin_ia32_cvtsd2ss(dst, src);

    printf("dst = {%.6f, %.6f, %.6f, %.6f}\n",
           dst[0], dst[1], dst[2], dst[3]);

    // Expected output:
    // dst[0] = 3.141590 (converted from src[0])
    // dst[1..3] unchanged: 1.0, 2.0, 3.0
    ASSERT(3, dst[0]);
    ASSERT(1, dst[1]);
    ASSERT(2, dst[2]);
    ASSERT(3, dst[3]);
    printf("OK\n");

    return 0;
}
