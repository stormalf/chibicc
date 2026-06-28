#include <stdarg.h>
#include "test.h"

typedef struct {
    int a;
} SmallStruct;

void print_small(int n, ...) {
    va_list ap;
    va_start(ap, n);
    SmallStruct s = va_arg(ap, SmallStruct);
    printf("a = %d\n", s.a);
    ASSERT(1, s.a);
    va_end(ap);
}

int main() {
    SmallStruct s1 = {1};
    print_small(1, s1);
    return 0;
}
