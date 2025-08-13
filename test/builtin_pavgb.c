#include "test.h"
// Define the vector type manually
typedef char v8qi __attribute__((vector_size(8)));
typedef unsigned char v8qu __attribute__((vector_size(8)));



#include <stdio.h>

int main() {
    v8qi a = {10, 20, 30, 40, 50, 60, 70, 80};
    v8qi b = {5, 15, 25, 35, 45, 55, 65, 75};

    v8qu r = (v8qu)__builtin_ia32_pavgb(a, b);

    for (int i = 0; i < 8; i++)
        printf("%u ", r[i]);
    printf("\n");
    ASSERT(8, r[0]);
    ASSERT(18, r[1]);
    ASSERT(28, r[2]);
    ASSERT(38, r[3]);
    ASSERT(48, r[4]);
    ASSERT(58, r[5]);
    ASSERT(68, r[6]);
    ASSERT(78, r[7]);
    printf("OK\n");

    return 0;
}
