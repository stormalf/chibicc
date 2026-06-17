struct PyObject {
    long ob_refcnt;
    long ob_type;
};

struct PyObject *builtin_id(struct PyObject *self, struct PyObject *v) {
    return v;
}

int main(void) {
    struct PyObject a, b;
    a.ob_refcnt = 1;
    a.ob_type = 0;
    b.ob_refcnt = 2;
    b.ob_type = 0;
    return (builtin_id(&a, &b) == &b) ? 0 : 1;
}
