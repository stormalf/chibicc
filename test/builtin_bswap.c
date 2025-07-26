
#include <stdint.h>
#include <inttypes.h>  // For PRIx macros
#include "test.h"
int main() {
    // Example values
    uint16_t value16 = 0x1234;
    uint32_t value32 = 0x12345678;
    uint64_t value64 = 0x123456789ABCDEF0;

    // Perform byte-swapping using built-in functions
    uint16_t swapped16 = __builtin_bswap16(value16);
    uint32_t swapped32 = __builtin_bswap32(value32);
    uint64_t swapped64 = __builtin_bswap64(value64);

    // Print original and swapped values
    printf("Original 16-bit value: 0x%04" PRIx16 "\n", value16);
    printf("Swapped 16-bit value: 0x%04" PRIx16 "\n", swapped16);
    ASSERT(0x3412, swapped16);

    printf("Original 32-bit value: 0x%08" PRIx32 "\n", value32);
    printf("Swapped 32-bit value: 0x%08" PRIx32 "\n", swapped32);
    Assert(0x78563412, swapped32);
    printf("Original 64-bit value: 0x%016" PRIx64 "\n", value64);
    printf("Swapped 64-bit value: 0x%016" PRIx64 "\n", swapped64);
    ASSERT(0xf0debc9a78563412, swapped64);
    return 0;
}
