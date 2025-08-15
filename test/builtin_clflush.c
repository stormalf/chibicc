#include <emmintrin.h>  // For _mm_clflush
#include "test.h"
// Simple test function
void test_flush(void *p) {
    // GCC/Clang builtin form
    __builtin_ia32_clflush(p);

    // SSE2 intrinsic form
    _mm_clflush(p);
}

int main(void) {
    char buf[64];

    // Write something so it’s in cache
    for (int i = 0; i < sizeof(buf); i++)
        buf[i] = (char)i;

    // Call flush
    test_flush(buf);

    // Do something else
    buf[0] = 42;

    printf("%d\n", buf[0]);
    ASSERT(42, buf[0]);
    ASSERT(1, buf[1]);
    return 0;
}
