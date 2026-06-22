#include "test.h"

typedef float v8sf __attribute__((vector_size(32)));
typedef double v4df __attribute__((vector_size(32)));
typedef double v2df __attribute__((vector_size(16)));
typedef float v4sf __attribute__((vector_size(16)));

int main() {
  // dpps256: dot product with mask 0xF1 (low element per lane)
  v8sf a = {1,2,3,4,5,6,7,8};
  v8sf b = {1,1,1,1,1,1,1,1};
  v8sf r = __builtin_ia32_dpps256(a, b, 0xF1);
  ASSERT(10, (int)r[0]);
  ASSERT(0, (int)r[1]);
  ASSERT(0, (int)r[2]);
  ASSERT(0, (int)r[3]);
  ASSERT(26, (int)r[4]);
  ASSERT(0, (int)r[5]);
  ASSERT(0, (int)r[6]);
  ASSERT(0, (int)r[7]);

  // shufpd256: shuffle doubles within lanes (imm=0 → both lanes pick [0] from each)
  v4df c = {1.0, 2.0, 3.0, 4.0};
  v4df d = {5.0, 6.0, 7.0, 8.0};
  v4df s = __builtin_ia32_shufpd256(c, d, 0);
  ASSERT(1, (int)s[0]);
  ASSERT(5, (int)s[1]);
  ASSERT(3, (int)s[2]);
  ASSERT(7, (int)s[3]);

  // shufps256: shuffle floats within lanes (imm=0 → replicate [0] per lane)
  v8sf e = {1,2,3,4,5,6,7,8};
  v8sf f = {9,10,11,12,13,14,15,16};
  v8sf t = __builtin_ia32_shufps256(e, f, 0x00);
  ASSERT(1, (int)t[0]);
  ASSERT(1, (int)t[1]);
  ASSERT(9, (int)t[2]);
  ASSERT(9, (int)t[3]);
  ASSERT(5, (int)t[4]);
  ASSERT(5, (int)t[5]);
  ASSERT(13, (int)t[6]);
  ASSERT(13, (int)t[7]);

  // vextractf128_pd256: extract lower 128 bits
  v2df x = __builtin_ia32_vextractf128_pd256(c, 0);
  ASSERT(1, (int)x[0]);
  ASSERT(2, (int)x[1]);

  // vextractf128_ps256: extract lower 128 bits
  v4sf y = __builtin_ia32_vextractf128_ps256(e, 0);
  ASSERT(1, (int)y[0]);
  ASSERT(2, (int)y[1]);
  ASSERT(3, (int)y[2]);
  ASSERT(4, (int)y[3]);

  // vinsertf128_pd256: insert xmm into ymm(low half)
  v2df ins = {9.0, 10.0};
  v4df ins_r = __builtin_ia32_vinsertf128_pd256(c, ins, 0);
  ASSERT(9, (int)ins_r[0]);
  ASSERT(10, (int)ins_r[1]);
  ASSERT(3, (int)ins_r[2]);
  ASSERT(4, (int)ins_r[3]);

  // vperm2f128_pd256: permute 128-bit halves (lower=src1, upper=src2)
  v4df p = __builtin_ia32_vperm2f128_pd256(c, d, 0x20);
  ASSERT(1, (int)p[0]);
  ASSERT(2, (int)p[1]);
  ASSERT(5, (int)p[2]);
  ASSERT(6, (int)p[3]);

  // vpermilpd: identity (imm=0)
  v2df v = {1.0, 2.0};
  v2df w = __builtin_ia32_vpermilpd(v, 0);
  ASSERT(1, (int)w[0]);
  ASSERT(1, (int)w[1]);

  // vpermilps: replicate element 0 (imm=0x00)
  v4sf vs = {1,2,3,4};
  v4sf ws = __builtin_ia32_vpermilps(vs, 0x00);
  ASSERT(1, (int)ws[0]);
  ASSERT(1, (int)ws[1]);
  ASSERT(1, (int)ws[2]);
  ASSERT(1, (int)ws[3]);

  // vpermilpd256: identity per lane (imm=0)
  v4df vpd = {1.0, 2.0, 3.0, 4.0};
  v4df wpd = __builtin_ia32_vpermilpd256(vpd, 0);
  ASSERT(1, (int)wpd[0]);
  ASSERT(1, (int)wpd[1]);
  ASSERT(3, (int)wpd[2]);
  ASSERT(3, (int)wpd[3]);

  // vpermilps256: replicate element 0 per lane (imm=0x00)
  v8sf vps = {1,2,3,4,5,6,7,8};
  v8sf wps = __builtin_ia32_vpermilps256(vps, 0x00);
  ASSERT(1, (int)wps[0]);
  ASSERT(1, (int)wps[1]);
  ASSERT(1, (int)wps[2]);
  ASSERT(1, (int)wps[3]);
  ASSERT(5, (int)wps[4]);
  ASSERT(5, (int)wps[5]);
  ASSERT(5, (int)wps[6]);
  ASSERT(5, (int)wps[7]);

  // cmppd: compare packed doubles EQ_OQ (predicate 0)
  v2df ca = {1.0, 2.0};
  v2df cb = {1.0, 3.0};
  v2df cr = __builtin_ia32_cmppd(ca, cb, 0);
  ASSERT(-2147483648, cr[0]);
  ASSERT(0, cr[1]);

  // cmpps: compare packed floats EQ_OQ
  v4sf cca = {1,2,3,4};
  v4sf ccb = {1,2,5,6};
  v4sf ccr = __builtin_ia32_cmpps(cca, ccb, 0);
  ASSERT(-2147483648, ccr[0]);
  ASSERT(-2147483648, ccr[1]);
  ASSERT(0, ccr[2]);
  ASSERT(0, ccr[3]);

  // cmpsd: compare scalar double EQ_OQ
  v2df sca = {1.0, 2.0};
  v2df scb = {1.0, 3.0};
  v2df scr = __builtin_ia32_cmpsd(sca, scb, 0);
  ASSERT(-2147483648, scr[0]);
  ASSERT(2, scr[1]);

  // cmpss: compare scalar float EQ_OQ
  v4sf ssa = {1,2,3,4};
  v4sf ssb = {1,5,3,4};
  v4sf ssr = __builtin_ia32_cmpss(ssa, ssb, 0);
  ASSERT(-2147483648, ssr[0]);
  ASSERT(2, ssr[1]);
  ASSERT(3, ssr[2]);
  ASSERT(4, ssr[3]);

  // cmppd256: compare packed doubles 256 EQ_OQ
  v4df pda = {1.0, 2.0, 3.0, 4.0};
  v4df pdb = {1.0, 7.0, 3.0, 8.0};
  v4df pdr = __builtin_ia32_cmppd256(pda, pdb, 0);
  ASSERT(-2147483648, pdr[0]);
  ASSERT(0, pdr[1]);
  ASSERT(-2147483648, pdr[2]);
  ASSERT(0, pdr[3]);

  // cmpps256: compare packed floats 256 EQ_OQ
  v8sf psa = {1,2,3,4,5,6,7,8};
  v8sf psb = {1,2,9,4,5,10,7,8};
  v8sf psr = __builtin_ia32_cmpps256(psa, psb, 0);
  ASSERT(-2147483648, psr[0]);
  ASSERT(-2147483648, psr[1]);
  ASSERT(0, psr[2]);
  ASSERT(-2147483648, psr[3]);
  ASSERT(-2147483648, psr[4]);
  ASSERT(0, psr[5]);
  ASSERT(-2147483648, psr[6]);
  ASSERT(-2147483648, psr[7]);

  return 0;
}
