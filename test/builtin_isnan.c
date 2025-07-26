
#include <math.h>

int main() {
    // Test with NaN (Not a Number)
    double nan_value = 0.0 / 0.0;
    float nan_value_f = 0.0f / 0.0f;

    if (__builtin_isnan(nan_value)) {
        printf("nan_value is NaN (double)\n");
    } else {
        printf("nan_value is NOT NaN (double)\n");
    }

    if (__builtin_isnan(nan_value_f)) {
        printf("nan_value_f is NaN (float)\n");
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
    }

    if (__builtin_isnan(regular_value_f)) {
        printf("regular_value_f is NaN (float)\n");
    } else {
        printf("regular_value_f is NOT NaN (float)\n");
    }

    return 0;
}
