

void example() {
  int *p = alloca(10 * sizeof(int));
  // Use the allocated memory...
}


int main() {
    example();
    return 0;
}