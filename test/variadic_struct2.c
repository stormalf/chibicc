#include <stddef.h>
#include <stdarg.h>
#include "test.h"

typedef struct {
    int a;  // 4 bytes
} SmallStruct;


typedef struct {
    int a;   // 4 bytes
    double b; // 8 bytes
} MediumStruct;


typedef struct {
    double a; // 8 bytes
    double b; // 8 bytes
    double c; // 8 bytes
} LargeStruct;

void print_large(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        LargeStruct s = va_arg(ap, LargeStruct);
        printf("LargeStruct %d: a = %f, b = %f, c = %f\n", i, s.a, s.b, s.c);
        if (i == 0) {
            ASSERT(1, s.a);
            ASSERT(1, s.b);            
            ASSERT(1, s.c);            
        }
    }

    va_end(ap);
}

void print_medium(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        MediumStruct s = va_arg(ap, MediumStruct);
        printf("MediumStruct %d: a = %d, b = %f\n", i, s.a, s.b);
        if (i == 0) {
            ASSERT(1, s.a);
            ASSERT(1, s.b);            
        }
    }

    va_end(ap);
}


void print_small(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        SmallStruct s = va_arg(ap, SmallStruct);
        printf("SmallStruct %d: a = %d\n", i, s.a);
        if (i == 0) {
            ASSERT(1, s.a);
         
        }        
    }

    va_end(ap);
}

void print_small_ptr(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        SmallStruct *s = va_arg(ap, SmallStruct *);
        printf("SmallStruct %d: a = %d\n", i, s->a);
        if (i == 0) {
            ASSERT(1, s->a);        
        }
    }

    va_end(ap);
}


void print_medium_ptr(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        MediumStruct *s = va_arg(ap, MediumStruct *);
        printf("MediumStruct %d: a = %d, b = %f\n", i, s->a, s->b);
        if (i == 0) {
            ASSERT(1, s->a);
            ASSERT(1, s->b);            
        }
    }

    va_end(ap);
}

void print_large_ptr(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        LargeStruct *s = va_arg(ap, LargeStruct *);
        printf("LargeStruct %d: a = %f, b = %f, c = %f\n", i, s->a, s->b, s->c);
        if (i == 0) {
            ASSERT(1, s->a);
            ASSERT(1, s->b);
            ASSERT(1, s->c);
        } else if (i == 1) {
            ASSERT(2, s->a);
            ASSERT(2, s->b);
            ASSERT(2, s->c);            
        } else if (i == 2) {
            ASSERT(3, s->a);
            ASSERT(3, s->b);
            ASSERT(3, s->c);
        }
    }

    va_end(ap);
}

void test_mixed1(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        int x = va_arg(ap, int);
        double y = va_arg(ap, double);
        SmallStruct s = va_arg(ap, SmallStruct);
        if (i == 0) {
            ASSERT(1, x);
            ASSERT(1, y);
            ASSERT(1, s.a);
        }


        printf("int: %d, double: %f, SmallStruct.a: %d\n", x, y, s.a);
    }

    va_end(ap);
}


void test_mixed2(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        char *str = va_arg(ap, char *);
        MediumStruct s = va_arg(ap, MediumStruct);
        MediumStruct *ps = va_arg(ap, MediumStruct *);

        printf("str: %s, MediumStruct.a: %d, b: %f, Pointer MediumStruct.a: %d, b: %f\n",
            str, s.a, s.b, ps->a, ps->b);
        if (i == 0) {
            ASSERT(2, ps->a);
            ASSERT(2, ps->b);
            ASSERT(1, s.a);
            ASSERT(1, s.b);
        }
            
    }

    va_end(ap);
}


void test_mixed3(int n, ...) {
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++) {
        int x = va_arg(ap, int);
        LargeStruct *p = va_arg(ap, LargeStruct *);
        double y = va_arg(ap, double);

        printf("int: %d, LargeStruct.a: %f, b: %f, c: %f, double: %f\n",
            x, p->a, p->b, p->c, y);
    }

    va_end(ap);
}


int main() {
    SmallStruct s1 = {1}, s2 = {2}, s3 = {3};
    print_small(3, s1, s2, s3);
    print_small_ptr(3, &s1, &s2, &s3);
    test_mixed1(2, 1, 1.1, s1, 2, 2.2, s2);
    MediumStruct s1 = {1, 1.1}, s2 = {2, 2.2}, s3 = {3, 3.3};
    print_medium(3, s1, s2, s3);
    print_medium_ptr(3, &s1, &s2, &s3);
    test_mixed2(1, "hello", s1, &s2);
    LargeStruct s1 = {1.1, 1.2, 1.3};
    LargeStruct s2 = {2.1, 2.2, 2.3};
    LargeStruct s3 = {3.1, 3.2, 3.3};
    print_large(3, s1, s2, s3);    
    print_large_ptr(3, &s1, &s2, &s3);
    LargeStruct ls = {1.1, 2.2, 3.3};
    test_mixed3(1, 42, &ls, 4.4);
    return 0;
}
