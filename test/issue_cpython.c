#include "test.h"

typedef struct {
    int type;
    const char *func;
    const char *err_msg;
} PyStatus;

PyStatus _PyStatus_OK() {
    return (PyStatus){0, NULL, NULL};
}

PyStatus _PyTime_Init(int *time) {
    *time = 123;
    return _PyStatus_OK();
}

int _PyStatus_EXCEPTION(PyStatus status) {
    return status.type != 0;
}

PyStatus test_func(int *time) {
    PyStatus status = _PyTime_Init(time);
    if (_PyStatus_EXCEPTION(status)) {
        return status;
    }
    return _PyStatus_OK();
}

int main() {
    int time = 0;
    PyStatus status = test_func(&time);
    ASSERT(0, status.type);
    ASSERT(123, time);
    return 0;
}