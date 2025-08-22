#include "test.h"
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
typedef __int128 __uint128_t;
bool umul_overflow_u8(uint8_t a, uint8_t b, uint8_t *res) {
    uint16_t r = (uint16_t)a * (uint16_t)b;
    *res = (uint8_t)r;
    return r > UINT8_MAX;
}

bool umul_overflow_u16(uint16_t a, uint16_t b, uint16_t *res) {
    uint32_t r = (uint32_t)a * (uint32_t)b;
    *res = (uint16_t)r;
    return r > UINT16_MAX;
}

bool umul_overflow_u32(uint32_t a, uint32_t b, uint32_t *res) {
    uint64_t r = (uint64_t)a * (uint64_t)b;
    *res = (uint32_t)r;
    return r > UINT32_MAX;
}

bool umul_overflow_u64(uint64_t a, uint64_t b, uint64_t *res) {
    __uint128_t r = (__uint128_t)a * (__uint128_t)b;
    *res = (uint64_t)r;
    return r > UINT64_MAX;
}


void test_umul_overflow() {
    uint8_t r8;
    uint16_t r16;
    uint32_t r32;
    uint64_t r64;
    __int128 r128;

    // 8-bit
    printf("8-bit: %d %d -> %d, overflow=%d\n", 10, 20, r8, umul_overflow_u8(10, 20, &r8));
    printf("8-bit overflow: %d %d -> %d, overflow=%d\n", 200, 2, r8, umul_overflow_u8(200, 2, &r8));
    ASSERT(0, umul_overflow_u8(10, 20, &r8));
    ASSERT(1, umul_overflow_u8(200, 2, &r8));
    // 16-bit
    printf("16-bit: %d %d -> %d, overflow=%d\n", 300, 100, r16, umul_overflow_u16(300, 100, &r16));
    printf("16-bit overflow: %d %d -> %d, overflow=%d\n", 40000, 2, r16, umul_overflow_u16(40000, 2, &r16));
    ASSERT(0, umul_overflow_u16(300, 100, &r16));
    ASSERT(1, umul_overflow_u16(40000, 2, &r16));
    // 32-bit
    printf("32-bit: %u %u -> %u, overflow=%d\n", 100000, 1000, r32, umul_overflow_u32(100000, 1000, &r32));
    printf("32-bit overflow: %u %u -> %u, overflow=%d\n", 3000000000U, 2U, r32, umul_overflow_u32(3000000000U, 2U, &r32));
    ASSERT(0, umul_overflow_u32(100000, 1000, &r32));
    ASSERT(1, umul_overflow_u32(3000000000U, 2U, &r32));
    // 64-bit
    printf("64-bit: %llu %llu -> %llu, overflow=%d\n", 10000000000ULL, 1000ULL, r64, umul_overflow_u64(10000000000ULL, 1000ULL, &r64));
    printf("64-bit overflow: %llu %llu -> %llu, overflow=%d\n", 0xFFFFFFFFFFFFFFF0ULL, 2ULL, r64, umul_overflow_u64(0xFFFFFFFFFFFFFFF0ULL, 2ULL, &r64));
    ASSERT(0, umul_overflow_u64(10000000000ULL, 1000ULL, &r64));
    ASSERT(1, umul_overflow_u64(0xFFFFFFFFFFFFFFF0ULL, 2ULL, &r64));

    
}

int main() {
    test_umul_overflow();
    return 0;
}
