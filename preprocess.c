// This file implements the C preprocessor.
//
// The preprocessor takes a list of tokens as an input and returns a
// new list of tokens as an output.
//
// The preprocessing language is designed in such a way that that's
// guaranteed to stop even if there is a recursive macro.
// Informally speaking, a macro is applied only once for each token.
// That is, if a macro token T appears in a result of direct or
// indirect macro expansion of T, T won't be expanded any further.
// For example, if T is defined as U, and U is defined as T, then
// token T is expanded to U and then to T and the macro expansion
// stops at that point.
//
// To achieve the above behavior, we attach for each token a set of
// macro names from which the token is expanded. The set is called
// "hideset". Hideset is initially empty, and every time we expand a
// macro, the macro name is added to the resulting tokens' hidesets.
//
// The above macro expansion algorithm is explained in this document
// written by Dave Prossor, which is used as a basis for the
// standard's wording:
// https://github.com/rui314/chibicc/wiki/cpp.algo.pdf

#include "chibicc.h"
#define PREPROCESS_C "preprocess.c"

typedef struct MacroParam MacroParam;
struct MacroParam
{
  MacroParam *next;
  char *name;
};

typedef struct MacroArg MacroArg;
struct MacroArg
{
  MacroArg *next;
  char *name;
  bool is_va_args;
  Token *tok;
};

typedef Token *macro_handler_fn(Token *);

typedef struct Macro Macro;
struct Macro
{
  char *name;
  bool is_objlike; // Object-like or function-like or attribut-like
  MacroParam *params;
  char *va_args_name;
  Token *body;
  macro_handler_fn *handler;
};

// `#if` can be nested, so we use a stack to manage nested `#if`s.
typedef struct CondIncl CondIncl;
struct CondIncl
{
  CondIncl *next;
  enum
  {
    IN_THEN,
    IN_ELIF,
    IN_ELSE
  } ctx;
  Token *tok;
  bool included;
};

typedef struct Hideset Hideset;
struct Hideset
{
  Hideset *next;
  char *name;
};

static HashMap macros;
static CondIncl *cond_incl;
static HashMap pragma_once;
static int include_next_idx;

//ISS-142
extern bool opt_E;

static Token *preprocess2(Token *tok);
static Macro *find_macro(Token *tok);
static void join_adjacent_string_literals(Token *tok);

static bool is_hash(Token *tok)
{
  return tok->at_bol && equal(tok, "#");
}

// Some preprocessor directives such as #include allow extraneous
// tokens before newline. This function skips such tokens.
static Token *skip_line(Token *tok)
{
  if (tok->at_bol)
    return tok;
  warn_tok(tok, "extra token");
  while (!tok->at_bol)
    tok = tok->next;
  return tok;
}

static Token *copy_token(Token *tok)
{
  Token *t = calloc(1, sizeof(Token));
  if (t == NULL)
    error("%s: in copy_token : t is null", PREPROCESS_C);
  *t = *tok;
  t->next = NULL;
  return t;
}

static Token *new_eof(Token *tok)
{
  Token *t = copy_token(tok);
  t->kind = TK_EOF;
  t->len = 0;
  return t;
}

static Hideset *new_hideset(char *name)
{
  Hideset *hs = calloc(1, sizeof(Hideset));
  if (hs == NULL)
    error("%s: in new_hideset : hs is null", PREPROCESS_C);
  hs->name = name;
  return hs;
}

static Hideset *hideset_union(Hideset *hs1, Hideset *hs2)
{
  Hideset head = {};
  Hideset *cur = &head;

  for (; hs1; hs1 = hs1->next)
    cur = cur->next = new_hideset(hs1->name);
  cur->next = hs2;
  return head.next;
}

static bool hideset_contains(Hideset *hs, char *s, int len)
{
  for (; hs; hs = hs->next)
    if (strlen(hs->name) == len && !strncmp(hs->name, s, len))
      return true;
  return false;
}

static Hideset *hideset_intersection(Hideset *hs1, Hideset *hs2)
{
  Hideset head = {};
  Hideset *cur = &head;

  for (; hs1; hs1 = hs1->next)
    if (hideset_contains(hs2, hs1->name, strlen(hs1->name)))
      cur = cur->next = new_hideset(hs1->name);
  return head.next;
}

static Token *add_hideset(Token *tok, Hideset *hs)
{
  Token head = {};
  Token *cur = &head;

  for (; tok; tok = tok->next)
  {
    Token *t = copy_token(tok);
    t->hideset = hideset_union(t->hideset, hs);
    cur = cur->next = t;
  }
  return head.next;
}

// Append tok2 to the end of tok1.
static Token *append(Token *tok1, Token *tok2)
{
  if (tok1->kind == TK_EOF)
    return tok2;

  Token head = {};
  Token *cur = &head;

  for (; tok1->kind != TK_EOF; tok1 = tok1->next)
    cur = cur->next = copy_token(tok1);
  cur->next = tok2;
  return head.next;
}

static Token *skip_cond_incl2(Token *tok)
{
  while (tok->kind != TK_EOF)
  {
    if (is_hash(tok) &&
        (equal(tok->next, "if") || equal(tok->next, "ifdef") ||
         equal(tok->next, "ifndef")))
    {
      tok = skip_cond_incl2(tok->next->next);
      continue;
    }
    if (is_hash(tok) && equal(tok->next, "endif"))
      return tok->next->next;
    tok = tok->next;
  }
  return tok;
}

