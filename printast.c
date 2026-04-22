/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "chibicc.h"

#define HASH_TABLE_SIZE 256


// Simple hash table entry
typedef struct HashTableEntry {
    Type *type;
    struct HashTableEntry *next;
} HashTableEntry;

// Simple hash table
HashTableEntry *hashTable[HASH_TABLE_SIZE];

// Hash function for Type pointer
unsigned int hash(Type *ty) {
    return ((unsigned long)ty) % HASH_TABLE_SIZE;
}

// Insert Type into hash table
bool insertType(Type *ty) {
    unsigned int index = hash(ty);
    HashTableEntry *entry = hashTable[index];

    while (entry) {
        if (entry->type == ty) {
            return false; // Type already exists, cycle detected
        }
        entry = entry->next;
    }

    // Insert new entry
    HashTableEntry *newEntry = malloc(sizeof(HashTableEntry));
    newEntry->type = ty;
    newEntry->next = hashTable[index];
    hashTable[index] = newEntry;
    return true;
}

static const char kBoolStr[2][6] = {"false", "true"};

static const char kTypeKindStr[17][8] = {
    "VOID",   "BOOL",  "CHAR",   "SHORT",   "INT",   "LONG",
    "INT128", "FLOAT", "DOUBLE", "LDOUBLE", "ENUM",  "PTR",
    "FUNC",   "ARRAY", "VLA",    "STRUCT",  "UNION",
};


