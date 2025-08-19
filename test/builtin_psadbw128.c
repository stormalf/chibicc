#include "test.h"

typedef char char16 __attribute__((vector_size(16)));
typedef unsigned long long ull2 __attribute__((vector_size(16)));

int main() {
    char16 a = { 10, 20, 30, 40, 50, 60, 70, 80,
                  90,100,110,120,130,140,150,160 };

    char16 b = { 15, 25, 35, 45, 55, 65, 75, 85,
                  85, 95,105,115,125,135,145,155 };

    ull2 result = (ull2)__builtin_ia32_psadbw128(a, b);

    printf("Low 8-byte sum:  %llu\n", result[0]);
    printf("High 8-byte sum: %llu\n", result[1]);

    ASSERT(40, result[0]);
    ASSERT(40, result[1]);

    printf("OK\n");
    return 0;
}
