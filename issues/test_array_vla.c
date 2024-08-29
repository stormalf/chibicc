#include <stdio.h>
int main() {

int arr[10];
int *ptr = arr;
printf("sizeof(arr) = %zu\n", sizeof(arr));  // Should print 40 (for int[10])
printf("sizeof(ptr) = %zu\n", sizeof(ptr));  // Should print 8 (assuming 64-bit system)
return 0;
}