#include <stdio.h>
#include <string.h>

// Struct > 16 bytes
typedef struct {
    long a;
    long b;
    long c;
    long d;
} BigStruct;  // 32 bytes

// Function with 10 parameters (exceeds register count)
int test_func(
    int p1, int p2, int p3, int p4, int p5, int p6,
    int p7, int p8, int p9, int p10) {
    
    printf("p1=%d p2=%d p3=%d p4=%d p5=%d\n", p1, p2, p3, p4, p5);
    printf("p6=%d p7=%d p8=%d p9=%d p10=%d\n", p6, p7, p8, p9, p10);
    
    // Verify values - generic check that all are non-zero and in ascending order
    if (p1 >= p2 || p2 >= p3 || p3 >= p4 || p4 >= p5 ||
        p5 >= p6 || p6 >= p7 || p7 >= p8 || p8 >= p9 || p9 >= p10) {
        printf("ERROR: arguments in wrong order!\n");
        return -1;
    }
    return 0;
}

// Function with struct > 16 bytes
int test_big_struct(BigStruct s, int x) {
    printf("s.a=%ld s.b=%ld s.c=%ld s.d=%ld x=%d\n",
           s.a, s.b, s.c, s.d, x);
    
    if (s.a != 100 || s.b != 200 || s.c != 300 || s.d != 400 || x != 500) {
        printf("ERROR: struct or arg corrupted!\n");
        return -1;
    }
    return 0;
}

int main(void) {
    printf("Test 1: 10 integer parameters\n");
    int r1 = test_func(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    printf("Result: %d (expected 0)\n\n", r1);
    
    printf("Test 2: struct > 16 bytes as parameter\n");
    BigStruct bs = {100, 200, 300, 400};
    int r2 = test_big_struct(bs, 500);
    printf("Result: %d (expected 0)\n\n", r2);
    
    printf("Test 3: combination\n");
    // Call with struct and many args
    int r3 = test_func(10, 20, 30, 40, 50, 60, 70, 80, 90, 100);
    printf("Result: %d (expected 0)\n\n", r3);
    
    if (r1 == 0 && r2 == 0 && r3 == 0) {
        printf("All tests PASSED\n");
    } else {
        printf("Some tests FAILED\n");
    }
    
    return 0;
}
