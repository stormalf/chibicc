inline int foo(void) {
    return 42;
}

int main(void) {
    return foo() != 42;
}