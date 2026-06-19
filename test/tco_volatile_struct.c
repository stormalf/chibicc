#include "test.h"
#include <stdint.h>

struct S {
    volatile int x;
    int y;
};

static int count = 0;
static uintptr_t first_sp = 0;

int test_volatile_struct(int n) {
    struct S s;
    s.x = n;
    uintptr_t sp = (uintptr_t)&s;
    
    if (first_sp == 0) first_sp = sp;
    
    if (n == 0) return 0;
    
    // If TCO is applied, sp will be the same as first_sp
    if (n == 1 && sp == first_sp) {
        printf("TCO was incorrectly applied to volatile struct!\n");
        return -1;
    }
    
    return test_volatile_struct(n - 1);
}

int main() {
    if (test_volatile_struct(10) == 0) {
        printf("TCO correctly disabled for volatile struct.\n");
        return 0;
    }
    return 1;
}
