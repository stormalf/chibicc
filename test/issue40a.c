
#include "test.h"
// fails silently (pointer to VLA)

int x = 10;
void fun(char (*a)[x]) { sizeof *a; printf("%zu\n", sizeof *a);  ASSERT(10, sizeof *a);}


int main(void) {
    char arr[10][20];
    fun(arr);
    return 0;
}