static const char kNodeKindStr[537][21] = {
    "NULL_EXPR", "ADD", "SUB", "MUL", "DIV", "NEG", "MOD", "BITAND",  "BITOR", "BITXOR", "SHL", "SHR", "EQ", "NE",
    "LT", "LE", "ASSIGN", "COND", "COMMA", "MEMBER", "ADDR", "DEREF", "NOT", "BITNOT", "LOGAND", "LOGOR", "RETURN",
    "IF", "FOR", "DO", "SWITCH", "CASE", "BLOCK", "GOTO", "GOTO_EXPR", "LABEL", "LABEL_VAL",  "FUNCALL", "EXPR_STMT", "STMT_EXPR", "VAR", "VLA_PTR", "NUM", "CAST", "MEMZERO",
    "ASM", "CAS", "EXCH", "CAS_N", "EXCH_N", "CMPEXCH", "CMPEXCH_N", "LOAD", "LOAD_N", "STORE", "STORE_N", "TESTANDSET", "TESTANDSETA", "CLEAR", "RELEASE", "FETCHADD", "FETCHSUB", "FETCHXOR", "FETCHAND",  
    "FETCHOR", "SUBFETCH", "SYNC", "MEMBARRIER", "BUILTIN_MEMCPY",  "BUILTIN_MEMSET", "BUILTIN_CLZ", "BUILTIN_CLZL", "BUILTIN_CLZLL", "BUILTIN_CTZ", "BUILTIN_CTZL", "BUILTIN_CTZLL", "POPCOUNT",    
    "EXPECT", "ABORT", "RETURN_ADDR", "BUILTIN_ADD_OVERFLOW", "BUILTIN_SUB_OVERFLOW",  "BUILTIN_MUL_OVERFLOW", "UNREACHABLE", "ALLOCA", "BUILTIN_INFF", 
    "BUILTIN_INF", "BUILTIN_NAN", "BUILTIN_NANF", "BUILTIN_NANL", "BUILTIN_ISNAN", "BUILTIN_HUGE_VALL", "BUILTIN_HUGE_VALF", "BUILTIN_HUGE_VAL",
    "BSWAP16", "BSWAP32", "BSWAP64", "FRAME_ADDRESS", "EMMS", "SFENCE", "LFENCE", "MFENCE", "PAUSE", "STMXCSR", "CVTPI2PS", "CVTPS2PI", "CLFLUSH", 
    "VEC_INIT_V2SI", "VEC_EXT_V2SI", "PACKSSWB", "PACKSSDW", "PACKUSWB", "PUNPCKHBW", "PUNPCKHWD", "PUNPCKHDQ", "PUNPCKLBW", "PUNPCKLWD", "PUNPCKLDQ",
    "PADDB", "PADDW", "PADDD", "PADDQ", "PADDSB", "PADDSW", "PADDUSB", "PADDUSW", "PSUBB", "PSUBW", "PSUBD", "PSUBQ", "PSUBSB", "PSUBSW", "PSUBUSB", "PSUBUSW", 
    "PMADDWD", "PMULHW", "PMULLW", "PSLLW", "PSLLWI", "PSLLD", "PSLLDI", "PSLLQ", "PSLLQI", "PSRAW", "PSRAWI", "PSRAD", "PSRADI", "PSRLW", "PSRLWI", "PSRLD", 
    "PSRLDI", "PSRLQ", "PSRLQI", "PAND", "PANDN", "POR", "PXOR", "PCMPEQB", "PCMPGTB", "PCMPEQW", "PCMPEQD", "PCMPGTW", "PCMPGTD", "VEC_INIT_V4HI", "VEC_INIT_V8QI",
    "ADDSS", "SUBSS", "MULSS", "DIVSS", "SQRTSS", "RCPSS", "RSQRTSS", "SQRTPS", "MINSS", "MAXSS", "RCPPS", "RSQRTPS", "MINPS", "MAXPS", "ANDPS", "ANDNPS", 
    "ORPS", "XORPS", "CMPEQSS", "CMPLTSS", "CMPLESS", "MOVSS", "CMPNEQSS", "CMPNLTSS", "CMPNLESS", "CMPORDSS", "CMPUNORDSS", "CMPEQPS", "CMPLTPS", "CMPLEPS",
    "CMPGTPS", "CMPGEPS", "CMPNEQPS", "CMPNLTPS", "CMPNLEPS", "CMPNGTPS", "CMPNGEPS", "CMPORDPS", "CMPUNORDPS", "COMIEQ", "COMILT", "COMILE", "COMIGT", "COMIGE",
    "COMINEQ", "UCOMIEQ", "UCOMILT", "UCOMILE", "UCOMIGT", "UCOMIGE", "UCOMINEQ", "CVTSS2SI", "CVTSS2SI64", "CVTTSS2SI", "CVTTSS2SI64", "CVTTPS2PI", "CVTSI2SS", 
    "CVTSI642SS", "MOVLHPS", "MOVHLPS", "UNPCKHPS", "UNPCKLPS", "LOADHPS", "STOREHPS", "LOADLPS", "STORELPS", "MOVMSKPS", "LDMXCSR", "SHUFPS", "SHUFFLE", "PMAXSW",
    "PMAXUB", "PMINSW", "PMINUB", "PMOVMSKB", "PMULHUW", "MASKMOVQ", "PAVGB", "PAVGW", "PSADBW", "MOVNTQ", "MOVNTPS", "SHUFPD", "VEC_EXT_V4SI", "ADDSD", "SUBSD", 
    "MULSD", "DIVSD", "SQRTPD", "MOVSD", "SQRTSD", "MINPD", "MINSD", "MAXPD", "MAXSD", "ANDPD", "ANDNPD", "ORPD", "XORPD", "CMPEQPD", "CMPLTPD", "CMPLEPD", 
    "CMPGTPD", "CMPGEPD", "CMPNEQPD", "CMPNLTPD", "CMPNLEPD", "CMPNGTPD", "CMPNGEPD", "CMPORDPD", "CMPUNORDPD", "CMPEQSD", "CMPLTSD", "CMPLESD", "CMPNEQSD", 
    "CMPNLTSD", "CMPNLESD", "CMPORDSD", "CMPUNORDSD", "COMISDEQ", "COMISDLT", "COMISDLE", "COMISDGT", "COMISDGE", "COMISDNEQ", "UCOMISDEQ", "UCOMISDLT", 
    "UCOMISDLE", "UCOMISDGT", "UCOMISDGE", "UCOMISDNEQ", "MOVQ128", "CVTDQ2PD", "CVTDQ2PS", "CVTPD2DQ", "CVTPD2PI", "CVTPD2PS", "CVTTPD2DQ", "CVTTPD2PI", 
    "CVTPI2PD","CVTPS2DQ", "CVTTPS2DQ", "CVTPS2PD", "CVTSD2SI", "CVTSD2SI64", "CVTTSD2SI", "CVTTSD2SI64", "CVTSD2SS", "CVTSI2SD", "CVTSI642SD", "CVTSS2SD", 
    "UNPCKHPD", "UNPCKLPD", "LOADHPD", "LOADLPD", "MOVMSKPD", "PACKSSWB128", "PACKSSDW128", "PACKUSWB128", "PUNPCKHB128", "PUNPCKHWD128",
    "PUNPCKHDQ128", "PUNPCKHQDQ128", "PUNPCKLBW128", "PUNPCKLWD128", "PUNPCKLDQ128", "PUNPCKLQDQ128", "PADDSB128", "PADDSW128", "PADDUSB128", "PADDUSW128", 
    "PSUBSB128", "PSUBSW128", "PSUBUSB128", "PSUBUSW128", "PMADDWD128", "PMULHW128", "PMULUDQ", "PMULUDQ128", "PSLLWI128", "PSLLDI128", "PSLLQI128", "PSRAWI128",
    "PSRADI128", "PSRLWI128", "PSRLDI128", "PSRLQI128", "PSLLW128", "PSLLD128", "PSLLQ128", "PSRAW128", "PSRAD128", "PSRLW128", "PSRLD128", "PSRLQ128", 
    "PANDN128", "PMAXSW128", "PMAXUB128", "PMINSW128", "PMINUB128", "PMOVMSKB128", "PMULHUW128", "MASKMOVDQU", "PAVGB128", "PAVGW128", "PSADBW128", "MOVNTI", 
    "MOVNTI64", "MOVNTDQ", "MOVNTPD", "POPCOUNTL", "POPCOUNTLL", "PARITY", "PARITYL", "PARITYLL", "UADD_OVERFLOW", "UADDL_OVERFLOW", "UADDLL_OVERFLOW", 
    "UMUL_OVERFLOW", "UMULL_OVERFLOW", "UMULLL_OVERFLOW", "POS", "MWAIT", "MONITOR", "ADDSUBPS", "HADDPS", "HSUBPS", "MOVSHDUP", "MOVSLDUP", "ADDSUBPD", 
    "HADDPD", "HSUBPD", "LDDQU", "PHADDW128", "PHADDD128", "PHADDSW128", "PHADDW", "PHADDD", "PHADDSW", "PHSUBW128", "PHSUBD128", "PHSUBSW128", "PHSUBW", "PHSUBD", 
    "PHSUBSW", "PMADDUBSW128", "PMADDUBSW", "PMULHRSW128", "PMULHRSW", "PSHUFB128", "PSHUFB", "PSIGNB128", "PSIGNW128", "PSIGND128", "PSIGNB", "PSIGNW",  
    "PSIGND", "PABSB128", "PABSW128", "PABSD128",  "PABSB", "PABSW", "PABSD", "PTESTZ128", "PTESTC128", "PTESTNZC128", "PBLENDVB128", "BLENDVPS", "BLENDVPD", 
    "PMINSB128", "PMAXSB128", "PMINUW128", "PMAXUW128", "PMINSD128", "PMAXSD128", "PMINUD128", "PMAXUD128", "PMULDQ128", "PHMINPOSUW128",
    "PMOVSXBD128", "PMOVSXWD128", "PMOVSXBQ128", "PMOVSXDQ128", "PMOVSXWQ128", "PMOVSXBW128",  "PMOVZXBD128", "PMOVZXWD128", "PMOVZXBQ128", "PMOVZXBW128",
    "PMOVZXDQ128", "PMOVZXWQ128",  "PACKUSDW128", "MOVNTDQA", "CRC32QI", "CRC32HI", "CRC32SI", "CRC32DI", "PSHUFD", "FETCHNAND", "ADD_AND_FETCH", "SUB_AND_FETCH",
    "BOOL_CAS", "PREFETCH", "RDTSC", "READEFLAGS_U64", "RDSSPQ", "SAVEPREVSSP", "SETSSBSY", "SLWPCB", "RDPKRU", "XBEGIN", "XEND", "SERIALIZE", "XSUSLDTRK", 
    "XRESLDTRK", "CLUI", "STUI", "TESTUI", "WBNOINVD", "XTEST", "WBINVD", "RDPID", "RDFSBASE32", "RDFSBASE64", "RDGSBASE32", "RDGSBASE64",
    "VZEROALL", "VZEROUPPER", "FEMMS", "BSRSI", "RDPMC", "RDTSCP", "ROLQI", "ROLHI", "RORQI", "RORHI", "BSRDI", "WRITEEFLAGS_U64", "INCSSPQ", "RSTORSSP",
    "WRSSD", "WRSSQ", "WRUSSD", "WRUSSQ", "CLRSSBSY", "SBB_U32", "ADDCARRYX_U32", "SBB_U64", "ADDCARRYX_U64", "TZCNT_U16", "BEXTR_U32", "ADDFETCH", "ORFETCH", "ANDFETCH",
    "XORFETCH", "NANDFETCH", "FPCLASSIFY", "ISUNORDERED", "SIGNBIT", "SIGNBITF", "SIGNBITL", "ATOMIC_IS_LOCK_FREE", "PSUBUSB256", "PCMPGTB256_MASK",
    "PSHUFB256", "PBLENDVB256", "PSRLDQI256", "PSLLDQI256", "VINSERTF128_SI256", "SI256_SI", "SI_SI256", "PALIGNR256"
};


