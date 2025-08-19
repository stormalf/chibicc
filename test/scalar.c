#include "test.h"

typedef int myint;
typedef int myarr[5];

float add_many(float a, float b, float c, float d, float e) {
    return a + b + c + d + e;
}

myarr myarrfunc() {
    myarr m = {1, 2, 3, 4, 5};
    return m;
}
myint add_many_int(myint a, myint b, myint c, myint d, myint e) {
    return a + b + c + d + e;
}
int main() {
    float x = add_many(1, 2, 3, 4, 5);
    printf("x = %f\n", x);
    ASSERT(15, x);
    myint a = 10;
    myint b = 5;
    myint c = 3;
    myint d = 7;
    myint e = 8;
    myint z = a + b + c + d + e;
    printf("z=%d\n", z);
    ASSERT(33, z);
    z = add_many_int(a, b, c, d, e);
    printf("z=%d\n", z);
    ASSERT(33, z);
    myarr t = myarrfunc();

    return 0;
}
