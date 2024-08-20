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
    char *reg64;        //store the register 64 bits
    int index;         // store the index
    char letter;       // store the letter corresponding to input
    int offset;         // store the offset
    int size;          // store the size to determine the operation to do ex movl movb movw movq
    bool isVariable;   // store true if it's a variable otherwise false for immediate value
    bool isAddress;    // store true if it's an address pointer
    bool isArray;       //true if it's an array variable
    bool isStruct;       //true if it's a struct variable
    bool isToNegate;    //true if the value should be negate
    int indexArray;     //store the index element of array
    int offsetArray;     //store the index of array
    int offsetStruct;   //store the offset of the struct
    bool isq;   //true if  q: 8-bit registers (al, bl, cl, dl)
    bool isl;  //true if l: 32-bit registers (eax, ebx, ecx, edx)
} AsmInput;

typedef struct
{
    Token *output;    // store the token corresponding to input
    char *variableNumber;     //store the variable %0, %1...
    char *prefix;     //= or +
    char *reg;        // store the register that corresponds to the variable size
    char *reg64;        //store the register 64 bits
    char letter;      // to store a b r
    int index;        // order in output
    int size;         // store the size to determine the operation to do
    bool isRegister;  // r
    bool isMemory;    // m
    bool isAlpha;     // if is not r neither m is considered Alpha
    int offset;        // store the offset
    bool isVariable;  // store true if it's a variable otherwise false for immediate value
    bool isAddress;   // store true if it's an address pointer
    bool isArray;       //true if it's an array variable
    bool isStruct;       //true if it's a struct variable
    int indexArray;     //store the index element of array
    int offsetArray;     //store the index of array
    int offsetStruct;   //store the offset of the struct
    bool inputToGenerate;   //true if it's the corresponding input should be generated
    bool isq;   //true if  q: 8-bit registers (al, bl, cl, dl)
    bool isl;  //true if l: 32-bit registers (eax, ebx, ecx, edx)
} AsmOutput;

typedef struct
{
    char *templatestr;
    //bool hasPercent;
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
extern Context *ctx;
static bool hasInput = false;
static bool hasOutput = false;
static bool isToNegate = false;



char *extended_asm(Node *node, Token **rest, Token *tok, Obj *locals)
{
    char *input_asm_str;
    char *output_loading;
    asmtype = 0;
    nbInput = 0;
    nbOutput = 0;
    nbClobber = 0;
    nbLabel = 0;
    hasInput = false;
    hasOutput = false;
    char *template = tok->str;
    char *asm_str = calloc(1, sizeof(char) * 10000);
    ctx->filename = EXTASM_C;
    ctx->funcname = "extended_asm";
    //case __asm__ volatile ("" ::: "memory")
    //case __asm__ __volatile__ ("rep; nop" ::: "memory");  
    //we generate a nop operation for each memory border defined
    //if (strlen(template) == 0 || !strncmp(template, "rep; nop", 9)) {
    if (strlen(template) == 0) {        
        while (!equal(tok->next, ")")) {
            tok = tok->next;
        }
        *rest = tok->next;
        ctx->line_no = __LINE__ + 1;
        *rest = skip(tok->next, ")", ctx);
        tok = *rest;
        asm_str = "\nnop;\n";
        return asm_str;
    }

    // allocate memory for all structs needed
    asmExt = calloc(1, sizeof(AsmExtended));
    asmExt->template = calloc(1, sizeof(AsmTemplate));
    for (int i = 0; i < 10; i++)
        asmExt->input[i] = calloc(1, sizeof(AsmInput));
    for (int i = 0; i < 10; i++)
        asmExt->output[i] = calloc(1, sizeof(AsmOutput));
    for (int i = 0; i < 10; i++)
        asmExt->clobber[i] = calloc(1, sizeof(AsmClobber));


    //strncpy(asm_str, "", strlen(asm_str) + 1);
    char *output_asm_str = calloc(1, sizeof(char) * 2500);
    char *input_final = calloc(1, sizeof(char) * 2500);
    char *input_for_output = calloc(1, sizeof(char) * 4000);
    asmExt->template->templatestr = template;
    // asmExt->template->hasPercent = check_template(template);

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
            if (equal(tok, ":"))
                break;
            output_asm(node, rest, tok, locals);
            // generate output instruction for each output variable
            if (asmExt->output[nbOutput]->variableNumber) {

                hasOutput = true;
                output_loading = generate_output_asm(asmExt->output[nbOutput]->variableNumber);
                // replace %9 by the correct register
                if (!output_loading)
                error("%s : %s:%d: error: in extended_asm function extended_asm :output_loading is null!", EXTASM_C, __FILE__, __LINE__);
                if (!asmExt->output[nbOutput]->reg)
                error("%s : %s:%d: error: in extended_asm function extended_asm :asmExt->output[nbOutput]->reg is null!", EXTASM_C, __FILE__, __LINE__);
                output_loading = subst_asm(output_loading, asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->variableNumber);
                //generate the ouput instruction
                strncat(output_asm_str, output_loading, strlen(output_loading));
            } else { //to manage the case of no output
                tok = tok->next;
                *rest = tok;
            }
            nbOutput++;
            tok = *rest;
            break;
        case AT_INPUT: // inputs
            // return %0, %1 or %x
            if (equal(tok, ":"))
                break;
            input_asm(node, rest, tok, locals);
            // generate input instruction to load the parameter into register
            if (asmExt->input[nbInput]->variableNumber) {
                hasInput = true;
                input_asm_str = generate_input_asm(asmExt->input[nbInput]->variableNumber);
                //replace %9, by the correct
                if (!input_asm_str)
                    error("%s %s:%d: error: in extended_asm function extended_asm :input_asm_str is null!", EXTASM_C, __FILE__, __LINE__);
                if (!asmExt->input[nbInput]->reg)
                    error("%s %s:%d: error: in extended_asm function extended_asm :asmExt->input[nbInput]->reg is null!", EXTASM_C, __FILE__, __LINE__);
                input_asm_str = subst_asm(input_asm_str, asmExt->input[nbInput]->reg, asmExt->input[nbInput]->variableNumber);
                // concatenate the input final strings to add to the assembly
                strncat(input_final, input_asm_str, strlen(input_asm_str));
            }  else { //to manage the case of no input
                tok = tok->next;
                *rest = tok;
            }
            nbInput++;
            tok = *rest;
            break;
        case AT_CLOBBER: // clobbers
            if (equal(tok, ":"))
                break;
            asmExt->clobber[nbClobber]->clobber = tok->loc;
            tok = tok->next;
            // if (equal(tok, ","))
            //     tok = tok->next;
            *rest = tok;
            nbClobber++;
            //error_tok(tok, "%s : in extended_asm function : clobber not managed yet!", EXTASM_C);
            break;
        case AT_LABEL: // labels
            //nbLabel++;
            tok = tok->next;
            *rest = tok;
            //error_tok(tok, "%s : in extended_asm function : label not managed yet!", EXTASM_C);
            break;
        default: // error
            error_tok(tok, "%s : in extended_asm function : too much parameters or complex extended assembly not managed!", EXTASM_C);
        }
        if (equal(tok, ":"))
            asmtype += 1;
        tok = tok->next;
    }

    if (hasOutput) {
        //replace each %9 by the correct output register

        for (int i = 0; i < nbOutput; i++)
        {
            if (asmExt->output[i]->isAddress) {
                char *tmp = calloc(1, sizeof(char) * 30);
                strncat(tmp, "(", 2);
                strncat(tmp, asmExt->output[i]->reg64, strlen(asmExt->output[i]->reg64) );
                strncat(tmp, ")", 2);
                asm_str = subst_asm(template, tmp, asmExt->output[i]->variableNumber);
                free(tmp);
            }else {
                    char *pchb = strstr(template,"b ");
                    if (pchb)
                        asm_str = subst_asm(template, update_register_size(asmExt->output[i]->reg, 1), asmExt->output[i]->variableNumber);
                    if (!pchb)
                        asm_str = subst_asm(template, asmExt->output[i]->reg, asmExt->output[i]->variableNumber);
                }
            }
    }


    if (hasInput) {
        //replace each %9 by the correct input register
        for (int i = 0; i < nbInput; i++)
        {
            if (asmExt->input[i]->isAddress) {
                char *tmp = calloc(1, sizeof(char) * 30);
                strncat(tmp, "(", 2);
                strncat(tmp, asmExt->input[i]->reg64, strlen(asmExt->input[i]->reg64) );
                strncat(tmp, ")", 2);
                asm_str = subst_asm(template, tmp, asmExt->input[i]->variableNumber);
                free(tmp);
            }else 
                asm_str = subst_asm(template, asmExt->input[i]->reg, asmExt->input[i]->variableNumber); 

        }

        //generate the input instructions before the output 
        if (input_final != NULL)
        {  

            input_for_output = generate_input_for_output();
            //input_for_output can be NULL if no input to generate for output
            //generate first the input for output and then the input for the rest of the template
            if (input_for_output != NULL && input_final != NULL) {
                strncat(input_for_output, input_final, strlen(input_final));
                strncpy(input_final, input_for_output, strlen(input_for_output) + 1);
                strncat(input_final, asm_str, strlen(asm_str));     
            } else {
                strncat(input_final, asm_str, strlen(asm_str));        
            }
            asm_str = input_final;            
        }
    }


    //generate the output instructions
    if (hasOutput && output_asm_str != NULL)
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
    if (isDebug)
        printf("=====template=%s\n====asm_str=%s\n====input_final==%s\n====output_asm_str===%s\n", template, asm_str, input_final, output_asm_str);
    *rest = tok;
    // free memory
    for (int i = 0; i < 10; i++)
        free(asmExt->input[i]);
    for (int i = 0; i < 10; i++)
        free(asmExt->output[i]);
    for (int i = 0; i < 10; i++)
        free(asmExt->clobber[i]);
    free(asmExt->template);
    // free(input_for_output);
    // free(output_asm_str);
    // free(input_final);
    free(asmExt);
    return asm_str;
}


