#include "test.h"
typedef long long v1di __attribute__((vector_size(8)));

#include <stdio.h>

int main() {
    v1di a = {0x123456789abcdef0LL};
    v1di count = {4};
    v1di result_var = __builtin_ia32_psrlq(a, count);
    v1di result_imm = __builtin_ia32_psrlqi(a, 4);

    printf("result_var: 0x%llx\n", result_var[0]);
    printf("result_imm: 0x%llx\n", result_imm[0]);

    LASSERT(0x123456789abcdefLL,  (long long)result_var[0]);
    LASSERT(0x123456789abcdefLL, (long long)result_imm[0]);

    int c = 4;
    result_imm = __builtin_ia32_psrlqi(a, c);
    LASSERT(0x123456789abcdefLL, (long long)result_imm[0]);
    printf("OK\n");
    return 0;
}
