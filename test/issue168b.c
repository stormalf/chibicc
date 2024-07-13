

int add2(int x, int y)
{
  return x + y;
}


int main() {
int (*fn)(int,int) = add2; fn(2,5);

return 0;
}