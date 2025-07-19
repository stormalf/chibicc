
#include "test.h"
  struct Fields {
    _Bool    a :1;
    long long  :3;
    unsigned b :4;
    _Bool    c :1;
    unsigned d :3;
    unsigned e :2;
    long       :2;
}  __attribute__((packed));


struct WithPadding {
    char a;           // 1 byte
    unsigned b : 3;   // 3 bits
    unsigned c : 5;   // 5 bits
    int d;            // 4 bytes
};

struct ZeroWidth {
    unsigned a : 5;   // 5 bits
    unsigned : 0;     // Forces alignment to next int
    unsigned b : 3;   // 3 bits
};


struct Complex {
    _Bool a : 1;      // 1 bit
    unsigned b : 3;   // 3 bits
    unsigned c : 5;   // 5 bits
    int d : 4;        // 4 bits
    unsigned long long e : 10; // 10 bits
};


struct MaxAlign {
    unsigned long long a : 64; // 64 bits
    unsigned long long b : 64; // 64 bits
};


int main() {
  { 
    struct { char a; int b; } __attribute__((packed)) x; 
    printf("%d\n", sizeof(x)); 
    ASSERT(5, sizeof(x));
  }


  { 
    union { int a; char b[4]; } x={0x01020304}; 
    printf("%d\n", x.b[0]); 
    ASSERT(4, x.b[0]); 
  }
  struct Fields s1 = {11,22,33,44,55,66,77};
  struct Fields s2 = {77,66,55,44,33,22,11};
  printf("%d\n", sizeof(struct Fields));
  ASSERT(2, sizeof(struct Fields));
  printf("%d\n", _Alignof(struct Fields));
  ASSERT(1, _Alignof(struct Fields));
  printf("Size of WithPadding struct: %lu\n", sizeof(struct WithPadding)); // Expected: 8
  ASSERT(8, sizeof(struct WithPadding));
  printf("Size of ZeroWidth struct: %lu\n", sizeof(struct ZeroWidth)); // Expected: 8
  ASSERT(8, sizeof(struct ZeroWidth));
  printf("Size of Complex struct: %lu\n", sizeof(struct Complex)); // Expected: 8
  ASSERT(8, sizeof(struct Complex));
  printf("Size of MaxAlign struct: %lu\n", sizeof(struct MaxAlign)); // Expected: 16
  ASSERT(16, sizeof(struct MaxAlign));


    return 0;
}