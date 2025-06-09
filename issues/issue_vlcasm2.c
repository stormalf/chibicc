
int foo (int *dstp) {
asm volatile (
  "movntdq %%xmm1, 0(%[dst])"
  :
  : [dst] "r"(dstp)
  : "memory"
);
}


int main() {

    return 0;
}