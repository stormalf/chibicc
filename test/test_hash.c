#include <stdio.h>
#include <string.h>
#include "test.h"

#define HASHMAP_SIZE 10
unsigned int hash(const char *key) {
    unsigned int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % HASHMAP_SIZE;
}

int main() {
    char *keys[] = {"float4", "float4a1", "float4a16"};
    for (int i = 0; i < 3; i++) {
        printf("Key: %s, Hash: %u\n", keys[i], hash(keys[i]));
        if (i == 0) {
            ASSERT(5, hash(keys[i]));
        } else if (i == 1) {
            ASSERT(1, hash(keys[i]));
        } else if (i == 2) {
            ASSERT(3, hash(keys[i]));
        }
    }
    return 0;
}
