#include "chibicc.h"
#define TYPE_C "type.c"

Type *ty_void = &(Type){TY_VOID, 1, 1};
Type *ty_bool = &(Type){TY_BOOL, 1, 1, true};

Type *ty_char = &(Type){TY_CHAR, 1, 1};
Type *ty_short = &(Type){TY_SHORT, 2, 2};
Type *ty_int = &(Type){TY_INT, 4, 4};
Type *ty_long = &(Type){TY_LONG, 8, 8};

Type *ty_uchar = &(Type){TY_CHAR, 1, 1, true};
Type *ty_ushort = &(Type){TY_SHORT, 2, 2, true};
Type *ty_uint = &(Type){TY_INT, 4, 4, true};
Type *ty_ulong = &(Type){TY_LONG, 8, 8, true};

Type *ty_float = &(Type){TY_FLOAT, 4, 4};
Type *ty_double = &(Type){TY_DOUBLE, 8, 8};
Type *ty_ldouble = &(Type){TY_LDOUBLE, 16, 16};
Type *ty_void_ptr = &(Type){TY_PTR, 8, 8, true};


static Type *new_type(TypeKind kind, int size, int align)
{
  Type *ty = calloc(1, sizeof(Type));
  if (ty == NULL)
    error("%s: %s:%d: error: in new_type ty is null!", TYPE_C, __FILE__, __LINE__);
  ty->kind = kind;
  ty->size = size;
  ty->align = align;
  return ty;
}

Type *new_qualified_type(Type *ty) {
  if (ty->origin)
    ty = ty->origin;

  Type *ret = calloc(1, sizeof(Type));
  *ret = *ty;
  ret->origin = ty;

  if (ty->size < 0) {
    ret->decl_next = ty->decl_next;
    ty->decl_next = ret;
  }
  return ret;
}

bool is_integer(Type *ty)
{
  TypeKind k = ty->kind;
  return k == TY_BOOL || k == TY_CHAR || k == TY_SHORT ||
         k == TY_INT || k == TY_LONG || k == TY_ENUM;
}

bool is_flonum(Type *ty)
{
  return ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE ||
         ty->kind == TY_LDOUBLE;
}


bool is_array(Type *ty) {
  return ty->kind == TY_ARRAY || ty->kind == TY_VLA;
}

bool is_bitfield(Node *node) {
  return node->kind == ND_MEMBER && node->member->is_bitfield;
}

// static bool is_bitfield2(Node *node, int *width) {
//   switch (node->kind) {
//   case ND_ASSIGN:
//     return is_bitfield2(node->lhs, width);
//   case ND_COMMA:
//     return is_bitfield2(node->rhs, width);
//   case ND_STMT_EXPR: {
//     Node *stmt = node->body;
//     while (stmt->next)
//       stmt = stmt->next;
//     if (stmt->kind == ND_EXPR_STMT)
//       return is_bitfield2(stmt->lhs, width);
//   }
//   case ND_MEMBER:
//     if (!node->member->is_bitfield)
//       return false;
//     *width = node->member->bit_width;
//     return true;
//   }
//   return false;
// }


int int_rank(Type *t) {
  switch (t->kind) {
    case TY_ENUM:
    case TY_BOOL:
    case TY_CHAR:
    case TY_SHORT:
      return 0;
    case TY_INT:
      return 1;
    case TY_LONG:
      return 2;
  }
  unreachable();
}

static void int_promotion(Node **node) {
  Type *ty = (*node)->ty;

  if (is_bitfield(*node)) {
    int int_width = ty_int->size * 8;
    int bit_width = (*node)->member->bit_width;

    if (bit_width == int_width && ty->is_unsigned) {
      *node = new_cast(*node, ty_uint);
    } else if (bit_width <= int_width) {
      *node = new_cast(*node, ty_int);
    } else {
      *node = new_cast(*node, ty);
    }
    return;
  }

  if (ty->size < ty_int->size) {
    *node = new_cast(*node, ty_int);
    return;
  }

  if (ty->size == ty_int->size && int_rank(ty) < int_rank(ty_int)) {
    if (ty->is_unsigned)
      *node = new_cast(*node, ty_uint);
    else
      *node = new_cast(*node, ty_int);
    return;
  }
}


