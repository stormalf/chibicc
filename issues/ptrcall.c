// test_expat_subset.c

#define PTRCALL


typedef struct PROLOG_STATE PROLOG_STATE;
typedef struct ENCODING ENCODING;

// Function pointer type
typedef int (*Handler)(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);

struct PROLOG_STATE {
  Handler handler;
  int includeLevel;
};

struct ENCODING {
  int dummy;
};

// --- token constants ---
enum {
  XML_TOK_XML_DECL,
  XML_TOK_COND_SECT_OPEN,
  XML_TOK_COND_SECT_CLOSE,
  XML_TOK_PROLOG_S,
  XML_TOK_CLOSE_BRACKET,
  XML_TOK_NONE
};

// --- role constants ---
enum {
  XML_ROLE_TEXT_DECL,
  XML_ROLE_NONE
};

// --- forward declarations (IMPORTANT for chibicc) ---
static int PTRCALL externalSubset1(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);
static int PTRCALL condSect0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);
static int PTRCALL internalSubset(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);
static int common(PROLOG_STATE *, int);

// --- test target functions ---

static int PTRCALL
externalSubset0(PROLOG_STATE *state, int tok, const char *ptr, const char *end,
                const ENCODING *enc) {
  state->handler = externalSubset1;
  if (tok == XML_TOK_XML_DECL)
    return XML_ROLE_TEXT_DECL;
  return externalSubset1(state, tok, ptr, end, enc);
}

static int PTRCALL
externalSubset1(PROLOG_STATE *state, int tok, const char *ptr, const char *end,
                const ENCODING *enc) {
  switch (tok) {
  case XML_TOK_COND_SECT_OPEN:
    state->handler = condSect0;
    return XML_ROLE_NONE;
  case XML_TOK_COND_SECT_CLOSE:
    if (state->includeLevel == 0)
      break;
    state->includeLevel -= 1;
    return XML_ROLE_NONE;
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_CLOSE_BRACKET:
    break;
  case XML_TOK_NONE:
    if (state->includeLevel)
      break;
    return XML_ROLE_NONE;
  default:
    return internalSubset(state, tok, ptr, end, enc);
  }
  return common(state, tok);
}

// --- stubs ---

static int PTRCALL
condSect0(PROLOG_STATE *state, int tok, const char *ptr, const char *end,
          const ENCODING *enc) {
  return 1;
}

static int PTRCALL
internalSubset(PROLOG_STATE *state, int tok, const char *ptr, const char *end,
               const ENCODING *enc) {
  return 2;
}

static int
common(PROLOG_STATE *state, int tok) {
  return 3;
}

// --- driver ---

int main(void) {
  PROLOG_STATE st = {0};
  ENCODING enc = {0};

  return externalSubset0(&st, XML_TOK_XML_DECL, 0, 0, &enc);
}
