#include <stdio.h>
//#include "test.h"
#define SIZE 10

int myarr[SIZE];
int myarr[] = {11, 34, };
int main(void) {
    for(int i = 0; i < SIZE; i++) {
        printf("%d: %d\n", i, myarr[i]);      

    }
    // ASSERT(11, myarr[0]);
    // ASSERT(34, myarr[1]);
    // ASSERT(0, myarr[2]);    
    // ASSERT(0, myarr[3]);
    // ASSERT(0, myarr[4]);
    // ASSERT(0, myarr[5]);
    // ASSERT(0, myarr[6]);
    // ASSERT(0, myarr[7]);
    // ASSERT(0, myarr[8]);
    // ASSERT(0, myarr[9]);

    return 0;
}