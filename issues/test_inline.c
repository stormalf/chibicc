#include <stdio.h>

struct A {
    int x;
};

struct A* get_a(int i);

/* external function (NOT defined) */
struct A* get_a(int i);

/* inline wrapper (like VLC case) */
static inline struct A*
wrap_get_a(struct A *const *p, int i)
{
    return get_a(i);
}

int main(void)
{
    struct A *a = 0;
    a = wrap_get_a(&a, 1);
    return 0;
}