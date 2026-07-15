#include "test.h"

extern int printf(const char *, ...);

int main(void)
{
  int timeout = 2;
  /* Statement expression with a goto at the end never produces a value;
     type analysis must not leave node->ty as NULL, otherwise the LLVM
     backend crashes in gen_ir_cast. */
  (1 ?
   printf("timeout=%d\n", timeout) :
   ({
     int i = 1;
     while (1)
       while (i--)
       some_label:
         printf("error\n");
     goto some_label;
   })
  );
  return 0;
}
