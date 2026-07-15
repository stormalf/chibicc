// Minimal reproducer: _mm256_extract_epi8 expands to vextractf128_si256 +
// vec_ext_v16qi. Under --backend-llvm the IR path for ND_VEXTRACTF128_SI256
// used gen_ir_vec_init which emitted:
//   insertelement <16 x i8> zeroinitializer, i8 %vec, i32 0
// where %vec had type <8 x i32> — a type mismatch caught by llc.
#include <immintrin.h>
#include "test.h"

int main() {
    __m256i v = _mm256_set_epi8(
        31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,
        15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

    // lane 0: bytes 0-15; element index 15 is byte value 15
    int8_t lo = _mm256_extract_epi8(v, 15);
    ASSERT(15, (int)lo);

    // lane 1: bytes 16-31; element index 29 maps to byte value 29
    int8_t hi = _mm256_extract_epi8(v, 29);
    ASSERT(29, (int)hi);

    printf("OK\n");
    return 0;
}
