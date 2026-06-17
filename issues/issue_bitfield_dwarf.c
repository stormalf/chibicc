// Test that bitfields have correct DWARF info for GDB
// This mimics CPython's PyASCIIObject state bitfield pattern
// Compile: ./chibicc -xc test/common -Itest issues/issue_bitfield_dwarf.c -g -o /tmp/bf_test

#include "test.h"

// CPython-like struct with bitfield state flags
typedef struct {
  unsigned long length;
  unsigned long hash;
  struct {
    unsigned int kind : 2;      // 0=unknown, 1=compact ascii, 2=compact, 3=legacy
    unsigned int compact : 1;
    unsigned int ascii : 1;
    unsigned int ready : 1;
    unsigned int : 24;          // padding
  } state;
} PyASCIIObject;

// Another pattern: bitfields at different offsets
typedef struct {
  int a : 1;
  int b : 2;
  int c : 3;
  int d : 4;
  int e : 5;
  int f : 6;
  int g : 7;
  int h : 8;
} BitPacked;

PyASCIIObject obj = {42, 0, {1, 1, 1, 1}}; // compact ascii string state
BitPacked bp = {1, 2, 3, 4, 5, 6, 7, 8};

int main() {
  // Runtime verification
  ASSERT(42, obj.length);
  ASSERT(0, obj.hash);
  ASSERT(1, obj.state.kind);
  ASSERT(1, obj.state.compact);
  ASSERT(1, obj.state.ascii);
  ASSERT(1, obj.state.ready);
  
  ASSERT(1, bp.a);
  ASSERT(2, bp.b);
  ASSERT(3, bp.c);
  ASSERT(4, bp.d);
  ASSERT(5, bp.e);
  ASSERT(6, bp.f);
  ASSERT(7, bp.g);
  ASSERT(8, bp.h);

  printf("OK\n");
  return 0;
}