void output_asm(Node *node, Token **rest, Token *tok, Obj *locals)
{
    VarScope *sc;
    ctx->funcname = "output_asm";
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
                else {
                    asmExt->output[nbOutput]->prefix = "+";
                }
                asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                if (!asmExt->output[nbOutput]->reg)
                    error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;
                asmExt->output[nbOutput]->letter = 'r';                
            }
            else if (!strncmp(tok->str, "=m", tok->len) || !strncmp(tok->str, "+m", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                if (!strncmp(tok->str, "=m", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else {
                    asmExt->output[nbOutput]->prefix = "+";
                }
                asmExt->output[nbOutput]->reg = specific_register_available("%rdi");
                if (!asmExt->output[nbOutput]->reg)
                    error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;                
                asmExt->output[nbOutput]->letter = 'm';
                asmExt->output[nbOutput]->inputToGenerate = true;
                
            }
            else if (!strncmp(tok->str, "=q", tok->len) || !strncmp(tok->str, "+q", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                asmExt->output[nbOutput]->isq = true;
                if (!strncmp(tok->str, "=q", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else {
                    asmExt->output[nbOutput]->prefix = "+";
                }
                asmExt->output[nbOutput]->reg = specific_register_available("%rdx");
                if (!asmExt->output[nbOutput]->reg)
                    error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;                
                asmExt->output[nbOutput]->letter = 'q';
                asmExt->output[nbOutput]->inputToGenerate = true;
                
            }
            else if (!strncmp(tok->str, "=l", tok->len) || !strncmp(tok->str, "+l", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                asmExt->output[nbOutput]->isl = true;
                if (!strncmp(tok->str, "=l", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else {
                    asmExt->output[nbOutput]->prefix = "+";
                }
                asmExt->output[nbOutput]->reg = specific_register_available("%rdx");
                if (!asmExt->output[nbOutput]->reg)
                    error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;                
                asmExt->output[nbOutput]->letter = 'l';
                asmExt->output[nbOutput]->inputToGenerate = true;
                
            }

            // assuming that it's =a =b ???
            else if (!strncmp(tok->str, "=a", tok->len) || !strncmp(tok->str, "=b", tok->len) || !strncmp(tok->str, "=c", tok->len) || !strncmp(tok->str, "=d", tok->len))
            {
                if (!strncmp(tok->str, "=a", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "=";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                    if (!asmExt->output[nbOutput]->reg)
                       error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;  
                    asmExt->output[nbOutput]->letter = 'a';

                }
                else if (!strncmp(tok->str, "=b", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "=";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rbx");
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg; 
                    asmExt->output[nbOutput]->letter = 'b';
                }
                else if (!strncmp(tok->str, "=c", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "=";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rcx");
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg; 
                    asmExt->output[nbOutput]->letter = 'c';
                }
                else if (!strncmp(tok->str, "=d", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "=";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rdx");
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg; 
                    asmExt->output[nbOutput]->letter = 'd';
                }                            
                else {
                tok = tok->next;
                ctx->line_no = __LINE__ + 1;
                *rest = skip(tok, ")", ctx);
                return;
                }
                    

                asmExt->output[nbOutput]->isAlpha = true;
                //asmExt->output[nbOutput]->prefix = "=";
                //asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                
                
            }
            else if (!strncmp(tok->str, "+a", tok->len) || !strncmp(tok->str, "+b", tok->len) || !strncmp(tok->str, "+c", tok->len) || !strncmp(tok->str, "+d", tok->len))
            {
                if (!strncmp(tok->str, "+a", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "+";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                    if (!asmExt->output[nbOutput]->reg)
                       error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;  
                    asmExt->output[nbOutput]->letter = 'a';

                }
                else if (!strncmp(tok->str, "+b", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "+";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rbx");
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg; 
                    asmExt->output[nbOutput]->letter = 'b';
                }
                else if (!strncmp(tok->str, "+c", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "+";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rcx");
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg; 
                    asmExt->output[nbOutput]->letter = 'c';
                }
                else if (!strncmp(tok->str, "+d", tok->len))
                {
                    asmExt->output[nbOutput]->prefix = "+";
                    asmExt->output[nbOutput]->reg = specific_register_available("%rdx");
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg; 
                    asmExt->output[nbOutput]->letter = 'd';
                }                            
                else {
                tok = tok->next;
                ctx->line_no = __LINE__ + 1;
                *rest = skip(tok, ")", ctx);
                return;
                }
                    

                asmExt->output[nbOutput]->isAlpha = true;
                //asmExt->output[nbOutput]->prefix = "=";
                //asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                
                
            }            
            //D for destination operand
            else if (!strncmp(tok->str, "=D", tok->len) || !strncmp(tok->str, "+D", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                if (!strncmp(tok->str, "=D", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else {
                    asmExt->output[nbOutput]->prefix = "+";
                }
                asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                if (!asmExt->output[nbOutput]->reg)
                    error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;                
                asmExt->output[nbOutput]->letter = 'D';
                asmExt->output[nbOutput]->inputToGenerate = true;
            }   
            //S for source operand
            else if (!strncmp(tok->str, "=S", tok->len) || !strncmp(tok->str, "+S", tok->len))
            {
                asmExt->output[nbOutput]->isMemory = true;
                if (!strncmp(tok->str, "=S", tok->len))
                    asmExt->output[nbOutput]->prefix = "=";
                else {
                    asmExt->output[nbOutput]->prefix = "+";
                }
                asmExt->output[nbOutput]->reg = specific_register_available("%rax");
                if (!asmExt->output[nbOutput]->reg)
                    error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->output[nbOutput]->reg64 = asmExt->output[nbOutput]->reg;                
                asmExt->output[nbOutput]->letter = 'S';
                asmExt->output[nbOutput]->inputToGenerate = true;
            } 

            asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
            asmExt->output[nbOutput]->index = nbOutput;

        }
        // skip the comma
        else if (equal(tok, ",")) {
            ctx->line_no = __LINE__ + 1;
            tok = skip(tok, ",", ctx);
        }
        // manage the variable inside parenthesis
        else if (equal(tok, "("))
        {
            ctx->line_no = __LINE__ + 1;
            tok = skip(tok, "(", ctx);
            // check if the variable is defined
            if (tok->kind == TK_IDENT)
            {
                //TODO potential issue if several variables with same name inside different functions.
                //need to check if the variable is in the correct function
                asmExt->output[nbOutput]->output = tok;
                sc = find_var(tok);
                if (!sc)
                    error_tok(tok, "%s %d: in output_asm function : variable undefined", EXTASM_C, __LINE__);
                if (!sc->var->ty)
                    error_tok(tok, "%s %d: in output_asm function : variable type unknown", EXTASM_C, __LINE__);
                // retrieve the size of the variable to determine the register to use here we use RAX variation
                asmExt->output[nbOutput]->size = sc->var->ty->size;
                if (!asmExt->output[nbOutput]->reg)
                    error_tok(tok, "%s %d: in output_asm function : reg is null extended assembly not managed yet", EXTASM_C, __LINE__);
              
                asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                asmExt->output[nbOutput]->isVariable = true;
                asmExt->output[nbOutput]->output = tok;
                asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);

                if (sc->var->funcname) {
                    update_offset(sc->var->funcname, locals);
                    asmExt->output[nbOutput]->offset = sc->var->offset;
                }
                else {
                    asmExt->output[nbOutput]->offset = 0;
                }

                //managing specific case of arrays
                if (sc->var->ty->kind == TY_ARRAY) {
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok->next, "[", ctx);
                    asmExt->output[nbOutput]->isArray = true;
                    asmExt->output[nbOutput]->isAddress = false;
                    asmExt->output[nbOutput]->indexArray = tok->val;
                    asmExt->output[nbOutput]->size = sc->var->ty->base->size;
                    if (!asmExt->output[nbOutput]->reg)
                        error("%s : %s:%d: error: in output_asm function :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                    //calculate the offset for each element from the bottom to the top r[0] has the lowest offset example -48, r[1] - 44, r[2] -40, r[3] - 36
                    asmExt->output[nbOutput]->offset = (sc->var->offset ) + (asmExt->output[nbOutput]->indexArray * asmExt->output[nbOutput]->size);
                    asmExt->output[nbOutput]->offsetArray = sc->var->offset; 
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok, "]", ctx);
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;
                }                
                //special case of array pointer it means that the parameter received is an address.
                if (sc->var->ty->kind == TY_PTR && equal(tok->next, "[")) {
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok->next, "[", ctx);
                    asmExt->output[nbOutput]->isArray = true;
                    asmExt->output[nbOutput]->isAddress = true;
                    asmExt->output[nbOutput]->indexArray = tok->val;
                    asmExt->output[nbOutput]->size = sc->var->ty->base->size;
                    if (!asmExt->output[nbOutput]->reg)
                        error_tok(tok, "%s %d: in output_asm function : reg is null extended assembly not managed yet", EXTASM_C, __LINE__);
                    asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                    //calculate the offset for each element from the bottom to the top r[0] has the lowest offset example -48, r[1] - 44, r[2] -40, r[3] - 36
                    asmExt->output[nbOutput]->offset = (asmExt->output[nbOutput]->indexArray * asmExt->output[nbOutput]->size);
                    asmExt->output[nbOutput]->offsetArray = sc->var->offset; 
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok, "]", ctx);
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;
                }

                //Trying to fix ISS-164 special case of ptr->value form (ptr to a struct)
                if (sc->var->ty->kind == TY_PTR && equal(tok->next, "->")) {
                    if (!sc->var->ty->base)
                        error_tok(tok, "%s %d: in output_asm function : expecting struct base but base is null!", EXTASM_C, __LINE__);
                    ctx->line_no = __LINE__ + 1;
                    asmExt->output[nbOutput]->output = tok;
                    tok = skip(tok->next, "->", ctx);
                    Token * tokmbr = tok;
                    // retrieve the size of the variable to determine the register to use here we use RAX variation
                    asmExt->output[nbOutput]->isAddress = true;  
                    asmExt->output[nbOutput]->isStruct = true;     
                    asmExt->output[nbOutput]->size = sc->var->ty->size;
                    if (!asmExt->output[nbOutput]->reg)
                        error_tok(tok, "%s %d: in output_asm function : reg is null extended assembly not managed yet", EXTASM_C, __LINE__);                
                    asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                    asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                    if (!sc->var->ty->base->members)
                        error_tok(tok, "%s %d: in output_asm function : expecting members but members is null", EXTASM_C, __LINE__);
                    if (sc->var->funcname) {
                        update_offset(sc->var->funcname, locals);
                        asmExt->output[nbOutput]->offset = sc->var->offset;
                        asmExt->output[nbOutput]->offsetStruct = sc->var->ty->base->members->offset ;
                    }
                    else {
                        asmExt->output[nbOutput]->offset = 0;
                    }
                    //need to update the specific struct field offset
                    char *toktmp = calloc(1, sizeof(char) * 300);
                    for (Member *mbr = sc->var->ty->base->members; mbr; mbr = mbr->next) {
                        if (mbr->name->len > 59)
                            error_tok(tok, "%s %d %d: in output_asm function : not enough size for toktmp", EXTASM_C, __LINE__, mbr->name->len);
                        strncat(toktmp, mbr->name->loc, mbr->name->len);
                        if (equal(tokmbr, toktmp)) {
                            asmExt->output[nbOutput]->offsetStruct = mbr->offset ;
                            asmExt->output[nbOutput]->size = mbr->ty->size ;
                            if (!asmExt->output[nbOutput]->reg)
                                error_tok(tok, "%s %d: in output_asm function : reg is null extended assembly not managed yet", EXTASM_C, __LINE__);
                            asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                        }
                    }
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;
                }

                // skip the variable to go to next token that should be a ")"
                // tok = tok->next;
                tok = tok->next;
                ctx->line_no = __LINE__ + 1;
                if (!equal(tok, ")"))
                    error_tok(tok, "%s %d: in output_asm function : extended assembly not managed yet", EXTASM_C, __LINE__);
                *rest = skip(tok, ")", ctx);
                return;
            }
            // pointer
            else if (equal(tok, "*"))
            {
                consume(&tok, tok, "*");
                if (tok->kind == TK_IDENT)
                {
                    asmExt->output[nbOutput]->isAddress = true;
                    asmExt->output[nbOutput]->output = tok;                    
                    sc = find_var(tok);
                    if (!sc)
                        error_tok(tok, "%s %d: in output_asm function : variable undefined2", EXTASM_C, __LINE__);
                    if (!sc->var->ty)
                        error_tok(tok, "%s %d: in output_asm function : variable type unknown2", EXTASM_C, __LINE__);
                    // retrieve the size of the variable to determine the register to use here we use RAX variation
                    // skip the variable to go to next token that should be a ")"
                
                    asmExt->output[nbOutput]->size = sc->var->ty->pointertype->size;
                    if (sc->var->funcname) {
                        update_offset(sc->var->funcname, locals);
                        asmExt->output[nbOutput]->offset = sc->var->offset;                       

                    } else {
                            asmExt->output[nbOutput]->offset = 0;                        

                    }
                    if (!asmExt->output[nbOutput]->reg)
                        error_tok(tok, "%s %d: in output_asm function : reg is null extended assembly not managed yet", EXTASM_C, __LINE__);
                    asmExt->output[nbOutput]->reg = update_register_size(asmExt->output[nbOutput]->reg, asmExt->output[nbOutput]->size);
                    asmExt->output[nbOutput]->variableNumber = retrieveVariableNumber(nbOutput);
                    tok = tok->next;

                    ctx->funcname = "output_asm";
                    ctx->line_no = __LINE__ + 1 ;
                    *rest = skip(tok, ")", ctx);
                    return;
                }
            }
        }


        tok = tok->next;
        *rest = tok;
    }
    return;
}

void input_asm(Node *node, Token **rest, Token *tok, Obj *locals)
{
    ctx->funcname = "input_asm";
    VarScope *sc;
    char *input_value = calloc(1, sizeof(char) * 300);
    asmExt->input[nbInput]->offset = 0;

    while (!equal(tok->next, ":") && !equal(tok->next, ";"))
    {
        // register in write only mode
        if (tok->kind == TK_STR && !strncmp(tok->str, "0", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(0);
            asmExt->input[nbInput]->index = 0;
            asmExt->input[nbInput]->reg = asmExt->output[0]->reg;
            if (!asmExt->input[nbInput]->reg)
                error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->output[0]->reg64;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "1", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(1);
            asmExt->input[nbInput]->index = 1;
            asmExt->input[nbInput]->reg = asmExt->output[1]->reg;
            if (!asmExt->input[nbInput]->reg)
                error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->output[1]->reg64;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "2", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(2);
            asmExt->input[nbInput]->index = 2;
            asmExt->input[nbInput]->reg = asmExt->output[2]->reg;
            if (!asmExt->input[nbInput]->reg)
                error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->output[2]->reg64;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "3", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(3);
            asmExt->input[nbInput]->index = 3;
            asmExt->input[nbInput]->reg = asmExt->output[3]->reg;
            if (!asmExt->input[nbInput]->reg)
                error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            

            asmExt->input[nbInput]->reg64 = asmExt->output[3]->reg64;
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "a", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('a'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'a';
            //=====ISS-156 case we have no output for the letter
            if (retrieve_output_index_from_letter('a') == -1) {
                asmExt->input[nbInput]->reg =  specific_register_available("%rax");
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);  
                asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            }
            else {
                asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('a')]->reg;
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->input[nbInput]->reg64 = asmExt->output[retrieve_output_index_from_letter('a')]->reg64;
            }
            
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "b", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('b'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'b';
            //=====ISS-156 case we have no output for the letter
            if (retrieve_output_index_from_letter('b') == -1) {
                asmExt->input[nbInput]->reg =  specific_register_available("%rbx");
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            }
            else {            
                asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('b')]->reg;
                if (!asmExt->input[nbInput]->reg)
                     error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->input[nbInput]->reg64 = asmExt->output[retrieve_output_index_from_letter('b')]->reg64;
            }
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "c", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('c'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'c';
            //=====ISS-156 case we have no output for the letter
            if (retrieve_output_index_from_letter('c') == -1) {
                asmExt->input[nbInput]->reg =  specific_register_available("%rcx");
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            }
            else {
                asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('c')]->reg;
                if (!asmExt->input[nbInput]->reg)
                     error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->input[nbInput]->reg64 = asmExt->output[retrieve_output_index_from_letter('c')]->reg64;
            }

        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "d", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(retrieve_output_index_from_letter('d'));
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->letter = 'd';
            //=====ISS-156 case we have no output for the letter
            if (retrieve_output_index_from_letter('d') == -1) {
                asmExt->input[nbInput]->reg =  specific_register_available("%rdx");
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__); 
                asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            }
            else {            
                asmExt->input[nbInput]->reg = asmExt->output[retrieve_output_index_from_letter('d')]->reg;
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__); 
                asmExt->input[nbInput]->reg64 = asmExt->output[retrieve_output_index_from_letter('d')]->reg64;
            }
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "m", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%rdi");
            if (!asmExt->input[nbInput]->reg)
                 error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            asmExt->input[nbInput]->letter = 'm';
        }
        else if (tok->kind == TK_STR && !strncmp(tok->str, "q", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%r10");
            asmExt->input[nbInput]->isq = true;
            if (!asmExt->input[nbInput]->reg)
                 error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            asmExt->input[nbInput]->letter = 'q';
        }        
        else if (tok->kind == TK_STR && !strncmp(tok->str, "l", tok->len))
        {

            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%r10");
            asmExt->input[nbInput]->isl = true;
            if (!asmExt->input[nbInput]->reg)
                 error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            asmExt->input[nbInput]->letter = 'l';
        }        


        else if (tok->kind == TK_STR && !strncmp(tok->str, "r", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%r8");
            if (!asmExt->input[nbInput]->reg)
                error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            asmExt->input[nbInput]->letter = 'r';
            
        }
        //D for destination operand
        else if (tok->kind == TK_STR && !strncmp(tok->str, "D", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%rdx");
            if (!asmExt->input[nbInput]->reg)
                 error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            asmExt->input[nbInput]->letter = 'D';
            
        }
        //S for source operand
        else if (tok->kind == TK_STR && !strncmp(tok->str, "S", tok->len))
        {
            asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbOutput + nbInput);
            asmExt->input[nbInput]->index = nbOutput + nbInput;
            asmExt->input[nbInput]->reg = specific_register_available("%r11");
            if (!asmExt->input[nbInput]->reg)
                 error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);            
            asmExt->input[nbInput]->reg64 = asmExt->input[nbInput]->reg;
            asmExt->input[nbInput]->letter = 'S';

        }

        else if (equal(tok, "("))
        {
            ctx->line_no = __LINE__ + 1;
            tok = skip(tok, "(", ctx);
            // check if the variable is defined
            if (equal(tok, "-")) 
            {
                isToNegate = true;
                consume(&tok, tok, "-");
            }            
            if (tok->kind == TK_IDENT)
            {           
                if (isToNegate) {
                    asmExt->input[nbInput]->isToNegate = isToNegate;
                    isToNegate = false;
                }
                    
                sc = find_var(tok);
                if (!sc)
                    error_tok(tok, "%s %d: in input_asm function : variable undefined", EXTASM_C, __LINE__);
                if (!sc->var->ty)
                    error_tok(tok, "%s %d: in input_asm function : variable type unknown", EXTASM_C, __LINE__);
                asmExt->input[nbInput]->input = tok;
                asmExt->input[nbInput]->isVariable = true;
                asmExt->input[nbInput]->size = sc->var->ty->size;
                if (sc->var->funcname) {
                    update_offset(sc->var->funcname, locals);
                    asmExt->input[nbInput]->offset = sc->var->offset;
                } 
                if (!asmExt->input[nbInput]->reg)
                    error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                //managing specific case of arrays
                if (sc->var->ty->kind == TY_ARRAY) {
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok->next, "[", ctx);
                    asmExt->input[nbInput]->isArray = true;
                    asmExt->input[nbInput]->indexArray = tok->val;
                    asmExt->input[nbInput]->isAddress = false;
                    asmExt->input[nbInput]->size = sc->var->ty->base->size;
                    if (!asmExt->input[nbInput]->reg)
                        error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                    //calculate the offset for each element from the bottom to the top r[0] has the lowest offset example -48, r[1] - 44, r[2] -40, r[3] - 36
                    asmExt->input[nbInput]->offset = (sc->var->offset ) + (asmExt->input[nbInput]->indexArray * asmExt->input[nbInput]->size);
                    asmExt->input[nbInput]->offsetArray = sc->var->offset; 
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok, "]", ctx);
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;
                }        
                if (sc->var->ty->kind == TY_PTR && equal(tok->next, "[")) {
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok->next, "[", ctx);
                    asmExt->input[nbInput]->isArray = true;
                    asmExt->input[nbInput]->isAddress = true;
                    asmExt->input[nbInput]->indexArray = tok->val;
                    asmExt->input[nbInput]->size = sc->var->ty->base->size;
                    if (!asmExt->input[nbInput]->reg)
                        error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);                    
                    asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                    //calculate the offset for each element from the bottom to the top r[0] has the lowest offset example -48, r[1] - 44, r[2] -40, r[3] - 36
                    asmExt->input[nbInput]->offset = (asmExt->input[nbInput]->indexArray * asmExt->input[nbInput]->size);
                    asmExt->input[nbInput]->offsetArray = sc->var->offset; 
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    tok = skip(tok, "]", ctx);
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;                    
                }
               //Trying to fix ISS-164 special case of ptr->value form (ptr to a struct)
                if (sc->var->ty->kind == TY_PTR && equal(tok->next, "->")) {
                    if (!sc->var->ty->base)
                        error_tok(tok, "%s %d: in input_asm function : expecting struct base but base is null!", EXTASM_C, __LINE__);
                    ctx->line_no = __LINE__ + 1;
                    asmExt->input[nbInput]->input = tok;
                    tok = skip(tok->next, "->", ctx);
                    Token * tokmbr = tok;
                    // retrieve the size of the variable to determine the register to use here we use RAX variation
                    asmExt->input[nbInput]->isAddress = true;  
                    asmExt->input[nbInput]->isStruct = true;     
                    asmExt->input[nbInput]->size = sc->var->ty->size;
                    if (!asmExt->input[nbInput]->reg)
                        error_tok(tok, "%s %d: in input_asm function : reg is null extended assembly not managed yet", EXTASM_C, __LINE__);                
                    asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                    //asmExt->input[nbInput]->variableNumber = retrieveVariableNumber(nbInput);
                    if (!sc->var->ty->base->members)
                        error_tok(tok, "%s %d: in input_asm function : expecting members but members is null", EXTASM_C, __LINE__);
                    if (sc->var->funcname) {
                        update_offset(sc->var->funcname, locals);
                        asmExt->input[nbInput]->offset = sc->var->offset;
                    }
                    else {
                        asmExt->input[nbInput]->offset = 0;
                    }
                    //need to update the specific struct field offset
                    char *toktmp = calloc(1, sizeof(char) * 300);                    
                    for (Member *mbr = sc->var->ty->base->members; mbr; mbr = mbr->next) {
                        if (mbr->name->len > 59)
                            error_tok(tok, "%s %d %d: in input_asm function : not enough size for toktmp", EXTASM_C, __LINE__, mbr->name->len);
                        strncat(toktmp, mbr->name->loc, mbr->name->len);                            
                        if (equal(tokmbr, toktmp)) {
                            asmExt->input[nbInput]->offsetStruct = mbr->offset ;
                            asmExt->input[nbInput]->size = mbr->ty->size ;
                            if (!asmExt->input[nbInput]->reg)
                                error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                            asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                        }
                    }
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;
                }


                tok = tok->next;
                ctx->line_no = __LINE__ + 1;
                *rest = skip(tok, ")", ctx);
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
                asmExt->input[nbInput]->isAddress = false;
                asmExt->input[nbInput]->input_value = input_value;
                asmExt->input[nbInput]->size = tok->ty->size;
                tok = tok->next;
                ctx->line_no = __LINE__ + 1;
                *rest = skip(tok, ")", ctx);
                return;
            } // pointer
            else if (equal(tok, "*"))
            {
                consume(&tok, tok, "*");
                if (tok->kind == TK_IDENT)
                {
                    asmExt->input[nbInput]->input = tok;                    
                    sc = find_var(tok);
                    if (!sc)
                        error_tok(tok, "%s %d: in input_asm function : variable undefined2", EXTASM_C, __LINE__);
                    asmExt->input[nbInput]->input = tok;
                    asmExt->input[nbInput]->isVariable = true;
                    asmExt->input[nbInput]->isAddress = true;
                    asmExt->input[nbInput]->size = sc->var->ty->size;
                    if (sc->var->funcname) {
                        update_offset(sc->var->funcname, locals);

                        asmExt->input[nbInput]->offset = sc->var->offset;
                    } 
                    if (!asmExt->input[nbInput]->reg)
                        error("%s : %s:%d: error: in input_asm function input_asm :reg is null!", EXTASM_C, __FILE__, __LINE__);
                    asmExt->input[nbInput]->reg = update_register_size(asmExt->input[nbInput]->reg, asmExt->input[nbInput]->size);
                    tok = tok->next;
                    ctx->line_no = __LINE__ + 1;
                    *rest = skip(tok, ")", ctx);
                    return;
                }
            }
        }
        else if (equal(tok, ",")) {
            ctx->line_no = __LINE__ + 1;
            tok = skip(tok, ",", ctx);
        }
        // else
        //     error_tok(tok, "%s : in input_asm function : input complex constraint not managed yet!", EXTASM_C);

        tok = tok->next;
        *rest = tok;
    }
    return;
}


// do the susbtitution into the template
char *subst_asm(char *template, char *output_str, char *input_str)
{
    return string_replace(template, input_str, output_str);
}

// do the susbtitution into the template
char *subst_asm_prefix(char *template, char *output_str, char *input_str)
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

    strncpy(str, bstr, strlen(bstr) + 1);
    if (strlen(str)> 10000)
        error("%s: %s:%d: error: in string_replace : not enough memory!", EXTASM_C, __FILE__, __LINE__);
    return str;
}




// generate input assembly instruction
char *generate_input_asm(char *input_str)
{
    char *tmp = calloc(1, sizeof(char) * 100);
    //case variable
    if (asmExt->input[nbInput]->isVariable && asmExt->input[nbInput]->isToNegate)
    {
        strncat(tmp, "\n", 3);
        strncat(tmp, opcode(asmExt->input[nbInput]->size), strlen(opcode(asmExt->input[nbInput]->size)));
        strncat(tmp, load_variable(asmExt->input[nbInput]->offset), strlen(load_variable(asmExt->input[nbInput]->offset)));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        strncat(tmp, "neg ", 5);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    else if (asmExt->input[nbInput]->isVariable)
    {
        strncat(tmp, "\n", 3);
        strncat(tmp, opcode(asmExt->input[nbInput]->size), strlen(opcode(asmExt->input[nbInput]->size)));
        strncat(tmp, load_variable(asmExt->input[nbInput]->offset), strlen(load_variable(asmExt->input[nbInput]->offset)));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    //case immediate value
    else
    {
        strncat(tmp, "\n", 3);
        strncat(tmp, opcode(asmExt->input[nbInput]->size), strlen(opcode(asmExt->input[nbInput]->size)));
        strncat(tmp, " $", 3);
        strncat(tmp, asmExt->input[nbInput]->input_value, strlen(asmExt->input[nbInput]->input_value));
        strncat(tmp, ", ", 3);
        strncat(tmp, asmExt->input[nbInput]->variableNumber, strlen(asmExt->input[nbInput]->variableNumber));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    error("%s : %s:%d: error: in extended_asm function generate_input_asm : unexpected error!", EXTASM_C, __FILE__, __LINE__);
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
    //case variable and not an address
    if (asmExt->output[nbOutput]->isVariable && !asmExt->output[nbOutput]->isAddress)
    {
        strncat(tmp, "\n", 3);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        strncat(tmp, ", ", 3);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offset), strlen(load_variable(asmExt->output[nbOutput]->offset)));
        strncat(tmp, ";\n", 3);
        return tmp;
    }
    //case not an address it means that it's an immediate value should probably never exists
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
    //case it's an array with address we need to generate the correct output for the specified index
    if (asmExt->output[nbOutput]->isAddress && asmExt->output[nbOutput]->isArray) {
        strncat(tmp, "\n", 3);
        strncat(tmp, "  movq ", 8);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offsetArray), strlen(load_variable(asmExt->output[nbOutput]->offsetArray)));
        strncat(tmp, ", %rsi\n", 8);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        //if index 0 we move the value into address pointed by rsi, if index 1 the value will be stored at address pointed by rsi + size of one element
        //if index 2 the value will be stored at address pointed by rsi + (index * size of one element)...
        char *tmp2 = calloc(1, sizeof(char) * 100);
        if (asmExt->output[nbOutput]->indexArray == 0)
            strncat(tmp, ", (%rsi)\n", 11);
        else {
            strncat(tmp, ", ", 3);
            snprintf(tmp2, sizeof(asmExt->output[nbOutput]->offset), "%d", asmExt->output[nbOutput]->offset);
            strncat(tmp2, "(%rsi)\n", 9); //to have example 4(%rsi) for index 1, 8(%rsi) for index 2...
            strncat(tmp, tmp2, strlen(tmp2));
        }
        return tmp;
    }

    //Trying to fix ======ISS-164 case it's a struct with address we need to generate the correct output for the specified struct member
    if (asmExt->output[nbOutput]->isAddress && asmExt->output[nbOutput]->isStruct) {
        strncat(tmp, "\n", 3);
        strncat(tmp, "  movq ", 8);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offset), strlen(load_variable(asmExt->output[nbOutput]->offset)));
        strncat(tmp, ", %rsi\n", 8);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        //if index 0 we move the value into address pointed by rsi, if index 1 the value will be stored at address pointed by rsi + size of one element
        //if index 2 the value will be stored at address pointed by rsi + (index * size of one element)...
        char *tmp2 = calloc(1, sizeof(char) * 100);
        if (asmExt->output[nbOutput]->offsetStruct == 0)
            strncat(tmp, ", (%rsi)\n", 11);
        else {
            strncat(tmp, ", ", 3);
            snprintf(tmp2, sizeof(asmExt->output[nbOutput]->offsetStruct), "%d", asmExt->output[nbOutput]->offsetStruct);
            strncat(tmp2, "(%rsi)\n", 9); //to have example 4(%rsi) for index 1, 8(%rsi) for index 2...
            strncat(tmp, tmp2, strlen(tmp2));
        }
        return tmp;
    }

    //case it's an address 
    else
    {
        if (asmExt->output[nbOutput]->letter == 'm'|| asmExt->output[nbOutput]->letter == 'r' || asmExt->output[nbOutput]->letter == 'q') {
        strncat(tmp, "\n", 3);
        strncat(tmp, "  movq ", 8);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offset), strlen(load_variable(asmExt->output[nbOutput]->offset)));
        strncat(tmp, ", %rsi\n", 8);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, " (%rsi), ", 11);
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        strncat(tmp, "\n", 3);
        return tmp;
        } else {
        strncat(tmp, "\n", 3);
        strncat(tmp, "  movq ", 8);
        strncat(tmp, load_variable(asmExt->output[nbOutput]->offset), strlen(load_variable(asmExt->output[nbOutput]->offset)));
        strncat(tmp, ", %rsi\n", 8);
        strncat(tmp, opcode(asmExt->output[nbOutput]->size), strlen(opcode(asmExt->output[nbOutput]->size)));
        strncat(tmp, asmExt->output[nbOutput]->variableNumber, strlen(asmExt->output[nbOutput]->variableNumber));
        strncat(tmp, ", (%rsi)\n", 11);
        return tmp;
        }
    }

    error("%s : %s:%d: error: in extended_asm function generate_output_asm : unexpected error!", EXTASM_C, __FILE__, __LINE__);

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
        error("%s %s %d : error: in load_variable : incorrect offset %d or not managed yet!", EXTASM_C, __FILE__, __LINE__, offset);
    char *targetaddr = calloc(20, sizeof(char));
    
    int length = snprintf(targetaddr, sizeof(offset), "%d", offset);
    if (length < 0)
        error("%s %s %d : error:in load_variable : error during snprintf function! offset=%d length=%d", EXTASM_C, __FILE__, __LINE__, offset, length);
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
    case 16:
        return "\n  mov ";        
    default:
        error("%s: %s:%d: error: in opcode : size %d unexpected!", EXTASM_C, __FILE__, __LINE__, size);
    }
}


