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
    char *variableNumber;     //store the variable %0, %1...
    char *input_value; // store the immediate value
    char *reg;        // store the register that corresponds to the variable size    
    int index;         // store the index
    char letter;       // store the letter corresponding to input
    int offset;         // store the offset
    int size;          // store the size to determine the operation to do ex movl movb movw mov
    bool isVariable;   // store true if it's a variable otherwise false for immediate value
    bool isAddress;    // store true if it's an address pointer
} AsmInput;

typedef struct
{
    Token *output;    // store the token corresponding to input
    char *variableNumber;     //store the variable %0, %1...
    char *prefix;     //= or +
    char *reg;        // store the register that corresponds to the variable size
    char letter;      // to store a b r
    int index;        // order in output
    int size;         // store the size to determine the operation to do
    bool isRegister;  // r
    bool isMemory;    // m
    bool isAlpha;     // if is not r neither m is considered Alpha
    int offset;        // store the offset
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
static int asmtype = 0;

char *extended_asm(Node *node, Token **rest, Token *tok, Obj *locals)
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
    char *output_loading;
    asmtype = 0;
    nbInput = 0;
    nbOutput = 0;
    nbClobber = 0;
    nbLabel = 0;
    //clear the registerUsed array
    clear_register_used();
    //mark the register used if found in template
    check_register_in_template(template);
    
    while (!equal(tok->next, ";") && !equal(tok, ";"))
    {
        switch (asmtype)
        {
        case AT_TEMPLATE: // assembler template
            break;
        case AT_OUTPUT: // outputs
            output_asm(node, rest, tok, locals);
            // generate output instruction for each output variable
            if (!asmExt->output[nbOutput]->variableNumber)
                error("%s : in extended_asm function extended_asm :asmExt->output[nbOutput]->variableNumber is null!", EXTASM_C);
            output_loading = generate_output_asm(asmExt->output[nbOutput]->variableNumber);
            // replace %9 by the correct register
            if (!output_loading)
               error("%s : in extended_asm function extended_asm :output_loading is null!", EXTASM_C);
            if (!asmExt->output[nbOutput]->reg)
               error("%s : in extended_asm function extended_asm :asmExt->output[nbOutput]->reg is null!", EXTASM_C);                 
            output_loading = subst_asm(output_loading, asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->variableNumber);
            //generate the ouput instruction
            strncat(output_asm_str, output_loading, strlen(output_loading));
            
            nbOutput++;
            tok = *rest;
            break;
        case AT_INPUT: // inputs
            // return %0, %1 or %x
            input_asm(node, rest, tok, locals);
            // generate input instruction to load the parameter into register
            if (!asmExt->input[nbInput]->variableNumber)
                error("%s : in extended_asm function extended_asm :asmExt->input[nbInput]->variableNumber is null!", EXTASM_C);
            input_asm_str = generate_input_asm(asmExt->input[nbInput]->variableNumber);
            //replace %9, by the correct
            if (!input_asm_str)
                error("%s : in extended_asm function extended_asm :input_asm_str is null!", EXTASM_C);
            if (!asmExt->input[nbInput]->reg)
                error("%s : in extended_asm function extended_asm :asmExt->input[nbInput]->reg is null!", EXTASM_C);
            input_asm_str = subst_asm(input_asm_str, asmExt->input[nbInput]->reg, asmExt->input[nbInput]->variableNumber);
            // concatenate the input final strings to add to the assembly
            strncat(input_final, input_asm_str, strlen(input_asm_str));

            nbInput++;
            tok = *rest;
            break;
        case AT_CLOBBER: // clobbers
            asmExt->clobber[nbClobber]->clobber = tok->loc;
            tok = tok->next;
            nbClobber++;
            //error_tok(tok, "%s : in extended_asm function : clobber not managed yet!", EXTASM_C);
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

    //replace each %9 by the correct output register
    for (int i = 0; i < nbOutput; i++)
    {
        asm_str = subst_asm(template, asmExt->output[i]->reg, asmExt->output[i]->variableNumber);
    }
    
    //replace each %9 by the correct input register
    for (int i = 0; i < nbInput; i++)
    {
        
        asm_str = subst_asm(template, asmExt->input[i]->reg, asmExt->input[i]->variableNumber);                
    }

    //generate the input instructions before the output 
    if (input_final != NULL)
    {
        strncat(input_final, asm_str, strlen(asm_str));
        asm_str = input_final;
    }
    //generate the output instructions
    if (output_asm_str != NULL)
    {
        strncat(asm_str, output_asm_str, strlen(output_asm_str));
    }

    //replace special characters
    // replace %% by %
    // replace ‘%{’ by '{', ‘%|’ by '|' and ‘%}’ by '}'
    asm_str = subst_asm(asm_str, " %", "%%");
    asm_str = subst_asm(asm_str, " {", "%{");
    asm_str = subst_asm(asm_str, " |", "%|");
    asm_str = subst_asm(asm_str, " }", "%}");
    //printf("=====%s\n", asm_str);
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

void output_asm(Node *node, Token **rest, Token *tok, Obj *locals)
{
    
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
                asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                asmExt->output[nbOutput]->letter = 'r';
                asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                
            }
            else if (!strncmp(tok->str, "=m", tok->len) || !strncmp(tok->str, "+m", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                if (!strncmp(tok->str, "=m", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else
                    asmExt->output[nbOutput]->prefix = "+";
                asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                asmExt->output[nbOutput]->letter = 'm';
                asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                
            }
            // assuming that it's =a =b ???
            else if (!strncmp(tok->str, "=a", tok->len) || !strncmp(tok->str, "=b", tok->len) || !strncmp(tok->str, "=c", tok->len) || !strncmp(tok->str, "=d", tok->len))
            {
                if (!strncmp(tok->str, "=a", tok->len))
                {
                    asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                    asmExt->output[nbOutput]->letter = 'a';

                }
                else if (!strncmp(tok->str, "=b", tok->len))
                {
                    asmExt->output[nbOutput]->reg = specific_register_available("%rbx");
                    asmExt->output[nbOutput]->letter = 'b';
                }
                else if (!strncmp(tok->str, "=c", tok->len))
                {
                    asmExt->output[nbOutput]->reg = specific_register_available("%rcx");
                    asmExt->output[nbOutput]->letter = 'c';
                }
                else if (!strncmp(tok->str, "=d", tok->len))
                {
                    asmExt->output[nbOutput]->reg = specific_register_available("%rdx");
                    asmExt->output[nbOutput]->letter = 'd';
                }
                else
                    error_tok(tok, "%s : in output_asm function : not implemented yet!", EXTASM_C);

                asmExt->output[nbOutput]->isAlpha = true;
                asmExt->output[nbOutput]->prefix = "=";
                asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                
                
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
                //TODO potential issue if several variables with same name inside different functions.
                //need to check if the variable is in the correct function
                sc = find_var(tok);
                if (!sc)
                    error_tok(tok, "%s : in output_asm function : variable undefined", EXTASM_C);
                if (!sc->var->ty)
                    error_tok(tok, "%s : in output_asm function : variable type unknown", EXTASM_C);
                // retrieve the size of the variable to determine the register to use here we use RAX variation
                asmExt->output[nbOutput]->size = sc->var->ty->size;
                asmExt->output[nbOutput]->isVariable = true;
                asmExt->output[nbOutput]->output = tok;
                
                if (sc->var->funcname) {
                    
                    update_offset(sc->var->funcname, locals);
                    asmExt->output[nbOutput]->offset = sc->var->offset;
                
                }
                else {
                    asmExt->output[nbOutput]->offset = 0;
                    
                }
                
                asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                // skip the variable to go to next token that should be a ")"
                // tok = tok->next;
                tok = tok->next;
                *rest = skip(tok, ")");
                return;
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
                    if (sc->var->funcname) {
                        update_offset(sc->var->funcname, locals);
                        asmExt->output[nbOutput]->offset = sc->var->offset;

                    } else {
                            asmExt->output[nbOutput]->offset = 0;                        

                    }
                    
                    asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                    
                    tok = tok->next;
                    *rest = skip(tok, ")");
                    return;
                }
            }
            else
                error_tok(tok, "%s : in output_asm function : identifier expected!", EXTASM_C);
        }

        else
            error_tok(tok, "%s : in output_asm function : output constraint not managed yet!", EXTASM_C);

        tok = tok->next;
    }
    return;
}

void input_asm(Node *node, Token **rest, Token *tok, Obj *locals)
{

    VarScope *sc;
    char *input_value = calloc(1, sizeof(char) * 20);
    asmExt->input[nbInput]->offset = 0;
    while (!equal(tok->next, ":") && !equal(tok->next, ";"))
    {
        // register in write only mode
        if (tok->kind == TK_STR && !strncmp(tok->str, "0", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(0);
            asmExt->input[nbInput]->index = 0;
            asmExt->input[nbInput]->reg = asmExt->output[0]->reg;
            
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "1", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(1);
            asmExt->input[nbInput]->index = 1;
            asmExt->input[nbInput]->reg = asmExt->output[1]->reg;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "2", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(2);
            asmExt->input[nbInput]->index = 2;
            asmExt->input[nbInput]->reg = asmExt->output[2]->reg;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "3", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(3);
            asmExt->input[nbInput]->index = 3;
            asmExt->input[nbInput]->reg = asmExt->output[3]->reg;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "a", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('a'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'a';
            asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('a')]->reg;
            
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "b", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('b'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'b';
            asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('b')]->reg;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "c", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('c'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'c';
            asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('c')]->reg;

        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "d", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('d'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'd';
            asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('d')]->reg;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "m", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%rax");
            asmExt->input[nbInput]->letter = 'm';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "r", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%rax");
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
                asmExt->input[nbInput]->size = sc->var->ty->size;
                if (sc->var->funcname) {
                    update_offset(sc->var->funcname, locals);
                    asmExt->input[nbInput]->offset = sc->var->offset;
                } 
                asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                tok = tok->next;
                *rest = skip(tok, ")");
                return;
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
                asmExt->input[nbInput]->input_value = input_value;
                asmExt->input[nbInput]->size = tok->ty->size;
                tok = tok->next;
                *rest = skip(tok, ")");
                return;
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
                    asmExt->input[nbInput]->size = sc->var->ty->size;
                    if (sc->var->funcname) {
                        update_offset(sc->var->funcname, locals);
                        asmExt->input[nbInput]->offset = sc->var->offset;
                    } 
                    asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                    tok = tok->next;
                    *rest = skip(tok, ")");
                    return;
                }
            }
        }
        else if (equal(tok, ","))
            tok = skip(tok, ",");
        else
            error_tok(tok, "%s : in input_asm function : input complex constraint not managed yet!", EXTASM_C);

        tok = tok->next;
    }
    return;
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
        strncat(tmp, load_variable(asmExt->input[nbInput]->offset), strlen(load_variable(asmExt->input[nbInput]->offset)));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else
    {
        strncat(tmp, opcode(asmExt->input[nbInput]->size), strlen(opcode(asmExt->input[nbInput]->size)));
        strncat(tmp, " $", 3);
        strncat(tmp, asmExt->input[nbInput]->input_value, strlen(asmExt->input[nbInput]->input_value));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    error("%s : in extended_asm function generate_input_asm : unexpected error!", EXTASM_C);
    //return NULL;
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
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        strncat(tmp, ", ", 3);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offset), strlen(load_variable(asmExt->output[nbOutput]->offset)));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else if (!asmExt->output[nbOutput]->isAddress)
    {
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, " $", 3);
        strncat(tmp, asmExt->input[nbInput]->input_value, strlen(asmExt->input[nbInput]->input_value));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else
    {
        strncat(tmp, "\n", 2);
        strncat(tmp, "  movq ", 8);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offset), strlen(load_variable(asmExt->output[nbOutput]->offset)));
        strncat(tmp, ", %rsi\n", 8);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        strncat(tmp, ", (%rsi)\n", 10);
        return tmp;
    }

    error("%s : in extended_asm function generate_output_asm : unexpected error!", EXTASM_C);

    //return NULL;
}

