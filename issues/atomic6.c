#include <stdio.h>
#include <stdint.h>

// Test __sync_fetch_and_sub
void test_sync_fetch_and_sub() {
    int value = 100;
    int result = __sync_fetch_and_sub(&value, 10);

    printf("Test __sync_fetch_and_sub:\n");
    printf("Initial value: 100, Subtracted: 10\n");
    printf("Result: %d, New value: %d\n\n", result, value);
}

// Test __sync_fetch_and_or
void test_sync_fetch_and_or() {
    int value = 0x0F0F;  // Initial value with some bits set
    int result = __sync_fetch_and_or(&value, 0xF0F0);  // OR with 0xF0F0

    printf("Test __sync_fetch_and_or:\n");
    printf("Initial value: 0x0F0F, OR with: 0xF0F0\n");
    printf("Result: 0x%X, New value: 0x%X\n\n", result, value);
}

// Test __sync_fetch_and_add
void test_sync_fetch_and_add() {
    int value = 50;
    int result = __sync_fetch_and_add(&value, 25);

    printf("Test __sync_fetch_and_add:\n");
    printf("Initial value: 50, Added: 25\n");
    printf("Result: %d, New value: %d\n\n", result, value);
}

int main() {
    test_sync_fetch_and_sub();  // Testing __sync_fetch_and_sub
    test_sync_fetch_and_or();   // Testing __sync_fetch_and_or
    test_sync_fetch_and_add();  // Testing __sync_fetch_and_add

    return 0;
}
