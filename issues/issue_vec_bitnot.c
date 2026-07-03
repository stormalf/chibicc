#include "test.h"
#include <stdint.h>

typedef int int4 __attribute__((vector_size(16)));

int main(void) {
    int4 a = {0x0f0f0f0f, 0x00ff00ff, 0x12345678, 0xffffffff};
    int4 not_a = ~a;
    ASSERT(0xf0f0f0f0, not_a[0]);
    ASSERT(0xff00ff00, not_a[1]);
    ASSERT(0xedcba987, not_a[2]);
    ASSERT(0x00000000, not_a[3]);
    printf("OK\n");
    return 0;
}
