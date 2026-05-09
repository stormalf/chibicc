#include "test.h"
#include <stdio.h>
struct P { int a,b; };
int main(){ printf("ai=%zu ap=%zu offb=%zu\n", _Alignof(int), _Alignof(struct P), offsetof(struct P,b)); return 0;}
