#include "test.h"
#include <stdint.h>

typedef float float4 __attribute__((vector_size(16)));
typedef double double2 __attribute__((vector_size(16)));
typedef int int4 __attribute__((vector_size(16)));

void print_float4(float4 v) {
    for (int i = 0; i < 4; i++) printf("%f ", v[i]);
    printf("\n");
}

void print_double2(double2 v) {
    for (int i = 0; i < 2; i++) printf("%f ", v[i]);
    printf("\n");
}

void print_int4(int4 v) {
    for (int i = 0; i < 4; i++) printf("%d ", v[i]);
    printf("\n");
}

int main() {
    float4 fv = {1,2,3,4};
    float4 fr;
    double2 dv = {1.5, 2.5};
    double2 dr;
    int4 iv = {10,20,30,40};
    int4 ir;

    // Float4 operations with scalar
    fr = fv + 2.0f;      // scalar rhs
    print_float4(fr);
    fr = 3.0f + fv;      // scalar lhs
    print_float4(fr);
    fr = fv - 1.0f;
    print_float4(fr);
    fr = 2.0f - fv;
    print_float4(fr);
    fr = fv * 2.0f;
    print_float4(fr);
    fr = 0.5f * fv;
    print_float4(fr);
    fr = fv / 2.0f;
    print_float4(fr);
    fr = 8.0f / fv;
    print_float4(fr);
    fr = -fv;
    print_float4(fr);

    // Double2 operations with scalar
    dr = dv + 1.0;
    print_double2(dr);
    dr = 2.0 + dv;
    print_double2(dr);
    dr = dv - 1.0;
    print_double2(dr);
    dr = 5.0 - dv;
    print_double2(dr);
    dr = dv * 2.0;
    print_double2(dr);
    dr = 0.5 * dv;
    print_double2(dr);
    dr = dv / 2.0;
    print_double2(dr);
    dr = 4.0 / dv;
    print_double2(dr);
    dr = -dv;
    print_double2(dr);

    // Int4 operations with scalar
    ir = iv + 5;
    print_int4(ir);
    ir = 10 + iv;
    print_int4(ir);
    ir = iv - 3;
    print_int4(ir);
    ir = 50 - iv;
    print_int4(ir);
    ir = iv * 2;
    print_int4(ir);
    ir = 3 * iv;
    print_int4(ir);
    ir = ~iv;
    print_int4(ir);
    ir = -iv;
    print_int4(ir);
    ir = iv & 0x0F;
    print_int4(ir);
    ir = iv | 0x0F;
    print_int4(ir);
    ir = iv ^ 0x0F;
    print_int4(ir);
    printf("OK\n");
    return 0;
}
