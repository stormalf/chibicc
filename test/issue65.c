#include "test.h"
struct S { unsigned long long int b:32; } s;

void f() {
    s.b = 10;
    ASSERT(10, s.b);
}
int main() {
    return 0;
}