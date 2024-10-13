#include <xmmintrin.h>
#include <stdio.h>



int main()
{
    __m128 a = _mm_set1_ps(1.0f);
    __m128 b = _mm_set1_ps(2.0f);
    __m128 c = _mm_add_ps(a, b);
    float d = _mm_cvtss_f32(c);
    printf("%f\n", d);
    return 0;
}