
#include "test.h"

// Pre-attribute
__attribute__((deprecated))
enum Color1 {
    RED1,
    GREEN1,
    BLUE1
};

// Post-attribute
enum Color2
__attribute__((deprecated))
{
    RED2,
    GREEN2,
    BLUE2
};

// Attribute on enum constants
enum Color3 {
    RED3 __attribute__((deprecated)),
    GREEN3,
    BLUE3
};

int main() {
    enum Color1 c1 = RED1;
    enum Color2 c2 = RED2;
    enum Color3 c3 = RED3;

    printf("Color1: %d\n", c1);
    ASSERT(0, c1);
    printf("Color2: %d\n", c2);
    ASSERT(0, c2);
    printf("Color3: %d\n", c3);
    ASSERT(0, c3);
    return 0;
}
