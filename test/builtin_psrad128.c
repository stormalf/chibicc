#include "test.h"
#include <stdint.h>

typedef int v4si __attribute__((vector_size(16)));

int main() {
    v4si a = { 100000, -100000, 2147483647, -2147483648 };
    v4si b = { 2, 2, 2, 2 };

    // Shift right arithmetic by 2 bits
    v4si r = __builtin_ia32_psrad128((v4si)a,(v4si)b);

    int *res = (int *)&r;
    for (int i = 0; i < 4; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    ASSERT(0, r[0]);
    ASSERT(-1, r[1]);
    ASSERT(0, r[2]);
    ASSERT(-1, r[3]);
  
    printf("OK\n");
    return 0;
}
