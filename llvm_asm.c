// This file parses extended inline assembly for the LLVM IR backend.
// It stores structured constraint/operand data in the AST node,
// leaving register allocation and code emission to ir.c.
//
// References:
//   https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html

#include "chibicc.h"

// Maximum number of operands (matching extended_asm.c limits)
#define MAX_ASM_OPERANDS 10

static void parse_asm_outputs(Node *node, Token **rest, Token *tok);
static void parse_asm_inputs(Node *node, Token **rest, Token *tok);
static void parse_asm_clobbers(Node *node, Token **rest, Token *tok);

void parse_llvm_asm(Node *node, Token **rest, Token *tok, Obj *locals, Obj *current_fn)
{
    node->asm_template = tok->str;

    node->asm_outputs = calloc(MAX_ASM_OPERANDS, sizeof(AsmOperand));
    node->asm_inputs = calloc(MAX_ASM_OPERANDS, sizeof(AsmOperand));
    node->asm_clobbers = calloc(MAX_ASM_OPERANDS, sizeof(char *));
    if (!node->asm_outputs || !node->asm_inputs || !node->asm_clobbers)
        error("%s:%d: error: in %s: out of memory", __FILE__, __LINE__, __func__);

    int phase = 0; // 0=template, 1=outputs, 2=inputs, 3=clobbers, 4=labels

    tok = tok->next; // advance past template string

    while (!equal(tok, ";") && !equal(tok, ")") && !equal(tok, "}")) {
        if (equal(tok, ":")) {
            phase++;
            tok = tok->next;
            continue;
        }

        if (equal(tok, ",")) {
            tok = tok->next;
            continue;
        }

        switch (phase) {
        case 0:
            break;
        case 1:
            parse_asm_outputs(node, &tok, tok);
            break;
        case 2:
            parse_asm_inputs(node, &tok, tok);
            break;
        case 3:
            parse_asm_clobbers(node, &tok, tok);
            break;
        case 4:
            // Labels - skip
            tok = tok->next;
            continue;
        default:
            error_tok(tok, "%s:%d: in %s: too many extended asm parameters", __FILE__, __LINE__, __func__);
        }

        // Check again for phase separator that the operand function may have
        // left tok at (after the closing ')')
        if (equal(tok, ":")) {
            phase++;
            tok = tok->next;
        } else if (!equal(tok, ";") && !equal(tok, ")") && !equal(tok, "}")) {
            tok = tok->next;
        }
    }

    // Skip past closing ')'
    while (equal(tok, ")"))
        tok = tok->next;
    *rest = tok;

    if (current_fn)
        current_fn->force_frame_pointer = true;
}

// Parse one output operand: [name] "constraint" (expr)
static void parse_asm_outputs(Node *node, Token **rest, Token *tok)
{
    int idx = node->asm_noutputs;
    if (idx >= MAX_ASM_OPERANDS)
        error_tok(tok, "%s:%d: in %s: too many output operands", __FILE__, __LINE__, __func__);

    AsmOperand *op = &node->asm_outputs[idx];

    // Check for named operand [name]
    if (equal(tok, "[") || equal(tok, "{")) {
        char close = equal(tok, "[") ? ']' : '}';
        tok = tok->next;
        if (tok->kind != TK_IDENT)
            error_tok(tok, "%s:%d: in %s: expected identifier in named operand", __FILE__, __LINE__, __func__);
        op->name = strndup(tok->loc, tok->len);
        tok = tok->next;
        if (!equal(tok, (char[]){close, 0}))
            error_tok(tok, "%s:%d: in %s: expected '%c' after operand name", __FILE__, __LINE__, __func__, close);
        tok = tok->next;
    }

    // Constraint string
    if (tok->kind != TK_STR)
        error_tok(tok, "%s:%d: in %s: expected constraint string in output operand", __FILE__, __LINE__, __func__);
    op->constraint = strdup(tok->str);
    tok = tok->next;

    // Skip '(' and parse expression
    if (!equal(tok, "("))
        error_tok(tok, "%s:%d: in %s: expected '(' after constraint", __FILE__, __LINE__, __func__);
    tok = tok->next;

    op->expr = conditional(&tok, tok);
    if (!op->expr)
        error_tok(tok, "%s:%d: in %s: failed to parse output expression", __FILE__, __LINE__, __func__);
    add_type(op->expr);

    // Skip ')'
    if (!equal(tok, ")"))
        error_tok(tok, "%s:%d: in %s: expected ')' after output expression", __FILE__, __LINE__, __func__);
    tok = tok->next;

    node->asm_noutputs++;
    *rest = tok;
}

// Parse one input operand: [name] "constraint" (expr)  or  digit (matching constraint)
static void parse_asm_inputs(Node *node, Token **rest, Token *tok)
{
    int idx = node->asm_ninputs;
    if (idx >= MAX_ASM_OPERANDS)
        error_tok(tok, "%s:%d: in %s: too many input operands", __FILE__, __LINE__, __func__);

    AsmOperand *op = &node->asm_inputs[idx];

    // Check for named operand [name]
    if (equal(tok, "[") || equal(tok, "{")) {
        char close = equal(tok, "[") ? ']' : '}';
        tok = tok->next;
        if (tok->kind != TK_IDENT)
            error_tok(tok, "%s:%d: in %s: expected identifier in named operand", __FILE__, __LINE__, __func__);
        op->name = strndup(tok->loc, tok->len);
        tok = tok->next;
        if (!equal(tok, (char[]){close, 0}))
            error_tok(tok, "%s:%d: in %s: expected '%c' after operand name", __FILE__, __LINE__, __func__, close);
        tok = tok->next;
    }

    // Constraint string (or matching constraint like "0", "1", etc.)
    if (tok->kind == TK_STR) {
        op->constraint = strdup(tok->str);
        tok = tok->next;

        // Check for matching constraint (digit)
        if (op->constraint[0] >= '0' && op->constraint[0] <= '9')
            op->match_index = op->constraint[0] - '0';
        else
            op->match_index = -1;
    } else {
        error_tok(tok, "%s:%d: in %s: expected constraint string in input operand", __FILE__, __LINE__, __func__);
    }

    // Skip '(' and parse expression
    if (!equal(tok, "("))
        error_tok(tok, "%s:%d: in %s: expected '(' after input constraint", __FILE__, __LINE__, __func__);
    tok = tok->next;

    op->expr = conditional(&tok, tok);
    if (!op->expr)
        error_tok(tok, "%s:%d: in %s: failed to parse input expression", __FILE__, __LINE__, __func__);
    add_type(op->expr);

    // Skip ')'
    if (!equal(tok, ")"))
        error_tok(tok, "%s:%d: in %s: expected ')' after input expression", __FILE__, __LINE__, __func__);
    tok = tok->next;

    node->asm_ninputs++;
    *rest = tok;
}

// Parse one clobber: register name or "memory" or "cc"
static void parse_asm_clobbers(Node *node, Token **rest, Token *tok)
{
    int idx = node->asm_nclobbers;
    if (idx >= MAX_ASM_OPERANDS)
        error_tok(tok, "%s:%d: in %s: too many clobbers", __FILE__, __LINE__, __func__);

    node->asm_clobbers[idx] = strdup(tok->str);
    node->asm_nclobbers++;
    *rest = tok->next;
}
