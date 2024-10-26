#include <stdio.h>
#include <stddef.h>

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

    // Example usage
    ComplexStruct cs;
    cs.callback = myCallback;
    cs.callback(42); // Should print "Callback called with 42"

    return 0;
}
