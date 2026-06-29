#include "test.h"

typedef double double2 __attribute__((vector_size(16)));

int main() {
    double2 a = {1.0, 2.0};
    double2 b = {3.0, 4.0};
    double2 c = __builtin_ia32_addsd(a, b);
    ASSERT(4, (int)c[0]);
    ASSERT(2, (int)c[1]);
    return 0;
}
