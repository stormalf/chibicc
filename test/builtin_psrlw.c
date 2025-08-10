#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a     = (v4hi){4, 8, -4, -8};   // v4hi with signed values
    v4hi count = (v4hi){1, 1, 1, 1};     // shift right by 1 bit each

    // Logical shift right on packed 16-bit integers (ignores sign)
    v4hi result = __builtin_ia32_psrlw(a, count);

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    
    ASSERT(4, a[0]);
    ASSERT(8, a[1]);
    ASSERT(-4, a[2]);
    ASSERT(-8, a[3]);

    ASSERT(1, count[0]);
    ASSERT(1, count[1]);
    ASSERT(1, count[2]);
    ASSERT(1, count[3]);
    ASSERT(0, result[0]);
    ASSERT(0, result[1]);
    ASSERT(0, result[2]);
    ASSERT(0, result[3]);


    printf("OK\n");
    return 0;
}
