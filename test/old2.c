
#include <stdio.h>

// K&R style function declaration
static void func1(p, i) char **p; int i; {
    printf("%s\n", p[i]);
}

int main() {
    char *array[] = { "one", "two", "three" };
    func1(array, 1);
    printf("%s\n", array[0]);
    printf("%s\n", array[1]);
    printf("%s\n", array[2]);
    return 0;
}
