#include "test.h"
inline int twice(int x)
{
    return x + x;
}

int main() {
int i = 1;
printf("%d\n", twice(i++));

return 0;
}