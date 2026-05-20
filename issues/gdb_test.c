struct PyObject {
  long ob_refcnt;
  struct PyTypeObject *ob_type;
};

struct PyObject *builtin_id(struct PyObject *self, struct PyObject *v) {
  return v;
}

int main(void) {
  struct PyObject a, b;
  builtin_id(&a, &b);
  return 0;
}
