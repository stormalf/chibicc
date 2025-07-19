#include "test.h"
typedef int MyInt, MyInt2[4];
enum MyEnum
{
ENUM_TEST
};

typedef enum MyEnum MyEnum;

int main() {
    printf("OK\n");
    ASSERT(0, ENUM_TEST);
    return 0;
}