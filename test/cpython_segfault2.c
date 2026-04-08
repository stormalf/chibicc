// test_memoryiter.c

#include <stddef.h>
#include <stdint.h>
#include "test.h"

/* ---------------- CPython core stubs ---------------- */

typedef intptr_t Py_ssize_t;

typedef struct _object {
    Py_ssize_t ob_refcnt;
    struct _typeobject *ob_type;
} PyObject;

typedef struct _typeobject {
    PyObject ob_base;
    const char *tp_name;
    Py_ssize_t tp_basicsize;

    void (*tp_dealloc)(PyObject *);
    PyObject *(*tp_getattro)(PyObject *, PyObject *);
    unsigned long tp_flags;

    int (*tp_traverse)(PyObject *, void *, void *);
    PyObject *(*tp_iter)(PyObject *);
    PyObject *(*tp_iternext)(PyObject *);
} PyTypeObject;

#define PyObject_HEAD PyObject ob_base;
#define PyVarObject_HEAD_INIT(type, size) \
    { { 1, (type) } }

#define Py_TPFLAGS_DEFAULT   0x00000001UL
#define Py_TPFLAGS_HAVE_GC   0x00000020UL

/* ---------------- Dummy dependent types ---------------- */

typedef struct {
    PyObject ob_base;
} PyMemoryViewObject;

/* ---------------- Forward declarations ---------------- */

static void memoryiter_dealloc(PyObject *self);
static int memoryiter_traverse(PyObject *self, void *visit, void *arg);
static PyObject *memoryiter_next(PyObject *self);
static PyObject *PyObject_GenericGetAttr(PyObject *obj, PyObject *name);
static PyObject *PyObject_SelfIter(PyObject *obj);

/* ---------------- memoryiterobject ---------------- */

typedef struct {
    PyObject_HEAD
    Py_ssize_t it_index;
    PyMemoryViewObject *it_seq; /* NULL when exhausted */
    Py_ssize_t it_length;
    const char *it_fmt;
} memoryiterobject;

PyTypeObject PyType_Type; /* dummy */

PyTypeObject _PyMemoryIter_Type = {    
    .tp_name = "memory_iterator",
    .tp_basicsize = sizeof(memoryiterobject),

    .tp_dealloc = memoryiter_dealloc,
    .tp_getattro = PyObject_GenericGetAttr,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,

    .tp_traverse = memoryiter_traverse,
    .tp_iter = PyObject_SelfIter,
    .tp_iternext = memoryiter_next,
};

static void
memoryiter_dealloc(PyObject *self)
{
    memoryiterobject *it = (memoryiterobject *)self;
    it->it_seq = NULL;
}

static int
memoryiter_traverse(PyObject *self, void *visit, void *arg)
{
    (void)self;
    (void)visit;
    (void)arg;
    return 0;
}

static PyObject *
memoryiter_next(PyObject *self)
{
    memoryiterobject *it = (memoryiterobject *)self;

    if (!it->it_seq || it->it_index >= it->it_length)
        return NULL;

    it->it_index++;
    return self; /* dummy non-NULL value */
}

static PyObject *
PyObject_GenericGetAttr(PyObject *obj, PyObject *name)
{
    (void)obj;
    (void)name;
    return NULL;
}

static PyObject *
PyObject_SelfIter(PyObject *obj)
{
    return obj;
}

int main(void)
{
    memoryiterobject it = {
        .ob_base = { 1, &_PyMemoryIter_Type },
        .it_index = 0,
        .it_seq = (PyMemoryViewObject *)0x1, /* fake non-NULL */
        .it_length = 2,
        .it_fmt = "B",
    };

    PyObject *o = (PyObject *)&it;

    printf("Type name: %s\n", _PyMemoryIter_Type.tp_name);
    printf("Size: %zu\n", sizeof(memoryiterobject));
    ASSERT(48, sizeof(memoryiterobject));

    _PyMemoryIter_Type.tp_iter(o);
    _PyMemoryIter_Type.tp_iternext(o);
    _PyMemoryIter_Type.tp_iternext(o);
    _PyMemoryIter_Type.tp_iternext(o); /* exhausted */

    _PyMemoryIter_Type.tp_dealloc(o);

    return 0;
}
