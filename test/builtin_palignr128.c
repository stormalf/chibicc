/*
 * test_palignr128.c
 *
 * Self-contained test for __builtin_ia32_palignr128 (the builtin behind
 * SSSE3's PALIGNR / _mm_alignr_epi8), written without <tmmintrin.h> so it
 * can be used to check a compiler's (e.g. chibicc's) support for the
 * builtin directly.
 *
 * Builtin signature, matching GCC's gcc/config/i386/tmmintrin.h:
 *
 *     typedef long long __v2di __attribute__((vector_size(16)));
 *     __v2di __builtin_ia32_palignr128(__v2di a, __v2di b, int n_bits);
 *
 * tmmintrin.h's _mm_alignr_epi8(a, b, n) expands to
 *     __builtin_ia32_palignr128((__v2di)a, (__v2di)b, n * 8)
 * i.e. the 3rd argument to the *builtin* is a BIT count (byte count * 8),
 * not a byte count -- that multiplication is done in this test too.
 *
 * The 3rd argument must be a compile-time constant: PALIGNR's shift
 * count is encoded as a true x86 immediate in the instruction, so (like
 * real GCC) a correct implementation should reject a non-constant here.
 * This test therefore drives each case through a macro so every call
 * site uses a literal.
 *
 * Semantics (Intel PALIGNR): concatenate a:b (a = high 128 bits, b = low
 * 128 bits) into a 256-bit value, shift it right by n bytes, and keep the
 * low 128 bits.  So for byte index i in the 16-byte result:
 *     result[i] = (i + n < 16) ? b[i + n] : a[i + n - 16]
 *
 * Build with a reference compiler to confirm the test itself is correct:
 *     gcc   -mssse3 test_palignr128.c -o ref  && ./ref
 *     clang -mssse3 test_palignr128.c -o ref  && ./ref
 *
 * Then build with chibicc to see whether it matches:
 *     chibicc -msse3 test_palignr128.c -o cc_out && ./cc_out
 * (Try -msse3, or no flag at all, if -mssse3 isn't a recognized chibicc
 * option -- chibicc's SSSE3 support may be gated behind -msse3 instead of
 * a dedicated -mssse3 flag; check chibicc --help for the exact name.)
 */

#include "test.h"
#include <string.h>
#include <tmmintrin.h>

typedef long long __v2di __attribute__((vector_size(16)));

typedef union {
    __v2di v;
    unsigned char b[16];
} v128;

static int check_case(int n, v128 x, v128 y, v128 got) {
    unsigned char expected[16];
    for (int i = 0; i < 16; i++) {
        int idx = i + n; /* idx is in [0, 31] for n in [0, 16] */
        expected[i] = (idx < 16) ? y.b[idx] : x.b[idx - 16];
    }

    int ok = memcmp(got.b, expected, 16) == 0;

    printf("n=%2d  got:      ", n);
    for (int i = 0; i < 16; i++) printf("%02x ", got.b[i]);
    printf("\n      expected: ");
    for (int i = 0; i < 16; i++) printf("%02x ", expected[i]);
    printf("  %s\n", ok ? "PASS" : "FAIL");

    return ok;
}

#define RUN_CASE(N, failures)                                     \
    do {                                                          \
        v128 x, y, got;                                           \
        for (int i = 0; i < 16; i++) {                            \
            x.b[i] = (unsigned char)i;                            \
            y.b[i] = (unsigned char)(0x10 + i);                   \
        }                                                         \
        got.v = __builtin_ia32_palignr128(x.v, y.v, (N) * 8);     \
        if (!check_case((N), x, y, got)) (failures)++;            \
    } while (0)

int main(void) {
    int failures = 0;

    RUN_CASE(0, failures);
    RUN_CASE(1, failures);
    RUN_CASE(4, failures);
    RUN_CASE(5, failures);
    RUN_CASE(8, failures);
    RUN_CASE(11, failures);
    RUN_CASE(15, failures);
    RUN_CASE(16, failures);

    if (failures == 0) {
        printf("\nAll palignr128 cases PASSED\n");
        return 0;
    }

    printf("\n%d palignr128 case(s) FAILED\n", failures);
    return 1;
}