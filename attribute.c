#include "chibicc.h"

extern Context *ctx;

Token *attribute_list(Token *tok, void *arg, Token *(*f)(Token *, void *))
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

Token *type_attributes(Token *tok, void *arg)
{
  Type *ty = arg;
  if (!ty) {
    warn_tok(tok, "%s:%d: in %s: ty is null", __FILE__, __LINE__, __func__);
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
        align = const_expr(&tok, tok);
        SET_CTX(ctx);
        tok = skip(tok, ")", ctx);
      }
      if (ty->kind == TY_VECTOR || ty->is_vector)
        ty->align = align;
      else
        ty->align = MAX(ty->align, align);
      return tok;
    }

  if (consume(&tok, tok, "ms_abi") || consume(&tok, tok, "__ms_abi__")) {
    ty->is_ms_abi = true;
    return tok;
  }

  if (consume(&tok, tok, "ms_struct") || consume(&tok, tok, "__ms_struct__")) {
    ty->is_ms_struct = true;
    return tok;
  }

  if (consume(&tok, tok, "constructor") || consume(&tok, tok, "__constructor__")) {
    ty->is_constructor = true;
    ty->constructor_priority = 65535;
    if (equal(tok, "(")) {
      SET_CTX(ctx);
      tok = skip(tok, "(",ctx);
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

  if (consume(&tok, tok, "destructor") || consume(&tok, tok, "__destructor__")) {
    ty->is_destructor = true;
    ty->destructor_priority = 65535;
    if (equal(tok, "(")) {
      SET_CTX(ctx);
      tok = skip(tok, "(",ctx);
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
        error_tok(tok, "%s:%d: in %s: unsupported vector_size %d; only 2, 4, 8, 16, 32 and 64 are supported", __FILE__, __LINE__, __func__, vs);
    }
    if (vs != ty->vector_size) {
        ty->vector_size = vs;
        if (!ty->is_aligned) ty->align = vs;
    }
    int base_size = ty->size;
    if (base_size == 0) {
        error_tok(tok, "%s:%d: in %s: incorrect base size %d;", __FILE__, __LINE__, __func__, base_size);
    }
    int n = vs / base_size;
    ty->is_vector = true;
    ty = vector_of(ty, n);
    SET_CTX(ctx);
    tok = skip(tok, ")", ctx);
    return tok;
  }

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
    SET_CTX(ctx);
    return skip(tok, ")", ctx);
  }

  if (consume(&tok, tok, "deprecated") || consume(&tok, tok, "__deprecated__") ||
      consume(&tok, tok, "may_alias") ||  consume(&tok, tok, "__may_alias__") ||
      consume(&tok, tok, "__transparent_union__") || consume(&tok, tok, "transparent_union")) {
    return tok;
  }

  if (consume(&tok, tok, "unused") || consume(&tok, tok, "__unused__")) {
    ty->is_unused = true;
    return tok;
  }

  if (consume(&tok, tok, "cleanup") || consume(&tok, tok, "__cleanup__")) {
      SET_CTX(ctx);
      tok = skip(tok, "(", ctx);
      if (tok->kind != TK_IDENT)
          error_tok(tok, "%s:%d: in %s: expected identifier in __cleanup__", __FILE__, __LINE__, __func__);
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

    if (equal(tok, "(")) {
        SET_CTX(ctx);
        tok = skip(tok, "(", ctx);
        if (tok->kind != TK_IDENT)
            error_tok(tok, "%s:%d: in %s: expected identifier", __FILE__, __LINE__, __func__);
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
      consume(&tok, tok, "noclone") ||
      consume(&tok, tok, "__noclone__") ||
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
                  error_tok(tok, "%s:%d: in %s: expected parameter index in __nonnull__", __FILE__, __LINE__, __func__);
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
    } else if (consume(&tok, tok, "closed")) {
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

    while (!equal(tok, ")")) {
      tok = tok->next;
    }

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

Token *thing_attributes(Token *tok, void *arg) {
  VarAttr *attr = arg;
  if (!attr) {
    warn_tok(tok, "%s:%d: in %s: attr is null", __FILE__, __LINE__, __func__);
    return tok;
  }

  if (consume(&tok, tok, "packed") || consume(&tok, tok, "__packed__"))
    {
      attr->is_packed = true;
      return tok;
    }

  if (consume(&tok, tok, "weak") || consume(&tok, tok, "__weak__")) {
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
    attr->constructor_priority = 65535;

    if (equal(tok, "(")) {
      SET_CTX(ctx);
      tok = skip(tok, "(",ctx);

      if (tok->kind == TK_NUM) {
        attr->constructor_priority = tok->val;
        tok = tok->next;
      } else {
        warn_tok(tok, "%s:%d: in %s: expected integer priority in constructor attribute", __FILE__, __LINE__, __func__);
      }
      SET_CTX(ctx);
      tok = skip(tok, ")", ctx);
    }

    return tok;
  }

  if (consume(&tok, tok, "destructor") || consume(&tok, tok, "__destructor__")) {
    attr->is_destructor = true;
    attr->destructor_priority = 65535;
    if (equal(tok, "(")) {
      SET_CTX(ctx);
      tok = skip(tok, "(",ctx);

      if (tok->kind == TK_NUM) {
        attr->destructor_priority = tok->val;
        tok = tok->next;
      } else {
        warn_tok(tok, "%s:%d: in %s: expected integer priority in destructor attribute", __FILE__, __LINE__, __func__);
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
    while (!equal(tok, ")")) {
      tok = tok->next;
    }
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

 if (consume(&tok, tok, "cleanup") || consume(&tok, tok, "__cleanup__")) {
      SET_CTX(ctx);
      tok = skip(tok, "(", ctx);
      if (tok->kind != TK_IDENT)
          error_tok(tok, "%s:%d: in %s: expected identifier in __cleanup__", __FILE__, __LINE__, __func__);

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
            error_tok(tok, "%s:%d: in %s: expected identifier in __malloc__ attribute", __FILE__, __LINE__, __func__);
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
      consume(&tok, tok, "__noinline__")) {
    attr->is_noinline = true;
    return tok;
  }

  if (consume(&tok, tok, "returns_twice") ||
      consume(&tok, tok, "__returns_twice__")) {
    attr->is_returned_twice = true;
    return tok;
  }

  if (consume(&tok, tok, "used") ||
      consume(&tok, tok, "__used__")) {
    attr->is_used = true;
    return tok;
  }

  if (consume(&tok, tok, "unused") ||
      consume(&tok, tok, "__unused__")) {
    attr->is_unused = true;
    return tok;
  }

  if (consume(&tok, tok, "noclone") ||
      consume(&tok, tok, "__noclone__") ||
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
                  error_tok(tok, "%s:%d: in %s: expected parameter index in __nonnull__", __FILE__, __LINE__, __func__);
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
      } else if (consume(&tok, tok, "closed")) {
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
