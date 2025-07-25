
#include "test.h"
int main(int argc, char *argv[])
 { 
    printf("argc=%d\n", argc);
    ASSERT(1, argc);
    return argc - 1; 
    
}