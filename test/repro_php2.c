#include "test.h"
struct op { long lval; };
#define Z_LVAL_P(z) ((z)->lval)
int main() {
    struct op o = {123456789};
    struct op *op1 = &o;
    long res;
    // Test nested parentheses
    __asm__ ("movq %1, %0" : "=r"(res) : "r"(((op1)->lval)));
    if (res != 123456789) {
        printf("FAILED: expected 123456789, got %ld\n", res);
        return 1;
    }
    printf("res => %ld\n", res);
    ASSERT(123456789, res);
    printf("OK\n");
    return 0;
}

