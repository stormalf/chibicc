#include "test.h"
#include <stdint.h>

typedef float float4 __attribute__((vector_size(16)));
typedef double double2 __attribute__((vector_size(16)));
typedef int int4 __attribute__((vector_size(16)));

void print_float4(float4 v) { for (int i = 0; i < 4; i++) printf("%f ", v[i]); printf("\n"); }
void print_double2(double2 v) { for (int i = 0; i < 2; i++) printf("%f ", v[i]); printf("\n"); }
void print_int4(int4 v) { for (int i = 0; i < 4; i++) printf("%d ", v[i]); printf("\n"); }

int main() {
    float4 fv1 = {1, 2, 3, 4};
    float4 fv2 = {5, 6, 7, 8};
    float4 fr;
    double2 dv1 = {1.5, 2.5};
    double2 dv2 = {3.5, 4.5};
    double2 dr;
    int4 iv1 = {10, 20, 30, 40};
    int4 iv2 = {1, 2, 3, 4};
    int4 ir;

    // Compound float4 expression
    fr = fv1 + 2.0f * fv2 - 1.0f;       // vector + scalar*vector - scalar
    print_float4(fr);

    fr = (3.0f + fv1) * (fv2 - 1.0f);   // scalar + vector multiplied by (vector - scalar)
    print_float4(fr);

    fr = -fv1 + fv2 / 2.0f;             // unary negation + vector / scalar
    print_float4(fr);

    // Compound double2 expression
    dr = dv1 + 1.0 * dv2 - 0.5;         // vector + scalar*vector - scalar
    print_double2(dr);

    dr = (2.0 + dv1) / (dv2 - 1.0);     // scalar + vector divided by (vector - scalar)
    print_double2(dr);

    dr = -dv1 + dv2 * 0.5;              // unary negation + vector * scalar
    print_double2(dr);

    // Compound int4 expression
    ir = iv1 + 3 * iv2 - 5;             // vector + scalar*vector - scalar
    print_int4(ir);

    ir = (10 + iv1) * (iv2 - 2);        // scalar + vector multiplied by (vector - scalar)
    print_int4(ir);

    ir = ~iv1 ^ iv2 + 1;                // bitwise NOT, XOR, addition
    print_int4(ir);

    printf("OK\n");
    return 0;
}