bool is_numeric(Type *ty)
{
  return is_integer(ty) || is_flonum(ty);
}

bool is_compatible(Type *t1, Type *t2)
{
  if (t1 == t2)
    return true;

  if (t1->origin)
    return is_compatible(t1->origin, t2);

  if (t2->origin)
    return is_compatible(t1, t2->origin);

  if (t1->kind != t2->kind)
    return false;

  if ((t1->kind == TY_VLA && t2->kind == TY_VLA) ||
    (t1->kind == TY_VLA && t2->kind == TY_ARRAY) ||
    (t1->kind == TY_ARRAY && t2->kind == TY_VLA))
    return is_compatible(t1->base, t2->base);
  if(is_vector(t1) && is_vector(t2))
    return is_compatible(t1->base, t2->base);

  switch (t1->kind)
  {
  case TY_CHAR:
  case TY_SHORT:
  case TY_INT:
  case TY_LONG:
    return t1->is_unsigned == t2->is_unsigned;
  case TY_FLOAT:
  case TY_DOUBLE:
  case TY_LDOUBLE:
    return true;
  case TY_PTR:
    return is_compatible(t1->base, t2->base);
  case TY_FUNC:
  {
    if (!is_compatible(t1->return_ty, t2->return_ty))
      return false;
    if (t1->is_variadic != t2->is_variadic)
      return false;

    Type *p1 = t1->params;
    Type *p2 = t2->params;
    for (; p1 && p2; p1 = p1->next, p2 = p2->next)
      if (!is_compatible(p1, p2))
        return false;
    return p1 == NULL && p2 == NULL;
  }
  case TY_ARRAY:
    if (!is_compatible(t1->base, t2->base))
      return false;
    return t1->array_len < 0 && t2->array_len < 0 &&
           t1->array_len == t2->array_len;
  case TY_VECTOR:
    if (!is_compatible(t1->base, t2->base))
      return false;
    return t1->array_len < 0 && t2->array_len < 0 &&
           t1->array_len == t2->array_len;           
  }
  return false;
}

Type *copy_type(Type *ty)
{
  Type *ret = calloc(1, sizeof(Type));
  if (ret == NULL)
    error("%s: %s:%d: error: in copy_type ret is null!", TYPE_C, __FILE__, __LINE__);
  *ret = *ty;
  ret->origin = ty;
  return ret;
}

Type *pointer_to(Type *base)
{
  Type *ty = new_type(TY_PTR, 8, 8);
  ty->base = base;
  ty->is_pointer = true;
  ty->pointertype = base;
  ty->is_unsigned = true;
  ty->is_vector = base->is_vector;
  return ty;
}

Type *func_type(Type *return_ty)
{
  // The C spec disallows sizeof(<function type>), but
  // GCC allows that and the expression is evaluated to 1.
  Type *ty = new_type(TY_FUNC, 1, 1);
  ty->return_ty = return_ty;
  ty->is_constructor = false;
  ty->is_destructor = false;
  ty->destructor_priority = 0;
  ty->constructor_priority = 0;  
  return ty;
}

Type *array_of(Type *base, int len)
{
  if (!base)
  error("%s %d: in array_of : base is null", TYPE_C, __LINE__); 
  Type *ty = new_type(TY_ARRAY, base->size * len, base->align);
  ty->base = base;
  ty->array_len = len;  
  ty->has_vla = base->has_vla; 
  return ty;
}


