#include <stdio.h>

void modify_array(int arr[4]) {
    arr[0] = 10; // Modify the first element
}

int main(void) {
    int arr[4] = {1, 2, 3, 4};
    modify_array(arr);
    printf("arr[0]: %d\n", arr[0]); 
    return 0;
}
