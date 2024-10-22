//#include <stdio.h>
typedef unsigned char u8;
struct S
{
  u8 a,b;
  u8 c[2];
};

struct U
{
  u8 a;
  struct S s;
  u8 b;
};
struct U gu = {3, 5,6,7,8, 4};

int main()
{
  //printf("%ld\n", sizeof(struct U));
    ({ struct { struct { int a; struct { int b; }; }; int c; } x={1,2,3,.b=4,5}; x.c; });
  return 0;
}
