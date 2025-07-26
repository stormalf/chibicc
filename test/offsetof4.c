#include "test.h"
#include <stddef.h>

struct lscpu_cputype {
    int vendor;
    int model;
    char modelname[64];
    int stepping;
};

int main() {
    size_t offset;

    // Test each offset via switch
    offset = offsetof(struct lscpu_cputype, vendor);
    switch (offset) {
        case offsetof(struct lscpu_cputype, vendor):
            printf("vendor offset: %zu\n", offset);
            ASSERT(0, offsetof(struct lscpu_cputype, vendor) );
            break;
        case offsetof(struct lscpu_cputype, model):
            printf("model offset: %zu\n", offset);
            ASSERT(4, offsetof(struct lscpu_cputype, model) );
            break;
        case offsetof(struct lscpu_cputype, modelname):
            printf("modelname offset: %zu\n", offset);
            ASSERT(8, offsetof(struct lscpu_cputype, modelname) );
            break;
        case offsetof(struct lscpu_cputype, stepping):
            printf("stepping offset: %zu\n", offset);
            ASSERT(72, offsetof(struct lscpu_cputype, stepping) );
            break;
        default:
            printf("Unknown offset: %zu\n", offset);
            break;
    }

    // Repeat for other fields, to demonstrate multiple cases
    offset = offsetof(struct lscpu_cputype, model);
    switch (offset) {
        case offsetof(struct lscpu_cputype, vendor):
            printf("vendor offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, model):
            printf("model offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, modelname):
            printf("modelname offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, stepping):
            printf("stepping offset: %zu\n", offset);
            break;
        default:
            printf("Unknown offset: %zu\n", offset);
            break;
    }

    // Similarly for modelname
    offset = offsetof(struct lscpu_cputype, modelname);
    switch (offset) {
        case offsetof(struct lscpu_cputype, vendor):
            printf("vendor offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, model):
            printf("model offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, modelname):
            printf("modelname offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, stepping):
            printf("stepping offset: %zu\n", offset);
            break;
        default:
            printf("Unknown offset: %zu\n", offset);
            break;
    }

    // Similarly for stepping
    offset = offsetof(struct lscpu_cputype, stepping);
    switch (offset) {
        case offsetof(struct lscpu_cputype, vendor):
            printf("vendor offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, model):
            printf("model offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, modelname):
            printf("modelname offset: %zu\n", offset);
            break;
        case offsetof(struct lscpu_cputype, stepping):
            printf("stepping offset: %zu\n", offset);
            break;
        default:
            printf("Unknown offset: %zu\n", offset);
            break;
    }

    return 0;
}
