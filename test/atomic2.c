
#include <stdatomic.h>
#include "test.h"


int main() {
    int value = 5;
    int expected = 5;
    int new_value = 10;

    if (atomic_compare_exchange_weak(&value, &expected, new_value)) {
        printf("Value was exchanged.\n");        
    } else {
        printf("Value was not exchanged. Expected: %d, Value: %d\n", expected, value);
    }
    printf("Final Value: %d\n", value);
    ASSERT(10, value);


    if (atomic_compare_exchange_strong(&value, &expected, new_value)) {
        printf("Value was exchanged.\n");
    } else {
        printf("Value was not exchanged. Expected: %d, Value: %d\n", expected, value);
    }
    printf("Final Value: %d\n", value);
    ASSERT(10, value);

    value = 5;
    int old_value = atomic_fetch_add(&value, 3);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
     ASSERT(5, old_value);
     ASSERT(8, value);

    value = 5;
    old_value = atomic_fetch_sub(&value, 3);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(2, value);


    value = 5; // 0101 in binary
    old_value = atomic_fetch_or(&value, 2); // 0010 in binary
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(7, value);

    value = 5; // 0101 in binary
    old_value = atomic_fetch_xor(&value, 3); // 0011 in binary
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(6, value);

    
    value = 5; // 0101 in binary
    old_value = atomic_fetch_and(&value, 3); // 0011 in binary
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(1, value);

    value = 5;
    old_value = atomic_exchange(&value, 10);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(10, value);

    value = 5;
    old_value = atomic_exchange_explicit(&value, 10, memory_order_seq_cst);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(10, value);
    
    value = 5;
    int loaded_value = atomic_load(&value);
    printf("Loaded Value: %d\n", loaded_value);
    ASSERT(5, value);
    ASSERT(5, loaded_value);
    
    value = 5;
    loaded_value = atomic_load_explicit(&value, memory_order_acquire);
    printf("Loaded Value: %d\n", loaded_value);
    ASSERT(5, value);
    ASSERT(5, loaded_value);    
    
    atomic_store(&value, 11);
    printf("Stored Value: %d\n", value);
    ASSERT(11, value);
    
    atomic_store_explicit(&value, 12, memory_order_release);
    printf("Stored Value: %d\n", value);
    ASSERT(12, value);

    atomic_flag flag = ATOMIC_FLAG_INIT;
    if (!atomic_flag_test_and_set(&flag)) {
        printf("Flag was clear and is now set.\n");
    } else {
        printf("Flag was already set.\n");
    }

   atomic_flag flag2 = ATOMIC_FLAG_INIT;
    if (!atomic_flag_test_and_set_explicit(&flag2, memory_order_acquire)) {
        printf("Flag2 was clear and is now set.\n");
    } else {
        printf("Flag2 was already set.\n");
    }


    atomic_flag flag3 = ATOMIC_FLAG_INIT;
    atomic_flag_test_and_set(&flag3);
    atomic_flag_clear(&flag3);
    printf("Flag3 is now clear.\n");



    atomic_flag flag4 = ATOMIC_FLAG_INIT;
    atomic_flag_test_and_set(&flag4);
    atomic_flag_clear_explicit(&flag4, memory_order_release);
    printf("Flag4 is now clear.\n");


    value = 5;
    old_value = __sync_val_compare_and_swap(&value, 5, 10);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(10, value);


    value = 5;
    old_value = __sync_fetch_and_add(&value, 3);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(8, value);

    value = 5;
    old_value = __sync_fetch_and_sub(&value, 3);
    printf("Old Value: %d, New Value: %d\n", old_value, value);
    ASSERT(5, old_value);
    ASSERT(2, value);    

    value = 5;
    old_value = __sync_val_compare_and_swap(&value, 5, 10);
    printf("Old value: %d, New value: %d\n", old_value, value); // Expected: Old value: 5, New value: 10
    ASSERT(5, old_value);
    ASSERT(10, value);
    value = 5;
    old_value = __sync_val_compare_and_swap(&value, 5, 20);
    printf("Old value: %d, New value: %d\n", old_value, value); // Expected: Old value: 5, New value: 20
    ASSERT(5, old_value);
    ASSERT(20, value);


    return 0;

}
