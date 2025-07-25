#include <asm/swab.h>

#include "test.h"

int main(void)
{
    __u32 val = 12;
    val = __arch_swab32(val);
    printf("%d\n", val);
    ASSERT(201326592, val);
    return 0;
}