// Skip until next `#else`, `#elif` or `#endif`.
// Nested `#if` and `#endif` are skipped.
static Token *skip_cond_incl(Token *tok)
{

  while (tok->kind != TK_EOF)
  {
    if (is_hash(tok) &&
        (equal(tok->next, "if") || equal(tok->next, "ifdef") ||
         equal(tok->next, "ifndef")))
    {
      tok = skip_cond_incl2(tok->next->next);
      continue;
    }

    if (is_hash(tok) &&
        (equal(tok->next, "elif") || equal(tok->next, "else") ||
         equal(tok->next, "endif")))
      break;
    tok = tok->next;
  }
  return tok;
}

// Double-quote a given string and returns it.
static char *quote_string(char *str)
{
  int bufsize = 3;
  for (int i = 0; str[i]; i++)
  {
    if (str[i] == '\\' || str[i] == '"')
      bufsize++;
    bufsize++;
  }

  char *buf = calloc(1, bufsize);
  if (buf == NULL)
    error("%s: in quote_string : buf is null", PREPROCESS_C);

  char *p = buf;
  *p++ = '"';
  for (int i = 0; str[i]; i++)
  {
    if (str[i] == '\\' || str[i] == '"')
      *p++ = '\\';
    *p++ = str[i];
  }
  *p++ = '"';
  *p++ = '\0';
  return buf;
}

static Token *new_str_token(char *str, Token *tmpl)
{
  char *buf = quote_string(str);
  return tokenize(new_file(tmpl->file->name, tmpl->file->file_no, buf));
}

// Copy all tokens until the next newline, terminate them with
// an EOF token and then returns them. This function is used to
// create a new list of tokens for `#if` arguments.
static Token *copy_line(Token **rest, Token *tok)
{
  Token head = {};
  Token *cur = &head;

  for (; !tok->at_bol; tok = tok->next)
    cur = cur->next = copy_token(tok);

  cur->next = new_eof(tok);
  *rest = tok;
  return head.next;
}

static Token *new_num_token(int val, Token *tmpl)
{
  char *buf = format("%d\n", val);
  return tokenize(new_file(tmpl->file->name, tmpl->file->file_no, buf));
}

static Token *read_const_expr(Token **rest, Token *tok)
{
  tok = copy_line(rest, tok);

  Token head = {};
  Token *cur = &head;

  while (tok->kind != TK_EOF)
  {
    // "defined(foo)" or "defined foo" becomes "1" if macro "foo"
    // is defined. Otherwise "0".
    if (equal(tok, "defined") || equal(tok, "__has_attribute"))
    {
      Token *start = tok;
      bool has_paren = consume(&tok, tok->next, "(");

      if (tok->kind != TK_IDENT)
        error_tok(start, "%s: in read_const_expr : macro name must be an identifier", PREPROCESS_C);
      Macro *m = find_macro(tok);
      tok = tok->next;

      if (has_paren)
        tok = skip(tok, ")");

      cur = cur->next = new_num_token(m ? 1 : 0, start);
      continue;
    }
    cur = cur->next = tok;
    tok = tok->next;
  }

  cur->next = tok;
  return head.next;
}

// Read and evaluate a constant expression.
static long eval_const_expr(Token **rest, Token *tok)
{
  Token *start = tok;
  Token *expr = read_const_expr(rest, tok->next);
  expr = preprocess2(expr);

  if (expr->kind == TK_EOF)
    error_tok(start, "%s: in eval_const_expr : no expression", PREPROCESS_C);

  // [https://www.sigbus.info/n1570#6.10.1p4] The standard requires
  // we replace remaining non-macro identifiers with "0" before
  // evaluating a constant expression. For example, `#if foo` is
  // equivalent to `#if 0` if foo is not defined.
  for (Token *t = expr; t->kind != TK_EOF; t = t->next)
  {
    if (t->kind == TK_IDENT)
    {
      Token *next = t->next;

      *t = *new_num_token(0, t);
      t->next = next;
    }
  }

  // Convert pp-numbers to regular numbers
  convert_pp_tokens(expr);

  Token *rest2;
  long val = const_expr(&rest2, expr);
  if (rest2->kind != TK_EOF)
    error_tok(rest2, "%s: in eval_const_expr : extra token", PREPROCESS_C);
  return val;
}

static CondIncl *push_cond_incl(Token *tok, bool included)
{
  CondIncl *ci = calloc(1, sizeof(CondIncl));
  if (ci == NULL)
    error("%s: in push_cond_incl : ci is null", PREPROCESS_C);
  ci->next = cond_incl;
  ci->ctx = IN_THEN;
  ci->tok = tok;
  ci->included = included;
  cond_incl = ci;
  return ci;
}

static Macro *find_macro(Token *tok)
{

  if (tok->kind != TK_IDENT)
    return NULL;
  return hashmap_get2(&macros, tok->loc, tok->len);
}

static Macro *add_macro(char *name, bool is_objlike, Token *body)
{
  Macro *m = calloc(1, sizeof(Macro));
  if (m == NULL)
    error("%s: in add_macro : m is null", PREPROCESS_C);
  m->name = name;
  m->is_objlike = is_objlike;
  m->body = body;
  hashmap_put(&macros, name, m);
  return m;
}

