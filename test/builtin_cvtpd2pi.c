#include "test.h"

typedef double v2df __attribute__((vector_size(16)));
typedef int v2si __attribute__((vector_size(8))); // 2×32-bit ints in 64-bit MMX register

v2si convert_double_to_mmx(v2df a) {
    return (v2si)__builtin_ia32_cvtpd2pi(a);
}

int main(void) {
    v2df a = { 3.8, -4.2 };
    v2si b = convert_double_to_mmx(a);

    printf("Converted: %d %d\n", b[0], b[1]);

    ASSERT(4, b[0]);
    ASSERT(-4, b[1]);
    printf("OK\n");
    return 0;
}
