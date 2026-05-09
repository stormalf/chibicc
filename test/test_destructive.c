#include <stdio.h>
typedef int v4si __attribute__((vector_size(16)));
typedef v4si myint;
v4si global_v;
int main() {
    printf("sizeof(global_v) = %zu\n", sizeof(global_v));
    if (sizeof(global_v) != 16) {
        printf("BUG: v4si size is %zu, expected 16\n", sizeof(global_v));
        return 1;
    }
    printf("OK\n");
    return 0;
}