static struct Visited {
  size_t i, n;
  intptr_t *p;
} g_visited;

static void PrintObj(FILE *, int, const char *, Obj *);
static void PrintNode(FILE *, int, const char *, Node *);
static void PrintType(FILE *, int, const char *, Type *);
static void PrintFpClassify(FILE *, int, const char *, FpClassify *);
static void PrintInitializer(FILE *, int, const char *, Initializer *);
static void PrintAsm(FILE *f, int l, const char *s, char *a);


static bool Visit(void *ptr) {
  intptr_t addr = (intptr_t)ptr;

  for (size_t i = 0; i < g_visited.i; ++i) {
    if (addr == g_visited.p[i]) {
      return false;
    }
  }

  if (g_visited.i == g_visited.n) {
    size_t new_n = g_visited.n ? g_visited.n * 2 : 64;
    intptr_t *new_p = realloc(g_visited.p, new_n * sizeof(intptr_t));
    if (!new_p) {
      return true;
    }
    g_visited.p = new_p;
    g_visited.n = new_n;
  }

  /* Append */
  g_visited.p[g_visited.i++] = addr;
  return true;
}

static void PrintLine(FILE *f, int l, char *fmt, ...) {
  int i;
  va_list ap;
  for (i = 0; i < l; ++i) fputc(' ', f);
  va_start(ap, fmt);
  vfprintf(f, fmt, ap);
  va_end(ap);
  fputc('\n', f);
}

