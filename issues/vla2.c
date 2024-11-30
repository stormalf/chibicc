#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nargs;         // Number of arguments
    int args[];       // Flexible array placeholder
} FunctionCallInfoBaseData;

// Helper function to calculate size required for the flexible array
size_t SizeForFunctionCallInfo(int nargs) {
    return sizeof(FunctionCallInfoBaseData) + (nargs - 1) * sizeof(int);
}

// Macro definition, using 'name' and 'nargs' to create a flexible allocation
#define LOCAL_FCINFO(name, nargs)                    \
    union {                                          \
        FunctionCallInfoBaseData fcinfo;             \
        char fcinfo_data[SizeForFunctionCallInfo(nargs)]; \
    } name##data;                                    \
    FunctionCallInfoBaseData *name = &name##data.fcinfo;


int main() {
    int nargs = 3;  // Set the number of arguments for testing

    // Using the LOCAL_FCINFO macro
    LOCAL_FCINFO(fcinfo, nargs);


    printf("Size required for fcinfo_data with nargs = %d: %zu bytes\n", nargs, SizeForFunctionCallInfo(nargs));
    // Set nargs and initialize args array
    fcinfo->nargs = nargs;
    printf("nargs = %d: %zu bytes\n", fcinfo->nargs, SizeForFunctionCallInfo(nargs));
    for (int i = 0; i < nargs; i++) {
        fcinfo->args[i] = i + 1;  // Initialize with values 1, 2, 3, ...
    }



    // Print the contents to verify correctness
    printf("Number of arguments: %d\n", fcinfo->nargs);
    printf("Arguments: ");
    for (int i = 0; i < fcinfo->nargs; i++) {
        printf("%d ", fcinfo->args[i]);
    }
    printf("\n");

    return 0;
}
