#include "test.h"
#include <stdlib.h>



typedef struct {
    int a;
    int b;
} T;

void test_struct_assignment_return_value(void) {
    T a = {0, 0};
    T b = {1, 2};

    // (a = b) should return 'a' (conceptually, address of a in implementation).
    // If it returns 'b' (address of b), then modifying the result modifies 'b'.
    // This validates the fix in codegen.c store() function.
    a = b;
    a.a = 5;

    ASSERT(5, a.a);
    ASSERT(2, a.b);
    ASSERT(1, b.a); // b should remain 1
    ASSERT(2, b.b);
}

void test_unnamed_bitfield(void) {
    struct {
        int a;
        int : 0;
        int b;
    } x;
    
    // If the unnamed bitfield bug exists (parse.c), 'b' is not in the member list.
    // This would fail to compile or runtime crash if offsets are wrong.
    x.a = 10;
    x.b = 20;
    
    ASSERT(10, x.a);
    ASSERT(20, x.b);
}

int main() {
    test_struct_assignment_return_value();
    test_unnamed_bitfield();
    printf("OK\n");
    return 0;
}
