#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

int main() {
    v4sf a = {1.0f, 2.0f, 3.0f, 4.0f};
    v4sf b = {1.0f, 5.0f, 3.5f, 4.0f};
    v4sf c = {0.0f/0.0f, 5.0f, 3.5f, 4.0f};  // NaN in lowest element

    int res;

    // __builtin_ia32_ucomieq: unordered compare equal
    res = __builtin_ia32_ucomieq(a, b);
    printf("ucomieq (a,b): %d\n", res);
    ASSERT(1, res);  // a[0]==b[0] => true

    res = __builtin_ia32_ucomieq(a, c);
    printf("ucomieq (a,c): %d\n", res);
    ASSERT(0, res);  // unordered because c[0] is NaN


    // __builtin_ia32_ucomigt: unordered compare greater than
    res = __builtin_ia32_ucomigt(b, a);
    printf("ucomigt (b,a): %d\n", res);
    ASSERT(0, res);  // b[0] > a[0]

    res = __builtin_ia32_ucomigt(a, c);
    printf("ucomigt (a,c): %d\n", res);
    ASSERT(0, res);  // unordered => false

    // __builtin_ia32_ucomige: unordered compare greater or equal
    res = __builtin_ia32_ucomige(a, b);
    printf("ucomige (a,b): %d\n", res);
    ASSERT(1, res);  // 1.0 >= 1.0 => true 

    res = __builtin_ia32_ucomige(b, a);
    printf("ucomige (b,a): %d\n", res);
    ASSERT(1, res);  // b[0] >= a[0] => false

    res = __builtin_ia32_ucomige(a, c);
    printf("ucomige (a,c): %d\n", res);
    ASSERT(0, res);  // unordered => false

    // __builtin_ia32_ucomilt: unordered compare less than
    res = __builtin_ia32_ucomilt(a, b);
    printf("ucomilt (a,b): %d\n", res);
    ASSERT(0, res);  // 1.0 < 1.0 false, 2.0 < 5.0 true but only lowest float counts

    res = __builtin_ia32_ucomilt(a, c);
    printf("ucomilt (a,c): %d\n", res);
    ASSERT(0, res);  // unordered => false

    // __builtin_ia32_ucomile: unordered compare less or equal
    res = __builtin_ia32_ucomile(a, b);
    printf("ucomile (a,b): %d\n", res);
    ASSERT(1, res);  // 1.0 <= 1.0 => true

    res = __builtin_ia32_ucomile(a, c);
    printf("ucomile (a,c): %d\n", res);
    ASSERT(0, res);  // unordered => false
    printf("OK\n");
    return 0;
}
