#include <stdio.h>
int fun( int a[n]) {
    int res = 0;
    for (int i = 0; i < n; i++)
        res = res + a[i];
    return res;
};

int main(void)
{
    int a[3] = {1, 2, 3};
    int b = fun( a);
    printf("%d %p \n", b, a);
    return 0;
}