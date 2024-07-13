#include <stdio.h>
#include <stddef.h>
#include <assert.h>
struct abc1 { int a, b, c; };
union abc2 { int a, b, c; };

typedef struct abc1 abc1;
typedef union abc2 abc2;

int main () {

assert(offsetof(abc1, a) == 0); // always, because there's no padding before a.
assert(offsetof(abc1, b) == 4); // here, on my system
assert(offsetof(abc2, a) == offsetof(abc2, b)); // (members overlap)

printf("%ld\n", offsetof(abc1, a) );
printf("%ld\n", offsetof(abc1, b) );
printf("%ld\n", offsetof(abc2, a) );
return 0;
}