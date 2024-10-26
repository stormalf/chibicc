#include <stdio.h>
#include <stddef.h>
#include <string.h>

// Define a structure with an array member
typedef struct {
    int id;
    char name[10];
    float values[5];
} MyStruct;

int main(void) {
    MyStruct s;
    
    // Using offsetof with array member
    size_t offset = offsetof(MyStruct, values[1]);

    printf("Offset of values[1] in MyStruct: %zu\n", offset);
    
    // Demonstrating memcpy with computed offset
    MyStruct src = {1, "Source", {1.0, 2.0, 3.0, 4.0, 5.0}};
    MyStruct dst = {0, "", {0.0, 0.0, 0.0, 0.0, 0.0}};
    
    memcpy(&dst.values[1], &src.values[1], offsetof(MyStruct, values[2]) - offsetof(MyStruct, values[1]) + sizeof(float));
    
    // Output results
    printf("Source values: ");
    for (int i = 0; i < 5; i++) printf("%.1f ", src.values[i]);
    printf("\nDestination values: ");
    for (int i = 0; i < 5; i++) printf("%.1f ", dst.values[i]);
    printf("\n");

    return 0;
}
