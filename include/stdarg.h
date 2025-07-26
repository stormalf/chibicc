#ifndef __STDARG_H
#define __STDARG_H

typedef struct {
  unsigned int gp_offset;
  unsigned int fp_offset;
  void *overflow_arg_area;
  void *reg_save_area;
} __va_elem;

typedef __va_elem va_list[1];
typedef unsigned long uintptr_t;
extern int printf(const char *fmt, ...);

#define va_start(ap, last) \
  do { *(ap) = *(__va_elem *)__va_area__; } while (0)

#define va_end(ap)

//for now alignment is not correctly managed by chibicc when we have variadic functions.
//we store into the stack by substracting directly the sz of the component (aligned to 8 or 16)
//but we need a more robust way to manage alignment and activate here the correct alignment. 
static void *__va_arg_mem(__va_elem *ap, int sz, int align) {  
  void *p = ap->overflow_arg_area;
  // if (align > 16) {
    
  //   p = (void *)(((uintptr_t)p + align - 1) & ~(align - 1));
  // }
  ap->overflow_arg_area = (void *)(((unsigned long)p + sz + 7) / 8 * 8);
  
  return p;
}


static void *__va_arg_gp(__va_elem *ap, int sz, int align) {  
  if (ap->gp_offset >= 48)
    return __va_arg_mem(ap, sz, align);

  void *r = ap->reg_save_area + ap->gp_offset;
  ap->gp_offset += 8;
  return r;
}

static void *__va_arg_fp(__va_elem *ap, int sz, int align) {
  if (ap->fp_offset >= 176)
    return __va_arg_mem(ap, sz, align);

  void *r = ap->reg_save_area + ap->fp_offset;
  ap->fp_offset += 16;
  return r;
}

#define va_arg(ap, ty)                                                  \
  ({                                                                    \
    int klass = __builtin_reg_class(ty);                                \
    *(ty *)(klass == 0 ? __va_arg_gp(ap, sizeof(ty), _Alignof(ty)) :    \
            klass == 1 ? __va_arg_fp(ap, sizeof(ty), _Alignof(ty)) :    \
            __va_arg_mem(ap, sizeof(ty), _Alignof(ty)));                \
  })

#define va_copy(dest, src) ((dest)[0] = (src)[0])

#define __GNUC_VA_LIST 1
typedef va_list __gnuc_va_list;

#endif