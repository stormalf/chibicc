#include "test.h"

int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = &arr[5];
    int *q = p - 3;
    ASSERT(2, *q);
    return 0;
}
