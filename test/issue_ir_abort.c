// Regression test: --emit-ir / --backend-llvm must emit declare void @abort()
// in the module preamble when __builtin_abort is used.
// Without the fix, llc fails with:
//   error: use of undefined value '@abort'
#define ASSERT_COND(cond) do { if (!(cond)) __builtin_abort(); } while (0)

int check(int x) { return x; }

int main() {
  ASSERT_COND(check(1) == 1);
  return 0;
}
