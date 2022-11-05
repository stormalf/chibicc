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
    Token *input;      // store the token corresponding to input
    char *input_str;   // store the generated instruction
    char *input_value; // store the immediate value
    int index;         // store the index
    char letter;       // store the letter corresponding to input
    int order;         // store the parameter order
    int size;          // store the size to determine the operation to do ex movl movb movw mov
    bool isVariable;   // store true if it's a variable otherwise false for immediate value
    bool isAddress;    // store true if it's an address pointer
} AsmInput;

typedef struct
{
    Token *output;    // store the token corresponding to input
    char *output_str; // store the generated instruction
    char *prefix;     //= or +
    char *reg;        // store the register that corresponds to the variable size
    char letter;      // to store a b r
    int index;        // order in output
    int size;         // store the size to determine the operation to do
    bool isRegister;  // r
    bool isMemory;    // m
    bool isAlpha;     // if is not r neither m is considered Alpha
    int order;        // order parameter
    bool isVariable;  // store true if it's a variable otherwise false for immediate value
    bool isAddress;   // store true if it's an address pointer
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

// typedef enum
// {
//     CT_REGISTER = 1,  // register
//     CT_MEMORY = 2,    // memory
//     CT_IMMEDIATE = 4, // immediate value, integer constant
//     CT_ANY = 7,       // could be a register or a memory or an immediate value
// } ConstraintType;

//
//+ means that the output is actually a read-write value.
//=& means that the output is an early-clobber output. Its initial value is unspecified.
//= means that the output is write-only.
//=@ccCOND is a special case of = that allows you to query the result of a condition code at the end of your assembly statement.

// typedef enum
// {
//     CP_READWRITEREG = 1, // +r
//     CP_READWRITEMEM,     // +m
//     CP_CLOBBEROUTPUTREG, // =&r
//     CP_WRITEONLYREG,     // =r
//     CP_WRITEONLYMEM,     // =m
//     CP_WRITEONLYOTH,     // =a =b =c...
//     CP_COND,             // =@ccCOND
// } ConstraintPrefix;

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
    char *output_asm_str = calloc(1, sizeof(char) * 300);
    char *input_final = calloc(1, sizeof(char) * 300);
    char *asm_str = calloc(1, sizeof(char) * 500);
    char *template = tok->str;
    asmExt->template->templatestr = template;
    asmExt->template->hasPercent = check_template(template);
    char *input_asm_str;
    char *output_str;
    char *output_loading;
    char *input_str;
    int asmtype = 0;
    nbInput = 0;
    nbOutput = 0;
    nbClobber = 0;
    nbLabel = 0;
    // printf("======%s\n", tok->loc);
    while (!equal(tok->next, ";") && !equal(tok, ";"))
    {
        switch (asmtype)
        {
        case AT_TEMPLATE: // assembler template
            break;
        case AT_OUTPUT: // outputs
            output_str = output_asm(node, rest, tok);
            // generate output instruction for each output variable
            output_loading = generate_output_asm(output_str);
            strncat(output_asm_str, output_loading, strlen(output_loading));
            nbOutput++;
            tok = *rest;
            break;
        case AT_INPUT: // inputs
            // return %0, %1 or %x
            input_str = input_asm(node, rest, tok);
            // generate input instruction to load the parameter into register
            input_asm_str = generate_input_asm(input_str);
            // retrieve output index corresponding to letter
            int regIndex = retrieve_output_index(asmExt->input[nbInput]->letter);
            // if index not found it means that we have in inputs "0", "1"...
            if (regIndex < 0)
                regIndex = asmExt->input[nbInput]->index;
            char *reg = asmExt->output[regIndex]->reg;
            if (!reg)
                error_tok(tok, "%s : in extended_asm function : register is null!", EXTASM_C);
            // replace %x by the correct register
            input_asm_str = subst_asm(input_asm_str, reg, input_str);
            // concatenate the input final strings to add to the assembly
            strncat(input_final, input_asm_str, strlen(input_asm_str));
            nbInput++;
            tok = *rest;
            break;
        case AT_CLOBBER: // clobbers
            // asmExt->clobber[nbClobber]->clobber = tok->loc;
            // tok = tok->next;
            // nbClobber++;
            error_tok(tok, "%s : in extended_asm function : clobber not managed yet!", EXTASM_C);
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
    if (output_asm_str != NULL)
    {
        strncat(asm_str, output_asm_str, strlen(output_asm_str));
    }
    // replace %% by %
    // replace ‘%{’ by '{', ‘%|’ by '|' and ‘%}’ by '}'
    asm_str = subst_asm(asm_str, " %", "%%");
    asm_str = subst_asm(asm_str, " {", "%{");
    asm_str = subst_asm(asm_str, " |", "%|");
    asm_str = subst_asm(asm_str, " }", "%}");
    *rest = tok;
    // free memory
    for (int i = 0; i < 10; i++)
        free(asmExt->input[i]);
    for (int i = 0; i < 10; i++)
        free(asmExt->output[i]);
    for (int i = 0; i < 10; i++)
        free(asmExt->clobber[i]);
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
                asmExt->output[nbOutput]->reg = "%rax";
                asmExt->output[nbOutput]->letter = 'r';
            }
            else if (!strncmp(tok->str, "=m", tok->len) || !strncmp(tok->str, "+m", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                if (!strncmp(tok->str, "=m", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else
                    asmExt->output[nbOutput]->prefix = "+";
                asmExt->output[nbOutput]->reg = "%rax";
                asmExt->output[nbOutput]->letter = 'm';
            }
            // assuming that it's =a =b ???
            else if (!strncmp(tok->str, "=a", tok->len) || !strncmp(tok->str, "=b", tok->len) || !strncmp(tok->str, "=c", tok->len) || !strncmp(tok->str, "=d", tok->len))
            {
                if (!strncmp(tok->str, "=a", tok->len))
                {
                    asmExt->output[nbOutput]->reg = "%rax";
                    asmExt->output[nbOutput]->letter = 'a';
                }
                else if (!strncmp(tok->str, "=b", tok->len))
                {
                    asmExt->output[nbOutput]->reg = "%rbx";
                    asmExt->output[nbOutput]->letter = 'b';
                }
                else if (!strncmp(tok->str, "=c", tok->len))
                {
                    asmExt->output[nbOutput]->reg = "%rcx";
                    asmExt->output[nbOutput]->letter = 'c';
                }
                else if (!strncmp(tok->str, "=d", tok->len))
                {
                    asmExt->output[nbOutput]->reg = "%rdx";
                    asmExt->output[nbOutput]->letter = 'd';
                }
                else
                    error_tok(tok, "%s : in output_asm function : not implemented yet!", EXTASM_C);

                asmExt->output[nbOutput]->isAlpha = true;
                asmExt->output[nbOutput]->prefix = "=";
            }
            asmExt->output[nbOutput]->index = nbOutput;
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
                asmExt->output[nbOutput]->size = sc->var->ty->size;
                asmExt->output[nbOutput]->isVariable = true;
                asmExt->output[nbOutput]->output = tok;
                if (sc->var->funcname)
                    asmExt->output[nbOutput]->order = retrieve_parameter_order(sc->var->order, sc->var->funcname);
                else
                    asmExt->output[nbOutput]->order = 0;
                asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                asmExt->output[nbOutput]->output_str = asmExt->output[nbOutput]->reg;
                // skip the variable to go to next token that should be a ")"
                // tok = tok->next;
                tok = tok->next;
                *rest = skip(tok, ")");
                output_str = asmExt->output[nbOutput]->output_str;
                if (!output_str)
                    error_tok(tok, "%s : in output_asm function : output_str is null!", EXTASM_C);
                return output_str;
            }
            // pointer
            else if (equal(tok, "*"))
            {
                consume(&tok, tok, "*");
                if (tok->kind == TK_IDENT)
                {

                    asmExt->output[nbOutput]->isAddress = true;
                    sc = find_var(tok);
                    if (!sc)
                        error_tok(tok, "%s : in output_asm function : variable undefined2", EXTASM_C);
                    if (!sc->var->ty)
                        error_tok(tok, "%s : in output_asm function : variable type unknown2", EXTASM_C);
                    // retrieve the size of the variable to determine the register to use here we use RAX variation
                    // skip the variable to go to next token that should be a ")"
                    asmExt->output[nbOutput]->size = sc->var->ty->pointertype->size;
                    asmExt->output[nbOutput]->order = retrieve_parameter_order(sc->var->order, sc->var->funcname);
                    asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                    asmExt->output[nbOutput]->output_str = asmExt->output[nbOutput]->reg;
                    tok = tok->next;
                    *rest = skip(tok, ")");
                    output_str = asmExt->output[nbOutput]->output_str;
                    if (!output_str)
                        error_tok(tok, "%s : in output_asm function : output_str is null!2", EXTASM_C);

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
        if (tok->kind == TK_STR && !strncmp(tok->str, "0", tok->len))
        {
            input_str = "%0";
            asmExt->input[nbInput]->index = 0;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "1", tok->len))
        {
            input_str = "%1";
            asmExt->input[nbInput]->index = 1;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "2", tok->len))
        {
            input_str = "%2";
            asmExt->input[nbInput]->index = 2;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "3", tok->len))
        {
            input_str = "%3";
            asmExt->input[nbInput]->index = 3;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "a", tok->len))
        {
            input_str = retrieve_output_index_str('a');
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'a';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "b", tok->len))
        {
            input_str = retrieve_output_index_str('b');
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'b';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "c", tok->len))
        {
            input_str = retrieve_output_index_str('c');
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'c';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "d", tok->len))
        {
            input_str = retrieve_output_index_str('d');
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'd';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "m", tok->len))
        {
            input_str = retrieve_output_index_str('m');
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'm';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "r", tok->len))
        {
            input_str = retrieve_output_index_str('r');
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'r';
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
                asmExt->input[nbInput]->size = sc->var->ty->size;
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
                asmExt->input[nbInput]->size = tok->ty->size;
                tok = tok->next;
                *rest = skip(tok, ")");
                return input_str;
            } // pointer
            else if (equal(tok, "*"))
            {
                consume(&tok, tok, "*");
                if (tok->kind == TK_IDENT)
                {
                    sc = find_var(tok);
                    if (!sc)
                        error_tok(tok, "%s : in input_asm function : variable undefined2", EXTASM_C);
                    asmExt->input[nbInput]->input = tok;
                    asmExt->input[nbInput]->isVariable = true;
                    asmExt->input[nbInput]->isAddress = true;
                    asmExt->input[nbInput]->input_str = input_str;
                    asmExt->input[nbInput]->size = sc->var->ty->size;
                    tok = tok->next;
                    *rest = skip(tok, ")");
                    return input_str;
                }
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
        strncat(tmp, opcode(asmExt->input[nbInput]->size), strlen(opcode(asmExt->input[nbInput]->size)));
        strncat(tmp, load_variable(asmExt->input[nbInput]->order), strlen(load_variable(asmExt->input[nbInput]->order)));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->input_str, strlen(asmExt->input[nbInput]->input_str));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else
    {
        strncat(tmp, opcode(asmExt->input[nbInput]->size), strlen(opcode(asmExt->input[nbInput]->size)));
        strncat(tmp, " $", 3);
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
    return strchr(template, '%') != NULL;
}

