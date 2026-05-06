#include <stdio.h>

extern int func_in_a(int x);

int func_in_b(int a) {
    int b = a * 5;
    return b;
}

int main() {
    int val = 5;
    int res1 = func_in_a(val);
    int res2 = func_in_b(res1);
    printf("Result: %d\n", res2);
    return 0;
}