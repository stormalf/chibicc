
#include "test.h"

typedef long long v1di __attribute__((vector_size(8)));

int main(void) {
    v1di a = {10000000000LL};
    v1di b = {5000000000LL};

    v1di result = (v1di)__builtin_ia32_psubq(a, b);

    printf("%lld\n", (long long)result[0]);
    LASSERT(5000000000, (long long)result[0]);
    printf("OK\n");
}
