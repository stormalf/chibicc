#include <stdio.h>

void add_arrays(float *a, float *b, float *result, int n) {
    for (int i = 0; i < n; i++)
        result[i] = a[i] + b[i];
}

#include <stdio.h>

int *get_array() {
    static int arr[4] = {1, 2, 3, 4}; // Static allows it to live after function ends
    return arr; // Returning array decays to pointer to first element
}

int main() {
    float a[4] = {1.0, 2.0, 3.0, 4.0};
    float b[4] = {10.0, 20.0, 30.0, 40.0};
    float result[4];

    add_arrays(a, b, result, 4);

    for (int i = 0; i < 4; i++)
        printf("result[%d] = %.1f\n", i, result[i]);

    int *a1 = get_array();
    printf("a[0]=%d\n", a1[0]);
    printf("a[1]=%d\n", a1[1]);
    printf("a[2]=%d\n", a1[2]);
    printf("a[3]=%d\n", a1[3]);        
    return 0;
}
