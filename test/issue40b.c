#include <stdio.h>
int fun( int n, int a[n]) {
    int res = 0;
    for (int i = 0; i < n; i++)
        res = res + a[i];
    return res;
};

int main(void)
{
    int c = 3;
    int a[c];

    for (int i = 0; i < c; i++)
        a[i] = i + 1;
    int b = fun(c, a);
    printf("%d %d \n", b, a[0]);
    return 0;
}