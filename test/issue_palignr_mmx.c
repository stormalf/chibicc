#include <tmmintrin.h>
#include <stdint.h>
#include "test.h"

int main(void) {
    __m64 a = _mm_set_pi8(
        0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01);

    __m64 b = _mm_set_pi8(
        0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11);

    __m64 r = _mm_alignr_pi8(b, a, 4);

    unsigned char *p = (unsigned char *)&r;

    for (int i = 0; i < 8; i++)
        printf("%02x ", p[i]);
    puts("");

    
    return 0;
}
