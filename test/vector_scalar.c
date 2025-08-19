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
    ASSERT(3, fr[0]);
    ASSERT(4, fr[1]);
    ASSERT(5, fr[2]);
    ASSERT(6, fr[3]);
    fr = 3.0f + fv;      // scalar lhs
    print_float4(fr);
    ASSERT(4, fr[0]);
    ASSERT(5, fr[1]);
    ASSERT(6, fr[2]);
    ASSERT(7, fr[3]);
    fr = fv - 1.0f;
    print_float4(fr);
    ASSERT(0, fr[0]);
    ASSERT(1, fr[1]);
    ASSERT(2, fr[2]);
    ASSERT(3, fr[3]);
    fr = 2.0f - fv;
    print_float4(fr);
    ASSERT(1, fr[0]);
    ASSERT(0, fr[1]);
    ASSERT(-1, fr[2]);
    ASSERT(-2, fr[3]);    
    fr = fv * 2.0f;
    print_float4(fr);
    ASSERT(2, fr[0]);
    ASSERT(4, fr[1]);
    ASSERT(6, fr[2]);
    ASSERT(8, fr[3]);    
    fr = 0.5f * fv;
    print_float4(fr);
    ASSERT(0, fr[0]);
    ASSERT(1, fr[1]);
    ASSERT(1, fr[2]);
    ASSERT(2, fr[3]);     
    fr = fv / 2.0f;
    print_float4(fr);
    ASSERT(0, fr[0]);
    ASSERT(1, fr[1]);
    ASSERT(1, fr[2]);
    ASSERT(2, fr[3]);      
    fr = 8.0f / fv;
    print_float4(fr);
    ASSERT(8, fr[0]);
    ASSERT(4, fr[1]);
    ASSERT(2, fr[2]);
    ASSERT(2, fr[3]);      
    fr = -fv;
    print_float4(fr);
    ASSERT(-1, fr[0]);
    ASSERT(-2, fr[1]);
    ASSERT(-3, fr[2]);
    ASSERT(-4, fr[3]);      

    // Double2 operations with scalar
    dr = dv + 1.0;
    print_double2(dr);
    ASSERT(2, dr[0]);
    ASSERT(3, dr[1]);
   
    dr = 2.0 + dv;
    print_double2(dr);
    ASSERT(3, dr[0]);
    ASSERT(4, dr[1]);    
    dr = dv - 1.0;
    print_double2(dr);
    ASSERT(0, dr[0]);
    ASSERT(1, dr[1]);        
    dr = 5.0 - dv;
    print_double2(dr);
    ASSERT(3, dr[0]);
    ASSERT(2, dr[1]);        
    dr = dv * 2.0;
    print_double2(dr);
    ASSERT(3, dr[0]);
    ASSERT(5, dr[1]);        
    dr = 0.5 * dv;
    print_double2(dr);
    ASSERT(0, dr[0]);
    ASSERT(1, dr[1]);        
    dr = dv / 2.0;
    print_double2(dr);
    ASSERT(0, dr[0]);
    ASSERT(1, dr[1]);        
    dr = 4.0 / dv;
    print_double2(dr);
    ASSERT(2, dr[0]);
    ASSERT(1, dr[1]);        
    dr = -dv;
    print_double2(dr);
    ASSERT(-1, dr[0]);
    ASSERT(-2, dr[1]);        

    // Int4 operations with scalar
    ir = iv + 5;
    print_int4(ir);
    ASSERT(15, ir[0]);
    ASSERT(25, ir[1]);
    ASSERT(35, ir[2]);
    ASSERT(45, ir[3]);      

    ir = 10 + iv;
    print_int4(ir);
    ASSERT(20, ir[0]);
    ASSERT(30, ir[1]);
    ASSERT(40, ir[2]);
    ASSERT(50, ir[3]);      

    ir = iv - 3;
    print_int4(ir);
    ASSERT(7, ir[0]);
    ASSERT(17, ir[1]);
    ASSERT(27, ir[2]);
    ASSERT(37, ir[3]);      

    ir = 50 - iv;
    print_int4(ir);
    ASSERT(40, ir[0]);
    ASSERT(30, ir[1]);
    ASSERT(20, ir[2]);
    ASSERT(10, ir[3]);      

    ir = iv * 2;
    print_int4(ir);
    ASSERT(20, ir[0]);
    ASSERT(40, ir[1]);
    ASSERT(60, ir[2]);
    ASSERT(80, ir[3]);      

    ir = 3 * iv;
    print_int4(ir);
    ASSERT(30, ir[0]);
    ASSERT(60, ir[1]);
    ASSERT(90, ir[2]);
    ASSERT(120, ir[3]);      

    ir = ~iv;
    print_int4(ir);
    ASSERT(-11, ir[0]);
    ASSERT(-21, ir[1]);
    ASSERT(-31, ir[2]);
    ASSERT(-41, ir[3]);      

    ir = -iv;
    print_int4(ir);
    ASSERT(-10, ir[0]);
    ASSERT(-20, ir[1]);
    ASSERT(-30, ir[2]);
    ASSERT(-40, ir[3]);      

    ir = iv & 0x0F;
    print_int4(ir);
    ASSERT(10, ir[0]);
    ASSERT(4, ir[1]);
    ASSERT(14, ir[2]);
    ASSERT(8, ir[3]);      

    ir = iv | 0x0F;
    print_int4(ir);
    ASSERT(15, ir[0]);
    ASSERT(31, ir[1]);
    ASSERT(31, ir[2]);
    ASSERT(47, ir[3]);      

    ir = iv ^ 0x0F;
    print_int4(ir);
    ASSERT(5, ir[0]);
    ASSERT(27, ir[1]);
    ASSERT(17, ir[2]);
    ASSERT(39, ir[3]);      

    printf("OK\n");
    return 0;
}
