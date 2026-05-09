#include <emmintrin.h>
#include "test.h"
#include <stdint.h>

static void check(int cond, const char *msg) {
    if (!cond) {
        printf("FAIL: %s\n", msg);
        __builtin_abort();
    }
}

int main(void) {
    int64_t data[2] = {
        0x1122334455667788LL,
        -0x1122334455667788LL
    };

    __m128i v = _mm_loadu_si128((const __m128i*)data);

    long long r0 = __builtin_ia32_vec_ext_v2di(v, 0);
    long long r1 = __builtin_ia32_vec_ext_v2di(v, 1);

    // lane 0 (low 64 bits)
    check(r0 == 0x1122334455667788LL, "ext[0]");

    // lane 1 (high 64 bits)
    check(r1 == -0x1122334455667788LL, "ext[1]");

    printf("OK\n");
    return 0;
}
