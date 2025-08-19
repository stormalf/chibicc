#include "test.h"

typedef unsigned char v8qu __attribute__((vector_size(8)));
typedef char v8qi __attribute__((vector_size(8)));


int main(void) {
    v8qu a = {1, 200, 3, 250, 5, 10, 7, 100};
    v8qu b = {100, 100, 200, 200, 0, 20, 10, 90};
    v8qi c = __builtin_ia32_pmaxub((v8qi)a, (v8qi)b);
    v8qu d = (v8qu)c;
    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned)c[i]);
    }
    printf("\n");

    // Expected output: 100 200 200 250 5 20 10 100
    ASSERT(100, d[0]);
    ASSERT(200, d[1]);
    ASSERT(200, d[2]);
    ASSERT(250, d[3]);
    ASSERT(5, d[4]);
    ASSERT(20, d[5]);
    ASSERT(10, d[6]);
    ASSERT(100, d[7]);
    printf("OK\n");
    return 0;
}
