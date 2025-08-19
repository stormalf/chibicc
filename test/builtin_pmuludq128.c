#include "test.h"

typedef long long __v2di __attribute__((vector_size(16)));
typedef int       __v4si __attribute__((vector_size(16)));

int main(void) {
    __v4si a = { 2, 0, 3, 0 }; // Only even-indexed elements are used for pmuludq
    __v4si b =  { 5, 0, 7, 0 };

    __v2di r = (__v2di)__builtin_ia32_pmuludq128(a, b);

    long long *res = (long long*)&r;
    printf("%lld %lld\n", res[0], res[1]); // Expected: 10 21

    ASSERT(10, res[0]);
    ASSERT(21, res[1]);
    printf("OK\n");

    return 0;
}
