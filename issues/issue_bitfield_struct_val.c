#include "test.h"

struct S0 {
   unsigned f0 : 18;
   const unsigned f1 : 1;
   signed : 0;
   signed f2 : 11;
   signed f3 : 16;
};

static int64_t  func_39(struct S0  p_40, const struct S0  p_41, uint16_t  p_42);

static int64_t  func_39(struct S0  p_40, const struct S0  p_41, uint16_t  p_42)
{
   return p_40.f3;
}

int main() {
   struct S0 s;
   s.f0 = 1; s.f1 = 0; s.f2 = 2; s.f3 = 3;
   ASSERT(3, func_39(s, s, 0));
   return 0;
}
