#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <nmmintrin.h>
#include "test.h"


int main() {
    // Example data
    const char data[] = "This is a test string for CRC32C!";
    size_t tmplength = sizeof(data);
    size_t length = sizeof(data) - 1; // Exclude the null terminator
    printf("length = %ld templength=%ld\n", length, tmplength);
    ASSERT(33, length);
    ASSERT(34, tmplength);

    // Initial CRC value
    uint32_t crc = 0;

    // Compute CRC
    crc = pg_comp_crc32c_sse42(crc, data, length);

    // Print the result
    printf("CRC32C: %08X\n", crc);

    return 0;
}
