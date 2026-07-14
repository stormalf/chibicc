#include "test.h"
#include <stdint.h>
#include <x86intrin.h>
//#include <cetintrin.h>
//#include <x86gprintrin.h> 

void f4(void) {
    __builtin_ia32_saveprevssp();
    __builtin_ia32_setssbsy();
    __builtin_ia32_slwpcb();    
    __builtin_ia32_xend();
    __builtin_ia32_serialize();
    __builtin_ia32_xsusldtrk();
    __builtin_ia32_xresldtrk();
    __builtin_ia32_clui();
    __builtin_ia32_stui();
    __builtin_ia32_testui();
    __builtin_ia32_wbnoinvd();
    __builtin_ia32_xtest();    
    __builtin_ia32_wbinvd();
    __builtin_ia32_vzeroall();
    __builtin_ia32_vzeroupper();
    __builtin_ia32_femms();
    __builtin_ia32_writeeflags_u64(0x200);
    unsigned long long x = 0x201;
    __builtin_ia32_writeeflags_u64(x);
    __builtin_ia32_incsspq(x);
    void *ptr;
    __builtin_ia32_rstorssp(ptr);
    __builtin_ia32_clrssbsy(1);
    int val = 1;
    __builtin_ia32_clrssbsy(val);    
}

unsigned int f7(void) {
    return __builtin_ia32_rdpid();
}

unsigned int f8(void) {
    return __builtin_ia32_rdfsbase32();
}

unsigned long long f9(void) {
    return __builtin_ia32_rdfsbase64();
}

unsigned int f10(void) {
    return __builtin_ia32_rdgsbase32();
}

unsigned long long f11(void) {
    return __builtin_ia32_rdgsbase64();
}

int f5(void) {
    return __builtin_ia32_rdpkru();
}

unsigned int f6(void) {
    return __builtin_ia32_xbegin();
}

unsigned long long f3(void) {
    return __builtin_ia32_rdsspq();
}

unsigned long long f1(void) {
    return __builtin_ia32_rdtsc();
}

unsigned long long f2(void) {
    return __builtin_ia32_readeflags_u64();
}


static inline void wrssd(uint32_t *p, uint32_t v) {
    __builtin_ia32_wrssd(p, v);
    __builtin_ia32_wrssq(p, v);
    __builtin_ia32_wrussd(p, v);
    __builtin_ia32_wrussq(p, v);
}

__attribute__((noinline))
void test(uint32_t *p) {
    wrssd(p, 0xdeadbeef);
}

static unsigned ref_sbb_u32(
    unsigned a,
    unsigned b,
    unsigned bin,
    unsigned *bout)
{
    unsigned tmp = a - b;
    unsigned res = tmp - bin;
    *bout = (a < b) | (tmp < bin);
    return res;
}

static unsigned char ref_addcarryx_u32(
    unsigned char cin,
    unsigned x,
    unsigned y,
    unsigned *out)
{
    unsigned sum = x + y;
    unsigned sum2 = sum + cin;
    *out = sum2;
    return (sum < x) | (sum2 < cin);
}

int test_addcarryx(void)
{
    unsigned vals[] = {
        0, 1, 0x7fffffff, 0x80000000, 0xffffffff
    };

    for (unsigned i = 0; i < 5; i++)
        for (unsigned j = 0; j < 5; j++)
            for (unsigned cin = 0; cin <= 1; cin++) {
                unsigned out1, out2;
                unsigned char c1 =
                    ref_addcarryx_u32(cin, vals[i], vals[j], &out1);
                unsigned char c2 =
                    __builtin_ia32_addcarryx_u32(
                        cin, vals[i], vals[j], &out2);

                if (out1 != out2 || c1 != c2)
                    return 1;
            }
    return 0;
}

static unsigned char ref_sbb_u64(
    unsigned char bin,
    unsigned long x,
    unsigned long y,
    unsigned long *out)
{
    unsigned long tmp = x - y;
    unsigned long res = tmp - bin;
    *out = res;
    return (x < y) | (tmp < bin);
}

int test_sbb_u64(void)
{
    unsigned long vals[] = {
        0UL, 1UL, 0x7fffffffffffffffUL, 0x8000000000000000UL, 0xffffffffffffffffUL
    };

    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            for (int bin=0; bin<=1; bin++) {
                unsigned long out1, out2;
                unsigned char b1 = ref_sbb_u64(bin, vals[i], vals[j], &out1);
                unsigned char b2 = __builtin_ia32_sbb_u64(bin, vals[i], vals[j], &out2);
                if (b1 != b2 || out1 != out2) return 1;
            }
    return 0;
}


