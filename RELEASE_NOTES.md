# Release notes

This document contains all release notes delivered. Only the current one is on the README.md

## old release notes

1.0.0 Initial version

1.0.1 adding --version -v option and fixing the -cc1 parameter that caused segmentation fault if other mandatory parameters are missing.
trying to document cc1 and x options and adding a max length control parameter. Adding documentation for other parameters too.

1.0.2 fixing issue with cc1 parameter only -cc1-input parameter is mandatory. Finishing parameters documentation.

1.0.3 trying to add some sanitizing functions and check if arguments have valid allowed characters (probably too strict!).

1.0.4 Fixing the output directory for dependencies "xxx.d" when -MD option is set, the output "xxx.d" file is generated in the current directory if no -o parameter defined or in the directory defined by -o parameter (issue #30). Adding Dockerfile and a devcontainer for those who want to play with that (issue #23). Typecheck void type expressions in return and assignment (issue #41). Binary add segfaults when at least 1 arg is non-numeric, and both are non-pointer types (issue #42). It's UB to have a call to va_start without a corresponding call to va_end (issue #51). Fix bug in codegen.c (issue #52). fix issue in main.c (issue #54). Fixed bug in preprocessor process extraneous tokens (issue #95). Hashmap: Do not insert duplicate keys (issue #98).

1.0.5 Fixing assembler error on larger than 32-bit bitfields (issue #65) by GabrielRavier. Fixing bitfield validation by zamfofex (issue #28). Replacing memcmp by strncmp (issue #48) by math4tots. Fixing empty structs as one-byte object (issue #36) by edubart.

1.0.6 Anonymously named bitfield member segfaults compiler (issue #31). Fixing anonymous union field (issue #45) by zamfofex. Fixing wrong size of string initialized by braces (issue #80) by zamfofex.

1.0.7 Internal error when initializing array of long with string literals (issue #72) by GabrielRavier. Fixing postfix tails on compound literals (issue #47) by zamfofex. Trying to fix nested designators error(issue #62). Fixing Using goto inside statement expressions gives an error (issue #37) by zamfofex. Fixing function type parameter without identifier errs (issue #63) by zamfofex.

1.0.8 Internal error on long double initializer (issue #69). Codegen error on atomic long double operation assignments (issue #71). Fix atomic fetch operations (issue #101) by chjj. Adding -soname < arg > and -rpath < dir > parameters (needed to be able to compile curl from source). Soname is used to create a symbolic link and rpath is passed to the linker. Testing chibicc with some C projects (compiling fine tcc, curl).

1.0.9 Adding pthread and pedantic to omitted parameters list. Added -fno-pic parameter. Adding ignored parameter: m32, nostdinc. Adding -dumpmachine parameter. Fixing issue with \_\_has_attribute(diagnose_if). Adding lots of attributes that can be applied to function (for now ignored them) : "\_\_attribute\_\_((noreturn))", "\_\_attribute\_\_((returns_twice))",
"\_\_attribute\_\_((noinline))", "\_\_attribute\_\_((always_inline))", "\_\_attribute\_\_((flatten))", "\_\_attribute\_\_((pure))",
"\_\_attribute\_\_((nothrow))", "\_\_attribute\_\_((sentinel))", "\_\_attribute\_\_((format))", "\_\_attribute\_\_((format_arg))",
"\_\_attribute\_\_((no_instrument_function))", "\_\_attribute\_\_((section))", "\_\_attribute\_\_((constructor))",
"\_\_attribute\_\_((destructor))", "\_\_attribute\_\_((used))", "\_\_attribute\_\_((unused))", "\_\_attribute\_\_((deprecated))",
"\_\_attribute\_\_((weak))", "\_\_attribute\_\_((alias))", "\_\_attribute\_\_((malloc))",
"\_\_attribute\_\_((warn_unused_result))", "\_\_attribute\_\_((nonnull))", "\_\_attribute\_\_((externally_visible))",
"\_\_attribute\_\_((visibility(\"default\")))", "\_\_attribute\_\_((visibility(\"hidden\")))",
"\_\_attribute\_\_((visibility(\"protected\")))", "\_\_attribute\_\_((visibility(\"internal\")))"

1.0.10 Fixing issue about string initialized by function-like (issue #107). Fixing issue when a macro ends a line and the next line starts by "#ifdef" the "#" is not recognized starting from beginning of the line (issue #108). Managing \#warning as preprocessor instruction (issue #109). Fixing issue with union initializer when comma found like "input_control_param_t it = { .id = p_input, .time.i_val = 1};" (issue #110) and input_control_param_t it = { .id = p_input,} (issue #113). Removing fix for issue 106 (caused other issues with VLC when trying to compile).

1.0.11 Fixing issue #113 about \_Atomic when it's placed after the type. Fixing other issue like issue #108 sometimes some #ifdef are not recognized if a macro ends the previous line and the next line starting by a preprocessing instruction. Managing differently -soname and adding option -z, and --version-script. Adding -debug option to write commands in /tmp/chibicc.log (later I'll add some debugs info/values on this file to help to fix bugs). Adding 2 functions in stdatomic.h needed by VLC atomic_compare_exchange_strong_explicit(object, expected, desired, success, failure) that returns false for now and atomic_compare_exchange_weak_explicit(object, expected, desired, success, failure) that returns false too. Managing .lo files (libtool object). Adding generic path for Fix 'gcc library path is not found' on some platforms #108 by [Stardust8502](https://github.com/Stardust8502/chibicc). 

1.0.12 Adding -dotfile parameter that generates a xxx.dot file that we can visualized using graphviz package by [hdewig100](https://github.com/hedwig100/chibicc). Adding in error message chibicc file name and function when a message error is displayed to help for debugging. Adding in Makefile the way to create shared library libchibicc.so. Fixing issue #116 with 1024_160 splitted wrongly in two tokens. Fixing issue #117 with number after generic parameter like "fromtype##2obj_decode". Fixing issue #118 same as 117, to allow some identifiers to start by number when they are generics. Linking lpthread if -pthread is passed. Ignoring -z and -Bsymbolic. Fixing the issue with linkage need to add current directory to the path before the others (probably it's a security issue because it means that for compiling the objects library found in the current path will be taken in priority!)
Fixing issue #119 about cmathcalls. Removing fix for #119 caused an infinite loop and fixing it by adding _Complex as attribute like _Atomic.

1.0.13 Adding other projects compiled successfully with chibicc. Adding some information in debug file like all tokens generated by tokenize function. Fixing some issues found with vlc static_assert function outside a function(#120 and #121). Adding -no-whole-archive and -whole-archive as ignored parameters. Fixing issue with #line that generates negative numbers that caused assembly issue. Fixing issue with argument used twice in regexec function that caused "undefined variable".

1.0.14 Removing sanitizing functions, causing issue during git compile. Fixing issue caused by fix issue 120. Fixing issue with -I \<dir\>. Fixing also the preprocess when some macros are defined after they are used, gcc allows it. For now the temporary fix manages only macro with empty body that they are used before their definition. Fixing issue #126 about old C style skipping for now the extra tokens. Fixing issue #128 about union initialized by an expression. Fixing a basic extended assembly #125 (partially) for now only something like 	\__asm\__("bswapl %0" : "=r" (val) : "0" (val)); works (a lot of work to forecast to add other assembly possibilities step by step). Fixing #127(#126) more securely (ignoring was not enough causing issue during linkage). Fixing a mistake on removing the fix for issue #121 that caused an infinite loop.

1.0.15 -fsigned-char parameter is mandatory for util-linux project. Removed by mistake in the previous version. Re-added it! Removing lots of conditions created for debug purposes that causes now infinite loop!

1.0.16  Fixing issue #133 with old C style function declaration when using comma separator for same variable type parameter declaration. Fixing also issue #136 (ISS-136) zlib project error with unknown extension. Fixing issue #134 (ISS-134) with parameter expression during zlib project.
Fixing issue #131 (ISS-131) parsing issue when trying to compile nginx project caused by fix #121. Adding some projects to test in Makefile because sometimes some fixes cause side effects!

1.0.17 Fixing ISS-129 need to manage output other than "=r". Fixing ISS-139 extended assembly compiling but execution doesn't return the correct result. Fixing temporary ISS-142 caused by join_adjacent_string_literals function.

1.0.18    adding install and uninstall in makefile (#PR24 from rurban). Adding ND_MOD in is_const_expr(#issue 134 from matthewsot). Fixing incorrect small struct passing in 5th argument position (issue #127 from sgraham). Fixing ISS-140 compiling chibicc with chibicc tests failed with trying to parse the object.o file instead of linking only. Fixing some issues with extended assembly (ISS-141) and reformating some but still have one issue with ASSERT used after assembly inline in some case (see ./issues/assign1.c)


1.0.19    fixing extended assembly issue when a register is already used in the template, the variable should be stored in another register available.


1.0.20    Fixing ISS-143 extended assembly doesn't manage well input with r. Removing assign1.c test doesn't work with gcc. Fixing ISS-144 compiling util-linux failed with expression returning void is not supported. Fixing ISS-145 compiling util-linux failed with invalid initalizer2. Fixing ISS-147 compiling util-linux failed with undefined variable __BYTE_ORDER__. Fixing ISS-148 compiling VLC failed with storage class specifier not allowed caused by static_assert function. Fixing also some issues with extended assembly not working in some cases. Fixing issue with extended assembly in string_replace that truncates the null terminated character and causing during nginx compile failure due to incorrect character. Generating "nop" instruction each time we found the memory barrier : __asm__ volatile ("" ::: "memory"). Compiling successfully some projects like curl, nginx, zlib, util-linux, openssl, openssh-portable. But some tests failed for util-linux, openssl and curl that means that probably we have some bugs somewhere. Fixing ISS-152 extended assembly   __asm__ __volatile__ ("rep; nop" ::: "memory"). Fixing ISS-150 fix on issue 40 caused other failures during VLC compilation. Fixing ISS-151 compiling neovim failed in struct_initializer2. Fixing ISS-153 -fomit-frame-pointer, -funwind-tables caused failure during neovim compilation. Adding -dM option to print the macro definition (it's not exactly the same result given by gcc) needed for compile neovim project.