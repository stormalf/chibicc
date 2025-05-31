#include <stdio.h>
#include "test.h"

int main(void) {


  {


    int i[2][4] = {[0][0 ... 1] = 4, 2, 3, 7, [1][1 ... 2] = 1, 9};


    int ans[] = {4,4,2,3,7,1,1,9};


    ASSERT(0, memcmp(&i, &ans, sizeof(ans)));

    int j[1][3] = {[0][0 ... 1] = 4, 2};
    printf("%d%d%d\n", j[0][0], j[0][1], j[0][2]); // expected 442, got 420

  }





  printf("OK\n");


}