// test_vec_ext_v8hi.c
#include <immintrin.h>
#include "test.h"

static void check(int cond, const char *msg) {
    if (!cond) {
        printf("FAIL: %s\n", msg);
        __builtin_abort();
    }
}

int main(void) {
    short data[8] = {
        1000, -1, 2000, -3000,
        7, 0, -12345, 32767
    };

    __m128i v = _mm_loadu_si128((const __m128i*)data);

    int r0 = __builtin_ia32_vec_ext_v8hi(v, 0);
    int r1 = __builtin_ia32_vec_ext_v8hi(v, 1);
    int r3 = __builtin_ia32_vec_ext_v8hi(v, 3);
    int r6 = __builtin_ia32_vec_ext_v8hi(v, 6);
    int r7 = __builtin_ia32_vec_ext_v8hi(v, 7);

    // correctness of lane selection
    check(r0 == 1000, "ext[0]");
    check(r1 == -1, "ext[1]");
    check(r3 == -3000, "ext[3]");
    check(r6 == -12345, "ext[6]");
    check(r7 == 32767, "ext[7]");

    printf("OK\n");
    return 0;
}
