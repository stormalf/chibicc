// test_vec_ext_v16qi.c
#include <immintrin.h>
#include "test.h"

static void check(int cond, const char *msg) {
    if (!cond) {
        printf("FAIL: %s\n", msg);
        __builtin_abort();
    }
}

int main(void) {
    unsigned char data[16] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15
    };

    __m128i v = _mm_loadu_si128((const __m128i*)data);

    int r0  = __builtin_ia32_vec_ext_v16qi(v, 0);
    int r7  = __builtin_ia32_vec_ext_v16qi(v, 7);
    int r15 = __builtin_ia32_vec_ext_v16qi(v, 15);

    // validate extraction correctness
    check(r0  == 0,  "ext[0]");
    check(r7  == 7,  "ext[7]");
    check(r15 == 15, "ext[15]");

    printf("OK\n");
    return 0;
}
