#include "test.h"
#include <stdint.h>

typedef long long v2di __attribute__((vector_size(16)));

int main() {
    v2di value = {0x1122334455667788LL, 0x99AABBCCDDEEFF00LL};
    v2di mem;

    __builtin_ia32_movntdq(&mem, value);

    printf("mem[0] = 0x%llX\n", mem[0]);
    printf("mem[1] = 0x%llX\n", mem[1]);
    LASSERT(0x1122334455667788, mem[0]);
    LASSERT(0x99AABBCCDDEEFF00, mem[1]);

    printf("OK\n");

    return 0;
}
