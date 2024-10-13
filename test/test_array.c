#include <stdio.h>
#include "test.h"
int main(int argc, char** argv) {
    char _Alignas(1024) arr1[11];
    char _Alignas(1024) arr2[argc];
    printf("%d\n", _Alignof arr1); // gcc/clang: 1024 chibicc: 1024
    ASSERT(1024, _Alignof arr1);
    printf("%d\n", _Alignof arr2); // gcc/clang: 1024 chibicc: 8
    ASSERT(8, _Alignof arr2);
    printf("%d\n", _Alignof *&arr1); // gcc:1024 clang:1
    ASSERT(1, _Alignof *&arr1);
    return 0;
}