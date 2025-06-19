#include <stdio.h>
#include <stddef.h>

typedef void (*Func1)(void);
typedef void (*Func2)(int);
typedef int (*Func3)(int);

typedef struct {
    Func1 func1;
    Func2 func2;
    Func3 func3;
} FunctionStruct;

void myFunc1(void) {
    printf("Func1 called!\n");
}

void myFunc2(int x) {
    printf("Func2 called with %d!\n", x);
}

int myFunc3(int x) {
    return x * 2;
}

int main() {
    printf("Offset of func1: %zu\n", offsetof(FunctionStruct, func1)); // Should be 0
    printf("Offset of func2: %zu\n", offsetof(FunctionStruct, func2)); // Should be sizeof(Func1)
    printf("Offset of func3: %zu\n", offsetof(FunctionStruct, func3)); // Should be sizeof(Func1) + sizeof(Func2)

    // Example usage
    FunctionStruct fs;
    fs.func1 = myFunc1;
    fs.func2 = myFunc2;
    fs.func3 = myFunc3;

    fs.func1();           // Should print "Func1 called!"
    fs.func2(10);         // Should print "Func2 called with 10!"
    printf("Func3 result: %d\n", fs.func3(5)); // Should print "Func3 result: 10"

    return 0;
}
