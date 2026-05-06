#include "chibicc.h"
#include <limits.h>
#include <string.h>

//  for debug needs
char *tokenkind2str(TokenKind kind)
{
    switch (kind)
    {
    case TK_IDENT:
        return "TK_IDENT";
    case TK_PUNCT:
        return "TK_PUNCT";
    case TK_KEYWORD:
        return "TK_KEYWORD";
    case TK_STR:
        return "TK_STR";
    case TK_NUM:
        return "TK_NUM";
    case TK_PP_NUM:
        return "TK_PP_NUM";
    case TK_EOF:
        return "TK_EOF";
    default:
        return "UNREACHABLE";
    }
}

// print all tokens received
void print_debug_tokens(char *currentfilename, char *function, Token *tok)
{

    fprintf(f, "=====================file : %s, function: %s\n", currentfilename, function);

    // for debug needs print all the tokens with values
    Token *t = tok;
    while (t->kind != TK_EOF)
    {
        if (t->len > 0)
        {
            char tokloc[t->len + 1];
            memset(tokloc, 0, sizeof(tokloc));
            char *ptokloc = &tokloc[0];
            strncpy(ptokloc, t->loc, t->len);
            fprintf(f, "token->kind: %s, token->len: %d, token->val: %ld, token->fval:%Lf \n", tokenkind2str(t->kind), t->len, t->val, t->fval);
            fprintf(f, "     token->str: %s, token->filename: %s, token->line_no: %d, token->at_bol:%d \n", t->str, t->filename, t->line_no, t->at_bol);
            fprintf(f, "     token->loc: %s \n", ptokloc);
        }
        // TK_EOF not sure that it helps to have this information in the log!
        //  else
        //  {
        //    fprintf(f, "token->kind: %s, token->len: %d, token->val: %ld, token->fval:%Lf \n", tokenkind2str(t->kind), t->len, t->val, t->fval);
        //    fprintf(f, "     token->str: %s, token->filename: %s, token->line_no: %d, token->at_bol:%d \n", t->str, t->filename, t->line_no, t->at_bol);
        //  }
        t = t->next;
    }
}

static void emit_base_type_die(int c, char *label, char *name, int encoding, int size) {
  println(".L.%s%d:", label, c);
  println("  .uleb128 5");
  println("  .string \"%s\"", name);
  println("  .byte %d", encoding);
  println("  .byte %d", size);
}

typedef struct DebugTypeInfo DebugTypeInfo;
struct DebugTypeInfo {
  Type *ty;
  int id;
  DebugTypeInfo *next;
};

typedef struct DebugQualTypeInfo DebugQualTypeInfo;
struct DebugQualTypeInfo {
  Type *ty;
  int id;
  DebugQualTypeInfo *next;
};

typedef struct EmittedTypedef EmittedTypedef;
struct EmittedTypedef {
  char *name;
  Type *ty;
  EmittedTypedef *next;
};

static DebugTypeInfo *find_debug_type(DebugTypeInfo *types, Type *ty) {
  for (DebugTypeInfo *it = types; it; it = it->next)
    if (it->ty == ty)
      return it;
  return NULL;
}

static DebugQualTypeInfo *find_debug_qual_type(DebugQualTypeInfo *types, Type *ty) {
  for (DebugQualTypeInfo *it = types; it; it = it->next)
    if (it->ty == ty)
      return it;
  return NULL;
}

static bool has_debug_type_qual(Type *ty) {
  return ty && (ty->is_const || ty->is_volatile || ty->is_restrict);
}

static Type *unqual_debug_type(Type *ty) {
  if (!ty)
    return NULL;
  if (ty->origin)
    return ty->origin;
  return ty;
}

