#include "test.h"
#include <xmmintrin.h>    // __m128, _mm_add_ps, _mm_set_ps

typedef __m128 v4;

v4 add7(v4 a, v4 b, v4 c, v4 d, v4 e, v4 f, v4 g) {
    return _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(a,b),c),d),e),f),g);
}

void print_v4(v4 x) {
    float f[4];
    _mm_storeu_ps(f, x);
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);
}

int main(){
    v4 a = _mm_set_ps(10,20,30,40);
    v4 b = _mm_set_ps(1,1,1,1);
    v4 c = _mm_set_ps(2,2,2,2);
    v4 d = _mm_set_ps(3,3,3,3);
    v4 e = _mm_set_ps(4,4,4,4);
    v4 f = _mm_set_ps(5,5,5,5);
    v4 g = _mm_set_ps(6,6,6,6);
    v4 r = add7(a,b,c,d,e,f,g);
    print_v4(r); // expect element-wise sums

    ASSERT(61, r[0]);
    ASSERT(51, r[1]);
    ASSERT(41, r[2]);
    ASSERT(31, r[3]);
    printf("OK\n");
    return 0;
}
