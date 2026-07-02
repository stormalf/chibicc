// Demonstrates that extern array followed by definition
// should compile, not produce LLVM redefinition error
extern int extarr[55];
int extarr[55];

int main(void) {
  extarr[0] = 42;
  return extarr[0];
}
