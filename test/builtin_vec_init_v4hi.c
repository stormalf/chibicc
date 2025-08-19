#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi v = __builtin_ia32_vec_init_v4hi(1, 2, 3, 4);

    for (int i = 0; i < 4; i++) {
        printf("%d ", v[i]);
        ASSERT(i+1, v[i]);
    }
    printf("\n");
    printf("OK\n");
    return 0;
}
