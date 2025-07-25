
#include "test.h"
int fun(int n, int a[n]) {
    int res = 0;
    for (int i = 0; i < n; i++)
        res = res + a[i];
    return res;
};

int main(void)
{
    int a[3] = {1, 2, 3};
    int b = fun(3, a);
    printf("%d %p \n", b, a);
    ASSERT(6, b);
    return 0;
}