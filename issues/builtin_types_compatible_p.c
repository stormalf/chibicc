#include "test.h"

int main() {
// Basic scalar compatibility
ASSERT(1, __builtin_types_compatible_p(int, int));
ASSERT(0, __builtin_types_compatible_p(int, long));
ASSERT(1, __builtin_types_compatible_p(const int, int));
ASSERT(1, __builtin_types_compatible_p(volatile int, int));
ASSERT(1, __builtin_types_compatible_p(const volatile int, int));

// Pointer qualifiers
ASSERT(1, __builtin_types_compatible_p(int *, int *));
ASSERT(0, __builtin_types_compatible_p(int *, const int *));
ASSERT(1, __builtin_types_compatible_p(int *const, int *));
ASSERT(0, __builtin_types_compatible_p(int **, int *));

// Arrays
ASSERT(1, __builtin_types_compatible_p(int[3], int[3]));
ASSERT(1, __builtin_types_compatible_p(int[3], int[]));
ASSERT(0, __builtin_types_compatible_p(int[3], int[4]));
ASSERT(0, __builtin_types_compatible_p(int[3], int *));
ASSERT(1, __builtin_types_compatible_p(int[], int[]));

// Struct tag identity
struct A { int x; };
struct B { int x; };

ASSERT(1, __builtin_types_compatible_p(struct A, struct A));
ASSERT(0, __builtin_types_compatible_p(struct A, struct B));

// Forward-declared (incomplete) structs
struct Fwd;
struct Fwd { int x; };

ASSERT(1, __builtin_types_compatible_p(struct Fwd, struct Fwd));

// Two distinct incomplete structs
struct X;
struct Y;

ASSERT(0, __builtin_types_compatible_p(struct X, struct Y));

// Nested structs
struct Outer1 { struct A a; };
struct Outer2 { struct A a; };
struct Outer3 { struct B a; };

ASSERT(0, __builtin_types_compatible_p(struct Outer1, struct Outer2));
ASSERT(0, __builtin_types_compatible_p(struct Outer1, struct Outer3));

// Typedef aliases
typedef int myint;
ASSERT(1, __builtin_types_compatible_p(myint, int));

typedef struct A A_alias;
ASSERT(1, __builtin_types_compatible_p(A_alias, struct A));

// Flexible array member (Postgres-style)
struct Flex1 {
  int len;
  char data[];
};

struct Flex2 {
  int len;
  char data[];
};

ASSERT(0, __builtin_types_compatible_p(struct Flex1, struct Flex2));
ASSERT(1, __builtin_types_compatible_p(struct Flex1, struct Flex1));

// Flexible vs fixed array
struct Flex3 {
  int len;
  char data[1];
};

ASSERT(0, __builtin_types_compatible_p(struct Flex1, struct Flex3));

// Function types
int fn1(int);
int fn2(int);
int fn3(long);

ASSERT(1, __builtin_types_compatible_p(typeof(fn1), typeof(fn2)));
ASSERT(0, __builtin_types_compatible_p(typeof(fn1), typeof(fn3)));

int oldstyle();
int proto(void);

ASSERT(1, __builtin_types_compatible_p(typeof(oldstyle), typeof(proto)));

// Enum vs int
enum E { E1 };
ASSERT(0, __builtin_types_compatible_p(enum E, int));

// Anonymous structs
ASSERT(0,
  __builtin_types_compatible_p(
    struct { int x; },
    struct { int x; }
  )
);

// Multi-level pointers
ASSERT(1, __builtin_types_compatible_p(int **, int **));
ASSERT(0, __builtin_types_compatible_p(int **, const int **));

// Array decay should NOT apply
ASSERT(0, __builtin_types_compatible_p(typeof((int[3]){0}), int *));

  printf("OK\n");
  return 0;
}