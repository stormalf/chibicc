#include <stdio.h>
// fails silently (pointer to VLA)
int x = 10;
void fun(char (*a)[x]) { sizeof *a; }


int main(void) {
    printf("%d\n", x);
    return 0;
}