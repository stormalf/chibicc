// chibicc should handle enum constants in inline asm input operands,
// treating them as immediate values (same as TK_NUM).

enum { MY_CONST = 42 };

int main() {
    int x;
    asm("mov %1, %0" : "=r"(x) : "r"(MY_CONST));
    if (x != 42)
        return 1;
    return 0;
}
