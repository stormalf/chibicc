#include "chibicc.h"
#define DWARF_C "dwarf.c"


// DWARF constants
#define DW_TAG_subprogram 0x2e
#define DW_TAG_formal_parameter 0x41
#define DW_TAG_variable 0x34
#define DW_TAG_base_type 0x24
#define DW_TAG_pointer_type 0x22
#define DW_TAG_structure_type 0x19
#define DW_TAG_array_type 0x1b
#define DW_TAG_enumeration_type 0x4f
#define DW_TAG_enumerator 0x4e
#define DW_TAG_typedef 0x5f
#define DW_TAG_const_type 0x0a
#define DW_TAG_volatile_type 0x0b

// DWARF attribute constants
#define DW_ATE_void 0x00
#define DW_ATE_address 0x01
#define DW_ATE_integer 0x02
#define DW_ATE_float 0x03
#define DW_ATE_pointer 0x04
#define DW_ATE_reference 0x05
#define DW_ATE_complex 0x06
#define DW_ATE_string 0x07
#define DW_ATE_structure 0x08
#define DW_ATE_union 0x09
#define DW_ATE_type 0x0A
#define DW_ATE_signed 0x0B
#define DW_ATE_unsigned 0x0C
#define DW_ATE_float128 0x0D
#define DW_ATE_decimal 0x0E
#define DW_ATE_float80 0x0F
#define DW_ATE_float64 0x10
#define DW_ATE_float32 0x11
#define DW_ATE_float16 0x12
#define DW_ATE_uint128 0x13
#define DW_ATE_int128 0x14
#define DW_ATE_char 0x15
#define DW_AT_prototyped 0x17
#define DW_AT_name 0x03
#define DW_AT_type 0x49
#define DW_AT_byte_size 0x0b
#define DW_AT_data_member_location 0x49
#define DW_AT_sibling 0x1b
#define DW_AT_decl_file 0x01
#define DW_AT_decl_line 0x02
#define DW_AT_decl_column 0x03
#define DW_AT_external 0x25
#define DW_AT_location 0x27
#define DW_AT_allocated 0x21

