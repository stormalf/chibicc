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

typedef struct
{
    Token *input;
    char *input_str;
    char *input_value;
    int index;
    bool isVariable;
} AsmInput;

typedef struct
{
    Token *output;
    char *output_str;
    char *prefix; //= or +
    char *reg;
    bool isRegister; // r
    bool isMemory;   // m
    bool isAlpha;    // a b ...
} AsmOutput;

typedef struct
{
    char *templatestr;
    bool hasPercent;
} AsmTemplate;

typedef struct
{
    char *clobber;
} AsmClobber;

typedef struct
{
    AsmTemplate *template;
    AsmOutput *output[10];
    AsmInput *input[10];
    AsmClobber *clobber[10];
    int nboutput;
    int nbinput;
    int nbclobber;
    int nblabel;
} AsmExtended;

typedef AsmExtended AsmExtended;

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
    CP_WRITEONLYOTH,     // =a =b =c...
    CP_COND,             // =@ccCOND
} ConstraintPrefix;

static AsmExtended *asmExt;
static int nbInput = 0;
static int nbOutput = 0;
static int nbClobber = 0;
static int nbLabel = 0;

char *extended_asm(Node *node, Token **rest, Token *tok)
{
    // allocate memory for all structs needed
    asmExt = calloc(1, sizeof(AsmExtended));
    asmExt->template = calloc(1, sizeof(AsmTemplate));
    for (int i = 0; i < 10; i++)
        asmExt->input[i] = calloc(1, sizeof(AsmInput));
    for (int i = 0; i < 10; i++)
        asmExt->output[i] = calloc(1, sizeof(AsmOutput));
    for (int i = 0; i < 10; i++)
        asmExt->clobber[i] = calloc(1, sizeof(AsmClobber));
    char *template = tok->str;
    asmExt->template->templatestr = template;
    asmExt->template->hasPercent = check_template(template);
    char *asm_str;
    char *input_asm_str;
    char *output_str;
    char *input_str;
    char *input_final = calloc(1, sizeof(char) * 300);
    int asmtype = 0;
    while (!equal(tok->next, ";") && !equal(tok, ";"))
    {
        switch (asmtype)
        {
        case AT_TEMPLATE: // assembler template
            break;
        case AT_OUTPUT: // outputs
            output_str = output_asm(node, rest, tok);
            nbOutput++;
            tok = *rest;
            break;
        case AT_INPUT: // inputs
            // return %0, %1 or %x
            input_str = input_asm(node, rest, tok);
            // return movl instruction only if template contain %
            if (!check_template(template))
            {
                input_asm_str = generate_input_asm(input_str);
                int regIndex = asmExt->input[nbInput]->index;
                char *reg = asmExt->output[regIndex]->reg;
                input_asm_str = subst_asm(input_asm_str, reg, input_str);
                strncat(input_final, input_asm_str, strlen(input_asm_str));
            }

            nbInput++;
            tok = *rest;
            break;
        case AT_CLOBBER: // clobbers
            asmExt->clobber[nbClobber]->clobber = tok->loc;
            tok = tok->next;
            nbClobber++;
            // error_tok(tok, "%s : in extended_asm function : clobber not managed yet!", EXTASM_C);
            break;
        case AT_LABEL: // labels
            nbLabel++;
            error_tok(tok, "%s : in extended_asm function : label not managed yet!", EXTASM_C);
            break;
        default: // error
            error_tok(tok, "%s : in extended_asm function : too much parameters or complex extended assembly not managed!", EXTASM_C);
        }
        if (equal(tok, ":"))
            asmtype += 1;

        tok = tok->next;
    }
    asm_str = subst_asm(template, output_str, input_str);
    if (input_final != NULL)
    {
        strncat(input_final, asm_str, strlen(asm_str));
        asm_str = input_final;
    }
    // replace %% by % if found
    asm_str = subst_asm(asm_str, " %", "%%");
    // replace ‘%{’ by '{', ‘%|’ by '|' and ‘%}’ by '}'
    asm_str = subst_asm(asm_str, " {", "%{");
    asm_str = subst_asm(asm_str, " |", "%|");
    asm_str = subst_asm(asm_str, " }", "%}");
    *rest = tok;
    return asm_str;
}