// we need to update the offset to be able to use this information later for loading result into output variables.
// TODO we can have an issue here if several functions with same name. Probably need to find in a better way to avoid this issue.
void update_offset(char *funcname, Obj *locals)
{
    //printf(" function %s \n", funcname);
    Obj *fn = find_func(funcname);
    if (fn) {
        //fixing ====ISS-161 issue with some locals missing in fn->locals
        //if (!fn->locals)
        fn->locals = locals;
        assign_lvar_offsets(fn);
    }

    
}



// update register following the size
char *update_register_size(char *reg, int size)
{
    if (!strncmp(reg, "%rax", strlen(reg)) || !strncmp(reg, "%eax", strlen(reg)) || !strncmp(reg, "%ax", strlen(reg)) || !strncmp(reg, "%ah", strlen(reg)) || !strncmp(reg, "%al", strlen(reg)))
        return reg_ax(size);
    else if (!strncmp(reg, "%rbx", strlen(reg)) || !strncmp(reg, "%ebx", strlen(reg)) || !strncmp(reg, "%bx", strlen(reg)) || !strncmp(reg, "%bh", strlen(reg)) || !strncmp(reg, "%bl", strlen(reg)))
        return reg_bx(size);
    else if (!strncmp(reg, "%rcx", strlen(reg)) || !strncmp(reg, "%ecx", strlen(reg)) || !strncmp(reg, "%cx", strlen(reg)) || !strncmp(reg, "%ch", strlen(reg)) || !strncmp(reg, "%cl", strlen(reg)))
        return reg_cx(size);
    else if (!strncmp(reg, "%rdx", strlen(reg)) || !strncmp(reg, "%edx", strlen(reg)) || !strncmp(reg, "%dx", strlen(reg)) || !strncmp(reg, "%dh", strlen(reg)) || !strncmp(reg, "%dl", strlen(reg)))
        return reg_dx(size);
    else if (!strncmp(reg, "%rdi", strlen(reg)) || !strncmp(reg, "%edi", strlen(reg)) || !strncmp(reg, "%di", strlen(reg)) || !strncmp(reg, "%dih", strlen(reg)) || !strncmp(reg, "%dil", strlen(reg)))
        return reg_di(size);       
    else if (!strncmp(reg, "%rsi", strlen(reg)) || !strncmp(reg, "%esi", strlen(reg)) || !strncmp(reg, "%si", strlen(reg)) || !strncmp(reg, "%sih", strlen(reg)) || !strncmp(reg, "%sil", strlen(reg)))
        return reg_si(size);       
    else if (!strncmp(reg, "%r8", strlen(reg)) || !strncmp(reg, "%r8d", strlen(reg)) || !strncmp(reg, "%r8w", strlen(reg)) || !strncmp(reg, "%r8h", strlen(reg)) || !strncmp(reg, "%r8b", strlen(reg)))
        return reg_si(size);                    
    else if (!strncmp(reg, "%r9", strlen(reg)) || !strncmp(reg, "%r9d", strlen(reg)) || !strncmp(reg, "%r9w", strlen(reg)) || !strncmp(reg, "%r9h", strlen(reg)) || !strncmp(reg, "%r9b", strlen(reg)))
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
    
    if (index > 8)
        error("%s: %s:%d: error: in retrieveVariableNumber : index %d not managed yet!", EXTASM_C, __FILE__, __LINE__, index);
    char *tmp;        
    char *variableNumberStr = calloc(20, sizeof(char));
    char *indexstr = calloc(20, sizeof(char));
    strncat(variableNumberStr, "%", 2);
    int length = snprintf(indexstr, sizeof(index), "%d", index);
    if (length < 0)
        error("%s %s %d : error: in retrieveVariableNumber : error during snprintf function! index=%d length=%d", EXTASM_C, __FILE__, __LINE__, index, length);
    strncat(variableNumberStr, indexstr, strlen(indexstr));
    tmp = variableNumberStr;
    return tmp;
}


