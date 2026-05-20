// Test DWARF output for struct alignment - simulate CPython patterns
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Pattern 1: Simple PyObject-like struct
struct PyObject {
    int64_t ob_refcnt;
    void *ob_type;
};

// Pattern 2: Type object with many fields  
struct PyTypeObject {
    struct PyObject ob_base;
    int64_t ob_size;
    const char *tp_name;
    int64_t tp_basicsize;
    int64_t tp_itemsize;
};

// Pattern 3: Struct with _Alignas members
struct AlignedMembers {
    char c;
    _Alignas(16) double d;
    _Alignas(32) int i;
};

// Pattern 4: Struct with __attribute__((aligned)) on struct itself
struct __attribute__((aligned(64))) BigAlignedStruct {
    char c;
    int i;
    double d;
};

// Pattern 5: Packed struct with ms_struct
#pragma pack(push, 1)
struct __attribute__((ms_struct)) PackedMS {
    uint8_t a;
    uint16_t b;
    uint32_t c;
};
#pragma pack(pop)

// Pattern 6: Nested struct with alignment - like _PyRuntime
struct Inner {
    int64_t x;
    _Alignas(16) double y;
};

struct Outer {
    char tag;
    struct Inner inner;
    int64_t arr[4];
};

// Pattern 7: Global instance similar to _PyRuntime
struct BigState {
    int64_t field1;
    struct AlignedMembers field2;
    struct PyObject *singletons[10];
    struct PyTypeObject type_obj;
};

static struct BigState global_state;

int main(void) {
    printf("sizeof(PyObject)=%zu\n", sizeof(struct PyObject));
    printf("offsetof(PyObject,ob_type)=%zu\n", offsetof(struct PyObject, ob_type));
    printf("sizeof(PyTypeObject)=%zu\n", sizeof(struct PyTypeObject));
    printf("offsetof(PyTypeObject,tp_name)=%zu\n", offsetof(struct PyTypeObject, tp_name));
    printf("sizeof(AlignedMembers)=%zu\n", sizeof(struct AlignedMembers));
    printf("offsetof(AlignedMembers,d)=%zu\n", offsetof(struct AlignedMembers, d));
    printf("offsetof(AlignedMembers,i)=%zu\n", offsetof(struct AlignedMembers, i));
    printf("sizeof(BigAlignedStruct)=%zu\n", sizeof(struct BigAlignedStruct));
    printf("sizeof(PackedMS)=%zu\n", sizeof(struct PackedMS));
    printf("sizeof(Inner)=%zu\n", sizeof(struct Inner));
    printf("sizeof(Outer)=%zu\n", sizeof(struct Outer));
    printf("offsetof(Outer,inner)=%zu\n", offsetof(struct Outer, inner));
    printf("sizeof(BigState)=%zu\n", sizeof(struct BigState));
    printf("sizeof(global_state)=%zu\n", sizeof(global_state));
    return 0;
}
