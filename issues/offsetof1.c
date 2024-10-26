#include <stdio.h>
#include <stddef.h>

typedef void (*FuncPtr)(void);

typedef struct {
    int a;
    FuncPtr func;
    double b;
} MyStruct;

void myFunction(void) {
    printf("Function called!\n");
}

int main() {
    printf("Offset of a: %zu\n", offsetof(MyStruct, a));    // Should be 0
    printf("Offset of func: %zu\n", offsetof(MyStruct, func)); // Should be sizeof(int)
    printf("Offset of b: %zu\n", offsetof(MyStruct, b));    // Should be sizeof(int) + sizeof(FuncPtr)

    // Example usage
    MyStruct s;
    s.func = myFunction;
    s.func(); // Should print "Function called!"

    return 0;
}