static bool is_builtin_debug_type(Type *ty) {
  if (!ty)
    return true;

  switch (ty->kind) {
  case TY_VOID:
  case TY_BOOL:
  case TY_ENUM:
  case TY_CHAR:
  case TY_SHORT:
  case TY_INT:
  case TY_LONG:
  case TY_LLONG:
  case TY_INT128:
  case TY_FLOAT:
  case TY_DOUBLE:
  case TY_LDOUBLE:
    return true;
  default:
    return false;
  }
}

static bool emit_builtin_type_ref(Type *ty, int c) {
  if (!ty) {
    println("  .long .L.type_int%d - .L.debug_info%d", c, c);
    return true;
  }

  switch (ty->kind) {
  case TY_VOID:
    println("  .long .L.type_void%d - .L.debug_info%d", c, c);
    return true;
  case TY_BOOL:
    println("  .long .L.type_bool%d - .L.debug_info%d", c, c);
    return true;
  case TY_ENUM:
    println("  .long .L.type_int%d - .L.debug_info%d", c, c);
    return true;
  case TY_CHAR:
    if (ty->is_unsigned) {
      println("  .long .L.type_uchar%d - .L.debug_info%d", c, c);
      return true;
    }
    println("  .long .L.type_char%d - .L.debug_info%d", c, c);
    return true;
  case TY_SHORT:
    if (ty->is_unsigned) {
      println("  .long .L.type_ushort%d - .L.debug_info%d", c, c);
      return true;
    }
    println("  .long .L.type_short%d - .L.debug_info%d", c, c);
    return true;
  case TY_INT:
    if (ty->is_unsigned) {
      println("  .long .L.type_uint%d - .L.debug_info%d", c, c);
      return true;
    }
    println("  .long .L.type_int%d - .L.debug_info%d", c, c);
    return true;
  case TY_LONG:
    if (ty->is_unsigned) {
      println("  .long .L.type_ulong%d - .L.debug_info%d", c, c);
      return true;
    }
    println("  .long .L.type_long%d - .L.debug_info%d", c, c);
    return true;
  case TY_LLONG:
    if (ty->is_unsigned) {
      println("  .long .L.type_ullong%d - .L.debug_info%d", c, c);
      return true;
    }
    println("  .long .L.type_llong%d - .L.debug_info%d", c, c);
    return true;
  case TY_INT128:
    if (ty->is_unsigned) {
      println("  .long .L.type_uint128%d - .L.debug_info%d", c, c);
      return true;
    }
    println("  .long .L.type_int128%d - .L.debug_info%d", c, c);
    return true;
  case TY_FLOAT:
    println("  .long .L.type_float%d - .L.debug_info%d", c, c);
    return true;
  case TY_DOUBLE:
    println("  .long .L.type_double%d - .L.debug_info%d", c, c);
    return true;
  case TY_LDOUBLE:
    println("  .long .L.type_ldouble%d - .L.debug_info%d", c, c);
    return true;
  default:
    return false;
  }
}

static void collect_debug_qual_type(Type *ty, DebugQualTypeInfo **types, int *next_id) {
  if (!has_debug_type_qual(ty))
    return;

  if (find_debug_qual_type(*types, ty))
    return;

  DebugQualTypeInfo *entry = calloc(1, sizeof(DebugQualTypeInfo));
  entry->ty = ty;
  entry->id = (*next_id)++;
  entry->next = *types;
  *types = entry;
}

static void collect_debug_type(Type *ty, DebugTypeInfo **types, int *next_id,
                               DebugQualTypeInfo **quals, int *next_qual_id) {
  if (!ty)
    return;

  if (has_debug_type_qual(ty))
    collect_debug_qual_type(ty, quals, next_qual_id);

  ty = unqual_debug_type(ty);

  if (is_builtin_debug_type(ty))
    return;

  if (ty->kind != TY_PTR && ty->kind != TY_ARRAY && ty->kind != TY_STRUCT &&
      ty->kind != TY_UNION)
    return;

  if (find_debug_type(*types, ty))
    return;

  DebugTypeInfo *entry = calloc(1, sizeof(DebugTypeInfo));
  entry->ty = ty;
  entry->id = (*next_id)++;
  entry->next = *types;
  *types = entry;

  if (ty->kind == TY_PTR || ty->kind == TY_ARRAY) {
    collect_debug_type(ty->base, types, next_id, quals, next_qual_id);
    return;
  }

  for (Member *mem = ty->members; mem; mem = mem->next)
    collect_debug_type(mem->ty, types, next_id, quals, next_qual_id);
}