static unsigned ref_bext(unsigned x, unsigned c) {
    unsigned s = c & 0xff;
    unsigned l = (c >> 8) & 0xff;
    if (l == 0 || s >= 32) return 0;
    if (s + l > 32) l = 32 - s;
    return (x >> s) & ((1u << l) - 1);
}


int main(void) {
    unsigned long long t1 = f1();
    unsigned long long t2 = f1();
    ASSERT(t2 > t1, 1);
    unsigned long long e1 = f2();
    unsigned long long e2 = f2();
    ASSERT(e2 >= e1, 1);
    unsigned long long s1 = f3();
    unsigned long long s2 = f3();
    ASSERT(s2 >= s1, 1);
    unsigned int p1 = f6();
    ASSERT(0, p1);
    int x = 0x80000000;   // bit 31 set
    int y = 0x00000100;   // bit 8 set
    int z = 0x00000001;   // bit 0 set

    printf("%d\n", __builtin_ia32_bsrsi(x)); // expected 31
    ASSERT(31, __builtin_ia32_bsrsi(x));
    printf("%d\n", __builtin_ia32_bsrsi(y)); // expected 8
    ASSERT(8, __builtin_ia32_bsrsi(y));
    printf("%d\n", __builtin_ia32_bsrsi(z)); // expected 0
    ASSERT(0, __builtin_ia32_bsrsi(z));
    uint32_t aux1, aux2;
    uint64_t tsc1, tsc2;
    tsc1 = __builtin_ia32_rdtscp(&aux1);
    tsc2 = __builtin_ia32_rdtscp(&aux2);
    if (tsc2 <= tsc1) {
        printf("Warning: TSC did not increase\n");
    }
    printf("TSC1 = %lu, AUX1 = %u\n", tsc1, aux1);
    printf("TSC2 = %lu, AUX2 = %u\n", tsc2, aux2);

    static const unsigned vals[] = {
        0x00000000u,
        0x00000001u,
        0x7fffffffu,
        0x80000000u,
        0xffffffffu,
    };

    for (unsigned i = 0; i < sizeof(vals)/sizeof(vals[0]); i++) {
        for (unsigned j = 0; j < sizeof(vals)/sizeof(vals[0]); j++) {
            for (unsigned bin = 0; bin <= 1; bin++) {
                unsigned a = vals[i];
                unsigned b = vals[j];
                unsigned ref_bout, test_bout;

                unsigned ref = ref_sbb_u32(a, b, bin, &ref_bout);
                unsigned test = __builtin_ia32_sbb_u32(
                    bin, a, b, &test_bout);
                    printf("a=0x%08x b=0x%08x bin=%u => "
                           "ref=0x%08x bout=%u | "
                           "test=0x%08x bout=%u\n",
                           a, b, bin,
                           ref, ref_bout,
                           test, test_bout);
                           ASSERT(ref, test);

   
            }
        }
    }

    printf("PASS: __builtin_ia32_sbb_u32\n");
    int az = test_addcarryx();
    printf("%d\n", az);
    ASSERT(0, az);
    int bz = test_sbb_u64();
    printf("%d\n", bz);
    ASSERT(0, bz);
    for (int i = 0; i <= 16; i++) {
    unsigned short x = (i == 16) ? 0 : (1u << i);
    unsigned short r = __builtin_ia32_tzcnt_u16(x);
    unsigned short refx = (x == 0) ? 16 : i;
    if (r != refx) {
        printf("FAIL x=%04x got=%u ref=%u\n", x, r, refx);
        return 1;
    }
    ASSERT(refx, r);
    }
        unsigned tests[] = {
        0xdeadbeef, 0, 1, 8, 16, 31, 32
    };

    // for (int s = 0; s < 40; s++) {
    //     for (int l = 0; l < 40; l++) {
    //         unsigned cbextr = (l << 8) | s;
    //         unsigned rbextr = __builtin_ia32_bextr_u32(0xdeadbeef, cbextr);
    //         unsigned ebextr = ref_bext(0xdeadbeef, cbextr);
    //         if (rbextr != ebextr) {
    //             printf("FAIL s=%u l=%u got=%x exp=%x\n", s, l, rbextr, ebextr);
    //             return 1;
    //         }
    //     }
    // }
    printf("OK\n");
    return 0;
}
