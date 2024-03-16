#include <stdio.h>

#define SIZE 10



int main(void)

{
    int myarr[SIZE]  = { 11, 34, 0, 0, 0, 0, 0, 0, 0, 0};
    int myarr2[SIZE]  = { 11, 34,};
    for (int i = 0; i < SIZE; ++i)
        printf("%d: %d\n", i, myarr[i]);
    for (int i = 0; i < SIZE; ++i)
        printf("%d: %d\n", i, myarr2[i]);

    return 0;
}