Type *vector_of(Type *base, int len)
{
  if (!base)
    error("%s %d: in vector_of : base is null", TYPE_C, __LINE__); 
  Type *ty = new_type(TY_VECTOR, base->size * len, base->align);
  int total_size = base->size * len;
  ty->size = total_size;
  ty->base = base;
  ty->array_len = len;  
  ty->has_vla = base->has_vla; 
  ty->is_vector = true;
  return ty;
}


Type *vla_of(Type *base, Node *len)
{

  Type *ty = new_type(TY_VLA, 8, 8);
  ty->base = base;
  ty->vla_len = len;
  ty->has_vla = true;
  return ty;

}




Type *enum_type(void)
{
  return new_type(TY_ENUM, 4, 4);
}

Type *struct_type(void)
{
  return new_type(TY_STRUCT, 0, 1);
}

static Type *get_common_type(Type *ty1, Type *ty2)
{

  //======ISS-158 trying to fix issue with "parse.c: in struct_ref : not a struct nor a union" when in a macro definition we have (size_t)-1 ? NULL : (n) - 1
  //assuming that if one is void it returns the second type that could be void also or different type.
  if (!ty2)
    return ty1;

  if (ty1->base) {
    if (ty1->base->kind == TY_VOID)
      if (ty2->base)
        return pointer_to(ty2->base);  
    return pointer_to(ty1->base);
  }

  if (ty1->kind == TY_FUNC)
    return pointer_to(ty1);
  if (ty2->kind == TY_FUNC)
    return pointer_to(ty2);

  if (ty1->kind == TY_LDOUBLE || ty2->kind == TY_LDOUBLE)
    return ty_ldouble;
  if (ty1->kind == TY_DOUBLE || ty2->kind == TY_DOUBLE)
    return ty_double;
  if (ty1->kind == TY_FLOAT || ty2->kind == TY_FLOAT)
    return ty_float;

  if (ty1->size < 4)
    ty1 = ty_int;
  if (ty2->size < 4)
    ty2 = ty_int;

  if (ty1->size != ty2->size)
    return (ty1->size < ty2->size) ? ty2 : ty1;

  if (ty2->is_unsigned)
    return ty2;
  return ty1;
}

// For many binary operators, we implicitly promote operands so that
// both operands have the same type. Any integral type smaller than
// int is always promoted to int. If the type of one operand is larger
// than the other's (e.g. "long" vs. "int"), the smaller operand will
// be promoted to match with the other.
//
// This operation is called the "usual arithmetic conversion".
static void usual_arith_conv(Node **lhs, Node **rhs)
{
  Type *ty = get_common_type((*lhs)->ty, (*rhs)->ty);
  *lhs = new_cast(*lhs, ty);
  *rhs = new_cast(*rhs, ty);
  
}


bool is_vector(Type *ty) {
  return ty && ty->kind == TY_VECTOR;
}



