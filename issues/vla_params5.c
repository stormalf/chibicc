#include "test.h"
#include <stdint.h>
typedef int32_t i32;
typedef uint8_t u8;

void fn1(i32 z, i32 b1[sizeof(z)]){
  ASSERT(4, sizeof(*b1));
  ASSERT(8, sizeof(b1));

}


void fn1b(i32 *z, i32 b1[sizeof(*z)]){
  ASSERT(4, sizeof(*b1));
  ASSERT(8, sizeof(b1));

}

void fn2(i32 z, i32 (*a)[z], i32 b1[sizeof(*a)]){
  ASSERT(28, sizeof(*a));
  ASSERT(8, sizeof(b1));
//   ASSERT(112, sizeof(*b2));
}


int main() {
    fn1(7, 0);
    fn1b(7, 0);
    fn2(7, 0, 0);
    printf("OK\n");

    return 0;
}