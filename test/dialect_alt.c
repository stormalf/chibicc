#include "test.h"
#include <stdint.h>
int main() {
  long tid;
  uintptr_t result;
  __asm__("{movq %%fs:0, %0|mov %0, qword ptr fs:[0]}" : "=r" (tid));
   __asm__("{movq %%rsp, %0" : "=r" (result));
  printf("Ok\n");
  return 0;
}