// generate input assembly instruction
char *generate_output_asm(char *output_str)
{
    char *tmp = calloc(1, sizeof(char) * 300);
    if (asmExt->output[nbOutput]->isVariable && !asmExt->output[nbOutput]->isAddress)
    {
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->output_str, strlen(asmExt->output[nbOutput]->output_str));
        strncat(tmp, ", ", 3);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->order), strlen(load_variable(asmExt->output[nbOutput]->order)));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else if (!asmExt->output[nbOutput]->isAddress)
    {
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, " $", 3);
        strncat(tmp, asmExt->input[nbInput]->input_value, strlen(asmExt->input[nbInput]->input_value));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->input_str, strlen(asmExt->input[nbInput]->input_str));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else
    {
        strncat(tmp, "\n", 2);
        strncat(tmp, "  movq ", 8);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->order), strlen(load_variable(asmExt->output[nbOutput]->order)));
        strncat(tmp, ", %rsi\n", 8);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->output_str, strlen(asmExt->output[nbOutput]->output_str));
        strncat(tmp, ", (%rsi)\n", 10);
        return tmp;
    }
    return NULL;
}

char *load_variable(int order)
{
    switch (order)
    {
    case 0:
        return "-12(%rbp)";
    case 1:
        return "-24(%rbp)";
    case 2:
        return "-32(%rbp)";
    case 3:
        return "-40(%rbp)";
    case 4:
        return "-48(%rbp)";
    default:
        error("%s: in load_variable : nb of parameters > 5 not managed yet!", EXTASM_C);
    }
}

