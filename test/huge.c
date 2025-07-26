
#include <math.h>
#include "test.h"

int main() {
    // Test with HUGE_VALF
    float huge_valf = HUGE_VALF;
    if (huge_valf == __builtin_huge_valf()) {
        printf("HUGE_VALF test passed: %f\n", huge_valf);
    } else {
        printf("HUGE_VALF test failed.\n");
    }

    // Test with HUGE_VALL
    long double huge_vall = HUGE_VALL;
    if (huge_vall == __builtin_huge_vall()) {
        printf("HUGE_VALL test passed: %Lf\n", huge_vall);
    } else {
        printf("HUGE_VALL test failed.\n");
    }

    // Test with HUGE_VAL
    double huge_val = HUGE_VAL;
    if (huge_val == __builtin_huge_val()) {
        printf("HUGE_VAL test passed: %f\n", huge_val);
    } else {
        printf("HUGE_VAL test failed.\n");
    }
    return 0;
}
