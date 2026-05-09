void f() {}
void g() __attribute__((alias("f")));
int main() { return 0; }
