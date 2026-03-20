#include "test.h"
int main() {
    unsigned long a[2] = {10, 20};
    unsigned long res;
    // Test (a)[i] case which fails in mulq.c
    __asm__ ("movq %1, %0" : "=r"(res) : "a"((a)[1]));
    if (res != 20) {
        printf("FAILED: expected 20, got %ld\n", res);
        return 1;
    }
    printf("res => %ld\n", res);
    ASSERT(20, res);
    printf("OK\n");
    return 0;
}
