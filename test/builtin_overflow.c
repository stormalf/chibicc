#include "test.h"
#include <stdint.h>

int main(void) {
    // ---------- 32-bit unsigned addition ----------
    unsigned int a32 = 0xFFFFFFFF;
    unsigned int b32 = 1;
    unsigned int res32;
    int overflow32 = __builtin_uadd_overflow(a32, b32, &res32);
    printf("uadd_overflow(0x%X + 0x%X) = %u, overflow = %d\n", a32, b32, res32, overflow32);

    // 32-bit constant addition
    unsigned int res32_const;
    int overflow32_const = __builtin_uadd_overflow(100u, 200u, &res32_const);
    printf("uadd_overflow(100 + 200) = %u, overflow = %d\n", res32_const, overflow32_const);

    // ---------- 64-bit unsigned long addition ----------
    unsigned long a64 = 0xFFFFFFFFFFFFFFFFUL;
    unsigned long b64 = 1;
    unsigned long res64;
    int overflow64 = __builtin_uaddl_overflow(a64, b64, &res64);
    printf("uaddl_overflow(0x%lX + 0x%lX) = %lu, overflow = %d\n", a64, b64, res64, overflow64);

    // 64-bit constant addition
    unsigned long res64_const;
    int overflow64_const = __builtin_uaddl_overflow(100UL, 200UL, &res64_const);
    printf("uaddl_overflow(100 + 200) = %lu, overflow = %d\n", res64_const, overflow64_const);

    // 64-bit constant addition
    unsigned long long  resl64_const;
    int overflowl64_const = __builtin_uaddll_overflow(100ULL, 200ULL, &resl64_const);
    printf("uaddll_overflow(100 + 200) = %lu, overflow = %d\n", resl64_const, overflowl64_const);


    return 0;
}
