int recursive_tail_call(int n) {
    if (n <= 0) return 1;
    return recursive_tail_call(n - 1);
}

int main() {
    return recursive_tail_call(1000000);
}
