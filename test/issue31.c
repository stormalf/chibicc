#include <stdio.h>
//#include "test.h"
struct info {
    int key;
    int :5;
    int data;
};

int Get(struct info * m) { return m->data;}

int main() {
     struct info info = {1, 1, 1};
     printf("%ld\n", sizeof(info));
     assert(8, sizeof(info));
     printf("%d\n", Get(&info));     
     assert(1, Get(&info));
    return 0;
}