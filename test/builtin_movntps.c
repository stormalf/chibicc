#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

int main(void) {
    float4 v = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 dst = {0.0f, 0.0f, 0.0f, 0.0f};

    // Non-temporal store equivalent: store vector into memory
    float4 *p = &dst;

    // Normally you'd use __builtin_ia32_movntps(p, v)
    // Here we just assign via pointer for testing
    *p = v;

    printf("dst = {%.1f, %.1f, %.1f, %.1f}\n",
           dst[0], dst[1], dst[2], dst[3]);

    ASSERT(1, dst[0]);
    ASSERT(2, dst[1]);
    ASSERT(3, dst[2]);
    ASSERT(4, dst[3]);
    printf("OK\n");
    return 0;
}
