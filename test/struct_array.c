#include <stdio.h>

// Define the struct with float, double, and int types
struct Data {
    float a;
    double b;
    int c;
};

// Define a typedef for an array of struct Data
typedef struct Data ARR[];
typedef float F;

    ARR arr = {
        {(F)1.1f, (F)2.2, (F)3},
        {(F)4.4f, (F)5.5, (F)6},
        {(F)7.7f, (F)8.8, (F)9}
    };
    
// Function to process an array of structs
void process_array(ARR arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Struct %d:\n", i);
        printf("  a = %.2f\n", arr[i].a);
        printf("  b = %.2lf\n", arr[i].b);
        printf("  c = %d\n", arr[i].c);
    }
}

int main() {
    // Define and initialize an array of structs using the typedef


    int size = sizeof(arr) / sizeof(arr[0]);

    // Pass the array to the function
    process_array(arr, size);

    return 0;
}
