#include "test.h"
#include <stdint.h>

typedef long long v8hi __attribute__((vector_size(16)));


int main() {
    v8hi a = { 1, 2 };
    v8hi b = {1,0}; 

    v8hi r = __builtin_ia32_psllq128((v8hi)a, (v8hi)b);

    long long *res = (long long *)&r;
    for (int i = 0; i < 2; i++) {
        printf("%lld ", res[i]);
    }
    printf("\n");

    ASSERT(2, r[0]);
    ASSERT(4, r[1]);
    printf("OK\n");

    return 0;
}

