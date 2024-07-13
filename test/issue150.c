#include <stdio.h>
#include "test.h"
#define HOST_IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)


int main() {
printf("%d\n", __ORDER_BIG_ENDIAN__ );
ASSERT(4321, __ORDER_BIG_ENDIAN__);
return 0;

}