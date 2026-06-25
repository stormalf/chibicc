#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <glob.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <sys/resource.h>
#include <stdatomic.h>
#include <limits.h>

#define SET_CTX(ctx) \
    do { \
        (ctx)->filename = __FILE__; \
        (ctx)->funcname = __func__; \
        (ctx)->line_no  = __LINE__ + 1; \
    } while (0)

#define LIBDIR "/usr/local"

#define ROUNDUP(X, K)   (((X) + (K) - 1) & -(K))
#define ROUNDDOWN(X, K) ((X) & -(K))

#ifndef __has_attribute
#define __has_attribute(x) __GCC4_has_attribute_##x
#endif

#define MAX(x, y) ((x) < (y) ? (y) : (x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define PRODUCT "chibicc"
#define VERSION "1.0.25"
#define MAXLEN 1001
#define DEFAULT_TARGET_MACHINE "x86_64-linux-gnu"
#define MAX_BUILTIN_ARGS 8
#define MAX_WEAK 20

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)


#define HELP PRODUCT " is a C compiler based on " PRODUCT " created by Rui Ueyama.\n \
See original project https://github.com/rui314/chibicc for more information\n \
this " PRODUCT " supports vector, some extended assembly and int128 \n"

#define USAGE PRODUCT " usage :\n \
--help or -h print the help\n \
--version or -v print the version of " PRODUCT "\n \
-cc1 run the cc1 function needs -cc1-input (-cc1-output optional) parameter \n \
-fuse-ld to specify other linker than ld used by default \n \
-x Specify the language of the following input files.\n \
    Permissible languages include: c assembler none\n \
    'none' means revert to the default behavior of\n \
    guessing the language based on the file's extension.\n \
-S generate assembly file \n \
-o path to output executable if omitted a.out generated\n \
-c path to source to compile \n \
-Xlinker <arg> Pass <arg> on to the linker.\n \
-Wl,<options> Pass comma-separated <options> on to the linker.\n \
-z <arg> Pass <arg> on to the linker. \n \
-soname <arg> Pass -soname <arg> on to the linker. \n \
--version-script <arg> Pass --version-script <arg> to the linker.\n \
-I<path> Pass path to the include directories \n \
-L<path> Pass path to the lib directories \n \
-D<macro> define macro example -DM13 \n \
-U<macro> undefine macro example -UM13\n \
-s to strip all symbols during linkage phasis \n \
-M -MD -MP -MMD -MF <arg> -MT <arg> -MQ <arg> compiler write a list of input files to \n \
    stdout in a format that \"make\" command can read. This feature is\n \
    used to automate file dependency management\n \
-fpic or -fPIC Generate position-independent code (PIC)\n \
-fno-pic disables the generation of position-independent code with relative address references\n \
-pie Create a dynamically linked position independent \n \
-fpie Create a dynamically linked position independent\n \
-fPIE Create a dynamically linked position independent\n \
-fcommon is the default if not specified, it's mainly useful to enable legacy code to link without errors\n \
-fno-common specifies that the compiler places uninitialized global variables in the BSS section of the object file.\n \
-static  pass to the linker to link a program statically\n \
-pthread pass to the linker to link with lpthread library \n \
-shared pass to the linker to produce a shared object which can then be linked with other objects to form an executable.\n \
-hashmap-test to test the hashmap function \n \
-idirafter <dir> apply to lookup for both the #include \"file\" and #include <file> directives.\n \
-### to dump all commands executed by chibicc \n \
-debug to dump all commands executed by chibicc in a log file in /tmp/chibicc.log\n \
-E Stop after the preprocessing stage; do not run the compiler proper. \n \
    The output is in the form of preprocessed source code, which is sent to the standard output.\n \
    Input files that don’t require preprocessing are ignored.\n \
-rpath <dir> Add a directory to the runtime library search path this parameter is passed to the linker. \n \
    This is used when linking an ELF executable with shared objects.\n \
    All -rpath arguments are concatenated and passed to the runtime linker,\n \
    which uses them to locate shared objects at runtime. \n \
    The -rpath option is also used when locating shared objects \n \
    which are needed by shared objects explicitly included in the link. \n \
-dumpmachine it's required by some projects returns x86_64-linux-gnu\n \
-dotfile generates a file with .dot extension that can be visualized using graphviz package \n \
-dM Print macro definitions in -E mode instead of normal output\n \
-print print all tokens in a log file in /tmp/chibicc.log \n \
-A print Abstract Syntax Tree in a log file in /tmp/chibicc.log \n \
-msse enabling sse support \n \
-mno-sse disabling sse support \n \
-msse2 enabling sse2 support \n \
-mno-sse2 disabling sse2 support \n \
-msse3 enabling sse3 support \n \
-mssse3 enabling supplemental sse3 support (but chibicc managed it as -msse3) \n \
-mno-sse3 disabling sse3 support \n \
-msse4 enabling sse4 support \n \
-mno-sse4 disabling sse4 support \n \
-msse4.1 enabling sse4.1 support \n \
-msse4.2 enabling sse4.2 support \n \
-mcrc32 enabling crc32 instruction support \n \
-nostdlib  Do not use the standard system startup files or libraries when linking \n \
-nostdinc Do not use the standard system header files when compiling \n \
-ffreestanding  Compile for a freestanding environment; implies no CRT startup files\n \
-fvisibility=default|hidden|protected  Set default symbol visibility\n \
-Wimplicit-function-declaration  Warn about implicit function declarations\n \
-Wno-implicit-function-declaration  Suppress implicit function declaration diagnostics\n \
-std=c99 generates an error on implicit function declaration (without -std only a warning is emitted) \n \
-std=c11 generates an error on implicit function declaration (without -std only a warning is emitted) \n \
-mmmx enabling mmx instructions \n \
-mno-mmx disabling mmx instructions \n \
-mavx enabling avx instructions \n \
-mavx2 enabling avx2 instructions \n \
-print-search-dirs prints minimal information on install dir. \n \
-Werror any warning is sent as an error and stops the compile \n \
-fomit-frame-pointer omits frame pointer and uses rsp-relative addressing. Minimal stack usage \n \
-f-no-omit-frame-pointer always keeps frame pointer (default) \n \
-fcf-protection enable control flow protection (CET IBT + SHSTK) \n \
-g enabling debug symbols \n \
-O0 disabling optimization \n \
-O or -O1 enabling optimization level 1 \n \
-O2 enabling optimization level 2 \n \
-O3 enabling optimization level 3 \n \
chibicc [ -o <path> ] <file>\n"

typedef struct Type Type;
typedef struct Node Node;
typedef struct Member Member;
typedef struct DebugTypedef DebugTypedef;
typedef struct Relocation Relocation;
typedef struct Hideset Hideset;
typedef struct Scope Scope;


typedef struct
{
  const char *filename;
  const char *funcname;
  int line_no;
} Context;

typedef Context Context;

struct FpClassify {
  Node *node;
  int args[5];
};
typedef struct FpClassify FpClassify;


//
// strings.c
//

typedef struct
{
  char **data;
  int capacity;
  int len;
} StringArray;

