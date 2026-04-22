// This file contains a recursive descent parser for C.
//
// Most functions in this file are named after the symbols they are
// supposed to read from an input token list. For example, stmt() is
// responsible for reading a statement from a token list. The function
// then construct an AST node representing a statement.
//
// Each function conceptually returns two values, an AST node and
// remaining part of the input tokens. Since C doesn't support
// multiple return values, the remaining tokens are returned to the
// caller via a pointer argument.
//
// Input tokens are represented by a linked list. Unlike many recursive
// descent parsers, we don't have the notion of the "input token stream".
// Most parsing functions don't change the global state of the parser.
// So it is very easy to lookahead arbitrary number of tokens in this
// parser.

#include "chibicc.h"



// Scope for local variables, global variables, typedefs
// or enum constants

// Represents a block scope.
typedef struct Scope Scope;
struct Scope
{
  Scope *next;

  // C has two block scopes; one is for variables/typedefs and
  // the other is for struct/union/enum tags.
  HashMap vars;
  HashMap tags;
};
typedef struct VarAttr VarAttr;
// Variable attributes such as typedef or extern.
struct VarAttr
{
  bool is_typedef;
  bool is_static;
  bool is_extern;
  bool is_inline;
  bool is_tls;
  int align;
  int min_vector_width;
    //from COSMOPOLITAN adding some attributes
  bool is_weak;
  bool is_ms_abi;
  bool is_aligned;
  bool is_noreturn;
  bool is_destructor;
  bool is_constructor;
  bool is_externally_visible;
  bool is_no_instrument_function;
  bool is_force_align_arg_pointer;
  bool is_no_caller_saved_registers;
  char *section;
  char *visibility;
  char *alias_name; //to store alias name for function when weak attribute
  int destructor_priority;
  int constructor_priority;
  bool is_packed;
};


// For local variable initializer.
typedef struct InitDesg InitDesg;
struct InitDesg
{
  InitDesg *next;
  int idx;
  Member *member;
  Obj *var;
};


typedef struct {
    const char *name;
    int node_kind;
} BuiltinEntry;


static int nbFunc = 0;
static Type* ArrayType[50][50];
static Token* ArrayToken[50][50];
static Token* ArrayTokenOrder[50][50];
static int ArrayTokenOrderCount[50];
static int order = 0;
static bool is_old_style = false;
static Type * current_type;
static VarAttr * current_attr;
// All local variable instances created during parsing are
// accumulated to this list.
static Obj *locals;
static char* current_section;

// Likewise, global variables are accumulated to this list.
static Obj *globals;

static Scope *scope = &(Scope){};

// Points to the function object the parser is currently parsing.
static Obj *current_fn;

// Lists of all goto statements and labels in the curent function.
static Node *gotos;
static Node *labels;

// Current "goto" and "continue" jump targets.
static char *brk_label;
static char *cont_label;

// Points to a node representing a switch if we are parsing
// a switch statement. Otherwise, NULL.
static Node *current_switch;

static Obj *builtin_alloca;
DebugTypedef *debug_typedefs;

extern Context *ctx;

static bool is_typename(Token *tok);
static Type *declspec(Token **rest, Token *tok, VarAttr *attr);
static Type *typename(Token **rest, Token *tok);
static Type *enum_specifier(Token **rest, Token *tok);
static Type *typeof_specifier(Token **rest, Token *tok);
static Type *type_suffix(Token **rest, Token *tok, Type *ty);
static Type *declarator(Token **rest, Token *tok, Type *ty);
static Node *declaration(Token **rest, Token *tok, Type *basety, VarAttr *attr);
static void array_initializer2(Token **rest, Token *tok, Initializer *init, int i);
static void struct_initializer2(Token **rest, Token *tok, Initializer *init, Member *mem, bool post_desig);
static void initializer2(Token **rest, Token *tok, Initializer *init);
static Initializer *initializer(Token **rest, Token *tok, Type *ty, Type **new_ty);
static Node *lvar_initializer(Token **rest, Token *tok, Obj *var);
static void gvar_initializer(Token **rest, Token *tok, Obj *var);
static Node *compound_stmt(Token **rest, Token *tok, Node **last);
static Node *stmt(Token **rest, Token *tok, bool chained);
static Node *expr_stmt(Token **rest, Token *tok);
static Node *expr(Token **rest, Token *tok);
//static int64_t eval(Node *node);
static int64_t eval2(Node *node, char ***label);
static int64_t eval_rval(Node *node, char ***label);
static bool is_const_expr(Node *node);
static Node *assign(Token **rest, Token *tok);
static Node *logor(Token **rest, Token *tok);
static long double eval_double(Node *node);
static Node *conditional(Token **rest, Token *tok);
static Node *logand(Token **rest, Token *tok);
static Node * bitor (Token * *rest, Token *tok);
static Node *bitxor(Token **rest, Token *tok);
static Node *bitand(Token **rest, Token *tok);
static Node *equality(Token **rest, Token *tok);
static Node *relational(Token **rest, Token *tok);
static Node *shift(Token **rest, Token *tok);
static Node *add(Token **rest, Token *tok);
static Node *new_add(Node *lhs, Node *rhs, Token *tok, bool is_op);
static Node *new_sub(Node *lhs, Node *rhs, Token *tok, bool is_op);
static Node *mul(Token **rest, Token *tok);
static Node *cast(Token **rest, Token *tok);
static Member *get_struct_member(Type *ty, Token *tok);
static Type *struct_decl(Token **rest, Token *tok);
static Type *union_decl(Token **rest, Token *tok);
static Node *postfix(Token **rest, Token *tok);
static Node *funcall(Token **rest, Token *tok, Node *node);
static Node *unary(Token **rest, Token *tok);
static Node *primary(Token **rest, Token *tok);
static Node *parse_typedef(Token **rest, Token *tok, Type *basety, VarAttr *attr);
static bool is_function(Token *tok);
static Token *function(Token *tok, Type *basety, VarAttr *attr);
static Token *global_declaration(Token *tok, Type *basety, VarAttr *attr);
//static void initializer3(Token **rest, Token *tok, Initializer *init);
//from COSMOPOLITAN adding attribute for variable
static Node *visit_all_vla(Node *node, Token *tok);
static Node *sizeof_vla_type(Type *ty, Token *tok);
static Token *thing_attributes(Token *tok, void *arg);
static Token *attribute_list(Token *tok, void *arg, Token *(*f)(Token *, void *));
static Token *type_attributes(Token *tok, void *arg);
static Token *static_assertion(Token *tok);
//managing old C style function definition
static bool check_old_style(Token **rest, Token *tok);

//from cosmopolitan managing builtin functions
static Node *ParseAtomic2(NodeKind kind, Token *tok, Token **rest);
static Node *ParseAtomic3(NodeKind kind, Token *tok, Token **rest);
static Node *ParseAtomicCompareExchangeN(NodeKind kind, Token *tok, Token **rest);
static Node *ParseSyncBoolCAS(NodeKind kind, Token *tok, Token **rest);

//for builtin functions
static Node *parse_memcpy(Token *tok, Token **rest);
static Node *parse_memset(Token *tok, Token **rest);
static Node *ParseBuiltin(NodeKind kind, Token *tok, Token **rest);
static Node *parse_overflow(NodeKind kind, Token *tok, Token **rest);
static Node *parse_huge_val(double fval, Token *tok, Token **rest);

static Token * old_style_params(Token **rest, Token *tok, Type *ty);
static Type *old_params(Type *ty, int nbparms);

//from @fuhsnn
static int64_t eval_sign_extend(Type *ty, uint64_t val);
static bool is_const_var(Obj *var);
static int64_t eval_rval(Node *node, char ***label);
static Obj *eval_var(Node *expr, bool allow_local);
static Obj *find_global_by_name(char *name);
static bool is_const_var(Obj *var) ;
static bool is_str_tok(Token **rest, Token *tok, Token **str_tok);

static Node *compound_stmt2(Token **rest, Token *tok);
static int builtin_enum(Token *tok);
static Node *scalar_to_vector(Node *scalar, Type *vec_ty);
static void promote_scalar_to_vector(Node *node);
static char *token_to_string(Token *tok);
static Node *ParseAtomicFetch(NodeKind kind, Token *tok, Token **rest);
static Node *ParseSyncFetch(NodeKind kind, Token *tok, Token **rest);
static Node *ParseAtomicBitwise(NodeKind kind, Token *tok, Token **rest);
static Node *ParseAtomicFence(NodeKind kind, Token *tok, Token **rest);
static Node *ParseAtomicClear(NodeKind kind, Token *tok, Token **rest);
static Token *skip_choose_expr_arg(Token *tok);
static bool is_c99_or_later(void) ;
Obj *find_func(char *name);
static Node *new_node(NodeKind kind, Token *tok);
static Node *new_unary(NodeKind kind, Node *expr, Token *tok);
static Node *new_var_node(Obj *var, Token *tok);
static Obj *new_gvar(char *name, Type *ty);
static Obj *new_lvar(char *name, Type *ty, char *funcname);
static Node *new_binary(NodeKind kind, Node *lhs, Node *rhs, Token *tok);
static Node *compute_vla_size(Type *ty, Token *tok);

static int align_down(int n, int align)
{
    return (n / align) * align;
}

static void enter_scope(void)
{

  Scope *sc = calloc(1, sizeof(Scope));
  if (sc == NULL)
    error("%s:%d: in enter_scope : sc pointer is null!", __FILE__, __LINE__ );
  sc->next = scope;
  scope = sc;
}

static void leave_scope(void)
{
  scope = scope->next;
}

// Find a variable by name.
VarScope *find_var(Token *tok)
{

  for (Scope *sc = scope; sc; sc = sc->next)
  {

    VarScope *sc2 = hashmap_get2(&sc->vars, tok->loc, tok->len);

    if (sc2)
      return sc2;
   
  }
  


  return NULL;
}

static Type *find_tag(Token *tok)
{
  for (Scope *sc = scope; sc; sc = sc->next)
  {
    Type *ty = hashmap_get2(&sc->tags, tok->loc, tok->len);
    if (ty)
      return ty;
  }
  return NULL;
}

static Node *new_node(NodeKind kind, Token *tok)
{
  static int count = 0;
  Node *node = calloc(1, sizeof(Node));
  if (node == NULL)
    error("%s:%d: error: in new_node : node is null", __FILE__, __LINE__);
  node->kind = kind;
  node->unique_number = count++;
  node->tok = tok;
  return node;
}

static Node *new_binary(NodeKind kind, Node *lhs, Node *rhs, Token *tok)
{
  Node *node = new_node(kind, tok);
  if (isDotfile && dotf != NULL)
  {
    fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(rhs->kind), rhs->unique_number);
    fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(lhs->kind), lhs->unique_number);
  }

  node->lhs = lhs;
  node->rhs = rhs;
  add_type(node->rhs);
  if (kind == ND_ASSIGN && node->rhs->ty->kind == TY_VOID  )
  {
    error_tok(node->rhs->tok, "%s:%d: in new_binary : Cannot assign void type expression", __FILE__, __LINE__);
  }

  // TODO type check other binary expressions, e.g., ND_ADD
  return node;
}

static Node *new_unary(NodeKind kind, Node *expr, Token *tok)
{
  Node *node = new_node(kind, tok);

  if (isDotfile && dotf != NULL)
    fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(expr->kind), expr->unique_number);
  node->lhs = expr;
  add_type(node->lhs);
  return node;
}

static Node *new_double(double fval, Token *tok)
{
  Node *node = new_node(ND_NUM, tok);
  node->fval = fval;
  node->ty = ty_double;
  return node;
}

static Node *new_num(int64_t val, Token *tok)
{
  Node *node = new_node(ND_NUM, tok);
  node->val = val;
  return node;
}

static Node *new_long(int64_t val, Token *tok)
{
  Node *node = new_node(ND_NUM, tok);
  node->val = val;
  node->ty = ty_long;
  return node;
}

static Node *new_ulong(long val, Token *tok)
{
  Node *node = new_node(ND_NUM, tok);
  node->val = val;
  node->ty = ty_ulong;
  return node;
}

static Node *new_boolean(bool val, Token *tok) {
  Node *node = new_node(ND_NUM, tok);
  node->val = val;
  node->ty = ty_bool;
  return node;
}

static Node *new_var_node(Obj *var, Token *tok)
{
  Node *node = new_node(ND_VAR, tok);
  node->var = var;
  return node;
}

static Node *new_vla_ptr(Obj *var, Token *tok)
{

  Node *node = new_node(ND_VLA_PTR, tok);
  node->var = var;
  return node;
}

Node *new_cast(Node *expr, Type *ty)
{
  //fix for case when cast has __attribute__
  add_type(expr);
  ty = unqual(ty);

  Node *node = calloc(1, sizeof(Node));
  if (node == NULL)
    error("%s:%d: error: in new_cast : node is null", __FILE__, __LINE__);
  node->kind = ND_CAST;
  node->tok = expr->tok;
  node->lhs = expr;
  if (!ty)
    error("%s:%d: error: in new_cast : type is null", __FILE__, __LINE__);
  node->ty = copy_type(ty);
  return node;
}

static void apply_cv_qualifier(Node *node, Type *ty2) {
  add_type(node);
  Type *ty = node->ty;
  if (ty->is_const < ty2->is_const || ty->is_volatile < ty2->is_volatile) {
    node->ty = new_qualified_type(ty);
    node->ty->is_const = ty->is_const | ty2->is_const;
    node->ty->is_volatile = ty->is_volatile | ty2->is_volatile;
  }
}

//force cast to bool commit slimcc 2e138bb
Node *to_bool(Node *expr) {
  return new_cast(expr, ty_bool);
}

static VarScope *push_scope(char *name)
{
  VarScope *sc = calloc(1, sizeof(VarScope));
  if (sc == NULL)
    error("%s:%d: error: in push_scope : sc is null!", __FILE__, __LINE__);

  hashmap_put(&scope->vars, name, sc);
  return sc;
}

static Initializer *new_initializer(Type *ty, bool is_flexible)
{
  Initializer *init = calloc(1, sizeof(Initializer));
  if (init == NULL)
    error("%s:%d: error: in new_initializer : init is null", __FILE__, __LINE__);
  init->ty = ty;

  if (ty->kind == TY_ARRAY)
  {
    if (is_flexible && (ty->size < 0 || ty->array_len < 0))
    {
      init->is_flexible = true;
      return init;
    }

    init->children = calloc(ty->array_len, sizeof(Initializer *));
    if (init->children == NULL)
      error("%s:%d: error: in new_initializer : init->children is null %ld %ld", __FILE__, __LINE__, ty->array_len, ty->size);
    for (int i = 0; i < ty->array_len; i++)
      init->children[i] = new_initializer(ty->base, false);
    return init;
  }

  
  if (ty->kind == TY_VECTOR)
  {

    init->children = calloc(ty->array_len, sizeof(Initializer *));
    if (init->children == NULL)
      error("%s:%d: error: in new_initializer : init->children is null %ld %ld", __FILE__, __LINE__, ty->array_len, ty->size);
    for (int i = 0; i < ty->array_len; i++)
      init->children[i] = new_initializer(ty->base, false);
    return init;
  }

  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION)
  {
    // Count the number of struct members.
    int len = 0;
    for (Member *mem = ty->members; mem; mem = mem->next)
      mem->idx = len++;


    init->children = calloc(len, sizeof(Initializer *));
    if (init->children == NULL)
      error("%s:%d: error: in new_initializer : init->children is null (bis)", __FILE__, __LINE__);
    for (Member *mem = ty->members; mem; mem = mem->next)
    {
      if (is_flexible && ty->is_flexible && !mem->next)
      {
        Initializer *child = calloc(1, sizeof(Initializer));
        if (child == NULL)
          error("%s:%d: error: in new_initializer : child is null", __FILE__, __LINE__);
        child->ty = mem->ty;
        child->is_flexible = true;
        init->children[mem->idx] = child;
      }
      else
      {

        init->children[mem->idx] = new_initializer(mem->ty, false);
      }
    }
    return init;
  }

  return init;
}

static Obj *new_var(char *name, Type *ty)
{

  Obj *var = calloc(1, sizeof(Obj));
  if (var == NULL)
    error("%s:%d: error: in new_var : var is null", __FILE__, __LINE__);
  var->name = name;
  var->ty = ty;
  var->align = ty->align;
  push_scope(name)->var = var;
  return var;
}

static Obj *new_lvar(char *name, Type *ty, char *funcname)
{

  Obj *var = new_var(name, ty);
  var->is_local = true;
  var->order = order;
  var->ptr = "%rbp";  // default, may be overridden by codegen
  var->is_weak = ty->is_weak;
  if (!funcname && current_fn)
    funcname = current_fn->funcname;
  var->funcname = funcname;
  if (var->ty->kind == TY_PTR) {
    var->ty->is_pointer = true;
    var->ty->pointertype = ty->base;   
    var->ty->size = ty->size; 
  }
  var->next = locals;
  locals = var;
  return var;
}

static Obj *new_gvar(char *name, Type *ty)
{
  Obj *var = new_var(name, ty);
  var->next = globals;
  var->is_static = true;
  var->is_definition = true;
  globals = var;
  return var;
}

static char *new_unique_name(void)
{
  static int id = 0;
  return format(".L..%d", id++);
}

static Obj *new_anon_gvar(Type *ty)
{
  return new_gvar(new_unique_name(), ty);
}

static Obj *new_string_literal(char *p, Type *ty)
{
  Obj *var = new_anon_gvar(ty);
  var->init_data = p;
  return var;
}

static char *get_ident(Token *tok)
{
  if (tok->kind != TK_IDENT)
    error_tok(tok, "%s:%d: in get_ident : expected an identifier", __FILE__, __LINE__);
  return strndup(tok->loc, tok->len);
}

static void record_debug_typedef(Token *tok, Type *ty) {
  DebugTypedef *entry = calloc(1, sizeof(DebugTypedef));
  entry->name = get_ident(tok);
  entry->ty = ty;
  entry->next = debug_typedefs;
  debug_typedefs = entry;
}

static Type *find_typedef(Token *tok)
{

  if (tok->kind == TK_IDENT)
  {
    VarScope *sc = find_var(tok);
    if (sc) {
      if (sc->type_def)
        return sc->type_def;
    }
  }
  return NULL;
}

static void push_tag_scope(Token *tok, Type *ty)
{
  ty->tag = tok;
  hashmap_put2(&scope->tags, tok->loc, tok->len, ty);
}

// declspec = ("void" | "_Bool" | "char" | "short" | "int" | "long" | "double"
//             | "typedef" | "static" | "extern" | "inline"
//             | "_Thread_local" | "__thread"
//             | "signed" | "unsigned"
//             | struct-decl | union-decl | typedef-name
//             | enum-specifier | typeof-specifier
//             | "const" | "volatile" | "auto" | "register" | "restrict"
//             | "__restrict" | "__restrict__" | "_Noreturn" | )+
// The order of typenames in a type-specifier doesn't matter. For
// example, `int long static` means the same as `static long int`.
// That can also be written as `static long` because you can omit
// `int` if `long` or `short` are specified. However, something like
// `char int` is not a valid type specifier. We have to accept only a
// limited combinations of the typenames.
//
// In this function, we count the number of occurrences of each typename
// while keeping the "current" type object that the typenames up
// until that point represent. When we reach a non-typename token,
// we returns the current type object.
static Type *declspec(Token **rest, Token *tok, VarAttr *attr)
{
  // We use a single integer as counters for all typenames.
  // For example, bits 0 and 1 represents how many times we saw the
  // keyword "void" so far. With this, we can use a switch statement
  // as you can see below.
  enum
  {
    VOID = 1 << 0,
    BOOL = 1 << 2,
    CHAR = 1 << 4,
    SHORT = 1 << 6,
    INT = 1 << 8,
    LONG = 1 << 10,
    FLOAT = 1 << 12,
    DOUBLE = 1 << 14,
    OTHER = 1 << 16,
    SIGNED = 1 << 17,
    UNSIGNED = 1 << 18,
    INT128 = 1 << 19,
  };

  Type *ty = copy_type(ty_int);  
  int counter = 0;
  bool is_atomic = false;
  bool is_const = false;
  bool is_restrict = false;
  bool is_volatile = false;
  
  while (is_typename(tok))
  {
    if (attr)
      current_attr = attr;
    tok = attribute_list(tok, ty, type_attributes);
    current_attr = NULL;
    //fixing =====ISS-155 __label__ out;  
    if (equal(tok, "__label__")) {
      consume(&tok, tok, "__label__");
      //skip the label identifier
      tok = tok->next;
      SET_CTX(ctx); 
      tok = skip(tok, ";", ctx);
    }


    // Handle storage class specifiers.
    if (equal(tok, "typedef") || equal(tok, "static") || equal(tok, "extern") || equal(tok, "__inline") ||
        equal(tok, "inline") || equal(tok, "_Thread_local") || equal(tok, "__thread"))
    {
      
      if (!attr) 
        error_tok(tok, "%s:%d: in declspec : storage class specifier is not allowed in this context", __FILE__, __LINE__);

      if (equal(tok, "typedef"))
        attr->is_typedef = true;
      else if (equal(tok, "static"))
        attr->is_static = true;
      else if (equal(tok, "extern"))
        attr->is_extern = true;
      else if (equal(tok, "inline") || equal(tok, "__inline"))
        attr->is_inline = true;
      else if (equal(tok, "_Thread_local") || equal(tok, "__thread"))
        attr->is_tls = true;
      else        
        error_tok(tok, "%s:%d: in declspec : unknown storage class specifier", __FILE__, __LINE__);

      //fixing  check for typedef specifier/attribute not strict enough #142 suggested by @samkho
      if (attr->is_typedef &&
          attr->is_static + attr->is_extern + attr->is_inline + attr->is_tls >= 1)
        error_tok(tok, "%s:%d: in declspec : typedef may not be used together with static,"
                       " extern, inline, __thread or _Thread_local",
                  __FILE__, __LINE__);

      tok = tok->next;
        //from COSMOPOLITAN adding other GNUC attributes
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }

    // These keywords are recognized but ignored.
    // fixing issue #119 _Complex
    if (consume(&tok, tok, "auto") || consume(&tok, tok, "register") ||
        consume(&tok, tok, "_Complex") ||  consume(&tok, tok, "_Noreturn")) {
        tok = attribute_list(tok, attr, thing_attributes);
        continue;
    }
    
    if (consume(&tok, tok, "const")) {
      is_const = true;
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }
    if (consume(&tok, tok, "volatile")) {
      is_volatile = true;
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }

    if (consume(&tok, tok, "restrict") || consume(&tok, tok, "__restrict") || consume(&tok, tok, "__restrict__")) {
      is_restrict = true;
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }

    if (equal(tok, "_Atomic"))
    {
      tok = tok->next;
      if (equal(tok, "("))
      {
        ty = typename(&tok, tok->next);
        SET_CTX(ctx); 
        tok = skip(tok, ")", ctx);
      }
      is_atomic = true;
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }

    if (equal(tok, "_Alignas"))
    {
      if (!attr)
        error_tok(tok, "%s:%d: in declspec : _Alignas is not allowed in this context", __FILE__, __LINE__);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      int align;
      if (is_typename(tok))
        align = typename(&tok, tok)->align;
      else
        align = const_expr(&tok, tok);
      attr->align = MAX(attr->align, align);   
   
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }

     
    if (attr && attr->is_typedef) {
      tok = attribute_list(tok, ty, type_attributes);
    } else if (attr) {
      tok = attribute_list(tok, attr, thing_attributes);
    }

    // Handle user-defined types.
    Type *ty2 = find_typedef(tok);
    if (attr)
      current_attr = attr;
    tok = attribute_list(tok, ty2, type_attributes);
    current_attr = NULL;
    if (equal(tok, "struct") || equal(tok, "union") || equal(tok, "enum") ||
        equal(tok, "typeof") || equal(tok, "__typeof") || ty2)
    {
      if (counter)
        break;

      if (equal(tok, "struct"))
      {
        ty = struct_decl(&tok, tok->next);        
      }
      else if (equal(tok, "union"))
      {
        ty = union_decl(&tok, tok->next);
      }
      else if (equal(tok, "enum"))
      {
        ty = enum_specifier(&tok, tok->next);
      }
      else if (equal(tok, "typeof") || equal(tok, "__typeof"))
      {
        ty = typeof_specifier(&tok, tok->next);
      }
      else
      {
        ty = ty2;
        tok = tok->next;

      }

      counter += OTHER;
      tok = attribute_list(tok, attr, thing_attributes);
      continue;
    }

    // Handle built-in types.
    if (equal(tok, "void"))
      counter += VOID;
    else if (equal(tok, "_Bool"))
      counter += BOOL;
    else if (equal(tok, "char"))
      counter += CHAR;
    else if (equal(tok, "short"))
      counter += SHORT;
    else if (equal(tok, "int"))
      counter += INT;
    else if (equal(tok, "long"))
      counter += LONG;
    else if (equal(tok, "float"))
      counter += FLOAT;
    else if (equal(tok, "double"))
      counter += DOUBLE;
    else if (equal(tok, "__int128"))
      counter += INT128;        
    else if (equal(tok, "signed"))
      counter |= SIGNED;
    else if (equal(tok, "unsigned"))
      counter |= UNSIGNED;
    else
      unreachable();

    switch (counter)
    {
    case VOID:
      ty = copy_type(ty_void);
      break;
    case BOOL:
      ty = copy_type(ty_bool);
      break;
    case CHAR:
    case SIGNED + CHAR:
      ty = copy_type(ty_char);
      break;
    case UNSIGNED + CHAR:
      ty = copy_type(ty_uchar);
      break;
    case SHORT:
    case SHORT + INT:
    case SIGNED + SHORT:
    case SIGNED + SHORT + INT:
      ty = copy_type(ty_short);
      break;
    case UNSIGNED + SHORT:
    case UNSIGNED + SHORT + INT:
      ty = copy_type(ty_ushort);
      break;
    case INT:
    case SIGNED:
    case SIGNED + INT:
      ty = copy_type(ty_int);
      break;
    case INT128:
    case SIGNED + INT128:
      ty = copy_type(ty_int128);
      break;         
    case UNSIGNED:
    case UNSIGNED + INT:
      ty = copy_type(ty_uint);
      break;
    case LONG:
    case LONG + INT:
    case SIGNED + LONG:
    case SIGNED + LONG + INT:
      ty = copy_type(ty_long);
      break;
    case LONG + LONG:
    case LONG + LONG + INT:      
    case SIGNED + LONG + LONG:
    case SIGNED + LONG + LONG + INT:
      ty = copy_type(ty_llong);
      break;
    case UNSIGNED + LONG:
    case UNSIGNED + LONG + INT:
      ty = copy_type(ty_ulong);
      break;
    case UNSIGNED + LONG + LONG:
    case UNSIGNED + LONG + LONG + INT:
      ty = copy_type(ty_ullong);
      break;
    case UNSIGNED + INT128:
      ty = copy_type(ty_uint128);
      break;      
    case FLOAT:
      ty = copy_type(ty_float);
      break;
    case DOUBLE:
      ty = copy_type(ty_double);
      break;
    case LONG + DOUBLE:    
      ty = copy_type(ty_ldouble);
      break;
    default:
      error_tok(tok, "%s:%d: in declspec : invalid type", __FILE__, __LINE__);
    }

    tok = tok->next;
    tok = attribute_list(tok, attr, thing_attributes);
  }


  *rest = tok;
  if (!ty)
    error_tok(tok, "%s:%d: in declspec : ty is null!", __FILE__, __LINE__);

  if (is_atomic || is_const || is_volatile || is_restrict) {
    Type *ty3 = new_qualified_type(ty);
    ty3->is_atomic = is_atomic;
    ty3->is_const = is_const;
    ty3->is_volatile = is_volatile;
    ty3->is_restrict = is_restrict;
    return ty3;
  }
  return ty;
}

// func-params = ("void" | param ("," param)* ("," "...")?)? ")"
// param       = declspec declarator
static Type *func_params(Token **rest, Token *tok, Type *ty)
{

  //tok = attribute_list(tok, ty, type_attributes);
  if (equal(tok, "void") && equal(tok->next, ")"))
  {
    *rest = tok->next->next;
    return func_type(ty);
  }

  Type head = {};
  Type *cur = &head;
  bool is_variadic = false;
  bool has_ellipsis = false;
  int nbparms = 0;
  // Function prototype scope: a prior parameter name is visible in
  // subsequent parameter declarators (e.g. int f(int n, int a[n])).
  enter_scope();
  while (!equal(tok, ")"))
  {

    tok = attribute_list(tok, ty, type_attributes);
    if (cur != &head) {
      if (equal(tok, ";")) {
        SET_CTX(ctx); 
        tok = skip(tok, ";", ctx);
      }
      //fix for Static assert declaration ISS-165/ISS-166
      else if (!equal(tok, ",")) {
        Node *node = expr(&tok, tok);
        if (eval(node->lhs) == 0) { 
          error("%s:%d: static assert error : %s",  __FILE__, __LINE__, node->rhs->tok->loc);
        }
        while(!equal(tok->next, ";")) 
          tok = tok->next;
        break;
    } else {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }
    }
    tok = attribute_list(tok, ty, type_attributes);
    if (equal(tok, "..."))
    {
      is_variadic = true;
      has_ellipsis = true;
      tok = tok->next;
      SET_CTX(ctx); 
      skip(tok, ")", ctx);
      break;
    }
    Type *ty2 = declspec(&tok, tok, NULL);
    tok = attribute_list(tok, ty2, type_attributes);
    //Type *backup = ty2;
    if (is_old_style) {
      Token *backup = tok;
      // Skip leading pointer stars: `int *name` or `int **name`
      while (equal(tok, "*"))
        tok = tok->next;
      // Also handle pointer-declarator form: `int (*name)[N]`
      // In that case tok is `(`, followed by optional stars, then the ident.
      if (equal(tok, "(")) {
        tok = tok->next;
        while (equal(tok, "*"))
          tok = tok->next;
      }
      if (equal(tok, "{"))
        break;
      if (tok->kind != TK_IDENT)
        error_tok(tok, "%s:%d: in func_params : expected identifier old source code not managed yet", __FILE__, __LINE__);
      ArrayToken[nbFunc][nbparms] = tok;
      tok = backup;
    }

    ty2 = declarator(&tok, tok, ty2);
    tok = attribute_list(tok, ty2, type_attributes);

    if (!ty2)
      error_tok(tok, "%s:%d: in func_params : ty2 is null", __FILE__, __LINE__);

    Token *name = ty2->name;

    if (is_array(ty2)) {
      Type *orig = ty2;   // save before decay
      Type *ty3 = pointer_to(ty2->base);
      ty3->is_atomic   = ty2->is_atomic;
      ty3->is_const    = ty2->is_const;
      ty3->is_volatile = ty2->is_volatile;
      ty3->is_restrict = ty2->is_restrict;
      ty2 = ty3;
      ty2->name = name;
      // FIX: stash the pre-decay VLA type so size emission can find vla_len
      if (orig->kind == TY_VLA)
          ty2->vla_param_ty = orig;
    }
    else if (ty2->kind == TY_FUNC) {
      // Likewise, a function is converted to a pointer to a function
      // only in the parameter context.
      ty2 = pointer_to(ty2);
      ty2->name = name;
    }
    if (is_old_style) {
      if (name)
        ArrayToken[nbFunc][nbparms] = name;
      ArrayType[nbFunc][nbparms] = ty2;
      nbparms++;
    }

    char *var_name = name ? get_ident(name) : "";
    ty2->param_var = new_lvar(var_name, ty2, NULL);

    cur = cur->next = copy_type(ty2);
  }

  leave_scope();

  if (cur == &head)
    is_variadic = true;
  ty = func_type(ty);
  tok = attribute_list(tok, ty, type_attributes);
  //the goal here is to rearrange the correct parameter order type following the parameter order for old C style
  //example 
  // void test_compress(compr, comprLen, uncompr, uncomprLen) char *compr,
  //   *uncompr;
  // long comprLen, uncomprLen;
  // the order of parameters inside parenthesis doesn't correspond to the declaration of each parameter.
  if (is_old_style) {
    ty->params = old_params(head.next, nbparms);
  } else 
    ty->params = head.next;
  ty->is_variadic = is_variadic;
  if ((cur == &head && !has_ellipsis) || is_old_style)
    ty->is_oldstyle = true;
  if (is_old_style && equal(tok, "{"))
    *rest = tok;
  else
    *rest = tok->next;
  if (!ty)
    error_tok(tok, "%s:%d: in func_params : ty is null!", __FILE__, __LINE__);
  return ty;
}

// array-dimensions = ("static" | "restrict")* const-expr? "]" type-suffix
static Type *array_dimensions(Token **rest, Token *tok, Type *ty)
{

  while (equal(tok, "static") || equal(tok, "restrict") || equal(tok, "__restrict") || equal(tok, "__restrict__") || equal(tok, "const") || equal(tok, "volatile"))
    tok = tok->next;

  if (consume(&tok, tok, "]") ||
      (equal(tok, "*") && tok->next && equal(tok->next, "]"))) {
    if (equal(tok, "*"))
      tok = tok->next->next;
    if (equal(tok, "["))
      ty = array_dimensions(&tok, tok->next, ty);
    tok = attribute_list(tok, ty, type_attributes);
    *rest = tok;
    return array_of(ty, -1);
  }

  Node *expr = assign(&tok, tok);
  add_type(expr);
  SET_CTX(ctx); 
  tok = skip(tok, "]", ctx);

  if (equal(tok, "["))
    ty = array_dimensions(&tok, tok->next, ty);
  *rest = tok;

  if (ty->kind != TY_VLA && is_const_expr(expr) )
    return array_of(ty, eval(expr));


  return vla_of(ty, expr);
}


static void pointer_qualifiers(Token **rest, Token *tok, Type *ty) {
  for (;; tok = tok->next) {
    if (equal(tok, "_Atomic"))
      ty->is_atomic = true;
    else if (equal(tok, "const"))
      ty->is_const = true;
    else if (equal(tok, "volatile"))
      ty->is_volatile = true;
    else if (equal(tok, "restrict") || equal(tok, "__restrict") || equal(tok, "__restrict__"))
      ty->is_restrict = true;
    else
      break;
  }
  *rest = tok;
}


// type-suffix = "(" func-params
//             | "[" array-dimensions
//             | ε
static Type *type_suffix(Token **rest, Token *tok, Type *ty)
{

  if (equal(tok, "("))
  {
    //in case of old style K&R we omit the parameters inside parenthesis and we parse the parameters that 
    //follow the old c style example 
    // void test_compress(compr, comprLen, uncompr, uncomprLen) char *compr,
    //   *uncompr;
    // long comprLen, uncomprLen;
    if (is_old_style) {
      nbFunc++;
      tok = old_style_params(rest, tok->next, ty);
      *rest = tok;    
      return func_params(rest, tok, ty);
    }
    return func_params(rest, tok->next, ty);
  }

  if (equal(tok, "["))
    return array_dimensions(rest, tok->next, ty);

  *rest = tok;
  if (!ty)
    error_tok(tok, "%s:%d: in type_suffix : ty is null!", __FILE__, __LINE__);
  return ty;
}

// pointers = ("*" ("const" | "volatile" | "restrict" | "_Complex" )*)*
static Type *pointers(Token **rest, Token *tok, Type *ty)
{
  while (consume(&tok, tok, "*"))
  {
    ty = pointer_to(ty);
    for (;;) {

      tok = attribute_list(tok, ty, type_attributes);
       pointer_qualifiers(&tok, tok, ty);
       if (equal(tok, "_Complex")) {
         tok = tok->next;
       } else {
         break;
       }
    }
  }
  tok = attribute_list(tok, ty, type_attributes);
  *rest = tok;
  if (!ty)
    error_tok(tok, "%s:%d: in pointers : ty is null!", __FILE__, __LINE__);
  return ty;
}

// declarator = pointers ("(" ident ")" | "(" declarator ")" | ident) type-suffix
static Type *declarator(Token **rest, Token *tok, Type *ty)
{
  tok = attribute_list(tok, ty, type_attributes);
  ty = pointers(&tok, tok, ty);
  
  if (equal(tok, "(") && !is_typename(tok->next) && !equal(tok->next, ")"))
  {

    Token *start = tok;
    Type dummy = {};
    declarator(&tok, start->next, &dummy);
    if (equal(tok, ")")) {
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }
    ty = type_suffix(rest, tok, ty);
    if (!ty)
      error_tok(tok, "%s:%d: in declarator : ty is null", __FILE__, __LINE__);
    return declarator(&tok, start->next, ty);
  }
  tok = attribute_list(tok, ty, type_attributes);  
  Token *name = NULL;
  Token *name_pos = tok;
  
  if (tok->kind == TK_IDENT)
  {
    name = tok;
    tok = tok->next;      
  }

  ty = type_suffix(rest, tok, ty);
  if (!ty)
    error_tok(tok, "%s:%d: in declarator : ty is null", __FILE__, __LINE__);  
  ty->name = name;
  ty->name_pos = name_pos;
  return ty;
}

// abstract-declarator = pointers ("(" abstract-declarator ")")? type-suffix
static Type *abstract_declarator(Token **rest, Token *tok, Type *ty)
{
  tok = attribute_list(tok, ty, type_attributes);
  ty = pointers(&tok, tok, ty);

  if (equal(tok, "(") && !is_typename(tok->next) && !equal(tok->next, ")"))
  {
    Token *start = tok;
    Type dummy = {};
    abstract_declarator(&tok, start->next, &dummy);
    SET_CTX(ctx); 
    tok = skip(tok, ")", ctx);
    ty = type_suffix(rest, tok, ty);
    if (!ty)
      error_tok(tok, "%s:%d: in declarator : ty is null", __FILE__, __LINE__);
    return abstract_declarator(&tok, start->next, ty);
  }
  tok = attribute_list(tok, ty, type_attributes);
  return type_suffix(rest, tok, ty);
}

// type-name = declspec abstract-declarator
static Type *typename(Token **rest, Token *tok)
{
  
  Type *ty = declspec(&tok, tok, NULL);
  tok = attribute_list(tok, ty, type_attributes);
  return abstract_declarator(rest, tok, ty);
}

static bool is_end(Token *tok)
{
  return equal(tok, "}") || (equal(tok, ",") && equal(tok->next, "}")) || equal(tok, ";");
}

static bool consume_end(Token **rest, Token *tok)
{
  if (equal(tok, "}"))
  {
    *rest = tok->next;
    return true;
  }

  if (equal(tok, ",") && equal(tok->next, "}"))
  {
    *rest = tok->next->next;
    return true;
  }

  return false;
}

// enum-specifier = ident? "{" enum-list? "}"
//                | ident ("{" enum-list? "}")?
//
// enum-list      = ident ("=" num)? ("," ident ("=" num)?)* ","?
static Type *enum_specifier(Token **rest, Token *tok)
{

  Type *ty = enum_type();
  tok = attribute_list(tok, ty, type_attributes);
  // Read a struct tag.
  Token *tag = NULL;
  if (tok->kind == TK_IDENT)
  {
    tag = tok;
    tok = tok->next;
  }
  tok = attribute_list(tok, ty, type_attributes);
  if (tag && !equal(tok, "{"))
  {
    Type *ty2 = find_tag(tag);
    if (!ty2)
      warn_tok(tag, "%s:%d: in enum_specifier : unknown enum type", __FILE__, __LINE__);
    if (ty2 && ty2->kind != TY_ENUM)
      error_tok(tag, "%s:%d: in enum_specifier : not an enum tag", __FILE__, __LINE__);
    *rest = tok;
    if (ty2)
      return ty2;

    if (!ty)
      error_tok(tok, "%s:%d: in enum_specifier : ty is null!", __FILE__, __LINE__);  
    return ty;
  }
  SET_CTX(ctx); 
  tok = skip(tok, "{", ctx);

  // Read an enum-list.
  int i = 0;
  int val = 0;
  while (!consume_end(rest, tok))
  {
    //tok->next = attribute_list(tok->next, ty, type_attributes);
    if (i++ > 0) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }

    char *name = get_ident(tok);
    tok = tok->next;
    tok = attribute_list(tok, ty, type_attributes);
    if (equal(tok, "="))
      val = const_expr(&tok, tok->next);
    tok = attribute_list(tok, ty, type_attributes);

    VarScope *sc = push_scope(name);
    sc->enum_ty = ty;
    sc->enum_val = val++;
  }

  if (tag)
    push_tag_scope(tag, ty);
  if (!ty)
    error_tok(tok, "%s:%d: in enum_specifier : ty is null!", __FILE__, __LINE__);    
  return ty;
}

// typeof-specifier = "(" (expr | typename) ")"
static Type *typeof_specifier(Token **rest, Token *tok)
{
  SET_CTX(ctx); 
  tok = skip(tok, "(", ctx);

  Type *ty;
  if (is_typename(tok))
  {
    ty = typename(&tok, tok);
  }
  else
  {
    Node *node = expr(&tok, tok);
    add_type(node);
    ty = node->ty;
  }
  SET_CTX(ctx); 
  *rest = skip(tok, ")", ctx);
  if (!ty)
    error_tok(tok, "%s:%d: in typeof_specifier : ty is null!", __FILE__, __LINE__);
  return ty;
}

static Node *visit_all_vla(Node *node, Token *tok) {
  if (!node)
    return new_node(ND_NULL_EXPR, tok);

  Node *res = new_node(ND_NULL_EXPR, tok);

  switch (node->kind) {
  case ND_VAR:
    if (node->var && node->var->vla_ty)
      res = new_binary(ND_COMMA, res, compute_vla_size(node->var->vla_ty, tok), tok);
    break;
  case ND_STMT_EXPR:
  case ND_BLOCK:
    for (Node *n = node->body; n; n = n->next)
      res = new_binary(ND_COMMA, res, visit_all_vla(n, tok), tok);
    break;
  case ND_FUNCALL:
    res = new_binary(ND_COMMA, res, visit_all_vla(node->lhs, tok), tok);
    for (Node *n = node->args; n; n = n->next)
      res = new_binary(ND_COMMA, res, visit_all_vla(n, tok), tok);
    break;
  case ND_COND:
    res = new_binary(ND_COMMA, res, visit_all_vla(node->cond, tok), tok);
    res = new_binary(ND_COMMA, res, visit_all_vla(node->then, tok), tok);
    res = new_binary(ND_COMMA, res, visit_all_vla(node->els, tok), tok);
    break;
  case ND_CAST:
  case ND_ADDR:
  case ND_DEREF:
  case ND_MEMBER:
  case ND_POS:
  case ND_NEG:
  case ND_NOT:
  case ND_BITNOT:
    res = new_binary(ND_COMMA, res, visit_all_vla(node->lhs, tok), tok);
    break;
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
  case ND_SHL:
  case ND_SHR:
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
  case ND_LOGAND:
  case ND_LOGOR:
  case ND_ASSIGN:
  case ND_COMMA:
    res = new_binary(ND_COMMA, res, visit_all_vla(node->lhs, tok), tok);
    res = new_binary(ND_COMMA, res, visit_all_vla(node->rhs, tok), tok);
    break;
  default:
    break;
  }

  return res;
}

// Generate code for computing a VLA size.
static Node *compute_vla_size(Type *ty, Token *tok)
{
  Node *node = new_node(ND_NULL_EXPR, tok);

  // Function parameters that are arrays decay to pointers; vla_param_ty
  // holds the original array type so we can still compute its element size.
  if (ty->kind == TY_PTR && ty->vla_param_ty) {
    if (!current_fn)
      return node;
    Node *n = compute_vla_size(ty->vla_param_ty, tok);
    ty->vla_size = ty->vla_param_ty->vla_size;
    if (!ty->vla_size)
      error_tok(tok, "%s:%d: compute_vla_size: vla_size null after computation",
                __FILE__, __LINE__);
    return new_binary(ND_COMMA, node, n, tok);
  }

  // If already computed for this function, only recurse into base so child
  // sizes are available, but do not re-emit the assignment.
  if (ty->vla_size) {
    if (!current_fn) {
      if (ty->base)
        compute_vla_size(ty->base, tok);
      return new_var_node(ty->vla_size, tok);
    }

    if (ty->vla_size->funcname && !strcmp(ty->vla_size->funcname, current_fn->funcname)) {
      if (ty->base) {
        Node *n = compute_vla_size(ty->base, tok);
        if (n->kind != ND_NULL_EXPR)
          return new_binary(ND_COMMA, node, n, tok);
      }
      return new_var_node(ty->vla_size, tok);
    }

    // First time we see this vla_size in the current function: register it.
    if (!ty->vla_size->funcname) {
      ty->vla_size->funcname = current_fn->funcname;
      ty->vla_size->next = locals;
      locals = ty->vla_size;
    } else if (strcmp(ty->vla_size->funcname, current_fn->funcname)) {
      // Came from a different function – reset so we reallocate below.
      ty->vla_size = NULL;
    }
  }

  // Recurse into base type first so its vla_size is set before we need it.
  if (ty->base)
    node = new_binary(ND_COMMA, node, compute_vla_size(ty->base, tok), tok);

  // Nothing VLA-related at this level – done.
  if (ty->kind != TY_VLA && !ty->has_vla)
    return node;

  // Struct/union containing VLA members: sum member sizes dynamically.
  if (ty->kind == TY_STRUCT || ty->kind == TY_UNION) {
    if (!ty->has_vla)
      return node;
    // Allocate a runtime variable to hold the struct/union size.
    ty->vla_size = new_lvar("", ty_ulong, NULL);
    ty->vla_size->vla_ty = ty;
    Node *sz = new_num(0, tok);

    for (Member *mem = ty->members; mem; mem = mem->next) {
      Node *member_size;
      if (mem->ty->kind == TY_VLA || mem->ty->has_vla) {
        node = new_binary(ND_COMMA, node, compute_vla_size(mem->ty, tok), tok);
        member_size = new_var_node(mem->ty->vla_size, tok);
      } else {
        member_size = new_num(mem->ty->size, tok);
      }
      sz = new_binary(ND_ADD, sz, member_size, tok);
    }

    Node *expr = new_binary(ND_ASSIGN, new_var_node(ty->vla_size, tok), sz, tok);
    return new_binary(ND_COMMA, node, expr, tok);
  }

  // TY_VLA: compute size = vla_len * base_size.
  // base recursion above has already set ty->base->vla_size if base is also VLA.
  Node *base_sz = (ty->base->kind == TY_VLA)
                ? new_var_node(ty->base->vla_size, tok)
                : new_num(ty->base->size, tok);

  if (!ty->vla_size) {
    ty->vla_size = new_lvar("", ty_ulong, NULL);
    ty->vla_size->vla_ty = ty;
  }

  if (ty->vla_len)
    node = new_binary(ND_COMMA, node, visit_all_vla(ty->vla_len, tok), tok);

  if (!current_fn)
    return new_var_node(ty->vla_size, tok);

  if (!ty->vla_len)
    error_tok(tok, "%s:%d: in compute_vla_size : vla_len is null!", __FILE__, __LINE__);

  Node *expr = new_binary(ND_ASSIGN, new_var_node(ty->vla_size, tok),
                          new_binary(ND_MUL, ty->vla_len, base_sz, tok),
                          tok);
  return new_binary(ND_COMMA, node, expr, tok);
}

// Return the sizeof expression for a VLA or struct-with-VLA type.
// Returns NULL if the type is a regular (compile-time) type.
static Node *sizeof_vla_type(Type *ty, Token *tok) {
  if ((ty->kind == TY_STRUCT || ty->kind == TY_UNION) && ty->has_vla) {
    if (!ty->vla_size) {
      Node *lhs = compute_vla_size(ty, tok);
      return new_binary(ND_COMMA, lhs, new_var_node(ty->vla_size, tok), tok);
    }
    return new_var_node(ty->vla_size, tok);
  }
  if (ty->kind == TY_VLA) {
    if (ty->vla_size)
      return new_var_node(ty->vla_size, tok);
    return compute_vla_size(ty, tok);
  }
  return NULL;  // not a runtime-sized type
}


static void need_alloca_bottom(void) {
  if (!current_fn) return;
  if (current_fn->alloca_bottom)
    return;
  //opt_omit_frame_pointer = false;
  current_fn->force_frame_pointer = true;
  current_fn->alloca_bottom = new_lvar("__alloca_size__", pointer_to(ty_char), current_fn->name);
}

static Node *new_alloca(Node *sz, int align)
{
  need_alloca_bottom();
  if (!builtin_alloca) {
    // Fallback implementation for alloca
    Node *node = new_node(ND_ALLOC, sz->tok);
    node->ty = pointer_to(ty_void); // Adjust the type as necessary
    node->lhs = sz; // `sz` is the size to allocate
    add_type(sz);
    return node;
  }
  Node *node = new_unary(ND_FUNCALL, new_var_node(builtin_alloca, sz->tok), sz->tok);
  node->func_ty = builtin_alloca->ty;
  node->ty = builtin_alloca->ty->return_ty;
  node->args = sz;
  node->val = align;
  add_type(sz);
  return node;
}


// declaration = declspec (declarator ("=" expr)? ("," declarator ("=" expr)?)*)? ";"
static Node *declaration(Token **rest, Token *tok, Type *basety, VarAttr *attr)
{

  Node head = {};
  Node *cur = &head;
  int i = 0;
  while (!equal(tok, ";"))
  {

    if (i++ > 0) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }
    VarAttr decl_attr = attr ? *attr : (VarAttr){};
    current_attr = &decl_attr;
    Type *ty = declarator(&tok, tok, basety);
    current_attr = NULL;
    if (!ty)
      error_tok(tok, "%s:%d: in declaration : ty is null", __FILE__, __LINE__);
    if (ty->kind == TY_VOID)
      error_tok(tok, "%s:%d: in declaration : variable declared void", __FILE__, __LINE__);
    if (!ty->name)
      error_tok(ty->name_pos, "%s:%d: in declaration : variable name omitted", __FILE__, __LINE__);    
    tok = attribute_list(tok, &decl_attr, thing_attributes);
    int alt_align = decl_attr.align;
    if (decl_attr.is_static)
    {
      // static local variable

      if (ty->kind == TY_VLA)
        error_tok(tok, "%s:%d: in declaration: variable length arrays cannot be 'static'", __FILE__, __LINE__);

      Obj *var = new_anon_gvar(ty);
      //from @fuhsnn fix Handle local static _Thread_local
      var->is_tls = decl_attr.is_tls;
      if (alt_align)
        var->align = alt_align;
      push_scope(get_ident(ty->name))->var = var;
      if (equal(tok, "="))
        gvar_initializer(&tok, tok->next, var);
      continue;
    }

    // Generate code for computing a VLA size. We need to do this
    // even if ty is not VLA because ty may be a pointer to VLA
    // (e.g. int (*foo)[n][m] where n and m are variables.)
    cur = cur->next = new_unary(ND_EXPR_STMT, compute_vla_size(ty, tok), tok);

    //from COSMOPOLITAN adding other GNUC attributes
    tok = attribute_list(tok, &decl_attr, thing_attributes);

    if (ty->kind == TY_VLA)
    {
      if (equal(tok, "="))
        error_tok(tok, "%s:%d: in declaration: variable-sized object may not be initialized", __FILE__, __LINE__);

      // Variable length arrays (VLAs) are translated to alloca() calls.
      // For example, `int x[n+2]` is translated to `tmp = n + 2,
      // x = alloca(tmp)`.
      
      Obj *var = new_lvar(get_ident(ty->name), ty, NULL);
      Token *tok = ty->name;
      tok = attribute_list(tok, ty, type_attributes);
      int var_align = MAX(decl_attr.align, ty->align);
      var->align = var_align;
      var->ty->align = MAX(var->ty->align, var_align);
      int align = MAX(16, var_align);
      Node *expr = new_binary(ND_ASSIGN, new_vla_ptr(var, tok),
                              new_alloca(new_var_node(ty->vla_size, tok), align),
                              tok);

      cur = cur->next = new_unary(ND_EXPR_STMT, expr, tok);
      continue;
    }
    
    Obj *var = new_lvar(get_ident(ty->name), ty, NULL);
    if (alt_align) {
      var->align = alt_align;
      var->ty->align = MAX(var->ty->align, alt_align);
    }

    if (equal(tok, "=")) {
      tok = tok->next;
      Node *expr;
      expr = lvar_initializer(&tok, tok, var);
      if (expr->lhs && expr->lhs->var && expr->lhs->var->name) {
        cur = cur->next = new_unary(ND_EXPR_STMT, expr, tok);
      }
    }
    //ISS-146
    if (var->ty->size < 0)
      error_tok(ty->name, "%s:%d: in declaration : variable has incomplete type", __FILE__, __LINE__);

    if (var->ty->kind == TY_VOID)
      error_tok(ty->name, "%s:%d: in declaration : variable declared void", __FILE__, __LINE__);
  }

  Node *node = new_node(ND_BLOCK, tok);
  node->body = head.next;
  *rest = tok->next;
  return node;
}

static Token *skip_excess_element(Token *tok)
{


  if (equal(tok, "{"))
  {
    tok = skip_excess_element(tok->next);
    SET_CTX(ctx); 
    return skip(tok, "}", ctx);
  }

  assign(&tok, tok);
  return tok;
}

// string-initializer = string-literal
static void string_initializer(Token **rest, Token *tok, Initializer *init)
{
  if (init->is_flexible)
    *init = *new_initializer(array_of(init->ty->base, tok->ty->array_len), false);

  int len = MIN(init->ty->array_len, tok->ty->array_len);

  switch (init->ty->base->size)
  {
  case 1:
  {
    char *str = tok->str;
    for (int i = 0; i < len; i++)
      init->children[i]->expr = new_num(str[i], tok);
    break;
  }
  case 2:
  {
    uint16_t *str = (uint16_t *)tok->str;
    for (int i = 0; i < len; i++)
      init->children[i]->expr = new_num(str[i], tok);
    break;
  }
  case 4:
  {
    uint32_t *str = (uint32_t *)tok->str;
    for (int i = 0; i < len; i++)
      init->children[i]->expr = new_num(str[i], tok);
    break;
  }
  case 8: {
    // Initialize array of 64-bit integers
    for (int i = 0; i < len; i++) {
        // We need to ensure that we are accessing the string in a manner suitable for 64-bit integers.
        // For simplicity, let's fill the 64-bit integer with repeated characters from the string.
        uint64_t value = 0;
        for (int j = 0; j < 8 && i * 8 + j < len; j++) {
            value |= (uint64_t)(unsigned char) tok->str[i * 8 + j] << (j * 8);
        }
        init->children[i]->expr = new_num(value, tok);
    }
    break;
    case 16:
      {
          // Initialize array of 128-bit integers
          for (int i = 0; i < len; i++)
          {
              __int128 value = 0;
              for (int j = 0; j < 16 && i * 16 + j < len; j++)
              {
                  value |= (__int128)(unsigned char)tok->str[i * 16 + j] << (j * 8);
              }
              init->children[i]->expr = new_num(value, tok);
          }
          
      }
    break;
  }
  default:
    error_tok(tok, "%s:%d: in string_initializer : array of inappropriate type initialized from string constant", __FILE__, __LINE__);
    // unreachable();
  }

  *rest = tok->next;
}

// array-designator = "[" const-expr "]"
//
// C99 added the designated initializer to the language, which allows
// programmers to move the "cursor" of an initializer to any element.
// The syntax looks like this:
//
//   int x[10] = { 1, 2, [5]=3, 4, 5, 6, 7 };
//
// `[5]` moves the cursor to the 5th element, so the 5th element of x
// is set to 3. Initialization then continues forward in order, so
// 6th, 7th, 8th and 9th elements are initialized with 4, 5, 6 and 7,
// respectively. Unspecified elements (in this case, 3rd and 4th
// elements) are initialized with zero.
//
// Nesting is allowed, so the following initializer is valid:
//
//   int x[5][10] = { [5][8]=1, 2, 3 };
//
// It sets x[5][8], x[5][9] and x[6][0] to 1, 2 and 3, respectively.
//
// Use `.fieldname` to move the cursor for a struct initializer. E.g.
//
//   struct { int a, b, c; } x = { .c=5 };
//
// The above initializer sets x.c to 5.
static void array_designator(Token **rest, Token *tok, Type *ty, int *begin, int *end)
{

  *begin = const_expr(&tok, tok->next);
  if (*begin >= ty->array_len)
    error_tok(tok, "%s:%d: in array_designator : array designator index exceeds array bounds", __FILE__, __LINE__);

  if (equal(tok, "..."))
  {
    *end = const_expr(&tok, tok->next);
    if (*end >= ty->array_len)
      error_tok(tok, "%s:%d: in array designator : index exceeds array bounds", __FILE__, __LINE__);
    if (*end < *begin)
      error_tok(tok, "%s:%d: in array designator : range [%d, %d] is empty", __FILE__, __LINE__, *begin, *end);
  }
  else
  {
    *end = *begin;
  }
  SET_CTX(ctx); 
  *rest = skip(tok, "]", ctx);
}

// struct-designator = "." ident
static Member *struct_designator(Token **rest, Token *tok, Type *ty)
{
  
  Token *start = tok;  
  if (equal(tok, ".")) {
    SET_CTX(ctx); 
    tok = skip(tok, ".", ctx);
  }
  if (tok->kind != TK_IDENT)
    error_tok(tok, "%s:%d: in struct_designator : expected a field designator", __FILE__, __LINE__);

  for (Member *mem = ty->members; mem; mem = mem->next)
  {

    // Anonymous struct member
    if (!mem->name)
    {
      if (mem->ty->kind == TY_STRUCT || mem->ty->kind == TY_UNION)
      {
        tok = attribute_list(tok, ty, type_attributes);
        if (get_struct_member(mem->ty, tok))
        {
          *rest = start;
          return mem;
        }
      }
      continue;
    }

    // Regular struct member
    if (mem->name->len == tok->len && !strncmp(mem->name->loc, tok->loc, tok->len))
    {
      *rest = tok->next;
      return mem;
    }
  }

  error_tok(tok, "%s:%d: in struct_designator : struct has no such member", __FILE__, __LINE__);
}

// designation = ("[" const-expr "]" | "." ident)* "="? initializer
static void designation(Token **rest, Token *tok, Initializer *init)
{
  tok = attribute_list(tok, init->ty, type_attributes);
  if (equal(tok, "["))
  {
    if (init->ty->kind != TY_ARRAY)
      error_tok(tok, "%s:%d: in designation : array index in non-array initializer", __FILE__, __LINE__);

    int begin, end;
    array_designator(&tok, tok, init->ty, &begin, &end);

    Token *tok2;
    for (int i = begin; i <= end; i++)
      designation(&tok2, tok, init->children[i]);
    //fix from @fuhsnn Fix array initializer post-designation offset  
    //array_initializer2(rest, tok2, init, begin + 1);
    array_initializer2(rest, tok2, init, end + 1);
    return;
  }

  
  if (equal(tok, ".") && init->ty->kind == TY_STRUCT)
  {
    Member *mem = struct_designator(&tok, tok, init->ty);
    designation(&tok, tok, init->children[mem->idx]);
    init->expr = NULL;

    struct_initializer2(rest, tok, init, mem->next, true);
    return;
  }


  if (equal(tok, ".") && init->ty->kind == TY_UNION)
  {
    
    Member *mem = struct_designator(&tok, tok, init->ty);
    init->mem = mem;
    designation(rest, tok, init->children[mem->idx]);
    return;
  }

  if (equal(tok, "."))
    error_tok(tok, "%s:%d: in designation: field name not in struct or union initializer", __FILE__, __LINE__);

  if (equal(tok, "=")) {
    SET_CTX(ctx); 
    tok = skip(tok, "=", ctx);
  }
  // tok = tok->next;

  initializer2(rest, tok, init);
}

// An array length can be omitted if an array has an initializer
// (e.g. `int x[] = {1,2,3}`). If it's omitted, count the number
// of initializer elements.
static int count_array_init_elements(Token *tok, Type *ty)
{
  
  bool first = true;
  Initializer *dummy = new_initializer(ty->base, true);

  int i = 0, max = 0;

  while (!consume_end(&tok, tok))
  {

    if (!first) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }

    first = false;

    if (equal(tok, "["))
    {
      i = const_expr(&tok, tok->next);
      if (equal(tok, "..."))
        i = const_expr(&tok, tok->next);
      SET_CTX(ctx);        
      tok = skip(tok, "]", ctx);
      designation(&tok, tok, dummy);
    }
    else
    {
      initializer2(&tok, tok, dummy);
    }

    i++;
    max = MAX(max, i);
  }
  return max;
}

// array-initializer1 = "{" initializer ("," initializer)* ","? "}"
static void array_initializer1(Token **rest, Token *tok, Initializer *init)
{
  SET_CTX(ctx); 
  tok = skip(tok, "{", ctx);

  // if (init->is_flexible)
  // {
  //   int len = count_array_init_elements(tok, init->ty);
  //   *init = *new_initializer(array_of(init->ty->base, len), false);
  // }

  bool first = true;

  if (init->is_flexible)
  {
    int len = count_array_init_elements(tok, init->ty);
    *init = *new_initializer(array_of(init->ty->base, len), false);
  }

  for (int i = 0; !consume_end(rest, tok); i++)
  {
    if (!first) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }

    first = false;

    if (equal(tok, "["))
    {
      int begin, end;
      array_designator(&tok, tok, init->ty, &begin, &end);

      Token *tok2;
      for (int j = begin; j <= end; j++)
        designation(&tok2, tok, init->children[j]);
      tok = tok2;
      i = end;
      continue;
    }

    if (i < init->ty->array_len)
      initializer2(&tok, tok, init->children[i]);
    else
      tok = skip_excess_element(tok);
  }
}

// array-initializer2 = initializer ("," initializer)*
static void array_initializer2(Token **rest, Token *tok, Initializer *init, int i)
{

  if (init->is_flexible)
  {
    int len = count_array_init_elements(tok, init->ty);
    *init = *new_initializer(array_of(init->ty->base, len), false);
  }

  for (; i < init->ty->array_len && !is_end(tok); i++)
  {
    Token *start = tok;
    if (i > 0) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }

    if (equal(tok, "[") || equal(tok, "."))
    {
      *rest = start;
      return;
    }

    initializer2(&tok, tok, init->children[i]);
  }
  *rest = tok;
}

// struct-initializer1 = "{" initializer ("," initializer)* ","? "}"
static void struct_initializer1(Token **rest, Token *tok, Initializer *init)
{
  SET_CTX(ctx);          
  tok = skip(tok, "{", ctx);

  Member *mem = init->ty->members;
  bool first = true;

  while (!consume_end(rest, tok))
  {
    if (!first) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }

    first = false;

    if (equal(tok, "."))
    {
      mem = struct_designator(&tok, tok, init->ty);
      designation(&tok, tok, init->children[mem->idx]);
      mem = mem->next;
      continue;
    }

    if (mem)
    {
      initializer2(&tok, tok, init->children[mem->idx]);
      mem = mem->next;
    }
    else
    {
      tok = skip_excess_element(tok);
    }
  }
}

// struct-initializer2 = initializer ("," initializer)*
static void struct_initializer2(Token **rest, Token *tok, Initializer *init, Member *mem, bool post_desig)
{
  bool first = true;
  for (; mem && !is_end(tok); mem = mem->next)
  {
    Token *start = tok;

    if (!first || post_desig) {
      SET_CTX(ctx);         
      tok = skip(tok, ",", ctx);
    }

    first = false;

    if (equal(tok, "[") || equal(tok, "."))
    {
      *rest = start;
      return;
    }


    initializer2(&tok, tok, init->children[mem->idx]);

  }
  *rest = tok;
}


static void union_initializer(Token **rest, Token *tok, Initializer *init) {
  SET_CTX(ctx);        
  tok = skip(tok, "{", ctx);

  bool first = true;

  for (; !consume_end(rest, tok); first = false) {
    if (!first) {
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
    }

    if (equal(tok, ".")) {
      init->mem = struct_designator(&tok, tok, init->ty);
      designation(&tok, tok, init->children[init->mem->idx]);
      continue;
    }

    if (first && init->ty->members) {
      init->mem = init->ty->members;
      initializer2(&tok, tok, init->children[0]);
    } else {
      tok = skip_excess_element(tok);
    }
  }
}

static void vector_initializer1(Token **rest, Token *tok, Initializer *init) {
  SET_CTX(ctx); 
  tok = skip(tok, "{", ctx);
  for (int i = 0; i < init->ty->array_len && !equal(tok, "}"); i++) {
    init->children[i] = calloc(1, sizeof(Initializer));
    init->children[i]->ty = init->ty->base;
    initializer2(&tok, tok, init->children[i]);
    if (equal(tok, ","))
      tok = tok->next;
  }

  SET_CTX(ctx); 
  *rest = skip(tok, "}", ctx);
}



// Recursively traverse a Node and mark all function references as address-used
static void mark_function_addresses_used(Node *node) {
  if (!node)
    return;

  switch (node->kind) {
  case ND_VAR:
    if (node->var && node->var->is_function)
      node->var->is_address_used = true;
    break;
  case ND_CAST:
    mark_function_addresses_used(node->lhs);
    break;
  case ND_ADDR:
  case ND_DEREF:
  case ND_MEMBER:
  case ND_POS:
  case ND_NEG:
  case ND_NOT:
  case ND_BITNOT:
    mark_function_addresses_used(node->lhs);
    break;
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
  case ND_SHL:
  case ND_SHR:
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
  case ND_LOGAND:
  case ND_LOGOR:
  case ND_ASSIGN:
    mark_function_addresses_used(node->lhs);
    mark_function_addresses_used(node->rhs);
    break;
  case ND_COND:
    mark_function_addresses_used(node->cond);
    mark_function_addresses_used(node->then);
    mark_function_addresses_used(node->els);
    break;
  case ND_COMMA:
    mark_function_addresses_used(node->lhs);
    mark_function_addresses_used(node->rhs);
    break;
  default:
    break;
  }
}

// initializer = string-initializer | array-initializer
//             | struct-initializer | union-initializer
//             | assign
static void initializer2(Token **rest, Token *tok, Initializer *init)
{

  // trying to fix issue #62
  if (equal(tok, ","))
    return;
  if (!init)
    error("%s:%d: error: in initializer2 :  init is null %s", __FILE__, __LINE__, tok->loc);

  if (init->ty->kind == TY_ARRAY && is_integer(init->ty->base)) {
    Token *start = tok;
    Token *str_tok;
    if (equal(tok, "{") && is_str_tok(&tok, tok->next, &str_tok)) {
      if (consume(rest, tok, "}")) {
        string_initializer(&tok, str_tok, init);
    return;
  }
      tok = start;
    }
    if (is_str_tok(rest, tok, &str_tok)) {
      string_initializer(&tok, str_tok, init);
      return;
    }
  }

  if (is_vector(init->ty)) {
    if (equal(tok, "{")) {
      vector_initializer1(rest, tok, init); 
      return;
    } 
  }

  if (init->ty->kind == TY_ARRAY) {
    if (equal(tok, "{"))
      array_initializer1(rest, tok, init);
    else
    array_initializer2(rest, tok, init, 0);
    return;
  }

  if (init->ty->kind == TY_STRUCT) {
    if (equal(tok, "{")) {
      struct_initializer1(rest, tok, init);
      return;
    }

    // A struct can be initialized with another struct. E.g.
    // `struct T x = y;` where y is a variable of type `struct T`.
    // Handle that case first.
    Node *expr = assign(rest, tok);
    add_type(expr);
    if (is_compatible(expr->ty, init->ty)) {
      init->expr = expr;
      return;
    }

    if (!init->ty->members)
      error_tok(tok, "%s:%d: error: in initializer2 :  initializer for empty aggregate requires explicit braces", __FILE__, __LINE__);

    struct_initializer2(rest, tok, init, init->ty->members, false);
    return;
  }

  if (init->ty->kind == TY_UNION) {
    if (equal(tok, "{")) {
    union_initializer(rest, tok, init);
    return;
    }

    Node *expr = assign(rest, tok);
    add_type(expr);
    if (is_compatible(expr->ty, init->ty)) {
      init->expr = expr;
      return;
    }
    if (!init->ty->members)
      error_tok(tok, "%s:%d: error: in initializer2 :  initializer for empty aggregate requires explicit braces", __FILE__, __LINE__);

    init->mem = init->ty->members;
    initializer2(rest, tok, init->children[0]);
    return;
  }

  if (equal(tok, "{"))
  {
    // An initializer for a scalar variable can be surrounded by
    // braces. E.g. `int x = {3};`. Handle that case.
    while (!equal(tok, "}")) {
    initializer2(&tok, tok->next, init);
    }
    SET_CTX(ctx); 
    *rest = skip(tok, "}", ctx);
    return;
  }

  init->expr = assign(rest, tok);
  add_type(init->expr);
  // Recursively mark all function references in this expression as address-used
  mark_function_addresses_used(init->expr);
  
}

static Type *copy_struct_type(Type *ty)
{
  ty = copy_type(ty);

  Member head = {};
  Member *cur = &head;
  for (Member *mem = ty->members; mem; mem = mem->next)
  {
    Member *m = calloc(1, sizeof(Member));
    if (m == NULL)
      error("%s:%d: error: in copy_struct_type :  m is null", __FILE__, __LINE__);
    *m = *mem;
    cur = cur->next = m;
  }

  ty->members = head.next;
  if (!ty)
    error("%s:%d: in copy_struct_type : ty is null!", __FILE__, __LINE__);
  return ty;
}

static Initializer *initializer(Token **rest, Token *tok, Type *ty, Type **new_ty)
{
  Initializer *init = new_initializer(ty, true);
  
  initializer2(rest, tok, init);

  if ((ty->kind == TY_STRUCT || ty->kind == TY_UNION) && ty->is_flexible)
  {
    ty = copy_struct_type(ty);
    Member *mem = ty->members;
    while (mem->next)
      mem = mem->next;
    mem->ty = init->children[mem->idx]->ty;
    ty->size += mem->ty->size;

    *new_ty = ty;
    return init;
  }

  *new_ty = init->ty;
  return init;
}

static Node *init_desg_expr(InitDesg *desg, Token *tok)
{
  if (desg->var)
    return new_var_node(desg->var, tok);

  if (desg->member)
  {
    Node *node = new_unary(ND_MEMBER, init_desg_expr(desg->next, tok), tok);
    node->member = desg->member;
    return node;
  }
  
  Node *lhs = init_desg_expr(desg->next, tok);
  Node *rhs = new_num(desg->idx, tok);
  return new_unary(ND_DEREF, new_add(lhs, rhs, tok, false), tok);
}

static Node *create_lvar_init(Initializer *init, Type *ty, InitDesg *desg, Token *tok)
{
  
  if (ty->kind == TY_ARRAY)
  {
    Node *node = new_node(ND_NULL_EXPR, tok);
    for (int i = 0; i < ty->array_len; i++)
    {
      InitDesg desg2 = {desg, i};
      Node *rhs = create_lvar_init(init->children[i], ty->base, &desg2, tok);
      node = new_binary(ND_COMMA, node, rhs, tok);
    }
    return node;
  }
  //case of vectors two kinds of initialization possible : direct like {1.0f, 2.0f...} or from expressions like function call
  if (is_vector(ty)) {
    if (init->expr) {
      Node *lhs = init_desg_expr(desg, tok);
      return new_binary(ND_ASSIGN, lhs, init->expr, tok);
    }
 

    Node *node = new_node(ND_NULL_EXPR, tok);
    for (int i = 0; i < ty->array_len; i++) {
      InitDesg desg2 = {desg, i};
      Node *rhs = create_lvar_init(init->children[i], ty->base, &desg2, tok);
      node = new_binary(ND_COMMA, node, rhs, tok);
    }
    return node;
  }
  if (init->expr) {    
    Node *lhs = init_desg_expr(desg, tok);
    return new_binary(ND_ASSIGN, lhs, init->expr, tok);
  }
  if (ty->kind == TY_STRUCT && !init->expr)
  {
    Node *node = new_node(ND_NULL_EXPR, tok);

    for (Member *mem = ty->members; mem; mem = mem->next)
    {
      
      InitDesg desg2 = {desg, 0, mem};
      Node *rhs = create_lvar_init(init->children[mem->idx], mem->ty, &desg2, tok);
      node = new_binary(ND_COMMA, node, rhs, tok);
    }
    return node;
  }

  if (ty->kind == TY_UNION)
  {
    if (!init->mem)
      return new_node(ND_NULL_EXPR, tok);
    Member *mem = init->mem ? init->mem : ty->members;
    InitDesg desg2 = {desg, 0, mem};
    return create_lvar_init(init->children[mem->idx], mem->ty, &desg2, tok);
  }

  if (!init->expr)
    return new_node(ND_NULL_EXPR, tok);

  Node *lhs = init_desg_expr(desg, tok);
  return new_binary(ND_ASSIGN, lhs, init->expr, tok);
}

// A variable definition with an initializer is a shorthand notation
// for a variable definition followed by assignments. This function
// generates assignment expressions for an initializer. For example,
// `int x[2][2] = {{6, 7}, {8, 9}}` is converted to the following
// expressions:
//
//   x[0][0] = 6;
//   x[0][1] = 7;
//   x[1][0] = 8;
//   x[1][1] = 9;
static Node *lvar_initializer(Token **rest, Token *tok, Obj *var)
{
  Initializer *init = initializer(rest, tok, var->ty, &var->ty);
  InitDesg desg = {NULL, 0, NULL, var};

  // If a partial initializer list is given, the standard requires
  // that unspecified elements are set to 0. Here, we simply
  // zero-initialize the entire memory region of a variable before
  // initializing it with user-supplied values.
  Node *lhs = new_node(ND_MEMZERO, tok);
  lhs->var = var;
  lhs->var->init = init;
  Node *rhs = create_lvar_init(init, var->ty, &desg, tok);

  return new_binary(ND_COMMA, lhs, rhs, tok);
}

static uint64_t read_buf(char *buf, int sz)
{
  if (sz == 1)
    return *buf;
  if (sz == 2)
    return *(uint16_t *)buf;
  if (sz == 4)
    return *(uint32_t *)buf;
  if (sz == 8)
    return *(uint64_t *)buf;
  if (sz == 16)
    return *(long double *)buf;
  unreachable();
}

static void write_buf(char *buf, uint64_t val, int sz)
{
  if (sz == 1)
    *buf = val;
  else if (sz == 2)
    *(uint16_t *)buf = val;
  else if (sz == 4)
    *(uint32_t *)buf = val;
  else if (sz == 8)
    *(uint64_t *)buf = val;
  else if (sz == 16)
    *(long double *)buf = val;
  else
    unreachable();
}

static Relocation *
write_gvar_data(Relocation *cur, Initializer *init, Type *ty, char *buf, int offset)
{
  if (ty->kind == TY_ARRAY)
  {
    int elem_size = ty->base->size;
    memset(buf + offset, 0, elem_size * ty->array_len);
    if (init->expr)
      error_tok(init->expr->tok, "%s:%d: in write_gvar_data : array initializer must be an initializer list", __FILE__, __LINE__);
    int sz = ty->base->size;
    for (int i = 0; i < ty->array_len; i++)
      cur = write_gvar_data(cur, init->children[i], ty->base, buf, offset + sz * i);
    return cur;
  }
  if (is_vector(ty))
  {
    int sz = ty->base->size;
    memset(buf + offset, 0, sz * ty->array_len);
    for (int i = 0; i < ty->array_len; i++)
      cur = write_gvar_data(cur, init->children[i], ty->base, buf, offset + sz * i);
    return cur;

  }
  if (!init->expr) {
  if (ty->kind == TY_STRUCT)
  {
    // Zero the whole struct first
    memset(buf + offset, 0, ty->size);
    for (Member *mem = ty->members; mem; mem = mem->next)
    {
      if (mem->is_bitfield)
      {
        Node *expr = init->children[mem->idx]->expr;
        if (!expr)
          continue;
        add_type(expr);

        char *loc = buf + offset + mem->offset;
        uint64_t oldval = read_buf(loc, mem->ty->size);
        uint64_t newval = eval(expr);
        uint64_t mask = (1L << mem->bit_width) - 1;
        uint64_t combined = oldval | ((newval & mask) << mem->bit_offset);
        write_buf(loc, combined, mem->ty->size);
      }
      else
      {

        cur = write_gvar_data(cur, init->children[mem->idx], mem->ty, buf,
                              offset + mem->offset);
        
      }
    }
    return cur;
  }

  if (ty->kind == TY_UNION)
  {
    memset(buf + offset, 0, ty->size);
    if (!init->mem)
      return cur;
    return write_gvar_data(cur, init->children[init->mem->idx],
                           init->mem->ty, buf, offset);
  }

  if (!init->expr)
    return cur;
  }
  
  add_type(init->expr);
  
   // Check if the initializer is a compound literal
  if (is_compatible(ty, init->expr->ty)) {
    int sofs = 0;
    Obj *var = eval_var(init->expr,  false);
    if (var && var->init_data && !var->is_weak && (is_const_var(var) || var->is_compound_lit)) {
      // Don't memcpy raw bytes into a pointer; use relocation path instead.
      bool can_copy = (ty->kind != TY_PTR);

      if (can_copy) {
        Relocation *srel = var->rel;
        while (srel && srel->offset < sofs)
          srel = srel->next;

        for (int pos = 0; pos < ty->size && (pos + sofs) < var->ty->size;) {
          if (srel && srel->offset == (pos + sofs)) {
            // Create new relocation
            cur = cur->next = calloc(1, sizeof(Relocation));
            cur->offset = (pos + offset);
            cur->label = srel->label;
            cur->addend = srel->addend;           
            srel = srel->next;
            pos += 8;
          } else {
            // Copy initialization data from compound literal
            buf[(pos + offset)] = var->init_data[(pos + sofs)];
            pos++;
          }
        }
        return cur;
      }
    }
  }

  if (ty->kind == TY_FLOAT)
  {
    *(float *)(buf + offset) = eval_double(init->expr);
    return cur;
  }

  if (ty->kind == TY_DOUBLE)
  {
    *(double *)(buf + offset) = eval_double(init->expr);
    return cur;
  }

    if (ty->kind == TY_LDOUBLE)
  {
    *(long double *)(buf + offset) = eval_double(init->expr);
    return cur;
  }


  char **label = NULL;
  uint64_t val = eval2(init->expr, &label);
  
  if (!label)
  {
    if (ty->kind == TY_BOOL)
      val = !!val;
    write_buf(buf + offset, val, ty->size);
    return cur;
  }

  // If this references a constant object with known data, fold the load.
  Obj *cvar = *label ? find_global_by_name(*label) : NULL;
  if (cvar && cvar->init_data &&
      (is_const_var(cvar) || cvar->is_compound_lit)) {
    if (is_numeric(ty) && !cvar->rel) {
      if (val + ty->size <= cvar->ty->size) {
        memcpy(buf + offset, cvar->init_data + val, ty->size);
        return cur;
      }
    }
    if (ty->kind == TY_PTR && cvar->rel && cvar->ty->kind == TY_PTR) {
      for (Relocation *srel = cvar->rel; srel; srel = srel->next) {
        if (srel->offset == (int)val) {
          Relocation *rel = calloc(1, sizeof(Relocation));
          if (rel == NULL)
            error("%s:%d: error: in write_gvar_data : rel is null", __FILE__, __LINE__);
          rel->offset = offset;
          rel->label = srel->label;
          rel->addend = srel->addend;           
          cur->next = rel;
          return cur->next;
        }
      }
    }
    if (ty->kind == TY_PTR && cvar->rel && init->expr) {
      Node *expr = init->expr;
      while (expr->kind == ND_CAST)
        expr = expr->lhs;
      if (expr->kind == ND_MEMBER) {
        int mofs = (int)val;
        for (Relocation *srel = cvar->rel; srel; srel = srel->next) {
          if (srel->offset == mofs) {
            Relocation *rel = calloc(1, sizeof(Relocation));
            if (rel == NULL)
              error("%s:%d: error: in write_gvar_data : rel is null", __FILE__, __LINE__);
            rel->offset = offset;
            rel->label = srel->label;
            rel->addend = srel->addend;                               
            cur->next = rel;
            return cur->next;
          }
        }
      }
    }
  }

  Relocation *rel = calloc(1, sizeof(Relocation));
  if (rel == NULL)
    error("%s:%d: error: in write_gvar_data : rel is null", __FILE__, __LINE__);
  rel->offset = offset;
  rel->label = label;
  rel->addend = val;
  cur->next = rel;
  return cur->next;
}

// Initializers for global variables are evaluated at compile-time and
// embedded to .data section. This function serializes Initializer
// objects to a flat byte array. It is a compile error if an
// initializer list contains a non-constant expression.
static void gvar_initializer(Token **rest, Token *tok, Obj *var)
{

  Initializer *init = initializer(rest, tok, var->ty, &var->ty);

  Relocation head = {};
  char *buf = calloc(1, var->ty->size);
  if (buf == NULL)
    error("%s:%d: error: in gvar_initializer : buf is null!", __FILE__, __LINE__);
  write_gvar_data(&head, init, var->ty, buf, 0);
  var->init_data = buf;
  var->rel = head.next;
}

// Returns true if a given token represents a type.
static bool is_typename(Token *tok)
{
  static HashMap map;
  if (map.capacity == 0)
  {
    static char *kw[] = {
        "void", "_Bool", "char", "short", "int", "long", "struct", "union",
        "typedef", "enum", "static", "extern", "_Alignas", "signed", "unsigned",
        "const", "volatile", "auto", "register", "restrict", "__restrict",
        "__restrict__", "_Noreturn", "float", "double", "typeof", "inline", "__inline",
        "_Thread_local", "__thread", "_Atomic", "_Complex", "__label__", "__typeof", "__int128"};

    for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++)
      hashmap_put(&map, kw[i], (void *)1);
  }

  return hashmap_get2(&map, tok->loc, tok->len) || find_typedef(tok);
}

// asm-stmt = "asm" ("volatile" | "inline")* "(" string-literal ")"
static Node *asm_stmt(Token **rest, Token *tok)
{
  if (current_fn) {
    current_fn->force_frame_pointer = true;
  }
  Node *node = new_node(ND_ASM, tok);
  tok = tok->next;

  while (equal(tok, "volatile") || equal(tok, "inline")  || equal(tok, "__inline"))
    tok = tok->next;

  SET_CTX(ctx);   
  tok = skip(tok, "(", ctx);
  if (tok->kind != TK_STR || tok->ty->base->kind != TY_CHAR)
    error_tok(tok, "%s:%d: in asm_stmt : expected string literal", __FILE__, __LINE__);

  // extended assembly like asm ( assembler_template: output operands (optional) : input operands (optional) : list of clobbered registers (optional))
  if (equal(tok->next, ":"))
  {
    //need_alloca_bottom();
    opt_omit_frame_pointer = false;
    node->asm_str = extended_asm(node, rest, tok, locals);
    if (!node->asm_str)
      error_tok(tok, "%s:%d: in asm_stmt : error during extended_asm function null returned!", __FILE__, __LINE__);
    return node;
  }
  node->asm_str = tok->str;
  SET_CTX(ctx);     
  *rest = skip(tok->next, ")", ctx);
  return node;
}

// stmt = "return" expr? ";"
//      | "if" "(" expr ")" stmt ("else" stmt)?
//      | "switch" "(" expr ")" stmt
//      | "case" const-expr ("..." const-expr)? ":" stmt
//      | "default" ":" stmt
//      | "for" "(" expr-stmt expr? ";" expr? ")" stmt
//      | "while" "(" expr ")" stmt
//      | "do" stmt "while" "(" expr ")" ";"
//      | "asm" asm-stmt
//      | "goto" (ident | "*" expr) ";"
//      | "break" ";"
//      | "continue" ";"
//      | ident ":" stmt
//      | "{" compound-stmt
//      | expr-stmt
static Node *stmt(Token **rest, Token *tok, bool chained) 
{


  if (equal(tok, "return"))
  {
    Type *ret_ty = current_fn->ty->return_ty;
    Node *node = new_node(ND_RETURN, tok);
    if (consume(rest, tok->next, ";"))
    {
      if (ret_ty->kind != TY_VOID)
      {
        error_tok(tok, "%s:%d: in stmt : Non-void function must return something", __FILE__, __LINE__);
      }
      return node;
    }


    Node *exp = expr(&tok, tok->next);
    SET_CTX(ctx);       
    *rest = skip(tok, ";", ctx);
    add_type(exp);
    // Type *ty = current_fn->ty->return_ty;
    // if (ty->kind != TY_STRUCT && ty->kind != TY_UNION)
    //   exp = new_cast(exp, current_fn->ty->return_ty);

    if (!exp->ty)
      error_tok(exp->tok, "%s:%d: in stmt : exp->ty is null", __FILE__, __LINE__);
      
    if (ret_ty->kind == TY_VOID && exp->ty->kind != TY_VOID)
    {
      error_tok(exp->tok, "%s:%d: in stmt : Void function must return void type expression", __FILE__, __LINE__);
    }
    if (ret_ty->kind != TY_VOID && exp->ty->kind == TY_VOID)
    {
      error_tok(exp->tok,
                "%s:%d: in stmt : Non-void function cannot return void type expression", __FILE__, __LINE__);
    }

    if (ret_ty->kind != TY_STRUCT && ret_ty->kind != TY_UNION)
      exp = new_cast(exp, ret_ty);
    node->lhs = exp;
    return node;
  }

  if (equal(tok, "if"))
  {
    Node *node = new_node(ND_IF, tok);
    SET_CTX(ctx);       
    tok = skip(tok->next, "(", ctx);
    node->cond = to_bool(expr(&tok, tok));


    if (isDotfile && dotf != NULL)
      fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->cond->kind), node->cond->unique_number);

    SET_CTX(ctx);        
    tok = skip(tok, ")", ctx);
    node->then = stmt(&tok, tok, true);

    if (isDotfile && dotf != NULL)
      fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->then->kind), node->then->unique_number);
    if (equal(tok, "else"))
    {
      node->els = stmt(&tok, tok->next, true);
      if (isDotfile && dotf != NULL)
        fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->els->kind), node->els->unique_number);
    }

    *rest = tok;
    return node;
  }

  //from COSMOPOLITAN adding function static_assertion
  if (equal(tok, "_Static_assert")) {
    Token *start = tok;
    *rest = static_assertion(tok);
    return new_node(ND_BLOCK, start);
  }

  if (equal(tok, "switch"))
  {
    Node *node = new_node(ND_SWITCH, tok);
    SET_CTX(ctx);      
    tok = skip(tok->next, "(", ctx);
    node->cond = expr(&tok, tok);

    SET_CTX(ctx);      
    tok = skip(tok, ")", ctx);

    Node *sw = current_switch;
    current_switch = node;

    char *brk = brk_label;
    brk_label = node->brk_label = new_unique_name();

    
    node->then = stmt(rest, tok, true);

    current_switch = sw;
    brk_label = brk;
    return node;
  }

  if (equal(tok, "case"))
  {
    if (!current_switch)
      error_tok(tok, "%s:%d: in stmt : stray case", __FILE__, __LINE__);

    Node *node = new_node(ND_CASE, tok);

    int64_t begin = const_expr(&tok, tok->next);
    int64_t end;
    
    add_type(current_switch->cond);

    if (equal(tok, "..."))
    {
      // [GNU] Case ranges, e.g. "case 1 ... 5:"
      end = const_expr(&tok, tok->next);
      // if (end < begin)
      //   error_tok(tok, "%s:%d: in stmt : empty case range specified", __FILE__, __LINE__);
    }
    else
    {
      end = begin;
    }

    if (current_switch->cond->ty->size == 4) {
      if (!current_switch->cond->ty->is_unsigned) {
        begin = (int32_t) begin;
        end = (int32_t) end;
      } else {
        begin = (uint32_t) begin;
        end = (uint32_t) end;
      }
    }

    if ((!current_switch->cond->ty->is_unsigned && (end < begin)) ||
      ((current_switch->cond->ty->is_unsigned && ((uint64_t)end < begin))))
      error_tok(tok, "%s:%d: in stmt : empty case range specified", __FILE__, __LINE__);

    SET_CTX(ctx); 
    tok = skip(tok, ":", ctx);
    VarAttr attr = {};
    tok = attribute_list(tok, &attr, thing_attributes);
    node->label = new_unique_name();
    if (chained) {
      if (is_typename(tok)) {
        node->lhs = compound_stmt2(rest, tok);
      } else {
      node->lhs = stmt(rest, tok, true);
      }
    } else
      *rest = tok;
    //duplicate case value detection
    for (Node *c = current_switch->case_next; c; c = c->case_next)
    {
      if (!(end < c->begin || begin > c->end))
        error_tok(tok, "%s:%d: in stmt : duplicated case value or overlapping range %ld", __FILE__, __LINE__, begin);
    }
    node->begin = begin;
    node->end = end;
    node->case_next = current_switch->case_next;
    current_switch->case_next = node;
    return node;
  }

  if (equal(tok, "default"))
  {
    if (!current_switch)
      error_tok(tok, "%s:%d: in stmt : stray default", __FILE__, __LINE__);

    Node *node = new_node(ND_CASE, tok);
    SET_CTX(ctx);        
    tok = skip(tok->next, ":", ctx);
    node->label = new_unique_name();
    if (chained) {
    if (is_typename(tok)) {
      node->lhs = compound_stmt2(rest, tok);
    } else {
      node->lhs = stmt(rest, tok, true);
    }
    } else
      *rest = tok;

    current_switch->default_case = node;
    return node;
  }

  if (equal(tok, "for"))
  {
    Node *node = new_node(ND_FOR, tok);
    SET_CTX(ctx);         
    tok = skip(tok->next, "(", ctx);

    enter_scope();

    char *brk = brk_label;
    char *cont = cont_label;
    brk_label = node->brk_label = new_unique_name();
    cont_label = node->cont_label = new_unique_name();

    if (is_typename(tok))
    {
      Type *basety = declspec(&tok, tok, NULL);
      node->init = declaration(&tok, tok, basety, NULL);
    }
    else
    {
      node->init = expr_stmt(&tok, tok);
    }
    if (!equal(tok, ";"))
    {
      node->cond = expr(&tok, tok);

      if (isDotfile && dotf != NULL)
        fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->cond->kind), node->cond->unique_number);
    }
    SET_CTX(ctx);      
    tok = skip(tok, ";", ctx);

    if (!equal(tok, ")"))
    {
      node->inc = expr(&tok, tok);

      if (isDotfile && dotf != NULL)
        fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->inc->kind), node->inc->unique_number);
    }
    SET_CTX(ctx);     
    tok = skip(tok, ")", ctx);

    node->then = stmt(rest, tok, true);

    if (isDotfile && dotf != NULL)
      fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->then->kind), node->then->unique_number);
    leave_scope();
    brk_label = brk;
    cont_label = cont;
    return node;
  }

  if (equal(tok, "while"))
  {
    Node *node = new_node(ND_FOR, tok);
    SET_CTX(ctx);     
    tok = skip(tok->next, "(", ctx);
    node->cond = expr(&tok, tok);
    SET_CTX(ctx);        
    tok = skip(tok, ")", ctx);

    char *brk = brk_label;
    char *cont = cont_label;
    brk_label = node->brk_label = new_unique_name();
    cont_label = node->cont_label = new_unique_name();

    node->then = stmt(rest, tok, true);
    brk_label = brk;
    cont_label = cont;
    return node;
  }

  if (equal(tok, "do"))
  {
    Node *node = new_node(ND_DO, tok);

    char *brk = brk_label;
    char *cont = cont_label;
    brk_label = node->brk_label = new_unique_name();
    cont_label = node->cont_label = new_unique_name();

    node->then = stmt(&tok, tok->next, true);
    brk_label = brk;
    cont_label = cont;
    SET_CTX(ctx); 
    tok = skip(tok, "while", ctx);
    SET_CTX(ctx);     
    tok = skip(tok, "(", ctx);
    node->cond = expr(&tok, tok);
    SET_CTX(ctx);       
    tok = skip(tok, ")", ctx);
    SET_CTX(ctx);        
    *rest = skip(tok, ";", ctx);
    return node;
  }

  if (equal(tok, "asm") || equal(tok, "__asm__") || equal(tok, "__asm")) 
    return asm_stmt(rest, tok);

  if (equal(tok, "goto"))
  {
    if (equal(tok->next, "*"))
    {
      // [GNU] `goto *ptr` jumps to the address specified by `ptr`.
      Node *node = new_node(ND_GOTO_EXPR, tok);
      node->lhs = expr(&tok, tok->next->next);
      SET_CTX(ctx);         
      *rest = skip(tok, ";", ctx);
      return node;
    }

    Node *node = new_node(ND_GOTO, tok);
    node->label = get_ident(tok->next);
    node->goto_next = gotos;
    gotos = node;
    SET_CTX(ctx);        
    *rest = skip(tok->next->next, ";", ctx);
    return node;
  }

  if (equal(tok, "break"))
  {
    if (!brk_label)
      error_tok(tok, "%s:%d: in stmt : stray break", __FILE__, __LINE__);
    Node *node = new_node(ND_GOTO, tok);
    node->unique_label = brk_label;
    SET_CTX(ctx);     
    *rest = skip(tok->next, ";", ctx);
    return node;
  }

  if (equal(tok, "continue"))
  {
    if (!cont_label)
      error_tok(tok, "%s:%d: in stmt : stray continue", __FILE__, __LINE__);
    Node *node = new_node(ND_GOTO, tok);
    node->unique_label = cont_label;
    SET_CTX(ctx);        
    *rest = skip(tok->next, ";", ctx);
    return node;
  }


  if ((tok->kind == TK_IDENT && equal(tok->next, ":")))
  {
    Node *node = new_node(ND_LABEL, tok);
    node->label = strndup(tok->loc, tok->len);
    node->unique_label = new_unique_name();

    //node->lhs = stmt(rest, tok->next->next);
    tok = tok->next->next;
    if (chained)
      node->lhs = stmt(rest, tok, true);
    else
      *rest = tok;
    node->goto_next = labels;
    labels = node;
    return node;
  }
  if (equal(tok, "{")) 
    return compound_stmt(rest, tok->next, NULL);


  return expr_stmt(rest, tok);
}

// compound-stmt = (typedef | declaration | stmt)* "}"
static Node *compound_stmt(Token **rest, Token *tok, Node **last) 
{
  Node *node = new_node(ND_BLOCK, tok);
  Node head = {0};
  Node *cur = &head;
  enter_scope();

  //while (!equal(tok, "}"))
  for (; !equal(tok, "}"); add_type(cur)) 
  {
    VarAttr attr = {};
    tok = attribute_list(tok, &attr, thing_attributes);

    if (is_typename(tok) && !equal(tok->next, ":"))
    {
      //VarAttr attr = {};
      Type *basety = declspec(&tok, tok, &attr);
      if (attr.is_typedef)
      {
  
        Node *vla_calc = parse_typedef(&tok, tok, basety, &attr);
        cur = cur->next = new_unary(ND_EXPR_STMT, vla_calc, tok);
        add_type(cur);
        continue;
      }

      if (is_function(tok))
      {
        tok = function(tok, basety, &attr);
        continue;
      }

      if (attr.is_extern)
      {
        tok = global_declaration(tok, basety, &attr);
        continue;
      }
      cur = cur->next = declaration(&tok, tok, basety, &attr);
    }
    else
    {
      //case specific of fallthrough
      //VarAttr attr= {};
      tok = attribute_list(tok, &attr, thing_attributes);
      cur = cur->next = stmt(&tok, tok, false);
    }
    add_type(cur);
  }
  
  if (last)
    *last = cur;

  leave_scope();

  node->body = head.next;

  if (isDotfile && dotf != NULL)
  {
    if (node->body != NULL)
      fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->body->kind), node->body->unique_number);
  }
  *rest = tok->next;
  return node;
}

// compound-stmt = (typedef | declaration | stmt)* 
//case of missing braces for compound statement
static Node *compound_stmt2(Token **rest, Token *tok)
{
  Node *node = new_node(ND_BLOCK, tok);
  Node head = {};
  Node *cur = &head;
  enter_scope();
  while (!equal(tok, "}") && !equal(tok, "case") && !equal(tok, "default"))
  {
    VarAttr attr = {};
    tok = attribute_list(tok, &attr, thing_attributes);
    if (is_typename(tok) && !equal(tok->next, ":"))
    {
      //VarAttr attr = {};
      Type *basety = declspec(&tok, tok, &attr);
      if (attr.is_typedef)
      {
        Node *vla_calc = parse_typedef(&tok, tok, basety, &attr);
        cur = cur->next = new_unary(ND_EXPR_STMT, vla_calc, tok);
        add_type(cur);
        continue;
      }

      if (is_function(tok))
      {
        tok = function(tok, basety, &attr);
        continue;
      }

      if (attr.is_extern)
      {
        tok = global_declaration(tok, basety, &attr);
        continue;
      }
      //cur = cur->next = declaration(&tok, tok, basety, &attr);
      Node *expr = declaration(&tok, tok, basety, &attr);
      if (expr)
        cur = cur->next = new_unary(ND_EXPR_STMT, expr, tok);
      continue;
    }
    else
    {
      //case specific of fallthrough
      //VarAttr attr= {};
      tok = attribute_list(tok, &attr, thing_attributes);
      cur = cur->next = stmt(&tok, tok, false);
    }
    //add_type(cur);
  }

  leave_scope();

  node->body = head.next;

  if (isDotfile && dotf != NULL)
  {
    if (node->body != NULL)
      fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->body->kind), node->body->unique_number);
  }
  *rest = tok;
  return node;
}


// expr-stmt = expr? ";"
static Node *expr_stmt(Token **rest, Token *tok)
{
  if (equal(tok, ";"))
  {
    *rest = tok->next;
    return new_node(ND_BLOCK, tok);
  }

  Node *node = new_node(ND_EXPR_STMT, tok);
  node->lhs = expr(&tok, tok);

  if (isDotfile && dotf != NULL)
    fprintf(dotf, "%s%d -> %s%d\n", nodekind2str(node->kind), node->unique_number, nodekind2str(node->lhs->kind), node->lhs->unique_number);

  SET_CTX(ctx);     
  *rest = skip(tok, ";", ctx);
  return node;
}

// expr = assign ("," expr)?
static Node *expr(Token **rest, Token *tok)
{

  Node *node = assign(&tok, tok);

  if (equal(tok, ","))
    return new_binary(ND_COMMA, node, expr(rest, tok->next), tok);
  *rest = tok;
  return node;
}

int64_t eval(Node *node)
{
  return eval2(node, NULL);
}


// Evaluate a given node as a constant expression.
//
// A constant expression is either just a number or ptr+n where ptr
// is a pointer to a global variable and n is a postiive/negative
// number. The latter form is accepted only as an initialization
// expression for a global variable.
static int64_t eval2(Node *node, char ***label)
{
  add_type(node);

  if (is_flonum(node->ty))
    return eval_double(node);

  switch (node->kind)
  {
  case ND_ADD:
    if (label) {
      char **l1 = NULL;
      char **l2 = NULL;
      int64_t v1 = eval2(node->lhs, &l1);
      int64_t v2 = eval2(node->rhs, &l2);
      if (l1 && l2)
        error_tok(node->tok, "%s:%d: in eval2 : invalid constant address expression", __FILE__, __LINE__);
      if (l2) {
        *label = l2;
        return v1 + v2;
      }
      if (l1)
        *label = l1;
      return v1 + v2;
    }
    return eval2(node->lhs, label) + eval(node->rhs);
  case ND_SUB:
    if (label) {
      char **l1 = NULL;
      char **l2 = NULL;
      int64_t v1 = eval2(node->lhs, &l1);
      int64_t v2 = eval2(node->rhs, &l2);
      if (l2)
        error_tok(node->tok, "%s:%d: in eval2 : invalid constant address expression", __FILE__, __LINE__);
      if (l1)
        *label = l1;
      return v1 - v2;
    }
    return eval2(node->lhs, label) - eval(node->rhs);
  case ND_MUL:
    return eval(node->lhs) * eval(node->rhs);
  case ND_DIV:
    // Check for division overflow
    if (eval(node->lhs) == LLONG_MIN && eval(node->rhs) == -1) {
      warn_tok(node->tok, "in eval2: %s:%d: integer overflow!", __FILE__, __LINE__);
      return 0;  // Return 0 or any other value you think is appropriate
    }
    if (eval(node->rhs) == 0)
          error_tok(node->tok, "%s  %d: in eval2 : eval(node->rhs) caused a division by zero!", __FILE__, __LINE__ );
    if (node->ty && node->ty->is_unsigned)
      return (uint64_t)eval(node->lhs) / (uint64_t)eval(node->rhs);
    return eval(node->lhs) / eval(node->rhs);
  case ND_POS:
    return eval(node->lhs);    
  case ND_NEG:
      if (node->ty->size == 4) {
      if (node->ty->is_unsigned)
        return (uint32_t)-eval(node->lhs);
      return (int32_t)-eval(node->lhs);
    }
    return -eval(node->lhs);
  case ND_MOD:
    // Check for division overflow
    if (eval(node->lhs) == LLONG_MIN && eval(node->rhs) == -1) {
      warn_tok(node->tok, "in eval2: %s:%d: integer overflow!", __FILE__, __LINE__);
      return 0;  
    }
    if (eval(node->rhs) == 0)
          error_tok(node->tok, "%s  %d: in eval2 : eval(node->rhs) caused a division by zero!", __FILE__, __LINE__ );    
    if (node->ty && node->ty->is_unsigned)
      return (uint64_t)eval(node->lhs) % eval(node->rhs);
    return eval(node->lhs) % eval(node->rhs);
  case ND_BITAND:
    return eval(node->lhs) & eval(node->rhs);
  case ND_BITOR:
    return eval(node->lhs) | eval(node->rhs);
  case ND_BITXOR:
    return eval(node->lhs) ^ eval(node->rhs);
  case ND_SHL:
    return eval(node->lhs) << eval(node->rhs);
  case ND_SHR:
    // if (node->ty->is_unsigned && node->ty->size == 8)
    //   return (uint64_t)eval(node->lhs) >> eval(node->rhs);
    // return eval(node->lhs) >> eval(node->rhs);
    if (node->ty->is_unsigned) {
      if (node->ty->size == 4)
        return (uint32_t)eval(node->lhs) >> eval(node->rhs);
      return (uint64_t)eval(node->lhs) >> eval(node->rhs);
    }
    if (node->ty->size == 4)
      return (int32_t)eval(node->lhs) >> eval(node->rhs);
    return eval(node->lhs) >> eval(node->rhs);    
  case ND_EQ:
    //from @fuhsnn fixing when lhs is a float
    if (is_flonum(node->lhs->ty))
      return eval_double(node->lhs) == eval_double(node->rhs);
    return eval(node->lhs) == eval(node->rhs);
  case ND_NE:
    //from @fuhsnn fixing when lhs is a float
    if (is_flonum(node->lhs->ty))
      return eval_double(node->lhs) != eval_double(node->rhs);
    return eval(node->lhs) != eval(node->rhs);
  case ND_LT:
    //from @fuhsnn fixing when lhs is a float
    if (is_flonum(node->lhs->ty))
      return eval_double(node->lhs) < eval_double(node->rhs);
    if (node->lhs->ty->is_unsigned)
      return (uint64_t)eval(node->lhs) < eval(node->rhs);
    return eval(node->lhs) < eval(node->rhs);
  case ND_LE:
    //from @fuhsnn fixing when lhs is a float
    if (is_flonum(node->lhs->ty))
      return eval_double(node->lhs) <= eval_double(node->rhs);
    if (node->lhs->ty->is_unsigned)
      return (uint64_t)eval(node->lhs) <= eval(node->rhs);
    return eval(node->lhs) <= eval(node->rhs);
  case ND_COND:
    return eval(node->cond) ? eval2(node->then, label) : eval2(node->els, label);
  case ND_COMMA:
    eval2(node->lhs, label);
    return eval2(node->rhs, label);
  case ND_NOT:
    //from @fuhsnn fixing when lhs is a float
    if (is_flonum(node->lhs->ty))
      return !eval_double(node->lhs);
    return !eval(node->lhs);
  case ND_BITNOT:
    if (node->ty->size == 4) {
      if (node->ty->is_unsigned)
        return (uint32_t)~eval(node->lhs);
      return (int32_t)~eval(node->lhs);
    }  
    return ~eval(node->lhs);
  case ND_LOGAND:
    return eval(node->lhs) && eval(node->rhs);
  case ND_LOGOR:
    return eval(node->lhs) || eval(node->rhs);
  case ND_CAST: {  
     if (is_flonum(node->lhs->ty)) {
        if (node->ty->kind == TY_BOOL)
          return !!eval_double(node->lhs);
        if (node->ty->size == 8 && node->ty->is_unsigned)
          return (uint64_t)eval_double(node->lhs);
        return eval_sign_extend(node->ty, eval_double(node->lhs));
      }
      if (node->ty->kind == TY_BOOL) {
        if (node->lhs->kind == ND_VAR && is_array(node->lhs->ty))
          return 1;
        return !!eval2(node->lhs, label);
      }
      int64_t val = eval2(node->lhs, label);
      if (is_integer(node->ty))
        return eval_sign_extend(node->ty, val);

      return val;
  }
  case ND_ADDR:
    return eval_rval(node->lhs, label);
  case ND_LABEL_VAL:
    *label = &node->unique_label;
    return 0;
  // fixing issue #115
  // case ND_DEREF:
  //   return eval2(node->lhs, label);
  //from @fuhsnn eval2():Evaluate ND_DEREF for TY_ARRAY
  case ND_DEREF:
    // if (node->ty->kind != TY_ARRAY && !is_vector(node->ty))
    //   error_tok(node->tok, "%s:%d: in eval2 : not a compile-time constant node->ty->kind=%d ", __FILE__, __LINE__, node->ty->kind);
    return eval2(node->lhs, label);    
  case ND_MEMBER:
    
    if (!label) {
      error_tok(node->tok, "%s:%d: in eval2 : not a compile-time constant", __FILE__, __LINE__ );
    }
    // if (node->ty->kind != TY_ARRAY) {
    //   error_tok(node->tok, "%s:%d: in eval2 : invalid initializer", __FILE__, __LINE__);
    // }
    return eval_rval(node->lhs, label) + node->member->offset;
  case ND_VAR:
    if (is_vector(node->var->ty))
      return 0; 
 
    if (node->var->is_static || node->var->is_definition) {
      if (label)
          *label = &node->var->name;
      return 0;          
    }
    
    //trying to fix ======ISS-145 compiling util-linux failed with invalid initalizer2 
    // if (node->var->ty->kind != TY_ARRAY && node->var->ty->kind != TY_FUNC && node->var->ty->kind != TY_INT) {
    //   error_tok(node->tok, "%s:%d: in eval2 : invalid initializer2 %d", __FILE__, __LINE__, node->var->ty->kind);
    // }
    //trying to fix ======ISS-145 compiling util-linux failed with invalid initalizer2 
    if (is_integer(node->var->ty))
      return 0;
    if (!label) {
      error_tok(node->tok, "%s:%d : in eval2 : not a compile-time constant %d", __FILE__, __LINE__, node->var->ty->kind);
    }
    *label = &node->var->name;
    return 0;
  case ND_NUM:
    return node->val;

  }
  error_tok(node->tok, "%s:%d: in eval2 : not a compile-time constant3", __FILE__, __LINE__);
}


static int64_t eval_rval(Node *node, char ***label)
{
  switch (node->kind)
  {
  case ND_VAR:
    if (node->var->is_local)
      error_tok(node->tok, "%s:%d: in eval2 : not a compile-time constant4", __FILE__, __LINE__);

    // Use the symbol name that will be emitted for this variable.
    // For variables/functions with an `asm` label, the emitted symbol
    // differs from the C identifier.
    *label = node->var->asmname ? &node->var->asmname : &node->var->name;
    return 0;
  case ND_DEREF:
    return eval2(node->lhs, label);
  case ND_MEMBER:
    return eval_rval(node->lhs, label) + node->member->offset;
  case ND_ADDR:
    return 1;
  }

  error_tok(node->tok, "%s:%d: in eval2 : invalid initializer3", __FILE__, __LINE__);
}

static bool is_const_expr(Node *node)
{
  add_type(node);  

  switch (node->kind)
  {
  case ND_ADD:
  case ND_SUB:
  case ND_MUL:
  case ND_DIV:
  case ND_MOD:
  case ND_BITAND:
  case ND_BITOR:
  case ND_BITXOR:
  case ND_SHL:
  case ND_SHR:
  case ND_EQ:
  case ND_NE:
  case ND_LT:
  case ND_LE:
  case ND_LOGAND:
  case ND_LOGOR:
    return is_const_expr(node->lhs) && is_const_expr(node->rhs);
  case ND_COND:
    if (!is_const_expr(node->cond))
      return false;
    return is_const_expr(eval(node->cond) ? node->then : node->els);
  case ND_COMMA:
    return is_const_expr(node->rhs) && is_const_expr(node->lhs);
  case ND_POS:
  case ND_NEG:
  case ND_NOT:
  case ND_BITNOT:
  case ND_CAST: 
    return is_const_expr(node->lhs);
  case ND_NUM:
    return true;
  case ND_MEMBER:
  case ND_ADDR:
  case ND_DEREF:
    return is_const_expr(node->lhs);
  }
  
  return false;
}

int64_t const_expr(Token **rest, Token *tok)
{
  Node *node = conditional(rest, tok);
  add_type(node);
  return eval(node);
}

static long double eval_double(Node *node)
{
  add_type(node);

  if (is_integer(node->ty))
  {
    if (node->ty->is_unsigned)
      return (unsigned long)eval(node);
    return eval(node);
  }

  switch (node->kind)
  {
  case ND_ADD:
    return eval_double(node->lhs) + eval_double(node->rhs);
  case ND_SUB:
    return eval_double(node->lhs) - eval_double(node->rhs);
  case ND_MUL:
    return eval_double(node->lhs) * eval_double(node->rhs);
  case ND_DIV:
    return eval_double(node->lhs) / eval_double(node->rhs);
  case ND_POS:
    return eval_double(node->lhs);    
  case ND_NEG:
    return -eval_double(node->lhs);
  case ND_COND:
    return eval_double(node->cond) ? eval_double(node->then) : eval_double(node->els);
  case ND_COMMA:
    eval_double(node->lhs);
    return eval_double(node->rhs);
  case ND_CAST:
    if (is_flonum(node->lhs->ty)) {
      if (node->ty->size == 4)
        return (float)eval_double(node->lhs);
      if (node->ty->size == 8)
        return (double)eval_double(node->lhs);
      return eval_double(node->lhs);
    }
    if (node->lhs->ty->size == 8 && node->lhs->ty->is_unsigned)
      return (uint64_t)eval(node->lhs);
    return eval(node->lhs);
  case ND_BUILTIN_NAN:
  case ND_BUILTIN_NANF:
  case ND_BUILTIN_INFF:
  case ND_FPCLASSIFY:
  case ND_NUM:
    return node->fval;
  }

  error_tok(node->tok, "%s:%d: in eval_double : not a compile-time constant %d", __FILE__, __LINE__, node->kind);
}

// Check if it is safe to re-evaluate an lvalue without introducing a temp.
// This intentionally accepts only address-stable forms rooted in variables.
static bool is_safe_lvalue(Node *node) {
  if (!node)
    return false;

  if (node->kind == ND_VAR)
    return true;

  if (node->kind == ND_MEMBER && !is_bitfield(node))
    return is_safe_lvalue(node->lhs);

  return false;
}

static Node *atomic_op(Node *binary, bool return_old) {

  Token *tok = binary->tok;
  Node head = {0};
  Node *cur = &head;

  Obj *addr = new_lvar("", pointer_to(binary->lhs->ty), NULL);
  Obj *val = new_lvar("", binary->rhs->ty, NULL);
  Obj *old = new_lvar("", binary->lhs->ty, NULL);
  Obj *new = new_lvar("", binary->lhs->ty, NULL);

  cur = cur->next =
    new_unary(ND_EXPR_STMT,
              new_binary(ND_ASSIGN, new_var_node(addr, tok),
                         new_unary(ND_ADDR, binary->lhs, tok), tok),
              tok);

  cur = cur->next =
    new_unary(ND_EXPR_STMT,
              new_binary(ND_ASSIGN, new_var_node(val, tok), binary->rhs, tok),
              tok);

  cur = cur->next =
    new_unary(ND_EXPR_STMT,
              new_binary(ND_ASSIGN, new_var_node(old, tok),
                         new_unary(ND_DEREF, new_var_node(addr, tok), tok), tok),
              tok);

  Node *loop = new_node(ND_DO, tok);
  loop->brk_label = new_unique_name();
  loop->cont_label = new_unique_name();

  Node *body = new_binary(ND_ASSIGN,
                          new_var_node(new, tok),
                          new_binary(binary->kind, new_var_node(old, tok),
                                     new_var_node(val, tok), tok),
                          tok);

  loop->then = new_node(ND_BLOCK, tok);
  loop->then->body = new_unary(ND_EXPR_STMT, body, tok);

  Node *cas = new_node(ND_CAS, tok);
  cas->cas_addr = new_var_node(addr, tok);
  cas->cas_old = new_unary(ND_ADDR, new_var_node(old, tok), tok);
  cas->cas_new = new_var_node(new, tok);
  loop->cond = new_unary(ND_NOT, cas, tok);

  cur = cur->next = loop;

  if (return_old)
    cur->next = new_unary(ND_EXPR_STMT, new_var_node(old, tok), tok);
  else
    cur->next = new_unary(ND_EXPR_STMT, new_var_node(new, tok), tok);

  Node *node = new_node(ND_STMT_EXPR, tok);
  node->body = head.next;
  return node;
}

// Convert op= operators to expressions containing an assignment.
//
// In general, `A op= C` is converted to ``tmp = &A, *tmp = *tmp op B`.
// However, if a given expression is of form `A.x op= C`, the input is
// converted to `tmp = &A, (*tmp).x = (*tmp).x op C` to handle assignments
// to bitfields.
static Node *to_assign(Node *binary)
{
  add_type(binary->lhs);
  add_type(binary->rhs);
  Token *tok = binary->tok;

  if (!current_fn)
    return new_binary(ND_ASSIGN, binary->lhs,
                      new_binary(binary->kind, binary->lhs, binary->rhs, tok),
                      tok);

  // -O1+: for simple lvalues, avoid creating a hidden pointer temp for op=
  // lowering. This reduces stack-frame pressure in recursive hot paths.
  if (opt_optimize_level1 && !binary->lhs->ty->is_atomic && is_safe_lvalue(binary->lhs)) {
      return new_binary(ND_ASSIGN, binary->lhs,
                        new_binary(binary->kind, binary->lhs, binary->rhs, tok),
                        tok);
  }
    // If A is an atomic type, Convert `A op= B` to
  //
  // ({
  //   T1 *addr = &A; T2 val = (B); T1 old = *addr; T1 new;
  //   do {
  //    new = old op val;
  //   } while (!atomic_compare_exchange_strong(addr, &old, new));
  //   new;
  // })
  // If A is an atomic type, Convert `A op= B` to atomic_op_fetch(&A, B)
  if (binary->lhs->ty->is_atomic)
    return atomic_op(binary, false);
    
  // Convert `A.x op= C` to `tmp = &A, (*tmp).x = (*tmp).x op C`.
  if (binary->lhs->kind == ND_MEMBER)
  {
    Obj *var = new_lvar("", pointer_to(binary->lhs->lhs->ty), NULL);
    Node *expr1 = new_binary(ND_ASSIGN, new_var_node(var, tok),
                             new_unary(ND_ADDR, binary->lhs->lhs, tok), tok);

    Node *expr2 = new_unary(ND_MEMBER,
                            new_unary(ND_DEREF, new_var_node(var, tok), tok),
                            tok);
    expr2->member = binary->lhs->member;

    Node *expr3 = new_unary(ND_MEMBER,
                            new_unary(ND_DEREF, new_var_node(var, tok), tok),
                            tok);
    expr3->member = binary->lhs->member;

    Node *expr4 = new_binary(ND_ASSIGN, expr2,
                             new_binary(binary->kind, expr3, binary->rhs, tok),
                             tok);

    return new_binary(ND_COMMA, expr1, expr4, tok);
  }


  // Convert `A op= B` to ``tmp = &A, *tmp = *tmp op B`.
  Obj *var = new_lvar("", pointer_to(binary->lhs->ty), NULL);
  Node *expr1 = new_binary(ND_ASSIGN, new_var_node(var, tok),
                           new_unary(ND_ADDR, binary->lhs, tok), tok);

  Node *expr2 =
      new_binary(ND_ASSIGN,
                 new_unary(ND_DEREF, new_var_node(var, tok), tok),
                 new_binary(binary->kind,
                            new_unary(ND_DEREF, new_var_node(var, tok), tok),
                            binary->rhs,
                            tok),
                 tok);

  return new_binary(ND_COMMA, expr1, expr2, tok);
}

// assign    = conditional (assign-op assign)?
// assign-op = "=" | "+=" | "-=" | "*=" | "/=" | "%=" | "&=" | "|=" | "^="
//           | "<<=" | ">>="
static Node *assign(Token **rest, Token *tok)
{

  Node *node = conditional(&tok, tok);

  if (equal(tok, "="))
    return new_binary(ND_ASSIGN, node, assign(rest, tok->next), tok);

  if (equal(tok, "+="))
    return to_assign(new_add(node, assign(rest, tok->next), tok, false));

  if (equal(tok, "-="))
    return to_assign(new_sub(node, assign(rest, tok->next), tok, false));

  if (equal(tok, "*="))
    return to_assign(new_binary(ND_MUL, node, assign(rest, tok->next), tok));

  if (equal(tok, "/="))
    return to_assign(new_binary(ND_DIV, node, assign(rest, tok->next), tok));

  if (equal(tok, "%="))
    return to_assign(new_binary(ND_MOD, node, assign(rest, tok->next), tok));

  if (equal(tok, "&="))
    return to_assign(new_binary(ND_BITAND, node, assign(rest, tok->next), tok));

  if (equal(tok, "|="))
    return to_assign(new_binary(ND_BITOR, node, assign(rest, tok->next), tok));

  if (equal(tok, "^="))
    return to_assign(new_binary(ND_BITXOR, node, assign(rest, tok->next), tok));

  if (equal(tok, "<<="))
    return to_assign(new_binary(ND_SHL, node, assign(rest, tok->next), tok));

  if (equal(tok, ">>="))
    return to_assign(new_binary(ND_SHR, node, assign(rest, tok->next), tok));

  *rest = tok;
  return node;
}

// conditional = logor ("?" expr? ":" conditional)?
static Node *conditional(Token **rest, Token *tok)
{
  Node *cond = logor(&tok, tok);


  if (!equal(tok, "?"))
  {
    *rest = tok;
    return cond;
  }


  if (equal(tok->next, ":") || equal(tok, ","))
  {
    // [GNU] Compile `a ?: b` as `tmp = a, tmp ? tmp : b`.
    add_type(cond);
    Obj *var = new_lvar("", cond->ty, NULL);
    Node *lhs = new_binary(ND_ASSIGN, new_var_node(var, tok), cond, tok);
    Node *rhs = new_node(ND_COND, tok);
    //commit 2e138bb from slimcc
    rhs->cond = to_bool(new_var_node(var, tok));
    rhs->then = new_var_node(var, tok);
    rhs->els = conditional(rest, tok->next->next);
    return new_binary(ND_COMMA, lhs, rhs, tok);
  }

  Node *node = new_node(ND_COND, tok);
  //commit 2e138bb from slimcc
  node->cond = to_bool(cond);
  node->then = expr(&tok, tok->next);
  SET_CTX(ctx);     
  tok = skip(tok, ":", ctx);
  node->els = conditional(rest, tok);
  return node;
}

// logor = logand ("||" logand)*
static Node *logor(Token **rest, Token *tok)
{
  Node *node = logand(&tok, tok);
  while (equal(tok, "||"))
  {
    Token *start = tok;
    //commit 2e138bb from slimcc
    node = new_binary(ND_LOGOR, to_bool(node), to_bool(logand(&tok, tok->next)), start);
  }
  *rest = tok;
  return node;
}

// logand = bitor ("&&" bitor)*
static Node *logand(Token **rest, Token *tok)
{
  Node *node = bitor (&tok, tok);
  while (equal(tok, "&&"))
  {
    Token *start = tok;
    //commit 2e138bb from slimcc
    node = new_binary(ND_LOGAND, to_bool(node), to_bool(bitor(&tok, tok->next)), start);
  }
  *rest = tok;
  return node;
}

// bitor = bitxor ("|" bitxor)*
static Node * bitor (Token * *rest, Token *tok)
{
  Node *node = bitxor(&tok, tok);
  while (equal(tok, "|"))
  {
    Token *start = tok;
    node = new_binary(ND_BITOR, node, bitxor(&tok, tok->next), start);
    promote_scalar_to_vector(node);
  }
  *rest = tok;
  return node;
}

// bitxor = bitand ("^" bitand)*
static Node *bitxor(Token **rest, Token *tok)
{
  Node *node = bitand(&tok, tok);
  while (equal(tok, "^"))
  {
    Token *start = tok;
    node = new_binary(ND_BITXOR, node, bitand(&tok, tok->next), start);
    promote_scalar_to_vector(node);
  }
  *rest = tok;
  return node;
}

// bitand = equality ("&" equality)*
static Node *bitand(Token **rest, Token *tok)
{
  Node *node = equality(&tok, tok);
  while (equal(tok, "&"))
  {
    Token *start = tok;
    node = new_binary(ND_BITAND, node, equality(&tok, tok->next), start);
    promote_scalar_to_vector(node);
  }
  *rest = tok;
  return node;
}

// equality = relational ("==" relational | "!=" relational)*
static Node *equality(Token **rest, Token *tok)
{
  Node *node = relational(&tok, tok);

  for (;;)
  {
    Token *start = tok;
 
    if (equal(tok, "=="))
    {
      node = new_binary(ND_EQ, node, relational(&tok, tok->next), start);
      continue;
    }

    if (equal(tok, "!="))
    {
      node = new_binary(ND_NE, node, relational(&tok, tok->next), start);
      continue;
    }

    *rest = tok;
    return node;
  }
}

// relational = shift ("<" shift | "<=" shift | ">" shift | ">=" shift)*
static Node *relational(Token **rest, Token *tok)
{
  Node *node = shift(&tok, tok);

  for (;;)
  {
    Token *start = tok;

    if (equal(tok, "<"))
    {
      node = new_binary(ND_LT, node, shift(&tok, tok->next), start);
      continue;
    }

    if (equal(tok, "<="))
    {
      node = new_binary(ND_LE, node, shift(&tok, tok->next), start);
      continue;
    }

    if (equal(tok, ">"))
    {
      node = new_binary(ND_LT, shift(&tok, tok->next), node, start);
      continue;
    }

    if (equal(tok, ">="))
    {
      node = new_binary(ND_LE, shift(&tok, tok->next), node, start);
      continue;
    }

    *rest = tok;
    return node;
  }
}

// shift = add ("<<" add | ">>" add)*
static Node *shift(Token **rest, Token *tok)
{
  Node *node = add(&tok, tok);
  for (;;)
  {
    Token *start = tok;

    if (equal(tok, "<<"))
    {
      node = new_binary(ND_SHL, node, add(&tok, tok->next), start);
      continue;
    }

    if (equal(tok, ">>"))
    {
      node = new_binary(ND_SHR, node, add(&tok, tok->next), start);
      continue;
    }

    *rest = tok;
    return node;
  }
}

// In C, `+` operator is overloaded to perform the pointer arithmetic.
// If p is a pointer, p+n adds not n but sizeof(*p)*n to the value of p,
// so that p+n points to the location n elements (not bytes) ahead of p.
// In other words, we need to scale an integer value before adding to a
// pointer value. This function takes care of the scaling.
static Node *new_add(Node *lhs, Node *rhs, Token *tok, bool is_op)
{
  
  add_type(lhs);
  add_type(rhs);

  //case of vectors + sclaras
  if (is_op && (is_vector(lhs->ty) || is_vector(rhs->ty))) {
    if (is_vector(lhs->ty) && !is_vector(rhs->ty)) {
      rhs = scalar_to_vector(rhs, lhs->ty);
      rhs->ty = lhs->ty;
    }
    else if (is_vector(rhs->ty) && !is_vector(lhs->ty)) {
      lhs = scalar_to_vector(lhs, rhs->ty);
      lhs->ty = rhs->ty;
    }
  }

  // case of vectors
  if (is_vector(lhs->ty) && is_vector(rhs->ty)) {
    
    if (lhs->ty->array_len != rhs->ty->array_len)
      error_tok(tok, "%s:%d: in new_add: incompatible vector types", __FILE__, __LINE__);
    Node *node = new_binary(ND_ADD, lhs, rhs, tok);
    node->ty =  lhs->ty;
    return node;
  }

  // num + num
  if (is_numeric(lhs->ty) && is_numeric(rhs->ty))
    return new_binary(ND_ADD, lhs, rhs, tok);
  
  if ((lhs->ty->base == NULL && rhs->ty->base == NULL) || (lhs->ty->base != NULL && rhs->ty->base != NULL)) {
    error_tok(tok, "%s:%d: in new_add : invalid operands", __FILE__, __LINE__);
  }

  // Canonicalize `num + ptr` to `ptr + num`.
  if (!lhs->ty->base && rhs->ty->base)
  {
    Node *tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }

  // VLA + num
  if (lhs->ty->base->kind == TY_VLA) {
    if (!lhs->ty->base->vla_size)
      rhs = new_binary(ND_MUL, rhs, new_long(lhs->ty->base->base->size, tok), tok);
    else
    rhs = new_binary(ND_MUL, rhs, new_var_node(lhs->ty->base->vla_size, tok), tok);
    return new_binary(ND_ADD, lhs, rhs, tok);
  }

  // ptr + num
  rhs = new_binary(ND_MUL, rhs, new_long(lhs->ty->base->size, tok), tok);
  return new_binary(ND_ADD, lhs, rhs, tok);
}

// Like `+`, `-` is overloaded for the pointer type.
static Node *new_sub(Node *lhs, Node *rhs, Token *tok, bool is_op)
{

  add_type(lhs);
  add_type(rhs);

  
  //case of vectors + scalars
  if (is_op && (is_vector(lhs->ty) || is_vector(rhs->ty))) {
    if (is_vector(lhs->ty) && !is_vector(rhs->ty)) {
      rhs = scalar_to_vector(rhs, lhs->ty);
      rhs->ty = lhs->ty;
    }
    else if (is_vector(rhs->ty) && !is_vector(lhs->ty)) {
      lhs = scalar_to_vector(lhs, rhs->ty);
      lhs->ty = rhs->ty;
    }
  }

  
  // case of vectors
  if (is_vector(lhs->ty) && is_vector(rhs->ty)) {
    if (lhs->ty->array_len != rhs->ty->array_len || lhs->ty->base->kind != rhs->ty->base->kind)
      error_tok(tok, "%s:%d: in new_sub : incompatible vector types", __FILE__, __LINE__);

    Node *node = new_binary(ND_SUB, lhs, rhs, tok);
    node->ty = lhs->ty; 
    return node;
  }

  // num - num
  if (is_numeric(lhs->ty) && is_numeric(rhs->ty))
    return new_binary(ND_SUB, lhs, rhs, tok);

  // VLA + num
  if (lhs->ty->base->kind == TY_VLA) {
    rhs = new_binary(ND_MUL, rhs, new_var_node(lhs->ty->base->vla_size, tok), tok);
    add_type(rhs);
    Node *node = new_binary(ND_SUB, lhs, rhs, tok);
    node->ty = lhs->ty;
    return node;
  }

  // ptr - num
  if (lhs->ty->base && is_integer(rhs->ty))
  {
    rhs = new_binary(ND_MUL, rhs, new_long(lhs->ty->base->size, tok), tok);
    add_type(rhs);
    Node *node = new_binary(ND_SUB, lhs, rhs, tok);
    node->ty = lhs->ty;
    return node;
  }

  // ptr - ptr, which returns how many elements are between the two.
  if (lhs->ty->base && rhs->ty->base)
  {
    Node *node = new_binary(ND_SUB, lhs, rhs, tok);
    node->ty = ty_long;
    return new_binary(ND_DIV, node, new_num(lhs->ty->base->size, tok), tok);
  }

  error_tok(tok, "%s:%d: in new_sub : invalid operands", __FILE__, __LINE__);
}

// add = mul ("+" mul | "-" mul)*
static Node *add(Token **rest, Token *tok)
{
  Node *node = mul(&tok, tok);

  for (;;)
  {
    Token *start = tok;

    if (equal(tok, "+"))
    {
      node = new_add(node, mul(&tok, tok->next), start, true);
      continue;
    }

    if (equal(tok, "-"))
    {
      node = new_sub(node, mul(&tok, tok->next), start, true);
      continue;
    }

    *rest = tok;
    return node;
  }
}

// mul = cast ("*" cast | "/" cast | "%" cast)*
static Node *mul(Token **rest, Token *tok)
{
  Node *node = cast(&tok, tok);

  for (;;)
  {
    Token *start = tok;

    if (equal(tok, "*"))
    {
      node = new_binary(ND_MUL, node, cast(&tok, tok->next), start);
      promote_scalar_to_vector(node);
      continue;
    }

    if (equal(tok, "/"))
    {
      node = new_binary(ND_DIV, node, cast(&tok, tok->next), start);
      promote_scalar_to_vector(node);
      continue;
    }

    if (equal(tok, "%"))
    {
      node = new_binary(ND_MOD, node, cast(&tok, tok->next), start);
      promote_scalar_to_vector(node);
      continue;
    }

    *rest = tok;
    return node;
  }
}

// cast = "(" type-name ")" cast | unary
static Node *cast(Token **rest, Token *tok)
{
  Token *start = tok;
  //fix for the following cast case : 
  //(__attribute__((__vector_size__ (16))) int)
  if (equal(tok, "(") && equal(tok->next, "__attribute__"))
  {
    while(tok->kind != TK_KEYWORD)
      tok = tok->next;
    
    Type *tmp =  typename(&tok, tok);
    tok = attribute_list(start->next, tmp, type_attributes);
    start->next = tok;
    Type *ty = typename(&tok, tok);
    SET_CTX(ctx);         
    tok = skip(tok, ")", ctx);
    
    // compound literal
    if (equal(tok, "{"))
      return unary(rest, start);

    // type cast
    Node *node = new_cast(cast(rest, tok), ty);
    node->tok = start;
    return node;
  }

  if (equal(tok, "(") && is_typename(tok->next))
  {
    //Token *start = tok;
    Type *ty = typename(&tok, tok->next);
    SET_CTX(ctx);       
    tok = skip(tok, ")", ctx);

    // compound literal
    if (equal(tok, "{"))
      return unary(rest, start);

    // type cast
    Node *node = new_cast(cast(rest, tok), ty);
    node->tok = start;
    return node;
  }

  return unary(rest, tok);
}

static void mark_var_address_taken(Node *node) {
  while (node->kind == ND_MEMBER)
    node = node->lhs;
  if (node->kind == ND_VAR && node->var)
    node->var->is_address_used = true;
}

// unary = ("+" | "-" | "*" | "&" | "!" | "~") cast
//       | ("++" | "--") unary
//       | "&&" ident
//       | postfix
static Node *unary(Token **rest, Token *tok)
{
  
  if (equal(tok, "+"))
    return new_unary(ND_POS, cast(rest, tok->next), tok);
    //return cast(rest, tok->next);

  if (equal(tok, "-"))
    return new_unary(ND_NEG, cast(rest, tok->next), tok);

  if (equal(tok, "&"))
  {
    Node *lhs = cast(rest, tok->next);
    add_type(lhs);
    //if (lhs->kind == ND_MEMBER && lhs->member->is_bitfield)
    if (is_bitfield(lhs))
      error_tok(tok, "%s:%d: in unary : cannot take address of bitfield", __FILE__, __LINE__);

    if (lhs->kind == ND_VAR && lhs->var && lhs->var->is_function) {
        lhs->var->is_address_used = true;
    }
    mark_var_address_taken(lhs);

    return new_unary(ND_ADDR, lhs, tok);
  }

  if (equal(tok, "*"))
  {
    // [https://www.sigbus.info/n1570#6.5.3.2p4] This is an oddity
    // in the C spec, but dereferencing a function shouldn't do
    // anything. If foo is a function, `*foo`, `**foo` or `*****foo`
    // are all equivalent to just `foo`.
    Node *node = cast(rest, tok->next);
    add_type(node);
    if (node->ty->kind == TY_FUNC)
      return node;

    Type *ty = node->ty;
    node = new_unary(ND_DEREF, node, tok);
    if (is_array(ty))
      apply_cv_qualifier(node, ty);
    return node;
    //return new_unary(ND_DEREF, node, tok);
  }

  if (equal(tok, "!"))
    return new_unary(ND_NOT, to_bool(cast(rest, tok->next)), tok);

  //commit slimcc 2e138bb  
  if (equal(tok, "~"))
    return new_unary(ND_BITNOT, cast(rest, tok->next), tok);

  // Read ++i as i+=1
  if (equal(tok, "++"))
    return to_assign(new_add(unary(rest, tok->next), new_num(1, tok), tok, false));

  // Read --i as i-=1
  if (equal(tok, "--"))
    return to_assign(new_sub(unary(rest, tok->next), new_num(1, tok), tok, false));

  // [GNU] labels-as-values
  if (equal(tok, "&&"))
  {
    Node *node = new_node(ND_LABEL_VAL, tok);
    node->label = get_ident(tok->next);
    node->goto_next = gotos;
    gotos = node;
    *rest = tok->next->next;
    return node;
  }
  return postfix(rest, tok);
}

// struct-members = (declspec declarator (","  declarator)* ";")*
static void struct_members(Token **rest, Token *tok, Type *ty)
{
  Member head = {};
  Member *cur = &head;
  //int idx = 0;
  while (!equal(tok, "}"))
  {
    VarAttr attr = {};
    tok = attribute_list(tok, &attr, thing_attributes);
    Type *basety = declspec(&tok, tok, &attr);    
    // Attributes placed between the type and the declarator list apply to
    // the whole declaration (i.e. to all declarators), like GCC.
    tok = attribute_list(tok, &attr, thing_attributes);
    bool first = true;

    // Anonymous struct member
    if ((basety->kind == TY_STRUCT || basety->kind == TY_UNION) &&
        consume(&tok, tok, ";"))
    {
      Member *mem = calloc(1, sizeof(Member));
      if (mem == NULL)
        error("%s:%d: error: in struct_members : mem is null", __FILE__, __LINE__);
      mem->ty = basety;
      //mem->idx = idx++;
      mem->align = mem->ty->align;
      mem->attr_align = attr.align;
      cur = cur->next = mem;
      continue;
    }
    
    // Regular struct members
    while (!consume(&tok, tok, ";"))
    {
      if (!first) {
        SET_CTX(ctx); 
        tok = skip(tok, ",", ctx);
      }
      first = false;

      VarAttr mem_attr = attr;
      tok = attribute_list(tok, &mem_attr, thing_attributes);
      if (equal(tok, ";"))
        break;

      Member *mem = calloc(1, sizeof(Member));
      if (mem == NULL)
        error("%s:%d: error: in struct_members : mem is null", __FILE__, __LINE__);

      mem->ty = declarator(&tok, tok, basety);
      tok = attribute_list(tok, &mem_attr, thing_attributes);
      mem->name = mem->ty->name;
      //mem->idx = idx++;
      mem->align = mem->ty->align;

      if (consume(&tok, tok, ":"))
      {
        if (!is_integer(mem->ty))
        {
          error_tok(tok, "%s:%d: in struct_members : only integers can be bitfields", __FILE__, __LINE__);
        }
        mem->is_bitfield = true;
        mem->bit_width = const_expr(&tok, tok);
        if (mem->bit_width < 0)
        {
          error_tok(tok, "%s:%d: in struct_members : bitfield width must be positive", __FILE__, __LINE__);
        }
        // Attributes can appear after the bitfield width (e.g. `int : 4 __attribute__((aligned(2)))`).
        tok = attribute_list(tok, &mem_attr, thing_attributes);
      }

      mem->attr_align = mem_attr.align;
      cur = cur->next = mem;
    }
  }

  // If the last element is an array of incomplete type, it's
  // called a "flexible array member". It should behave as if
  // if were a zero-sized array.
  if (cur != &head && cur->ty->kind == TY_ARRAY && cur->ty->array_len < 0)
  {
    cur->ty = array_of(cur->ty->base, 0);
    ty->is_flexible = true;
    cur->ty->is_flexible = true;
  }

  
  //Check for VLA-containing members
  for (Member *mem = head.next; mem; mem = mem->next) {
    if (mem->ty->has_vla) {
      ty->has_vla = true;
      break;
    }
  }


  *rest = tok->next;
  ty->members = head.next;
}

//from COSMOPOLITAN adding attribute management
static Token *attribute_list(Token *tok, void *arg, Token *(*f)(Token *, void *)) 
{

  while (consume(&tok, tok, "__attribute__") || consume(&tok, tok, "__attribute"))
  {

    SET_CTX(ctx);            
    tok = skip(tok, "(", ctx);
    SET_CTX(ctx);       
    tok = skip(tok, "(", ctx);
    bool first = true;
    while (!consume(&tok, tok, ")")) {
      if (!first) {
        SET_CTX(ctx); 
        tok = skip(tok, ",", ctx);
      }
      first = false;
            tok = f(tok, arg);
    }
    SET_CTX(ctx);     
    tok = skip(tok, ")", ctx);
  }
  return tok;
}


// attribute = ("__attribute__" "(" "(" "packed" ")" ")")*
static Token *type_attributes(Token *tok, void *arg)
{
  Type *ty = arg;
  if (!ty) {
    warn_tok(tok, "in type_attributes: %s:%d: ty is null", __FILE__, __LINE__);
    return tok;
  }

  if (consume(&tok, tok, "packed") || consume(&tok, tok, "__packed__"))
      {
        ty->is_packed = true;
        return tok;
      }



  if (consume(&tok, tok, "aligned") || consume(&tok, tok, "__aligned__"))
      {
        ty->is_aligned = true;
        int align = 16;
        if (equal(tok, "(")) {
          SET_CTX(ctx); 
          tok = skip(tok, "(", ctx);
          //from COSMOPOLITAN adding is_aligned
          align = const_expr(&tok, tok);
          SET_CTX(ctx); 
          tok = skip(tok, ")", ctx);
        }
        // GCC/Clang: aligned(N) must not reduce alignment, except vector
        // types where __attribute__((aligned(N))) can override vector_size.
        if (ty->kind == TY_VECTOR || ty->is_vector)
          ty->align = align;
        else
          ty->align = MAX(ty->align, align);
        return tok;
      }

  //from COSMOPOLITAN adding ms_abi
  if (consume(&tok, tok, "ms_abi") || consume(&tok, tok, "__ms_abi__")) {
    ty->is_ms_abi = true;
    return tok;
  }


  if (consume(&tok, tok, "constructor") || consume(&tok, tok, "__constructor__")) {
    ty->is_constructor = true;
    ty->constructor_priority = 65535; // Default GCC priority
    if (equal(tok, "(")) {
      SET_CTX(ctx); 
      tok = skip(tok, "(",ctx);

      // Parse the priority integer constant if present
      if (tok->kind == TK_NUM) {
        ty->constructor_priority = tok->val;
        tok = tok->next;
      } else {
        warn_tok(tok, "in type_attributes: %s:%d: expected integer priority in constructor attribute", __FILE__, __LINE__);
      }

      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }

    return tok;
  }


  // if (consume(&tok, tok, "destructor") || consume(&tok, tok, "__destructor__")) {
  //   ty->is_destructor = true;
  //   return tok;
  // }

  if (consume(&tok, tok, "destructor") || consume(&tok, tok, "__destructor__")) {
    ty->is_destructor = true;
    ty->destructor_priority = 65535; // Default GCC priority

    if (equal(tok, "(")) {
      SET_CTX(ctx);        
      tok = skip(tok, "(",ctx);

      // Parse the priority integer constant if present
      if (tok->kind == TK_NUM) {
        ty->destructor_priority = tok->val;
        tok = tok->next;
      } else {
        warn_tok(tok, "in type_attributes: %s:%d: expected integer priority in destructor attribute", __FILE__, __LINE__);
      }
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }

    return tok;
  }


  if (consume(&tok, tok, "vector_size") || consume(&tok, tok, "__vector_size__")) {
    SET_CTX(ctx);          
    tok = skip(tok, "(", ctx);
    int vs = const_expr(&tok, tok);
    if (vs != 2 && vs != 4 && vs != 8 && vs != 16 && vs != 32 && vs != 64) {
        error_tok(tok, "%s:%d: unsupported vector_size %d; only 2, 4, 8, 16, 32 and 64 are supported", __FILE__, __LINE__, vs);
    }
    if (vs != ty->vector_size) {
        //ty->size = vs;
        ty->vector_size = vs;
        if (!ty->is_aligned) ty->align = vs;
    }
    int base_size = ty->size;
    if (base_size == 0) {
        error_tok(tok, "%s:%d: in types_attributes: incorrect base size %d;", __FILE__, __LINE__, base_size);
    }  
    int n = vs / base_size;
    
    ty->is_vector = true;
    ty = vector_of(ty, n);
    SET_CTX(ctx); 
    tok = skip(tok, ")", ctx);
    return tok;
  }



  //from COSMOPOLITAN adding warn_if_not_aligned
  if (consume(&tok, tok, "warn_if_not_aligned") || consume(&tok, tok, "__warn_if_not_aligned__") ) {
    SET_CTX(ctx);          
    tok = skip(tok, "(", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx);          
    tok = skip(tok, ")", ctx);
    return tok;
  }


  if (equal(tok->next, "(") && (consume(&tok, tok, "__deprecated__") || 
       consume(&tok, tok, "deprecated"))) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx);  
    return skip(tok, ")", ctx);
  }

  if (consume(&tok, tok, "__target__") || 
       consume(&tok, tok, "target")) {
    SET_CTX(ctx);          
    tok = skip(tok, "(", ctx);
    ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx);  
    return skip(tok, ")", ctx);
  }

  
  if (consume(&tok, tok, "section") || consume(&tok, tok, "__section__")) {        
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    ty->section = ConsumeStringLiteral(&tok, tok);
    current_section = ty->section;
    SET_CTX(ctx);     
    return skip(tok, ")", ctx);
  }


  //from COSMOPOLITAN adding deprecated, may_alias, unused
  if (consume(&tok, tok, "deprecated") || consume(&tok, tok, "__deprecated__") ||
      consume(&tok, tok, "may_alias") ||  consume(&tok, tok, "__may_alias__") ||
      consume(&tok, tok, "__transparent_union__") || consume(&tok, tok, "transparent_union")) {
    return tok;
  }
  
  // Handle __cleanup__ attribute
  if (consume(&tok, tok, "cleanup") || consume(&tok, tok, "__cleanup__")) {
      SET_CTX(ctx); 
      tok = skip(tok, "(", ctx);  
      if (tok->kind != TK_IDENT)  
          error_tok(tok, "%s:%d: in type_attributes: expected identifier in __cleanup__", __FILE__, __LINE__);

      // Store the cleanup function name
      current_type = copy_type(ty); 

      tok = tok->next;  
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx); 
      return tok;
  }
 
  if (consume(&tok, tok, "cold") || consume(&tok, tok, "__cold__")) {
    return tok;
  }
  
  if (consume(&tok, tok, "hot") || consume(&tok, tok, "__hot__")) {  
    return tok;
  }

    if (consume(&tok, tok, "malloc") || consume(&tok, tok, "__malloc__")) {
      

    // Check for optional parameters: e.g., __malloc__(rpl_free, 1)
    if (equal(tok, "(")) {
        SET_CTX(ctx); 
        tok = skip(tok, "(", ctx);
        // Parse the deallocator function name (e.g., rpl_free)
        if (tok->kind != TK_IDENT)
            error_tok(tok, "%s:%d: expected identifier in __malloc__ attribute", __FILE__, __LINE__);
        tok = tok->next;

        // Optionally consume comma and size argument
        if (equal(tok, ",")) {
            tok = tok->next;
            const_expr(&tok, tok); // size index (e.g., 1)
        }
        SET_CTX(ctx); 
        tok = skip(tok, ")", ctx);
    }
    return tok;
  }

  if (consume(&tok, tok, "null_terminated_string_arg")) {


    // GCC syntax: __attribute__((null_terminated_string_arg(index)))
    if (equal(tok, "(")) {
        SET_CTX(ctx); 
        tok = skip(tok, "(", ctx);
        const_expr(&tok, tok);  
        SET_CTX(ctx); 
        tok = skip(tok, ")", ctx);
    }
    return tok;
  }


  if (consume(&tok, tok, "noinline") ||
      consume(&tok, tok, "__noinline__") ||
      consume(&tok, tok, "const") ||
      consume(&tok, tok, "__const__") ||
      consume(&tok, tok, "pure") ||
      consume(&tok, tok, "__pure__") ||
      consume(&tok, tok, "dontclone") ||
      consume(&tok, tok, "__dontclone__") ||
      consume(&tok, tok, "may_alias") ||
      consume(&tok, tok, "__may_alias__") ||
      consume(&tok, tok, "warn_unused_result") ||
      consume(&tok, tok, "__warn_unused_result__") ||
      consume(&tok, tok, "flatten") ||
      consume(&tok, tok, "__flatten__") ||
      consume(&tok, tok, "leaf") ||
      consume(&tok, tok, "__leaf__") ||
      consume(&tok, tok, "no_reorder") ||
      consume(&tok, tok, "__no_reorder__") ||
      consume(&tok, tok, "dontthrow") ||
      consume(&tok, tok, "__dontthrow__") ||
      consume(&tok, tok, "optnone") ||
      consume(&tok, tok, "__optnone__") ||
      consume(&tok, tok, "returns_twice") ||
      consume(&tok, tok, "__returns_twice__") ||
      consume(&tok, tok, "nodebug") ||
      consume(&tok, tok, "__nodebug__") ||
      consume(&tok, tok, "artificial") ||
      consume(&tok, tok, "__artificial__") ||
      consume(&tok, tok, "returns_nonnull") ||
      consume(&tok, tok, "__returns_nonnull__") ||
      consume(&tok, tok, "deprecated") ||
      consume(&tok, tok, "__deprecated__") ||
      consume(&tok, tok, "__transparent_union__") || 
      consume(&tok, tok, "transparent_union") ||
      consume(&tok, tok, "gnu_inline") ||
      consume(&tok, tok, "__gnu_inline__") ||
      consume(&tok, tok, "used") ||
      consume(&tok, tok, "__used__") ||
      consume(&tok, tok, "unused") ||
      consume(&tok, tok, "__unused__") ||
      consume(&tok, tok, "no_icf") ||
      consume(&tok, tok, "__no_icf__") ||
      consume(&tok, tok, "noipa") ||
      consume(&tok, tok, "__noipa__") ||
      consume(&tok, tok, "noplt") ||
      consume(&tok, tok, "__noplt__") ||
      consume(&tok, tok, "stack_protect") ||
      consume(&tok, tok, "__stack_protect__") ||
      consume(&tok, tok, "no_sanitize_address") ||
      consume(&tok, tok, "__no_sanitize_address__") ||
      consume(&tok, tok, "no_sanitize_thread") ||
      consume(&tok, tok, "__no_sanitize_thread__") ||
      consume(&tok, tok, "no_split_stack") ||
      consume(&tok, tok, "__no_split_stack__") ||
      consume(&tok, tok, "no_stack_limit") ||
      consume(&tok, tok, "__no_stack_limit__") ||
      consume(&tok, tok, "no_sanitize_undefined") ||
      consume(&tok, tok, "__no_sanitize_undefined__") ||
      consume(&tok, tok, "__nonstring__") ||
      consume(&tok, tok, "nonstring") ||       
      consume(&tok, tok, "no_profile_instrument_function") ||
      consume(&tok, tok, "stdcall") ||
      consume(&tok, tok, "ms_struct") ||
      consume(&tok, tok, "__stub__") || 
      consume(&tok, tok, "__retain__") || 
      consume(&tok, tok, "transaction_pure") || 
      consume(&tok, tok, "transaction_may_cancel_outer") || 
      consume(&tok, tok, "transaction_callable") || 
      consume(&tok, tok, "tainted_args") ||     
      consume(&tok, tok, "__designated_init__") ||         
      consume(&tok, tok, "__flag_enum__") ||            
      consume(&tok, tok, "__no_profile_instrument_function__")) 
    {
        return tok;
  }

  //fallthrough is the last instruction in case: followed by a semicolon
  if (consume(&tok, tok, "fallthrough") ||
    consume(&tok, tok, "__fallthrough__") )
    {
      return tok;
    }
        
  if (consume(&tok, tok, "__diagnose_if__") ||
      consume(&tok, tok, "diagnose_if") || consume(&tok, tok, "__no_sanitize__") ||
      consume(&tok, tok, "no_sanitize")) {
      tok = skip(tok, "(", ctx);
      int depth = 1;
      while (depth > 0) {
          if (equal(tok, "(")) depth++;
          else if (equal(tok, ")")) depth--;
          tok = tok->next;
      }
      return tok;
  }


  if (consume(&tok, tok, "format") || consume(&tok, tok, "__format__")) {
    SET_CTX(ctx);       
    tok = skip(tok, "(", ctx);
    consume(&tok, tok, "printf") ;
    consume(&tok, tok, "__printf__");
    consume(&tok, tok, "scanf");
    consume(&tok, tok, "__scanf__");
    consume(&tok, tok, "strftime");
    consume(&tok, tok, "__strftime__");
    consume(&tok, tok, "strfmon");
    consume(&tok, tok, "__strfmon__");
    consume(&tok, tok, "gnu_printf");
    consume(&tok, tok, "__gnu_printf__");
    consume(&tok, tok, "gnu_scanf");
    consume(&tok, tok, "__gnu_scanf__");
    consume(&tok, tok, "gnu_strftime");
    consume(&tok, tok, "__gnu_strftime__");
    SET_CTX(ctx);     
    tok = skip(tok, ",", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx); 
    tok = skip(tok, ")", ctx);
    return tok;
  }

  if (consume(&tok, tok, "format_arg") || consume(&tok, tok, "__format_arg__")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx);      
    tok =skip(tok, ")", ctx);
    return tok;
  }

  if (consume(&tok, tok, "mode") || consume(&tok, tok, "__mode__")) {
    SET_CTX(ctx);     
    tok = skip(tok, "(", ctx);
    if (consume(&tok, tok, "__QI__") || consume(&tok, tok, "__HI__") ||
        consume(&tok, tok, "__SI__") || consume(&tok, tok, "__DI__") ||
        consume(&tok, tok, "__TI__") || consume(&tok, tok, "__SF__") ||
        consume(&tok, tok, "__DF__") || consume(&tok, tok, "__XF__") ||
        consume(&tok, tok, "__TF__") || consume(&tok, tok, "__SQ__") || consume(&tok, tok, "__HQ__") ||
        consume(&tok, tok, "__SA__") || consume(&tok, tok, "__DA__") || consume(&tok, tok, "__TQ__") ||
        consume(&tok, tok, "__V2SI__") || consume(&tok, tok, "__V4SI__") || consume(&tok, tok, "__V8HI__") ||
        consume(&tok, tok, "__V16QI__") || consume(&tok, tok, "__word__") || consume(&tok, tok, "__pointer__") ||
        consume(&tok, tok, "__CQI__") || consume(&tok, tok, "__CHI__") || consume(&tok, tok, "__CDF__") ||
        consume(&tok, tok, "__TC__") ||consume(&tok, tok, "__BI__")) {
      SET_CTX(ctx);  
      return skip(tok, ")", ctx);
    }
    SET_CTX(ctx);  
    return skip(tok, ")", ctx);
  }

  if (consume(&tok, tok, "nothrow") || consume(&tok, tok, "__nothrow__")) {
    return tok;
  }


  if (consume(&tok, tok, "noreturn") || consume(&tok, tok, "__noreturn__")) {
    return tok;
  }

  if (consume(&tok, tok, "__noescape__") || consume(&tok, tok, "noescape")) {
    return tok;
  }

  if (consume(&tok, tok, "__common__")) {
    return tok;
  }



  if (consume(&tok, tok, "const") || consume(&tok, tok, "__const__")) {
      ty->is_const = true;
    return tok;
  }

  if (consume(&tok, tok, "always_inline") || consume(&tok, tok, "__always_inline__")) {
      ty->is_inline = true;
    return tok;
  }

  if (consume(&tok, tok, "__min_vector_width__")) {
      ty->min_vector_width = const_expr(&tok, tok);
    return tok;
  }

  if (consume(&tok, tok, "nonnull") || consume(&tok, tok, "__nonnull__")) {
      if (equal(tok, "(")) {
          SET_CTX(ctx); 
          tok = skip(tok, "(",ctx);
          while (!equal(tok, ")")) {
              if (tok->kind != TK_NUM) {
                  error_tok(tok, "%s:%d: expected parameter index in __nonnull__", __FILE__, __LINE__);
              }
              tok = tok->next;
              if (equal(tok, ","))
                  tok = tok->next;
              else
                  break;
          }
          SET_CTX(ctx); 
          tok = skip(tok, ")",ctx);
      }

     return tok;
  }

  if (consume(&tok, tok, "enum_extensibility") ||
      consume(&tok, tok, "__enum_extensibility__")) {
    tok = skip(tok, "(", ctx);

    if (consume(&tok, tok, "open")) {
      //
    } else if (consume(&tok, tok, "closed")) {
      //
    }
    tok = skip(tok, ")", ctx);
    return tok;
  }

  if (consume(&tok, tok, "sentinel") || consume(&tok, tok, "__sentinel__") ||
    consume(&tok, tok, "optimize") || consume(&tok, tok, "__optimize__") ||
    consume(&tok, tok, "assume_aligned") || consume(&tok, tok, "__assume_aligned__") ||
    consume(&tok, tok, "alloc_size") || consume(&tok, tok, "__alloc_size__") ||
    consume(&tok, tok, "attribute_alloc_size") || consume(&tok, tok, "__attribute_alloc_size__") ||
    consume(&tok, tok, "alloc_align") || consume(&tok, tok, "__alloc_align__")) {
    if (consume(&tok, tok, "(")) {
      for (;;) {
        const_expr(&tok, tok);
        if (consume(&tok, tok, ")")) break;
        SET_CTX(ctx);          
        tok = skip(tok, ",", ctx);
      }
    }
    return tok;
  }


  if (consume(&tok, tok, "error") || consume(&tok, tok, "__error__") ||
      consume(&tok, tok, "warning") || consume(&tok, tok, "__warning__") ||
      consume(&tok, tok, "__access__")
      )  {
    
    bool two_parent= false;    
    SET_CTX(ctx);     
    tok = skip(tok, "(", ctx);    
    if (equal(tok, "("))   { 
      SET_CTX(ctx); 
      tok = skip(tok, "(", ctx);
      two_parent = true;
    }

    ConsumeStringLiteral(&tok, tok); 

    if (two_parent) {   
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }
    SET_CTX(ctx);  
    return skip(tok, ")", ctx);
  }


  if (consume(&tok, tok, "no_sanitize"))  {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);     
    ConsumeStringLiteral(&tok, tok); 
    SET_CTX(ctx);   
    return skip(tok, ")", ctx);
  }

  if (consume(&tok, tok, "weak") || consume(&tok, tok, "__weak__")) {
    //int __attribute__((weak, alias("lxc_attach_main"))) main(int argc, char *argv[]);
    ty->is_weak = true;
    consume(&tok, tok, ",");
    if (consume(&tok, tok, "alias")) {
      SET_CTX(ctx); 
      tok = skip(tok, "(", ctx);
      ty->alias_name = ConsumeStringLiteral(&tok, tok); 
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }
    return tok;
  }

  if (consume(&tok, tok, "__weakref__")) {
    ty->is_weak = true;
    SET_CTX(ctx);
    tok = skip(tok, "(", ctx);
    ty->alias_name = ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx);
    tok = skip(tok, ")", ctx);
    return tok;
  }

  if (consume(&tok, tok, "alias")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    ty->alias_name = ConsumeStringLiteral(&tok, tok); 
    SET_CTX(ctx); 
    tok = skip(tok, ")", ctx);
    return tok;
  }


  if (consume(&tok, tok, "visibility") || consume(&tok, tok, "__visibility__")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    ty->visibility = ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }


  return tok;
}


//from COSMOPOLITAN adding attribute for variable
static Token *thing_attributes(Token *tok, void *arg) {
  VarAttr *attr = arg;
  if (!attr) {
    warn_tok(tok, "in thing_attributes: %s:%d: attr is null", __FILE__, __LINE__);
    return tok;
  }

  if (consume(&tok, tok, "packed") || consume(&tok, tok, "__packed__"))
    {
      attr->is_packed = true;
      return tok;
    }

  if (consume(&tok, tok, "weak") || consume(&tok, tok, "__weak__")) {
    //int __attribute__((weak, alias("lxc_attach_main"))) main(int argc, char *argv[]);
    attr->is_weak = true;
    consume(&tok, tok, ",");
    if (consume(&tok, tok, "alias")) {
      SET_CTX(ctx); 
      tok = skip(tok, "(", ctx);
      attr->alias_name = ConsumeStringLiteral(&tok, tok); 
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }
    return tok;
  }

  if (consume(&tok, tok, "__weakref__")) {
    attr->is_weak = true;
    SET_CTX(ctx);
    tok = skip(tok, "(", ctx);
    attr->alias_name = ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx);
    tok = skip(tok, ")", ctx);
    return tok;
  }

  if (consume(&tok, tok, "alias")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    attr->alias_name = ConsumeStringLiteral(&tok, tok); 
    SET_CTX(ctx); 
    tok = skip(tok, ")", ctx);
    return tok;
  }


  if (consume(&tok, tok, "hot") || consume(&tok, tok, "__hot__")) {
    attr->section = ".text.likely";
    return tok;
  }

  if (consume(&tok, tok, "cold") || consume(&tok, tok, "__cold__")) {
    attr->section = ".text.unlikely";
    return tok;
  }

  if (consume(&tok, tok, "__target__") || 
       consume(&tok, tok, "target")) {
    SET_CTX(ctx);          
    tok = skip(tok, "(", ctx);
    ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx);  
    return skip(tok, ")", ctx);
  }


  if (consume(&tok, tok, "section") || consume(&tok, tok, "__section__")) {    
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    attr->section = ConsumeStringLiteral(&tok, tok);
    current_section = attr->section;
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }
  
  if (consume(&tok, tok, "noreturn") || consume(&tok, tok, "__noreturn__")) {
    attr->is_noreturn = true;
    return tok;
  }

  if (consume(&tok, tok, "__noescape__") ||  consume(&tok, tok, "noescape")) {
    return tok;
  }

  if (consume(&tok, tok, "__common__")) {
    return tok;
  }

  if (consume(&tok, tok, "nothrow") || consume(&tok, tok, "__nothrow__")) {
    return tok;
  }

  if (consume(&tok, tok, "always_inline") || consume(&tok, tok, "__always_inline__")) {
    attr->is_inline = true;
    return tok;
  }

  if (consume(&tok, tok, "__min_vector_width__")) {
      attr->min_vector_width = const_expr(&tok, tok);
    return tok;
  }

  if (consume(&tok, tok, "const") || consume(&tok, tok, "__const__")) {
    return tok;
  }

  if (consume(&tok, tok, "visibility") || consume(&tok, tok, "__visibility__")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    attr->visibility = ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }
  if (consume(&tok, tok, "externally_visible") || consume(&tok, tok, "__externally_visible__")) {
    attr->is_externally_visible = true;
    return tok;
  }
  if (consume(&tok, tok, "no_instrument_function") || consume(&tok, tok, "__no_instrument_function__")) {
    attr->is_no_instrument_function = true;
    return tok;
  }
  if (consume(&tok, tok, "force_align_arg_pointer") || consume(&tok, tok, "__force_align_arg_pointer__")) {
    attr->is_force_align_arg_pointer = true;
    return tok;
  }
  if (consume(&tok, tok, "no_caller_saved_registers") || consume(&tok, tok, "__no_caller_saved_registers__")) {
    attr->is_no_caller_saved_registers = true;
    return tok;
  }
  if (consume(&tok, tok, "ms_abi")) {
    attr->is_ms_abi = true;
    return tok;
  }

  if (consume(&tok, tok, "constructor") || consume(&tok, tok, "__constructor__")) {
    attr->is_constructor = true;
    attr->constructor_priority = 65535; // Default GCC priority

    if (equal(tok, "(")) {
      SET_CTX(ctx);        
      tok = skip(tok, "(",ctx);

      // Parse the priority integer constant if present
      if (tok->kind == TK_NUM) {
        attr->constructor_priority = tok->val;
        tok = tok->next;
      } else {
        warn_tok(tok, "in thing_attributes: %s:%d: expected integer priority in constructor attribute", __FILE__, __LINE__);
      }
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }

    return tok;
  }  

  if (consume(&tok, tok, "destructor") || consume(&tok, tok, "__destructor__")) {
    attr->is_destructor = true;
    attr->destructor_priority = 65535; // Default GCC priority
    if (equal(tok, "(")) {
      SET_CTX(ctx);        
      tok = skip(tok, "(",ctx);

      // Parse the priority integer constant if present
      if (tok->kind == TK_NUM) {
        attr->destructor_priority = tok->val;
        tok = tok->next;
      } else {
        warn_tok(tok, "in thing_attributes: %s:%d: expected integer priority in destructor attribute", __FILE__, __LINE__);
      }
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }

    return tok;
  }  


  if (consume(&tok, tok, "aligned") || consume(&tok, tok, "__aligned__"))
      {
        attr->is_aligned = true;
        if (equal(tok, "(")) {
          SET_CTX(ctx); 
          tok = skip(tok, "(", ctx);
          //from COSMOPOLITAN adding is_aligned        
          attr->align = const_expr(&tok, tok);
          SET_CTX(ctx); 
          tok = skip(tok, ")", ctx);
        } else {
          attr->align = 16;
        }
        return tok;
      }


  if (consume(&tok, tok, "warn_if_not_aligned") || consume(&tok, tok, "__warn_if_not_aligned__")) {
    SET_CTX(ctx);     
    tok = skip(tok, "(", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx);     
    return skip(tok, ")", ctx);
  }



  if (consume(&tok, tok, "error") || consume(&tok, tok, "__error__") ||
      consume(&tok, tok, "warning") || consume(&tok, tok, "__warning__") ||
       consume(&tok, tok, "__access__")
      )  {

    bool two_parent= false; 
    SET_CTX(ctx);        
    tok = skip(tok, "(", ctx);

    if (equal(tok, "("))   { 
      SET_CTX(ctx); 
      tok = skip(tok, "(", ctx);
      two_parent = true;
    }
    ConsumeStringLiteral(&tok, tok); 
    if (two_parent) {   
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx);
    }
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }


  if (consume(&tok, tok, "mode") || consume(&tok, tok, "__mode__")) {
    SET_CTX(ctx);           
    tok = skip(tok, "(", ctx);
    if (consume(&tok, tok, "__QI__") || consume(&tok, tok, "__HI__") ||
        consume(&tok, tok, "__SI__") || consume(&tok, tok, "__DI__") ||
        consume(&tok, tok, "__TI__") || consume(&tok, tok, "__SF__") ||
        consume(&tok, tok, "__DF__") || consume(&tok, tok, "__XF__") ||
        consume(&tok, tok, "__TF__") || consume(&tok, tok, "__SQ__") || consume(&tok, tok, "__HQ__") ||
        consume(&tok, tok, "__SA__") || consume(&tok, tok, "__DA__") || consume(&tok, tok, "__TQ__") ||
        consume(&tok, tok, "__V2SI__") || consume(&tok, tok, "__V4SI__") || consume(&tok, tok, "__V8HI__") ||
        consume(&tok, tok, "__V16QI__") || consume(&tok, tok, "__word__") || consume(&tok, tok, "__pointer__") ||
        consume(&tok, tok, "__CQI__") || consume(&tok, tok, "__CHI__") || consume(&tok, tok, "__CDF__") ||
        consume(&tok, tok, "__TC__") || consume(&tok, tok, "__BI__")) {
      SET_CTX(ctx);  
      return skip(tok, ")", ctx);
    }
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }

  
  if (equal(tok->next, "(") && (consume(&tok, tok, "__deprecated__") || 
       consume(&tok, tok, "deprecated"))) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx);   
    return skip(tok, ")", ctx);
  }

 
 
 // Handle __cleanup__ attribute
 if (consume(&tok, tok, "cleanup") || consume(&tok, tok, "__cleanup__")) {
      SET_CTX(ctx); 
      tok = skip(tok, "(", ctx);  
      if (tok->kind != TK_IDENT)  
          error_tok(tok, "%s:%d: expected identifier in __cleanup__", __FILE__, __LINE__);

      // Store the cleanup function name
      current_attr = attr;

      tok = tok->next;
      SET_CTX(ctx); 
      tok = skip(tok, ")", ctx); 
      return tok;
  }

 
  if (consume(&tok, tok, "malloc") || consume(&tok, tok, "__malloc__")) {
    if (equal(tok, "(")) {
        SET_CTX(ctx); 
        tok = skip(tok, "(", ctx);        
        if (tok->kind != TK_IDENT)
            error_tok(tok, "%s:%d: expected identifier in __malloc__ attribute", __FILE__, __LINE__);
        tok = tok->next;
        if (equal(tok, ",")) {
            tok = tok->next;
            const_expr(&tok, tok); 
        }
        SET_CTX(ctx); 
        tok = skip(tok, ")", ctx);
    }
    return tok;
  }

  if (consume(&tok, tok, "null_terminated_string_arg")) {
    if (equal(tok, "(")) {
        SET_CTX(ctx); 
        tok = skip(tok, "(", ctx);
        const_expr(&tok, tok); 
        SET_CTX(ctx); 
        tok = skip(tok, ")", ctx);
    }
    return tok;
  }


  if (consume(&tok, tok, "noinline") ||
      consume(&tok, tok, "__noinline__") ||
      consume(&tok, tok, "const") ||
      consume(&tok, tok, "__const__") ||
      consume(&tok, tok, "pure") ||
      consume(&tok, tok, "__pure__") ||
      consume(&tok, tok, "dontclone") ||
      consume(&tok, tok, "__dontclone__") ||
      consume(&tok, tok, "may_alias") ||
      consume(&tok, tok, "__may_alias__") ||
      consume(&tok, tok, "warn_unused_result") ||
      consume(&tok, tok, "__warn_unused_result__") ||
      consume(&tok, tok, "flatten") ||
      consume(&tok, tok, "__flatten__") ||
      consume(&tok, tok, "leaf") ||
      consume(&tok, tok, "__leaf__") ||
      consume(&tok, tok, "no_reorder") ||
      consume(&tok, tok, "__no_reorder__") ||
      consume(&tok, tok, "dontthrow") ||
      consume(&tok, tok, "__dontthrow__") ||
      consume(&tok, tok, "optnone") ||
      consume(&tok, tok, "__optnone__") ||
      consume(&tok, tok, "returns_twice") ||
      consume(&tok, tok, "__returns_twice__") ||
      consume(&tok, tok, "nodebug") ||
      consume(&tok, tok, "__nodebug__") ||
      consume(&tok, tok, "artificial") ||
      consume(&tok, tok, "__artificial__") ||
      consume(&tok, tok, "returns_nonnull") ||
      consume(&tok, tok, "__returns_nonnull__") ||
      consume(&tok, tok, "deprecated") ||
      consume(&tok, tok, "__deprecated__") ||
      consume(&tok, tok, "__transparent_union__") || 
      consume(&tok, tok, "transparent_union") ||
      consume(&tok, tok, "gnu_inline") ||
      consume(&tok, tok, "__gnu_inline__") ||
      consume(&tok, tok, "used") ||
      consume(&tok, tok, "__used__") ||
      consume(&tok, tok, "unused") ||
      consume(&tok, tok, "__unused__") ||
      consume(&tok, tok, "no_icf") ||
      consume(&tok, tok, "__no_icf__") ||
      consume(&tok, tok, "noipa") ||
      consume(&tok, tok, "__noipa__") ||
      consume(&tok, tok, "noplt") ||
      consume(&tok, tok, "__noplt__") ||
      consume(&tok, tok, "stack_protect") ||
      consume(&tok, tok, "__stack_protect__") ||
      consume(&tok, tok, "no_sanitize_address") ||
      consume(&tok, tok, "__no_sanitize_address__") ||
      consume(&tok, tok, "no_sanitize_thread") ||
      consume(&tok, tok, "__no_sanitize_thread__") ||
      consume(&tok, tok, "no_split_stack") ||
      consume(&tok, tok, "__no_split_stack__") ||
      consume(&tok, tok, "no_stack_limit") ||
      consume(&tok, tok, "__no_stack_limit__") ||
      consume(&tok, tok, "no_sanitize_undefined") ||
      consume(&tok, tok, "__no_sanitize_undefined__") ||
      consume(&tok, tok, "__nonstring__") ||
      consume(&tok, tok, "nonstring") ||       
      consume(&tok, tok, "no_profile_instrument_function") ||
      consume(&tok, tok, "stdcall") ||
      consume(&tok, tok, "__stub__") || 
      consume(&tok, tok, "__retain__") || 
      consume(&tok, tok, "transaction_pure") || 
      consume(&tok, tok, "transaction_may_cancel_outer") || 
      consume(&tok, tok, "transaction_callable") ||     
      consume(&tok, tok, "tainted_args") ||     
      consume(&tok, tok, "__designated_init__") ||  
      consume(&tok, tok, "__flag_enum__") ||                
      consume(&tok, tok, "__no_profile_instrument_function__")) 
    {
        return tok;
    }


    if (consume(&tok, tok, "always_inline") || consume(&tok, tok, "__always_inline__")) {
      attr->is_inline = true;
        return tok;
    }

    //fallthrough is the last instruction in case: followed by a semicolon
    if (consume(&tok, tok, "fallthrough") ||
      consume(&tok, tok, "__fallthrough__") )
    {
      return tok;
    }

    if (consume(&tok, tok, "__diagnose_if__") ||
        consume(&tok, tok, "diagnose_if") || consume(&tok, tok, "__no_sanitize__") ||
      consume(&tok, tok, "no_sanitize")) {
        tok = skip(tok, "(", ctx);
        int depth = 1;
        while (depth > 0) {
            if (equal(tok, "(")) depth++;
            else if (equal(tok, ")")) depth--;
            tok = tok->next;
        }
        return tok;
    }


    if (consume(&tok, tok, "nonnull") || consume(&tok, tok, "__nonnull__")) {
      if (equal(tok, "(")) {
          SET_CTX(ctx); 
          tok = skip(tok, "(",ctx);
          while (!equal(tok, ")")) {
              if (tok->kind != TK_NUM) {
                  error_tok(tok, "%s:%d: expected parameter index in __nonnull__", __FILE__, __LINE__);
              }
              tok = tok->next;
              if (equal(tok, ","))
                  tok = tok->next;
              else
                  break;
          }
          SET_CTX(ctx); 
          tok = skip(tok, ")",ctx);
      }
     return tok;
    }

    if (consume(&tok, tok, "enum_extensibility") ||
      consume(&tok, tok, "__enum_extensibility__")) {
      tok = skip(tok, "(", ctx);

      if (consume(&tok, tok, "open")) {
        //
      } else if (consume(&tok, tok, "closed")) {
        //
      }
      tok = skip(tok, ")", ctx);
      return tok;
    }

    if (consume(&tok, tok, "sentinel") || consume(&tok, tok, "__sentinel__") ||
      consume(&tok, tok, "optimize") || consume(&tok, tok, "__optimize__") ||
      consume(&tok, tok, "assume_aligned") || consume(&tok, tok, "__assume_aligned__") ||
      consume(&tok, tok, "alloc_size") || consume(&tok, tok, "__alloc_size__") ||
      consume(&tok, tok, "attribute_alloc_size") || consume(&tok, tok, "__attribute_alloc_size__") ||
      consume(&tok, tok, "alloc_align") || consume(&tok, tok, "__alloc_align__")) {
    if (consume(&tok, tok, "(")) {
      for (;;) {
        const_expr(&tok, tok);
        if (consume(&tok, tok, ")")) break;
        SET_CTX(ctx);          
        tok = skip(tok, ",", ctx);
      }
    }
    return tok;
  }

  if (consume(&tok, tok, "format") || consume(&tok, tok, "__format__")) {
    SET_CTX(ctx);     
    tok = skip(tok, "(", ctx);
    consume(&tok, tok, "printf");
    consume(&tok, tok, "__printf__");
    consume(&tok, tok, "scanf");
    consume(&tok, tok, "__scanf__");
    consume(&tok, tok, "strftime");
    consume(&tok, tok, "__strftime__");
    consume(&tok, tok, "strfmon");
    consume(&tok, tok, "__strfmon__");
    consume(&tok, tok, "gnu_printf");
    consume(&tok, tok, "__gnu_printf__");
    consume(&tok, tok, "gnu_scanf");
    consume(&tok, tok, "__gnu_scanf__");
    consume(&tok, tok, "gnu_strftime");
    consume(&tok, tok, "__gnu_strftime__");
    SET_CTX(ctx);     
    tok = skip(tok, ",", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }



  if (consume(&tok, tok, "format_arg")  || consume(&tok, tok, "__format_arg__")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    const_expr(&tok, tok);
    SET_CTX(ctx);     
    return skip(tok, ")", ctx);
  }

  if (consume(&tok, tok, "no_sanitize"))  {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    ConsumeStringLiteral(&tok, tok); 
    SET_CTX(ctx); 
    return skip(tok, ")", ctx);
  }


  return tok;
  
}


bool equal_tok(Token *a, Token *b) {
  return a->len == b->len && !memcmp(a->loc, b->loc, b->len);
}

// struct-union-decl = attribute? ident? ("{" struct-members)?
static Type *struct_union_decl(Token **rest, Token *tok, bool *no_list)
{
  Type *ty = struct_type();
  ty->size = -1;
  tok = attribute_list(tok, ty, type_attributes);

  // Read a tag.
  Token *tag = NULL;

    
  if (tok->kind == TK_IDENT)
  {
    tag = tok;
    ty->name = tag;
    ty->tag_name = tag;
    tok = tok->next;
  }

  if (tag && !equal(tok, "{"))
  {
    *rest = tok;
    *no_list = true;

    Type *ty2 = find_tag(tag);
    if (ty2)
      return ty2;

    ty->size = -1;
    push_tag_scope(tag, ty);
    if (!ty)
      error_tok(tok, "%s:%d: in struct_union_decl : ty is null!", __FILE__, __LINE__);
    return ty;
  }

  SET_CTX(ctx);     
  tok = skip(tok, "{", ctx);

  // Construct a struct object.
  struct_members(&tok, tok, ty);
  *rest = attribute_list(tok, ty, type_attributes);

  if (tag)
  {
    // If this is a redefinition, overwrite a previous type.
    // Otherwise, register the struct type.
    Type *ty2 = hashmap_get2(&scope->tags, tag->loc, tag->len);
    if (ty2) {
      for (Type *t = ty2; t; t = t->decl_next) {
        t->size = ty->size;
        t->align = MAX(t->align, ty->align);
        t->members = ty->members;
        t->is_flexible = ty->is_flexible;
        t->is_packed = ty->is_packed;
        t->tag_name = ty->tag_name;
      }
      return ty2;
    }
    ty->tag = tag;
    push_tag_scope(tag, ty);
  }
  if (!ty)
    error_tok(tok, "%s:%d: in struct_union_decl : ty is null!", __FILE__, __LINE__);
  return ty;
}

// struct-decl = struct-union-decl
static Type *struct_decl(Token **rest, Token *tok)
{
  bool no_list = false;
  Type *ty = struct_union_decl(rest, tok, &no_list);
  tok = attribute_list(tok, ty, type_attributes);
  ty->kind = TY_STRUCT;

  if (no_list)
    return ty;

  int pack_align = ty->is_packed ? 1 : tok->pack_align;

  //ty->size = MAX(ty->size, 0);

  // Assign offsets within the struct to members.
  int bits = 0;
  Member head = {0};
  Member *cur = &head;

  for (Member *mem = ty->members; mem; mem = mem->next)
  {
    int mem_align = mem->align;
    if (pack_align > 0)
      mem_align = MIN(mem_align, pack_align);
    if (mem->attr_align)
      mem_align = MAX(mem_align, mem->attr_align);

    if (mem->is_bitfield && mem->bit_width == 0)
    {
      // Zero-width anonymous bitfield has a special meaning.
      // It affects only alignment.
      bits = align_to(bits, mem_align * 8);
    }
    else if (mem->is_bitfield)
    {
      if (mem->attr_align)
        bits = align_to(bits, mem_align * 8);

      int sz = mem->ty->size;
      if (bits / (sz * 8) != (bits + mem->bit_width - 1) / (sz * 8))
        bits = align_to(bits, sz * 8);

      mem->offset = align_down(bits / 8, sz);
      mem->bit_offset = bits % (sz * 8);
      bits += mem->bit_width;
    }
    else
    {
      bits = align_to(bits, mem_align * 8);
      mem->offset = bits / 8;
      bits += mem->ty->size * 8;
    }

    
    if (!mem->name && mem->is_bitfield ) {         
        cur->next = NULL;        
        continue;            
    }


        //from COSMOPOLITAN adding is_aligned
    if (ty->align < mem_align)
      ty->align = mem_align;
    cur = cur->next = mem;
  }

  ty->members = head.next;
  ty->size = align_to(bits, ty->align * 8) / 8;

  for (Type *t = ty->decl_next; t; t = t->decl_next) {
    t->size = ty->size;
    t->align = ty->align;
    t->is_packed = ty->is_packed;
    t->members = ty->members;
  }
  if (!ty)
    error_tok(tok, "%s:%d: in struct_decl : ty is null!", __FILE__, __LINE__);
  return ty;
}

// union-decl = struct-union-decl
static Type *union_decl(Token **rest, Token *tok)
{
  bool no_list = false;
  Type *ty = struct_union_decl(rest, tok, &no_list);
  tok = attribute_list(tok, ty, type_attributes);
  ty->kind = TY_UNION;

  if (no_list)
    return ty;

  int pack_align = ty->is_packed ? 1 : tok->pack_align;

 Member head = {0};
  Member *cur = &head;
  for (Member *mem = ty->members; mem; mem = mem->next) {
    int mem_align = mem->align;
    if (pack_align > 0)
      mem_align = MIN(mem_align, pack_align);
    if (mem->attr_align)
      mem_align = MAX(mem_align, mem->attr_align);

    int sz;
    if (mem->is_bitfield)
      sz = align_to(mem->bit_width, 8) / 8;
    else
      sz = mem->ty->size;

    ty->size = MAX(ty->size, sz);

    if (!mem->name && mem->is_bitfield) {
      cur->next = NULL;
      continue;
    }

    if (ty->align < mem_align)
      ty->align = mem_align;

    cur = cur->next = mem;
  }
  ty->members = head.next;
  ty->size = align_to(ty->size, ty->align);

  for (Type *t = ty->decl_next; t; t = t->decl_next) {
    t->size = ty->size;
    t->align = ty->align;
    t->is_packed = ty->is_packed;
    t->members = ty->members;
  }
  if (!ty)
    error_tok(tok, "%s:%d: in union_decl : ty is null!", __FILE__, __LINE__);
  return ty;
}

// Find a struct member by name.
static Member *get_struct_member(Type *ty, Token *tok)
{

  for (Member *mem = ty->members; mem; mem = mem->next)
  {
    // Anonymous struct member
    if (!mem->name)
    {

      //if (mem->ty->kind == TY_STRUCT || mem->ty->kind == TY_UNION)
        if (get_struct_member(mem->ty, tok))
          return mem;

      continue;
    }
  
    // Regular struct member
    if (mem->name->len == tok->len &&
        !strncmp(mem->name->loc, tok->loc, tok->len))
      return mem;
  }
  return NULL;
}

// Create a node representing a struct member access, such as foo.bar
// where foo is a struct and bar is a member name.
//
// C has a feature called "anonymous struct" which allows a struct to
// have another unnamed struct as a member like this:
//
//   struct { struct { int a; }; int b; } x;
//
// The members of an anonymous struct belong to the outer struct's
// member namespace. Therefore, in the above example, you can access
// member "a" of the anonymous struct as "x.a".
//
// This function takes care of anonymous structs.
static Node *struct_ref(Node *node, Token *tok)
{
  add_type(node);
  if (node->ty->kind != TY_STRUCT && node->ty->kind != TY_UNION) 
    error_tok(node->tok, "%s:%d: in struct_ref : not a struct nor a union", __FILE__, __LINE__);

  Type *ty = node->ty;
  for (;;)
  {
    Member *mem = get_struct_member(ty, tok);
    if (!mem)
      error_tok(tok, "%s:%d: in struct_ref : no such member", __FILE__, __LINE__);
    node = new_unary(ND_MEMBER, node, tok);
    node->member = mem;
    if (mem->name)
      break;

    ty = mem->ty;
  }
  return node;
}


static void chain_expr(Node **lhs, Node *rhs) {
  if (rhs)
    *lhs = !*lhs ? rhs : new_binary(ND_COMMA, *lhs, rhs, rhs->tok);
}


// Convert A++ to `(typeof A)((A += 1) - 1)`
// static Node *new_inc_dec(Node *node, Token *tok, int addend)
// {
//   add_type(node);
//   return new_cast(new_add(to_assign(new_add(node, new_num(addend, tok), tok, false)),
//                           new_num(-addend, tok), tok, false),
//                   node->ty);
// }
static Node *new_inc_dec(Node *node, Token *tok, int addend) {
  add_type(node);

  if (!current_fn) {
    return new_cast(new_add(to_assign(new_add(node, new_num(addend, tok), tok, false)),
                            new_num(-addend, tok), tok, false),
                    node->ty);
  }

  // -O1+: for simple variable postfix inc/dec, avoid hidden pointer temp.
  // `_Bool` is special: `(b += 1) - 1` does not preserve old value semantics.
  if (opt_optimize_level1 && !node->ty->is_atomic &&
      node->ty->kind != TY_BOOL && is_safe_lvalue(node)) {
    return new_cast(new_add(to_assign(new_add(node, new_num(addend, tok), tok, false)),
                            new_num(-addend, tok), tok, false),
                    node->ty);
  }

  enter_scope();

  if (is_bitfield(node)) {
    Obj *tmp = new_lvar("", node->ty, NULL);
    Obj *ptr = new_lvar("", pointer_to(node->lhs->ty), NULL);

    Node *expr = new_binary(ND_ASSIGN, new_var_node(ptr, tok),
                             new_unary(ND_ADDR, node->lhs, tok), tok);

    Node *memref1 = new_unary(ND_MEMBER,
                              new_unary(ND_DEREF, new_var_node(ptr, tok), tok),
                              tok);
    memref1->member = node->member;

    Node *memref2 = new_unary(ND_MEMBER,
                              new_unary(ND_DEREF, new_var_node(ptr, tok), tok),
                              tok);
    memref2->member = node->member;

    chain_expr(&expr, new_binary(ND_ASSIGN, new_var_node(tmp, tok), memref1, tok));
    chain_expr(&expr, to_assign(new_add(memref2, new_num(addend, tok), tok, false)));
    chain_expr(&expr, new_var_node(tmp, tok));
    leave_scope();
    return expr;
  }

  Obj *tmp = new_lvar("", node->ty, NULL);
  Obj *ptr = new_lvar("", pointer_to(node->ty), NULL);

  Node *expr = new_binary(ND_ASSIGN, new_var_node(ptr, tok),
                          new_unary(ND_ADDR, node, tok), tok);
  chain_expr(&expr, new_binary(ND_ASSIGN, new_var_node(tmp, tok),
                               new_unary(ND_DEREF, new_var_node(ptr, tok), tok), tok));
  chain_expr(&expr, to_assign(new_add(new_unary(ND_DEREF, new_var_node(ptr, tok), tok),
                                      new_num(addend, tok), tok, false)));
  chain_expr(&expr, new_var_node(tmp, tok));
  leave_scope();
  return expr;
}


// postfix = "(" type-name ")" "{" initializer-list "}" postfix-tail*
//         = ident "(" func-args ")" postfix-tail*
//         | primary postfix-tail*
//
// postfix-tail = "[" expr "]"
//              | "(" func-args ")"
//              | "." ident
//              | "->" ident
//              | "++"
//              | "--"
static Node *postfix(Token **rest, Token *tok)
{
  

  Node *node;
  if (equal(tok, "(") && is_typename(tok->next))
  {

    // Compound literal
    Token *start = tok;
    Type *ty = typename(&tok, tok->next);
    tok = attribute_list(tok, ty, type_attributes);
    if (ty->kind == TY_VLA)
      error_tok(tok, "%s:%d: in postfix : compound literals cannot be VLA", __FILE__, __LINE__);
    SET_CTX(ctx);     
    tok = skip(tok, ")", ctx);

    if (scope->next == NULL)
    {
      Obj *var = new_anon_gvar(ty);
      var->is_compound_lit = true;
      gvar_initializer(&tok, tok, var);
      node = new_var_node(var, start);
    }
    else
    {
      Obj *var = new_lvar("", ty, NULL);
      var->is_compound_lit = true;
      Node *lhs = lvar_initializer(&tok, tok, var);
      Node *rhs = new_var_node(var, tok);
      node = new_binary(ND_COMMA, lhs, rhs, start);

    }
  }
  else
  {
    
    node = primary(&tok, tok);
  }

  // Node *node = primary(&tok, tok);

  for (;;)
  {

    if (equal(tok, "("))
    {
      node = funcall(&tok, tok->next, node);
      
      continue;
    }

    if (equal(tok, "["))
    {
      // x[y] is short for *(x+y)
      Token *start = tok;
      Node *idx = expr(&tok, tok->next);
      SET_CTX(ctx);           
      tok = skip(tok, "]", ctx);
      
      add_type(node);
      Type *ty = node->ty;
      node = new_unary(ND_DEREF, new_add(node, idx, start, false), start);
      if (is_array(ty))
        apply_cv_qualifier(node, ty);
       continue;
    }

    if (equal(tok, "."))
    {
      node = struct_ref(node, tok->next);
      tok = tok->next->next;
      continue;
    }

    if (equal(tok, "->"))
    {
      // x->y is short for (*x).y
      add_type(node);
      Type *ty = node->ty;
      node = new_unary(ND_DEREF, node, tok);
      node = struct_ref(node, tok->next);

      if (is_array(ty))
        apply_cv_qualifier(node, ty);

      tok = tok->next->next;
      continue;
    }

    if (equal(tok, "++"))
    {
      node = new_inc_dec(node, tok, 1);
      tok = tok->next;
      continue;
    }

    if (equal(tok, "--"))
    {
      node = new_inc_dec(node, tok, -1);
      tok = tok->next;
      continue;
    }

    *rest = tok;
    return node;
  }
}

static char *token_to_string(Token *tok) {
  char *buf = calloc(tok->len + 1, 1);  // allocate and zero-initialize
  memcpy(buf, tok->loc, tok->len);
  return buf;
}

static bool is_returned_twice(char *name) {
  return !strcmp(name, "setjmp") || !strcmp(name, "_setjmp") ||
         !strcmp(name, "sigsetjmp") || !strcmp(name, "__sigsetjmp") ||
         !strcmp(name, "__builtin_setjmp") ||
         !strcmp(name, "savectx") || !strcmp(name, "vfork") ||
         !strcmp(name, "getcontext");
}



// funcall = (assign ("," assign)*)? ")"
static Node *funcall(Token **rest, Token *tok, Node *fn)
{
  add_type(fn);
  
  if (fn->kind == ND_VAR && (!strcmp(fn->var->name, "alloca") || !strcmp(fn->var->name, "__builtin_alloca")))
    need_alloca_bottom();

  if (fn->ty->kind != TY_FUNC &&
      (fn->ty->kind != TY_PTR || fn->ty->base->kind != TY_FUNC))
    error_tok(fn->tok, "%s:%d: in funcall : not a function %d %s", __FILE__, __LINE__, fn->ty->kind, tok->loc);

  Type *ty = (fn->ty->kind == TY_FUNC) ? fn->ty : fn->ty->base;
  Type *param_ty = ty->params;

  Node head = {};
  Node *cur = &head;

  while (!equal(tok, ")"))
  {
    if (cur != &head) {
      SET_CTX(ctx);        
      tok = skip(tok, ",", ctx);
    }

    Node *arg = assign(&tok, tok);
    add_type(arg);


    if (!param_ty && !ty->is_variadic && !ty->is_oldstyle)
      error_tok(tok, "%s:%d: in funcall : too many arguments", __FILE__, __LINE__);

    //can't be done later because param_ty will be set to the next value
    //if param_ty is null it means that it's a variadic argument.
    if (!param_ty){
      arg->ty->is_variadic = true;      
    }


    if (param_ty)
    {
      if (param_ty->kind != TY_STRUCT && param_ty->kind != TY_UNION)
        arg = new_cast(arg, param_ty);
      param_ty = param_ty->next;
      
    }
    else if (arg->ty->kind == TY_FLOAT)
    {
      // If parameter type is omitted (e.g. in "..."), float
      // arguments are promoted to double.
      arg = new_cast(arg, ty_double);
    } else if (is_array(arg->ty))
        arg = new_cast(arg, pointer_to(arg->ty->base));
      else if (arg->ty->kind == TY_FUNC)
        arg = new_cast(arg, pointer_to(arg->ty));


    cur = cur->next = arg;
  }

  if (param_ty && !ty->is_oldstyle)
    error_tok(tok, "%s:%d: in funcall : too few arguments", __FILE__, __LINE__);
  SET_CTX(ctx);    
  *rest = skip(tok, ")", ctx);

  Node *node = new_unary(ND_FUNCALL, fn, tok);
  node->func_ty = ty;
  node->ty = ty->return_ty;
  node->args = head.next;

  


  // If a function returns a struct, it is caller's responsibility
  // to allocate a space for the return value.
  if (node->ty->kind == TY_STRUCT || node->ty->kind == TY_UNION)
    node->ret_buffer = new_lvar("", node->ty, NULL);
  return node;
}

// generic-selection = "(" assign "," generic-assoc ("," generic-assoc)* ")"
//
// generic-assoc = type-name ":" assign
//               | "default" ":" assign
static Node *generic_selection(Token **rest, Token *tok)
{
  // Token *start = tok;
  SET_CTX(ctx);   
  tok = skip(tok, "(", ctx);

  Node *ctrl = assign(&tok, tok);
  add_type(ctrl);

  Type *t1 = ctrl->ty;
  if (t1->kind == TY_FUNC)
    t1 = pointer_to(t1);
  else if (is_array(t1))
    t1 = pointer_to(t1->base);
  else
    t1 = unqual(t1);

  // try to fix issue with VLC
  Node *ret = NULL;

  while (!consume(rest, tok, ")"))
  {
    SET_CTX(ctx);          
    tok = skip(tok, ",", ctx);

    if (equal(tok, "default"))
    {
      SET_CTX(ctx);           
      tok = skip(tok->next, ":", ctx);
      Node *node = assign(&tok, tok);
      if (!ret)
        ret = node;
      continue;
    }

    Type *t2 = typename(&tok, tok);
    SET_CTX(ctx); 
    tok = skip(tok, ":", ctx);
    Node *node = assign(&tok, tok);
    if (is_compatible2(t1, t2))
      ret = node;
  }

  if (!ret)
  {
    ret = ctrl;
    // error_tok(start, "controlling expression type not compatible with"
    //           " any generic association type");
  }
  return ret;
}

static Token *skip_choose_expr_arg(Token *tok) {
  int paren = 0;
  int bracket = 0;
  int brace = 0;

  for (; tok->kind != TK_EOF; tok = tok->next) {
    if (paren == 0 && bracket == 0 && brace == 0 &&
        (equal(tok, ",") || equal(tok, ")")))
      return tok;

    if (equal(tok, "(")) {
      paren++;
      continue;
    }
    if (equal(tok, "[")) {
      bracket++;
      continue;
    }
    if (equal(tok, "{")) {
      brace++;
      continue;
    }

    if (equal(tok, ")")) {
      if (paren > 0) {
        paren--;
        continue;
      }
      error_tok(tok, "%s:%d: in skip_choose_expr_arg : unbalanced ')'", __FILE__, __LINE__);
    }
    if (equal(tok, "]")) {
      if (bracket > 0) {
        bracket--;
        continue;
      }
      error_tok(tok, "%s:%d: in skip_choose_expr_arg : unbalanced ']'", __FILE__, __LINE__);
    }
    if (equal(tok, "}")) {
      if (brace > 0) {
        brace--;
        continue;
      }
      error_tok(tok, "%s:%d: in skip_choose_expr_arg : unbalanced '}'", __FILE__, __LINE__);
    }
  }

  error_tok(tok, "%s:%d: in skip_choose_expr_arg : unexpected end of input", __FILE__, __LINE__);
  return tok;
}


// primary = "(" "{" stmt+ "}" ")"
//         | "(" expr ")"
//         | "sizeof" "(" type-name ")"
//         | "sizeof" unary
//         | "_Alignof" "(" type-name ")"
//         | "_Alignof" unary
//         | "_Generic" generic-selection
//         | "__builtin_types_compatible_p" "(" type-name, type-name, ")"
//         | "__builtin_reg_class" "(" type-name ")"
//         | ident
//         | str
//         | num
static Node *primary(Token **rest, Token *tok)
{

  Token *start = tok;


  if ((equal(tok, "(") && equal(tok->next, "{")))
  {
    // This is a GNU statement expresssion.
    // Node *node = new_node(ND_STMT_EXPR, tok);
    // node->body = compound_stmt(&tok, tok->next->next)->body;
    Node *stmt = NULL;
    Node *node = compound_stmt(&tok, tok->next->next, &stmt);
    node->kind = ND_STMT_EXPR;

    if (stmt && stmt->kind == ND_EXPR_STMT) {
      Node *expr = stmt->lhs;
      if (expr->ty->kind == TY_STRUCT || expr->ty->kind == TY_UNION) {
        Obj *var = new_lvar("", expr->ty, NULL);
        expr = new_binary(ND_ASSIGN, new_var_node(var, tok),
                          expr, tok);
        add_type(expr);
        stmt->lhs = expr;
      } else if (is_array(expr->ty)) {
        stmt->lhs = new_cast(expr, pointer_to(expr->ty->base));
      }
    }
    SET_CTX(ctx);       
    *rest = skip(tok, ")", ctx);
    return node;
  }
  
  if (equal(tok, "("))
  {
    Node *node = expr(&tok, tok->next);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "sizeof"))
  {
    if (equal(tok->next, "(") && is_typename(tok->next->next)) {
      // sizeof(type-name)
      enter_scope();
      Type *ty = typename(&tok, tok->next->next);
      leave_scope();
      SET_CTX(ctx);
      *rest = skip(tok, ")", ctx);

      // Runtime-sized types (VLA / struct-with-VLA).
      Node *vla_node = sizeof_vla_type(ty, tok);
      if (vla_node)
        return vla_node;

      // Flexible array member: exclude the last (unsized) member.
      if (ty->kind == TY_STRUCT && ty->is_flexible) {
        Member *mem = ty->members;
        while (mem->next)
          mem = mem->next;
        if (mem->ty->kind == TY_ARRAY)
          return new_ulong((ty->size - mem->ty->size), tok);
      }

      if ((ty->kind == TY_UNION || ty->kind == TY_STRUCT) && ty->size < 0)
        error_tok(tok, "%s:%d: in primary : incomplete type for sizeof", __FILE__, __LINE__);

      return new_ulong(ty->size, start);
    } else {
      // sizeof expr
      Node *node = unary(rest, tok->next);
      add_type(node);

      // GCC: array in comma-expr decays (unless compound literal).
      if (node->kind == ND_COMMA && node->rhs && is_array(node->rhs->ty)
          && node->rhs->var && !node->rhs->var->is_compound_lit)
        node->ty = pointer_to(node->ty->base);

      // Runtime-sized types (VLA / struct-with-VLA).
      Node *vla_node = sizeof_vla_type(node->ty, tok);
      if (vla_node)
        return vla_node;

      if ((node->ty->kind == TY_UNION || node->ty->kind == TY_STRUCT) && node->ty->size < 0)
        error_tok(tok, "%s:%d: in primary : incomplete type for sizeof", __FILE__, __LINE__);

      if (node->ty->kind == TY_STRUCT && node->ty->is_flexible) {
        Member *mem = node->ty->members;
        while (mem->next)
          mem = mem->next;
        if (mem->ty->kind == TY_ARRAY)
          return new_ulong((node->ty->size - mem->ty->size), tok);
      }

      if (node->ty->size < 0)
        error_tok(tok, "%s:%d: in primary : incomplete type for sizeof", __FILE__, __LINE__);

      return new_ulong(node->ty->size, start);
    }
  }



  //from @fuhsnn merging alignof
  if (equal(tok, "_Alignof") || equal(tok, "alignof") ||  equal(tok, "__alignof__")) {
    Token *start = tok;
    Type *ty;
    if (equal(tok->next, "(") && is_typename(tok->next->next)) {
      Token *start_paren = tok->next;
      enter_scope();
      ty = typename(&tok, tok->next->next);
      leave_scope();
      SET_CTX(ctx); 
      *rest = skip(tok, ")", ctx);
      if (equal(*rest, "{")) {
        Node *node = unary(rest, start_paren);
        add_type(node);
        ty = node->ty;
      }
    } else {
      Node *node = unary(rest, tok->next);
      switch (node->kind) {
        case ND_MEMBER:
          return new_ulong(MAX(node->member->align, node->member->attr_align), start);
        case ND_VAR:
          return new_ulong(node->var->align, start);
        }
      add_type(node);
      ty = node->ty;
    }
    // _Alignof does not apply array-to-pointer decay for expressions.
    // Preserve array alignment (including _Alignas/aligned on arrays).
    return new_ulong(ty->align, start);
  }

  if (equal(tok, "_Generic"))
    return generic_selection(rest, tok->next);

  if (equal(tok, "__builtin_types_compatible_p"))
  {
    SET_CTX(ctx);      
    tok = skip(tok->next, "(", ctx);
    Type *t1 = typename(&tok, tok);
    if (equal(tok, ",")) {
      SET_CTX(ctx);       
      tok = skip(tok, ",", ctx);
    }
    Type *t2 = typename(&tok, tok);
    SET_CTX(ctx);       
    *rest = skip(tok, ")", ctx);

    return new_num(is_compatible(unqual(t1), unqual(t2)), start);
  }

  if (equal(tok, "__builtin_constant_p")) {
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    Node *expr = assign(&tok, tok);
    SET_CTX(ctx);     
    *rest = skip(tok, ")", ctx);
    bool is_constant = false;
    if (expr->tok->kind == TK_NUM || expr->tok->kind == TK_STR || is_const_expr(expr)) {
        // Consider numeric and character literals as constants
        is_constant = true;
    }
    return new_num(is_constant ? 1 : 0, start);
  }

  if (equal(tok, "__builtin_choose_expr")) {
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);

    Node *cond_node = conditional(&tok, tok);
    if (!is_const_expr(cond_node))
      error_tok(cond_node->tok, "%s:%d: in primary : __builtin_choose_expr condition is not constant", __FILE__, __LINE__);
    int64_t cond = eval(cond_node);
    SET_CTX(ctx);
    tok = skip(tok, ",", ctx);

    if (cond) {
      Node *node = assign(&tok, tok);
      SET_CTX(ctx);
      tok = skip(tok, ",", ctx);
      tok = skip_choose_expr_arg(tok);
      SET_CTX(ctx);
      *rest = skip(tok, ")", ctx);
      return node;
    }

    tok = skip_choose_expr_arg(tok);
    SET_CTX(ctx);
    tok = skip(tok, ",", ctx);
    Node *node = assign(&tok, tok);
    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_rotateleft32")) {
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    Node *x = assign(&tok, tok);
    SET_CTX(ctx);
    tok = skip(tok, ",", ctx);
    Node *y = assign(&tok, tok);
    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);

    Node *x_u = new_cast(x, ty_uint);
    Node *y_u = new_cast(y, ty_uint);
    Node *mask1 = new_num(31, start);
    Node *mask2 = new_num(31, start);

    Node *y_mask1 = new_binary(ND_BITAND, y_u, mask1, start);
    Node *y_mask2 = new_binary(ND_BITAND, y_u, mask2, start);
    Node *left = new_binary(ND_SHL, x_u, y_mask1, start);

    Node *sub = new_binary(ND_SUB, new_num(32, start), y_mask2, start);
    Node *sub_mask = new_binary(ND_BITAND, sub, new_num(31, start), start);
    Node *right = new_binary(ND_SHR, x_u, sub_mask, start);

    return new_binary(ND_BITOR, left, right, start);
  }

  if (equal(tok, "__builtin_rotateleft64")) {
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    Node *x = assign(&tok, tok);
    SET_CTX(ctx);
    tok = skip(tok, ",", ctx);
    Node *y = assign(&tok, tok);
    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);

    Node *x_u = new_cast(x, ty_ulong);
    Node *y_u = new_cast(y, ty_ulong);
    Node *mask1 = new_num(63, start);
    Node *mask2 = new_num(63, start);

    Node *y_mask1 = new_binary(ND_BITAND, y_u, mask1, start);
    Node *y_mask2 = new_binary(ND_BITAND, y_u, mask2, start);
    Node *left = new_binary(ND_SHL, x_u, y_mask1, start);

    Node *sub = new_binary(ND_SUB, new_num(64, start), y_mask2, start);
    Node *sub_mask = new_binary(ND_BITAND, sub, new_num(63, start), start);
    Node *right = new_binary(ND_SHR, x_u, sub_mask, start);

    return new_binary(ND_BITOR, left, right, start);
  }


 if (equal(tok, "__builtin_offsetof") || equal(tok, "offsetof")) {
    SET_CTX(ctx);     
    tok = skip(tok->next, "(", ctx);
    Type *ty = typename(&tok, tok);
    SET_CTX(ctx);       
    tok = skip(tok, ",", ctx);

    Node *node = NULL;
    int offset = 0;
    do {
      Member *mem;
      do {
        mem = struct_designator(&tok, tok, ty);
        offset += mem->offset;
        ty = mem->ty;
      } while (!mem->name);
      SET_CTX(ctx);   
      for (; ty->base && consume(&tok, tok, "["); tok = skip(tok, "]", ctx)) {
        ty = ty->base;
        Node *expr = conditional(&tok, tok);
        if (!node)
          node = new_binary(ND_MUL, expr, new_long(ty->size, tok), tok);
        else
          node = new_binary(ND_ADD, node, new_binary(ND_MUL, expr, new_long(ty->size, tok), tok), tok);
      }
    } while (consume(&tok, tok, "."));
    SET_CTX(ctx);   
    *rest = skip(tok, ")", ctx);
    if (!node)
      return new_ulong(offset, tok);
    return new_binary(ND_ADD, node, new_ulong(offset, tok), tok);
  }



  //trying to fix ===== some builtin functions linked to mmx/emms
  if (equal(tok, "__builtin_ia32_emms") ||  equal(tok, "__builtin_ia32_rdtsc") ||
      equal(tok, "__builtin_ia32_readeflags_u64") || equal(tok, "__builtin_ia32_rdsspq") ||
      equal(tok, "__builtin_ia32_saveprevssp") || equal(tok, "__builtin_ia32_setssbsy") ||
      equal(tok, "__builtin_ia32_xbegin") || equal(tok, "__builtin_ia32_xend") ||
      equal(tok, "__builtin_ia32_serialize") || equal(tok, "__builtin_ia32_xsusldtrk") ||
      equal(tok, "__builtin_ia32_xresldtrk") || equal(tok, "__builtin_ia32_clui") ||
      equal(tok, "__builtin_ia32_stui") || equal(tok, "__builtin_ia32_testui") ||
      equal(tok, "__builtin_ia32_wbnoinvd") || equal(tok, "__builtin_ia32_xtest") ||
      equal(tok, "__builtin_ia32_wbinvd") || equal(tok, "__builtin_ia32_rdpid") ||
      equal(tok, "__builtin_ia32_slwpcb") || equal(tok, "__builtin_ia32_rdpkru") ||
      equal(tok, "__builtin_ia32_rdfsbase32") || equal(tok, "__builtin_ia32_rdfsbase64") ||
      equal(tok, "__builtin_ia32_rdgsbase32") || equal(tok, "__builtin_ia32_rdgsbase64") ||      
      equal(tok, "__builtin_ia32_vzeroall") || equal(tok, "__builtin_ia32_vzeroupper") ||
      equal(tok, "__builtin_ia32_femms") ||
      equal(tok, "__builtin_ia32_sfence") || equal(tok, "__builtin_ia32_pause") ||
      equal(tok, "__builtin_ia32_lfence") || equal(tok, "__builtin_ia32_mfence")) 
  {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx);      
      tok = skip(tok->next, "(", ctx);
      SET_CTX(ctx); 
      *rest = skip(tok, ")", ctx);    
      return node;
    }
  }

  if (equal(tok, "__builtin_ia32_stmxcsr")) {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);    
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      if (!equal(tok, ")")) {
        node->lhs = assign(&tok, tok); 
        add_type(node->lhs);
      }
      SET_CTX(ctx); 
      *rest = skip(tok, ")", ctx);    
      return node;
    }
  }

  if (equal(tok, "__builtin_ia32_cvtss2si") || equal(tok, "__builtin_ia32_cvttss2si") ||
    equal(tok, "__builtin_ia32_cvttss2si64") || equal(tok, "__builtin_ia32_movmskps") ||
    equal(tok, "__builtin_ia32_ldmxcsr") ||  equal(tok, "__builtin_ia32_sqrtpd") ||
    equal(tok, "__builtin_ia32_sqrtsd") ||  equal(tok, "__builtin_ia32_movq128") ||
    equal(tok, "__builtin_ia32_cvtdq2pd") || equal(tok, "__builtin_ia32_cvtdq2ps") ||
    equal(tok, "__builtin_ia32_cvtpd2dq") || equal(tok, "__builtin_ia32_cvtpd2ps") ||
    equal(tok, "__builtin_ia32_cvttpd2dq") || equal(tok, "__builtin_ia32_cvtps2dq") || 
    equal(tok, "__builtin_ia32_cvttps2dq") || equal(tok, "__builtin_ia32_cvtps2pd") || 
    equal(tok, "__builtin_ia32_cvtsd2si") || equal(tok, "__builtin_ia32_cvtsd2si64") || 
    equal(tok, "__builtin_ia32_cvttsd2si") || equal(tok, "__builtin_ia32_cvttsd2si64") ||
    equal(tok, "__builtin_ia32_movmskpd") || equal(tok, "__builtin_ia32_pmovmskb128") || 
    equal(tok, "__builtin_ia32_cvtss2si64") || equal(tok, "__builtin_ia32_cvtps2pi") || 
    equal(tok, "__builtin_ia32_cvttps2pi") || equal(tok, "__builtin_ia32_cvttpd2pi") || 
    equal(tok, "__builtin_ia32_cvtpi2pd") ||  equal(tok, "__builtin_ia32_cvtpd2pi") ||
    equal(tok, "__builtin_ia32_sqrtss") || equal(tok, "__builtin_ia32_rcpss") || 
    equal(tok, "__builtin_ia32_rcpps") || equal(tok, "__builtin_ia32_rsqrtps") ||
    equal(tok, "__builtin_ia32_clflush") || equal(tok, "_mm_clflush") ||
    equal(tok, "__builtin_ia32_pmovmskb") || equal(tok, "__builtin_ia32_sqrtps") || 
    equal(tok, "__builtin_parity") || equal(tok, "__builtin_parityl") ||
    equal(tok, "__builtin_parityll") || equal(tok, "__builtin_ia32_movshdup") ||
    equal(tok, "__builtin_ia32_movsldup") || equal(tok, "__builtin_ia32_lddqu") ||
    equal(tok, "__builtin_ia32_pabsb128") || equal(tok, "__builtin_ia32_pabsw128") || 
    equal(tok, "__builtin_ia32_pabsd128") || equal(tok, "__builtin_ia32_pabsb") || 
    equal(tok, "__builtin_ia32_pabsw") || equal(tok, "__builtin_ia32_pabsd") ||
    equal(tok, "__builtin_ia32_phminposuw128") || equal(tok, "__builtin_ia32_pmovsxbd128") ||
    equal(tok, "__builtin_ia32_pmovsxwd128") || equal(tok, "__builtin_ia32_pmovsxbq128") || 
    equal(tok, "__builtin_ia32_pmovsxdq128") || equal(tok, "__builtin_ia32_pmovsxwq128") ||
    equal(tok, "__builtin_ia32_pmovsxbw128") || equal(tok, "__builtin_ia32_pmovzxbd128") ||
    equal(tok, "__builtin_ia32_pmovzxwd128") || equal(tok, "__builtin_ia32_pmovzxbq128") || 
    equal(tok, "__builtin_ia32_pmovzxdq128") || equal(tok, "__builtin_ia32_pmovzxwq128") ||
    equal(tok, "__builtin_ia32_pmovzxbw128") || equal(tok, "__builtin_ia32_movntdqa") ||
    equal(tok, "__builtin_ia32_bsrsi") || equal(tok, "__builtin_ia32_rdpmc") ||
    equal(tok, "__builtin_ia32_bsrdi") || equal(tok, "__builtin_ia32_rdtscp") ||
    equal(tok, "__builtin_ia32_writeeflags_u64") || equal(tok, "__builtin_ia32_incsspq") ||
    equal(tok, "__builtin_ia32_rstorssp") || equal(tok, "__builtin_ia32_clrssbsy") || 
    equal(tok, "__builtin_ia32_rsqrtss") || equal(tok, "__builtin_ia32_tzcnt_u16")) {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);    
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->lhs = assign(&tok, tok);
      add_type(node->lhs);
      SET_CTX(ctx); 
      *rest = skip(tok, ")", ctx);
      return node;
    }

  }
   
  if (equal(tok, "__builtin_ia32_pblendvb128") || 
      equal(tok, "__builtin_ia32_blendvpd") ||
      equal(tok, "__builtin_ia32_blendvps") ||
      equal(tok, "__builtin_ia32_pcmpgtb256_mask"))
  {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->builtin_args[0] = assign(&tok, tok);
      add_type(node->builtin_args[0]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[1] = assign(&tok, tok);
      add_type(node->builtin_args[1]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[2] = assign(&tok, tok);
      add_type(node->builtin_args[2]);
      node->builtin_nargs = 3;
      SET_CTX(ctx);       
      *rest = skip(tok, ")", ctx);
    return node;
    }
  }

  //builtin shuffle can have two forms : 
  //builtin_shuffle(a, b, mask) or
  //builtin_shuffle(a, mask)  where B defaults to A
  if (equal(tok, "__builtin_shuffle")) {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx);
      tok = skip(tok->next, "(", ctx);
      Node *a = assign(&tok, tok);
      add_type(a);
      SET_CTX(ctx);
      tok = skip(tok, ",", ctx);
      Node *second = assign(&tok, tok);
      add_type(second);
      SET_CTX(ctx);
      if (equal(tok, ",")) {
        tok = tok->next;
        Node *mask = assign(&tok, tok);
        add_type(mask);
        node->builtin_args[0] = a;
        node->builtin_args[1] = second;
        node->builtin_args[2] = mask;
      } else {
        node->builtin_args[0] = a;
        node->builtin_args[1] = a;      
        node->builtin_args[2] = second; 
      }
      node->builtin_nargs = 3;
      SET_CTX(ctx);
      *rest = skip(tok, ")", ctx);
      return node;
    }
  }


  if (equal(tok, "__builtin_ia32_maskmovq"))
  {   
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->builtin_args[0] = assign(&tok, tok);
      add_type(node->builtin_args[0]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[1] = assign(&tok, tok);
      add_type(node->builtin_args[1]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[2] = assign(&tok, tok);
      add_type(node->builtin_args[2]);
      node->builtin_nargs = 3;
      SET_CTX(ctx);       
      *rest = skip(tok, ")", ctx);
    return node;
    }
  }

  if (equal(tok, "__builtin_ia32_monitor") || equal(tok, "__builtin_ia32_mwait")) {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
        Node *node = new_node(builtin, tok);
        SET_CTX(ctx); 
        tok = skip(tok->next, "(", ctx);
        node->builtin_args[0] = assign(&tok, tok);
        add_type(node->builtin_args[0]);
        tok = skip(tok, ",", ctx);
        node->builtin_args[1] = assign(&tok, tok);
        add_type(node->builtin_args[1]);
        if (builtin == ND_MONITOR) { // third argument only for monitor
            tok = skip(tok, ",", ctx);
            node->builtin_args[2] = assign(&tok, tok);
            add_type(node->builtin_args[2]);
            node->builtin_nargs = 3;
        } else {
            node->builtin_nargs = 2;
        }
        SET_CTX(ctx);       
        *rest = skip(tok, ")", ctx);
        return node;
    }
  }

  
    
  if (equal(tok, "__builtin_ia32_maskmovdqu") || equal(tok, "__builtin_prefetch"))
  {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->builtin_args[0] = assign(&tok, tok);
      add_type(node->builtin_args[0]);
      int nargs = 1;
      while (equal(tok, ",")) {
          tok = tok->next;
          if (nargs < 16) {
              node->builtin_args[nargs] = assign(&tok, tok);
              add_type(node->builtin_args[nargs]);
              nargs++;
          } else {
              error_tok(tok, "too many arguments to builtin");
          }
      }
      node->builtin_nargs = nargs;
      SET_CTX(ctx);       
      *rest = skip(tok, ")", ctx);
    return node;
    }
  }
    

  if (equal(tok, "__builtin_ia32_vec_init_v4hi") || equal(tok, "__builtin_ia32_sbb_u32") || 
    equal(tok, "__builtin_ia32_addcarryx_u32") || equal(tok, "__builtin_ia32_sbb_u64") || 
    equal(tok, "__builtin_ia32_addcarryx_u64"))
  {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->builtin_args[0] = assign(&tok, tok);
      add_type(node->builtin_args[0]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[1] = assign(&tok, tok);
      add_type(node->builtin_args[1]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[2] = assign(&tok, tok);
      add_type(node->builtin_args[2]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[3] = assign(&tok, tok);
      add_type(node->builtin_args[3]);
      node->builtin_nargs = 4;
      SET_CTX(ctx);       
      *rest = skip(tok, ")", ctx);
    return node;
    }
  }

     
  if (equal(tok, "__builtin_ia32_shufps") || equal(tok, "__builtin_ia32_shufpd"))
  {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->lhs = assign(&tok, tok);
      add_type(node->lhs);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->rhs = assign(&tok, tok);
      add_type(node->rhs);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->rhs->val = const_expr(&tok, tok);
      SET_CTX(ctx);       
      *rest = skip(tok, ")", ctx);
    return node;
    }
  }

  if (equal(tok, "__builtin_ia32_vec_init_v8qi"))
  {
    int builtin = builtin_enum(tok);
    if (builtin != -1) {
      Node *node = new_node(builtin, tok);
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);
      node->builtin_args[0] = assign(&tok, tok);
      add_type(node->builtin_args[0]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[1] = assign(&tok, tok);
      add_type(node->builtin_args[1]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[2] = assign(&tok, tok);
      add_type(node->builtin_args[2]);
      SET_CTX(ctx); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[3] = assign(&tok, tok);
      add_type(node->builtin_args[3]);
      tok = skip(tok, ",", ctx);
      node->builtin_args[4] = assign(&tok, tok);
      add_type(node->builtin_args[4]);
      tok = skip(tok, ",", ctx);
      node->builtin_args[5] = assign(&tok, tok);
      add_type(node->builtin_args[5]);   
      tok = skip(tok, ",", ctx);
      node->builtin_args[6] = assign(&tok, tok);
      add_type(node->builtin_args[6]); 
      tok = skip(tok, ",", ctx);
      node->builtin_args[7] = assign(&tok, tok);
      add_type(node->builtin_args[7]);                  
      node->builtin_nargs = 8;      
      SET_CTX(ctx);       
      *rest = skip(tok, ")", ctx);
    return node;
    }
  }


  //managing lots of  builtin_ia32 that needs two args
  // defined in builtin_table[]
  int builtin = builtin_enum(tok);
  if (builtin != -1) {
    Node *node = new_node(builtin, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok);
    add_type(node->lhs);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->rhs = assign(&tok, tok);
    add_type(node->rhs);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }


  if (equal(tok, "__builtin_reg_class"))
  {
    SET_CTX(ctx);      
    tok = skip(tok->next, "(", ctx);
    Type *ty = typename(&tok, tok);
    SET_CTX(ctx);      
    *rest = skip(tok, ")", ctx);

    if (is_integer(ty) || ty->kind == TY_PTR)
      return new_num(0, start);
    if (ty->kind == TY_FLOAT || ty->kind == TY_DOUBLE || ty->kind == TY_VECTOR)
      return new_num(1, start);
    return new_num(2, start);
  }


  if (equal(tok, "__atomic_is_lock_free")) {
    Node *node = new_node(ND_ATOMIC_IS_LOCK_FREE, tok);
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok);
    SET_CTX(ctx);
    if (consume(&tok, tok, ",")) {
      node->rhs = assign(&tok, tok);
    }
    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_compare_and_swap"))
  {
    Node *node = new_node(ND_CAS, tok);
    SET_CTX(ctx);     
    tok = skip(tok->next, "(", ctx);
    node->cas_addr = assign(&tok, tok);
    SET_CTX(ctx);     
    tok = skip(tok, ",", ctx);
    node->cas_old = assign(&tok, tok);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->cas_new = assign(&tok, tok);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }


  if (equal(tok, "__builtin_atomic_exchange"))
  {
    Node *node = new_node(ND_EXCH, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok);
    add_type(node->lhs);
    SET_CTX(ctx);     
    tok = skip(tok, ",", ctx);
    node->rhs = assign(&tok, tok);
    add_type(node->rhs);
    SET_CTX(ctx);       
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__sync_val_compare_and_swap")) {
    Node *node = new_node(ND_CAS_N, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->cas_addr = assign(&tok, tok);
    add_type(node->cas_addr);
    SET_CTX(ctx);     
    tok = skip(tok, ",", ctx);
    node->cas_old = assign(&tok, tok);
    add_type(node->cas_old);
    SET_CTX(ctx);     
    tok = skip(tok, ",", ctx);
    node->cas_new = assign(&tok, tok);
    add_type(node->cas_new);
    SET_CTX(ctx);       
    *rest = skip(tok, ")", ctx);
    return node;
  }


  // Extend the parser to recognize __sync_synchronize()
  if (equal(tok, "__sync_synchronize")) {
      Node *node = new_node(ND_SYNC, tok);
      SET_CTX(ctx);     
      *rest = skip(tok->next, "(", ctx);
      SET_CTX(ctx);     
      *rest = skip(*rest, ")", ctx);
      return node;
  }

  if (equal(tok, "__builtin_memcpy") && equal(tok->next, "(")) {
      return parse_memcpy(tok, rest);
  }

  if (equal(tok, "__builtin_memset") && equal(tok->next, "(")) {
      return parse_memset(tok, rest);
  }

  if (equal(tok, "__builtin_huge_valf")) {
    Node *node = new_node(ND_BUILTIN_HUGE_VALF, tok); 
    node->ty = ty_float;
    node->fval = INFINITY;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_inf")) {
    Node *node = new_node(ND_BUILTIN_INF, tok); 
    node->ty = ty_double;
    node->fval = INFINITY;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    SET_CTX(ctx); 
    *rest = skip(tok, ")",  ctx);
    return node;
  }
  if (equal(tok, "__builtin_huge_val")) {
    Node *node = new_node(ND_BUILTIN_HUGE_VAL, tok); 
    node->ty = ty_double;
    node->fval = INFINITY;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    SET_CTX(ctx); 
    *rest = skip(tok, ")",  ctx);
    return node;
  }

  if (equal(tok, "__builtin_huge_vall")) {
    Node *node = new_node(ND_BUILTIN_HUGE_VALL, tok);
    node->ty = ty_ldouble;
    node->fval = INFINITY; 
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }

    if (equal(tok, "__builtin_fpclassify")) {
      Node *node = new_node(ND_FPCLASSIFY, tok);
      node->fpc = calloc(1, sizeof(FpClassify));
      node->ty = ty_int;
      SET_CTX(ctx);
      tok = skip(tok->next, "(", ctx);
      for (int i = 0; i < 5; ++i) {
        node->fpc->args[i] = const_expr(&tok, tok);
        SET_CTX(ctx);
        tok = skip(tok, ",", ctx);
      }
      node->fpc->node = expr(&tok, tok);
      add_type(node->fpc->node);
      if (!is_flonum(node->fpc->node->ty)) {        
        error_tok(tok, "%s:%d: in primary : need floating point", __FILE__, __LINE__);
      }
      SET_CTX(ctx);
      *rest = skip(tok, ")", ctx);
      return node;
    }

  if (equal(tok, "__builtin_inff")) {
    Node *node = new_node(ND_BUILTIN_INFF, tok);
    node->ty = ty_float;    
    node->fval = INFINITY;     
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;
  }

  if (equal(tok, "__builtin_nan")) {
    Node *node = new_node(ND_BUILTIN_NAN, tok);
    node->ty = ty_double;
    node->fval = NAN;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    if (tok->kind == TK_STR)
      tok = tok->next; 
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }

    if (equal(tok, "__builtin_nanf")) {
    Node *node = new_node(ND_BUILTIN_NANF, tok);
    node->ty = ty_float;
    node->fval = NAN;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    if (tok->kind == TK_STR)
      tok = tok->next;
    SET_CTX(ctx);       
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_nanl")) {
  Node *node = new_node(ND_BUILTIN_NANL, tok);
  node->ty = ty_ldouble;
  node->fval = NAN;
  SET_CTX(ctx); 
  tok = skip(tok->next, "(", ctx);
  if (tok->kind == TK_STR)
    tok = tok->next;
  SET_CTX(ctx); 
  *rest = skip(tok, ")", ctx);
  return node;
}
  if (equal(tok, "__builtin_isnan"))
  {
    return ParseBuiltin(ND_BUILTIN_ISNAN, tok, rest);
  }

  if (equal(tok, "__builtin_clz"))
  {
    return ParseBuiltin(ND_BUILTIN_CLZ, tok, rest);
  }

  if (equal(tok, "__builtin_clzl"))
  {
    return ParseBuiltin(ND_BUILTIN_CLZL, tok, rest);
  }

  if (equal(tok, "__builtin_clzll"))
  {
    return ParseBuiltin(ND_BUILTIN_CLZLL, tok, rest);
  }

  if (equal(tok, "__builtin_stdc_leading_zeros"))
  {
    return ParseBuiltin(ND_BUILTIN_CLZLL, tok, rest);
  }


  if (equal(tok, "__builtin_ctz"))
  {
    return ParseBuiltin(ND_BUILTIN_CTZ, tok, rest);
  }


  if (equal(tok, "__builtin_ctzl"))
  {
    return ParseBuiltin(ND_BUILTIN_CTZL, tok, rest);
  }


  if (equal(tok, "__builtin_ctzll"))
  {
    return ParseBuiltin(ND_BUILTIN_CTZLL, tok, rest);
  }

  if (equal(tok, "__builtin_stdc_trailing_zeros"))
  {
    return ParseBuiltin(ND_BUILTIN_CTZLL, tok, rest);
  }

  if (equal(tok, "__builtin_stdc_count_ones"))
  {
    return ParseBuiltin(ND_POPCOUNTLL, tok, rest);
  }

  if (equal(tok, "__builtin_stdc_has_single_bit"))
  {
    Node *node = ParseBuiltin(ND_POPCOUNTLL, tok, rest);
    node->builtin_val = new_cast(node->builtin_val, ty_ulong);
    add_type(node->builtin_val);
    add_type(node);
    Node *one = new_num(1, tok);
    one = new_cast(one, node->ty);
    add_type(one);
    return new_binary(ND_EQ, node, one, tok);
    
  }

  if (equal(tok, "__builtin_stdc_bit_width"))
  {
    Token *start = tok;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    Node *arg = assign(&tok, tok);
    SET_CTX(ctx);      
    *rest = skip(tok, ")", ctx);

    add_type(arg);
    Obj *var = new_lvar("", ty_ulong, NULL);
    Node *init = new_unary(ND_EXPR_STMT, new_binary(ND_ASSIGN, new_var_node(var, start), new_cast(arg, ty_ulong), start), start);
    
    Node *clz = new_node(ND_BUILTIN_CLZLL, start);
    clz->builtin_val = new_var_node(var, start);
    
    Node *cond_node = new_node(ND_COND, start);
    cond_node->cond = to_bool(new_var_node(var, start));
    cond_node->then = new_binary(ND_SUB, new_num(64, start), clz, start);
    cond_node->els = new_num(0, start);
    
    Node *node = new_node(ND_STMT_EXPR, start);
    node->body = init;
    init->next = new_unary(ND_EXPR_STMT, cond_node, start);
    return node;
  }

  if (equal(tok, "__builtin_bswap16")) {
      return ParseBuiltin(ND_BUILTIN_BSWAP16, tok, rest);
  }

  if (equal(tok, "__builtin_bswap32")) {
      return ParseBuiltin(ND_BUILTIN_BSWAP32, tok, rest);
  }

  if (equal(tok, "__builtin_bswap64")) {
      return ParseBuiltin(ND_BUILTIN_BSWAP64, tok, rest);
  }

  if (equal(tok, "__builtin_popcount")) {
      Node *node = ParseBuiltin(ND_POPCOUNT, tok, rest);
      node->builtin_val = new_cast(node->builtin_val, ty_uint);
      return node;
  }

  if (equal(tok, "__builtin_popcountl")) {
      Node *node = ParseBuiltin(ND_POPCOUNTL, tok, rest);
      node->builtin_val = new_cast(node->builtin_val, ty_ulong);
      add_type(node);
      add_type(node->builtin_val);
      return node;
  }

  if (equal(tok, "__builtin_popcountll")) {
      Node *node = ParseBuiltin(ND_POPCOUNTLL, tok, rest);
      node->builtin_val = new_cast(node->builtin_val, ty_ullong);
      add_type(node);
      add_type(node->builtin_val);      
      return node;
  }


  if (equal(tok, "__builtin_isunordered")) {
    Node *node = new_node(ND_ISUNORDERED, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); 
    add_type(node->lhs);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->rhs = assign(&tok, tok); 
    add_type(node->rhs);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;
  }

  if (equal(tok, "__builtin_signbit")) {
    Node *node = new_node(ND_SIGNBIT, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); 
    add_type(node->lhs);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;
  }

  if (equal(tok, "__builtin_signbitf")) {
    Node *node = new_node(ND_SIGNBITF, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); 
    add_type(node->lhs);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;
  }

  if (equal(tok, "__builtin_signbitl")) {
    Node *node = new_node(ND_SIGNBITL, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); 
    add_type(node->lhs);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;
  }

  if (equal(tok, "__builtin_expect")) {
    Node *node = new_node(ND_EXPECT, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); 
    add_type(node->lhs);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->rhs = assign(&tok, tok); 
    add_type(node->rhs);
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;
  }

  if (equal(tok, "__builtin_assume_aligned")) {
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);

    Node *node = assign(&tok, tok);
    add_type(node);

    SET_CTX(ctx);
    tok = skip(tok, ",", ctx);
    assign(&tok, tok);

    if (consume(&tok, tok, ",")) {
      assign(&tok, tok);
    }

    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_abort")) {
      Node *node = new_node(ND_ABORT, tok); 
      SET_CTX(ctx); 
      tok = skip(tok->next, "(", ctx);  
      SET_CTX(ctx);   
      *rest = skip(tok, ")", ctx);
      return node; 
  }


  if (equal(tok, "__builtin_return_address")) {
    if (current_fn)
      current_fn->force_frame_pointer = true;
    Node *node = new_node(ND_RETURN_ADDR, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); 
    add_type(node->lhs);

    if (opt_omit_frame_pointer && is_const_expr(node->lhs) && eval(node->lhs) > 0) {
      opt_omit_frame_pointer = false;
    }

    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_frame_address"))
  {
    if (current_fn)
      current_fn->force_frame_pointer = true;
    Node *node = new_node(ND_BUILTIN_FRAME_ADDRESS, tok);
    add_type(node);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok);
    add_type(node->lhs);

    if (opt_omit_frame_pointer && (!is_const_expr(node->lhs) || eval(node->lhs) > 0)) {
      opt_omit_frame_pointer = false;
    }

    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
  }

  if (equal(tok, "__builtin_add_overflow")) {
    return parse_overflow(ND_BUILTIN_ADD_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_uadd_overflow")) {
    return parse_overflow(ND_UADD_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_uaddll_overflow")) {
    return parse_overflow(ND_UADDLL_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_uaddl_overflow")) {
    return parse_overflow(ND_UADDL_OVERFLOW, tok, rest);
  }
  if (equal(tok, "__builtin_umul_overflow")) {
    return parse_overflow(ND_UMUL_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_umulll_overflow")) {
    return parse_overflow(ND_UMULLL_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_umull_overflow")) {
    return parse_overflow(ND_UMULL_OVERFLOW, tok, rest);
  }



  if (equal(tok, "__builtin_sub_overflow")) {
    return parse_overflow(ND_BUILTIN_SUB_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_mul_overflow")) {
    return parse_overflow(ND_BUILTIN_MUL_OVERFLOW, tok, rest);
  }

  if (equal(tok, "__builtin_unreachable")) {
    Node *node = new_node(ND_UNREACHABLE, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    SET_CTX(ctx);     
    *rest = skip(tok, ")", ctx);
    return node;
  }


  if (equal(tok, "__builtin_atomic_exchange_n") || equal(tok, "__atomic_exchange_n")) {
    return ParseAtomic3(ND_EXCH_N, tok, rest);
  }

  if (equal(tok, "__builtin_atomic_compare_exchange") || equal(tok, "__atomic_compare_exchange")) {
    return ParseAtomicCompareExchangeN(ND_CMPEXCH, tok, rest);
  }


  if (equal(tok, "__builtin_atomic_compare_exchange_n") || equal(tok, "__atomic_compare_exchange_n")) {
    return ParseAtomicCompareExchangeN(ND_CMPEXCH_N, tok, rest);
  }

  if (equal(tok, "__builtin_atomic_load") || equal(tok, "__atomic_load")) {
    return ParseAtomic3(ND_LOAD, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_store") || equal(tok, "__atomic_store")) {
    return ParseAtomic3(ND_STORE, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_load_n") || equal(tok, "__atomic_load_n")) {
    return ParseAtomic2(ND_LOAD_N, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_store_n") || equal(tok, "__atomic_store_n")) {
    return ParseAtomic3(ND_STORE_N, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_fetch_add")) {
    return ParseAtomicFetch(ND_FETCHADD, tok, rest);
  }
  if (equal(tok, "__atomic_fetch_add")) {
    return ParseAtomic3(ND_FETCHADD, tok, rest);
  }
  if (equal(tok, "__atomic_add_fetch")) {
    return ParseAtomic3(ND_ADDFETCH, tok, rest);
  }
  if (equal(tok, "__atomic_fetch_sub")) {
    return ParseAtomic3(ND_FETCHSUB, tok, rest);
  }  
  if (equal(tok, "__atomic_sub_fetch")) {
    return ParseAtomic3(ND_SUBFETCH, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_fetch_sub")) {
    return ParseAtomicFetch(ND_FETCHSUB, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_fetch_xor")) {
    return ParseAtomicFetch(ND_FETCHXOR, tok, rest);
  }
  if (equal(tok, "__atomic_fetch_xor")) {
    return ParseAtomic3(ND_FETCHXOR, tok, rest);
  }  
  if (equal(tok, "__atomic_xor_fetch")) {
    return ParseAtomic3(ND_XORFETCH, tok, rest);
  }
  if (equal(tok, "__builtin_atomic_fetch_and")) {
    return ParseAtomicFetch(ND_FETCHAND, tok, rest);
  }
  if (equal(tok, "__atomic_fetch_and")) {
    return ParseAtomic3(ND_FETCHAND, tok, rest);
  }  
  if (equal(tok, "__atomic_and_fetch")) {
    return ParseAtomic3(ND_ANDFETCH, tok, rest);
  }    
  if (equal(tok, "__builtin_atomic_fetch_or")) {
    return ParseAtomicFetch(ND_FETCHOR, tok, rest);
  }
  if (equal(tok, "__atomic_fetch_or")) {
    return ParseAtomic3(ND_FETCHOR, tok, rest);
  }  
  if (equal(tok, "__atomic_or_fetch")) {
    return ParseAtomic3(ND_ORFETCH, tok, rest);
  }    
  if (equal(tok, "__builtin_atomic_test_and_set")) {
    return ParseAtomic2(ND_TESTANDSETA, tok, rest);
  }

  if (equal(tok, "__atomic_test_and_set")) {
    return ParseAtomic2(ND_TESTANDSETA, tok, rest);
  }

  if (equal(tok, "__atomic_clear")) {
    return ParseAtomicClear(ND_CLEAR, tok, rest);
  }

  if (equal(tok, "__sync_add_and_fetch")) {
      return ParseAtomic3(ND_ADD_AND_FETCH, tok, rest);
  }

  if (equal(tok, "__sync_sub_and_fetch")) {
      return ParseAtomic3(ND_SUB_AND_FETCH, tok, rest);
  }
  if (equal(tok, "__sync_bool_compare_and_swap")) {
      return ParseSyncBoolCAS(ND_BOOL_CAS, tok, rest);
  }

  if (equal(tok, "__builtin_atomic_fetch_nand") || equal(tok, "__atomic_fetch_nand"))
    return ParseAtomicBitwise(ND_FETCHNAND, tok, rest);

  if (equal(tok, "__atomic_nand_fetch"))
    return ParseAtomicBitwise(ND_NANDFETCH, tok, rest);

  if (equal(tok, "__builtin_atomic_clear")) {
    return ParseAtomic2(ND_CLEAR, tok, rest);
  }

  if (equal(tok, "__atomic_thread_fence")) {
    return ParseAtomicFence(ND_MEMBARRIER, tok, rest);
  }

  if (equal(tok, "__atomic_signal_fence")) {
    return ParseAtomicFence(ND_MEMBARRIER, tok, rest);
  }

  if (equal(tok, "__sync_lock_test_and_set")) {
    Node *node = new_node(ND_TESTANDSET, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next,  "(", ctx);
    node->lhs = assign(&tok, tok);
    add_type(node->lhs);
    node->ty = node->lhs->ty->base;
    SET_CTX(ctx); 
    tok = skip(tok,  ",", ctx);
    node->rhs = assign(&tok, tok);
    add_type(node->rhs);
    SET_CTX(ctx);     
    *rest = skip(tok,  ")", ctx);
    return node;
  }
  if (equal(tok, "__sync_lock_release")) {
    Node *node = new_node(ND_RELEASE, tok);
    SET_CTX(ctx);     
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok);
    add_type(node->lhs);
    node->ty = node->lhs->ty->base;
    SET_CTX(ctx);      
    *rest = skip(tok, ")", ctx);
    return node;
  }


  if (equal(tok, "__sync_fetch_and_add"))
      return ParseSyncFetch(ND_FETCHADD, tok, rest);

  if (equal(tok, "__sync_add_and_fetch"))
      return ParseSyncFetch(ND_ADDFETCH, tok, rest);

  if (equal(tok, "__sync_fetch_and_sub"))
      return ParseSyncFetch(ND_FETCHSUB, tok, rest);

  if (equal(tok, "__sync_sub_and_fetch"))
      return ParseSyncFetch(ND_SUBFETCH, tok, rest);

  if (equal(tok, "__sync_fetch_and_or"))
      return ParseSyncFetch(ND_FETCHOR, tok, rest);

  if (equal(tok, "__sync_or_and_fetch"))
    return ParseSyncFetch(ND_ORFETCH, tok, rest);

  if (equal(tok, "__sync_fetch_and_and"))
      return ParseSyncFetch(ND_FETCHAND, tok, rest);

  if (equal(tok, "__sync_and_and_fetch"))
    return ParseSyncFetch(ND_ANDFETCH, tok, rest);
    
  if (equal(tok, "__sync_fetch_and_xor"))
      return ParseSyncFetch(ND_FETCHXOR, tok, rest);

  if (equal(tok, "__sync_xor_and_fetch"))
    return ParseSyncFetch(ND_XORFETCH, tok, rest);    

  if (equal(tok, "__sync_fetch_and_nand"))
      return ParseSyncFetch(ND_FETCHNAND, tok, rest);

  if (equal(tok, "__sync_nand_and_fetch"))
    return ParseSyncFetch(ND_NANDFETCH, tok, rest);       

  if (equal(tok, "__builtin_atomic_fetch_op"))
  {
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    Node *obj = new_unary(ND_DEREF, assign(&tok, tok), tok);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    Node *val = assign(&tok, tok);
    add_type(val);    
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    Node *node;
    if (equal(tok, "0"))
      node = new_add(obj, val, tok, false);
    else if (equal(tok, "1"))
      node = new_sub(obj, val, tok, false);
    else if (equal(tok, "2"))
      node = new_binary(ND_BITOR, obj, val, tok);
    else if (equal(tok, "3"))
      node = new_binary(ND_BITXOR, obj, val, tok);
    else if (equal(tok, "4"))
      node = new_binary(ND_BITAND, obj, val, tok);
    else
      error_tok(tok, "%s:%d: in primary : invalid fetch operator", __FILE__, __LINE__);

    node->atomic_fetch = true;
    SET_CTX(ctx);     
    *rest = skip(tok->next, ")", ctx);
    return to_assign(node);
  }

  // Handle __builtin_huge_valf
  if (equal(tok, "__builtin_huge_valf")) {
    return parse_huge_val(HUGE_VALF, tok, rest);
  }
  // Handle __builtin_huge_vall
  if (equal(tok, "__builtin_huge_vall")) {
    return parse_huge_val(HUGE_VALL, tok, rest);
  }
  // Handle __builtin_huge_val
  if (equal(tok, "__builtin_huge_val")) {
    return parse_huge_val(HUGE_VAL, tok, rest);
  }


  if (tok->kind == TK_IDENT)
  {
    //  Variable or enum constant
    VarScope *sc = find_var(tok);
    *rest = tok->next;


    // For "static inline" function
    if (sc && sc->var && sc->var->is_function)
    {
      if (current_fn)
        strarray_push(&current_fn->refs, sc->var->name);
      else  {
        sc->var->is_root = true;
      }
      if (sc->var->is_address_used) {
        sc->var->is_root = true;
      }

      char *name = sc->var->name;
     
      if (is_returned_twice(name)) {
        dont_reuse_stack = true;
        if (current_fn)
          current_fn->force_frame_pointer = true;
      }
    
    }

    if (sc)
    {
      
      if (sc->var)
        return new_var_node(sc->var, tok);
      if (sc->enum_ty)
        return new_num(sc->enum_val, tok);
    }

    if (equal(tok->next, "("))
    {
      Obj *fn = find_func(token_to_string(tok));

      if (!fn && (is_c99_or_later() || opt_implicit)) {
        error_tok(tok, "%s:%d: in primary : implicit declaration of function", __FILE__, __LINE__);
      }    

      if (!fn) {
        warn_tok(tok, "%s:%d: in primary : implicit declaration of function", __FILE__, __LINE__);
        Type *ty = func_type(ty_int);        
        ty->is_variadic = true;
        fn = new_gvar(token_to_string(tok), ty);
        fn->name = token_to_string(tok);
        fn->is_function = true;
        fn->is_definition = false;
        fn->is_tentative = true;
        fn->is_static = false;
        fn->is_extern = true;
      }
      // Node *node = unary(rest, tok->next);      
      // return node;
      *rest = tok->next;
      return new_var_node(fn, tok);      
    }

    //printf("=======%s:%d\n", tok->loc, __LINE__);
    error_tok(tok, "%s:%d: in primary : error: undefined variable %.*s", __FILE__, __LINE__, tok->len, tok->loc);
  }

  if (tok->kind == TK_STR)
  {
    Type *ty = copy_type(tok->ty);
    ty->is_const = true;
    Obj *var = new_string_literal(tok->str, ty);
    *rest = tok->next;
    return new_var_node(var, tok);
  }

  if (equal(tok, "false")) {
    *rest = tok->next;
    return new_boolean(0, tok);
  }

  if (equal(tok, "true")) {
    *rest = tok->next;
    return new_boolean(1, tok);
  }

  if (tok->kind == TK_NUM)
  {
    Node *node;
    if (is_flonum(tok->ty))
    {
      node = new_node(ND_NUM, tok);          
      node->fval = tok->fval;
    }
    else
    {
      node = new_num(tok->val, tok);
    }

    node->ty = tok->ty;    
    *rest = tok->next;
    return node;
  }

  error_tok(tok, "%s:%d: in primary : expected an expression %s", __FILE__, __LINE__, tok->loc);
}

static Node *parse_typedef(Token **rest, Token *tok, Type *basety, VarAttr *attr) 
{
  bool first = true;    
  Node *node = new_node(ND_NULL_EXPR, tok);
  while (!consume(rest, tok, ";"))
  {
    if (!first) {
      SET_CTX(ctx);        
      tok = skip(tok, ",", ctx);
    }
    first = false;

    Type *ty = declarator(&tok, tok, basety);
    if (!ty)
      error_tok(tok, "%s:%d: in parse_typedef : ty is null", __FILE__, __LINE__);
    if (!ty->name)
      error_tok(ty->name_pos, "%s:%d: in parse_typedef : typedef name omitted", __FILE__, __LINE__);
    //from COSMOPOLITAN adding other GNUC attributes
    tok = attribute_list(tok, ty, type_attributes);      
    if (attr && attr->align) {
      ty->is_aligned = true;
      ty->align = MAX(ty->align, attr->align);
    }
    if (ty->is_vector  && !is_vector(ty)) {
      int len = ty->vector_size / ty->size;
      Token *name = ty->name;
      ty = vector_of(ty, len);
      ty->name = name;
    }
    record_debug_typedef(ty->name, ty);
    push_scope(get_ident(ty->name))->type_def = ty;    
    node = new_binary(ND_COMMA, node, compute_vla_size(ty, tok), tok);
  }
  
  return node;
}

static void create_param_lvars(Type *param, char *funcname)
{
  if (!param) return;
 // from @fuhsnn Adjust ABI with unnamed function parameter #2 
    create_param_lvars(param->next, funcname);
  //if (!param->name)
  //  return;
  // error_tok(param->name_pos, "parameter name omitted");
  //new_lvar(get_ident(param->name), param, funcname);
    if (param->param_var) {
      param->param_var->next = locals;
      locals = param->param_var;
      param->param_var->funcname = funcname;
      param->param_var->order = order;
      if (param->name)
        push_scope(get_ident(param->name))->var = param->param_var;
    } else {
    if (!param->name)
      new_lvar("", param, funcname);
    else
    new_lvar(get_ident(param->name), param, funcname);
    }
    order++;

}


// This function matches gotos or labels-as-values with labels.
//
// We cannot resolve gotos as we parse a function because gotos
// can refer a label that appears later in the function.
// So, we need to do this after we parse the entire function.
static void resolve_goto_labels(void)
{
  for (Node *x = gotos; x; x = x->goto_next)
  {
    for (Node *y = labels; y; y = y->goto_next)
    {
      if (!strcmp(x->label, y->label))
      {
        x->unique_label = y->unique_label;
        break;
      }
    }

    if (x->unique_label == NULL)
      error_tok(x->tok->next, "%s:%d: in resolve_goto_labels : use of undeclared label", __FILE__, __LINE__);
  }

  gotos = labels = NULL;
}

Obj *find_func(char *name)
{
  Scope *sc = scope;
  while (sc->next)
    sc = sc->next;

  VarScope *sc2 = hashmap_get(&sc->vars, name);
  if (sc2 && sc2->var && sc2->var->is_function)
    return sc2->var;
  return NULL;
}

static void mark_live(Obj *var)
{
  if (!var->is_function || var->is_live)
    return;

  var->is_live = true;

  for (int i = 0; i < var->refs.len; i++)
  {
    Obj *fn = find_func(var->refs.data[i]);
    if (fn)
      mark_live(fn);
  }
}

//implementing tail call optimization. Marking tails calls.
static void mark_tail_calls(Node *node) {
  if (!node)
    return;

  switch (node->kind) {
  case ND_BLOCK:
    if (!node->body)
      return;
    Node *last = node->body;
    while (last->next)
      last = last->next;
    mark_tail_calls(last);
    break;
  case ND_IF:
    mark_tail_calls(node->then);
    mark_tail_calls(node->els);
    break;
  case ND_RETURN:
    mark_tail_calls(node->lhs);
    break;
  case ND_EXPR_STMT:
    mark_tail_calls(node->lhs);
    break;
  case ND_CAST:
    mark_tail_calls(node->lhs);
    break;
  case ND_COMMA:
    mark_tail_calls(node->rhs);
    break;
  case ND_FUNCALL:
    node->is_tail = true;
    break;
  }
}

static Token *function(Token *tok, Type *basety, VarAttr *attr)
{

  Type *ty = declarator(&tok, tok, basety);
  
  tok = attribute_list(tok, attr, thing_attributes); 
  if (!ty)
    error_tok(tok, "%s:%d: in function : ty is null", __FILE__, __LINE__);
  if (!ty->name)
    error_tok(ty->name_pos, "%s:%d: in function : function name omitted", __FILE__, __LINE__);  

  char *name_str = get_ident(ty->name);

  Obj *fn = find_func(name_str);
  if (fn)
  {
    // Redeclaration
    if (!fn->is_function)
      error_tok(tok, "%s:%d: in function : redeclared as a different kind of symbol", __FILE__, __LINE__);
    if (fn->is_definition && equal(tok, "{"))
      error_tok(tok, "%s:%d: in function : redefinition of %s", __FILE__, __LINE__, name_str);
    if (!fn->is_static && attr->is_static)
      error_tok(tok, "%s:%d: in function : static declaration follows a non-static declaration", __FILE__, __LINE__);
    fn->is_definition = fn->is_definition || equal(tok, "{");
  }
  else
  {
    fn = new_gvar(name_str, ty);
    fn->funcname = name_str;
    fn->is_function = true;
    fn->is_definition = equal(tok, "{");
    fn->is_static = attr->is_static || (attr->is_inline && !attr->is_extern);
    fn->is_inline = attr->is_inline;
    
  }
  //from COSMOPOLITAN adding other GNUC attributes
  fn->alias_name = attr->alias_name;
  fn->is_extern |= attr->is_extern;
  fn->is_weak |= attr->is_weak;
  fn->section = attr->section;
  fn->is_ms_abi |= attr->is_ms_abi;
  fn->visibility = fn->visibility ?: attr->visibility;
  fn->is_aligned |= attr->is_aligned;
  fn->is_noreturn |= attr->is_noreturn;
  fn->is_destructor |= attr->is_destructor;
  fn->is_constructor |=  attr->is_constructor;
  if (attr->destructor_priority > 0)
    fn->destructor_priority = attr->destructor_priority;
  if (attr->constructor_priority > 0)
    fn->constructor_priority = attr->constructor_priority;
  fn->is_externally_visible |= attr->is_externally_visible;
  fn->is_no_instrument_function |= attr->is_no_instrument_function;
  fn->is_force_align_arg_pointer |= attr->is_force_align_arg_pointer;
  fn->is_no_caller_saved_registers |= attr->is_no_caller_saved_registers;
  fn->file_no = tok->file->file_no;
  fn->line_no = tok->line_no; 

  fn->is_root = !(fn->is_static && fn->is_inline);

   if (consume(&tok, tok, "asm") || consume(&tok, tok, "__asm__") || consume(&tok, tok, "__asm")) {
    SET_CTX(ctx); 
    tok = skip(tok, "(", ctx);
    fn->asmname = ConsumeStringLiteral(&tok, tok);
    SET_CTX(ctx); 
    tok = skip(tok, ")", ctx);
  }
 //from COSMOPOLITAN adding other GNUC attributes
  tok = attribute_list(tok, attr, thing_attributes);
  if (consume(&tok, tok, ";") || consume(&tok, tok, ","))
    return tok;

  current_fn = fn;
  locals = NULL;
  enter_scope();

  // if it's a pointer we don't know the size of the type of pointer int ? char ?
  create_param_lvars(ty->params, name_str);
  if (is_old_style) {
    int n = ArrayTokenOrderCount[nbFunc];
    for (int i = 0; i < n; i++) {
      Token *name = ArrayTokenOrder[nbFunc][i];
      VarScope *sc = name ? find_var(name) : NULL;
      if (!sc || !sc->var) {
        Type *t = copy_type(ty_int);
        t->name = name;
        new_lvar(get_ident(name), t, name_str);
        order++;
      }
    }
  }
  // store the number of function parameters to be used for extended assembly
  fn->nbparm = order;
  // A buffer for a struct/union return value is passed
  // as the hidden first parameter.
  Type *rty = ty->return_ty;
  if ((rty->kind == TY_STRUCT || rty->kind == TY_UNION) && rty->size > 16)
    new_lvar("", pointer_to(rty), name_str);

  fn->params = locals;
  //to fix issue with complex vla in parameters
  Node vla_head = {};
  Node *vla_cur = &vla_head;
  for (Type *t = ty->params; t; t = t->next) {
    Node *comp = compute_vla_size(t, t->name_pos ? t->name_pos : tok);
    if (comp->kind != ND_NULL_EXPR)
      vla_cur = vla_cur->next = new_unary(ND_EXPR_STMT, comp, t->name_pos ? t->name_pos : tok);
  }


  if (ty->is_variadic)
    fn->va_area = new_lvar("__va_area__", array_of(ty_char, 200), name_str);
  

  //from COSMOPOLITAN adding other GNUC attributes
  tok = attribute_list(tok, ty, type_attributes);
  if (consume(&tok, tok, ";")  || consume(&tok, tok, ","))
    return tok;


  SET_CTX(ctx);    
  tok = skip(tok, "{", ctx);
  is_old_style = false;
  // [https://www.sigbus.info/n1570#6.4.2.2p1] "__func__" is
  // automatically defined as a local variable containing the
  // current function name.
  
  //tok = attribute_list(tok, ty, type_attributes);
  push_scope("__func__")->var =
      new_string_literal(fn->name, array_of(ty_char, strlen(fn->name) + 1));

  //in assert.h __PRETTY_FUNCTION__ is an alias for __func__ for the current function
  push_scope("__PRETTY_FUNCTION__")->var =
      new_string_literal(fn->name, array_of(ty_char, strlen(fn->name) + 1));


  // [GNU] __FUNCTION__ is yet another name of __func__.
  push_scope("__FUNCTION__")->var =
      new_string_literal(fn->name, array_of(ty_char, strlen(fn->name) + 1));
  
  fn->body = compound_stmt(&tok, tok, NULL);

  if (vla_head.next) {
    vla_cur->next = fn->body->body;
    fn->body->body = vla_head.next;
  }

  //implementing tail call optimization.
  mark_tail_calls(fn->body);
  fn->locals = locals;  
  order = 0;
  leave_scope();
  resolve_goto_labels();
  return tok;
}


static Token *global_declaration(Token *tok, Type *basety, VarAttr *attr)
{
  bool first = true;
  

  while (!consume(&tok, tok, ";"))
  {

    if (!first) {
      SET_CTX(ctx);         
      tok = skip(tok, ",", ctx);
    }
    first = false;
    Type *ty = declarator(&tok, tok, basety);
    if (!ty)
      error_tok(tok, "%s:%d: in global_declaration : ty is null", __FILE__, __LINE__);    
    if (!ty->name)
      error_tok(ty->name_pos, "%s:%d: in global_declaration : variable name omitted", __FILE__, __LINE__);
    if (ty->name) {
      VarScope *sc = find_var(ty->name);
      if (sc && sc->var) {
        if (sc->var->is_definition && !sc->var->is_tentative && !sc->var->is_extern && equal(tok, "=") )
          error_tok(ty->name, "%s:%d: in global_declaration : redefinition of the variable %s", __FILE__, __LINE__, token_to_string(ty->name));        
      }
    
  }
    
    Obj *var = new_gvar(get_ident(ty->name), ty);
    
    
    //from COSMOPOLITAN adding other GNUC attributes
    VarAttr decl_attr = attr ? *attr : (VarAttr){};
    while (true) {
      if (consume(&tok, tok, "asm") || consume(&tok, tok, "__asm__") || consume(&tok, tok, "__asm")) {
        SET_CTX(ctx);
        tok = skip(tok, "(", ctx);
        var->asmname = ConsumeStringLiteral(&tok, tok);
        SET_CTX(ctx);
        tok = skip(tok, ")", ctx);
        continue;
      }

      Token *old2 = tok;
      tok = attribute_list(tok, &decl_attr, thing_attributes);
      if (tok != old2)
        continue;
      break;
    }

    var->is_weak = decl_attr.is_weak;
    var->alias_name = decl_attr.alias_name;
    var->section = decl_attr.section; 
    if (!decl_attr.section && current_section) {
      var->section = current_section;
    } 
    var->visibility = decl_attr.visibility;
    var->is_aligned = var->is_aligned | decl_attr.is_aligned;
    var->is_externally_visible = decl_attr.is_externally_visible;
    var->is_definition = !decl_attr.is_extern;
    var->is_static = decl_attr.is_static;
    var->is_tls = decl_attr.is_tls;
    if (decl_attr.align)
      var->align = MAX(var->align, decl_attr.align);

    if (equal(tok, "="))
      gvar_initializer(&tok, tok->next, var);
    else if (!decl_attr.is_extern)
      var->is_tentative = true;
     
    current_section=NULL;
  }
  return tok;
}


// Lookahead tokens and returns true if a given token is a start
// of a function definition or declaration.
static bool is_function(Token *tok)
{

  if (equal(tok, ";"))
    return false;
  Type dummy = {};
  Type *ty = declarator(&tok, tok, &dummy);
  if (!ty)
    error_tok(tok, "%s %d: in is_function : ty is null", __FILE__, __LINE__);

  return ty->kind == TY_FUNC;
}


static bool var_in_array(const char *str, Obj *varArr[], size_t count) {
    for (size_t i = 0; i < count ; i++) {
        if (varArr[i] && varArr[i]->name && strcmp(str, varArr[i]->name) == 0) {
            return true; 
        }
    }
    return false;  
}


// Remove redundant tentative definitions.
// works fine when we have tentative and definition but didn't work when we have multiple tentatives.
// that's why here we're doing two passes and managed the case of duplicate tentatives.
static void scan_globals(void)
{
  Obj head;
  Obj *cur = &head;
  Obj *varArr[MAX_GLOBAL_VAR];  
  int i = 0;
  //the first pass skipped the duplicated tentative and stores in an Array of objects duplicated tentative
  for (Obj *var = globals; var; var = var->next)
  {
    if (!var->is_tentative)
    {
      cur = cur->next = var;
      continue;
    }

    // Find another definition of the same identifier.
    Obj *var2 = globals;
    
    for (; var2; var2 = var2->next) {
      if (var != var2 && var2->is_definition && !strcmp(var->name, var2->name)) {
        //warn_tok(var->tok, "%s:%d: in scan_globals : duplicated tentative definition", __FILE__, __LINE__);  
        if (var2->is_tentative && !var_in_array(var->name, varArr, i + 1 ) && (i + 1) < MAX_GLOBAL_VAR) {
          varArr[i++] = var;                
        }
        break;
      }
    }

    // If there's another definition, the tentative definition
    // is redundant
    if (!var2)
      cur = cur->next = var;
  }
  cur->next = NULL;
  globals = head.next;
}


static char *prefix_builtin(const char *name) {
    const char *prefix = "__builtin_";
    size_t len = strlen(prefix) + strlen(name) + 1;
    char *buf = malloc(len);
    if (!buf) return NULL; 
    strcpy(buf, prefix);
    strcat(buf, name);
    return buf;
}

// static Obj *declare0(char *name, Type *ret) {
//   if (!opt_fbuiltin) new_gvar(name, func_type(ret));
//   return new_gvar(prefix_builtin(name), func_type(ret));
// }

// static Obj *declare1(char *name, Type *ret, Type *p1) {
//   Type *ty = func_type(ret);
//   ty->params = copy_type(p1);
//   if (!opt_fbuiltin) new_gvar(name, ty);
//   return new_gvar(prefix_builtin(name), ty);
// }

// static Obj *declare2(char *name, Type *ret, Type *p1, Type *p2) {
//   Type *ty = func_type(ret);
//   ty->params = copy_type(p1);
//   ty->params->next = copy_type(p2);
//   if (!opt_fbuiltin) new_gvar(name, ty);
//   return new_gvar(prefix_builtin(name), ty);
// }

static Obj *declare3(char *s, Type *r, Type *a, Type *b, Type *c) {
  Type *ty = func_type(r);
  ty->params = copy_type(a);
  ty->params->next = copy_type(b);
  ty->params->next->next = copy_type(c);
  if (!opt_fbuiltin) new_gvar(s, ty);
  return new_gvar(prefix_builtin(s), ty);
}


static void declare_builtin_functions(void)
{
  Type *ty = func_type(pointer_to(ty_void));
  ty->params = copy_type(ty_int);
  builtin_alloca = new_gvar("alloca", ty);
  builtin_alloca->is_definition = false;
  Obj *builtin = new_gvar("__builtin_alloca", ty);
  builtin->is_definition = false;
  Type *pvoid = pointer_to(ty_void);
  //Type *pchar = pointer_to(ty_char);
  declare3("memcpy", pvoid, pvoid, pvoid, ty_ulong);
  declare3("memset", pvoid, pvoid, ty_int, ty_ulong);
}

// program = (typedef | function-definition | global-variable)*
Obj *parse(Token *tok)
{
  char *path;
  char *fullpath = calloc(1, sizeof(char) * 400);;
  //char *filename;
  if (isDotfile && dotf == NULL)
  {
    if (base_file == NULL && opt_o == NULL)
    {
      fprintf(stderr, "%s: in parse base_file and opt_o are null!\n", __FILE__);
      exit(1);
    }
    path = replace_extn(opt_o ? opt_o : base_file, ".dot");
    if (opt_o != NULL)
    {

      //filename = extract_filename(opt_o);
      fullpath = extract_path(opt_o);
      strncat(fullpath, path, strlen(path));
    }
    //printf("%s %s %s\n", fullpath, filename, path);
    dotf = fopen(fullpath, "w");
    if (dotf == NULL)
    {
      fprintf(stderr, "%s: in parse dot file cannot be opend\n", __FILE__);
      exit(1);
    } 
    fprintf(dotf, "digraph A { \n");
    
  }

  if (opt_fbuiltin)
    declare_builtin_functions();


  globals = NULL;

  while (tok->kind != TK_EOF)
  {
    current_fn = NULL;
    locals = NULL;
    if (equal(tok, "_Static_assert")) {
      tok = static_assertion(tok);
      continue;
    }
    //fixing ISS-192 found during php-src compile
    if (equal(tok, "asm") || equal(tok, "__asm__") || equal(tok, "__asm")) {
      Node *node = asm_stmt(&tok, tok);
      add_type(node);
      continue;
    }


    VarAttr attr = {};
    //from COSMOPOLITAN adding other GNUC attributes
    tok = attribute_list(tok, &attr, thing_attributes);
    Type *basety = declspec(&tok, tok, &attr);
    tok = attribute_list(tok, &attr, thing_attributes);

    // Typedef
    if (attr.is_typedef)
    {
      parse_typedef(&tok, tok, basety, &attr);
      continue;
    }

    // Function
    if (is_function(tok))
    {
      if (check_old_style(&tok, tok)) {
        is_old_style = true;
        tok = function(tok, basety, &attr);
        continue;        
     }
      is_old_style = false;
      tok = function(tok, basety, &attr);
      continue;
    }
    // Global variable
    tok = global_declaration(tok, basety, &attr);
  }

  for (Obj *var = globals; var; var = var->next)
    if (var->is_root || var->is_address_used)
      mark_live(var);

  // Remove redundant tentative definitions.
  scan_globals();

  return globals;
}

// for dot diagram
char *nodekind2str(NodeKind kind)
{
  switch (kind)
  {
  case ND_NULL_EXPR: return "NULL_EXPR";
  case ND_ADD: return "ADD";
  case ND_SUB: return "SUB";
  case ND_MUL: return "MUL";
  case ND_DIV: return "DIV";
  case ND_POS: return "POS";
  case ND_NEG: return "NEG";
  case ND_MOD: return "MOD";
  case ND_BITAND: return "BITAND";
  case ND_BITOR: return "BITOR";
  case ND_BITXOR: return "BITXOR";
  case ND_SHL: return "SHL";
  case ND_SHR: return "SHR";
  case ND_EQ: return "EQ";
  case ND_NE: return "NE";
  case ND_LT: return "LT";
  case ND_LE: return "LE";
  case ND_ASSIGN: return "ASSIGN";
  case ND_COND: return "COND"; 
  case ND_COMMA: return "COMMA";
  case ND_MEMBER: return "MEMBER"; 
  case ND_ADDR: return "ADDR";
  case ND_DEREF: return "DEREF";
  case ND_NOT: return "NOT";
  case ND_BITNOT: return "BITNOT"; 
  case ND_LOGAND: return "LOGAND"; 
  case ND_LOGOR: return "LOGOR"; 
  case ND_RETURN: return "RETURN";
  case ND_IF: return "IF";
  case ND_FOR: return "FOR"; 
  case ND_DO: return "DO"; 
  case ND_SWITCH: return "SWITCH"; 
  case ND_CASE: return "CASE"; 
  case ND_BLOCK: return "BLOCK"; 
  case ND_GOTO: return "GOTO"; 
  case ND_GOTO_EXPR: return "GOTO_EXPR"; 
  case ND_LABEL: return "LABEL"; 
  case ND_LABEL_VAL: return "LABEL_VAL";
  case ND_FUNCALL: return "FUNCALL";
  case ND_EXPR_STMT: return "EXPRSTMR";
  case ND_STMT_EXPR: return "STMTEXPR"; 
  case ND_VAR: return "VAR"; 
  case ND_VLA_PTR: return "VLAPTR"; 
  case ND_NUM: return "NUM";
  case ND_CAST: return "CAST";
  case ND_MEMZERO: return "MEMZERO"; 
  case ND_ASM: return "ASM";
  case ND_CAS: return "CAS";
  case ND_CAS_N: return "CAS_N";
  case ND_EXCH: return "EXCHANGE";
  case ND_EXCH_N: return "EXCHANGE_N";
  case ND_CMPEXCH: return "COMPARE_EXCHANGE";
  case ND_CMPEXCH_N: return "COMPARE_EXCHANGE_N";
  case ND_LOAD: return "LOAD";
  case ND_LOAD_N: return "LOAD_N";
  case ND_STORE: return "STORE"; 
  case ND_STORE_N: return "STORE_N"; 
  case ND_TESTANDSET: return "TESTANDSET";
  case ND_TESTANDSETA: return "TESTANDSETA";
  case ND_CLEAR: return "CLEAR"; 
  case ND_RELEASE: return "RELEASE"; 
  case ND_FETCHADD: return "FETCHADD";
  case ND_FETCHSUB: return "FETCHSUB";
  case ND_FETCHXOR: return "FETCHXOR";
  case ND_FETCHAND: return "FETCHAND";    
  case ND_FETCHOR: return "FETCHOR";
  case ND_SUBFETCH: return "SUBFETCH";
  case ND_SYNC: return "SYNC";   
  case ND_MEMBARRIER: return "MEMBARRIER"; 
  case ND_BUILTIN_MEMCPY: return "MEMCPY";  
  case ND_BUILTIN_MEMSET: return "MEMSET";  
  case ND_BUILTIN_CLZ: return "CLZ";   
  case ND_BUILTIN_CLZL: return "CLZL";   
  case ND_BUILTIN_CLZLL: return "CLZLL";  
  case ND_BUILTIN_CTZ: return "CTZ";   
  case ND_BUILTIN_CTZL: return "CTZL";  
  case ND_BUILTIN_CTZLL: return "CTZLL";  
  case ND_BUILTIN_INFF: return "INFF";   
  case ND_BUILTIN_INF: return "INFF";  
  case ND_BUILTIN_NAN: return "NAN";   
  case ND_BUILTIN_NANF: return "NANF";   
  case ND_BUILTIN_NANL: return "NANL";   
  case ND_BUILTIN_ISNAN: return "ISNAN"; 
  case ND_BUILTIN_HUGE_VAL: return "ISNAN"; 
  case ND_BUILTIN_HUGE_VALF: return "ISNAN"; 
  case ND_BUILTIN_HUGE_VALL: return "ISNAN";
  case ND_POPCOUNT: return "POPCOUNT";
  case ND_POPCOUNTL: return "POPCOUNTL";
  case ND_POPCOUNTLL: return "POPCOUNTLL";
  case ND_RETURN_ADDR: return "RETURN_ADDRESS";  
  case ND_BUILTIN_FRAME_ADDRESS: return "FRAME_ADDRESS"; 
  case ND_BUILTIN_ADD_OVERFLOW: return "ADD_OVERFLOW";    
  case ND_BUILTIN_SUB_OVERFLOW: return "SUB_OVERFLOW";    
  case ND_BUILTIN_MUL_OVERFLOW: return "MUL_OVERFLOW"; 
  case ND_UADD_OVERFLOW: return "UADD_OVERFLOW";  
  case ND_UADDL_OVERFLOW: return "UADDL_OVERFLOW";    
  case ND_UADDLL_OVERFLOW: return "UADDLL_OVERFLOW";    
  case ND_UMUL_OVERFLOW: return "UMUL_OVERFLOW";  
  case ND_UMULL_OVERFLOW: return "UMULL_OVERFLOW";    
  case ND_UMULLL_OVERFLOW: return "UMULLL_OVERFLOW";      
  case ND_BUILTIN_BSWAP16:  return "BSWAP16";   
  case ND_BUILTIN_BSWAP32: return "BSWAP32";    
  case ND_BUILTIN_BSWAP64: return "BSWAP64"; 
  case ND_ALLOC: return "ALLOCA";
  case ND_ABORT: return "ABORT";
  case ND_EXPECT: return "EXPECT";
  case ND_EMMS: return "EMMS";
  case ND_LFENCE: return "LFENCE";
  case ND_MFENCE: return "MFENCE";
  case ND_SFENCE: return "SFENCE";
  case ND_PAUSE: return "PAUSE";
  case ND_STMXCSR: return "STMXCSR";
  case ND_LDMXCSR: return "LDMXCSR";    
  case ND_CVTPI2PS: return "CVTPI2PS";    
  case ND_CVTPS2PI: return "CVTPS2PI";
  case ND_CLFLUSH: return "CLFLUSH"; 
  case ND_VECINITV2SI: return "VEC_INIT_V2SI";
  case ND_VECEXTV2SI: return "VEC_EXT_V2SI";
  case ND_VECEXTV4SI: return "VEC_EXT_V4SI";
  case ND_VECINITV8QI: return "VEC_INIT_V8QI";   
  case ND_VECINITV4HI: return "VEC_INIT_V4HI";        
  case ND_PACKSSWB: return "PACKSSWB";
  case ND_PACKSSDW: return "PACKSSDW";
  case ND_PACKUSWB: return "PACKUSWB";
  case ND_PUNPCKHBW: return "PUNPCKHBW";
  case ND_PUNPCKHWD: return "PUNPCKHWD";   
  case ND_PUNPCKHDQ: return "PUNPCKHDQ";   
  case ND_PUNPCKLBW: return "PUNPCKLBW";  
  case ND_PUNPCKLWD: return "PUNPCKLWD";   
  case ND_PUNPCKLDQ: return "PUNPCKLDQ";   
  case ND_PADDB: return "PADDB";   
  case ND_PADDW: return "PADDW";  
  case ND_PADDD: return "PADDD";
  case ND_PADDQ: return "PADDQ";   
  case ND_PADDSB: return "PADDSB";  
  case ND_PADDSW: return "PADDSW";   
  case ND_PADDUSB: return "PADDUSB"; 
  case ND_PADDUSW: return "PADDUSW";   
  case ND_PSUBB: return "PSUBB";    
  case ND_PSUBW: return "PSUBW";   
  case ND_PSUBD: return "PSUBD";     
  case ND_PSUBQ: return "PSUBQ";  
  case ND_PSUBSB: return "PSUBSB";   
  case ND_PSUBSW: return "PSUBSW"; 
  case ND_PSUBUSB: return "PSUBUSB"; 
  case ND_PSUBUSW: return "PSUBUSW";     
  case ND_PMADDWD: return "PMADDWD";    
  case ND_PMULHW: return "PMULHW";   
  case ND_PMULLW: return "PMULLW";  
  case ND_PSLLW: return "PSLLW";   
  case ND_PSLLWI: return "PSLLWI"; 
  case ND_PSLLD: return "PSLLD";      
  case ND_PSLLDI: return "PSLLDI";   
  case ND_PSLLQ: return "PSLLQ";
  case ND_PSLLQI: return "PSLLQI";  
  case ND_PSRAW: return "PSRAW";   
  case ND_PSRAWI: return "PSRAWI";
  case ND_PSRAD: return "PSRAD";  
  case ND_PSRADI: return "PSRADI";
  case ND_PSRLW: return "PSRLW";      
  case ND_PSRLWI: return "PSRLWI";   
  case ND_PSRLD: return "PSRLD";      
  case ND_PSRLDI: return "PSRLDI";  
  case ND_PSRLQ: return "PSRLQ";      
  case ND_PSRLQI: return "PSRLQI"; 
  case ND_PAND: return "PAND";  
  case ND_PANDN: return "PANDN";    
  case ND_POR: return "POR";
  case ND_PXOR: return "PXOR";    
  case ND_PCMPEQB: return "PCMPEQB";     
  case ND_PCMPGTB: return "PCMPGTB";  
  case ND_PCMPEQW: return "PCMPEQW";  
  case ND_PCMPEQD: return "PCMPEQD";        
  case ND_PCMPGTW: return "PCMPGTW";  
  case ND_PCMPGTD: return "PCMPGTD";  
  case ND_ADDSS: return "ADDSS";  
  case ND_SUBSS: return "SUBSS";   
  case ND_MULSS: return "MULSS";  
  case ND_DIVSS: return "DIVSS";  
  case ND_SQRTSS: return "SQRTSS"; 
  case ND_SQRTPS: return "SQRTPS";     
  case ND_RSQRTSS: return "RSQRTSS";  
  case ND_RSQRTPS: return "RSQRTPS";         
  case ND_RCPSS: return "RCPSS"; 
  case ND_RCPPS: return "RCPPS";      
  case ND_MINSS: return "MINSS";
  case ND_MINPS: return "MINPS"; 
  case ND_MAXPS: return "MAXPS";        
  case ND_MAXSS: return "MAXSS"; 
  case ND_ANDPS: return "ANDPS";       
  case ND_ANDNPS: return "ANDNPS";   
  case ND_ORPS: return "ORPS";  
  case ND_XORPS: return "XORPS";   
  case ND_CMPEQSS: return "CMPEQSS";    
  case ND_CMPLTSS: return "CMPLTSS";  
  case ND_CMPLESS: return "CMPLESS";    
  case ND_MOVSS: return "MOVSS";   
  case ND_CMPNEQSS: return "CMPNEQSS"; 
  case ND_CMPNLTSS: return "CMPNLTSS"; 
  case ND_CMPNLESS: return "CMPNLESS"; 
  case ND_CMPORDSS: return "CMPORDSS"; 
  case ND_CMPUNORDSS: return "CMPUNORDSS";    
  case ND_CMPEQPS: return "CMPEQPS";  
  case ND_CMPLTPS: return "CMPLTPS";     
  case ND_CMPLEPS: return "CMPLEPS";  
  case ND_CMPGTPS: return "CMPGTPS";     
  case ND_CMPGEPS: return "CMPGEPS"; 
  case ND_CMPNEQPS: return "CMPNEQPS";  
  case ND_CMPNLTPS: return "CMPNLTPS";         
  case ND_CMPNLEPS: return "CMPNLEPS"; 
  case ND_CMPNGTPS: return "CMPNGTPS";     
  case ND_CMPNGEPS: return "CMPNGEPS"; 
  case ND_CMPORDPS: return "CMPORDPS";   
  case ND_CMPUNORDPS: return "CMPUNORDPS";  
  case ND_COMIEQ: return "COMIEQ";  
  case ND_COMILT: return "COMILT";     
  case ND_COMILE: return "COMILE"; 
  case ND_COMIGT: return "COMIGT"; 
  case ND_COMIGE: return "COMIGE";     
  case ND_COMINEQ: return "COMINEQ";                                                                                                                                                                                                                                                                                                                             
  case ND_UCOMIEQ: return "UCOMIEQ";  
  case ND_UCOMILT: return "UCOMILT";     
  case ND_UCOMILE: return "UCOMILE"; 
  case ND_UCOMIGT: return "UCOMIGT"; 
  case ND_UCOMIGE: return "UCOMIGE";     
  case ND_UCOMINEQ: return "UCOMINEQ";
  case ND_CVTSS2SI: return "CVTSS2SI";    
  case ND_CVTSS2SI64: return "CVTSS2SI64";   
  case ND_CVTTSS2SI: return "CVTTSS2SI";  
  case ND_CVTTSS2SI64: return "CVTTSS2SI64";
  case ND_CVTTPS2PI: return "CVTTPS2PI";   
  case ND_CVTSI2SS: return "CVTSI2SS";   
  case ND_CVTSI642SS: return "CVTSI642SS";  
  case ND_MOVLHPS: return "MOVLHPS";    
  case ND_MOVHLPS: return "MOVHLPS"; 
  case ND_UNPCKHPS: return "UNPCKHPS";  
  case ND_UNPCKLPS: return "UNPCKLPS";  
  case ND_LOADHPS: return "LOADHPS";        
  case ND_STOREHPS: return "STOREHPS"; 
  case ND_LOADLPS: return "LOADLPS";        
  case ND_STORELPS: return "STORELPS"; 
  case ND_MOVMSKPS: return "MOVMSKPS";    
  case ND_SHUFPS: return "SHUFPS";       
  case ND_SHUFFLE: return "SHUFFLE";     
  case ND_PMAXSW: return "PMAXSW";     
  case ND_PMAXUB: return "PMAXUB";   
  case ND_PMINSW: return "PMINSW"; 
  case ND_PMINUB: return "PMINUB";        
  case ND_PMOVMSKB: return "PMOVMSKB";
  case ND_PMULHUW: return "PMULHUW";   
  case ND_MASKMOVQ: return "MASKMOVQ";   
  case ND_PAVGB: return "PAVGB";            
  case ND_PAVGW: return "PAVGW"; 
  case ND_PSADBW: return "PSADBW";    
  case ND_MOVNTQ: return "MOVNTQ";    
  case ND_MOVNTPS: return "MOVNTPS";         
  case ND_SHUFPD: return "SHUFPD";       
  case ND_ADDSD: return "ADDSD";   
  case ND_SUBSD: return "SUBSD";       
  case ND_MULSD: return "MULSD";   
  case ND_DIVSD: return "DIVSD";    
  case ND_SQRTPD: return "SQRTPD"; 
  case ND_SQRTSD: return "SQRTSD"; 
  case ND_MOVSD: return "MOVSD";        
  case ND_MINPD: return "MINPD";            
  case ND_MINSD: return "MINSD";        
  case ND_MAXPD: return "MAXPD";  
  case ND_MAXSD: return "MAXSD";  
  case ND_ANDPD: return "ANDPD";    
  case ND_ANDNPD: return "ANDNPD";  
  case ND_ORPD: return "ORPD";         
  case ND_XORPD: return "XORPD";      
  case ND_CMPEQPD: return "CMPEQPD";    
  case ND_CMPLTPD: return "CMPLTPD"; 
  case ND_CMPLEPD: return "CMPLEPD"; 
  case ND_CMPGTPD: return "CMPGTPD"; 
  case ND_CMPGEPD: return "CMPGEPD";  
  case ND_CMPNEQPD: return "CMPNEQPD"; 
  case ND_CMPNLTPD: return "CMPNLTPD";  
  case ND_CMPNLEPD: return "CMPNLEPD";  
  case ND_CMPNGTPD: return "CMPNGTPD";   
  case ND_CMPNGEPD: return "CMPNGEPD";   
  case ND_CMPORDPD: return "CMPORDPD";   
  case ND_CMPUNORDPD: return "CMPUNORDPD";
  case ND_CMPEQSD: return "CMPEQSD";   
  case ND_CMPLTSD: return "CMPLTSD";    
  case ND_CMPLESD: return "CMPLESD";    
  case ND_CMPNEQSD: return "CMPNEQSD";   
  case ND_CMPNLTSD: return "CMPNLTSD";     
  case ND_CMPNLESD: return "CMPNLESD";  
  case ND_CMPORDSD: return "CMPORDSD";    
  case ND_CMPUNORDSD: return "CMPUNORDSD"; 
  case ND_COMISDEQ: return "COMISDEQ"; 
  case ND_COMISDLT: return "COMISDLT"; 
  case ND_COMISDLE: return "COMISDLE"; 
  case ND_COMISDGT: return "COMISDGT"; 
  case ND_COMISDGE: return "COMISDGE"; 
  case ND_COMISDNEQ: return "COMISDNEQ"; 
  case ND_UCOMISDEQ: return "UCOMISDEQ"; 
  case ND_UCOMISDLT: return "UCOMISDLT"; 
  case ND_UCOMISDLE: return "UCOMISDLE"; 
  case ND_UCOMISDGT: return "UCOMISDGT"; 
  case ND_UCOMISDGE: return "UCOMISDGE"; 
  case ND_UCOMISDNEQ: return "UCOMISDNEQ"; 
  case ND_MOVQ128: return "MOVQ128"; 
  case ND_CVTDQ2PD: return "CVTDQ2PD"; 
  case ND_CVTDQ2PS: return "CVTDQ2PS"; 
  case ND_CVTPD2DQ: return "CVTPD2DQ"; 
  case ND_CVTPD2PI: return "CVTPD2PI"; 
  case ND_CVTPD2PS: return "CVTPD2PS"; 
  case ND_CVTTPD2DQ: return "CVTTPD2DQ";
  case ND_CVTTPD2PI: return "CVTTPD2PI";  
  case ND_CVTPI2PD: return "CVTPI2PD"; 
  case ND_CVTPS2DQ: return "CVTPS2DQ";  
  case ND_CVTTPS2DQ: return "CVTTPS2DQ";
  case ND_CVTPS2PD: return "CVTPS2PD"; 
  case ND_CVTSD2SI: return "CVTSD2SI"; 
  case ND_CVTSD2SI64: return "CVTSD2SI64";
  case ND_CVTTSD2SI: return "CVTTSD2SI";  
  case ND_CVTTSD2SI64: return "CVTTSD2SI64";
  case ND_CVTSD2SS: return "CVTSD2SS"; 
  case ND_CVTSI2SD: return "CVTSI2SD"; 
  case ND_CVTSI642SD: return "CVTSI642SD";
  case ND_CVTSS2SD: return "CVTSS2SD";  
  case ND_UNPCKHPD: return "UNPCKHPD";  
  case ND_UNPCKLPD: return "UNPCKLPD";  
  case ND_LOADHPD: return "LOADHPD";       
  case ND_LOADLPD: return "LOADLPD";  
  case ND_MOVMSKPD: return "MOVMSKPD";    
  case ND_PACKSSWB128: return "PACKSSWB128";   
  case ND_PACKSSDW128: return "PACKSSDW128";   
  case ND_PACKUSWB128: return "PACKUSWB128";     
  case ND_PUNPCKHBW128: return "PUNPCKHB128";   
  case ND_PUNPCKHWD128: return "PUNPCKHWD128";  
  case ND_PUNPCKHDQ128: return "PUNPCKHDQ128";   
  case ND_PUNPCKHQDQ128: return "PUNPCKHQDQ128"; 
  case ND_PUNPCKLBW128: return "PUNPCKLBW128";   
  case ND_PUNPCKLWD128: return "PUNPCKLWD128";   
  case ND_PUNPCKLDQ128: return "PUNPCKLDQ128";      
  case ND_PUNPCKLQDQ128: return "PUNPCKLQDQ128";      
  case ND_PADDSB128: return "PADDSB128";     
  case ND_PADDSW128: return "PADDSW128";   
  case ND_PADDUSB128: return "PADDUSB128";      
  case ND_PADDUSW128: return "PADDUSW128";   
  case ND_PSUBSB128: return "PSUBSB128";      
  case ND_PSUBSW128: return "PSUBSW128";  
  case ND_PSUBUSB128: return "PSUBUSB128";   
  case ND_PSUBUSW128: return "PSUBUSW128";    
  case ND_PMADDWD128: return "PMADDWD128";         
  case ND_PMULHW128: return "PMULHW128";  
  case ND_PMULUDQ: return "PMULUDQ";    
  case ND_PMULUDQ128: return "PMULUDQ128";      
  case ND_PSLLWI128: return "PSLLWI128";           
  case ND_PSLLDI128: return "PSLLDI128";   
  case ND_PSLLQI128: return "PSLLQI128"; 
  case ND_PSRAWI128: return "PSRAWI128";     
  case ND_PSRADI128: return "PSRADI128";   
  case ND_PSRLWI128: return "PSRLWI128";     
  case ND_PSRLDI128: return "PSRLDI128"; 
  case ND_PSRLQI128: return "PSRLQI128";   
  case ND_PSLLW128: return "PSLLW128";      
  case ND_PSLLD128: return "PSLLD128";   
  case ND_PSLLQ128: return "PSLLQ128";     
  case ND_PSRAW128: return "PSRAW128";   
  case ND_PSRAD128: return "PSRAD128";         
  case ND_PSRLW128: return "PSRLW128";   
  case ND_PSRLD128: return "PSRLD128";   
  case ND_PSRLQ128: return "PSRLQ128";  
  case ND_PANDN128: return "PANDN128";     
  case ND_PMAXSW128: return "PMAXSW128";         
  case ND_PMAXUB128: return "PMAXUB128";         
  case ND_PMINSW128: return "PMINSW128"; 
  case ND_PMINUB128: return "PMINUB128";      
  case ND_PMOVMSKB128: return "PMOVMSKB128";   
  case ND_PMULHUW128: return "PMULHUW128";        
  case ND_MASKMOVDQU: return "MASKMOVDQU";   
  case ND_PAVGB128: return "PAVGB128";        
  case ND_PAVGW128: return "PAVGW128";        
  case ND_PSADBW128: return "PSADBW128";       
  case ND_MOVNTI: return "MOVNTI";  
  case ND_MOVNTI64: return "MOVNTI64";  
  case ND_MOVNTDQ: return "MOVNTDQ";  
  case ND_MOVNTPD: return "MOVNTPD";     
  case ND_PARITY: return "PARITY";    
  case ND_PARITYL: return "PARITYL";  
  case ND_PARITYLL: return "PARITYLL";    
  case ND_MWAIT: return "MWAIT";
  case ND_MONITOR: return "MONITOR";
  case ND_ADDSUBPS: return "ADDSUBPS";
  case ND_HADDPS: return "HADDPS";
  case ND_HSUBPS: return "HSUBPS";
  case ND_MOVSHDUP: return "MOVSHDUP";
  case ND_MOVSLDUP: return "MOVSLDUP";
  case ND_ADDSUBPD: return "ADDSUBPD";
  case ND_HADDPD: return "HADDPD";
  case ND_HSUBPD: return "HSUBPD";
  case ND_PHADDW128: return "PHADDW128";
  case ND_PHADDD128: return "PHADDD128";
  case ND_PHADDSW128: return "PHADDSW128";
  case ND_PHADDW: return "PHADDW";
  case ND_PHADDD: return "PHADDD";
  case ND_PHADDSW: return "PHADDSW";
  case ND_PHSUBW128: return "PHSUBW128";
  case ND_PHSUBD128: return "PHSUBD128";
  case ND_PHSUBSW128: return "PHSUBSW128";
  case ND_PHSUBW: return "PHSUBW";
  case ND_PHSUBD: return "PHSUBD";
  case ND_PHSUBSW: return "PHSUBSW";
  case ND_PMADDUBSW128: return "PMADDUBSW128";
  case ND_PMADDUBSW: return "PMADDUBSW";
  case ND_PMULHRSW128: return "PMULHRSW128";
  case ND_PMULHRSW: return "PMULHRSW";
  case ND_PSHUFB128: return "PSHUFB128";
  case ND_PSHUFB: return "PSHUFB";
  case ND_PSIGNB128: return "PSIGNB128";
  case ND_PSIGNW128: return "PSIGNW128";
  case ND_PSIGND128: return "PSIGND128";
  case ND_PSIGNB: return "PSIGNB";
  case ND_PSIGNW: return "PSIGNW";
  case ND_PSIGND: return "PSIGND";
  case ND_PABSB128: return "PABSB128";
  case ND_PABSW128: return "PABSW128";
  case ND_PABSD128: return "PABSD128";
  case ND_PABSB: return "PABSB";
  case ND_PABSW: return "PABSW";
  case ND_PABSD: return "PABSD";
  case ND_PTESTZ128: return "PTESTZ128";
  case ND_PTESTC128: return "PTESTC128";
  case ND_PTESTNZC128: return "PTESTNZC128";
  case ND_PBLENDVB128: return "PBLENDVB128";
  case ND_BLENDVPS: return "BLENDVPS";
  case ND_BLENDVPD: return "BLENDVPD";
  case ND_PMINSB128: return "PMINSB128";
  case ND_PMAXSB128: return "PMAXSB128";
  case ND_PMINUW128: return "PMINUW128";
  case ND_PMAXUW128: return "PMAXUW128";
  case ND_PMINSD128: return "PMINSD128";
  case ND_PMAXSD128: return "PMAXSD128";  
  case ND_PMINUD128: return "PMINUD128";
  case ND_PMAXUD128: return "PMAXUD128";
  case ND_PMULDQ128: return "PMULDQ128";
  case ND_PHMINPOSUW128: return "PHMINPOSUW128";
  case ND_PMOVSXBD128: return "PMOVSXBD128";
  case ND_PMOVSXWD128: return "PMOVSXWD128";
  case ND_PMOVSXBQ128: return "PMOVSXBQ128";
  case ND_PMOVSXDQ128: return "PMOVSXDQ128";
  case ND_PMOVSXWQ128: return "PMOVSXWQ128";
  case ND_PMOVSXBW128: return "PMOVSXBW128";
  case ND_PMOVZXBD128: return "PMOVZXBD128";
  case ND_PMOVZXWD128: return "PMOVZXWD128";
  case ND_PMOVZXBQ128: return "PMOVZXBQ128";
  case ND_PMOVZXDQ128: return "PMOVZXDQ128";
  case ND_PMOVZXWQ128: return "PMOVZXWQ128";
  case ND_PMOVZXBW128: return "PMOVZXBW128";
  case ND_PACKUSDW128: return "PACKUSDW128";
  case ND_MOVNTDQA: return "MOVNTDQA";
  case ND_CRC32QI: return "CRC32QI";
  case ND_CRC32HI: return "CRC32HI";
  case ND_CRC32SI: return "CRC32SI";
  case ND_CRC32DI: return "CRC32DI";
  case ND_PSHUFD: return "PSHUFD";
  case ND_FETCHNAND: return "FETCHNAND";
  case ND_ADD_AND_FETCH: return "ADD_AND_FETCH";
  case ND_SUB_AND_FETCH: return "SUB_AND_FETCH";
  case ND_BOOL_CAS: return "BOOL_CAS";
  case ND_PREFETCH: return "PREFETCH";
  case ND_RDTSC: return "RDTSC";
  case ND_READEFLAGS_U64: return "READEFLAGS_U64";
  case ND_RDSSPQ: return "RDSSPQ";
  case ND_SAVEPREVSSP: return "SAVEPREVSSP";
  case ND_SETSSBSY: return "SETSSBSY";
  case ND_SLWPCB: return "SLWPCB";
  case ND_RDPKRU: return "RDPKRU";
  case ND_XBEGIN: return "XBEGIN";
  case ND_XEND: return "XEND";
  case ND_SERIALIZE: return "SERIALIZE";
  case ND_XSUSLDTRK: return "XSUSLDTRK";
  case ND_XRESLDTRK: return "XRESLDTRK";
  case ND_CLUI: return "CLUI";
  case ND_STUI: return "STUI";
  case ND_TESTUI: return "TESTUI";
  case ND_WBNOINVD: return "WBNOINVD";
  case ND_XTEST: return "XTEST";
  case ND_WBINVD: return "WBINVD";
  case ND_RDPID: return "RDPID";
  case ND_RDFSBASE32: return "RDFSBASE32";
  case ND_RDFSBASE64: return "RDFSBASE64";
  case ND_RDGSBASE32: return "RDGSBASE32";
  case ND_RDGSBASE64: return "RDGSBASE64";
  case ND_VZEROALL: return "VZEROALL";
  case ND_VZEROUPPER: return "VZEROUPPER";
  case ND_FEMMS: return "FEMMS";
  case ND_BSRSI: return "BSRSI";
  case ND_RDPMC: return "RDPMC";
  case ND_RDTSCP: return "RDTSCP";
  case ND_ROLQI: return "ROLQI";
  case ND_ROLHI: return "ROLHI";
  case ND_RORQI: return "RORQI";
  case ND_RORHI: return "RORHI";
  case ND_BSRDI: return "BSRDI";  
  case ND_WRITEEFLAGS_U64: return "WRITEEFLAGS_U64";
  case ND_INCSSPQ: return "INCSSPQ";
  case ND_RSTORSSP: return "RSTORSSP";
  case ND_WRSSD: return "WRSSD";
  case ND_WRSSQ: return "WRSSQ";
  case ND_WRUSSD: return "WRUSSD";
  case ND_WRUSSQ: return "WRUSSQ";
  case ND_CLRSSBSY: return "CLRSSBSY";
  case ND_SBB_U32: return "SBB_U32";
  case ND_ADDCARRYX_U32: return "ADDCARRYX_U32";
  case ND_SBB_U64: return "SBB_U64";
  case ND_ADDCARRYX_U64: return "ADDCARRYX_U64";  
  case ND_TZCNT_U16: return "TZCNT_U16";
  case ND_BEXTR_U32: return "BEXTR_U32";
  case ND_ADDFETCH: return "ADDFETCH";
  case ND_FPCLASSIFY: return "FPCLASSIFY";
  case ND_ISUNORDERED: return "ISUNORDERED";
  case ND_SIGNBIT: return "SIGNBIT";
  case ND_SIGNBITF: return "SIGNBITF";
  case ND_SIGNBITL: return "SIGNBITL";
  case ND_ATOMIC_IS_LOCK_FREE: return "ATOMIC_IS_LOCK_FREE";
  case ND_PSUBUSB256: return "PSUBUSB256";
  case ND_PCMPGTB256_MASK: return "PCMPGTB256_MASK";
  case ND_PSHUFB256: return "PSHUFB256";  
  default: return "UNREACHABLE"; 
  }
}

//from COSMOPOLITAN adding function ConsumeStringLiteral
char *ConsumeStringLiteral(Token **rest, Token *tok) {
  char *s;
  if (tok->kind != TK_STR || tok->ty->base->kind != TY_CHAR) {
   
    error_tok(tok, "%s:%d: in ConsumeStringLiteral : expected string literal but got tok->kind %d", __FILE__, __LINE__, tok->kind);
  }
  s = tok->str;
  *rest = tok->next;
  return s;
}


//from COSMOPOLITAN adding function static_assertion
static Token *static_assertion(Token *tok) {
  char *msg;
  Token *start = tok;
  Token *errmsg = tok;
  SET_CTX(ctx);
  tok = skip(tok->next, "(", ctx);
  int64_t cond = const_expr(&tok, tok);

  if (consume(&tok, tok, ",")) {
    errmsg = tok;
    msg = ConsumeStringLiteral(&tok, tok);
  } else {
    msg = "static assertion failed";
  }
  SET_CTX(ctx);
  tok = skip(tok, ")", ctx);
  SET_CTX(ctx);  
  tok = skip(tok, ";", ctx);
  if (!cond) {
    error_tok(start, "%s:%d: in static_assertion : %s %s", __FILE__, __LINE__, msg, errmsg->loc);

  }
  return tok;
}



// this function checks if we have an old C style function declaration
static bool check_old_style(Token **rest, Token *tok)
{
  Token *start = tok;
  is_old_style = false;

  while (tok->kind != TK_EOF && !equal(tok, "{"))
  {
 
      //found a function body
      if (equal(tok, ";") && equal(tok->next, "{"))
      {
        tok = start;
        return true; 
      }
      //if function declaration ending with ";" exit
      if (equal(tok, ")") && equal(tok->next, ";"))
      {
        break;
      }

      // //if function not followed by a Keyword exit
      // if (equal(tok, ")") && tok->next &&tok->next->kind != TK_KEYWORD)
      // {
      //   break;
      // }

      if (equal(tok, "}"))
      {
        break;
      }


        tok = tok->next;
  }

  tok = start;
  return false;
}



static Token * old_style_params(Token **rest, Token *tok, Type *ty) {
  int nbparms = 0;
  bool first = true;

  while(!equal(tok, ")"))
  {
    //first count the number of parameters 
    if (!first) {
      SET_CTX(ctx);
      tok = skip(tok, ",", ctx);
      }
    first = false;
    ArrayTokenOrder[nbFunc][nbparms] = tok;

    nbparms++;
    tok = tok->next;
  }
  ArrayTokenOrderCount[nbFunc] = nbparms;
  tok = tok->next;
  return tok;
}


static Node *ParseBuiltin(NodeKind kind, Token *tok, Token **rest) {
  Node *node = new_node(kind, tok);
  SET_CTX(ctx);    
  tok = skip(tok->next, "(", ctx);
  node->builtin_val = assign(&tok, tok);
  add_type(node->builtin_val); 
  SET_CTX(ctx);      
  *rest = skip(tok, ")", ctx);
  return node;  
}

//from cosmopolitan managing builtin atomics
static Node *ParseAtomic2(NodeKind kind, Token *tok, Token **rest) {
  Node *node = new_node(kind, tok);
  SET_CTX(ctx); 
  tok = skip(tok->next, "(", ctx);
  node->lhs = assign(&tok, tok);
  add_type(node->lhs);
  node->ty = node->lhs->ty->base;
  if (equal(tok, ",")) {
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->memorder = const_expr(&tok, tok);
  }   
  SET_CTX(ctx); 
  *rest = skip(tok, ")", ctx);
  return node;
}

static Node *ParseAtomic3(NodeKind kind, Token *tok, Token **rest) {
  Node *node = new_node(kind, tok);
  SET_CTX(ctx); 
  tok = skip(tok->next, "(", ctx);
  node->lhs = assign(&tok, tok);
  add_type(node->lhs);
  node->ty = node->lhs->ty->base;
  SET_CTX(ctx); 
  tok = skip(tok, ",", ctx);
  node->rhs = assign(&tok, tok);
  add_type(node->rhs);
  // Check if there's a comma, indicating a memory order argument
  if (equal(tok, ",")) {
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->memorder = const_expr(&tok, tok);
  } 
  SET_CTX(ctx); 
  *rest = skip(tok, ")", ctx);
  return node;
}

static Node *ParseAtomicFetch(NodeKind kind, Token *tok, Token **rest) {
    Token *start = tok;
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    Node *obj = new_unary(ND_DEREF, assign(&tok, tok), start);
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    Node *val = assign(&tok, tok);
    int memorder = __ATOMIC_SEQ_CST; 
    if (equal(tok, ",")) {
        tok = skip(tok, ",", ctx);
        memorder = const_expr(&tok, tok); 
    }
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    Node *binary;
    char *loc = start->loc + 23;
    int len = start->len - 23;

    if (!strncmp("add", loc, len))
      binary = new_add(obj, val, start, false);
    else if (!strncmp("sub", loc, len))
      binary = new_sub(obj, val, start, false);
    else if (!strncmp("and", loc, len))
      binary = new_binary(ND_BITAND, obj, val, start);
    else if (!strncmp("or", loc, len))
      binary = new_binary(ND_BITOR, obj, val, start);
    else if (!strncmp("xor", loc, len))
      binary = new_binary(ND_BITXOR, obj, val, start);
    else      
      error_tok(start, "%s:%d: in ParseAtomicFetch: unsupported atomic fetch op!", __FILE__, __LINE__);
    binary->memorder = memorder;
    add_type(binary->lhs);
    add_type(binary->rhs);
    return atomic_op(binary, true);
  }

static Node *ParseAtomicCompareExchangeN(NodeKind kind, Token *tok, Token **rest) {
  Node *node = new_node(kind, tok);
  SET_CTX(ctx);
  tok = skip(tok->next, "(", ctx);
  node->cas_ptr = assign(&tok, tok);
  add_type(node->cas_ptr);
  tok = skip(tok, ",", ctx);
  node->cas_expected = assign(&tok, tok);
  add_type(node->cas_expected);
  tok = skip(tok, ",", ctx);
  node->cas_desired = assign(&tok, tok);
  add_type(node->cas_desired);
  tok = skip(tok, ",", ctx);
  node->cas_weak = assign(&tok, tok);
  add_type(node->cas_weak);
  tok = skip(tok, ",", ctx);
  node->cas_success = assign(&tok, tok);
  add_type(node->cas_success);
  tok = skip(tok, ",", ctx);
  node->cas_failure = assign(&tok, tok);
  add_type(node->cas_failure);
  *rest = skip(tok, ")", ctx);
  node->ty = ty_bool;
  return node;
}


//builtin function memcpy
static Node *parse_memcpy(Token *tok, Token **rest) {
    Node *node = new_node(ND_BUILTIN_MEMCPY, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->builtin_dest = assign(&tok, tok);
    add_type(node->builtin_dest); 
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->builtin_src = assign(&tok, tok);
    add_type(node->builtin_src); 
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->builtin_size = assign(&tok, tok);
    add_type(node->builtin_size); 
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;  
}


static Node *parse_memset(Token *tok, Token **rest) {
    Node *node = new_node(ND_BUILTIN_MEMSET, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->builtin_dest = assign(&tok, tok);
    add_type(node->builtin_dest); 
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->builtin_val = assign(&tok, tok);
    add_type(node->builtin_val); 
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->builtin_size = assign(&tok, tok);
    add_type(node->builtin_size); 
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);
    return node;
}

static Node *ParseAtomicFence(NodeKind kind, Token *tok, Token **rest) {
    Node *node = new_node(kind, tok);
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); // memory order
    add_type(node->lhs);
    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);
    return node;
}

static Node *ParseAtomicClear(NodeKind kind, Token *tok, Token **rest) {
    Node *node = new_node(kind, tok);
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok); // pointer
    add_type(node->lhs);
    node->ty = node->lhs->ty->base;
    // __atomic_clear has a second argument for memory order
    if (equal(tok, ",")) {
        SET_CTX(ctx);
        tok = skip(tok, ",", ctx);
        node->memorder = const_expr(&tok, tok);
    }
    SET_CTX(ctx);
    *rest = skip(tok, ")", ctx);
    return node;
}

static Node *parse_overflow(NodeKind kind, Token *tok, Token **rest) {
    // Parse the arguments for __builtin_add_overflow
    Node *node = new_node(kind, tok);
    SET_CTX(ctx); 
    tok = skip(tok->next, "(", ctx);
    node->lhs = assign(&tok, tok);
    add_type(node->lhs); 
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->rhs = assign(&tok, tok);
    add_type(node->rhs); 
    SET_CTX(ctx); 
    tok = skip(tok, ",", ctx);
    node->builtin_dest = assign(&tok, tok);
    add_type(node->builtin_dest); 
    SET_CTX(ctx); 
    *rest = skip(tok, ")", ctx);    
    return node;

}


// //the goal of this function is to put the correct type for the correct parameter order in case of old C style K&R
// // example :
// // void test_compress(compr, comprLen, uncompr, uncomprLen) char *compr,
// //   *uncompr;
// // long comprLen, uncomprLen;
// // the order of parameters inside parenthesis doesn't correspond to the declaration of each parameter.
// // that's why this function found the parameter order and update the type for this order and returns new ty->params following
// // the expected order and not the declaration order. It's quite complex and probably we can find an easiest way to do it
static Type *old_params(Type *ty, int nbparms) {
  Type head = {};
  Type *cur = &head;
  bool isOrdered = true;
  int nborder = ArrayTokenOrderCount[nbFunc];

  // Check if parameters are already in order
  for (int i = 0; i < nbparms && i < nborder; i++) {
    if (strncmp(ArrayTokenOrder[nbFunc][i]->loc, ArrayToken[nbFunc][i]->loc, ArrayToken[nbFunc][i]->len) != 0) {
      isOrdered = false;
      break;
    }
  }

  // If parameters are already in order, return the original type list
  if (isOrdered) {
    return ty;
  }

  // If not in order, create a new Type list with parameters in correct order
  for (int i = 0; i < nborder; i++) {
    bool found = false;
    for (int j = 0; j < nbparms; j++) {
      if (strncmp(ArrayTokenOrder[nbFunc][i]->loc, ArrayToken[nbFunc][j]->loc, ArrayTokenOrder[nbFunc][i]->len) == 0) {
        cur = cur->next = copy_type(ArrayType[nbFunc][j]);
        found = true;
        break;
      }
    }
    if (!found) {
      Type *t = copy_type(ty_int);
      t->name = ArrayTokenOrder[nbFunc][i];
      cur = cur->next = t;
    }
  }

  return head.next;
}

static Node *parse_huge_val(double fval, Token *tok, Token **rest) {
  Node *node = new_double(fval, tok);
  SET_CTX(ctx);    
  tok = skip(tok->next, "(", ctx);
  SET_CTX(ctx); 
  tok = skip(tok, ")", ctx);
  *rest = tok;
  return node;
}

static int64_t eval_sign_extend(Type *ty, uint64_t val) {
  switch (ty->size) {
  case 1: return ty->is_unsigned ? (uint8_t)val : (int64_t)(int8_t)val;
  case 2: return ty->is_unsigned ? (uint16_t)val : (int64_t)(int16_t)val;
  case 4: return ty->is_unsigned ? (uint32_t)val : (int64_t)(int32_t)val;
  case 8: return val;
  case 16: return ty->is_unsigned ? (uint64_t)val : (int64_t)val;

  }
  printf("====FATAL ERROR %ld\n", ty->size );
  unreachable();
}


static bool is_const_var(Obj *var) {
  Type *ty = var->ty;
  for (; ty && ty->kind == TY_ARRAY; ty = ty->base)
    if (ty->is_const)
      return true;
  return ty->is_const;
}



static Obj *eval_var(Node *expr, bool allow_local) {

  if (expr->kind != ND_VAR)
    return NULL;

  Obj *var = expr->var;
  if (!var)
    return NULL;


  if (var->is_compound_lit)
    return var;

  if (!allow_local && (var->is_static || var->is_definition) &&
      var->init_data && is_const_var(var))
    return var;

  return NULL;
}

static Obj *find_global_by_name(char *name) {
  if (!name)
    return NULL;
  for (Obj *var = globals; var; var = var->next) {
    if (var->name && !strcmp(var->name, name))
      return var;
  }
  return NULL;
}


static bool is_str_tok(Token **rest, Token *tok, Token **str_tok) {
  if (equal(tok, "(") && is_str_tok(&tok, tok->next, str_tok) &&
    consume(rest, tok, ")"))
    return true;

  if (tok->kind == TK_STR) {
    *str_tok = tok;
    *rest = tok->next;
    return true;
  }
  return false;
}

static BuiltinEntry builtin_table[] = {
    { "__builtin_ia32_packssdw", ND_PACKSSDW },
    { "__builtin_ia32_packsswb", ND_PACKSSWB },
    { "__builtin_ia32_packuswb", ND_PACKUSWB },
    { "__builtin_ia32_punpckhbw", ND_PUNPCKHBW },
    { "__builtin_ia32_punpckhwd", ND_PUNPCKHWD },
    { "__builtin_ia32_punpckhdq", ND_PUNPCKHDQ },
    { "__builtin_ia32_punpcklbw", ND_PUNPCKLBW },
    { "__builtin_ia32_punpcklwd", ND_PUNPCKLWD },
    { "__builtin_ia32_punpckldq", ND_PUNPCKLDQ },
    { "__builtin_ia32_paddb", ND_PADDB },
    { "__builtin_ia32_paddw", ND_PADDW },
    { "__builtin_ia32_paddd", ND_PADDD },
    { "__builtin_ia32_paddq", ND_PADDQ },
    { "__builtin_ia32_paddsb", ND_PADDSB },
    { "__builtin_ia32_paddsw", ND_PADDSW },
    { "__builtin_ia32_paddusb", ND_PADDUSB },
    { "__builtin_ia32_paddusw", ND_PADDUSW },
    { "__builtin_ia32_psubb", ND_PSUBB },
    { "__builtin_ia32_psubw", ND_PSUBW },
    { "__builtin_ia32_psubd", ND_PSUBD },
    { "__builtin_ia32_psubq", ND_PSUBQ },
    { "__builtin_ia32_psubsb", ND_PSUBSB },
    { "__builtin_ia32_psubsw", ND_PSUBSW },
    { "__builtin_ia32_psubusb", ND_PSUBUSB },
    { "__builtin_ia32_psubusw", ND_PSUBUSW },
    { "__builtin_ia32_pmaddwd", ND_PMADDWD },
    { "__builtin_ia32_pmulhw", ND_PMULHW },
    { "__builtin_ia32_pmullw", ND_PMULLW },
    { "__builtin_ia32_psllw", ND_PSLLW },
    { "__builtin_ia32_psllwi", ND_PSLLWI },
    { "__builtin_ia32_pslld", ND_PSLLD },
    { "__builtin_ia32_pslldi", ND_PSLLDI },
    { "__builtin_ia32_psllq", ND_PSLLQ },
    { "__builtin_ia32_psllqi", ND_PSLLQI },
    { "__builtin_ia32_psraw", ND_PSRAW },
    { "__builtin_ia32_psrawi", ND_PSRAWI },
    { "__builtin_ia32_psrad", ND_PSRAD },
    { "__builtin_ia32_psradi", ND_PSRADI },
    { "__builtin_ia32_psrlw", ND_PSRLW },
    { "__builtin_ia32_psrlwi", ND_PSRLWI },
    { "__builtin_ia32_psrld", ND_PSRLD },
    { "__builtin_ia32_psrldi", ND_PSRLDI },
    { "__builtin_ia32_psrlq", ND_PSRLQ },
    { "__builtin_ia32_psrlqi", ND_PSRLQI },
    { "__builtin_ia32_pand", ND_PAND },
    { "__builtin_ia32_pandn", ND_PANDN },
    { "__builtin_ia32_por", ND_POR },
    { "__builtin_ia32_pxor", ND_PXOR },
    { "__builtin_ia32_pcmpeqb", ND_PCMPEQB },
    { "__builtin_ia32_pcmpgtb", ND_PCMPGTB },
    { "__builtin_ia32_pcmpeqw", ND_PCMPEQW },
    { "__builtin_ia32_pcmpgtw", ND_PCMPGTW },
    { "__builtin_ia32_pcmpeqd", ND_PCMPEQD },    
    { "__builtin_ia32_pcmpgtd", ND_PCMPGTD },      
    { "__builtin_ia32_vec_init_v4hi", ND_VECINITV4HI },  
    { "__builtin_ia32_vec_init_v8qi", ND_VECINITV8QI },    
    { "__builtin_ia32_vec_init_v2si", ND_VECINITV2SI },   
    { "__builtin_ia32_vec_ext_v2si", ND_VECEXTV2SI },       
    { "__builtin_ia32_vec_ext_v4si", ND_VECEXTV4SI },       
    { "__builtin_ia32_emms", ND_EMMS },       
    { "__builtin_ia32_sfence", ND_SFENCE },       
    { "__builtin_ia32_lfence", ND_LFENCE },     
    { "__builtin_ia32_mfence", ND_MFENCE },       
    { "__builtin_ia32_pause", ND_PAUSE },     
    { "__builtin_ia32_stmxcsr", ND_STMXCSR },   
    { "__builtin_ia32_ldmxcsr", ND_LDMXCSR },     
    { "__builtin_ia32_cvtpi2ps", ND_CVTPI2PS },    
    { "__builtin_ia32_cvtps2pi", ND_CVTPS2PI },    
    { "__builtin_ia32_addss", ND_ADDSS },        
    { "__builtin_ia32_subss", ND_SUBSS },        
    { "__builtin_ia32_mulss", ND_MULSS },   
    { "__builtin_ia32_divss", ND_DIVSS },     
    { "__builtin_ia32_sqrtss", ND_SQRTSS },   
    { "__builtin_ia32_sqrtps", ND_SQRTPS },   
    { "__builtin_ia32_rcpss", ND_RCPSS },     
    { "__builtin_ia32_rsqrtss", ND_RSQRTSS },
    { "__builtin_ia32_rsqrtps", ND_RSQRTPS },
    { "__builtin_ia32_minss", ND_MINSS },          
    { "__builtin_ia32_minps", ND_MINPS },           
    { "__builtin_ia32_maxss", ND_MAXSS },  
    { "__builtin_ia32_maxps", ND_MAXPS },       
    { "__builtin_ia32_rcpps", ND_RCPPS },     
    { "__builtin_ia32_andps", ND_ANDPS },      
    { "__builtin_ia32_andnps", ND_ANDNPS }, 
    { "__builtin_ia32_orps", ND_ORPS },   
    { "__builtin_ia32_xorps", ND_XORPS },  
    { "__builtin_ia32_cmpeqss", ND_CMPEQSS },
    { "__builtin_ia32_cmpltss", ND_CMPLTSS },       
    { "__builtin_ia32_cmpless", ND_CMPLESS },      
    { "__builtin_ia32_movss", ND_MOVSS },    
    { "__builtin_ia32_cmpneqss", ND_CMPNEQSS },  
    { "__builtin_ia32_cmpnltss", ND_CMPNLTSS },       
    { "__builtin_ia32_cmpnless", ND_CMPNLESS },         
    { "__builtin_ia32_cmpordss", ND_CMPORDSS },  
    { "__builtin_ia32_cmpunordss", ND_CMPUNORDSS },  
    { "__builtin_ia32_cmpeqps", ND_CMPEQPS },
    { "__builtin_ia32_cmpltps", ND_CMPLTPS },
    { "__builtin_ia32_cmpleps", ND_CMPLEPS },
    { "__builtin_ia32_cmpgtps", ND_CMPGTPS },
    { "__builtin_ia32_cmpgeps", ND_CMPGEPS },
    { "__builtin_ia32_cmpneqps", ND_CMPNEQPS },
    { "__builtin_ia32_cmpnltps", ND_CMPNLTPS },
    { "__builtin_ia32_cmpnleps", ND_CMPNLEPS },
    { "__builtin_ia32_cmpngtps", ND_CMPNGTPS },
    { "__builtin_ia32_cmpngeps", ND_CMPNGEPS },
    { "__builtin_ia32_cmpordps", ND_CMPORDPS },  
    { "__builtin_ia32_cmpunordps", ND_CMPUNORDPS },  
    { "__builtin_ia32_comieq", ND_COMIEQ },  
    { "__builtin_ia32_comilt", ND_COMILT },  
    { "__builtin_ia32_comile", ND_COMILE },  
    { "__builtin_ia32_comigt", ND_COMIGT },  
    { "__builtin_ia32_comige", ND_COMIGE },  
    { "__builtin_ia32_comineq", ND_COMINEQ },  
    { "__builtin_ia32_ucomieq", ND_UCOMIEQ },  
    { "__builtin_ia32_ucomilt", ND_UCOMILT },  
    { "__builtin_ia32_ucomile", ND_UCOMILE },  
    { "__builtin_ia32_ucomigt", ND_UCOMIGT },  
    { "__builtin_ia32_ucomige", ND_UCOMIGE },  
    { "__builtin_ia32_ucomineq", ND_UCOMINEQ },   
    { "__builtin_ia32_cvtss2si", ND_CVTSS2SI },   
    { "__builtin_ia32_cvtss2si64", ND_CVTSS2SI64 },   
    { "__builtin_ia32_cvttss2si", ND_CVTTSS2SI },   
    { "__builtin_ia32_cvttss2si64", ND_CVTTSS2SI64 },
    { "__builtin_ia32_cvttps2pi", ND_CVTTPS2PI },      
    { "__builtin_ia32_cvtsi2ss", ND_CVTSI2SS },      
    { "__builtin_ia32_cvtsi642ss", ND_CVTSI642SS },
    { "__builtin_ia32_movlhps", ND_MOVLHPS },         
    { "__builtin_ia32_movhlps", ND_MOVHLPS },         
    { "__builtin_ia32_unpckhps", ND_UNPCKHPS },    
    { "__builtin_ia32_unpcklps", ND_UNPCKLPS },         
    { "__builtin_ia32_loadhps", ND_LOADHPS },   
    { "__builtin_ia32_storehps", ND_STOREHPS },        
    { "__builtin_ia32_loadlps", ND_LOADLPS },   
    { "__builtin_ia32_storelps", ND_STORELPS },   
    { "__builtin_ia32_movmskps", ND_MOVMSKPS },  
    { "__builtin_ia32_shufps", ND_SHUFPS },         
    { "__builtin_shuffle", ND_SHUFFLE },       
    { "__builtin_ia32_pmaxsw", ND_PMAXSW },     
    { "__builtin_ia32_pmaxub", ND_PMAXUB },   
    { "__builtin_ia32_pminsw", ND_PMINSW },   
    { "__builtin_ia32_pminub", ND_PMINUB },          
    { "__builtin_ia32_clflush", ND_CLFLUSH },          
    { "_mm_clflush", ND_CLFLUSH },          
    { "__builtin_ia32_pmovmskb", ND_PMOVMSKB },   
    { "__builtin_ia32_pmulhuw", ND_PMULHUW },
    { "__builtin_ia32_maskmovq", ND_MASKMOVQ },    
    { "__builtin_ia32_pavgb", ND_PAVGB },
    { "__builtin_ia32_pavgw", ND_PAVGW },
    { "__builtin_ia32_psadbw", ND_PSADBW },
    { "__builtin_ia32_movntq", ND_MOVNTQ },
    { "__builtin_ia32_movntps", ND_MOVNTPS },
    { "__builtin_ia32_shufpd", ND_SHUFPD },    
    { "__builtin_ia32_addsd", ND_ADDSD },  
    { "__builtin_ia32_subsd", ND_SUBSD },  
    { "__builtin_ia32_mulsd", ND_MULSD },  
    { "__builtin_ia32_divsd", ND_DIVSD }, 
    { "__builtin_ia32_sqrtpd", ND_SQRTPD },
    { "__builtin_ia32_movsd", ND_MOVSD },  
    { "__builtin_ia32_sqrtsd", ND_SQRTSD },
    { "__builtin_ia32_minpd", ND_MINPD },      
    { "__builtin_ia32_minsd", ND_MINSD },      
    { "__builtin_ia32_maxpd", ND_MAXPD },        
    { "__builtin_ia32_maxsd", ND_MAXSD },       
    { "__builtin_ia32_andpd", ND_ANDPD }, 
    { "__builtin_ia32_andnpd", ND_ANDNPD },
    { "__builtin_ia32_orpd", ND_ORPD },      
    { "__builtin_ia32_xorpd", ND_XORPD },   
    { "__builtin_ia32_cmpeqpd", ND_CMPEQPD },  
    { "__builtin_ia32_cmpltpd", ND_CMPLTPD },  
    { "__builtin_ia32_cmplepd", ND_CMPLEPD },     
    { "__builtin_ia32_cmpgtpd", ND_CMPGTPD },     
    { "__builtin_ia32_cmpgepd", ND_CMPGEPD },    
    { "__builtin_ia32_cmpneqpd", ND_CMPNEQPD },        
    { "__builtin_ia32_cmpnltpd", ND_CMPNLTPD }, 
    { "__builtin_ia32_cmpnlepd", ND_CMPNLEPD }, 
    { "__builtin_ia32_cmpngtpd", ND_CMPNGTPD },  
    { "__builtin_ia32_cmpngepd", ND_CMPNGEPD },    
    { "__builtin_ia32_cmpordpd", ND_CMPORDPD },       
    { "__builtin_ia32_cmpunordpd", ND_CMPUNORDPD },   
    { "__builtin_ia32_cmpeqsd", ND_CMPEQSD },         
    { "__builtin_ia32_cmpltsd", ND_CMPLTSD },       
    { "__builtin_ia32_cmplesd", ND_CMPLESD }, 
    { "__builtin_ia32_cmpneqsd", ND_CMPNEQSD },     
    { "__builtin_ia32_cmpnltsd", ND_CMPNLTSD },    
    { "__builtin_ia32_cmpnlesd", ND_CMPNLESD },   
    { "__builtin_ia32_cmpordsd", ND_CMPORDSD },       
    { "__builtin_ia32_cmpunordsd", ND_CMPUNORDSD },     
    { "__builtin_ia32_comisdeq", ND_COMISDEQ },     
    { "__builtin_ia32_comisdlt", ND_COMISDLT},   
    { "__builtin_ia32_comisdle", ND_COMISDLE},   
    { "__builtin_ia32_comisdgt", ND_COMISDGT},   
    { "__builtin_ia32_comisdge", ND_COMISDGE},    
    { "__builtin_ia32_comisdneq", ND_COMISDNEQ},  
    { "__builtin_ia32_ucomisdeq", ND_UCOMISDEQ },     
    { "__builtin_ia32_ucomisdlt", ND_UCOMISDLT},   
    { "__builtin_ia32_ucomisdle", ND_UCOMISDLE},   
    { "__builtin_ia32_ucomisdgt", ND_UCOMISDGT},   
    { "__builtin_ia32_ucomisdge", ND_UCOMISDGE},    
    { "__builtin_ia32_ucomisdneq", ND_UCOMISDNEQ},    
    { "__builtin_ia32_movq128", ND_MOVQ128},     
    { "__builtin_ia32_cvtdq2pd", ND_CVTDQ2PD},     
    { "__builtin_ia32_cvtdq2ps", ND_CVTDQ2PS},     
    { "__builtin_ia32_cvtpd2dq", ND_CVTPD2DQ}, 
    { "__builtin_ia32_cvtpd2pi", ND_CVTPD2PI},  
    { "__builtin_ia32_cvtpd2ps", ND_CVTPD2PS},    
    { "__builtin_ia32_cvttpd2dq", ND_CVTTPD2DQ},
    { "__builtin_ia32_cvttpd2pi", ND_CVTTPD2PI},       
    { "__builtin_ia32_cvtpi2pd", ND_CVTPI2PD}, 
    { "__builtin_ia32_cvtps2dq", ND_CVTPS2DQ},  
    { "__builtin_ia32_cvttps2dq", ND_CVTTPS2DQ},
    { "__builtin_ia32_cvtps2pd", ND_CVTPS2PD},  
    { "__builtin_ia32_cvtsd2si", ND_CVTSD2SI},      
    { "__builtin_ia32_cvtsd2si64", ND_CVTSD2SI64}, 
    { "__builtin_ia32_cvttsd2si", ND_CVTTSD2SI},   
    { "__builtin_ia32_cvttsd2si64", ND_CVTTSD2SI64},
    { "__builtin_ia32_cvtsd2ss", ND_CVTSD2SS},        
    { "__builtin_ia32_cvtsi2sd", ND_CVTSI2SD},        
    { "__builtin_ia32_cvtsi642sd", ND_CVTSI642SD},
    { "__builtin_ia32_cvtss2sd", ND_CVTSS2SD},      
    { "__builtin_ia32_unpckhpd", ND_UNPCKHPD},           
    { "__builtin_ia32_unpcklpd", ND_UNPCKLPD},   
    { "__builtin_ia32_loadhpd", ND_LOADHPD },   
    { "__builtin_ia32_loadlpd", ND_LOADLPD },      
    { "__builtin_ia32_movmskpd", ND_MOVMSKPD },    
    { "__builtin_ia32_packsswb128", ND_PACKSSWB128 },  
    { "__builtin_ia32_packssdw128", ND_PACKSSDW128 },        
    { "__builtin_ia32_packuswb128", ND_PACKUSWB128 },       
    { "__builtin_ia32_punpckhbw128", ND_PUNPCKHBW128 },   
    { "__builtin_ia32_punpckhwd128", ND_PUNPCKHWD128 }, 
    { "__builtin_ia32_punpckhdq128", ND_PUNPCKHDQ128 },    
    { "__builtin_ia32_punpckhqdq128", ND_PUNPCKHQDQ128 },
    { "__builtin_ia32_punpcklbw128", ND_PUNPCKLBW128 },          
    { "__builtin_ia32_punpcklwd128", ND_PUNPCKLWD128 },    
    { "__builtin_ia32_punpckldq128", ND_PUNPCKLDQ128 }, 
    { "__builtin_ia32_punpcklqdq128", ND_PUNPCKLQDQ128 },        
    { "__builtin_ia32_paddsb128", ND_PADDSB128 },     
    { "__builtin_ia32_paddsw128", ND_PADDSW128 },   
    { "__builtin_ia32_paddusb128", ND_PADDUSB128 },     
    { "__builtin_ia32_paddusw128", ND_PADDUSW128 },       
    { "__builtin_ia32_psubsb128", ND_PSUBSB128 },     
    { "__builtin_ia32_psubsw128", ND_PSUBSW128 },   
    { "__builtin_ia32_psubusb128", ND_PSUBUSB128 },    
    { "__builtin_ia32_psubusw128", ND_PSUBUSW128 },              
    { "__builtin_ia32_pmaddwd128", ND_PMADDWD128 },  
    { "__builtin_ia32_pmulhw128", ND_PMULHW128 },      
    { "__builtin_ia32_pmuludq", ND_PMULUDQ },          
    { "__builtin_ia32_pmuludq128", ND_PMULUDQ128 },          
    { "__builtin_ia32_psllwi128", ND_PSLLWI128 },   
    { "__builtin_ia32_pslldi128", ND_PSLLDI128 },    
    { "__builtin_ia32_psllqi128", ND_PSLLQI128 },     
    { "__builtin_ia32_psrawi128", ND_PSRAWI128 },          
    { "__builtin_ia32_psradi128", ND_PSRADI128 },     
    { "__builtin_ia32_psrlwi128", ND_PSRLWI128 },    
    { "__builtin_ia32_psrldi128", ND_PSRLDI128 },       
    { "__builtin_ia32_psrlqi128", ND_PSRLQI128 }, 
    { "__builtin_ia32_psllw128", ND_PSLLW128 },   
    { "__builtin_ia32_pslld128", ND_PSLLD128 },       
    { "__builtin_ia32_psllq128", ND_PSLLQ128 },        
    { "__builtin_ia32_psraw128", ND_PSRAW128 },   
    { "__builtin_ia32_psrad128", ND_PSRAD128 },  
    { "__builtin_ia32_psrlw128", ND_PSRLW128 },  
    { "__builtin_ia32_psrld128", ND_PSRLD128 },
    { "__builtin_ia32_psrlq128", ND_PSRLQ128 },        
    { "__builtin_ia32_pandn128", ND_PANDN128 },    
    { "__builtin_ia32_pmaxsw128", ND_PMAXSW128 },   
    { "__builtin_ia32_pmaxub128", ND_PMAXUB128 }, 
    { "__builtin_ia32_pminsw128", ND_PMINSW128 },   
    { "__builtin_ia32_pminub128", ND_PMINUB128 }, 
    { "__builtin_ia32_pmovmskb128", ND_PMOVMSKB128 },  
    { "__builtin_ia32_pmulhuw128", ND_PMULHUW128 }, 
    { "__builtin_ia32_maskmovdqu", ND_MASKMOVDQU },     
    { "__builtin_ia32_pavgb128", ND_PAVGB128 },   
    { "__builtin_ia32_pavgw128", ND_PAVGW128 },   
    { "__builtin_ia32_psadbw128", ND_PSADBW128 }, 
    { "__builtin_ia32_movnti", ND_MOVNTI },   
    { "__builtin_ia32_movnti64", ND_MOVNTI64 },   
    { "__builtin_ia32_movntdq", ND_MOVNTDQ },   
    { "__builtin_ia32_movntpd", ND_MOVNTPD },  
    { "__builtin_parity", ND_PARITY }, 
    { "__builtin_parityl", ND_PARITYL }, 
    { "__builtin_parityll", ND_PARITYLL }, 
    { "__builtin_ia32_mwait", ND_MWAIT }, 
    { "__builtin_ia32_monitor", ND_MONITOR }, 
    { "__builtin_ia32_addsubps", ND_ADDSUBPS }, 
    { "__builtin_ia32_haddps", ND_HADDPS }, 
    { "__builtin_ia32_hsubps", ND_HSUBPS }, 
    { "__builtin_ia32_movshdup", ND_MOVSHDUP }, 
    { "__builtin_ia32_movsldup", ND_MOVSLDUP },
    { "__builtin_ia32_addsubpd", ND_ADDSUBPD }, 
    { "__builtin_ia32_haddpd", ND_HADDPD }, 
    { "__builtin_ia32_hsubpd", ND_HSUBPD },
    { "__builtin_ia32_lddqu", ND_LDDQU },    
    { "__builtin_ia32_phaddw128", ND_PHADDW128 },
    { "__builtin_ia32_phaddd128", ND_PHADDD128 },
    { "__builtin_ia32_phaddsw128", ND_PHADDSW128 },
    { "__builtin_ia32_phaddw", ND_PHADDW },
    { "__builtin_ia32_phaddd", ND_PHADDD },
    { "__builtin_ia32_phaddsw", ND_PHADDSW },    
    { "__builtin_ia32_phsubw128", ND_PHSUBW128 },    
    { "__builtin_ia32_phsubd128", ND_PHSUBD128 },    
    { "__builtin_ia32_phsubsw128", ND_PHSUBSW128 },    
    { "__builtin_ia32_phsubw", ND_PHSUBW },    
    { "__builtin_ia32_phsubd", ND_PHSUBD },    
    { "__builtin_ia32_phsubsw", ND_PHSUBSW },  
    { "__builtin_ia32_pmaddubsw128", ND_PMADDUBSW128 }, 
    { "__builtin_ia32_pmaddubsw", ND_PMADDUBSW }, 
    { "__builtin_ia32_pmulhrsw128", ND_PMULHRSW128 }, 
    { "__builtin_ia32_pmulhrsw", ND_PMULHRSW },
    { "__builtin_ia32_pshufb128", ND_PSHUFB128 },
    { "__builtin_ia32_pshufb", ND_PSHUFB  },
    { "__builtin_ia32_psignb128", ND_PSIGNB128 },
    { "__builtin_ia32_psignw128", ND_PSIGNW128 },
    { "__builtin_ia32_psignd128", ND_PSIGND128 },
    { "__builtin_ia32_psignb", ND_PSIGNB },
    { "__builtin_ia32_psignw", ND_PSIGNW },
    { "__builtin_ia32_psignd", ND_PSIGND },
    { "__builtin_ia32_pabsb128", ND_PABSB128 },
    { "__builtin_ia32_pabsw128", ND_PABSW128 },
    { "__builtin_ia32_pabsd128", ND_PABSD128 },
    { "__builtin_ia32_pabsb", ND_PABSB },
    { "__builtin_ia32_pabsw", ND_PABSW },
    { "__builtin_ia32_pabsd", ND_PABSD },
    { "__builtin_ia32_ptestz128", ND_PTESTZ128 },
    { "__builtin_ia32_ptestc128", ND_PTESTC128 },
    { "__builtin_ia32_ptestnzc128", ND_PTESTNZC128 },
    { "__builtin_ia32_pblendvb128", ND_PBLENDVB128 },
    { "__builtin_ia32_blendvps", ND_BLENDVPS },
    { "__builtin_ia32_blendvpd", ND_BLENDVPD },
    { "__builtin_ia32_pminsb128", ND_PMINSB128 },
    { "__builtin_ia32_pmaxsb128", ND_PMAXSB128 },
    { "__builtin_ia32_pminuw128", ND_PMINUW128 },
    { "__builtin_ia32_pmaxuw128", ND_PMAXUW128 },
    { "__builtin_ia32_pminsd128", ND_PMINSD128 },
    { "__builtin_ia32_pmaxsd128", ND_PMAXSD128 },
    { "__builtin_ia32_pminud128", ND_PMINUD128 },
    { "__builtin_ia32_pmaxud128", ND_PMAXUD128 },
    { "__builtin_ia32_pmuldq128", ND_PMULDQ128 },
    { "__builtin_ia32_phminposuw128", ND_PHMINPOSUW128 },
    { "__builtin_ia32_pmovsxbd128", ND_PMOVSXBD128 },
    { "__builtin_ia32_pmovsxwd128", ND_PMOVSXWD128 },
    { "__builtin_ia32_pmovsxbq128", ND_PMOVSXBQ128 },
    { "__builtin_ia32_pmovsxdq128", ND_PMOVSXDQ128 },
    { "__builtin_ia32_pmovsxwq128", ND_PMOVSXWQ128 },
    { "__builtin_ia32_pmovsxbw128", ND_PMOVSXBW128 },
    { "__builtin_ia32_pmovzxbd128", ND_PMOVZXBD128 },
    { "__builtin_ia32_pmovzxwd128", ND_PMOVZXWD128 },
    { "__builtin_ia32_pmovzxbq128", ND_PMOVZXBQ128 },
    { "__builtin_ia32_pmovzxdq128", ND_PMOVZXDQ128 },
    { "__builtin_ia32_pmovzxwq128", ND_PMOVZXWQ128 },
    { "__builtin_ia32_pmovzxbw128", ND_PMOVZXBW128 },    
    { "__builtin_ia32_packusdw128", ND_PACKUSDW128 },  
    { "__builtin_ia32_movntdqa", ND_MOVNTDQA },    
    { "__builtin_ia32_crc32qi", ND_CRC32QI },    
    { "__builtin_ia32_crc32hi", ND_CRC32HI },    
    { "__builtin_ia32_crc32si", ND_CRC32SI },    
    { "__builtin_ia32_crc32di", ND_CRC32DI },
    { "__builtin_ia32_pshufd", ND_PSHUFD },
    { "__builtin_prefetch", ND_PREFETCH },
    { "__builtin_ia32_rdtsc", ND_RDTSC },
    { "__builtin_ia32_readeflags_u64", ND_READEFLAGS_U64 },
    { "__builtin_ia32_rdsspq", ND_RDSSPQ },   
    { "__builtin_ia32_saveprevssp", ND_SAVEPREVSSP },
    { "__builtin_ia32_setssbsy", ND_SETSSBSY },
    { "__builtin_ia32_slwpcb", ND_SLWPCB },
    { "__builtin_ia32_rdpkru", ND_RDPKRU },
    { "__builtin_ia32_xbegin", ND_XBEGIN },
    { "__builtin_ia32_xend", ND_XEND },    
    { "__builtin_ia32_serialize", ND_SERIALIZE },    
    { "__builtin_ia32_xsusldtrk", ND_XSUSLDTRK },
    { "__builtin_ia32_xresldtrk", ND_XRESLDTRK },
    { "__builtin_ia32_clui", ND_CLUI },
    { "__builtin_ia32_stui", ND_STUI },
    { "__builtin_ia32_testui", ND_TESTUI },
    { "__builtin_ia32_wbnoinvd", ND_WBNOINVD },
    { "__builtin_ia32_xtest", ND_XTEST },
    { "__builtin_ia32_wbinvd", ND_WBINVD },
    { "__builtin_ia32_rdpid", ND_RDPID },
    { "__builtin_ia32_rdfsbase32", ND_RDFSBASE32 },
    { "__builtin_ia32_rdfsbase64", ND_RDFSBASE64 },
    { "__builtin_ia32_rdgsbase32", ND_RDGSBASE32 },
    { "__builtin_ia32_rdgsbase64", ND_RDGSBASE64 },
    { "__builtin_ia32_vzeroall", ND_VZEROALL },
    { "__builtin_ia32_vzeroupper", ND_VZEROUPPER },
    { "__builtin_ia32_femms", ND_FEMMS },
    { "__builtin_ia32_bsrsi", ND_BSRSI },
    { "__builtin_ia32_rdpmc", ND_RDPMC },
    { "__builtin_ia32_rdtscp", ND_RDTSCP },
    { "__builtin_ia32_rolqi", ND_ROLQI },
    { "__builtin_ia32_rolhi", ND_ROLHI },
    { "__builtin_ia32_rorqi", ND_RORQI },
    { "__builtin_ia32_rorhi", ND_RORHI },
    { "__builtin_ia32_bsrdi", ND_BSRDI },    
    { "__builtin_ia32_writeeflags_u64", ND_WRITEEFLAGS_U64 },
    { "__builtin_ia32_incsspq", ND_INCSSPQ },
    { "__builtin_ia32_rstorssp", ND_RSTORSSP },
    { "__builtin_ia32_wrssd", ND_WRSSD },
    { "__builtin_ia32_wrssq", ND_WRSSQ },
    { "__builtin_ia32_wrussd", ND_WRUSSD },
    { "__builtin_ia32_wrussq", ND_WRUSSQ },
    { "__builtin_ia32_clrssbsy", ND_CLRSSBSY },
    { "__builtin_ia32_sbb_u32", ND_SBB_U32 },
    { "__builtin_ia32_addcarryx_u32", ND_ADDCARRYX_U32 },
    { "__builtin_ia32_sbb_u64", ND_SBB_U64 },
    { "__builtin_ia32_addcarryx_u64", ND_ADDCARRYX_U64 },    
    { "__builtin_ia32_tzcnt_u16", ND_TZCNT_U16 },
    { "__builtin_ia32_bextr_u32", ND_BEXTR_U32 },
    { "__builtin_ia32_psubusb256", ND_PSUBUSB256 },
    { "__builtin_ia32_pcmpgtb256_mask", ND_PCMPGTB256_MASK },
    { "__builtin_ia32_pshufb256", ND_PSHUFB256 },
};


static int builtin_enum(Token *tok) {
    for (size_t i = 0; i < sizeof(builtin_table) / sizeof(builtin_table[0]); i++) {
        if (equal(tok, builtin_table[i].name))
            return builtin_table[i].node_kind;
    }
    return -1; // not found
}

// scalar_to_vector now marks the node as a scalar promotion
static Node *scalar_to_vector(Node *scalar, Type *vec_ty) {
    Node *n = new_unary(ND_CAST, scalar, scalar->tok);
    n->ty = vec_ty;                  // target vector type
    n->is_scalar_promoted = true;     // renamed flag for clarity
    return n;
}

// Promote scalars to vectors for a binary operation
static void promote_scalar_to_vector(Node *node) {
    add_type(node->lhs);
    add_type(node->rhs);

    if (is_vector(node->rhs->ty) && !is_vector(node->lhs->ty)) {
        node->lhs = scalar_to_vector(node->lhs, node->rhs->ty);
        node->lhs->is_scalar_promoted = true;
    }

    if (is_vector(node->lhs->ty) && !is_vector(node->rhs->ty)) {
        node->rhs = scalar_to_vector(node->rhs, node->lhs->ty);
        node->rhs->is_scalar_promoted = true;
    }
}

static Node *ParseSyncBoolCAS(NodeKind kind, Token *tok, Token **rest) {
    Node *node = new_node(kind, tok);
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    node->cas_ptr = assign(&tok, tok);
    add_type(node->cas_ptr);
    tok = skip(tok, ",", ctx);
    node->cas_expected = assign(&tok, tok);
    add_type(node->cas_expected);
    tok = skip(tok, ",", ctx);
    node->cas_desired = assign(&tok, tok);
    add_type(node->cas_desired);
    *rest = skip(tok, ")", ctx);
    node->ty = ty_bool;
    return node;
}

static Node *ParseSyncFetch(NodeKind kind, Token *tok, Token **rest) {
    tok = skip(tok->next, "(", ctx);
    Node *ptr = assign(&tok, tok);
    tok = skip(tok, ",", ctx);
    Node *val = assign(&tok, tok);
    add_type(val);
    int memorder = __ATOMIC_SEQ_CST; 
    if (equal(tok, ",")) {
        tok = skip(tok, ",", ctx);
        memorder = const_expr(&tok, tok); 
    }
    Node *node = new_node(kind, tok);  
    node->lhs = ptr;
    node->rhs = val;
    node->memorder = memorder;
    node->atomic_fetch = true;       
    *rest = skip(tok, ")", ctx);
    return node;
}

static Node *ParseAtomicBitwise(NodeKind kind, Token *tok, Token **rest) {
    SET_CTX(ctx);
    tok = skip(tok->next, "(", ctx);
    Node *ptr = assign(&tok, tok);     
    tok = skip(tok, ",", ctx);
    Node *val = assign(&tok, tok);     
    add_type(val);
    int memorder = __ATOMIC_SEQ_CST; 
    if (equal(tok, ",")) {
        tok = skip(tok, ",", ctx);
        memorder = const_expr(&tok, tok); 
    }
    Node *node = new_node(kind, tok);
    node->lhs = ptr;
    node->rhs = val;
    node->memorder = memorder;
    node->atomic_fetch = true;
    *rest = skip(tok, ")", ctx);
    return node;
}

static bool is_c99_or_later(void) {
  switch (current_std) {
  case STD_C99:
  case STD_C11:
  case STD_C17:
  case STD_C23:
  case STD_GNU99:
  case STD_GNU11:
  case STD_GNU17:
  case STD_GNU23:
    return true;
  default:
    return false;
  }
}
