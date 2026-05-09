#include <unistd.h>

int main() {
  execl("/bin/sh", "sh", "-c", "XXXX", NULL);
  return 0;
}
