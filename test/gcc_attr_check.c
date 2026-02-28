#include <stdio.h>
#include <stddef.h>
struct S1 { int x __attribute__((aligned(32))), y; };
int main(){printf("offx=%zu offy=%zu align=%zu size=%zu\n",offsetof(struct S1,x),offsetof(struct S1,y),_Alignof(struct S1),sizeof(struct S1));}
