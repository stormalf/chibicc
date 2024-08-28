void test_func(__int128 a, __int128 b) {
    __int128 sum = a + b;
    ASSERT128(sum, a + b);
}

int main() {
    __int128 x = I128(1, 0);
    __int128 y = I128(2, 0);
    test_func(x, y);
    return 0;
}
