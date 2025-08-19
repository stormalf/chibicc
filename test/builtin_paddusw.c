
#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main(void) {
    v4hi a = {30000, 100, 65000, 500};
    v4hi b = {10000, 200, 1000, 200};

    v4hi result = (v4hi)__builtin_ia32_paddusw(a, b);

    for (int i = 0; i < 4; i++)
        printf("%u ", (unsigned short)result[i]);

    ASSERT(30000, a[0]);
    ASSERT(100, a[1]);
    ASSERT(65000, (unsigned short)a[2]);
    ASSERT(500, a[3]);
    ASSERT(10000, b[0]);
    ASSERT(200, b[1]);
    ASSERT(1000, b[2]);
    ASSERT(200, b[3]);   
    ASSERT(40000, (unsigned short) result[0]);
    ASSERT(300, result[1]);
    ASSERT(65535, (unsigned short) result[2]);
    ASSERT(700, result[3]);
    
    printf("\n");
    printf("OK\n");
}
