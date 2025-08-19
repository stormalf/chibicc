#include "test.h"
#include <stdint.h>

typedef short v8hi __attribute__((vector_size(16)));
typedef unsigned short v8hu __attribute__((vector_size(16)));

v8hi paddusw128_test(v8hi a, v8hi b) {
    return __builtin_ia32_paddusw128(a, b);
}

int main() {
    v8hi a = {65535, 1000, 50000, 65530, 40000, 200, 65535, 60000};
    v8hi b = {1, 60000, 20000, 10, 30000, 700, 100, 10000};

    v8hu result = (v8hu)paddusw128_test(a, b);

    for (int i = 0; i < 8; i++)
        printf("%u ", result[i]);
    printf("\n");

    ASSERT(65535, result[0]);
    ASSERT(61000, result[1]);
    ASSERT(65535, result[2]);
    ASSERT(65535, result[3]);
    ASSERT(65535, result[4]);
    ASSERT(900, result[5]);
    ASSERT(65535, result[6]);
    ASSERT(65535, result[7]);
    printf("OK\n");
    return 0;
}
