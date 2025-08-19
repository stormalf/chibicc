#include "test.h"
typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {1000, 2000, 3000, 4000};
    v4hi b = {10, 20, 30, 40};

    v4hi result = __builtin_ia32_paddw(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", a[i]);
        ASSERT((i+1) * 1000, a[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        printf("%d ", b[i]);
        ASSERT((i+1) * 10, b[i]);
    }
    

    for (int i = 0; i < 4; i++) {
        printf("%d ", result[i]);
    }
    ASSERT(1010, result[0]);
    ASSERT(2020, result[1]);
    ASSERT(3030, result[2]);
    ASSERT(4040, result[3]);

    printf("OK\n");

    return 0;
}
