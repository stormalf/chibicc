
#include "test.h"

typedef double v2df __attribute__((vector_size(16)));
typedef int v4si __attribute__((vector_size(16)));

v4si convert_double_to_int(v2df a) {
    return (v4si)__builtin_ia32_cvtpd2dq(a);
}

int main(void) {
    v2df a = { 1.5, -2.9 };
    v4si b = convert_double_to_int(a);

    // Only first 2 elements contain results; rest are undefined/zero
    printf("Converted: %d %d %d %d\n", b[0], b[1], b[2], b[3]);
    ASSERT(2, b[0]);
    ASSERT(-3, b[1]);
    ASSERT(0, b[2]);
    ASSERT(0, b[3]);
    printf("OK\n");
    return 0;
}
