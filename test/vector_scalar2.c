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
    ASSERT(10, fr[0]);
    ASSERT(13, fr[1]);
    ASSERT(16, fr[2]);
    ASSERT(19, fr[3]);

    fr = (3.0f + fv1) * (fv2 - 1.0f);   // scalar + vector multiplied by (vector - scalar)
    print_float4(fr);
    ASSERT(16, fr[0]);
    ASSERT(25, fr[1]);
    ASSERT(36, fr[2]);
    ASSERT(49, fr[3]);    

    fr = -fv1 + fv2 / 2.0f;             // unary negation + vector / scalar
    print_float4(fr);
    ASSERT(1, fr[0]);
    ASSERT(1, fr[1]);
    ASSERT(0, fr[2]);
    ASSERT(0, fr[3]);    

    // Compound double2 expression
    dr = dv1 + 1.0 * dv2 - 0.5;         // vector + scalar*vector - scalar
    print_double2(dr);
    ASSERT(4, dr[0]);
    ASSERT(6, dr[1]);
 

    dr = (2.0 + dv1) / (dv2 - 1.0);     // scalar + vector divided by (vector - scalar)
    print_double2(dr);
    ASSERT(1, dr[0]);
    ASSERT(1, dr[1]);

    dr = -dv1 + dv2 * 0.5;              // unary negation + vector * scalar
    print_double2(dr);

    ASSERT(0, dr[0]);
    ASSERT(-0, dr[1]);

    // Compound int4 expression
    ir = iv1 + 3 * iv2 - 5;             // vector + scalar*vector - scalar
    print_int4(ir);
    ASSERT(8, ir[0]);
    ASSERT(21, ir[1]);   
    ASSERT(34, ir[2]);
    ASSERT(47, ir[3]);    

    ir = (10 + iv1) * (iv2 - 2);        // scalar + vector multiplied by (vector - scalar)
    print_int4(ir);
    ASSERT(-20, ir[0]);
    ASSERT(0, ir[1]);   
    ASSERT(40, ir[2]);
    ASSERT(100, ir[3]);        

    ir = ~iv1 ^ iv2 + 1;                // bitwise NOT, XOR, addition
    print_int4(ir);
    ASSERT(-9, ir[0]);
    ASSERT(-24, ir[1]);   
    ASSERT(-27, ir[2]);
    ASSERT(-46, ir[3]);    
    printf("OK\n");
    return 0;
}
