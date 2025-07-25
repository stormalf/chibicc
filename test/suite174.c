
#include <math.h>
#include "test.h"

int main()
{
   // variables
   float a = 12.34 + 56.78;
   printf("%f\n", a);
   ASSERT(69, a);

   // infix operators
   printf("%f\n", 12.34 + 56.78);
   printf("%f\n", 12.34 - 56.78);
   printf("%f\n", 12.34 * 56.78);
   printf("%f\n", 12.34 / 56.78);

   // comparison operators
   printf("%d %d %d %d %d %d\n", 12.34 < 56.78, 12.34 <= 56.78, 12.34 == 56.78, 12.34 >= 56.78, 12.34 > 56.78, 12.34 != 56.78);
   printf("%d %d %d %d %d %d\n", 12.34 < 12.34, 12.34 <= 12.34, 12.34 == 12.34, 12.34 >= 12.34, 12.34 > 12.34, 12.34 != 12.34);
   printf("%d %d %d %d %d %d\n", 56.78 < 12.34, 56.78 <= 12.34, 56.78 == 12.34, 56.78 >= 12.34, 56.78 > 12.34, 56.78 != 12.34);

   // assignment operators
   a = 12.34;
   a += 56.78;
   printf("%f\n", a);
   ASSERT(69, a);

   a = 12.34;
   a -= 56.78;
   printf("%f\n", a);
   ASSERT(-44, a);

   a = 12.34;
   a *= 56.78;
   printf("%f\n", a);
   ASSERT(700, a);

   a = 12.34;
   a /= 56.78;
   printf("%f\n", a);
   ASSERT(0, a);

   // prefix operators
   printf("%f\n", +12.34);
   printf("%f\n", -12.34);

   // type coercion
   a = 2;
   printf("%f\n", a);   
   printf("%f\n", sin(2));

   return 0;
}