static MacroParam *read_macro_params(Token **rest, Token *tok, char **va_args_name)
{
  MacroParam head = {};
  MacroParam *cur = &head;

  while (!equal(tok, ")"))
  {
    if (cur != &head)
      tok = skip(tok, ",");

    if (equal(tok, "..."))
    {
      *va_args_name = "__VA_ARGS__";
      *rest = skip(tok->next, ")");
      return head.next;
    }

    if (tok->kind != TK_IDENT)
      error_tok(tok, "%s in read_macro_params : expected an identifier", PREPROCESS_C);

    if (equal(tok->next, "..."))
    {
      *va_args_name = strndup(tok->loc, tok->len);
      *rest = skip(tok->next->next, ")");
      return head.next;
    }

    MacroParam *m = calloc(1, sizeof(MacroParam));
    if (m == NULL)
      error("%s: in read_macro_params : m is null", PREPROCESS_C);

    m->name = strndup(tok->loc, tok->len);
    cur = cur->next = m;
    tok = tok->next;
  }

  *rest = tok->next;
  return head.next;
}

static void read_macro_definition(Token **rest, Token *tok)
{

  if (tok->kind != TK_IDENT)
    error_tok(tok, "%s: in read_macro_definition : macro name must be an identifier", PREPROCESS_C);

  char *name = strndup(tok->loc, tok->len);
  tok = tok->next;
  if (!tok->has_space && equal(tok, "("))
  {
    // Function-like macro
    char *va_args_name = NULL;
    MacroParam *params = read_macro_params(&tok, tok->next, &va_args_name);
    Macro *m = add_macro(name, false, copy_line(rest, tok));
    m->params = params;
    m->va_args_name = va_args_name;
  }
  else
  {
    // Object-like macro
    add_macro(name, true, copy_line(rest, tok));
  }
}

static MacroArg *read_macro_arg_one(Token **rest, Token *tok, bool read_rest)
{
  Token head = {};
  Token *cur = &head;
  int level = 0;

  for (;;)
  {
    if (level == 0 && equal(tok, ")"))
      break;
    if (level == 0 && !read_rest && equal(tok, ","))
      break;

    if (tok->kind == TK_EOF)
      error_tok(tok, "%s: in read_macro_arg_one : premature end of input", PREPROCESS_C);
    

    if (equal(tok, "("))
      level++;
    else if (equal(tok, ")"))
      level--;
    cur = cur->next = copy_token(tok);
    tok = tok->next;
  }

  cur->next = new_eof(tok);


  MacroArg *arg = calloc(1, sizeof(MacroArg));
  if (arg == NULL)
    error("%s: in read_macro_arg_one : arg is null", PREPROCESS_C);

  arg->tok = head.next;
  *rest = tok;
  return arg;
}

static MacroArg *
read_macro_args(Token **rest, Token *tok, MacroParam *params, char *va_args_name)
{
  Token *start = tok;
  tok = tok->next->next;

  MacroArg head = {};
  MacroArg *cur = &head;

  MacroParam *pp = params;
  for (; pp; pp = pp->next)
  {
    if (cur != &head)
      tok = skip(tok, ",");
    cur = cur->next = read_macro_arg_one(&tok, tok, false);
    cur->name = pp->name;
  }

  if (va_args_name)
  {
    MacroArg *arg;
    if (equal(tok, ")"))
    {
      arg = calloc(1, sizeof(MacroArg));
      if (arg == NULL)
        error("%s: in read_macro_args : arg is null", PREPROCESS_C);

      arg->tok = new_eof(tok);
    }
    else
    {
      if (pp != params)
        tok = skip(tok, ",");
      arg = read_macro_arg_one(&tok, tok, true);
    }
    arg->name = va_args_name;
    ;
    arg->is_va_args = true;
    cur = cur->next = arg;
  }
  else if (pp)
  {
    error_tok(start, "%s: in read_macro_args : too many arguments", PREPROCESS_C);
  }

  skip(tok, ")");
  *rest = tok;
  return head.next;
}

static MacroArg *find_arg(MacroArg *args, Token *tok)
{
  for (MacroArg *ap = args; ap; ap = ap->next)
    if (tok->len == strlen(ap->name) && !strncmp(tok->loc, ap->name, tok->len))
      return ap;
  return NULL;
}

// Concatenates all tokens in `tok` and returns a new string.
static char *join_tokens(Token *tok, Token *end)
{
  // Compute the length of the resulting token.
  int len = 1;
  for (Token *t = tok; t != end && t->kind != TK_EOF; t = t->next)
  {
    if (t != tok && t->has_space)
      len++;
    len += t->len;
  }

  char *buf = calloc(1, len);
  if (buf == NULL)
    error("%s: in join_tokens : buf is null", PREPROCESS_C);

  // Copy token texts.
  int pos = 0;
  for (Token *t = tok; t != end && t->kind != TK_EOF; t = t->next)
  {
    if (t != tok && t->has_space)
      buf[pos++] = ' ';
    strncpy(buf + pos, t->loc, t->len);
    pos += t->len;
  }
  buf[pos] = '\0';
  return buf;
}

