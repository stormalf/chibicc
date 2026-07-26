#include "test.h"
//#include <smmintrin.h>

typedef short v8hi __attribute__((vector_size(16)));

static void dump(const char *name, v8hi v) {
    printf("%s = {", name);
    for (int i = 0; i < 8; i++) {
        printf("%d", v[i]);
        if (i != 7) printf(", ");
    }
    printf("}\n");
}

int main(void) {
    // X: all positive
    v8hi X = {  1,  2,  3,  4,  5,  6,  7,  8 };

    // Y: all negative
    v8hi Y = { -1, -2, -3, -4, -5, -6, -7, -8 };

    // Mask: select lower 4 words from Y (bits 0-3 set) and upper 4 from X (bits 4-7 clear)
    // For PBLENDW, the mask is a 8-bit immediate where each bit selects between X (0) and Y (1)
    v8hi MASK = { 0, 0, 0, 0, -1, -1, -1, -1 }; // This won't work directly, we need to use the intrinsic properly

    // Actually, let's test it the way it's used in smmintrin.h
    // _mm_blend_epi16 takes an 8-bit immediate mask
    v8hi R = (v8hi)__builtin_ia32_pblendw128(
        (v8hi)X,   // X
        (v8hi)Y,   // Y
        0xF0       // Mask: 11110000b - select high 4 bits from Y, low 4 from X
    );

    dump("X", X);
    dump("Y", Y);
    dump("R", R);

    // Expected:
    // R = { X[0..3], Y[4..7] } = { 1, 2, 3, 4, -5, -6, -7, -8 }
    int ok = 1;
    short expected[] = { 1, 2, 3, 4, -5, -6, -7, -8 };
    for (int i = 0; i < 8; i++) {
        if (R[i] != expected[i]) {
            ok = 0;
            break;
        }
    }

    printf(ok ? "pblendw128 OK\n" : "pblendw128 FAIL\n");
    return ok ? 0 : 1;
}