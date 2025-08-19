#include "test.h"

typedef long long int int4 __attribute__((vector_size(16)));

int main() {
    int4 a = {0xF0F0F0F0, 0xAAAAAAAA};
    int4 b = {0x0F0F0F0F, 0x55555555};

    int4 c = __builtin_ia32_pandn128(a, b); // ~a & b

    for(int i = 0; i < 2; i++) {
        printf("%llX ", c[i]);
    }
    printf("\n");
    
    ASSERT(0xF0F0F0F, c[0]);
    ASSERT(0x55555555, c[1]);
    printf("OK\n");
    return 0;
}