static void PrintBool(FILE *f, int l, const char *s, bool b) {
  if (!b) return;
  PrintLine(f, l, "%s%s", s, kBoolStr[b]);
}

static void PrintInt(FILE *f, int l, const char *s, long x) {
  if (!x) return;
  PrintLine(f, l, "%s%ld", s, x);
}


static void PrintStr(FILE *f, int l, const char *s, const char *t) {
  if (!t || !*t) return;
  PrintLine(f, l, "%s%s", s, t);
}


static void PrintTokStr(FILE *f, int l, const char *s, Token *t) {
  if (!t) return;
  PrintLine(f, l, "%s%.*s", s, (int)t->len, t->loc);
}

static void PrintMember(FILE *f, int l, const char *s, Member *m) {
  if (!m) return;
  PrintLine(f, l, "%sMember { # %p", s, m);
  PrintTokStr(f, l + 2, "name: ", m->name);
  PrintInt(f, l + 2, "idx: ", m->idx);
  PrintInt(f, l + 2, "align: ", m->align);
  PrintInt(f, l + 2, "offset: ", m->offset);
  PrintBool(f, l + 2, "is_bitfield: ", m->is_bitfield);
  PrintInt(f, l + 2, "bit_offset: ", m->bit_offset);
  PrintInt(f, l + 2, "bit_width: ", m->bit_width);
  PrintType(f, l + 2, "ty: ", m->ty);
  PrintLine(f, l, "}");
}

