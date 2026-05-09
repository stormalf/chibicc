typedef int (f_t)(int);
f_t a, b; // Testing comma list (CPython)

int main() { 
  if (0) b(42); // Should compile now
  return 0;
}
// 'a' and 'b' are unreferenced, should not appear in nm as 'U'
