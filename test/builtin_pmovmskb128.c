#include "test.h"

typedef char char16 __attribute__((vector_size(16)));
typedef unsigned char uchar16 __attribute__((vector_size(16)));

int main() {
    // Only the MSB of each byte matters
    char16 a = {
        0x80, 0x7F, 0xFF, 0x01,
        0x00, 0xC0, 0x20, 0xF0,
        0x10, 0x08, 0x04, 0x02,
        0x81, 0x82, 0x83, 0x84
    };

    int mask = __builtin_ia32_pmovmskb128(a);

    printf("%04X\n", mask);
    ASSERT(0xF0A5, mask);


    printf("OK\n");
    return 0;
}
