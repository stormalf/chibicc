#include "test.h"
#include <stdint.h>

typedef long long v2di __attribute__((vector_size(16)));


int main() {
    v2di a = { 0xFFFFFFFFFFFFFFFF, 0x8000000000000000 };

    // Shift right logical by 1
    v2di r = __builtin_ia32_psrlqi128((v2di)a, 1);

    unsigned long long *res = (unsigned long long *)&r;
    for (int i = 0; i < 2; i++) {
        printf("%016llx ", res[i]);
    }
    printf("\n");

    LASSERT(0x7fffffffffffffff, r[0]);
    LASSERT(0x4000000000000000, r[1]);
    int count = 1;
    // Shift right logical by 1
    r = __builtin_ia32_psrlqi128((v2di)a, count);

    res = (unsigned long long *)&r;
    for (int i = 0; i < 2; i++) {
        printf("%016llx ", res[i]);
    }
    printf("\n");

    printf("OK\n");
    return 0;
}
