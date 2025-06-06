#include <stddef.h>

void test_gs_segment(void **ofs, void *value) {
  void *res;

  __asm__("movq %%gs:%1, %0"
          : "=r" (res)
          : "m" (*((void **)ofs))
          :);

  __asm__("movq %%fs:%1, %0"
          : "=r" (res)
          : "m" (*((void **)ofs))
          :);

  __asm__("movq %1,%%gs:%0"
          : "=m" (*((void **)ofs))
          : "rn" (value)
          :);

  __asm__("movq %1,%%fs:%0"
          : "=m" (*((void **)ofs))
          : "rn" (value)
          :);
}


int main() {

  return 0;
}