static void PrintMembers(FILE *f, int l, const char *s, Member *m) {
  for (; m; m = m->next) {
    PrintMember(f, l, s, m);
  }
}

static void PrintType(FILE *f, int l, const char *s, Type *t) {
  for (; t; t = t->next) {
    if (!insertType(t)) {
        //printf("Detected cycle at address: %p\n", (void *)t);
        break; // Exit to avoid infinite loop
    }
 
    if (Visit(t)) {
      PrintLine(f, l, "%sType { # %p", s, t);
      PrintLine(f, l + 2, "kind: TY_%s", kTypeKindStr[t->kind]);
      PrintInt(f, l + 2, "size: ", t->size);
      PrintInt(f, l + 2, "align: ", t->align);
      PrintBool(f, l + 2, "is_unsigned: ", t->is_unsigned);
      PrintBool(f, l + 2, "is_atomic: ", t->is_atomic);
      PrintType(f, l + 2, "base: ", t->base);
      PrintTokStr(f, l + 2, "name: ", t->name);
      PrintTokStr(f, l + 2, "name_pos: ", t->name_pos);
      PrintInt(f, l + 2, "array_len: ", t->array_len);
      PrintInt(f, l + 2, "vector_size: ", t->vector_size);
      PrintNode(f, l + 2, "vla_len: ", t->vla_len);
      PrintObj(f, l + 2, "vla_size: ", t->vla_size);
      PrintMembers(f, l + 2, "members: ", t->members);
      PrintBool(f, l + 2, "is_flexible: ", t->is_flexible);
      PrintBool(f, l + 2, "is_packed: ", t->is_packed);
      PrintBool(f, l + 2, "is_aligned: ", t->is_aligned);
      PrintBool(f, l + 2, "is_const: ", t->is_const);
      PrintBool(f, l + 2, "is_restrict: ", t->is_restrict);
      PrintBool(f, l + 2, "is_volatile: ", t->is_volatile);
      PrintBool(f, l + 2, "is_static: ", t->is_static);
      PrintBool(f, l + 2, "is_ms_abi: ", t->is_ms_abi);
      PrintBool(f, l + 2, "is_pointer: ", t->is_pointer);
      PrintBool(f, l + 2, "has_vla: ", t->has_vla);
      PrintBool(f, l + 2, "is_weak: ", t->is_weak);
      PrintBool(f, l + 2, "is_inline: ", t->is_inline);
      PrintBool(f, l + 2, "is_compound_lit: ", t->is_compound_lit);
      PrintBool(f, l + 2, "is_vector: ", t->is_vector);
      PrintBool(f, l + 2, "is_constructor: ", t->is_constructor);
      PrintInt(f, l + 2, "constructor_priority: ", t->constructor_priority);
      PrintBool(f, l + 2, "is_destructor: ", t->is_destructor);
      PrintInt(f, l + 2, "destructor_priority: ", t->destructor_priority);
      PrintStr(f, l + 2, "visibility: ", t->visibility);
      PrintStr(f, l + 2, "alias_name: ", t->alias_name);
      PrintStr(f, l + 2, "section: ", t->section);
      PrintType(f, l + 2, "return_ty: ", t->return_ty);
      PrintType(f, l + 2, "params: ", t->params);
      PrintBool(f, l + 2, "is_variadic: ", t->is_variadic);
      PrintType(f, l + 2, "pointertype: ", t->pointertype);
      PrintType(f, l + 2, "origin: ", t->origin);
      PrintType(f, l + 2, "decl_next: ", t->decl_next);
      PrintInt(f, l + 2, "min_vector_width: ", t->min_vector_width);
      PrintLine(f, l, "}");
    } else if (t->name) {
      PrintLine(f, l, "%sTY_%s %.*s # %p", s, kTypeKindStr[t->kind],
                t->name->len, t->name->loc, t);
    } else {
      PrintLine(f, l, "%sTY_%s # %p", s, kTypeKindStr[t->kind], t);
    }
  }
}

static void PrintAsm(FILE *f, int l, const char *s, char * a) {
if (!a) return;
  PrintLine(f, l, "%sAsm { # %p", s, a);
  PrintStr(f, l + 2, "str: ", a);
}