static void emit_unqualified_type_ref(Type *ty, DebugTypeInfo *types, int c) {
  ty = unqual_debug_type(ty);

  if (emit_builtin_type_ref(ty, c))
    return;

  DebugTypeInfo *entry = find_debug_type(types, ty);
  if (!entry) {
    println("  .long .L.type_int%d - .L.debug_info%d", c, c);
    return;
  }

  println("  .long .L.type_custom_%d_%d - .L.debug_info%d", c, entry->id, c);
}

static char *qual_outer_label(DebugQualTypeInfo *entry, int c) {
  Type *ty = entry->ty;
  if (ty->is_const)
    return format(".L.type_const_%d_%d", c, entry->id);
  if (ty->is_volatile)
    return format(".L.type_volatile_%d_%d", c, entry->id);
  return format(".L.type_restrict_%d_%d", c, entry->id);
}

static void emit_type_ref(Type *ty, DebugTypeInfo *types, DebugQualTypeInfo *quals, int c) {
  if (has_debug_type_qual(ty)) {
    DebugQualTypeInfo *entry = find_debug_qual_type(quals, ty);
    if (entry) {
      println("  .long %s - .L.debug_info%d", qual_outer_label(entry, c), c);
      return;
    }
  }

  emit_unqualified_type_ref(ty, types, c);
}

static void emit_struct_name(Type *ty, int id) {
  Token *tag = ty ? ty->tag_name : NULL;
  if (!tag && ty)
    tag = ty->name;

  if (tag) {
    println("  .string \"%.*s\"", tag->len, tag->loc);
    return;
  }

  println("  .string \"type_%d\"", id);
}

static void emit_member_name(Member *mem, int idx) {
  if (!mem->name) {
    println("  .string \"member_%d\"", idx);
    return;
  }

  println("  .string \"%.*s\"", mem->name->len, mem->name->loc);
}

static void emit_custom_type_die(DebugTypeInfo *entry, DebugTypeInfo *types, int c) {
  Type *ty = entry->ty;
  println(".L.type_custom_%d_%d:", c, entry->id);

  switch (ty->kind) {
  case TY_PTR:
    println("  .uleb128 6");
    emit_unqualified_type_ref(ty->base, types, c);
    return;
  case TY_ARRAY: {
    int64_t count = ty->array_len;
    if (count < 0)
      count = 0;
    println("  .uleb128 7");
    emit_unqualified_type_ref(ty->base, types, c);
    println("  .uleb128 8");
    println("  .uleb128 %ld", count);
    println("  .byte 0");
    return;
  }
  case TY_STRUCT:
  case TY_UNION: {
    println("  .uleb128 %d", ty->kind == TY_STRUCT ? 9 : 11);
    emit_struct_name(ty, entry->id);
    println("  .uleb128 %ld", ty->size);
    int member_idx = 0;
    for (Member *mem = ty->members; mem; mem = mem->next) {
      println("  .uleb128 10");
      emit_member_name(mem, member_idx++);
      emit_unqualified_type_ref(mem->ty, types, c);
      println("  .uleb128 %d", ty->kind == TY_UNION ? 0 : mem->offset);
    }
    println("  .byte 0");
    return;
  }
  default:
    return;
  }
}