//codegen.c generates correctly the offset but it's too late.
//two possibilities:
// - write some specific value example %nameofvaroffset% that will be at the end after codegen.c replaced in assembly file
// by the correct value.
// - or trying to do the same job as codegen.c but here. It's the goal of assign_lvar_offsets_assembly in update_offset function
// need to test in several cases
char *load_variable(int offset)
{
    //generic solution to handle all values of offset 
    if (offset == 0)
        error("%s %d: in load_variable : incorrect offset or not managed yet!", EXTASM_C, offset);
    char *targetaddr = calloc(20, sizeof(char));
    
    int length = snprintf(targetaddr, sizeof(offset), "%d", offset);
    if (length < 0)
        error("%s %d %d: in load_variable : error during snprintf function!", EXTASM_C, offset, length);

    strncat(targetaddr, "(%rbp)", 7);
    return targetaddr;
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


// we need to update the offset to be able to use this information later for loading result into output variables.
// TODO we can have an issue here if several functions with same name. Probably need to find in a better way to avoid this issue.
void update_offset(char *funcname, Obj *locals)
{
    //printf(" function %s \n", funcname);
    Obj *fn = find_func(funcname);
    if (fn) {
        if (!fn->locals)
            fn->locals = locals;
       assign_lvar_offsets_assembly(fn);
    }

    
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
    else if (!strncmp(reg, "%rdi", 5))
        return reg_di(size);       
    else if (!strncmp(reg, "%rsi", 5))
        return reg_si(size);       
    else if (!strncmp(reg, "%r8", 5))
        return reg_si(size);                    
    else if (!strncmp(reg, "%r9", 5))
        return reg_si(size);               
    else
        return reg;
}


//returns the index corresponding to the letter received in parameter
int retrieve_output_index_from_letter(char letter)
{
    for (int i = 0; i < nbOutput; i++)
    {
        if (asmExt->output[i]->letter == letter)
            return asmExt->output[i]->index;
    }

    return -1;
}

//retrieve the variable number string like M0, %1, %2...
char * retrieveVariableNumber(int index) 
{
    if (index >=6)
        error("%s: in retrieveVariableNumber : index %d not managed yet!", EXTASM_C, index);    
    char *tmp;        
    char *variableNumberStr = calloc(20, sizeof(char));
    char *indexstr = calloc(20, sizeof(char));
    strncat(variableNumberStr, "%", 2);
    int length = snprintf(indexstr, sizeof(index), "%d", index);
    if (length < 0)
        error("%s %d %d: in retrieveVariableNumber : error during snprintf function!", EXTASM_C, index, length);
    strncat(variableNumberStr, indexstr, strlen(indexstr));
    tmp = variableNumberStr;
    return tmp;
}
