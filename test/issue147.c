#include <limits.h>
#include <stdint.h>

#include "test.h"

#define __ORDER_LITTLE_ENDIAN__ 1234
//#define __BYTE_ORDER__ 1234

#define IS_LITTLE_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

int main()
{
    printf("is_little_endian=%d\n", IS_LITTLE_ENDIAN);
    ASSERT(1, IS_LITTLE_ENDIAN);
    return 0;
}