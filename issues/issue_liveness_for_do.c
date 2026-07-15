#include "test.h"

// Test that variables used inside for/do-while loop bodies
// are not incorrectly reported as unused.

static int sum_for(int n) {
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += i;
    }
    return sum;
}

static int sum_do(int n) {
    int sum = 0;
    int i = 0;
    do {
        sum += i;
        i++;
    } while (i < n);
    return sum;
}

static int next_val(int *p) {
    int *q = p;
    int result = *q;
    return result;
}

int main() {
    ASSERT(10, sum_for(5));
    ASSERT(10, sum_do(5));
    int arr[] = {42};
    ASSERT(42, next_val(arr));
    return 0;
}
