#include "test.h"

int test_return_cast(void) {
    return (int){42};
}

float test_return_cast_float(void) {
    return (float){3.14f};
}

int main(void) {
    int i = test_return_cast();
    float f = test_return_cast_float();

    printf("i = %d\n", i);
    printf("f = %f\n", f);

    ASSERT(42, i);
    ASSERT(3, (int)f); // simple cast to int for test
    return 0;
}
