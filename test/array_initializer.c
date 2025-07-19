#include "test.h"

#define SIZE 10



int main()

{
    int myarr[SIZE]  = { 11, 34, 0, 0, 0, 0, 0, 0, 0, 0};
    int myarr2[SIZE]  = { 11, 34,};
    for (int i = 0; i < SIZE; ++i)
        printf("%d: %d\n", i, myarr[i]);
    for (int i = 0; i < SIZE; ++i)
        printf("%d: %d\n", i, myarr2[i]);

    ASSERT(0, myarr2[9]);
    return 0;
}