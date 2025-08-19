#include "test.h"

typedef short __v4hi __attribute__((vector_size(8)));

int main(void) {
    __v4hi a = {-1900, -2000, 3000, -4000};
    __v4hi b = {-1000, -2500, -3000, 4000};

    // Compute pairwise signed minimum using the builtin intrinsic
    __v4hi r = __builtin_ia32_pminsw(a, b);

    // Print results
    for (int i = 0; i < 4; i++) {
        printf("r[%d] = %d\n", i, r[i]);
    }
    ASSERT(-1900, r[0]);
    ASSERT(-2500, r[1]);
    ASSERT(-3000, r[2]);
    ASSERT(-4000, r[3]);
    
    printf("OK\n");

    return 0;
}
