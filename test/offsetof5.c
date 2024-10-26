#include <stdio.h>
#include <stddef.h>  // For offsetof
#include "test.h"
struct Address {
    char street[20];
    int zipcode;
};

struct Person {
    char initial;
    int age;
    double height;
    float weight;
    struct Address addr;
};




int main() {
    // Use offsetof to get the offsets of struct members
    printf("Offset of 'initial': %lu\n", offsetof(struct Person, initial));
    ASSERT(0, offsetof(struct Person, initial));
    printf("Offset of 'age': %lu\n", offsetof(struct Person, age));
    ASSERT(4, offsetof(struct Person, age));
    printf("Offset of 'height': %lu\n", offsetof(struct Person, height));
    ASSERT(8, offsetof(struct Person, height));
    printf("Offset of 'weight': %lu\n", offsetof(struct Person, weight));
    ASSERT(16, offsetof(struct Person, weight));
    printf("Offset of 'age': %lu\n", offsetof(struct Person, age));
    ASSERT(4, offsetof(struct Person, age));
    printf("Offset of 'addr': %lu\n", offsetof(struct Person, addr));
    ASSERT(20, offsetof(struct Person, addr));
    printf("Offset of 'addr.street': %lu\n", offsetof(struct Person, addr.street));
    ASSERT(20, offsetof(struct Person, addr.street));
    printf("Offset of 'addr.zipcode': %lu\n", offsetof(struct Person, addr.zipcode));
    ASSERT(40, offsetof(struct Person, addr.zipcode));

    return 0;
}
