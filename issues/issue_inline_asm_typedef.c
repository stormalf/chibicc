// chibicc should produce a clear error message (not crash) when an
// inline asm input operand refers to a typedef name instead of a variable.

typedef int mytype_t;

int main() {
    int x;
    asm("nop %0" : "=r"(x) : "r"(mytype_t));
    return 0;
}