//generate the input for the output when + is a prefix for output
char *generate_input_for_output() {
    char *tmp = calloc(1, sizeof(char) * 500);

    for (int i = 0; i < nbOutput; i++)
    {
        //not sure yet about in which case exactly we need to generate the input for the output
      //not sure yet about in which case exactly we need to generate the input for the output
        if ((asmExt->output[i]->offset != 0 && (!strncmp(asmExt->output[i]->prefix, "+", 2) || asmExt->output[i]->isAddress))) {
            if (asmExt->output[i]->isVariable && !asmExt->output[i]->isAddress)
                {
                    strncat(tmp, "\n", 3);
                    strncat(tmp, opcode(asmExt->output[i]->size), strlen(opcode(asmExt->output[i]->size)));
                    strncat(tmp, load_variable(asmExt->output[i]->offset), strlen(load_variable(asmExt->output[i]->offset)));
                    strncat(tmp, ", ", 3);
                    strncat(tmp, asmExt->output[i]->reg, strlen(asmExt->output[i]->reg));
                    strncat(tmp, ";\n", 3);             

                }else if (asmExt->output[i]->isAddress) {
                    strncat(tmp, "\n", 3);
                    strncat(tmp, opcode(8), 8);
                    strncat(tmp, load_variable(asmExt->output[i]->offset), strlen(load_variable(asmExt->output[i]->offset)));
                    strncat(tmp, ", ", 3);
                    strncat(tmp, asmExt->output[i]->reg64, strlen(asmExt->output[i]->reg64));
                    strncat(tmp, ";\n", 3);    
                }       
     
        }


    }
    return tmp;
}