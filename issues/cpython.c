// probe_dict_layout.c
#define Py_BUILD_CORE 1                 // unlocks internal headers’ declarations
#include <Python.h>
#include <internal/pycore_dict.h>       // <-- defines struct _dictkeysobject
#include <stddef.h>
#include "test.h"

int main(void) {
    printf("sizeof(PyDictObject)        = %zu\n", sizeof(PyDictObject));
    printf("sizeof(PyDictKeysObject)    = %zu\n", sizeof(PyDictKeysObject));
    printf("offsetof(PyDictObject, ma_keys)   = %zu\n", offsetof(PyDictObject, ma_keys));
    printf("offsetof(PyDictObject, ma_values) = %zu\n", offsetof(PyDictObject, ma_values));
    return 0;
}
