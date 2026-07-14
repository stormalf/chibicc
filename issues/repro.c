int main() {
  int i = 0;
  int j = 0;
  int k = 0;
  do {
    if (++j > 3) break;
    continue;
    k++;
  } while (1);
  return j;
}
