#include "test.h"
// Define the vector type manually
typedef short v4si __attribute__((vector_size(8)));
typedef unsigned short v4qu __attribute__((vector_size(8)));



#include <stdio.h>

int main() {
    v4si a = {10, 20, 30, 40};
    v4si b = {5, 15, 25, 35};

    v4qu r = (v4qu)__builtin_ia32_pavgw(a, b);

    for (int i = 0; i < 4; i++)
        printf("%u ", r[i]);
    printf("\n");
    ASSERT(8, r[0]);
    ASSERT(18, r[1]);
    ASSERT(28, r[2]);
    ASSERT(38, r[3]);

    v4si c = {100, 200, 300, 400};
    v4si d = {50, 150, 250, 350};

    v4qu r2 = (v4qu)__builtin_ia32_pavgw(c, d);

    for (int i = 0; i < 4; i++)
        printf("%u ", r2[i]);
    printf("\n");
    ASSERT(75, r2[0]);
    ASSERT(175, r2[1]);
    ASSERT(275, r2[2]);
    ASSERT(375, r2[3]);

    printf("OK\n");

    return 0;
}