void add_type(Node *node)
{
  if (!node || node->ty)
    return;

  add_type(node->lhs);
  add_type(node->rhs);
  add_type(node->cond);
  add_type(node->then);
  add_type(node->els);
  add_type(node->init);
  add_type(node->inc);

  for (Node *n = node->body; n; n = n->next)
    add_type(n);
  for (Node *n = node->args; n; n = n->next)
    add_type(n);

  switch (node->kind)
  {
  case ND_NUM:
    node->ty = ty_int;
    return;
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
    if (is_vector(node->lhs->ty) && is_vector(node->rhs->ty)) {
          node->ty = node->lhs->ty;
    } else {
        usual_arith_conv(&node->lhs, &node->rhs);
        node->ty = node->lhs->ty;
    }
    return;
  case ND_NEG:
  {
    Type *ty = get_common_type(ty_int, node->lhs->ty);
    node->lhs = new_cast(node->lhs, ty);
    node->ty = ty;
    return;
  }
  case ND_ASSIGN:
    if (node->lhs->ty->kind == TY_ARRAY)
      error_tok(node->lhs->tok, "%s %d: not an lvalue", TYPE_C, __LINE__);
    if (node->lhs->ty->kind != TY_STRUCT && node->lhs->ty->kind != TY_UNION)
      node->rhs = new_cast(node->rhs, node->lhs->ty);
    node->ty = node->lhs->ty;
    return;
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
    usual_arith_conv(&node->lhs, &node->rhs);
    node->ty = ty_int;
    return;
  case ND_ALLOC:
    add_type(node->lhs);  
  case ND_FUNCALL:
    node->ty = node->func_ty->return_ty;
    return;
  case ND_NOT:
  case ND_LOGOR:
  case ND_LOGAND:
    node->ty = ty_int;
    return;
  case ND_BITNOT:
  case ND_SHL:
  case ND_SHR:
    //node->ty = node->lhs->ty;  
    if (!is_integer(node->lhs->ty))
      error_tok(node->tok, "%s %d %d invalid operand ", TYPE_C, __LINE__, node->kind);
    int_promotion(&node->lhs);
    node->ty = node->lhs->ty;       
    return;
  case ND_VAR:
      if (!node->var) {
        error_tok(node->tok, "%s %d %d variable undefined ", TYPE_C, __LINE__, node->kind);
      }
  case ND_VLA_PTR:
    node->ty = node->var->ty;
    return;
  case ND_COND:
    //======ISS-154 trying to fix deferencing pointer issue when we have a macro that can return a pointer or null  (self) ? NULL
    //printf("======%d %d %s\n", node->then->ty->kind, node->els->ty->kind,  node->tok->loc);
    if (node->then->ty->kind == TY_VOID && node->els->ty->kind == TY_VOID)
    {
      node->ty = ty_void;
    }
    else
    {
      usual_arith_conv(&node->then, &node->els);
      node->ty = node->then->ty;
    }
    return;
  case ND_COMMA:
    node->ty = node->rhs->ty;
    return;
  case ND_MEMBER:
    node->ty = node->member->ty;
    return;
  case ND_ADDR:
  {
    Type *ty = node->lhs->ty;
  //from @fuhsnn add_type():Remove overaggressive array decaying
    node->ty = pointer_to(ty);
    return;
  }
  case ND_DEREF:
    if (!node->lhs->ty->base) {
      //ISS-163 trying to fix issue with pointer dereference
      if (node->lhs->ty)
        node->lhs->ty->base = node->lhs->ty;
      else
        error_tok(node->tok, "%s %d: invalid pointer dereference", TYPE_C, __LINE__);
    }
    //======ISS-154 trying to fix deferencing pointer issue when we have a macro that can return a pointer or null  (self) ? NULL      
    //printf("======%d %d %s\n", node->lhs->ty->base->kind, node->lhs->ty->kind, node->lhs->tok->loc);
    if (node->lhs->ty->base->kind == TY_VOID && node->lhs->ty->kind == TY_VOID)
      error_tok(node->tok, "%s %d : dereferencing a void pointer", TYPE_C, __LINE__);
    if (node->lhs->ty->base->kind == TY_VOID)
      node->lhs->ty->base = node->lhs->ty;
    node->ty = node->lhs->ty->base;
    return;
  case ND_STMT_EXPR:
    if (node->body)
    {
      Node *stmt = node->body;
      while (stmt->next) {
        stmt = stmt->next;
        add_type(stmt);
      }
      while (stmt->kind == ND_LABEL) {
        stmt = stmt->lhs;
        add_type(stmt);
      }
      if (stmt->kind == ND_EXPR_STMT)
      {
        node->ty = stmt->lhs->ty;
        return;
      }
    }
    //trying to fix =====ISS-144 compiling util-linux failed with expression returning void is not supported
    //error_tok(node->tok, "%s statement expression returning void is not supported", TYPE_C);
    return;
  case ND_LABEL_VAL:
    node->ty = pointer_to(ty_void);
    return;
  case ND_CAS:
    add_type(node->cas_addr);
    add_type(node->cas_old);
    add_type(node->cas_new);
    node->ty = ty_bool;

    if (node->cas_addr->ty->kind != TY_PTR)
      error_tok(node->cas_addr->tok, "%s %d: pointer expected", TYPE_C, __LINE__);
    if (node->cas_old->ty->kind != TY_PTR)
      error_tok(node->cas_old->tok, "%s %d: pointer expected", TYPE_C, __LINE__);
    return;
  case ND_CAS_N:
    add_type(node->cas_addr);
    add_type(node->cas_old);
    add_type(node->cas_new);
    node->ty = ty_bool;
    if (node->cas_addr->ty->kind != TY_PTR)
      error_tok(node->cas_addr->tok, "%s %d: pointer expected", TYPE_C, __LINE__);
    return;
  case ND_BUILTIN_MEMCPY:
    add_type(node->builtin_dest);
    add_type(node->builtin_src);
    add_type(node->builtin_size);
    return;
  case ND_BUILTIN_MEMSET:
    add_type(node->builtin_dest);
    add_type(node->builtin_val);
    add_type(node->builtin_size);
    return;
  case ND_PXOR:
  case ND_POR:
  case ND_PAND:
  case ND_PANDN:
  case ND_PSRLQ:
  case ND_PSRLQI:
  case ND_PSLLQI:
  case ND_PSLLQ:
  case ND_PSUBQ:
  case ND_PADDQ:
    node->ty = vector_of(ty_long, 1);
    return;
  case ND_PCMPGTD:
  case ND_PCMPEQD:
  case ND_PSRADI:
  case ND_PSRAD:
  case ND_PSLLDI:
  case ND_PSLLD:
  case ND_PSUBD:
  case ND_PADDD:
  case ND_PUNPCKLDQ:
  case ND_PUNPCKHDQ:
  case ND_VECINITV2SI:  
  case ND_CVTPS2PI:  
    node->ty = vector_of(ty_int, 2);
    return;
  case ND_CMPNEQPS:
  case ND_CMPGEPS:
  case ND_CMPGTPS:
  case ND_CMPLEPS:
  case ND_CMPLTPS:
  case ND_CMPEQPS:
  case ND_CMPUNORDSS:
  case ND_CMPORDSS:
  case ND_CMPNLESS:
  case ND_CMPNLTSS:
  case ND_CMPNEQSS:
  case ND_MOVSS:
  case ND_CMPLESS:
  case ND_CMPLTSS:
  case ND_CMPEQSS:
  case ND_XORPS:
  case ND_ORPS:
  case ND_ANDNPS:
  case ND_ANDPS:
  case ND_MAXPS:
  case ND_MINPS:
  case ND_RSQRTPS:
  case ND_RCPPS:
  case ND_SQRTPS:   
  case ND_MAXSS:
  case ND_MINSS:
  case ND_RSQRTSS:
  case ND_RCPSS:
  case ND_SQRTSS: 
  case ND_DIVSS:
  case ND_MULSS:
  case ND_SUBSS:
  case ND_ADDSS:
  case ND_CVTPI2PS:
    add_type(node->rhs);
    add_type(node->lhs);
    node->ty = vector_of(ty_float, 4);
    return;    
  case ND_EXPECT:
    add_type(node->rhs);
    add_type(node->lhs);
    node->ty = ty_bool;
    return;
  case ND_ABORT:
    return;
  case ND_STMXCSR:
    node->ty = ty_void_ptr;
    return;
  case ND_CLFLUSH:
  case ND_BUILTIN_FRAME_ADDRESS:
  case ND_RETURN_ADDR:
    add_type(node->lhs);
    node->ty = ty_void_ptr;
    return;
  case ND_BUILTIN_SUB_OVERFLOW:
  case ND_BUILTIN_MUL_OVERFLOW:
  case ND_BUILTIN_ADD_OVERFLOW:
    add_type(node->lhs);
    add_type(node->rhs);
    add_type(node->builtin_dest);
    node->ty = ty_bool;
    return;
  case ND_BUILTIN_ISNAN:
    add_type(node->builtin_val);
    node->ty = ty_bool;
    return;
  case ND_BUILTIN_CTZ:
  case ND_BUILTIN_CTZL:
  case ND_BUILTIN_CTZLL:
  case ND_BUILTIN_CLZ:
  case ND_BUILTIN_CLZL:
  case ND_BUILTIN_CLZLL:
  case ND_BUILTIN_BSWAP32:  
  case ND_POPCOUNT:
    add_type(node->builtin_val);
    node->ty = ty_int;
    return;
  case ND_BUILTIN_BSWAP16:
    add_type(node->builtin_val);
    node->ty = ty_short;
    return;   
  case ND_BUILTIN_BSWAP64:
    add_type(node->builtin_val);
    node->ty = ty_long;
    return;       
  case ND_EXCH_N:
  case ND_FETCHADD:
  case ND_FETCHSUB:
  case ND_FETCHXOR:
  case ND_FETCHAND:
  case ND_FETCHOR:
  case ND_SUBFETCH:
    if (node->lhs->ty->kind != TY_PTR)
      error_tok(node->lhs->tok, "pointer expected");
    node->rhs = new_cast(node->rhs, node->lhs->ty->base);
    node->ty = node->lhs->ty->base;
    return;
  case ND_EMMS:
  case ND_SFENCE:
  case ND_LFENCE:
  case ND_MFENCE:
  case ND_PAUSE:
  case ND_UNREACHABLE:
    node->ty = ty_void;
    return;
  case ND_EXCH:
    if (node->lhs->ty->kind != TY_PTR)
      error_tok(node->cas_addr->tok, "%s %d: pointer expected", TYPE_C, __LINE__);
    node->ty = node->lhs->ty->base;
    return;
  case ND_BUILTIN_NANF:  
  case ND_BUILTIN_INFF:
  case ND_BUILTIN_HUGE_VALF:
    node->ty = ty_float;
    return;
  case ND_BUILTIN_NAN:    
  case ND_BUILTIN_INF:
  case ND_BUILTIN_HUGE_VAL:
    node->ty = ty_double;
    return;    
  case ND_BUILTIN_NANL:  
  case ND_BUILTIN_HUGE_VALL:
    node->ty = ty_ldouble;
    return;      
  case ND_VECEXTV2SI:
    node->ty = ty_int;
    return;
  case ND_VECINITV4HI:
  case ND_PCMPGTW:
  case ND_PCMPEQW:
  case ND_PSRLDI:
  case ND_PSRLD:       
  case ND_PSRLWI:
  case ND_PSRLW:
  case ND_PSRAWI:
  case ND_PSRAW: 
  case ND_PSLLWI:
  case ND_PSLLW:
  case ND_PMULLW:
  case ND_PMULHW:
  case ND_PMADDWD:
  case ND_PSUBSW:
  case ND_PSUBW:
  case ND_PADDW:
  case ND_PADDSW:
  case ND_PADDUSW:
  case ND_PUNPCKLWD:
  case ND_PUNPCKHWD:    
  case ND_PACKSSDW:
    node->ty = vector_of(ty_short, 4);
    return;
  case ND_PCMPEQB:
  case ND_PSUBUSB:
  case ND_PACKUSWB:
  case ND_PADDUSB:
    node->ty = vector_of(ty_uchar, 8);
    return;  
  case ND_VECINITV8QI:    
  case ND_PCMPGTB:
  case ND_PSUBSB:
  case ND_PSUBB:
  case ND_PADDB:
  case ND_PADDSB:
  case ND_PUNPCKLBW:
  case ND_PUNPCKHBW:
  case ND_PACKSSWB:
    node->ty = vector_of(ty_char, 8);
    return;
  case ND_PSUBUSW:
    node->ty = vector_of(ty_ushort, 4);
    return;
  }
}