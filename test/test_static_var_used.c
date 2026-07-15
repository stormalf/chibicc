// Test: chibicc should NOT warn about a static global variable that IS used
static int used_static_var = 0;

int main(void) {
  return used_static_var;
}
