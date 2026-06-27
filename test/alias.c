#include "test.h"
void f() {}
void g() __attribute__((alias("f")));
int main() { printf("Ok\n"); return 0; }
