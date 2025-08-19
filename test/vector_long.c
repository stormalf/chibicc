#include "test.h"

typedef long long4 __attribute__((vector_size(16)));

int main() {
    long4 lv = {1, 2};
    long4 res;

    res = lv + 1; // scalar promotion
    printf("%ld %ld\n", res[0], res[1]);
    ASSERT(2, res[0]);
    ASSERT(3, res[1]);
    return 0;
}
