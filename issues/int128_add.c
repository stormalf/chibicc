#include <stdint.h>
#include <stdio.h>

typedef __int128 int128_t;

void add_int128(int128_t *result, int128_t a, int128_t b) {
    *result = a + b;
}

int main() {
    int128_t x = 12345678901234567890123456789012345678;
    int128_t y = 98765432109876543210987654321098765432;
    int128_t result;

    add_int128(&result, x, y);

    printf("Result: %lld\n", (long long)result); // This will only print the lower 64 bits
    return 0;
}
