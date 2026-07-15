static int unused_static_var;
int used_global = 5;
static int unused_static_fn() { return 1; }
int used_fn() { return used_global; }

int main() {
  return used_fn();
}
