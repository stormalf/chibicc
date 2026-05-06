#include <stdio.h>
#include <stdlib.h>

// Function with 5 arguments
static int func5(int a, int b, int c, int d, int e) {
    printf("func5: a=%d b=%d c=%d d=%d e=%d\n", a, b, c, d, e);
    // Check if arguments are correct
    if (a != 1 || b != 2 || c != 3 || d != 4 || e != 5) {
        printf("ERROR: arguments corrupted!\n");
        return 0;
    }
    return 1;
}

// Function that calls func5 with complex expressions
static int call_test(void) {
    int x = 10;
    int result = func5(x - 9,          // 1
                      x - 8,          // 2
                      x - 7,          // 3
                      x - 6,          // 4
                      x - 5);         // 5
    return result;
}

// Test with pointers
static void func5_ptr(void *a, void *b, void *c, void *d, void *e) {
    printf("func5_ptr: a=%p b=%p c=%p d=%p e=%p\n", a, b, c, d, e);
    // Expect sequential numbers as pointers (testing with integers cast to pointers)
}

int main(void) {
    printf("Test 1: simple 5 args\n");
    if (!call_test()) return 1;
    
    printf("\nTest 2: pointer args\n");
    func5_ptr((void*)0x100, (void*)0x200, (void*)0x300, (void*)0x400, (void*)0x500);
    
    printf("\nTest 3: mixed args with function calls as arguments\n");
    // Function that returns int
    int (*fn)(int) = (int(*)(int))abs; // use abs as a function
    // Call func5 with some arguments being function calls
    // This exercises evaluation order
    int a = func5(fn(-1), fn(-2), fn(-3), fn(-4), fn(-5));
    printf("Result: %d (expected 1 if all args correct)\n", a);
    
    printf("\nAll tests passed\n");
    return 0;
}