char *opcode(int size)
{
    switch (size)
    {
    case 1:
        return "\n  movb ";
    case 2:
        return "\n  movw ";
    case 4:
        return "\n  movl ";
    case 8:
        return "\n  movq ";
    default:
        error("%s: in opcode : size %d unexpected!", EXTASM_C, size);
    }
}

// retrieve the order parameter
// chibicc stores them in descendent order the last one is 0, the previous one is 1...
// we retrieve the number of parameters and convert the order in the ascendent order
// the first one becomes 0, the second one becomes 1... the last one n-1
int retrieve_parameter_order(int order, char *funcname)
{
    Obj *fn = find_func(funcname);
    if (fn)
        return (fn->nbparm - 1 - order);

    return 0;
}

// update register following the size
char *update_register_size(char *reg, int size)
{
    if (!strncmp(reg, "%rax", 5))
        return reg_ax(size);
    else if (!strncmp(reg, "%rbx", 5))
        return reg_bx(size);
    else if (!strncmp(reg, "%rcx", 5))
        return reg_cx(size);
    else if (!strncmp(reg, "%rdx", 5))
        return reg_dx(size);
    else
        error("%s: in update_register_size : reg %s unexpected!", EXTASM_C, reg);
}

char *retrieve_output_index_str(char letter)
{
    for (int i = 0; i < nbOutput; i++)
    {
        if (asmExt->output[i]->letter == letter)
        {
            switch (asmExt->output[i]->index)
            {
            case 0:
                return "%0";
            case 1:
                return "%1";
            case 2:
                return "%2";
            case 3:
                return "%3";
            case 4:
                return "%4";
            case 5:
                return "%5";
            }
        }
    }

    return "%0";
}

int retrieve_output_index(char letter)
{
    for (int i = 0; i < nbOutput; i++)
    {
        if (asmExt->output[i]->letter == letter)
            return asmExt->output[i]->index;
    }

    return -1;
}