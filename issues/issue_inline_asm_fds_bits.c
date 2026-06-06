// Regression: __FD_ZERO inline asm uses &__FDS_BITS(fdsp)[0]
// which chibicc cannot handle yet.
// Expected: error (not crash)
typedef unsigned long __fd_mask;
typedef struct { __fd_mask fds_bits[16]; } fd_set;

int main() {
    fd_set fds;
    fd_set *fdsp = &fds;
    int __d0, __d1;
    __asm__ __volatile__ ("cld; rep; stosl"
        : "=c" (__d0), "=D" (__d1)
        : "a" (0), "0" (sizeof(fd_set) / sizeof(__fd_mask)),
          "1" (&((fdsp)->fds_bits)[0])
        : "memory");
    return 0;
}
