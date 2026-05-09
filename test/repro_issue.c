#include <stdio.h>

typedef int v4si __attribute__((vector_size(16))), myint;
int x __attribute__((aligned(64))), y;

int main() {
    setbuf(stdout, NULL);
    v4si v = {1, 2, 3, 4};
    myint i = 5;
    printf("i = %d\n", i);
    printf("sizeof(v) = %ld\n", sizeof(v));
    printf("sizeof(i) = %ld\n", sizeof(i));
    if (sizeof(i) == sizeof(v)) {
        printf("BUG: myint is treated as vector!\n");
    }
    
    printf("alignof(x) = %ld\n", __alignof__(x));
    printf("alignof(y) = %ld\n", __alignof__(y));
    if (__alignof__(y) == 64) {
        printf("BUG: y is treated as aligned(64)!\n");
    }

    return 0;
}