// Concatenates all tokens in `arg` and returns a new string token.
// This function is used for the stringizing operator (#).
static Token *stringize(Token *hash, Token *arg)
{
  // Create a new string token. We need to set some value to its
  // source location for error reporting function, so we use a macro
  // name token as a template.
  char *s = join_tokens(arg, NULL);
  return new_str_token(s, hash);
}

// Concatenate two tokens to create a new token.
static Token *paste(Token *lhs, Token *rhs)
{
  // Paste the two tokens.
  char *buf = format("%.*s%.*s", lhs->len, lhs->loc, rhs->len, rhs->loc);
  // Tokenize the resulting string.
  Token *tok = tokenize(new_file(lhs->file->name, lhs->file->file_no, buf));
  if (tok->next->kind != TK_EOF)
    error_tok(lhs, "%s: in paste : pasting forms '%s', an invalid token", PREPROCESS_C, buf);
  return tok;
}

static bool has_varargs(MacroArg *args)
{
  for (MacroArg *ap = args; ap; ap = ap->next)
    if (!strcmp(ap->name, "__VA_ARGS__"))
      return ap->tok->kind != TK_EOF;
  return false;
}

// Replace func-like macro parameters with given arguments.
static Token *subst(Token *tok, MacroArg *args)
{
  Token head = {};
  Token *cur = &head;

  while (tok->kind != TK_EOF)
  {
    // "#" followed by a parameter is replaced with stringized actuals.
    if (equal(tok, "#"))
    {
      MacroArg *arg = find_arg(args, tok->next);
      if (!arg)
        error_tok(tok->next, "%s: in subst : '#' is not followed by a macro parameter", PREPROCESS_C);
      cur = cur->next = stringize(tok, arg->tok);
      tok = tok->next->next;
      continue;
    }

    // [GNU] If __VA_ARG__ is empty, `,##__VA_ARGS__` is expanded
    // to the empty token list. Otherwise, its expaned to `,` and
    // __VA_ARGS__.
    if (equal(tok, ",") && equal(tok->next, "##"))
    {
      MacroArg *arg = find_arg(args, tok->next->next);
      if (arg && arg->is_va_args)
      {
        if (arg->tok->kind == TK_EOF)
        {
          tok = tok->next->next->next;
        }
        else
        {
          cur = cur->next = copy_token(tok);
          tok = tok->next->next;
        }
        continue;
      }
    }

    if (equal(tok, "##"))
    {
      if (cur == &head)
        error_tok(tok, "%s: in subst : '##' cannot appear at start of macro expansion", PREPROCESS_C);

      if (tok->next->kind == TK_EOF)
        error_tok(tok, "%s: in subst : '##' cannot appear at end of macro expansion", PREPROCESS_C);

      MacroArg *arg = find_arg(args, tok->next);
      if (arg)
      {
        if (arg->tok->kind != TK_EOF)
        {
          *cur = *paste(cur, arg->tok);
          for (Token *t = arg->tok->next; t->kind != TK_EOF; t = t->next)
            cur = cur->next = copy_token(t);
        }
        tok = tok->next->next;
        continue;
      }
      *cur = *paste(cur, tok->next);
      tok = tok->next->next;
      continue;
    }

    MacroArg *arg = find_arg(args, tok);

    if (arg && equal(tok->next, "##"))
    {
      Token *rhs = tok->next->next;
      if (arg->tok->kind == TK_EOF)
      {
        MacroArg *arg2 = find_arg(args, rhs);
        if (arg2)
        {
          for (Token *t = arg2->tok; t->kind != TK_EOF; t = t->next)
            cur = cur->next = copy_token(t);
        }
        else
        {
          cur = cur->next = copy_token(rhs);
        }
        tok = rhs->next;
        continue;
      }

      for (Token *t = arg->tok; t->kind != TK_EOF; t = t->next)
        cur = cur->next = copy_token(t);
      tok = tok->next;
      continue;
    }

    // If __VA_ARG__ is empty, __VA_OPT__(x) is expanded to the
    // empty token list. Otherwise, __VA_OPT__(x) is expanded to x.
    if (equal(tok, "__VA_OPT__") && equal(tok->next, "("))
    {
      MacroArg *arg = read_macro_arg_one(&tok, tok->next->next, true);
      if (has_varargs(args))
        for (Token *t = arg->tok; t->kind != TK_EOF; t = t->next)
          cur = cur->next = t;
      tok = skip(tok, ")");
      continue;
    }

    // Handle a macro token. Macro arguments are completely macro-expanded
    // before they are substituted into a macro body.
    if (arg)
    {
      Token *t = preprocess2(arg->tok);
      // t->at_bol = tok->at_bol;
      t->has_space = tok->has_space;
      for (; t->kind != TK_EOF; t = t->next)
        cur = cur->next = copy_token(t);
      tok = tok->next;
      continue;
    }

    // Handle a non-macro token.
    cur = cur->next = copy_token(tok);
    tok = tok->next;
    continue;
  }

  cur->next = tok;
  return head.next;
}