static void PrintFpClassify(FILE *f, int l, const char *s, FpClassify *fpc) {
  if (!fpc) return;
  PrintLine(f, l, "%sFpClassify { # %p", s, fpc);
  PrintNode(f, l + 2, "node: ", fpc->node);
  for (int i = 0; i < 5; ++i) {
    PrintInt(f, l + 2, "arg: ", fpc->args[i]);
  }
  PrintLine(f, l, "}");
}

static void PrintInitializer(FILE *f, int l, const char *s, Initializer *init) {
  if (!init) return;
  PrintLine(f, l, "%sInitializer { # %p", s, init);
  PrintType(f, l + 2, "ty: ", init->ty);
  PrintTokStr(f, l + 2, "tok: ", init->tok);
  PrintBool(f, l + 2, "is_flexible: ", init->is_flexible);
  PrintNode(f, l + 2, "expr: ", init->expr);
  if (init->children && init->ty) {
     int len = 0;
     if (init->ty->kind == TY_ARRAY || init->ty->kind == TY_VECTOR) len = init->ty->array_len;
     else if (init->ty->kind == TY_STRUCT || init->ty->kind == TY_UNION) {
        for (Member *m = init->ty->members; m; m = m->next) len++;
     }
     for (int i = 0; i < len; ++i) {
        if (init->children[i])
            PrintInitializer(f, l + 2, "child: ", init->children[i]);
     }
  }
  PrintMember(f, l + 2, "mem: ", init->mem);
  PrintLine(f, l, "}");
  if (init->next) PrintInitializer(f, l, "next: ", init->next);
}

