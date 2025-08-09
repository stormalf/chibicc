#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));
typedef unsigned char v8qi __attribute__((vector_size(8)));

int main() {
    v4hi a = {300, -30, 1000, -1000};
    v4hi b = {100, 200, 40000, -40000};
    ASSERT(300, a[0]);
    ASSERT(-30, a[1]);
    ASSERT(1000, a[2]);
    ASSERT(-1000, a[3]);
    ASSERT(100, b[0]);
    ASSERT(-25536, b[2]); //40000 is changed to -25536  warning: overflow in conversion from ‘int’ to ‘short int’ changes value from ‘-40000’ to ‘25536’ [-Woverflow]
    ASSERT(25536, b[3]); // warning: overflow in conversion from ‘int’ to ‘short int’ changes value from ‘-40000’ to ‘25536’ [-Woverflow]

    v8qi result = (v8qi)__builtin_ia32_packuswb(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned int)result[i]);
    }
    ASSERT(255, result[0]);
    ASSERT(0, result[1]);
    ASSERT(255, result[2]);
    ASSERT(0, result[3]);
    ASSERT(100, result[4]);
    ASSERT(200, result[5]);
    ASSERT(0, result[6]);
    ASSERT(255, result[7]);
    printf("OK\n");
    return 0;
}