// If tok is a macro, expand it and return true.
// Otherwise, do nothing and return false.
static bool expand_macro(Token **rest, Token *tok)
{

  if (hideset_contains(tok->hideset, tok->loc, tok->len))
    return false;

  Macro *m = find_macro(tok);
  if (!m)
    return false;

  // Built-in dynamic macro application such as __LINE__
  if (m->handler)
  {
    *rest = m->handler(tok);
    (*rest)->next = tok->next;
    return true;
  }

  // Object-like macro application
  if (m->is_objlike)
  {
    Hideset *hs = hideset_union(tok->hideset, new_hideset(m->name));
    Token *body = add_hideset(m->body, hs);
    for (Token *t = body; t->kind != TK_EOF; t = t->next)
    {
      t->origin = tok;
    }
    *rest = append(body, tok->next);
    //(*rest)->at_bol = tok->at_bol;
    (*rest)->has_space = tok->has_space;
    return true;
  }

  // If a funclike macro token is not followed by an argument list,
  // treat it as a normal identifier.
  if (!equal(tok->next, "("))
    return false;

  // Function-like macro application
  Token *macro_token = tok;
  MacroArg *args = read_macro_args(&tok, tok, m->params, m->va_args_name);
  Token *rparen = tok;
  // Tokens that consist a func-like macro invocation may have different
  // hidesets, and if that's the case, it's not clear what the hideset
  // for the new tokens should be. We take the interesection of the
  // macro token and the closing parenthesis and use it as a new hideset
  // as explained in the Dave Prossor's algorithm.
  Hideset *hs = hideset_intersection(macro_token->hideset, rparen->hideset);
  hs = hideset_union(hs, new_hideset(m->name));
  Token *body = subst(m->body, args);
  body = add_hideset(body, hs);
  
  for (Token *t = body; t->kind != TK_EOF; t = t->next)
  {
    t->origin = macro_token;

  }
  *rest = append(body, tok->next);
  //#issue 108 not sure why but this corrupts some tokens "#" that are not recognized starting at beginning of the line.
  // (*rest)->at_bol = macro_token->at_bol;
  // (*rest)->has_space = macro_token->has_space;
  return true;
}

char *search_include_paths(char *filename)
{
  if (filename[0] == '/')
    return filename;

  static HashMap cache;
  char *cached = hashmap_get(&cache, filename);
  if (cached)
    return cached;

  // Search a file from the include paths.
  for (int i = 0; i < include_paths.len; i++)
  {
    char *path = format("%s/%s", include_paths.data[i], filename);
    // printf("%s\n", path);
    if (!file_exists(path))
      continue;
    hashmap_put(&cache, filename, path);
    include_next_idx = i + 1;
    return path;
  }
  return NULL;
}

static char *search_include_next(char *filename)
{
  for (; include_next_idx < include_paths.len; include_next_idx++)
  {
    char *path = format("%s/%s", include_paths.data[include_next_idx], filename);
    if (file_exists(path))
      return path;
  }
  return NULL;
}

// Read an #include argument.
static char *read_include_filename(Token **rest, Token *tok, bool *is_dquote)
{
  // Pattern 1: #include "foo.h"
  if (tok->kind == TK_STR)
  {
    // A double-quoted filename for #include is a special kind of
    // token, and we don't want to interpret any escape sequences in it.
    // For example, "\f" in "C:\foo" is not a formfeed character but
    // just two non-control characters, backslash and f.
    // So we don't want to use token->str.
    *is_dquote = true;
    *rest = skip_line(tok->next);
    return strndup(tok->loc + 1, tok->len - 2);
  }

  // Pattern 2: #include <foo.h>
  if (equal(tok, "<"))
  {
    // Reconstruct a filename from a sequence of tokens between
    // "<" and ">".
    Token *start = tok;

    // Find closing ">".
    for (; !equal(tok, ">"); tok = tok->next)
      if (tok->at_bol || tok->kind == TK_EOF)
        error_tok(tok, "%s: in read_include_filename : expected '>'", PREPROCESS_C);

    *is_dquote = false;
    *rest = skip_line(tok->next);
    return join_tokens(start->next, tok);
  }

  // Pattern 3: #include FOO
  // In this case FOO must be macro-expanded to either
  // a single string token or a sequence of "<" ... ">".
  if (tok->kind == TK_IDENT)
  {
    Token *tok2 = preprocess2(copy_line(rest, tok));
    return read_include_filename(&tok2, tok2, is_dquote);
  }

  error_tok(tok, "%s: in read_include_filename : expected a filename", PREPROCESS_C);
}

// Detect the following "include guard" pattern.
//
//   #ifndef FOO_H
//   #define FOO_H
//   ...
//   #endif
static char *detect_include_guard(Token *tok)
{
  // Detect the first two lines.
  if (!is_hash(tok) || !equal(tok->next, "ifndef"))
    return NULL;
  tok = tok->next->next;

  if (tok->kind != TK_IDENT)
    return NULL;

  char *macro = strndup(tok->loc, tok->len);
  tok = tok->next;

  if (!is_hash(tok) || !equal(tok->next, "define") || !equal(tok->next->next, macro))
    return NULL;

  // Read until the end of the file.
  while (tok->kind != TK_EOF)
  {
    if (!is_hash(tok))
    {
      tok = tok->next;
      continue;
    }

    if (equal(tok->next, "endif") && tok->next->next->kind == TK_EOF)
      return macro;

    if (equal(tok, "if") || equal(tok, "ifdef") || equal(tok, "ifndef"))
      tok = skip_cond_incl(tok->next);
    else
      tok = tok->next;
  }
  return NULL;
}

