int recursive_tail_call(int a, int b, int c, int d, int e, int f, int g, int *out) {
    if (g <= 0) {
        *out = 42;
        return 0;
    }
    int local = g;
    if (local < 0) {
        *out = -1;
        return 0;
    }
    return recursive_tail_call(a, b, c, d, e, f, g - 1, out);
}

int main() {
    int out = 0;
    recursive_tail_call(1, 2, 3, 4, 5, 6, 10, &out);
    return (out == 42) ? 0 : 1;
}
