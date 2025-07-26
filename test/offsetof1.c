
#include <stddef.h>
#include "test.h"

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
    printf("sizeof(int)= %zu\n", sizeof(int)); // Should be 4
    ASSERT(4, sizeof(int));
    ASSERT(8, sizeof(long));
    ASSERT(4, SIZEOF_INT);
    ASSERT(8, SIZEOF_LONG);
    ASSERT(0, offsetof(MyStruct, a));
    ASSERT(8, offsetof(MyStruct, func));
    ASSERT(16, offsetof(MyStruct, b));
    // Example usage
    MyStruct s;
    s.func = myFunction;
    s.func(); // Should print "Function called!"

    return 0;
}
