
#include <math.h>
#include "test.h"

int main() {
    // Test with NaN (Not a Number)
    double nan_value = 0.0 / 0.0;
    float nan_value_f = 0.0f / 0.0f;
    int a = 0, b = 0, c = 0, d = 0; 

    if (__builtin_isnan(nan_value)) {
        printf("nan_value is NaN (double)\n");
        a = 1;
    } else {
        printf("nan_value is NOT NaN (double)\n");
    }

    if (__builtin_isnan(nan_value_f)) {
        printf("nan_value_f is NaN (float)\n");
        b = 1;
    } else {
        printf("nan_value_f is NOT NaN (float)\n");
    }

    // Test with a regular number
    double regular_value = 123.456;
    float regular_value_f = 123.456f;

    if (__builtin_isnan(regular_value)) {
        printf("regular_value is NaN (double)\n");
    } else {
        printf("regular_value is NOT NaN (double)\n");
        c = 1;
    }

    if (__builtin_isnan(regular_value_f)) {
        printf("regular_value_f is NaN (float)\n");
    } else {
        printf("regular_value_f is NOT NaN (float)\n");
        d = 1;
    }

    ASSERT(1, a);
    ASSERT(1, b);
    ASSERT(1, c);
    ASSERT(1, d);
    return 0;
}
