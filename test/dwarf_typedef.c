// Test: DWARF should emit typedef references so GDB pretty-printers
// can match types like "PyObject" instead of "struct _object".
//
// Compile:
//   ./chibicc -g -c issues/test_typedef_dwarf.c -o /tmp/test_td.o
//   readelf --debug-dump=info /tmp/test_td.o > /tmp/test_td.dwarf
//
// Verify that the parameter type references go through the typedef:
//   grep -A3 "DW_TAG_typedef" /tmp/test_td.dwarf   # should show "PyObject"
//   grep "builtin_id" -A10 /tmp/test_td.dwarf | grep "DW_AT_type"
//   # The type ref should point to a pointer_type whose target is the typedef

typedef struct _object {
    long ob_refcnt;
    struct _typeobject *ob_type;
} PyObject;

struct _typeobject {
    PyObject ob_base;
    long ob_size;
    const char *tp_name;
};

// Function using typedef'd pointer — DWARF must show PyObject *
PyObject *builtin_id(PyObject *self, PyObject *v) {
    return v;
}

// Dummy main to make a complete program
int main(void) {
    PyObject a, b;
    builtin_id(&a, &b);
    return 0;
}