// DWARF opcodes
#define DW_OP_addr 0x03
#define DW_OP_const1u 0x08
#define DW_OP_const1s 0x09
#define DW_OP_const2u 0x0a
#define DW_OP_const2s 0x0b
#define DW_OP_const4u 0x0c
#define DW_OP_const4s 0x0d
#define DW_OP_const8u 0x0e
#define DW_OP_const8s 0x0f
#define DW_OP_constu 0x10
#define DW_OP_consts 0x11
#define DW_OP_dup 0x12
#define DW_OP_drop 0x13
#define DW_OP_over 0x14
#define DW_OP_pick 0x15
#define DW_OP_swap 0x16
#define DW_OP_rot 0x17
#define DW_OP_xderef 0x18
#define DW_OP_abs 0x19
#define DW_OP_and 0x1a
#define DW_OP_div 0x1b
#define DW_OP_minus 0x1c
#define DW_OP_mod 0x1d
#define DW_OP_mul 0x1e
#define DW_OP_neg 0x1f
#define DW_OP_not 0x20
#define DW_OP_or 0x21
#define DW_OP_plus 0x22
#define DW_OP_plus_uconst 0x23
#define DW_OP_shl 0x24
#define DW_OP_shr 0x25
#define DW_OP_shra 0x26
#define DW_OP_xor 0x27
#define DW_OP_bra 0x28
#define DW_OP_eq 0x29
#define DW_OP_ge 0x2a
#define DW_OP_gt 0x2b
#define DW_OP_le 0x2c
#define DW_OP_lt 0x2d
#define DW_OP_ne 0x2e
#define DW_OP_skip 0x2f
#define DW_OP_lit0 0x30
#define DW_OP_lit1 0x31
#define DW_OP_lit2 0x32
#define DW_OP_lit3 0x33
#define DW_OP_lit4 0x34
#define DW_OP_lit5 0x35
#define DW_OP_lit6 0x36
#define DW_OP_lit7 0x37
#define DW_OP_lit8 0x38
#define DW_OP_lit9 0x39
#define DW_OP_lit10 0x3a
#define DW_OP_lit11 0x3b
#define DW_OP_lit12 0x3c
#define DW_OP_lit13 0x3d
#define DW_OP_lit14 0x3e
#define DW_OP_lit15 0x3f
#define DW_OP_lit16 0x40
#define DW_OP_lit17 0x41
#define DW_OP_lit18 0x42
#define DW_OP_lit19 0x43
#define DW_OP_lit20 0x44
#define DW_OP_lit21 0x45
#define DW_OP_lit22 0x46
#define DW_OP_lit23 0x47
#define DW_OP_lit24 0x48
#define DW_OP_lit25 0x49
#define DW_OP_lit26 0x4a
#define DW_OP_lit27 0x4b
#define DW_OP_lit28 0x4c
#define DW_OP_lit29 0x4d
#define DW_OP_lit30 0x4e
#define DW_OP_lit31 0x4f
#define DW_OP_reg0 0x50
#define DW_OP_reg1 0x51
#define DW_OP_reg2 0x52
#define DW_OP_reg3 0x53
#define DW_OP_reg4 0x54
#define DW_OP_reg5 0x55
#define DW_OP_reg6 0x56
#define DW_OP_reg7 0x57
#define DW_OP_reg8 0x58
#define DW_OP_reg9 0x59
#define DW_OP_reg10 0x5a
#define DW_OP_reg11 0x5b
#define DW_OP_reg12 0x5c
#define DW_OP_reg13 0x5d
#define DW_OP_reg14 0x5e
#define DW_OP_reg15 0x5f
#define DW_OP_reg16 0x60
#define DW_OP_reg17 0x61
#define DW_OP_reg18 0x62
#define DW_OP_reg19 0x63
#define DW_OP_reg20 0x64
#define DW_OP_reg21 0x65
#define DW_OP_reg22 0x66
#define DW_OP_reg23 0x67
#define DW_OP_reg24 0x68
#define DW_OP_reg25 0x69
#define DW_OP_reg26 0x6a
#define DW_OP_reg27 0x6b
#define DW_OP_reg28 0x6c
#define DW_OP_reg29 0x6d
#define DW_OP_reg30 0x6e
#define DW_OP_reg31 0x6f
#define DW_OP_breg0 0x70
#define DW_OP_breg1 0x71
#define DW_OP_breg2 0x72
#define DW_OP_breg3 0x73
#define DW_OP_breg4 0x74
#define DW_OP_breg5 0x75
#define DW_OP_breg6 0x76
#define DW_OP_breg7 0x77
#define DW_OP_breg8 0x78
#define DW_OP_breg9 0x79
#define DW_OP_breg10 0x7a
#define DW_OP_breg11 0x7b
#define DW_OP_breg12 0x7c
#define DW_OP_breg13 0x7d
#define DW_OP_breg14 0x7e
#define DW_OP_breg15 0x7f
#define DW_OP_breg16 0x80
#define DW_OP_breg17 0x81
#define DW_OP_breg18 0x82
#define DW_OP_breg19 0x83
#define DW_OP_breg20 0x84
#define DW_OP_breg21 0x85
#define DW_OP_breg22 0x86
#define DW_OP_breg23 0x87
#define DW_OP_breg24 0x88
#define DW_OP_breg25 0x89
#define DW_OP_breg26 0x8a
#define DW_OP_breg27 0x8b
#define DW_OP_breg28 0x8c
#define DW_OP_breg29 0x8d
#define DW_OP_breg30 0x8e
#define DW_OP_breg31 0x8f
#define DW_OP_regx 0x90
#define DW_OP_fbreg 0x91
#define DW_OP_bregx 0x92
#define DW_OP_piece 0x93
#define DW_OP_deref_size 0x94
#define DW_OP_xderef_size 0x95
#define DW_OP_nop 0x96
#define DW_OP_push_object_address 0x97
#define DW_OP_call2 0x98    
#define DW_AT_encoding 0x01



static void emit_dwarf_line_info(Token *tok);
static void emit_dwarf_type(Type *ty);
static void emit_dwarf_tag(int tag);
static void emit_dwarf_attribute(int attr, int value);
static void emit_dwarf_variable(Obj *var, bool is_parameter);
static void emit_dwarf_function(Obj *fn);
static void emit_dwarf_stack_location(int offset);
static void emit_dwarf_register_location(int reg);
static void emit_dwarf_headers();
static void emit_dwarf_types(Obj *prog);
static void emit_abbrev_data();
static void emit_debug_info_header();
static void emit_line_info();
static void determine_prototypes(Obj *prog);



