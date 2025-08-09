#include "test.h"

typedef unsigned short v4hu __attribute__((vector_size(8)));
typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hu a = {65535, 40000, 30000, 10000};
    v4hu b = {1, 1000, 40000, 5000};

    v4hu result = (v4hu)__builtin_ia32_psubusw((v4hi)a, (v4hi)b);

    for (int i = 0; i < 4; i++) {
        printf("%u ", (unsigned)result[i]);
    }
    printf("\n");
    ASSERT(65535, a[0]);
    ASSERT(40000, a[1]);
    ASSERT(30000, a[2]);
    ASSERT(10000, a[3]);
    ASSERT(1, b[0]);
    ASSERT(1000, b[1]);
    ASSERT(40000, b[2]);
    ASSERT(5000, b[3]);

    ASSERT(65534, (unsigned) result[0]);
    ASSERT(39000, (unsigned) result[1]);
    ASSERT(0, (unsigned) result[2]);
    ASSERT(5000, (unsigned) result[3]);
    printf("OK\n");
    return 0;
}
