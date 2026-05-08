// test_int128_bitand_constfold.c
//
// Verifies:
//   - __int128 constant folding
//   - bitwise AND folding
//   - correct truncation semantics
//   - no accidental 64-bit truncation
//
// Expected:
//   exit code 0

typedef unsigned __int128 u128;

int main(void) {

    // high 64-bit pattern
    u128 a =
        ((u128)0x123456789ABCDEF0ULL << 64) |
         (u128)0xFEDCBA9876543210ULL;

    u128 b =
        ((u128)0xFFFFFFFF00000000ULL << 64) |
         (u128)0x00000000FFFFFFFFULL;

    // should be fully constant-folded
    u128 c = a & b;

    unsigned long hi = (unsigned long)(c >> 64);
    unsigned long lo = (unsigned long)c;

    if (hi != 0x1234567800000000ULL)
        return 1;

    if (lo != 0x0000000076543210ULL)
        return 2;

    return 0;
}