static void PrintNode(FILE *f, int l, const char *s, Node *n) {
    for (; n; n = n->next) {
    if (!Visit(n)) {
      /* already printed this node; print a short marker and continue */
      PrintLine(f, l, "%sNode # %p (already visited)", s, n);
      continue;
    }

    const char *kindstr = "UNKNOWN";
    if (n->kind >= 0 && n->kind < (int)(sizeof(kNodeKindStr)/sizeof(kNodeKindStr[0])))
      kindstr = kNodeKindStr[n->kind];

    PrintLine(f, l, "%sNode { # %p", s, n);
    PrintLine(f, l + 2, "kind: ND_%s", kindstr);
    PrintLine(f, l + 2, "kind: ND_%s", kNodeKindStr[n->kind]);
    PrintType(f, l + 2, "ty: ", n->ty);
    if (n->lhs) PrintNode(f, l + 2, "lhs: ", n->lhs);
    if (n->rhs) PrintNode(f, l + 2, "rhs: ", n->rhs);
    if (n->cond) PrintNode(f, l + 2, "cond: ", n->cond);
    if (n->then) PrintNode(f, l + 2, "then: ", n->then);
    if (n->els) PrintNode(f, l + 2, "els: ", n->els);
    if (n->init) PrintNode(f, l + 2, "init: ", n->init);
    if (n->inc) PrintNode(f, l + 2, "inc: ", n->inc);
    if (n->body) PrintNode(f, l + 2, "body: ", n->body);
    if (n->case_next) PrintNode(f, l + 2, "case_next: ", n->case_next);
    if (n->default_case) PrintNode(f, l + 2, "default_case: ", n->default_case);
    PrintType(f, l + 2, "func_ty: ", n->func_ty);
    PrintNode(f, l + 2, "args: ", n->args);
    PrintObj(f, l + 2, "ret_buffer: ", n->ret_buffer);
    PrintBool(f, l + 2, "pass_by_stack: ", n->pass_by_stack);
    PrintBool(f, l + 2, "realign_stack: ", n->realign_stack);
    if (n->label) PrintStr(f, l + 2, "label: ", n->label);
    if (n->unique_label) PrintStr(f, l + 2, "unique_label: ", n->unique_label);
    if (n->goto_next) PrintNode(f, l + 2, "goto_next: ", n->goto_next);
    if (n->brk_label) PrintStr(f, l + 2, "brk_label: ", n->brk_label);
    if (n->cont_label) PrintStr(f, l + 2, "cont_label: ", n->cont_label);
    PrintInt(f, l + 2, "begin: ", n->begin);
    if (n->asm_str) PrintAsm(f, l + 2, "asm: ", n->asm_str);
    PrintInt(f, l + 2, "end: ", n->end);
    if (n->member) PrintMember(f, l + 2, "member: ", n->member);
    PrintObj(f, l + 2, "var: ", n->var);
    PrintInt(f, l + 2, "val: ", n->val);
    PrintInt(f, l + 2, "memorder: ", n->memorder);
    if (n->cas_addr) PrintNode(f, l + 2, "cas_addr: ", n->cas_addr);
    if (n->cas_old) PrintNode(f, l + 2, "cas_old: ", n->cas_old);
    if (n->cas_new) PrintNode(f, l + 2, "cas_new: ", n->cas_new);
    if (n->cas_ptr) PrintNode(f, l + 2, "cas_ptr: ", n->cas_ptr);
    if (n->cas_expected) PrintNode(f, l + 2, "cas_expected: ", n->cas_expected);
    if (n->cas_desired) PrintNode(f, l + 2, "cas_desired: ", n->cas_desired);
    if (n->cas_weak) PrintNode(f, l + 2, "cas_weak: ", n->cas_weak);
    if (n->cas_success) PrintNode(f, l + 2, "cas_success: ", n->cas_success);
    if (n->cas_failure) PrintNode(f, l + 2, "cas_failure: ", n->cas_failure);
    if (n->builtin_dest) PrintNode(f, l + 2, "builtin_dest: ", n->builtin_dest);
    if (n->builtin_src) PrintNode(f, l + 2, "builtin_src: ", n->builtin_src);
    if (n->builtin_size) PrintNode(f, l + 2, "builtin_size: ", n->builtin_size);
    if (n->atomic_expr) PrintNode(f, l + 2, "atomic_expr: ", n->atomic_expr);
    if (n->atomic_addr) PrintObj(f, l + 2, "atomic_addr: ", n->atomic_addr);
    PrintBool(f, l + 2, "atomic_fetch: ", n->atomic_fetch);
    if (n->builtin_val) PrintNode(f, l + 2, "builtin_val: ", n->builtin_val);
    for (int i = 0; i < n->builtin_nargs; i++) {
        PrintNode(f, l + 2, "builtin_arg: ", n->builtin_args[i]);
    }
    PrintInt(f, l + 2, "builtin_nargs: ", n->builtin_nargs);
    if (n->fpc) PrintFpClassify(f, l + 2, "fpc: ", n->fpc);
    PrintBool(f, l + 2, "is_tail: ", n->is_tail);
    PrintBool(f, l + 2, "is_scalar_promoted: ", n->is_scalar_promoted);
    if (n->fval) PrintLine(f, l + 2, "fval: %Lf", n->fval);
    PrintLine(f, l, "}");
  }
}

static void PrintRelo(FILE *f, int l, const char *s, Relocation *r) {
  for (; r; r = r->next) {
    PrintLine(f, l, "%sRelocation { # %p", s, r);
    PrintInt(f, l + 2, "offset: ", r->offset);
    if (r->label) PrintStr(f, l + 2, "label: ", *r->label);
    PrintInt(f, l + 2, "addend: ", r->addend);
    PrintLine(f, l, "}");
  }
}