static Token *include_file(Token *tok, char *path, Token *filename_tok)
{
  // Check for "#pragma once"
  if (hashmap_get(&pragma_once, path))
    return tok;

  // If we read the same file before, and if the file was guarded
  // by the usual #ifndef ... #endif pattern, we may be able to
  // skip the file without opening it.
  static HashMap include_guards;
  char *guard_name = hashmap_get(&include_guards, path);
  if (guard_name && hashmap_get(&macros, guard_name))
    return tok;

  Token *tok2 = tokenize_file(path);
  if (!tok2)
    error_tok(filename_tok, "%s: in include_file : %s: cannot open file: %s", PREPROCESS_C, path, strerror(errno));

  guard_name = detect_include_guard(tok2);
  if (guard_name)
    hashmap_put(&include_guards, path, guard_name);

  return append(tok2, tok);
}

// Read #line arguments
static void read_line_marker(Token **rest, Token *tok)
{
  Token *start = tok;
  bool isReadLine = true;
  tok = preprocess(copy_line(rest, tok), isReadLine);
  // if (isDebug && f != NULL)
  //   print_debug_tokens(PREPROCESS_C, "read_line_marker", tok);

  if (tok->kind != TK_NUM && tok->ty->kind != TY_INT)
    error_tok(tok, "%s: in read_line_marker : invalid line marker", PREPROCESS_C);

  // fix issue with negative number that cause Assembler less number than one
  start->file->line_delta = tok->val - start->line_no;

  tok = tok->next;
  if (tok->kind == TK_EOF)
    return;

  if (tok->kind != TK_STR)
    error_tok(tok, "%s: in read_line_marker : filename expected", PREPROCESS_C);
  start->file->display_name = tok->str;
}

// Visit all tokens in `tok` while evaluating preprocessing
// macros and directives.
static Token *preprocess2(Token *tok)
{
  Token head = {};
  Token *cur = &head;

  while (tok->kind != TK_EOF)
  {

    // // // If it is a macro, expand it.
    if (expand_macro(&tok, tok))
      continue;

    // Pass through if it is not a "#".
    if (!is_hash(tok))
    {
      tok->line_delta = tok->file->line_delta;
      tok->filename = tok->file->display_name;
      cur = cur->next = tok;
      tok = tok->next;
      continue;
    }

    Token *start = tok;
    tok = tok->next;
    if (equal(tok, "include"))
    {
      bool is_dquote;
      char *filename = read_include_filename(&tok, tok->next, &is_dquote);

      if (filename[0] != '/' && is_dquote)
      {
        char *path = format("%s/%s", dirname(strdup(start->file->name)), filename);
        if (file_exists(path))
        {
          tok = include_file(tok, path, start->next->next);
          continue;
        }
      }

      char *path = search_include_paths(filename);
      tok = include_file(tok, path ? path : filename, start->next->next);
      continue;
    }

    if (equal(tok, "include_next"))
    {
      bool ignore;
      char *filename = read_include_filename(&tok, tok->next, &ignore);
      char *path = search_include_next(filename);
      tok = include_file(tok, path ? path : filename, start->next->next);
      continue;
    }
    if (equal(tok, "define"))
    {
      read_macro_definition(&tok, tok->next);
      continue;
    }

    if (equal(tok, "undef"))
    {
      tok = tok->next;
      if (tok->kind != TK_IDENT)
        error_tok(tok, "%s: in preprocess2 : macro name must be an identifier", PREPROCESS_C);
      undef_macro(strndup(tok->loc, tok->len));
      tok = skip_line(tok->next);
      continue;
    }

    if (equal(tok, "if"))
    {
      long val = eval_const_expr(&tok, tok);
      push_cond_incl(start, val);
      if (!val)
        tok = skip_cond_incl(tok);
      continue;
    }

    if (equal(tok, "ifdef"))
    {
      bool defined = find_macro(tok->next);
      push_cond_incl(tok, defined);
      tok = skip_line(tok->next->next);
      if (!defined)
        tok = skip_cond_incl(tok);
      continue;
    }

    if (equal(tok, "ifndef"))
    {
      bool defined = find_macro(tok->next);
      push_cond_incl(tok, !defined);
      tok = skip_line(tok->next->next);
      if (defined)
        tok = skip_cond_incl(tok);
      continue;
    }

    if (equal(tok, "elif"))
    {
      if (!cond_incl || cond_incl->ctx == IN_ELSE)
        error_tok(start, "%s: in preprocess2 : stray #elif", PREPROCESS_C);
      cond_incl->ctx = IN_ELIF;

      if (!cond_incl->included && eval_const_expr(&tok, tok))
        cond_incl->included = true;
      else
        tok = skip_cond_incl(tok);
      continue;
    }

    if (equal(tok, "else"))
    {
      if (!cond_incl || cond_incl->ctx == IN_ELSE)
        error_tok(start, "%s: in preprocess2 : stray #else", PREPROCESS_C);
      cond_incl->ctx = IN_ELSE;
      tok = skip_line(tok->next);

      if (cond_incl->included)
        tok = skip_cond_incl(tok);
      continue;
    }

    if (equal(tok, "endif"))
    {
      if (!cond_incl)
        error_tok(start, "%s: in preprocess2 : stray #endif", PREPROCESS_C);
      cond_incl = cond_incl->next;
      tok = skip_line(tok->next);
      continue;
    }

    if (equal(tok, "line"))
    {
      read_line_marker(&tok, tok->next);
      // tok = skip_line(tok->next->next->next);
      continue;
    }

    if (tok->kind == TK_PP_NUM)
    {
      read_line_marker(&tok, tok);
      continue;
    }

    if (equal(tok, "pragma") && equal(tok->next, "once"))
    {
      hashmap_put(&pragma_once, tok->file->name, (void *)1);
      tok = skip_line(tok->next->next);
      continue;
    }

    if (equal(tok, "pragma"))
    {
      do
      {
        tok = tok->next;
      } while (!tok->at_bol);
      continue;
    }

    if (equal(tok, "error"))
      error_tok(tok, "%s: in preprocess2 : error", PREPROCESS_C);

    // `#`-only line is legal. It's called a null directive.
    if (tok->at_bol)
      continue;

    if (equal(tok, "warning"))
    {
      if (tok->next->str != NULL)
        printf("warning: %s\n", tok->next->str);
      tok = skip_line(tok->next->next);
      continue;
    }
    error_tok(tok, "%s: in preprocess2 : invalid preprocessor directive", PREPROCESS_C);
  }
  cur->next = tok;

  return head.next;
}

