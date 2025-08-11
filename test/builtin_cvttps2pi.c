#include "test.h"

// Define __m64 as a 64-bit integer type to hold MMX registers
typedef long long __m64;

typedef float __v4sf __attribute__((vector_size(16)));
typedef int __v2si __attribute__((vector_size(8)));

int main(void) {
    // Create a vector of 4 floats (like __v4sf)
    __v4sf vec = { 123.9f, 456.7f, -789.5f, 0.0f };

    // Convert the lowest two floats to packed 16-bit ints in MMX register
    __v2si result = __builtin_ia32_cvttps2pi(vec);

    // Since we cannot directly print __m64, cast it to unsigned 64-bit for printing
    unsigned long long packed = (unsigned long long)result;

    printf("Input floats: %.1f, %.1f\n", vec[0], vec[1]);
    printf("Packed 16-bit ints: 0x%016llx\n", packed);

    // Extract low and high 16-bit parts to check correctness
    short low  = (short)(packed & 0xFFFF);
    short high = (short)((packed >> 16) & 0xFFFF);

    printf("Extracted 16-bit ints: %d, %d\n", low, high);


int *res_ints = (int *)&result;

printf("Extracted 32-bit ints: %d, %d\n", res_ints[0], res_ints[1]);
ASSERT(123, res_ints[0]);
ASSERT(456, res_ints[1]);
printf("OK\n");
if (res_ints[0] == 123 && res_ints[1] == 456) {
    puts("PASS");
    return 0;
} else {
    puts("FAIL");
    return 1;
}

}
