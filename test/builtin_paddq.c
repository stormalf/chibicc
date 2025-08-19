#include "test.h"

typedef long long v1di __attribute__((vector_size(8)));

int main() {
    v1di a = {1000000000LL};
    v1di b = {1234567890LL};

    v1di result = __builtin_ia32_paddq(a, b);

    printf("%lld\n", result[0]);
    LASSERT(1000000000LL, a[0]);
    LASSERT(1234567890LL, b[0]);
    LASSERT(2234567890LL, (long long) result[0]);
    printf("OK\n");

    return 0;
}