static void emit_qual_type_dies(DebugQualTypeInfo *quals, DebugTypeInfo *types, int c) {
  for (DebugQualTypeInfo *entry = quals; entry; entry = entry->next) {
    Type *ty = entry->ty;

    if (ty->is_restrict) {
      println(".L.type_restrict_%d_%d:", c, entry->id);
      println("  .uleb128 16");
      emit_unqualified_type_ref(ty, types, c);
    }

    if (ty->is_volatile) {
      println(".L.type_volatile_%d_%d:", c, entry->id);
      println("  .uleb128 15");
      if (ty->is_restrict)
        println("  .long .L.type_restrict_%d_%d - .L.debug_info%d", c, entry->id, c);
      else
        emit_unqualified_type_ref(ty, types, c);
    }

    if (ty->is_const) {
      println(".L.type_const_%d_%d:", c, entry->id);
      println("  .uleb128 14");
      if (ty->is_volatile)
        println("  .long .L.type_volatile_%d_%d - .L.debug_info%d", c, entry->id, c);
      else if (ty->is_restrict)
        println("  .long .L.type_restrict_%d_%d - .L.debug_info%d", c, entry->id, c);
      else
        emit_unqualified_type_ref(ty, types, c);
    }
  }
}

static bool is_emitted_typedef(EmittedTypedef *head, char *name, Type *ty) {
  for (EmittedTypedef *it = head; it; it = it->next) {
    if (it->ty == ty && !strcmp(it->name, name))
      return true;
  }
  return false;
}

static void emit_typedef_dies(DebugTypeInfo *types, DebugQualTypeInfo *quals, int c) {
  EmittedTypedef *emitted = NULL;

  for (DebugTypedef *td = debug_typedefs; td; td = td->next) {
    if (!td->name || !td->ty)
      continue;
    if (is_emitted_typedef(emitted, td->name, td->ty))
      continue;

    EmittedTypedef *entry = calloc(1, sizeof(EmittedTypedef));
    entry->name = td->name;
    entry->ty = td->ty;
    entry->next = emitted;
    emitted = entry;

    println("  .uleb128 12");
    println("  .string \"%s\"", td->name);
    emit_type_ref(td->ty, types, quals, c);
  }
}


