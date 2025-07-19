
#include "test.h"
long double x = 0;

int main(void) {
    printf("%Lf %ld\n", x, sizeof(x));
    ASSERT(16, sizeof(x));
    return 0;
}