#include "test.h"
typedef double v2df __attribute__((vector_size(16)));

int main() {
    v2df a = {1.0, 99.0};
    v2df b = {1.0, 77.0};

    v2df r = __builtin_ia32_cmpltsd(a, b);
    printf("Result: [%llx, %llx]\n",
           ((unsigned long long*)&r)[0],
           ((unsigned long long*)&r)[1]);

    ASSERT(0, r[0]);
    ASSERT(99, r[1]);
    printf("OK\n");
    return 0;
}
