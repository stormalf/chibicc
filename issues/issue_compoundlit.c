#include <stdio.h>

struct S {
  int a, b;
};

int main() {
    struct S s1 = {11,-22 };
    //int i = sizeof(char){1};
    //printf("%d\n", i);
    printf("%d\n", sizeof ({ int arr[11]; arr; }) );  //gcc prints 8 chibicc prints 44
    printf("%d\n", sizeof ({ int arr[s1.a]; arr; }) ); //gcc prints 8 chibicc prints random value
    return 0;
}