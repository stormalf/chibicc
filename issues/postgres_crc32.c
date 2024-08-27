#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <nmmintrin.h> // For SSE 4.2 CRC32 intrinsics

// Function prototype
uint32_t pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len);

int main() {
    // Example data
    const char data[] = "This is a test string for CRC32C!";
    size_t length = sizeof(data) - 1; // Exclude the null terminator

    // Initial CRC value
    uint32_t crc = 0;

    // Compute CRC
    crc = pg_comp_crc32c_sse42(crc, data, length);

    // Print the result
    printf("CRC32C: %08X\n", crc);

    return 0;
}

// Function implementation
uint32_t pg_comp_crc32c_sse42(uint32_t crc, const void *data, size_t len) {
    const unsigned char *p = data;
    const unsigned char *pend = p + len;

#ifdef __x86_64__
    while (p + 8 <= pend) {
        crc = (uint32_t) _mm_crc32_u64(crc, *((const uint64_t *) p));
        p += 8;
    }

    if (p + 4 <= pend) {
        crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
        p += 4;
    }
#else
    while (p + 4 <= pend) {
        crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
        p += 4;
    }
#endif

    while (p < pend) {
        crc = _mm_crc32_u8(crc, *p);
        p++;
    }

    return crc;
}
