#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = {100000, 200000};
    v2si b = {10, 20};

    v2si result = __builtin_ia32_paddd(a, b);

    for (int i = 0; i < 2; i++) {
        printf("%d ", a[i]);
        ASSERT((i+1) * 100000, a[i]);
    }
    
    for (int i = 0; i < 2; i++) {
        printf("%d ", b[i]);
        ASSERT((i+1) * 10, b[i]);
    }
        
    for (int i = 0; i < 2; i++) {
        printf("%d ", result[i]);
    }

    ASSERT(100010, result[0]);
    ASSERT(200020, result[1]);
    printf("OK\n");

    return 0;
}
