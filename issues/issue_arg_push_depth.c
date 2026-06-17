// Reproducer for argument push depth tracking bug with omit-frame-pointer
// When -O3 enables -fomit-frame-pointer, pushing arguments on the real stack
// via push() changes %rsp, but subsequent RSP-relative local variable access
// doesn't account for the changed %rsp.

extern void callee(int a, int b, int c, int d, int e, int f, int g);
extern int get_val(void);

int test_arg_depth(int p1, int p2) {
    int local1 = get_val();
    int local2 = get_val();
    // This call has 7 args (>6 so one is stack-passed)
    // Right-to-left eval: g, f, e, d, c, b, a
    // push() for each reg arg changes %rsp
    // RSP-relative access to p1/p2/locals during eval must account for depth
    callee(p1, p2, local1, local2, get_val(), get_val(), get_val());
    return p1 + p2 + local1 + local2;
}
