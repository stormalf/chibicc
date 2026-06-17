struct PyObject {
    long ob_refcnt;
    struct PyTypeObject *ob_type;
};

struct PyObject *builtin_id(struct PyObject *self, struct PyObject *v) {
    return v;
}

struct PyObject *builtin_abs(struct PyObject *self, struct PyObject *v) {
    int x = 42;
    long y = 100;
    return v;
}

int main(void) {
    struct PyObject a, b;
    builtin_id(&a, &b);
    builtin_abs(&a, &b);
    return 0;
}
