
#include <stddef.h>
#include "test.h"

typedef void (*Callback)(int);

typedef struct {
    int a;
    char b;
    Callback callback;
    double c;
} ComplexStruct;

void myCallback(int x) {
    printf("Callback called with %d\n", x);
}

int main() {
    printf("Offset of a: %zu\n", offsetof(ComplexStruct, a)); // Should be 0
    printf("Offset of b: %zu\n", offsetof(ComplexStruct, b)); // Should be sizeof(int)
    printf("Offset of callback: %zu\n", offsetof(ComplexStruct, callback)); // Should be sizeof(int) + sizeof(char)
    printf("Offset of c: %zu\n", offsetof(ComplexStruct, c)); // Should be sizeof(int) + sizeof(char) + sizeof(Callback)
    ASSERT(0, offsetof(ComplexStruct, a));
    ASSERT(4, offsetof(ComplexStruct, b)); // Assuming int is 4 bytes
    ASSERT(8, offsetof(ComplexStruct, callback)); // Assuming char is 1 byte
    ASSERT(16, offsetof(ComplexStruct, c)); // Assuming Callback is a pointer 
    

    // Example usage
    ComplexStruct cs;
    cs.callback = myCallback;
    cs.callback(42); // Should print "Callback called with 42"

    return 0;
}
