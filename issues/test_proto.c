#include <stdio.h>
int f(int n, int a[n]) {
    return sizeof(a);
}
int main() {
    int a[10];
    printf("%d\n", f(10, a));
    return 0;
}
