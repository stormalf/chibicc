#include <stdio.h>
#include <stddef.h>
#include "test.h"

typedef struct {
    int array[2][3][4];
} MultiDimArray;

int main() {
    MultiDimArray m;

    // Size of the entire structure
    printf("Size of MultiDimArray struct: %zu bytes\n", sizeof(MultiDimArray));

    // Individual element offsets for validation
    printf("Offset of 'array[0][0][0]': %zu\n", offsetof(MultiDimArray, array[0][0][0]));
    ASSERT(0, offsetof(MultiDimArray, array[0][0][0]));
    printf("Offset of 'array[0][1][2]': %zu\n", offsetof(MultiDimArray, array[0][1][2]));
    ASSERT(24, offsetof(MultiDimArray, array[0][1][2]));
    printf("Offset of 'array[1][2][3]': %zu\n", offsetof(MultiDimArray, array[1][2][3]));
    ASSERT(92, offsetof(MultiDimArray, array[1][2][3]));

    // Total expected size calculation
    size_t expected_size = 2 * 3 * 4 * sizeof(int);
    printf("Expected size of array (2 * 3 * 4 * sizeof(int)): %zu bytes\n", expected_size);
    ASSERT(96, expected_size);

    return 0;
}
