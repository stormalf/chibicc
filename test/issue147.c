#include <limits.h>
#include <stdint.h>
#include "test.h"

#define __ORDER_LITTLE_ENDIAN__ 1234
//#define __BYTE_ORDER__ 1234

#define IS_LITTLE_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

int main()
{

    return 0;
}