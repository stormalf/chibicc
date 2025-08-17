#include "test.h"
int main() 
{

    __int128 a = 8 ;
    __int128 b = 7;
    __int128 c = a + b ;

    printf("c=%d\n", c);
    ASSERT(15, c);

    c = c + 17 + a + b + (7 * 8);
    printf("c=%d\n", c);
    ASSERT(103, c);

    c = a - b;
    ASSERT(1, c);
    c = a * b;
    ASSERT(56, c);
    c = c / 2;
    ASSERT(28, c);
    c = c % 2;
    ASSERT(0, c);
    c++;
    ASSERT(1, c);
    c--;
    ASSERT(0, c);
    printf("OK\n");
    return 0;

}