// Regression test for __builtin_bswap16 leaving garbage in upper bits of %eax.
// When __builtin_bswap16 returns uint16_t, the upper 16 bits of %eax may
// contain stale data from a previous 32-bit computation. This causes incorrect
// results when the bswap16 result is used in pointer arithmetic or wider
// arithmetic (as SQLite does for btree page cell offsets).
//
// The fix: gen_builtin_bswap16 must zero-extend before rotating.
#include "test.h"
#include <stdint.h>

// Simulate SQLite's get2byteAligned macro
static uint16_t get2byte_bswap16(const unsigned char *x) {
    return __builtin_bswap16(*(uint16_t*)(x));
}

// Force some 32-bit operations that would leave non-zero upper bits
// in %eax before calling __builtin_bswap16
uint16_t test_bswap16_with_prior_32bit(unsigned char *cellIdx) {
    volatile int noise = 0xDEADBEEF;  // this may leave upper bits dirty
    (void)noise;
    
    // Read cell offset - if bswap16 doesn't zero-extend, the upper 16 bits
    // of %eax from the previous computation could corrupt the result
    return get2byte_bswap16(cellIdx);
}

int main() {
    // Big-endian cell offsets in a simulated btree page
    unsigned char cellIdx[4] = {0x00, 0x05, 0x00, 0x10};
    
    uint16_t off0 = test_bswap16_with_prior_32bit(cellIdx + 0);
    uint16_t off1 = test_bswap16_with_prior_32bit(cellIdx + 2);
    
    ASSERT(5, off0);
    ASSERT(16, off1);
    
    // Also test directly without indirection
    ASSERT(5, get2byte_bswap16(cellIdx + 0));
    ASSERT(16, get2byte_bswap16(cellIdx + 2));
    ASSERT(256, get2byte_bswap16((unsigned char[]){0x01, 0x00}));
    
    // Test edge cases
    ASSERT(0x0000, get2byte_bswap16((unsigned char[]){0x00, 0x00}));
    ASSERT(0xFFFF, get2byte_bswap16((unsigned char[]){0xFF, 0xFF}));
    ASSERT(0x00FF, get2byte_bswap16((unsigned char[]){0x00, 0xFF}));
    ASSERT(0xFF00, get2byte_bswap16((unsigned char[]){0xFF, 0x00}));
    ASSERT(0x8000, get2byte_bswap16((unsigned char[]){0x80, 0x00}));
    ASSERT(0x1234, get2byte_bswap16((unsigned char[]){0x12, 0x34}));
    
    // Simulate SQLite's btree page offset calculation with pointer arithmetic
    unsigned char aData[512];
    for (int i = 0; i < 512; i++) aData[i] = (unsigned char)i;
    
    uint16_t maskPage = 0x1FF;
    
    unsigned char *pCell = aData + (maskPage & get2byte_bswap16(cellIdx));
    ASSERT(5, (int)(long)(pCell - aData));
    
    printf("OK\n");
    return 0;
}
