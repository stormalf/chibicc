// This file manages extended assembly.
//	asm <optional stuff> (
//	    "assembler template"
//	    : outputs
//	    : inputs
//	    : clobbers
//	    : labels)
// references https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html and https://www.felixcloutier.com/documents/gcc-asm.html
//
// Special format strings
// In addition to the tokens described by the input, output, and goto operands, these tokens have special meanings in the assembler template:
//
//‘%%’
// Outputs a single ‘%’ into the assembler code.
//
//‘%=’
// Outputs a number that is unique to each instance of the asm statement in the entire compilation. This option is useful when creating local labels and referring to them multiple times in a single template that generates multiple assembler instructions.
//
//‘%{’
//‘%|’
//‘%}’
// Outputs ‘{’, ‘|’, and ‘}’ characters (respectively) into the assembler code.
// When unescaped, these characters have special meaning to indicate multiple assembler dialects.

#include "chibicc.h"
#define EXTASM_C "extended_asm.c"

typedef enum
{
    AT_TEMPLATE, // assembler template
    AT_OUTPUT,   // outputs
    AT_INPUT,    // inputs
    AT_CLOBBER,  // clobbers
    AT_LABEL,    // labels
} AsmType;

typedef enum
{
    CT_REGISTER = 1,  // register
    CT_MEMORY = 2,    // memory
    CT_IMMEDIATE = 4, // immediate value, integer constant
    CT_ANY = 7,       // could be a register or a memory or an immediate value
} ConstraintType;

//
//+ means that the output is actually a read-write value.
//=& means that the output is an early-clobber output. Its initial value is unspecified.
//= means that the output is write-only.
//=@ccCOND is a special case of = that allows you to query the result of a condition code at the end of your assembly statement.

typedef enum
{
    CP_READWRITEREG = 1, // +r
    CP_READWRITEMEM,     // +m
    CP_CLOBBEROUTPUTREG, // =&r
    CP_WRITEONLYREG,     // =r
    CP_WRITEONLYMEM,     // =m
    CP_COND,             // =@ccCOND
} ConstraintPrefix;

static int nbOperand = 0;

char *extended_asm(Node *node, Token **rest, Token *tok)
{
    char *template = tok->str;
    char *asm_str;
    char *output_str;
    char *input_str;
    int asmtype = 0;
    nbOperand = 0;
    while (!equal(tok->next, ";") && !equal(tok, ";"))
    {
        switch (asmtype)
        {
        case AT_TEMPLATE: // assembler template
            break;
        case AT_OUTPUT: // outputs
            output_str = output_asm(node, rest, tok);
            tok = *rest;
            break;
        case AT_INPUT: // inputs
            input_str = input_asm(node, rest, tok);
            tok = *rest;
            break;
        case AT_CLOBBER: // clobbers
            break;
        case AT_LABEL: // labels
            break;
        default: // error
            error_tok(tok, "%s : in extended_asm function : too much parameters or complex extended assembly not managed!", EXTASM_C);
        }
        if (equal(tok, ":"))
            asmtype += 1;

        tok = tok->next;
    }
    asm_str = subst_asm(template, output_str, input_str);
    *rest = tok;
    return asm_str;
}

char *output_asm(Node *node, Token **rest, Token *tok)
{
    int cstPrefix = 0;
    char *output_str;
    VarScope *sc;
    while (!equal(tok->next, ":") && !equal(tok->next, ";"))
    {
        // register in write only mode
        if (tok->kind == TK_STR && !strncmp(tok->str, "=r", tok->len))
            cstPrefix = CP_WRITEONLYREG;
        // check if the register constraint is followed by a variable like "=r" (val)
        else if (equal(tok, "("))
        {
            tok = skip(tok, "(");
            // check if the variable is defined
            if (tok->kind == TK_IDENT)
            {
                sc = find_var(tok);
                if (!sc)
                    error_tok(tok, "%s : in output_asm function : variable undefined", EXTASM_C);
                if (!sc->var->ty)
                    error_tok(tok, "%s : in output_asm function : variable type unknown", EXTASM_C);
                // retrieve the size of the variable to determine the register to use here we use RAX variation
                output_str = reg_ax(sc->var->ty->size);
                if (!output_str)
                    error_tok(tok, "%s : in output_asm function : output_str is null!", EXTASM_C);
                // skip the variable to go to next token that should be a ")"
                tok = tok->next;
                nbOperand++;
                *rest = skip(tok, ")");
                return output_str;
            }
            error_tok(tok, "%s : in output_asm function : identifier expected!", EXTASM_C);
        }
        else
            error_tok(tok, "%s : in output_asm function : output constraint not managed yet!", EXTASM_C);

        tok = tok->next;
    }
    return NULL;
}

char *input_asm(Node *node, Token **rest, Token *tok)
{
    VarScope *sc;
    char *input_str;
    while (!equal(tok->next, ":") && !equal(tok->next, ";"))
    {
        // register in write only mode
        if (tok->kind == TK_STR && !strncmp(tok->str, "0", tok->len))
            input_str = "%0";
        else if (equal(tok, "("))
        {
            tok = skip(tok, "(");
            // check if the variable is defined
            if (tok->kind == TK_IDENT)
            {
                sc = find_var(tok);
                if (!sc)
                    error_tok(tok, "%s : in input_asm function : variable undefined", EXTASM_C);
                tok = tok->next;
                *rest = skip(tok, ")");
                return input_str;
            }
        }
        else
            error_tok(tok, "%s : in input_asm function : input complex constraint not managed yet!", EXTASM_C);

        tok = tok->next;
    }
    return NULL;
}

char *subst_asm(char *template, char *output_str, char *input_str)
{
    return string_replace(template, input_str, output_str);
}

char *string_replace(char *str, char *oldstr, char *newstr)
{
    char bstr[strlen(str)];
    memset(bstr, 0, sizeof(bstr));
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (!strncmp(str + i, oldstr, strlen(oldstr)))
        {
            strcat(bstr, newstr);
            i += strlen(oldstr) - 1;
        }
        else
        {
            strncat(bstr, str + i, 1);
        }
    }

    strcpy(str, bstr);
    return str;
}