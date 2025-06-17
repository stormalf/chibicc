#include <stdio.h>
#include <stddef.h>
#include "test.h"

// Define structures with function pointers
typedef struct {
    void (*func1)(void);
    void (*func2)(void);
} SimpleStruct;

typedef struct {
    int a;
    void (*func1)(void);
} MixedStruct;

void test_func(void) {
    printf("Test function called.\n");
}

int main(void) {
    // Test SimpleStruct
    printf("Size of SimpleStruct: %zu\n", sizeof(SimpleStruct));
    printf("Offset of func1 in SimpleStruct: %zu\n", offsetof(SimpleStruct, func1));
    printf("Offset of func2 in SimpleStruct: %zu\n", offsetof(SimpleStruct, func2));
    
    // Test MixedStruct
    printf("Size of MixedStruct: %zu\n", sizeof(MixedStruct));
    printf("Offset of func1 in MixedStruct: %zu\n", offsetof(MixedStruct, func1));
    // Verify function pointer assignment
    SimpleStruct ss = { test_func, test_func };
    MixedStruct ms = { 0, test_func };
    ASSERT(16, sizeof(ss));  
    
    printf("Function pointer func1 in SimpleStruct: %p\n", ss.func1);
    printf("Function pointer func2 in SimpleStruct: %p\n", ss.func2);
    printf("Function pointer func1 in MixedStruct: %p\n", ms.func1);
    
    return 0;
}

