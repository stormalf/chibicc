#include <stdio.h>
#include <stdint.h>
typedef __attribute__((aligned(32))) int A;
int main(){
  A z;
  printf("alignof(A)=%zu alignof(z)=%zu addrmod=%zu\n", _Alignof(A), _Alignof(z), ((uintptr_t)&z)%32);
  return 0;
}
