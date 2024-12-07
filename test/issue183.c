#include <stdio.h>

int main () {
    int a = 1;

    switch (a)
    {
    case 0: 
        int c = 2;
        printf("c = %d\n", c);
        /* code */
        break;
    
    case 1: 
        int c = 1;
        printf("c = %d\n", c);
        break;
    
    default:  {
        int c = 3;
        printf("c = %d\n", c);
        break;
    }
    
    
    }

    return 0;
}