char *output_asm(Node *node, Token **rest, Token *tok)
{
    char *output_str;
    VarScope *sc;
    while (!equal(tok->next, ":") && !equal(tok->next, ";"))
    {
        // register in write only mode
        // check if the register constraint is followed by a variable like "=r" (val)
        if (tok->kind == TK_STR)
        {
            if (!strncmp(tok->str, "=r", tok->len) || !strncmp(tok->str, "+r", tok->len))
            {
                asmExt->output[nbOutput]->isRegister = true;
                if (!strncmp(tok->str, "=r", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else
                    asmExt->output[nbOutput]->prefix = "+";
            }
            else if (!strncmp(tok->str, "=m", tok->len) || !strncmp(tok->str, "+m", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                if (!strncmp(tok->str, "=m", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else
                    asmExt->output[nbOutput]->prefix = "+";
            }
            // assuming that it's =a =b ???
            else if (!strncmp(tok->str, "=a", tok->len) || !strncmp(tok->str, "=b", tok->len) || !strncmp(tok->str, "=c", tok->len) || !strncmp(tok->str, "=d", tok->len))
            {
                if (!strncmp(tok->str, "=a", tok->len))
                    asmExt->output[nbOutput]->reg = "%eax";
                else if (!strncmp(tok->str, "=b", tok->len))
                    asmExt->output[nbOutput]->reg = "%ebx";
                else if (!strncmp(tok->str, "=c", tok->len))
                    asmExt->output[nbOutput]->reg = "%ecx";
                else if (!strncmp(tok->str, "=d", tok->len))
                    asmExt->output[nbOutput]->reg = "%edx";
                else
                    error_tok(tok, "%s : in output_asm function : not implemented yet!", EXTASM_C);

                asmExt->output[nbOutput]->isAlpha = true;
                asmExt->output[nbOutput]->prefix = "=";
            }
        }

        // skip the comma
        else if (equal(tok, ","))
            tok = skip(tok, ",");
        // manage the variable inside parenthesis
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
                asmExt->output[nbOutput]->output = tok;
                asmExt->output[nbOutput]->output_str = output_str;
                tok = tok->next;
                *rest = skip(tok, ")");
                return output_str;
            }
            // pointer
            else if (equal(tok, "*"))
            {
                consume(&tok, tok, "*");
                if (tok->kind == TK_IDENT)
                {
                    sc = find_var(tok);
                    if (!sc)
                        error_tok(tok, "%s : in output_asm function : variable undefined2", EXTASM_C);
                    if (!sc->var->ty)
                        error_tok(tok, "%s : in output_asm function : variable type unknown2", EXTASM_C);
                    // retrieve the size of the variable to determine the register to use here we use RAX variation
                    output_str = reg_ax(sc->var->ty->size);
                    if (!output_str)
                        error_tok(tok, "%s : in output_asm function : output_str is null!2", EXTASM_C);
                    // skip the variable to go to next token that should be a ")"
                    tok = tok->next;
                    *rest = skip(tok, ")");
                    return output_str;
                }
            }
            else
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
    char *input_str = calloc(1, sizeof(char) * 20);
    char *input_value = calloc(1, sizeof(char) * 20);
    while (!equal(tok->next, ":") && !equal(tok->next, ";"))
    {
        // register in write only mode
        if (tok->kind == TK_STR && (!strncmp(tok->str, "0", tok->len) || !strncmp(tok->str, "a", tok->len)))
        {
            input_str = "%0";
            asmExt->input[nbInput]->index = 0;
        }
        else if (tok->kind == TK_STR && (!strncmp(tok->str, "1", tok->len) || !strncmp(tok->str, "b", tok->len)))
        {
            input_str = "%1";
            asmExt->input[nbInput]->index = 1;
        }
        else if (tok->kind == TK_STR && (!strncmp(tok->str, "2", tok->len) || !strncmp(tok->str, "c", tok->len)))
        {
            input_str = "%2";
            asmExt->input[nbInput]->index = 2;
        }
        else if (tok->kind == TK_STR && (!strncmp(tok->str, "3", tok->len) || !strncmp(tok->str, "d", tok->len)))
        {
            input_str = "%3";
            asmExt->input[nbInput]->index = 3;
        }
        else if (equal(tok, "("))
        {
            tok = skip(tok, "(");
            // check if the variable is defined
            if (tok->kind == TK_IDENT)
            {
                sc = find_var(tok);
                if (!sc)
                    error_tok(tok, "%s : in input_asm function : variable undefined", EXTASM_C);

                asmExt->input[nbInput]->input = tok;
                asmExt->input[nbInput]->isVariable = true;
                asmExt->input[nbInput]->input_str = input_str;
                tok = tok->next;
                *rest = skip(tok, ")");
                return input_str;
            } // immediate value
            else if (tok->kind == TK_NUM)
            {
                int length = snprintf(NULL, 0, "%ld", tok->val);
                if (tok->val == 0)
                    strncat(input_value, "0 ", 3);
                else
                    snprintf(input_value, length + 1, "%ld", tok->val);
                asmExt->input[nbInput]->input = tok;
                asmExt->input[nbInput]->isVariable = false;
                asmExt->input[nbInput]->input_str = input_str;
                asmExt->input[nbInput]->input_value = input_value;
                tok = tok->next;
                *rest = skip(tok, ")");
                return input_str;
            }
        }
        else if (equal(tok, ","))
            tok = skip(tok, ",");
        else
            error_tok(tok, "%s : in input_asm function : input complex constraint not managed yet!", EXTASM_C);

        tok = tok->next;
    }
    return NULL;
}

// do the susbtitution into the template
char *subst_asm(char *template, char *output_str, char *input_str)
{
    return string_replace(template, input_str, output_str);
}

// generic string replace function
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

    strncpy(str, bstr, strlen(bstr));
    return str;
}

// generate input assembly instruction
char *generate_input_asm(char *input_str)
{
    char *tmp = calloc(1, sizeof(char) * 100);
    if (asmExt->input[nbInput]->isVariable)
    {
        strncat(tmp, "	movl	-12(%rbp), ", 25);
        strncat(tmp, asmExt->input[nbInput]->input_str, strlen(asmExt->input[nbInput]->input_str));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else
    {
        strncat(tmp, "	movl	$", 15);
        strncat(tmp, asmExt->input[nbInput]->input_value, strlen(asmExt->input[nbInput]->input_value));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->input_str, strlen(asmExt->input[nbInput]->input_str));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    return NULL;
}

// check if template contains %
bool check_template(char *template)
{
    return strchr(template, '%');
}
