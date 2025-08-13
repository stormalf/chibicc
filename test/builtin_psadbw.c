#include "test.h"
typedef char  v8qi __attribute__((vector_size(8)));
typedef unsigned long   v1du __attribute__((vector_size(8)));


#include <stdio.h>

int main() {
    v8qi a = {10, 20, 30, 40, 50, 60, 70, 80};
    v8qi b = {15, 25, 35, 45, 55, 65, 75, 85};

    v1du r = (v1du)__builtin_ia32_psadbw(a, b);

    printf("%lu\n", r[0]); 
    ASSERT(40, r[0]);
    printf("OK\n");
    return 0;
}