void define_macro(char *name, char *buf)
{
  if (strncmp(name, "__has_attribute", 15))
  {
    Token *tok = tokenize(new_file("<built-in>", 1, buf));
    add_macro(name, true, tok);
  }
}

void undef_macro(char *name)
{
  hashmap_delete(&macros, name);
}

static Macro *add_builtin(char *name, macro_handler_fn *fn)
{
  Macro *m = add_macro(name, true, NULL);
  m->handler = fn;
  return m;
}

static Token *file_macro(Token *tmpl)
{
  while (tmpl->origin)
    tmpl = tmpl->origin;
  return new_str_token(tmpl->file->display_name, tmpl);
}

static Token *line_macro(Token *tmpl)
{
  while (tmpl->origin)
    tmpl = tmpl->origin;
  int i = tmpl->line_no + tmpl->file->line_delta;
  return new_num_token(i, tmpl);
}

// __COUNTER__ is expanded to serial values starting from 0.
static Token *counter_macro(Token *tmpl)
{
  static int i = 0;
  return new_num_token(i++, tmpl);
}

// __TIMESTAMP__ is expanded to a string describing the last
// modification time of the current file. E.g.
// "Fri Jul 24 01:32:50 2020"
static Token *timestamp_macro(Token *tmpl)
{
  struct stat st;
  if (stat(tmpl->file->name, &st) != 0)
    return new_str_token("??? ??? ?? ??:??:?? ????", tmpl);

  char buf[30];
  ctime_r(&st.st_mtime, buf);
  buf[24] = '\0';
  return new_str_token(buf, tmpl);
}

static Token *base_file_macro(Token *tmpl)
{
  return new_str_token(base_file, tmpl);
}

// __DATE__ is expanded to the current date, e.g. "May 17 2020".
static char *format_date(struct tm *tm)
{
  static char mon[][4] = {
      "Jan",
      "Feb",
      "Mar",
      "Apr",
      "May",
      "Jun",
      "Jul",
      "Aug",
      "Sep",
      "Oct",
      "Nov",
      "Dec",
  };

  return format("\"%s %2d %d\"", mon[tm->tm_mon], tm->tm_mday, tm->tm_year + 1900);
}

