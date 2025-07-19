#include <stddef.h>
#include "test.h"
int main() {

int arr[10];
int *ptr = arr;
printf("sizeof(arr) = %zu\n", sizeof(arr));  // Should print 40 (for int[10])
ASSERT(40, sizeof(arr));
printf("sizeof(ptr) = %zu\n", sizeof(ptr));  // Should print 8 (assuming 64-bit system)
ASSERT(8, sizeof(ptr));
return 0;
}