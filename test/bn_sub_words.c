typedef unsigned long BN_ULONG;

BN_ULONG bn_sub_words(BN_ULONG *rp, const BN_ULONG *ap, const BN_ULONG *bp, int n) {
    BN_ULONG ret;
    long i = 0;
    if (n <= 0)
        return 0;

    asm volatile("       subq    %0,%0           \n" /* clear borrow */
                 "       jmp     1f              \n"
                 ".p2align 4                     \n"
                 "1:     movq    (%4,%2,8),%0    \n"
                 "       sbbq    (%5,%2,8),%0    \n"
                 "       movq    %0,(%3,%2,8)    \n"
                 "       lea     1(%2),%2        \n"
                 "       dec     %1              \n"
                 "       jnz     1b              \n"
                 "       sbbq    %0,%0           \n"
        : "=&r"(ret), "+c"(n), "+r"(i)
        : "r"(rp), "r"(ap), "r"(bp)
        : "cc", "memory");

    return ret & 1;
}

int main() {
    BN_ULONG a[4] = {5, 6, 7, 8};
    BN_ULONG b[4] = {1, 2, 3, 4};
    BN_ULONG r[4];
    bn_sub_words(r, a, b, 4);
    if (r[0] != 4 || r[1] != 4 || r[2] != 4 || r[3] != 4)
        return 1;
    return 0;
}