void strarray_push(StringArray *arr, char *s);
char *format(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

//
// tokenize.c
//

// Token
typedef enum
{
  TK_IDENT,   // Identifiers
  TK_PUNCT,   // Punctuators
  TK_KEYWORD, // Keywords
  TK_STR,     // String literals
  TK_NUM,     // Numeric literals
  TK_PP_NUM,  // Preprocessing numbers
  TK_EOF,     // End-of-file markers  
} TokenKind;

typedef struct
{
  char *name;
  unsigned int file_no;
  char *contents;

  // For #line directive
  char *display_name;
  int line_delta;
} File;

// Token type
typedef struct Token Token;
struct Token
{
  TokenKind kind;   // Token kind
  Token *next;      // Next token
  int64_t val;     // If kind is TK_NUM, its value
  long double fval; // If kind is TK_NUM, its value
  char *loc;        // Token location
  int len;          // Token length
  Type *ty;         // Used if TK_NUM or TK_STR
  char *str;        // String literal contents including terminating '\0'

  File *file;       // Source location
  char *filename;   // Filename
  int line_no;      // Line number
  int line_delta;   // Line number
  int pack_align;   // Active #pragma pack value (0 means default)
  bool at_bol;      // True if this token is at beginning of line
  bool has_space;   // True if this token follows a space character
  Hideset *hideset; // For macro expansion
  Token *origin;    // If this is expanded from a macro, the original token
};

noreturn void error(char *fmt, ...) __attribute__((format(printf, 1, 2)));
noreturn void error_at(char *loc, char *fmt, ...) __attribute__((format(printf, 2, 3)));
noreturn void error_tok(Token *tok, char *fmt, ...) __attribute__((format(printf, 2, 3)));
void warn_tok(Token *tok, char *fmt, ...) __attribute__((format(printf, 2, 3)));
bool equal(Token *tok, const char *op);
Token *skip(Token *tok, char *op, Context *ctx);
bool consume(Token **rest, Token *tok, char *str);
void convert_pp_tokens(Token *tok);
File **get_input_files(void);
File *new_file(char *name, unsigned int file_no, char *contents);
Token *tokenize_string_literal(Token *tok, Type *basety);
Token *tokenize(File *file);
Token *tokenize_file(char *filename);
void convert_universal_chars(char *p);
char *get_abs_path(char *path);
bool startswith(char *p, char *q);

#define unreachable() \
  error("internal error at %s:%d", __FILE__, __LINE__)

//
// preprocess.c
//

char *search_include_paths(char *filename);
void init_macros(void);
void define_macro(char *name, char *buf);
void undef_macro(char *name);
Token *preprocess(Token *tok, bool isReadLine);
void define_typedefs(void);
void print_all_macros(void);

//
// parse.c
//
// This struct represents a variable initializer. Since initializers
// can be nested (e.g. `int x[2][2] = {{1, 2}, {3, 4}}`), this struct
// is a tree data structure.
typedef struct Initializer Initializer;
struct Initializer
{
  Initializer *next;
  Type *ty;
  Token *tok;
  bool is_flexible;

  // If it's not an aggregate type and has an initializer,
  // `expr` has an initialization expression.
  Node *expr;

  // If it's an initializer for an aggregate type (e.g. array or struct),
  // `children` has initializers for its children.
  Initializer **children;

  // Only one member can be initialized for a union.
  // `mem` is used to clarify which member is initialized.
  Member *mem;
};


// Variable or function
typedef struct Obj Obj;
struct Obj
{
  Obj *next;
  char *name;     // Variable name
  char *funcname; // function name
  char *alias_name; // alias name for function when weak attribute
  Type *ty;       // Type
  Token *tok;     // representative token
  bool is_local;  // local or global/function
  bool is_compound_lit; //to handle compound literals
  int align;      // alignment

  // Local variable
  int offset;
  char *ptr;
  int order;
  int nbparm;
  // Global variable or function
  bool is_function;
  bool is_definition;
  bool is_static;
  bool is_extern;

  // Global variable
  bool is_tentative;
  bool is_tls;
  char *init_data;
  Relocation *rel;

  // Function
  //from COSMOPOLITAN adding is_weak
  char *section;
  bool is_weak;
  bool is_externally_visible;
  char *visibility;
  char *asmname;
  bool is_inline;
  int min_vector_width;

  //from COSMOPOLITAN adding is_aligned, is_noreturn, is_destructor, is_constructor, is_ms_abi, is_no_instrument_function, is_force_align_arg_pointer, is_no_caller_saved_registers
  bool is_aligned;
  bool is_noreturn;
  bool is_constructor;
  bool is_destructor;
  int  destructor_priority;
  int  constructor_priority;
  bool is_ms_abi; 
  bool is_no_instrument_function;
  bool is_force_align_arg_pointer;
  bool is_no_caller_saved_registers;
  
  // Function calls vfork returns twice unsafe with stack frames
  Obj *params;
  Node *body;
  Obj *locals;
  Obj *va_area;
  Obj *alloca_bottom;
  int stack_size;
  int overflow_arg_area; 
  bool pass_by_stack; 
  int stack_offset;
  int stack_align;

  // Static inline function
  bool is_live;
  bool is_root;
  StringArray refs;

  //for dwarf 
  int file_no; // Index or number to identify the source file
  int line_no; // Line number where the variable or function is defined
  bool is_prototyped; // Whether the function is prototyped or not
  Initializer *init;
  bool is_address_used;
  bool is_param;
  char *cleanup_name;
  bool force_frame_pointer;
  Type *vla_ty;
  bool is_returned_twice;
};

// Global variable can be initialized either by a constant expression
// or a pointer to another global variable. This struct represents the
// latter.
typedef struct Relocation Relocation;
struct Relocation
{
  Relocation *next;
  int offset;
  char **label;
  long addend;
};

// AST node
typedef enum
{
  ND_NULL_EXPR, // Do nothing
  ND_ADD,       // +
  ND_SUB,       // -
  ND_MUL,       // *
  ND_DIV,       // /
  ND_NEG,       // unary -
  ND_MOD,       // %
  ND_BITAND,    // &
  ND_BITOR,     // |
  ND_BITXOR,    // ^
  ND_SHL,       // <<
  ND_SHR,       // >>
  ND_EQ,        // ==
  ND_NE,        // !=
  ND_LT,        // <
  ND_LE,        // <=
  ND_ASSIGN,    // =
  ND_COND,      // ?:
  ND_COMMA,     // ,
  ND_MEMBER,    // . (struct member access)
  ND_ADDR,      // unary &
  ND_DEREF,     // unary *
  ND_NOT,       // !
  ND_BITNOT,    // ~
  ND_LOGAND,    // &&
  ND_LOGOR,     // ||
  ND_RETURN,    // "return"
  ND_IF,        // "if"
  ND_FOR,       // "for" or "while"
  ND_DO,        // "do"
  ND_SWITCH,    // "switch"
  ND_CASE,      // "case"
  ND_BLOCK,     // { ... }
  ND_GOTO,      // "goto"
  ND_GOTO_EXPR, // "goto" labels-as-values
  ND_LABEL,     // Labeled statement
  ND_LABEL_VAL, // [GNU] Labels-as-values
  ND_FUNCALL,   // Function call
  ND_EXPR_STMT, // Expression statement
  ND_STMT_EXPR, // Statement expression
  ND_VAR,       // Variable
  ND_VLA_PTR,   // VLA designator
  ND_NUM,       // Integer
  ND_CAST,      // Type cast
  ND_MEMZERO,   // Zero-clear a stack variable
  ND_ASM,       // "asm"
  ND_CAS,       // Atomic compare-and-swap
  ND_EXCH,      // Atomic exchange
  ND_CAS_N,     //atomic compare-and-swap with value
  ND_EXCH_N,       // Atomic exchange with value
  ND_CMPEXCH,
  ND_CMPEXCH_N,
  ND_LOAD,         // Atomic load to pointer
  ND_LOAD_N,       // Atomic load to result
  ND_STORE,        // Atomic store to pointer
  ND_STORE_N,      // Atomic store to result
  ND_TESTANDSET,   // Sync lock test and set
  ND_TESTANDSETA,  // Atomic lock test and set
  ND_CLEAR,        // Atomic clear
  ND_RELEASE,      // Atomic lock release
  ND_FETCHADD,     // Atomic fetch and add
  ND_FETCHSUB,     // Atomic fetch and sub
  ND_FETCHXOR,     // Atomic fetch and xor
  ND_FETCHAND,     // Atomic fetch and and
  ND_FETCHOR,      // Atomic fetch and or
  ND_SUBFETCH,     // Atomic sub and fetch
  ND_SYNC,      //atomic synchronize
  ND_MEMBARRIER, // atomic thread/signal fence
  ND_BUILTIN_MEMCPY, //builtin memcpy
  ND_BUILTIN_MEMSET, //builtin memset
  ND_BUILTIN_CLZ, //builtin clz
  ND_BUILTIN_CLZL, //builtin clzl
  ND_BUILTIN_CLZLL, //builtin clzll
  ND_BUILTIN_CTZ, //builtin ctz
  ND_BUILTIN_CTZL, //builtin ctzl
  ND_BUILTIN_CTZLL, //builtin ctzll
  ND_POPCOUNT,    //builtin popcount
  ND_EXPECT,    //builtin expect
  ND_ABORT,    //builtin abort
  ND_RETURN_ADDR,    //builtin return address
  ND_BUILTIN_ADD_OVERFLOW,  //builtin add overflow
  ND_BUILTIN_SUB_OVERFLOW,  //builtin sub overflow
  ND_BUILTIN_MUL_OVERFLOW, //builtin mul overflow
  ND_UNREACHABLE,   //builtin unreachable
  ND_ALLOC,   //builtin alloca
  ND_BUILTIN_INFF, //builtin inff
  ND_BUILTIN_INF, //builtin inf
  ND_BUILTIN_NAN, //builtin nan
  ND_BUILTIN_NANF, //builtin nanf
  ND_BUILTIN_NANL, //builtin nanl
  ND_BUILTIN_ISNAN, //builtin isnan
  ND_BUILTIN_HUGE_VALL, //builtin huge vall
  ND_BUILTIN_HUGE_VALF, //builtin huge valf
  ND_BUILTIN_HUGE_VAL, //builtin huge val
  ND_BUILTIN_BSWAP16, //builtin bswap16
  ND_BUILTIN_BSWAP32, //builtin bswap32
  ND_BUILTIN_BSWAP64, //builtin bswap64,
  ND_BUILTIN_FRAME_ADDRESS, // builtin frame address
  ND_STDC_BIT_CEIL, // builtin stdc bit ceil
  ND_EMMS,
  ND_SFENCE,
  ND_LFENCE,
  ND_MFENCE,
  ND_PAUSE,
  ND_STMXCSR,
  ND_CVTPI2PS,
  ND_CVTPS2PI,
  ND_CLFLUSH,
  ND_VECINITV2SI, 
  ND_VECEXTV2SI,
  ND_PACKSSWB,
  ND_PACKSSDW,
  ND_PACKUSWB,
  ND_PUNPCKHBW,
  ND_PUNPCKHWD,
  ND_PUNPCKHDQ,
  ND_PUNPCKLBW,
  ND_PUNPCKLWD,
  ND_PUNPCKLDQ,
  ND_PADDB,
  ND_PADDW,
  ND_PADDD,
  ND_PADDQ,
  ND_PADDSB,
  ND_PADDSW,
  ND_PADDUSB,
  ND_PADDUSW,
  ND_PSUBB,
  ND_PSUBW,
  ND_PSUBD,
  ND_PSUBQ,
  ND_PSUBSB,
  ND_PSUBSW,
  ND_PSUBUSB,
  ND_PSUBUSW,
  ND_PMADDWD,
  ND_PMULHW,
  ND_PMULLW,
  ND_PSLLW,
  ND_PSLLWI,
  ND_PSLLD,
  ND_PSLLDI,
  ND_PSLLQ,
  ND_PSLLQI,
  ND_PSRAW,
  ND_PSRAWI,
  ND_PSRAD,
  ND_PSRADI,
  ND_PSRLW,
  ND_PSRLWI,
  ND_PSRLD,
  ND_PSRLDI,
  ND_PSRLQ,
  ND_PSRLQI,
  ND_PAND,
  ND_PANDN,
  ND_POR,
  ND_PXOR,
  ND_PCMPEQB,
  ND_PCMPGTB,
  ND_PCMPEQW,
  ND_PCMPGTW,
  ND_PCMPEQD,
  ND_PCMPGTD,  
  ND_VECINITV4HI,
  ND_VECINITV8QI,
  ND_ADDSS,
  ND_SUBSS,
  ND_MULSS,
  ND_DIVSS,
  ND_SQRTSS,
  ND_RCPSS,
  ND_RSQRTSS,
  ND_SQRTPS,
  ND_MINSS,
  ND_MAXSS,
  ND_RCPPS,
  ND_RSQRTPS,
  ND_MINPS,
  ND_MAXPS,
  ND_ANDPS,
  ND_ANDNPS,
  ND_ORPS,
  ND_XORPS,
  ND_CMPEQSS,
  ND_CMPLTSS,
  ND_CMPLESS,
  ND_MOVSS,
  ND_CMPNEQSS,
  ND_CMPNLTSS,
  ND_CMPNLESS,
  ND_CMPORDSS,
  ND_CMPUNORDSS,
  ND_CMPEQPS,
  ND_CMPLTPS,
  ND_CMPLEPS,
  ND_CMPGTPS,
  ND_CMPGEPS,
  ND_CMPNEQPS,
  ND_CMPNLTPS,
  ND_CMPNLEPS,
  ND_CMPNGTPS,
  ND_CMPNGEPS,
  ND_CMPORDPS,
  ND_CMPUNORDPS,
  ND_COMIEQ,
  ND_COMILT,
  ND_COMILE,
  ND_COMIGT,
  ND_COMIGE,
  ND_COMINEQ,
  ND_UCOMIEQ,
  ND_UCOMILT,
  ND_UCOMILE,
  ND_UCOMIGT,
  ND_UCOMIGE,
  ND_UCOMINEQ,
  ND_CVTSS2SI,
  ND_CVTSS2SI64,
  ND_CVTTSS2SI,
  ND_CVTTSS2SI64,
  ND_CVTTPS2PI,
  ND_CVTSI2SS,
  ND_CVTSI642SS,
  ND_MOVLHPS,
  ND_MOVHLPS,
  ND_UNPCKHPS,
  ND_UNPCKLPS,
  ND_LOADHPS,
  ND_STOREHPS,
  ND_LOADLPS,
  ND_STORELPS,
  ND_MOVMSKPS,
  ND_LDMXCSR,
  ND_SHUFPS,
  ND_SHUFFLE,
  ND_PMAXSW,
  ND_PMAXUB,
  ND_PMINSW,
  ND_PMINUB,
  ND_PMOVMSKB,
  ND_PMULHUW,
  ND_MASKMOVQ,
  ND_PAVGB,
  ND_PAVGW,
  ND_PSADBW,
  ND_MOVNTQ,
  ND_MOVNTPS,
  ND_SHUFPD,
  ND_ROUNDPD,
  ND_ROUNDSD,
  ND_ROUNDSS,
  ND_ROUNDPS,
  ND_VECEXTV4SI,
  ND_VECEXTV4SF,
  ND_ADDSD,
  ND_SUBSD,
  ND_MULSD,
  ND_DIVSD,
  ND_SQRTPD,
  ND_MOVSD,
  ND_SQRTSD,
  ND_MINPD,
  ND_MINSD,
  ND_MAXPD,
  ND_MAXSD,
  ND_ANDPD,
  ND_ANDNPD,
  ND_ORPD,
  ND_XORPD,
  ND_CMPEQPD,
  ND_CMPLTPD,
  ND_CMPLEPD,
  ND_CMPGTPD,
  ND_CMPGEPD,
  ND_CMPNEQPD,
  ND_CMPNLTPD,
  ND_CMPNLEPD,
  ND_CMPNGTPD,
  ND_CMPNGEPD,
  ND_CMPORDPD,
  ND_CMPUNORDPD,
  ND_CMPEQSD,
  ND_CMPLTSD,
  ND_CMPLESD,
  ND_CMPNEQSD,
  ND_CMPNLTSD,
  ND_CMPNLESD,
  ND_CMPORDSD,
  ND_CMPUNORDSD,
  ND_COMISDEQ,
  ND_COMISDLT,
  ND_COMISDLE,
  ND_COMISDGT,
  ND_COMISDGE,
  ND_COMISDNEQ,
  ND_UCOMISDEQ,
  ND_UCOMISDLT,
  ND_UCOMISDLE,
  ND_UCOMISDGT,
  ND_UCOMISDGE,
  ND_UCOMISDNEQ,
  ND_MOVQ128,
  ND_CVTDQ2PD,
  ND_CVTDQ2PS,
  ND_CVTPD2DQ,
  ND_CVTPD2PI,
  ND_CVTPD2PS,
  ND_CVTTPD2DQ,
  ND_CVTTPD2PI,
  ND_CVTPI2PD,
  ND_CVTPS2DQ,
  ND_CVTTPS2DQ,
  ND_CVTPS2PD,
  ND_CVTSD2SI,
  ND_CVTSD2SI64,
  ND_CVTTSD2SI,
  ND_CVTTSD2SI64,
  ND_CVTSD2SS,
  ND_CVTSI2SD,
  ND_CVTSI642SD,
  ND_CVTSS2SD,
  ND_UNPCKHPD,
  ND_UNPCKLPD,
  ND_LOADHPD,
  ND_LOADLPD,
  ND_MOVMSKPD,
  ND_PACKSSWB128,
  ND_PACKSSDW128,
  ND_PACKUSWB128,
  ND_PUNPCKHBW128,
  ND_PUNPCKHWD128,
  ND_PUNPCKHDQ128,
  ND_PUNPCKHQDQ128,
  ND_PUNPCKLBW128,
  ND_PUNPCKLWD128,
  ND_PUNPCKLDQ128,
  ND_PUNPCKLQDQ128,
  ND_PADDSB128,
  ND_PADDSW128,
  ND_PADDUSB128,
  ND_PADDUSW128,
  ND_PSUBSB128,
  ND_PSUBSW128,
  ND_PSUBUSB128,
  ND_PSUBUSW128,  
  ND_PMADDWD128,
  ND_PMULHW128,
  ND_PMULUDQ,
  ND_PMULUDQ128,
  ND_PSLLWI128,
  ND_PSLLDI128,
  ND_PSLLQI128,
  ND_PSRAWI128,
  ND_PSRADI128,
  ND_PSRLWI128,
  ND_PSRLDI128,
  ND_PSRLQI128,
  ND_PSLLW128,
  ND_PSLLD128,
  ND_PSLLQ128,
  ND_PSRAW128,
  ND_PSRAD128,
  ND_PSRLW128,
  ND_PSRLD128,
  ND_PSRLQ128,
  ND_PANDN128,
  ND_PMAXSW128,
  ND_PMAXUB128,
  ND_PMINSW128,
  ND_PMINUB128,
  ND_PMOVMSKB128,
  ND_PMULHUW128,
  ND_MASKMOVDQU,
  ND_PAVGB128,
  ND_PAVGW128,
  ND_PSADBW128,
  ND_MOVNTI,
  ND_MOVNTI64,
  ND_MOVNTDQ,
  ND_MOVNTPD,
  ND_POPCOUNTL,
  ND_POPCOUNTLL,
  ND_PARITY,
  ND_PARITYL,
  ND_PARITYLL,
  ND_UADD_OVERFLOW,
  ND_UADDL_OVERFLOW,
  ND_UADDLL_OVERFLOW,
  ND_UMUL_OVERFLOW,
  ND_UMULL_OVERFLOW,
  ND_UMULLL_OVERFLOW,
  ND_POS,
  ND_MWAIT,
  ND_MONITOR,
  ND_ADDSUBPS,
  ND_HADDPS,
  ND_HSUBPS,
  ND_MOVSHDUP,
  ND_MOVSLDUP,
  ND_ADDSUBPD,
  ND_HADDPD,
  ND_HSUBPD,
  ND_LDDQU,
  ND_PHADDW128,
  ND_PHADDD128,
  ND_PHADDSW128,
  ND_PHADDW,
  ND_PHADDD,
  ND_PHADDSW,
  ND_PHSUBW128,
  ND_PHSUBD128,
  ND_PHSUBSW128,
  ND_PHSUBW,
  ND_PHSUBD,
  ND_PHSUBSW,
  ND_PMADDUBSW128,
  ND_PMADDUBSW,
  ND_PMULHRSW128,
  ND_PMULHRSW,
  ND_PSHUFB128,
  ND_PSHUFB,
  ND_PSIGNB128,
  ND_PSIGNW128,
  ND_PSIGND128,
  ND_PSIGNB,
  ND_PSIGNW,
  ND_PSIGND,
  ND_PABSB128,
  ND_PABSW128,
  ND_PABSD128,
  ND_PABSB,
  ND_PABSW,
  ND_PABSD,
  ND_PTESTZ128,
  ND_PTESTC128,
  ND_PTESTNZC128,
  ND_PBLENDVB128,
  ND_PBLENDW128,
  ND_BLENDVPS,
  ND_BLENDVPD,
  ND_BLENDPS,
  ND_BLENDPD,
  ND_BLENDPS256,
  ND_BLENDPD256,
  ND_DPPS,
  ND_DPPD,
  ND_INSERTPS128,
  ND_MPSADBW128,
  ND_MPSADBW256,
  ND_PMINSB128,
  ND_PMAXSB128,
  ND_PMINUW128,
  ND_PMAXUW128,
  ND_PMINSD128,
  ND_PMAXSD128,
  ND_PMINUD128,
  ND_PMAXUD128,
  ND_PMULDQ128,  
  ND_PHMINPOSUW128,
  ND_PMOVSXBD128, 
  ND_PMOVSXWD128,
  ND_PMOVSXBQ128,
  ND_PMOVSXDQ128,
  ND_PMOVSXWQ128,
  ND_PMOVSXBW128,
  ND_PMOVZXBD128,
  ND_PMOVZXWD128,
  ND_PMOVZXBQ128,
  ND_PMOVZXBW128,
  ND_PMOVZXDQ128,
  ND_PMOVZXWQ128,
  ND_PACKUSDW128,
  ND_MOVNTDQA,
  ND_CRC32QI,
  ND_CRC32HI,
  ND_CRC32SI,
  ND_CRC32DI,
  ND_PSHUFD,
  ND_PSHUFHW,
  ND_PSHUFLW,
  ND_PSHUFW,
  ND_FETCHNAND,       
  ND_ADD_AND_FETCH,   
  ND_SUB_AND_FETCH,   
  ND_BOOL_CAS,        
  ND_PREFETCH,
  ND_RDTSC,
  ND_READEFLAGS_U64,
  ND_RDSSPQ,
  ND_SAVEPREVSSP,
  ND_SETSSBSY,
  ND_SLWPCB,
  ND_RDPKRU,
  ND_XBEGIN,
  ND_XEND,
  ND_SERIALIZE,
  ND_XSUSLDTRK,
  ND_XRESLDTRK,
  ND_CLUI,
  ND_STUI,
  ND_TESTUI,
  ND_WBNOINVD,
  ND_XTEST,
  ND_WBINVD,
  ND_RDPID,
  ND_RDFSBASE32,
  ND_RDFSBASE64,
  ND_RDGSBASE32,
  ND_RDGSBASE64,
  ND_VZEROALL,
  ND_VZEROUPPER,
  ND_FEMMS,
  ND_BSRSI,
  ND_RDPMC,
  ND_RDTSCP,
  ND_ROLQI,
  ND_ROLHI,
  ND_RORQI,
  ND_RORHI,
  ND_BSRDI, 
  ND_WRITEEFLAGS_U64,
  ND_INCSSPQ,
  ND_RSTORSSP,
  ND_WRSSD,
  ND_WRSSQ,
  ND_WRUSSD,
  ND_WRUSSQ,
  ND_CLRSSBSY,
  ND_SBB_U32,
  ND_ADDCARRYX_U32,
  ND_SBB_U64,
  ND_ADDCARRYX_U64,
  ND_TZCNT_U16,
  ND_BEXTR_U32,
  ND_BEXTR_U64,
  ND_ADDFETCH,  
  ND_ORFETCH,
  ND_ANDFETCH,
  ND_XORFETCH,
  ND_NANDFETCH,
  ND_FPCLASSIFY,   // floating point classify
  ND_ISUNORDERED,
  ND_SIGNBIT,
  ND_SIGNBITF,
  ND_SIGNBITL,
  ND_ATOMIC_IS_LOCK_FREE, //builtin atomic is lock free
  ND_PSUBUSB256,
  ND_PCMPGTB256_MASK,
  ND_PSHUFB256,
  ND_PBLENDVB256,
  ND_PSRLDQI128,
  ND_PSLLDQI128,
  ND_PSRLDQI256,
  ND_PSLLDQI256,
  ND_VINSERTF128_SI256,    
  ND_SI256_SI,
  ND_SI_SI256,
  ND_PALIGNR128,
  ND_PALIGNR256,
  ND_PALIGNR,
  ND_VPERM2I128_SI256,
  ND_PBLENDD256,
  ND_VEXTRACTF128_SI256,
  ND_VECEXTV16QI,
  ND_VECEXTV8HI,
  ND_ANDNOTSI256,
  ND_VECEXTV2DI,
  ND_PMULHUW256,
  ND_PD256_PD,
  ND_PS256_PS,
  ND_PSRLQI256,
  ND_PSLLQI256,
  ND_PERMDI256,
  ND_PSLLDI256,
  ND_PSRLDI256,
  ND_PSRADI256,
  ND_VECEXTV4HI,
  ND_VECSETV4HI,
  ND_VECSETV8HI,
  ND_VECSETV16QI,
  ND_VECSETV4SI,
  ND_VECSETV2DI,
  ND_PCMPISTRM128,
  ND_PCMPISTRI128,
  ND_PCMPISTRIA128,
  ND_PCMPISTRIC128,
  ND_PCMPISTRIO128,
  ND_PCMPISTRIS128,
  ND_PCMPISTRIZ128,
  ND_PCMPESTRM128,
  ND_PCMPESTRI128,
  ND_PCMPESTRIA128,
  ND_PCMPESTRIC128,
  ND_PCMPESTRIO128,
  ND_PCMPESTRIS128,
  ND_PCMPESTRIZ128,
  ND_PCLMULQDQ128,
  ND_DPPS256,
  ND_SHUFPD256,
  ND_SHUFPS256,
  ND_CMPPD,
  ND_CMPPS,
  ND_CMPPD256,
  ND_CMPPS256,
  ND_CMPSD,
  ND_CMPSS,
  ND_VEXTRACTF128_PD256,
  ND_VEXTRACTF128_PS256,
  ND_VINSERTF128_PD256,
  ND_VINSERTF128_PS256,
  ND_VPERM2F128_PD256,
  ND_VPERM2F128_PS256,
  ND_VPERM2F128_SI256,
  ND_VPERMILPD,
  ND_VPERMILPS,
  ND_VPERMILPD256,
  ND_VPERMILPS256,
  ND_EXP2PD_MASK,
  ND_EXP2PS_MASK,
  ND_RCP28PD_MASK,
  ND_RCP28PS_MASK,
  ND_RCP28SD_ROUND,
  ND_RCP28SS_ROUND,
  ND_RSQRT28PD_MASK,
  ND_RSQRT28PS_MASK,
  ND_RSQRT28SD_ROUND,
  ND_RSQRT28SS_ROUND,
  ND_GATHERPFDPD,
  ND_GATHERPFDPS,
  ND_GATHERPFQPD,
  ND_GATHERPFQPS,
  ND_SCATTERPFDPD,
  ND_SCATTERPFDPS,
  ND_SCATTERPFQPD,
  ND_SCATTERPFQPS,
  ND_VPSHLD_V32HI,
  ND_VPSHLD_V16SI,
  ND_VPSHLD_V8DI,
  ND_VPSHLD_V16SI_MASK,
  ND_VPSHLD_V8DI_MASK,
  ND_VPSHRD_V32HI,
  ND_VPSHRD_V16SI,
  ND_VPSHRD_V8DI,
  ND_VPSHRD_V16SI_MASK,
  ND_VPSHRD_V8DI_MASK,
  ND_XABORT,
  ND_VPCLMULQDQ_V4DI,
  ND_VPCLMULQDQ_V8DI,
} NodeKind;

// AST node type
struct 
Node
{
  NodeKind kind; // Node kind
  Node *next;    // Next node
  Type *ty;      // Type, e.g. int or pointer to int
  Token *tok;    // Representative token

  Node *lhs; // Left-hand side
  Node *rhs; // Right-hand side

  // "if" or "for" statement
  Node *cond;
  Node *then;
  Node *els;
  Node *init;
  Node *inc;  
  // "break" and "continue" labels
  char *brk_label;
  char *cont_label;

  // Block or statement expression
  Node *body;

  // Struct member access
  Member *member;

  // Function call
  Type *func_ty;
  Node *args;
  bool pass_by_stack;
  int stack_offset;       // Offset for stack-passed arguments during function calls
  bool realign_stack;
  Obj *ret_buffer;

  // Goto or labeled statement, or labels-as-values
  char *label;
  char *unique_label;
  Node *goto_next;

  // Switch
  Node *case_next;
  Node *default_case;

  // Case
  long begin;
  long end;

  // "asm" string literal
  char *asm_str;
  char memorder;
  // Atomic compare-and-swap
  Node *cas_addr;
  Node *cas_old;
  Node *cas_new;
  //compare and exchange
  Node *cas_ptr;
  Node *cas_expected;
  Node *cas_desired;
  Node *cas_weak;
  Node *cas_success;
  Node *cas_failure;

//for builtin memcpy
  Node *builtin_dest;
  Node *builtin_src;
  Node *builtin_size;
  Node *builtin_val;
  Node *builtin_args[MAX_BUILTIN_ARGS];
  int  builtin_nargs;
  // Atomic op= operators
  Obj *atomic_addr;
  Node *atomic_expr;

  // Atomic fetch operation
  bool atomic_fetch;

  // Variable
  Obj *var;

  // Numeric literal
  int64_t val;
  long double fval;
  FpClassify *fpc;
  // for dot diagram
  int unique_number;
  bool is_scalar_promoted;  
  bool is_tail;
  bool clobbers_rbx;
};

typedef struct
{
  Obj *var;
  Type *type_def;
  Type *enum_ty;
  int enum_val;
} VarScope;

Node *new_cast(Node *expr, Type *ty);
int64_t  const_expr(Token **rest, Token *tok);
Node *conditional(Token **rest, Token *tok);
Obj *parse(Token *tok);
VarScope *find_var(Token *tok);
Obj *find_func(char *name);
//from COSMOPOLITAN adding function ConsumeStringLiteral
char *ConsumeStringLiteral(Token **rest, Token *tok) ;
int64_t  eval(Node *node);
bool equal_tok(Token *a, Token *b);

extern bool opt_fbuiltin;
//
// type.c
//

typedef enum
{
  TY_VOID,
  TY_BOOL,
  TY_CHAR,
  TY_SHORT,
  TY_INT,
  TY_LONG,
  TY_FLOAT,
  TY_DOUBLE,
  TY_LDOUBLE,
  TY_ENUM,
  TY_PTR,
  TY_FUNC,
  TY_ARRAY,
  TY_VLA, // variable-length array
  TY_STRUCT,
  TY_UNION,
  TY_VECTOR,
  TY_INT128,
  TY_LLONG,
} TypeKind;



struct Type
{
  TypeKind kind;
  int64_t size;          // sizeof() value
  int align;         // alignment
  bool is_unsigned;  // unsigned or signed
  bool is_atomic;    // true if _Atomic
   //from COSMOPOLITAN adding is_const, is_restrict, is_volatile
  bool is_const;     // const
  bool is_restrict;  // restrict
  bool is_volatile;  // volatile
  //from COSMOPOLITAN adding is_ms_abi, is_static
  bool is_ms_abi;    // microsoft abi
  bool is_static;    // for array parameter pointer
  
  bool is_pointer;   // true if it's a pointer
  Type *pointertype; // store the pointer type int, char...
  Type *origin;      // for type compatibility check
  Type *decl_next;    // forward declarations
  Token *tag;

  // Pointer-to or array-of type. We intentionally use the same member
  // to represent pointer/array duality in C.
  //
  // In many contexts in which a pointer is expected, we examine this
  // member instead of "kind" member to determine whether a type is a
  // pointer or not. That means in many contexts "array of T" is
  // naturally handled as if it were "pointer to T", as required by
  // the C spec.
  Type *base;

  // Declaration
  Token *name;
  Token *name_pos;
  Obj *param_var; // placeholder var for function parameter (used by VLA sizes)

  // Array
  int64_t array_len;
  //from COSMOPOLITAN adding vector_size
  int vector_size;

  // Variable-length array
  Node *vla_len; // # of elements
  Obj *vla_size; // sizeof() value
  Type *vla_param_ty;   // original VLA type before array→pointer decay in func params

  // Struct
  Member *members;
  bool is_flexible;
  bool is_packed;
  bool is_ms_struct;
  bool has_vla;  
  //from COSMOPOLITAN adding is_aligned
  bool is_aligned;
  bool is_weak;
  char *visibility;
  bool is_inline;
  int min_vector_width;
  bool is_compound_lit; // Flag to indicate if this type is a compound literal
  // Function type
  Type *return_ty;
  Type *params;
  bool is_variadic;
  bool is_oldstyle;
  Type *next;
  char *alias_name; // alias name for function when weak attribute
  char *section;
  bool is_constructor;
  bool is_destructor;
  int destructor_priority;
  int constructor_priority;
  bool is_vector;
  Token *tag_name; // struct/union/enum tag name

  // Scope tree for function-local variables
  struct Scope *scopes;
};

struct DebugTypedef
{
  DebugTypedef *next;
  char *name;
  Type *ty;
};

// Struct member
struct Member
{
  Member *next;
  Type *ty;
  Token *tok; // for error message
  Token *name;
  int idx;
  // Natural alignment of the member's type (i.e. before any packing rules).
  int align;
  // Explicit requested alignment from attributes (_Alignas / __attribute__((aligned))).
  // This is a minimum alignment request and may override packing.
  int attr_align;
  int offset;

  // Bitfield
  bool is_bitfield;
  int bit_offset;
  int bit_width;
};

extern Type *ty_void;
extern Type *ty_void_ptr;
extern Type *ty_bool;

extern Type *ty_char;
extern Type *ty_short;
extern Type *ty_int;
extern Type *ty_long;
extern Type *ty_llong;

extern Type *ty_uchar;
extern Type *ty_ushort;
extern Type *ty_uint;
extern Type *ty_ulong;
extern Type *ty_ullong;

extern Type *ty_float;
extern Type *ty_double;
extern Type *ty_ldouble;

extern Type *ty_int128;
extern Type *ty_uint128;

bool is_integer(Type *ty);
bool is_flonum(Type *ty);
bool is_numeric(Type *ty);
bool is_builtin_canonical_type(Type *ty);
bool is_compatible(Type *t1, Type *t2);
bool is_compatible2(Type *t1, Type *t2);
Type *copy_type(Type *ty);
Type *pointer_to(Type *base);
Type *func_type(Type *return_ty);
Type *array_of(Type *base, int64_t  size);
Type *vector_of(Type *base, int64_t  size);
Type *vla_of(Type *base, Node *expr);
Type *enum_type(void);
Type *struct_type(void);
void add_type(Node *node);
bool is_bitfield(Node *node);
bool is_array(Type *ty);
Type *new_qualified_type(Type *ty);
Type *unqual(Type *ty);
bool is_vector(Type *ty);
bool is_int128(Type *ty);
bool is_pointer(Type *ty);
bool is_const_expr(Node *node);
bool contains_label(Node *node);

extern DebugTypedef *debug_typedefs;


//
// printast.c
//

extern const char kNodeKindStr[][21];
void print_ast(FILE *, Obj *);

//
// debug.c
//

char *tokenkind2str(TokenKind kind);
void print_debug_tokens(char *currentfilename, char *function, Token *tok);
void emit_debug_info(Obj *prog);

//
// codegen.c
//

void gen_expr(Node *node);
void codegen(Obj *prog, FILE *out);
int align_to(int n, int align);
int count(void);
int push_tmp(void);
void pop_tmp(char *arg);
void pushx_tmp(void);
void popx_tmp(char *a, char *b);
char *reg_ax(int sz);
char *reg_bx(int sz);
char *reg_cx(int sz);
char *reg_dx(int sz);
char *reg_di(int sz);
char *reg_si(int sz);
char *reg_r8w(int sz);
char *reg_r9w(int sz);
char *reg_r10w(int sz);
char *reg_r11w(int sz);
char *reg_r12w(int sz);
char *reg_r13w(int sz);
char *reg_r14w(int sz);
char *reg_r15w(int sz);
void assign_lvar_offsets(Obj *prog);
int add_register_used(char *regist);
void clear_register_used();
char *register32_to_64(char *regist);
char *register16_to_64(char *regist);
char *register8_to_64(char *regist);
char *register_available();  
char *specific_register_available(char *regist); 
bool check_register_used(char *regist);
void check_register_in_template(char *template); 
void pushreg(const char *arg);
void gen_fpclassify(FpClassify *);
void println(char *fmt, ...);
int get_align(Obj *var);
bool is_omit_fp(Obj *fn);
Obj *get_current_fn(void);
void gen_addr(Node *node);
void load(Type *ty);
void push_xmm(int x);
void pop_xmm(int x);
void push_ymm(int x);
void pop_ymm(int x);
void push_vec(Type *ty);
void pop_vec(Type *ty, int reg);
void pushv(void);
void popv(int reg);
void push_tmpf(void);
void pop_tmpf(int reg);
void pushld(void);
void popld(void);
int vec_use_ymm(Type *ty);

extern bool dont_reuse_stack;
extern char *lvar_ptr;
extern int depth;

//
// builtin.c
//

void gen_builtin_alloca(Node *node);
void gen_memset(Node *node);
void gen_memcpy(Node *node);
void gen_builtin_single(Node *node, const char *insn, const char *reg);
void gen_builtin_stdc_bit_ceil(Node *node);
void gen_add_overflow(Node *node);
void gen_sub_overflow(Node *node);
void gen_mul_overflow(Node *node);
void gen_umul_overflow(Node *node);
void gen_uadd_overflow(Node *node);
void gen_alloc(Node *node);
void gen_prefetch(Node *node);
void gen_builtin_clz(Node *node);
void gen_builtin_clzl(Node *node);
void gen_builtin_bswap16(Node *node);
void gen_builtin_bswap32(Node *node);
void gen_builtin_bswap64(Node *node);
void gen_builtin_frame_address(Node *node);
void gen_builtin_expect(Node *node);
void gen_builtin_abort(Node *node);
void gen_builtin_return_address(Node *node);
void gen_builtin_isnan(Node *node);
void gen_builtin_nanf(Node *node);
void gen_builtin_nan(Node *node);
void gen_builtin_nanl(Node *node);
void gen_tzcnt_u16(Node *node);
void gen_bextr_u32(Node *node);
void gen_bextr_u64(Node *node);
void gen_binop1(Node *node, const char *insn);
void gen_binop2(Node *node, const char *insn);
void gen_nothing(Node *node);
void gen_singleop(Node *node, const char *insn);
void gen_fetchadd(Node *node);
void gen_add_fetch(Node *node);
void gen_sub_fetch(Node *node);
void gen_fetchsub(Node *node);
void gen_crc32qi(Node *node);
void gen_crc32di(Node *node);
void gen_crc32hi(Node *node);
void gen_crc32si(Node *node);
void gen_release(Node *node);
void gen_rdtsc(Node *node);
void gen_rdpkru(Node *node);
void gen_bsrsi(Node *node);
void gen_bsrdi(Node *node);
void gen_rdpmc(Node *node);
void gen_rdtscp(Node *node);
void gen_rolqi(Node *node);
void gen_rorqi(Node *node);
void gen_rolhi(Node *node);
void gen_rorhi(Node *node);
void gen_readeflags_u64(Node *node);
void gen_writeeflags_u64(Node *node);
void gen_incsspq(Node *node);
void gen_rstorssp(Node *node);
void gen_wrssd(Node *node);
void gen_wrssq(Node *node);
void gen_wrussd(Node *node);
void gen_wrussq(Node *node);
void gen_clrssbsy(Node *node);
void gen_sbb_u32(Node *node);
void gen_sbb_u64(Node *node);
void gen_addcarryx_u32(Node *node);
void gen_addcarryx_u64(Node *node);
void gen_cas(Node *node);
void gen_bool_cas(Node *node);
void gen_add_and_fetch(Node *node);
void gen_sub_and_fetch(Node *node);
void gen_fetchnand(Node *node);
void gen_cas_n(Node *node);
void gen_single_binop(const char *insn);
void gen_cvt_binop(Node *node, const char *insn);
void gen_atomic_is_lock_free(Node *node);
void gen_store_binop(Node *node, const char *insn);
void gen_loadlps(Node *node);
void gen_stmxcsr(Node *node);
void gen_single_addr_binop(Node *node, const char *insn);
void gen_parity(Node *node);
void gen_mwait(Node *node);
void gen_monitor(Node *node);
void gen_movq128(Node *node);
void gen_movnti(Node *node);
void gen_movnti64(Node *node);
void gen_movnt_binop(Node *node, const char *insn);
void gen_movntdqa(Node *node);
void gen_sse_binop1(Node *node, const char *insn, bool rhs_is_imm);
void gen_sse_binop2(Node *node, const char *insn, const char *reg, bool rhs_is_imm);
void gen_sse_binop3(Node *node, const char *insn, bool rhs_is_imm);
void gen_sse_binop4(Node *node, const char *insn, const char *insn2);
void gen_sse_binop5(Node *node, const char *insn, const char *insn2);
void gen_sse_binop6(Node *node, const char *insn, const char *insn2);
void gen_sse_binop7(Node *node, const char *insn);
void gen_sse_binop8(Node *node, const char *insn, const char *reg);
void gen_sse_binop9(Node *node, const char *insn);
void gen_sse_binop10(Node *node, const char *insn, const char *reg);
void gen_sse_binop11(Node *node, const char *insn, const char *reg);
void gen_sse_binop12(Node *node, const char *insn);
void gen_lddqu(Node *node);
void gen_signbit(Node *node);
void gen_isunordered(Node *node);
void gen_vec_init_v2si(Node *node);
void gen_vec_ext(Node *node);
void gen_vec_ext_v4sf(Node *node);
void gen_vec_set_v4hi(Node *node);
void gen_vec_set_v8hi(Node *node);
void gen_vec_set_v16qi(Node *node);
void gen_vec_set_v4si(Node *node);
void gen_vec_set_v2di(Node *node);
void gen_psubusb256(Node *node);
void gen_vec_init_binop(Node *node, const char *insn);
void gen_pshufd(Node *node);
void gen_pshufhw(Node *node);
void gen_pshuflw(Node *node);
void gen_pshufw(Node *node);
void gen_shuf_binop(Node *node, const char *insn);
void gen_round(Node *node, const char *insn);
void gen_psll_binop(Node *node, const char *insn);
void gen_shuffle(Node *node, const char *insn);
void gen_maskmovq(Node *node);
void gen_maskmovdqu(Node *node);
void gen_cvtpi2ps(Node *node);
void gen_loadhps(Node *node);
void gen_packss128_binop(Node *node, const char *insn);
void gen_sse_pblendvb128(Node *node);
void gen_pblendvb256(Node *node);
void gen_sse_blendvpx(Node *node, const char *insn);
void gen_pcmpgtb256_mask(Node *node);
void gen_pshufb256(Node *node);
void gen_avx2_256(Node *node, const char *insn);
void gen_sse2_dqshift(Node *node, const char *insn);
void gen_vinsertf128_si256(Node *node);
void gen_avx2_permdi256(Node *node);
void gen_avx2_psll_binop(Node *node, const char *insn);
void gen_palignr128(Node *node);
void gen_avx2_palignr256(Node *node);
void gen_palignr(Node *node);
void gen_vperm2i128_si256(Node *node);
void gen_pblendd256(Node *node);
void gen_pmulhuw256(Node *node);
void gen_andnotsi256(Node *node);
void gen_vextractf128_si256(Node *node);
void gen_si256(Node *node);
void gen_cvt_mmx_binop(Node *node, const char *insn);
void gen_cvt_sse_binop2(Node *node, const char *insn, const char *reg, bool is_address);
void gen_cvt_mmx_binop3(Node *node, const char *insn);
void gen_cvt_mmx_binop4(Node *node, const char *insn);
void gen_mmx_binop(Node *node, const char *insn, bool rhs_is_imm);
void gen_mmx_binop1(Node *node, const char *insn);
void gen_sse_testz(Node *node);
void gen_sse_testc(Node *node);
void gen_sse_testnzc(Node *node);
void gen_blendps(Node *node, bool is256);
void gen_blendpd(Node *node, bool is256);
void gen_dpps(Node *node);
void gen_dppd(Node *node);
void gen_insertps128(Node *node);
void gen_mpsadbw128(Node *node);
void gen_mpsadbw256(Node *node);
void gen_pcmpistrm128(Node *node);
void gen_pcmpistri128(Node *node);
void gen_pcmpestrm128(Node *node);
void gen_pcmpestri128(Node *node);
void gen_pclmulqdq128(Node *node);
void gen_pcmpi_flag(Node *node, const char *flag_insn, bool is_explicit);
void gen_dpps256(Node *node);
void gen_shufpd256(Node *node);
void gen_shufps256(Node *node);
void gen_avx_cmp(Node *node, const char *insn, bool is256);
void gen_vextractf128_pd256(Node *node);
void gen_vextractf128_ps256(Node *node);
void gen_vinsertf128_pd256(Node *node);
void gen_vinsertf128_ps256(Node *node);
void gen_vperm2f128_si256(Node *node);
void gen_vperm2f128_pd256(Node *node);
void gen_vperm2f128_ps256(Node *node);
void gen_vpermilpd(Node *node);
void gen_vpermilps(Node *node);
void gen_vpermilpd256(Node *node);
void gen_vpermilps256(Node *node);
void gen_xabort(Node *node);
void gen_vpclmulqdq_v4di(Node *node);
void gen_avx512er_first(Node *node);
void gen_avx512pf_void(Node *node);
void gen_vbmi2_3(Node *node);
void gen_vbmi2_5(Node *node);
void gen_pblendw128(Node *node);

//
// unicode.c
//

int encode_utf8(char *buf, uint32_t c);
uint32_t decode_utf8(char **new_pos, char *p);
bool is_ident1(uint32_t c);
bool is_ident2(uint32_t c);
int display_width(char *p, int len);

//
// hashmap.c
//

typedef struct
{
  char *key;
  int keylen;
  void *val;
} HashEntry;

typedef struct
{
  HashEntry *buckets;
  int capacity;
  int used;
} HashMap;

void *hashmap_get(HashMap *map, char *key);
void *hashmap_get2(HashMap *map, char *key, int keylen);
void hashmap_put(HashMap *map, char *key, void *val);
void hashmap_put2(HashMap *map, char *key, int keylen, void *val);
void hashmap_delete(HashMap *map, char *key);
void hashmap_delete2(HashMap *map, char *key, int keylen);
void hashmap_test(void);

// Scope tree - represents nested block scopes for variables/tags.
// `parent` points to the enclosing scope (outer scope).
// `children`/`sibling_next` links child scopes at the same nesting level.
// `locals` is the linked list of Obj variables declared in this scope.
struct Scope
{
  Scope *parent;
  Scope *children;
  Scope *sibling_next;
  Obj *locals;
  HashMap vars;
  HashMap tags;
};

//
// main.c
//
typedef enum {
  // ISO modes
  STD_C89,
  STD_C99,
  STD_C11,
  STD_C17,
  STD_C23,
  // GNU modes
  STD_GNU89,
  STD_GNU99,    
  STD_GNU11,
  STD_GNU17,
  STD_GNU23,
} Standard;


bool file_exists(char *path);
void dump_machine(void);
void dump_version(void);
bool startsWith(const char *restrict string, const char *restrict prefix);

extern StringArray include_paths;
extern bool opt_fpic;
extern bool opt_fpie;
extern bool opt_shared;
extern bool opt_fcommon;
extern char *base_file;
extern char *dot_file;
extern char *opt_o;
extern char *replace_extn(char *tmpl, char *extn);
extern FILE *dotf;
extern FILE *f;
extern bool isDotfile;
extern bool isDebug;
extern bool printTokens;
extern bool isPrintMacro;
extern char *extract_filename(char *tmpl);
extern char *extract_path(char *tmpl);
extern bool opt_sse;
extern bool opt_sse2;
extern bool opt_sse3;
extern bool opt_sse4;
extern bool opt_mmx;
extern bool opt_crc32;
extern bool opt_g;
extern FILE *open_file(char *path);
extern FILE *ofile;
extern Standard current_std;
extern char *weak_symbols[MAX_WEAK]; 
extern int weak_count;
extern bool opt_implicit;
extern bool opt_werror;
extern bool opt_optimize;
extern bool opt_optimize_level1;
extern bool opt_optimize_level2;
extern bool opt_optimize_level3;
extern bool opt_omit_frame_pointer;
extern bool opt_avx2;
extern bool opt_avx;
extern bool opt_tbm;
extern char *opt_fvisibility;
extern bool opt_implicit_warn;
extern bool opt_no_implicit;
extern bool opt_ffreestanding;

//
// extended_asm.c
//

char *extended_asm(Node *node, Token **rest, Token *tok, Obj *locals, Obj *current_fn);
void output_asm(Node *node, Token **rest, Token *tok, Obj *locals);
void input_asm(Node *node, Token **rest, Token *tok, Obj *locals);
char *subst_asm(char *template, char *output_str, char *input_str);
char *string_replace(char *str, char *oldstr, char *newstr);
char *generate_input_asm(char *input_str);
bool check_template(char *template);
int search_output_index(char c);
char *int_to_string(int i);
void update_offset(char *funcname, Obj *locals);
char *load_variable(int order);
char *subst_fp_placeholder(const char *asm_str, const char *fp);
char *generate_output_asm(char *output_str);
char *opcode(int size);
char *update_register_size(char *reg, int size);
char *retrieve_output_index_str(char letter);
int retrieve_output_index_from_letter(char letter);
char *retrieveVariableNumber(int index);
char *generate_input_for_output(void);
char *generate_return_rax(Token *retval);
