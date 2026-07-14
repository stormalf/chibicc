// Test: chibicc should NOT warn about a static function that IS used
// (Regression: false positive "defined but not used" when a non-static
//  function calls a static function)
static int used_static_fn(void) { return 0; }

int main(void) {
  return used_static_fn();
}
