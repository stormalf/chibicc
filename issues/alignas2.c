#include <stdio.h>
#include <stddef.h>
//#include "test.h"
struct S {
  _Alignas(2048) char i[127] ;
};

static void lvar(int cnt) {
  if (cnt > 3)
    return;
  //ASSERT(0, ({ _Alignas(1024) int i; (unsigned long)&i % 1024; }));
  _Alignas(1024) int i;
  printf("=====%d\n", (unsigned long)&i % 1024);
  lvar(cnt + 1);
}

static void larray(int cnt) {
  if (cnt > 3)
    return;
  //ASSERT(0, ({ _Alignas(512) char arr[17]; (unsigned long)&arr[0] % 512; }));
   _Alignas(512) char arr[17];
  printf("=====%d\n", (unsigned long)&arr[0] % 512);
  larray(cnt + 1);
}

static void vla22(int cnt) {
  if (cnt > 3)
    return;
  //ASSERT(0, ({ _Alignas(256) char vla[cnt]; (unsigned long)&vla[0] % 256; }));
  _Alignas(256) char vla1[cnt];
  printf("=====%d\n", (unsigned long)&vla1[0] % 256);
  vla22(cnt + 1);
}

static void lstruct(int cnt) {
  if (cnt > 3)
    return;
  //ASSERT(0, ({ struct S s; (unsigned long)&s.i % 2048; }));
  struct S s;
  printf("=====%d\n", (unsigned long)&s.i % 2048);
  lstruct(cnt + 1);
}

static void pass_by_stack_struct(int cnt, struct S s) {
  if (cnt > 3)
    return;
  //ASSERT(0, ({ (unsigned long)&s.i % 2048; }));
  printf("=====%d\n", (unsigned long)&s.i % 2048);
  pass_by_stack_struct(cnt + 1, s);
}

static void mix(int cnt, struct S s) {
  if (cnt > 3)
    return;

  //ASSERT(0, ({ (unsigned long)&s.i % 2048; }));
  printf("=====%d\n", (unsigned long)&s.i % 2048);
  _Alignas(1024) int i;
  //ASSERT(0, (unsigned long)&i % 1024 );
  printf("=====%d\n", (unsigned long)&i % 1024 );

  _Alignas(256) char arr[17];
  //ASSERT(0, (unsigned long)&arr[0] % 256 );
  printf("=====%d\n", (unsigned long)&arr[0] % 256 );

  _Alignas(512) char vla[cnt];
  //ASSERT(0, ({ (unsigned long)&vla[0] % 512; }));
  printf("=====%d\n", (unsigned long)&vla[0] % 512);

  struct S s2 = s;
  //ASSERT(0,  (unsigned long)&s2.i % 2048 );
  printf("=====%d\n", (unsigned long)&s2.i % 2048 );

  mix(cnt + 1, s2);
}

int main(void) {
  struct S s;
  //ASSERT(0,  (unsigned long)&s.i % 2048 );
  printf("=====%d\n", (unsigned long)&s.i % 2048 );
  printf("Offset of i: %lu\n", offsetof(struct S, i));
  printf("Size of struct S: %lu\n", sizeof(struct S));



  lvar(1);
  larray(1);
  vla22(1);
  lstruct(1);
  pass_by_stack_struct(1,s);
  mix(1, s);

  printf("OK\n");
  return 0;
}