// __TIME__ is expanded to the current time, e.g. "13:34:03".
static char *format_time(struct tm *tm)
{
  return format("\"%02d:%02d:%02d\"", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void init_macros(void)
{
  // Define predefined macros
  define_macro("_LP64", "1");
  define_macro("__C99_MACRO_WITH_VA_ARGS", "1");
  define_macro("__ELF__", "1");
  define_macro("__LP64__", "1");
  define_macro("__SIZEOF_DOUBLE__", "8");
  define_macro("__SIZEOF_FLOAT__", "4");
  define_macro("__SIZEOF_INT__", "4");
  define_macro("__SIZEOF_LONG_DOUBLE__", "8");
  define_macro("__SIZEOF_LONG_LONG__", "8");
  define_macro("__SIZEOF_LONG__", "8");
  define_macro("__SIZEOF_POINTER__", "8");
  define_macro("__SIZEOF_PTRDIFF_T__", "8");
  define_macro("__SIZEOF_SHORT__", "2");
  define_macro("__SIZEOF_SIZE_T__", "8");
  define_macro("__SIZE_TYPE__", "unsigned long");
  define_macro("__STDC_HOSTED__", "1");
  define_macro("__STDC_NO_COMPLEX__", "1");
  define_macro("__STDC_UTF_16__", "1");
  define_macro("__STDC_UTF_32__", "1");
  define_macro("__STDC_VERSION__", "201112L");
  define_macro("__STDC__", "1");
  define_macro("__USER_LABEL_PREFIX__", "");
  define_macro("__alignof__", "_Alignof");
  define_macro("__amd64", "1");
  define_macro("__amd64__", "1");
  define_macro("__chibicc__", "1");
  define_macro("__const__", "const");
  define_macro("__gnu_linux__", "1");
  define_macro("__inline__", "inline");
  define_macro("__linux", "1");
  define_macro("__linux__", "1");
  define_macro("__signed__", "signed");
  define_macro("__typeof__", "typeof");
  define_macro("__unix", "1");
  define_macro("__unix__", "1");
  define_macro("__volatile__", "volatile");
  define_macro("__x86_64", "1");
  define_macro("__x86_64__", "1");
  define_macro("linux", "1");
  define_macro("unix", "1");
  define_macro("nonnull", "1");
  //=======fixing temporary ISS-147 defining the two macros for the linux platform
  define_macro("__ORDER_LITTLE_ENDIAN__", "1234");
  define_macro("__ORDER_BIG_ENDIAN__", "5678");
  define_macro("__BYTE_ORDER__", "__ORDER_LITTLE_ENDIAN__");
  

  add_builtin("__FILE__", file_macro);
  add_builtin("__LINE__", line_macro);
  add_builtin("__COUNTER__", counter_macro);
  add_builtin("__TIMESTAMP__", timestamp_macro);
  add_builtin("__BASE_FILE__", base_file_macro);

  time_t now = time(NULL);
  struct tm *tm = localtime(&now);
  define_macro("__DATE__", format_date(tm));
  define_macro("__TIME__", format_time(tm));
}

typedef enum
{
  STR_NONE,
  STR_UTF8,
  STR_UTF16,
  STR_UTF32,
  STR_WIDE,
} StringKind;

static StringKind getStringKind(Token *tok)
{
  if (!strcmp(tok->loc, "u8"))
    return STR_UTF8;

  switch (tok->loc[0])
  {
  case '"':
    return STR_NONE;
  case 'u':
    return STR_UTF16;
  case 'U':
    return STR_UTF32;
  case 'L':
    return STR_WIDE;
  }
  unreachable();
}

// Concatenate adjacent string literals into a single string literal
// as per the C spec.
static void join_adjacent_string_literals(Token *tok)
{
  // First pass: If regular string literals are adjacent to wide
  // string literals, regular string literals are converted to a wide
  // type before concatenation. In this pass, we do the conversion.
  for (Token *tok1 = tok; tok1->kind != TK_EOF;)
  {
    if (tok1->kind != TK_STR || tok1->next->kind != TK_STR)
    {
      tok1 = tok1->next;
      continue;
    }

    StringKind kind = getStringKind(tok1);
    Type *basety = tok1->ty->base;

    for (Token *t = tok1->next; t->kind == TK_STR; t = t->next)
    {
      StringKind k = getStringKind(t);
      if (kind == STR_NONE)
      {
        kind = k;
        basety = t->ty->base;
      }
      else if (k != STR_NONE && kind != k)
      {
        error_tok(t, "%s: in join_adjacent_string_literals : unsupported non-standard concatenation of string literals", PREPROCESS_C);
      }
    }

    if (basety->size > 1)
      for (Token *t = tok1; t->kind == TK_STR; t = t->next)
        if (t->ty->base->size == 1)
          *t = *tokenize_string_literal(t, basety);

    while (tok1->kind == TK_STR)
      tok1 = tok1->next;
  }


  // Second pass: concatenate adjacent string literals.
  for (Token *tok1 = tok; tok1->kind != TK_EOF;)
  {

    if (tok1->kind != TK_STR || tok1->next->kind != TK_STR)
    {
      tok1 = tok1->next;
      continue;
    }

    Token *tok2 = tok1->next;
    while (tok2->kind == TK_STR)
      tok2 = tok2->next;

    int len = tok1->ty->array_len;
    for (Token *t = tok1->next; t != tok2; t = t->next)
      len = len + t->ty->array_len - 1;

    char *buf = calloc(tok1->ty->base->size, len);
    if (buf == NULL)
      error("%s: in join_adjacent_string_literals :  buf is null", PREPROCESS_C);

    int i = 0;
    for (Token *t = tok1; t != tok2; t = t->next)
    {
      memcpy(buf + i, t->str, t->ty->size);
      i = i + t->ty->size - t->ty->base->size;
    }

    *tok1 = *copy_token(tok1);
    tok1->ty = array_of(tok1->ty->base, len);
    tok1->str = buf;
    tok1->next = tok2;
    tok1 = tok2;
  }

}

// Entry point function of the preprocessor.
Token *preprocess(Token *tok, bool isReadLine)
{
  tok = preprocess2(tok);
  // to manage issue with macro used before its definition. gcc allows it
  tok = preprocess3(tok);

  if (cond_incl && !isReadLine)
    error_tok(cond_incl->tok, "%s: in preprocess : unterminated conditional directive", PREPROCESS_C);
  convert_pp_tokens(tok);
  //ISS-142 temp fix 
  if (!opt_E)
    join_adjacent_string_literals(tok);

  
  for (Token *t = tok; t; t = t->next)
    t->line_no += abs(t->line_delta); // fixing issue with negative number that caused assembly issue

  return tok;
}

// a temp fix to manage the fact that gcc allows that a macro was defined after their use. See issue124.c for more details
Token *preprocess3(Token *tok)
{
  Token head = {};
  Token *cur = &head;
  // Token *start = tok;

  while (tok->kind != TK_EOF)
  {
    Macro *m = find_macro(tok);
    if (m != NULL && m->body->len == 0)
    {
      if (expand_macro(&tok, tok))
        continue;
    }
    cur = cur->next = tok;
    tok = tok->next;
  }

  cur->next = tok;
  return head.next;
}