#include "test.h"
#include <stdint.h>

typedef int v4si __attribute__((vector_size(16)));

int main() {
    v4si a = { 100000, -100000, 2147483647, -2147483648 };

    // Shift right arithmetic by 2 bits
    v4si r = __builtin_ia32_psradi128((v4si)a, 2);

    int *res = (int *)&r;
    for (int i = 0; i < 4; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    ASSERT(25000, r[0]);
    ASSERT(-25000, r[1]);
    ASSERT(536870911, r[2]);
    ASSERT(-536870912, r[3]);

    int count = 2;
    r = __builtin_ia32_psradi128((v4si)a, 2);

    res = (int *)&r;
    for (int i = 0; i < 4; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    ASSERT(25000, r[0]);
    ASSERT(-25000, r[1]);
    ASSERT(536870911, r[2]);
    ASSERT(-536870912, r[3]);    
    printf("OK\n");
    return 0;
}
