// Test for -fvisibility=hidden and -ffreestanding flags
// These flags should be accepted without error

// Test for -ffreestanding
// In freestanding environment, certain standard library functions may not be available
// We'll just verify the flag is accepted

// Test for -fvisibility=hidden
// This affects symbol visibility in the compiled object

void hidden_func(void) __attribute__((visibility("hidden")));
void visible_func(void);

void hidden_func(void) {
    // This function should have hidden visibility
}

void visible_func(void) {
    // This function should have default visibility
    hidden_func();
}

int main(void) {
    visible_func();
    return 0;
}