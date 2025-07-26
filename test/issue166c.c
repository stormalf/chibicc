#include <stdbool.h>
#include "test.h"
#define N 4

typedef struct {
    bool arr[N + 1];
} S;

int foo(int x) {
    typedef struct {
        bool arr[x + 1];
    } S;
    return sizeof(S);
}

int main() {
    S s = {0};
    s.arr[0] = 1;
    printf("%d\n", foo(10)); //should return 11 
    ASSERT(11, foo(10));
    if (s.arr[0])
        return 0;
    return 1;
}
