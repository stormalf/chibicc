#include "test.h"
#include <stdint.h>

typedef short v8hi __attribute__((vector_size(16)));


int main() {
    v8hi a = { 1, 2, 3, 4, 5, 6, 7, 8 };
    v8hi b = {1,0,2,3,1,0,2,3}; 

    v8hi r = __builtin_ia32_psllw128((v8hi)a, (v8hi)b);

    short *res = (short *)&r;
    for (int i = 0; i < 8; i++) {
        printf("%d ", res[i]);
        ASSERT(0, r[i]);
    }
    printf("\n");

    printf("OK\n");

    return 0;
}