static void PrintObj(FILE *f, int l, const char *s, Obj *o) {
  if (!o) return;
  PrintLine(f, l, "%sObj { # %p", s, o);
  PrintStr(f, l + 2, "name: ", o->name);
  if (o->funcname) PrintStr(f, l + 2, "funcname: ", o->funcname);
  if (o->alias_name) PrintStr(f, l + 2, "alias_name: ", o->alias_name);
  PrintType(f, l + 2, "ty: ", o->ty);
  PrintBool(f, l + 2, "is_local: ", o->is_local);
  PrintBool(f, l + 2, "is_compound_lit: ", o->is_compound_lit);
  PrintInt(f, l + 2, "align: ", o->align);
  PrintInt(f, l + 2, "offset: ", o->offset);
  PrintInt(f, l + 2, "order: ", o->order);
  PrintInt(f, l + 2, "nbparm: ", o->nbparm);
  PrintBool(f, l + 2, "is_function: ", o->is_function);
  PrintBool(f, l + 2, "is_definition: ", o->is_definition);
  PrintBool(f, l + 2, "is_static: ", o->is_static);
  PrintBool(f, l + 2, "is_weak: ", o->is_weak);
  PrintBool(f, l + 2, "is_extern: ", o->is_extern);
  PrintBool(f, l + 2, "is_externally_visible: ", o->is_externally_visible);
  if (o->asmname) PrintStr(f, l + 2, "asmname: ", o->asmname);
  if (o->section) PrintStr(f, l + 2, "section: ", o->section);
  if (o->visibility) PrintStr(f, l + 2, "visibility: ", o->visibility);
  PrintBool(f, l + 2, "is_tentative: ", o->is_tentative);
  //PrintBool(f, l + 2, "is_string_literal: ", o->is_string_literal);
  PrintBool(f, l + 2, "is_tls: ", o->is_tls);
  if (o->init_data) PrintStr(f, l + 2, "init_data: ", o->init_data);
  PrintRelo(f, l + 2, "rel: ", o->rel);
  PrintBool(f, l + 2, "is_inline: ", o->is_inline);
  PrintBool(f, l + 2, "is_aligned: ", o->is_aligned);
  PrintBool(f, l + 2, "is_noreturn: ", o->is_noreturn);
  PrintBool(f, l + 2, "is_destructor: ", o->is_destructor);
  PrintInt(f, l + 2, "destructor_priority: ", o->destructor_priority);
  PrintBool(f, l + 2, "is_constructor: ", o->is_constructor);
  PrintInt(f, l + 2, "constructor_priority: ", o->constructor_priority);
  PrintBool(f, l + 2, "is_externally_visible: ", o->is_externally_visible);
  PrintBool(f, l + 2,
            "is_no_instrument_function: ", o->is_no_instrument_function);
  PrintBool(f, l + 2,
            "is_force_align_arg_pointer: ", o->is_force_align_arg_pointer);
  PrintBool(f, l + 2,
            "is_no_caller_saved_registers: ", o->is_no_caller_saved_registers);

  PrintTokStr(f, l + 2, "tok: ", o->tok);
  PrintStr(f, l + 2, "ptr: ", o->ptr);
  PrintBool(f, l + 2, "is_ms_abi: ", o->is_ms_abi);
  PrintInt(f, l + 2, "stack_offset: ", o->stack_offset);
  PrintInt(f, l + 2, "stack_align: ", o->stack_align);
  for (int i = 0; i < o->refs.len; i++) {
      PrintStr(f, l + 2, "ref: ", o->refs.data[i]);
  }
  PrintInitializer(f, l + 2, "init: ", o->init);
  PrintBool(f, l + 2, "force_frame_pointer: ", o->force_frame_pointer);
  PrintInt(f, l + 2, "min_vector_width: ", o->min_vector_width);

  PrintInt(f, l + 2, "stack_size: ", o->stack_size);
  PrintInt(f, l + 2, "overflow_arg_area: ", o->overflow_arg_area);
  PrintBool(f, l + 2, "pass_by_stack: ", o->pass_by_stack);
  PrintObj(f, l + 2, "params: ", o->params);
  if (o->body) PrintNode(f, l + 2, "body: ", o->body);
  if (o->locals) PrintObj(f, l + 2, "locals: ", o->locals);
  if (o->va_area) PrintObj(f, l + 2, "va_area: ", o->va_area);
  if (o->alloca_bottom) PrintObj(f, l + 2, "alloca_bottom: ", o->alloca_bottom);
  PrintBool(f, l + 2, "is_live: ", o->is_live);
  PrintBool(f, l + 2, "is_root: ", o->is_root);
  PrintInt(f, l + 2, "file_no: ", o->file_no);
  PrintInt(f, l + 2, "line_no: ", o->line_no);
  PrintBool(f, l + 2, "is_prototyped: ", o->is_prototyped);
  PrintBool(f, l + 2, "is_address_used: ", o->is_address_used);
  PrintBool(f, l + 2, "is_param: ", o->is_param);
  PrintLine(f, l, "}");
}


void print_ast(FILE *f, Obj *o) {
  g_visited.i = 0;
  for (; o ; o = o->next) {
    PrintObj(f, 0, "", o);
  }
}