static void emit_dwarf_stack_location(int offset) {
    // Emit the DWARF attribute for stack location
    // DW_AT_location with offset from base pointer (BP or SP)
    emit_dwarf_attribute(DW_AT_location, offset);
}

static void emit_dwarf_register_location(int reg) {
    // Emit the DWARF attribute for register location
    // DW_AT_location with register number
    emit_dwarf_attribute(DW_AT_location, reg);
}


static void emit_dwarf_headers() {
    // Start of the .debug_abbrev section
    println("  .section .debug_abbrev");
    println("begin_abbrev:");
    println("  .byte 0x00");  // Zero termination
    // Emit the abbreviations
    println("  .byte 0x01");  // Abbreviation code for DW_TAG_compile_unit
    println("  .byte 0x01");  // Children: DW_CHILDREN_yes
    println("  .byte 0x0E");  // Attribute: DW_AT_producer
    println("  .byte 0x01");  // Form: DW_FORM_string
    println("  .byte 0x00");  // End of the abbreviation entry

    // Zero-termination of the .debug_abbrev section
    println("  .byte 0x05");  // Zero termination
    // End of the .debug_abbrev section
    println("end_abbrev:");

    // Now start the .debug_info section
    println("  .section .debug_info");
    println("begin_debug_info:");

    // Length of the debug_info (we will fill this in later)
    println("  .long 0");  // Placeholder for the length, to be filled in later

    // Version number (2 bytes)
    println("  .word 4");  // DWARF version 4

    // Abbreviation offset (4 bytes) - should point to the begin_abbrev section Abbrev Offset: 0xb08
    println("  .long begin_abbrev - begin_debug_info");  // Correct offset to the abbreviation section

    // Pointer size (1 byte)
    println("  .byte 8");  // Pointer size: 8 bytes for 64-bit

    // Emit your function's DWARF information here...

    // Now we finalize the length of the .debug_info section
    println("  .long end_debug_info - begin_debug_info - 4");  // Fill in the correct length minus this field

    // End of the .debug_info section
    println("end_debug_info:");

    // Return to .debug_info section for subsequent data
    println("  .section .debug_info");
}


// Helper function to emit abbreviation data
static void emit_abbrev_data() {
    // This is where you define abbreviations for various DWARF entities.
    // The format follows DWARF specifications for encoding.
    // For example:
    println("  .byte 0x01"); // Abbrev number
    println("  .byte DW_TAG_variable"); // Tag for variable
    println("  .byte DW_AT_name"); // Attribute for name
    println("  .byte DW_FORM_strp"); // Form for string pointer
    // Continue for other attributes...
}

// Helper function to emit the initial header for .debug_info
static void emit_debug_info_header() {
    // Emit version and other necessary fields
    println("  .byte 0x03"); // DWARF version 3 (or whatever version you're supporting)
    // More fields need to be added as per the DWARF spec...
}

// Helper function to emit line information
static void emit_line_info() {
    // This is where you emit the necessary line number information.
    // You would emit file names, line numbers, etc.
}


void emit_dwarf_finish() {
    // Emit any necessary final bytes for DWARF sections
    // Finalize all open sections such as .debug_info, .debug_abbrev, etc.
}


static void emit_dwarf_line_info(Token *tok) {
    //emit_dwarf_attribute(DW_AT_decl_file, tok->filename); // Emit file name where declared
    //emit_dwarf_attribute(DW_AT_decl_line, tok->line_no);  // Emit line number where declared
}

static void emit_dwarf_type(Type *ty) {
    switch (ty->kind) {
        case TY_INT:
            emit_dwarf_tag(DW_TAG_base_type);
            //emit_dwarf_attribute(DW_AT_name, "int");
            emit_dwarf_attribute(DW_AT_encoding, DW_ATE_signed);  // Signed integer
            emit_dwarf_attribute(DW_AT_byte_size, 4);  // Size of int is 4 bytes
            break;
        case TY_FLOAT:
            emit_dwarf_tag(DW_TAG_base_type);
            //emit_dwarf_attribute(DW_AT_name, "float");
            emit_dwarf_attribute(DW_AT_encoding, DW_ATE_float);   // Floating point
            emit_dwarf_attribute(DW_AT_byte_size, 4);  // Size of float is 4 bytes
            break;
        // Add cases for other types (e.g., structs, arrays, etc.)
        default:
            // Handle complex types such as structs, unions, arrays, etc.
            break;
    }
}