void emit_debug_info(Obj *prog) {
  if (!opt_g)
    return;

  static int c = 0;
  static int label_count = 0;

  // Compute absolute source path and compilation directory
  char abs_path[PATH_MAX] = {0};
  char comp_dir[PATH_MAX] = {0};
  if (base_file) {
    // Use base_file directly without realpath
    snprintf(abs_path, sizeof(abs_path), "%s", base_file);
    // Extract directory from path (find last '/')
    char *last_slash = strrchr(base_file, '/');
    if (last_slash && last_slash != base_file) {
      size_t dir_len = last_slash - base_file;
      if (dir_len < sizeof(comp_dir)) {
        strncpy(comp_dir, base_file, dir_len);
        comp_dir[dir_len] = '\0';
      }
    } else {
      snprintf(comp_dir, sizeof(comp_dir), ".");
    }
  } else {
    snprintf(abs_path, sizeof(abs_path), "%s", "unknown_source");
    snprintf(comp_dir, sizeof(comp_dir), ".");
  }

  println("  .section .debug_abbrev,\"\",@progbits");
  println(".L.debug_abbrev%d:", c);

  println("  .uleb128 1");                    // Abbrev code
  println("  .uleb128 0x11");                 // DW_TAG_compile_unit
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x25");                 // DW_AT_producer
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x13");                 // DW_AT_language
  println("  .uleb128 0xb");                  // DW_FORM_data1
  println("  .uleb128 0x1b");                 // DW_AT_comp_dir
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x3");                 // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x10");                 // DW_AT_stmt_list
  println("  .uleb128 0x17");                 // DW_FORM_sec_offset
  println("  .uleb128 0x11");                 // DW_AT_low_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .uleb128 0x12");                 // DW_AT_high_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .byte 0");
  println("  .byte 0");
  //println("  .byte 0");

  println("  .uleb128 2");                    // Abbrev code
  println("  .uleb128 0x2e");                 // DW_TAG_subprogram
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x3a");                 // DW_AT_decl_file
  println("  .uleb128 0x15");                 // DW_FORM_udata
  println("  .uleb128 0x3b");                 // DW_AT_decl_line
  println("  .uleb128 0x15");                 // DW_FORM_udata
  println("  .uleb128 0x11");                 // DW_AT_low_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .uleb128 0x12");                 // DW_AT_high_pc
  println("  .uleb128 0x1");                  // DW_FORM_addr
  println("  .uleb128 0x40");                 // DW_AT_frame_base
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .uleb128 0x3f");                 // DW_AT_external
  println("  .uleb128 0xc");                  // DW_FORM_flag
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 3");                    // Abbrev code
  println("  .uleb128 0x5");                  // DW_TAG_formal_parameter
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .uleb128 0x2");                  // DW_AT_location
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 4");                    // Abbrev code
  println("  .uleb128 0x34");                 // DW_TAG_variable
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .uleb128 0x2");                  // DW_AT_location
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 5");                    // Abbrev code
  println("  .uleb128 0x24");                 // DW_TAG_base_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x3e");                 // DW_AT_encoding
  println("  .uleb128 0xb");                  // DW_FORM_data1
  println("  .uleb128 0xb");                  // DW_AT_byte_size
  println("  .uleb128 0xb");                  // DW_FORM_data1
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 6");                    // Abbrev code
  println("  .uleb128 0xf");                  // DW_TAG_pointer_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 7");                    // Abbrev code
  println("  .uleb128 0x1");                  // DW_TAG_array_type
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 8");                    // Abbrev code
  println("  .uleb128 0x21");                 // DW_TAG_subrange_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x37");                 // DW_AT_count
  println("  .uleb128 0xf");                  // DW_FORM_udata
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 9");                    // Abbrev code
  println("  .uleb128 0x13");                 // DW_TAG_structure_type
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0xb");                  // DW_AT_byte_size
  println("  .uleb128 0xf");                  // DW_FORM_udata
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 10");                   // Abbrev code
  println("  .uleb128 0xd");                  // DW_TAG_member
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .uleb128 0x38");                 // DW_AT_data_member_location
  println("  .uleb128 0xf");                  // DW_FORM_udata
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 11");                   // Abbrev code
  println("  .uleb128 0x17");                 // DW_TAG_union_type
  println("  .byte 1");                       // DW_CHILDREN_yes
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0xb");                  // DW_AT_byte_size
  println("  .uleb128 0xf");                  // DW_FORM_udata
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 12");                   // Abbrev code
  println("  .uleb128 0x16");                 // DW_TAG_typedef
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 13");                   // Abbrev code
  println("  .uleb128 0x34");                 // DW_TAG_variable
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x3");                  // DW_AT_name
  println("  .uleb128 0x8");                  // DW_FORM_string
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .uleb128 0x3a");                 // DW_AT_decl_file
  println("  .uleb128 0x15");                 // DW_FORM_udata
  println("  .uleb128 0x3b");                 // DW_AT_decl_line
  println("  .uleb128 0x15");                 // DW_FORM_udata
  println("  .uleb128 0x3f");                 // DW_AT_external
  println("  .uleb128 0xc");                  // DW_FORM_flag
  println("  .uleb128 0x2");                  // DW_AT_location
  println("  .uleb128 0x18");                 // DW_FORM_exprloc
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 14");                   // Abbrev code
  println("  .uleb128 0x26");                 // DW_TAG_const_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 15");                   // Abbrev code
  println("  .uleb128 0x35");                 // DW_TAG_volatile_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .byte 0");
  println("  .byte 0");

  println("  .uleb128 16");                   // Abbrev code
  println("  .uleb128 0x37");                 // DW_TAG_restrict_type
  println("  .byte 0");                       // DW_CHILDREN_no
  println("  .uleb128 0x49");                 // DW_AT_type
  println("  .uleb128 0x13");                 // DW_FORM_ref4
  println("  .byte 0");
  println("  .byte 0");

  println("  .byte 0");                       // End of abbrevs

  println("  .section .debug_info,\"\",@progbits");
  println(".L.debug_info%d:", c);
  println("  .long .L.debug_info_end%d - .L.debug_info_start%d", c, c);
  println(".L.debug_info_start%d:", c);
  println("  .short 4");
  println("  .long .L.debug_abbrev%d", c);
  println("  .byte 8");

  println("  .uleb128 1");
  println("  .string \"%s\"", PRODUCT);            // DW_AT_producer
  println("  .byte 0xc");                     // DW_AT_language (DW_LANG_C99)
  println("  .string \"%s\"", comp_dir);       // DW_AT_comp_dir (new)
  println("  .string \"%s\"", abs_path);       // DW_AT_name (absolute path)
  println("  .long .L.line_table_start0");     // DW_AT_stmt_list
  println("  .quad .L.text_start");           // DW_AT_low_pc
  println("  .quad .L.text_end");             // DW_AT_high_pc

  // Emit base types
  emit_base_type_die(c, "type_void", "void", 0, 0);
  emit_base_type_die(c, "type_bool", "_Bool", 2, 1);       // DW_ATE_boolean
  emit_base_type_die(c, "type_char", "char", 6, 1);        // DW_ATE_signed_char
  emit_base_type_die(c, "type_uchar", "unsigned char", 8, 1); // DW_ATE_unsigned_char
  emit_base_type_die(c, "type_short", "short", 5, 2);      // DW_ATE_signed
  emit_base_type_die(c, "type_ushort", "unsigned short", 7, 2); // DW_ATE_unsigned
  emit_base_type_die(c, "type_int", "int", 5, 4);          // DW_ATE_signed
  emit_base_type_die(c, "type_uint", "unsigned int", 7, 4); // DW_ATE_unsigned
  emit_base_type_die(c, "type_long", "long", 5, 8);        // DW_ATE_signed
  emit_base_type_die(c, "type_ulong", "unsigned long", 7, 8); // DW_ATE_unsigned
  emit_base_type_die(c, "type_llong", "long long", 5, 8);  // DW_ATE_signed
  emit_base_type_die(c, "type_ullong", "unsigned long long", 7, 8); // DW_ATE_unsigned
  emit_base_type_die(c, "type_int128", "__int128", 5, 16); // DW_ATE_signed
  emit_base_type_die(c, "type_uint128", "unsigned __int128", 7, 16); // DW_ATE_unsigned
  emit_base_type_die(c, "type_float", "float", 4, 4);      // DW_ATE_float
  emit_base_type_die(c, "type_double", "double", 4, 8);    // DW_ATE_float
  emit_base_type_die(c, "type_ldouble", "long double", 4, 16); // DW_ATE_float

  DebugTypeInfo *types = NULL;
  DebugQualTypeInfo *quals = NULL;
  int next_type_id = 0;
  int next_qual_id = 0;
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition || !fn->is_live)
      continue;

    for (Obj *var = fn->params; var; var = var->next)
      collect_debug_type(var->ty, &types, &next_type_id, &quals, &next_qual_id);

    for (Obj *var = fn->locals; var; var = var->next)
      if (!var->is_param)
        collect_debug_type(var->ty, &types, &next_type_id, &quals, &next_qual_id);
  }

  for (Obj *var = prog; var; var = var->next) {
    if (var->is_function || !var->is_definition || !var->name)
      continue;
    collect_debug_type(var->ty, &types, &next_type_id, &quals, &next_qual_id);
  }

  for (DebugTypedef *td = debug_typedefs; td; td = td->next)
    collect_debug_type(td->ty, &types, &next_type_id, &quals, &next_qual_id);

  for (DebugTypeInfo *entry = types; entry; entry = entry->next)
    emit_custom_type_die(entry, types, c);

  emit_qual_type_dies(quals, types, c);
  emit_typedef_dies(types, quals, c);

  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function || !fn->is_definition)
      continue;
    
    if (!fn->is_live)
      continue;

    println("  .uleb128 2");
    println("  .string \"%s\"", fn->name);
    println("  .uleb128 %d", fn->file_no);
    println("  .uleb128 %d", fn->line_no);
    char *name = fn->asmname ? fn->asmname : fn->name;
    println("  .quad %s", name);
    println("  .quad .L.end.%s", name);
    
    // Frame base
    int lbl_fb = label_count++;
    println("  .uleb128 .L.loc_end_%d - .L.loc_start_%d", lbl_fb, lbl_fb);
    println(".L.loc_start_%d:", lbl_fb);
    if (is_omit_fp(fn)) {
        // If frame pointer is omitted, offsets are relative to RSP at entry.
        // We define frame base as RSP + stack_size.
        println("  .byte 0x77"); // DW_OP_breg7 (rsp)
        println("  .sleb128 %d", fn->stack_size);
    } else if (fn->stack_align > 16) {
        println("  .byte 0x53"); // DW_OP_reg3 (rbx)
    } else {
        println("  .byte 0x56"); // DW_OP_reg6 (rbp)
    }
    println(".L.loc_end_%d:", lbl_fb);
    
    println("  .byte %d", !fn->is_static);

    for (Obj *var = fn->params; var; var = var->next) {
        if (!var->name) continue;
        println("  .uleb128 3");
        println("  .string \"%s\"", var->name);
        
        emit_type_ref(var->ty, types, quals, c);

        int lbl = label_count++;
        println("  .uleb128 .L.loc_end_%d - .L.loc_start_%d", lbl, lbl);
        println(".L.loc_start_%d:", lbl);
        // println("  .byte 0x91"); // DW_OP_fbreg
        // println("  .sleb128 %d", var->offset);
        // SysV ABI argument registers
        static int argreg64[] = {5, 4, 1, 2, 8, 9}; // rdi, rsi, rdx, rcx, r8, r9

        if (var->nbparm < 6) {
          println("  .byte %d", 0x50 + argreg64[var->nbparm]); // DW_OP_regX
        }        
        println(".L.loc_end_%d:", lbl);
    }

    for (Obj *var = fn->locals; var; var = var->next) {
        if (var->is_param || !var->name) continue;
        println("  .uleb128 4");
        println("  .string \"%s\"", var->name);
        
        emit_type_ref(var->ty, types, quals, c);

        int lbl = label_count++;
        println("  .uleb128 .L.loc_end_%d - .L.loc_start_%d", lbl, lbl);
        println(".L.loc_start_%d:", lbl);
        println("  .byte 0x91"); // DW_OP_fbreg
        println("  .sleb128 %d", var->offset);
        println(".L.loc_end_%d:", lbl);
    }

    println("  .byte 0"); // End of children
  }

  for (Obj *var = prog; var; var = var->next) {
    if (var->is_function || !var->is_definition || !var->name)
      continue;

    println("  .uleb128 13");
    println("  .string \"%s\"", var->name);
    emit_type_ref(var->ty, types, quals, c);
    println("  .uleb128 %d", var->file_no);
    println("  .uleb128 %d", var->line_no);
    println("  .byte %d", !var->is_static);

    // DW_OP_addr <symbol>
    println("  .byte 9");
    println("  .byte 0x3");
    println("  .quad %s", var->name);
  }

  println("  .byte 0");
  println(".L.debug_info_end%d:", c);

  println("  .section .debug_line,\"\",@progbits");
  println(".L.line_table_start0:");
}
