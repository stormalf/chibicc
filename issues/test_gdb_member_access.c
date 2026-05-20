// Test: GDB Python API struct member access with typedef'd structs
// Reproduces the pattern used in CPython GDB pretty-printers:
//   gdb.lookup_type('PyVarObject').pointer() -> cast -> ['ob_size']
//
// Compile:
//   ./chibicc -g issues/test_gdb_member_access.c -o /tmp/test_gdb_prog
//   gdb -batch -x /tmp/test_gdb.py /tmp/test_gdb_prog

typedef struct _object {
    long ob_refcnt;
    struct _typeobject *ob_type;
} PyObject;

typedef struct _typeobject {
    PyObject ob_base;
    long ob_size;
    const char *tp_name;
} PyTypeObject;

typedef struct {
    PyObject ob_base;
    long ob_size;
} PyVarObject;

typedef struct {
    PyVarObject ob_base;
    PyObject *ob_item[1];
} PyTupleObject;

PyVarObject global_var;
PyTupleObject global_tuple;

int main(void) {
    global_var.ob_size = 42;
    global_var.ob_base.ob_refcnt = 1;
    global_tuple.ob_base.ob_size = 3;
    global_tuple.ob_item[0] = 0;
    return 0;
}