static void emit_dwarf_tag(int tag) {
    // Emit the DWARF tag to the appropriate section
    // For example, write the tag into .debug_info section
    // Example: emit_section(".debug_info", tag);
}

static void emit_dwarf_attribute(int attr, int value) {
    // Emit the DWARF attribute with its value
    // For example: emit_section(".debug_info", attr, value);
}


static void emit_dwarf_variable(Obj *var, bool is_parameter) {
    // Decide whether this is a function parameter or a local variable
    if (is_parameter) {
        emit_dwarf_tag(DW_TAG_formal_parameter);
    } else {
        emit_dwarf_tag(DW_TAG_variable);
    }

    // Emit the variable's name and type
    //emit_dwarf_attribute(DW_AT_name, var->name);       // Variable name
    //emit_dwarf_attribute(DW_AT_type, var->ty);         // Variable type (we'll link this to the type info)

    // Emit location (register or stack)
    if (var->offset < 0) {
        // Variable is stored on the stack (stack pointer/base pointer + offset)
        emit_dwarf_stack_location(var->offset);
    } else {
        // Variable is stored in a register
        //emit_dwarf_register_location(var->reg);
    }

    // Optionally, emit variable’s source file and line number info
    emit_dwarf_line_info(var->tok);  // Assuming var->tok holds the token for declaration
}



static void emit_dwarf_function(Obj *fn) {

    // // Emit the function's start DWARF information
    // println("  .loc %d %d", fn->file_no, fn->line_no);  // DWARF location for the function
    // println("  .type %s, @function", fn->name);  // DWARF type for the function

    // // Optionally emit additional function attributes
    // if (fn->is_prototyped) {
    //     println("  .cfi_startproc"); // Begin function CFI (Call Frame Information)
    // }
    
    // // Emit DWARF information for parameters
    // for (Obj *param = fn->params; param; param = param->next) {
    //     println("  .loc %d %d", param->file_no, param->line_no); // Parameter location
    //     println("  .cfi_var_offset %s, %d", param->name, param->offset);  // Offset for parameter location
    //     //println("  .param %s", param->name); // Parameter name
    //     // Emit type information for the parameter
    //     emit_dwarf_type(param->ty);
    // }
    
    // // Emit DWARF information for local variables
    // for (Obj *var = fn->locals; var; var = var->next) {
    //     println("  .loc %d %d", var->file_no, var->line_no); // Local variable location
    //     println("  .local %s", var->name); // Local variable name
    //     // Emit type information for the variable
    //     emit_dwarf_type(var->ty);
    // }
    
    // // Emit the function's end DWARF information
    // if (fn->is_prototyped) {
    //     println("  .cfi_endproc"); // End function CFI
    // }
}


void generate_dwarf_info(Obj *prog) {
    // Emit headers for various DWARF sections like .debug_info, .debug_abbrev, .debug_line
    emit_dwarf_headers();
    determine_prototypes(prog);

    // Traverse all functions in the program
    for (Obj *fn = prog; fn; fn = fn->next) {
        if (!fn->is_function) 
            continue;

        // Emit DWARF information for the function
        emit_dwarf_function(fn);

        // Emit DWARF for parameters
        for (Obj *var = fn->params; var; var = var->next) {
            emit_dwarf_variable(var, true);  // true indicates it is a parameter
        }

        // Emit DWARF for local variables
        for (Obj *var = fn->locals; var; var = var->next) {
            emit_dwarf_variable(var, false); // false indicates it is a local variable
        }
    }

    // Optionally emit type information if needed (e.g., for structs or complex types)
    emit_dwarf_types(prog);

    // Finalize the DWARF sections
    emit_dwarf_finish();
}

static void emit_dwarf_types(Obj *prog) {
    // Emit type information for DWARF sections like .debug_info, .debug_abbrev, .debug_line, etc.
    // Example: emit_section(".debug_info", type_data);
}



static void determine_prototypes(Obj *prog) {
  for (Obj *fn = prog; fn; fn = fn->next) {
    if (!fn->is_function)
      continue;

    // Assume it is prototyped unless a param lacks a type
    bool is_prototyped = true;
    for (Obj *var = fn->params; var; var = var->next) {
      if (!var->ty) {
        is_prototyped = false;
        break;
      }
    }
    fn->is_prototyped = is_prototyped;
  }
}
