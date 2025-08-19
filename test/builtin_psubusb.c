#include "test.h"

typedef unsigned char v8qu __attribute__((vector_size(8)));
typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qu a = {255, 200, 100, 50, 25, 10, 5, 0};
    v8qu b = {1, 50, 50, 25, 10, 5, 5, 0};

    v8qu result =(v8qu) __builtin_ia32_psubusb((v8qi)a, (v8qi)b);

    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned)result[i]);
    }
    printf("\n");
    ASSERT(255, a[0]);
    ASSERT(200, a[1]);
    ASSERT(100, a[2]);
    ASSERT(50, a[3]);
    ASSERT(25, a[4]);
    ASSERT(10, a[5]);
    ASSERT(5, a[6]);
    ASSERT(0, a[7]);

    ASSERT(1, b[0]);
    ASSERT(50, b[1]);
    ASSERT(50, b[2]);
    ASSERT(25, b[3]);
    ASSERT(10, b[4]);
    ASSERT(5, b[5]);
    ASSERT(5, b[6]);
    ASSERT(0, b[7]);

    ASSERT(254, (unsigned) result[0]);
    ASSERT(150, (unsigned) result[1]);
    ASSERT(50, (unsigned) result[2]);
    ASSERT(25, (unsigned) result[3]);
    ASSERT(15, (unsigned) result[4]);
    ASSERT(5, (unsigned) result[5]);
    ASSERT(0, (unsigned) result[6]);
    ASSERT(0, (unsigned) result[7]);
    

    printf("OK\n");

    return 0;
}
