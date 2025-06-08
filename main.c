#include "chibicc.h"
#define MAIN_C "main.c"

typedef enum
{
  FILE_NONE,
  FILE_C,
  FILE_ASM,
  FILE_OBJ,
  FILE_AR,
  FILE_DSO,
  FILE_RSP,
} FileType;

StringArray include_paths;
bool opt_fcommon = true;
bool opt_fbuiltin = true;
bool opt_fpic;
bool opt_fpie;
bool opt_shared;
bool opt_sse3;
bool opt_sse4;
bool opt_g;



static FileType opt_x;
static StringArray opt_include;
bool opt_E;
static bool opt_A;
static bool opt_M;
static bool opt_MD;
static bool opt_MMD;
static bool opt_MP;
static bool opt_S;
static bool opt_c;
static bool opt_cc1;
static bool opt_hash_hash_hash;
static bool opt_static;
static bool isCc1input = false;
static bool isCc1output = false;
static char *opt_MF;
static char *opt_MT;
char *opt_o;
static char *opt_linker;
// static char *symbolic_name;
static char *r_path;
static bool opt_nostdinc;
static bool opt_nostdlib;
static bool opt_v;

static StringArray ld_extra_args;
static StringArray std_include_paths;

char *base_file;
static char *output_file;
FILE *f;

// for dot diagrams
FILE *dotf;
char *dot_file;
bool isDotfile = false;
bool isDebug = false;
bool isPrintMacro = false;
bool printTokens = false;
char *previousfile = " ";
Context *ctx;

static char logFile[] = "/tmp/chibicc.log";
static StringArray input_paths;
static StringArray tmpfiles;


static void enable_core_dump() {
    struct rlimit rl;
    rl.rlim_cur = RLIM_INFINITY;
    rl.rlim_max = RLIM_INFINITY;
    if (setrlimit(RLIMIT_CORE, &rl) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }
}

static void segfault_handler(int signum) {
    printf("Segmentation fault (signal %d)\n", signum);
    abort();  // Generate a core dump
}

static void setup_signal_handlers() {
    signal(SIGSEGV, segfault_handler);
}


static void print_string_array(StringArray *arr) {
    for (int i = 0; i < arr->len; i++) {
        printf("=====ld_extra_args[%d]: %s\n", i, arr->data[i]);
    }
}



static void print_include_directories() {
    strarray_push(&include_paths,  "./include");
    // Add standard include paths.
    strarray_push(&include_paths, "/usr/local/include/x86_64-linux-gnu/chibicc");
    strarray_push(&include_paths, "/usr/include/x86_64-linux-gnu");
    strarray_push(&include_paths, "/usr/local/include");
    strarray_push(&include_paths, "/usr/include");
    strarray_push(&include_paths, "/usr/lib/gcc/x86_64-linux-gnu/11/include");
    //strarray_push(&include_paths, "/usr/include/chibicc/include");
    #if defined(__APPLE__) && defined(__MACH__)
    strarray_push(&include_paths, "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include");
    define_macro("__GNUC__", "5"); // for MacOS SDK compatibility
    #endif

    // Keep a copy of the standard include paths for -MMD option.
    for (int i = 0; i < include_paths.len; i++)
    {
      strarray_push(&std_include_paths, include_paths.data[i]);
    }

    printf("#include \"...\" search starts here:\n");
    printf("#include <...> search starts here:\n");

    for (int i = 0; i < std_include_paths.len; i++)
    {
      char *dir = std_include_paths.data[i];
      printf(" %s\n", dir);
    }

    printf("End of search list.\n");
}


static void usage(int status)
{
  fprintf(stderr, HELP);
  fprintf(stderr, USAGE);
  exit(status);
}

// print the version of the command
static void printVersion()
{
  printf("%s version : %s\n", PRODUCT, VERSION);
  
}

// check the length and validity of parameter to avoid non valid input values
static void check_parms_length(char *arg)
{
  if (strlen(arg) > MAXLEN)
  {
    error("%s : %s:%d: error: in check_parms_length maximum length parameter overpassed", MAIN_C, __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
}

static bool take_arg(char *arg)
{
  char *x[] = {
      "-o", "-I", "-idirafter", "-include", "-x", "-MF", "-MT", "-MQ", "-Xlinker", "-cc1-input", "-cc1-output", "-fuse-ld", "-soname", "-rpath", "--version-script"};

  for (int i = 0; i < sizeof(x) / sizeof(*x); i++)
  {
    if (!strcmp(arg, x[i]))
      return true;
  }
  return false;
}

static void add_default_include_paths(char *argv0)
{
  if (opt_nostdinc)
    return;
  // We expect that chibicc-specific include files are installed
  // to ./include relative to argv[0].
  strarray_push(&include_paths, format("%s/include", dirname(strdup(argv0))));

  // Add standard include paths.
  strarray_push(&include_paths, "/usr/local/include/x86_64-linux-gnu/chibicc");
  strarray_push(&include_paths, "/usr/include");
  strarray_push(&include_paths, "/usr/local/include");
  strarray_push(&include_paths, "/usr/include/x86_64-linux-gnu");
  strarray_push(&include_paths, "/usr/lib/gcc/x86_64-linux-gnu/11/include");
  //strarray_push(&include_paths, "/usr/include/chibicc/include");
  #if defined(__APPLE__) && defined(__MACH__)
  strarray_push(&include_paths, "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include");
  define_macro("__GNUC__", "5"); // for MacOS SDK compatibility
  #endif

  // Keep a copy of the standard include paths for -MMD option.
  for (int i = 0; i < include_paths.len; i++)
  {
    strarray_push(&std_include_paths, include_paths.data[i]);
  }
}

static void define(char *str)
{
  char *eq = strchr(str, '=');
  if (eq)
    define_macro(strndup(str, eq - str), eq + 1);
  else
    define_macro(str, "1");
}

static FileType parse_opt_x(char *s)
{
  if (!strcmp(s, "c"))
    return FILE_C;
  if (!strcmp(s, "assembler"))
    return FILE_ASM;
  if (!strcmp(s, "none"))
    return FILE_NONE;
  error("%s : %s:%d: error: in parse_opt_x <command line>: unknown argument for -x: %s", MAIN_C, __FILE__, __LINE__, s);
}


static char *quote_makefile(char *s)
{
  char *buf = calloc(1, strlen(s) * 2 + 1);
  if (buf == NULL)
  {
    error("%s : %s:%d: error: in quote_makefile buf pointer is null!", MAIN_C, __FILE__, __LINE__);
  }

  for (int i = 0, j = 0; s[i]; i++)
  {
    switch (s[i])
    {
    case '$':
      buf[j++] = '$';
      buf[j++] = '$';
      break;
    case '#':
      buf[j++] = '\\';
      buf[j++] = '#';
      break;
    case ' ':
    case '\t':
      for (int k = i - 1; k >= 0 && s[k] == '\\'; k--)
        buf[j++] = '\\';
      buf[j++] = '\\';
      buf[j++] = s[i];
      break;
    default:
      buf[j++] = s[i];
      break;
    }
  }
  return buf;
}

static void parse_args(int argc, char **argv)
{
  // Make sure that all command line options that take an argument
  // have an argument.
  for (int i = 1; i < argc; i++)
    if (take_arg(argv[i]))
      if (!argv[++i])
      {
        printf("parameter without value! the following parameters need to be followed by a value :\n");
        printf("-o, -I, -idirafter, -include, -x, -MF, -MQ, -MT, -Xlinker, -cc1-input, -cc1-output, -fuse-ld, -soname, -rpath, --version-script \n");
        usage(1);
      }

  StringArray idirafter = {};

  for (int i = 1; i < argc; i++)
  {

    if (!strcmp(argv[i], "-###"))
    {
      opt_hash_hash_hash = true;
      continue;
    }

    if (!strcmp(argv[i], "-cc1"))
    {
      opt_cc1 = true;
      continue;
    }

    if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
    {
      usage(0);
      continue;
    }

    if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")  || !strcmp(argv[i], "-V") || !strcmp(argv[i], "-version"))
    {
      printVersion();
      print_include_directories();
      opt_v = true;
      //exit(0);
      continue;

    }

    if (!strcmp(argv[i], "-fuse-ld"))
    {
      opt_linker = argv[++i];
      check_parms_length(opt_linker);
      continue;
    }

    if (startsWith(argv[i], "-march="))
    {
      continue;
    }


    // if (!strcmp(argv[i], "-msse3")) {
    //   opt_sse3 = true;
    //   continue;
    // }

    // if (startsWith(argv[i], "-msse4")) {
    //   opt_sse4 = true;
    //   continue;
    // }

    if (startsWith(argv[i], "-flto"))
    {
      continue;
    }

    if (startsWith(argv[i], "-mtune="))
    {
      continue;
    }


    if (!strcmp(argv[i], "-o"))
    {
      opt_o = argv[++i];
      check_parms_length(opt_o);
      continue;
    }

    if (!strncmp(argv[i], "-o", 2))
    {
      opt_o = argv[i] + 2;
      continue;
    }

    if (!strcmp(argv[i], "-S"))
    {
      opt_S = true;
      continue;
    }

    if (!strcmp(argv[i], "-debug"))
    {
      isDebug = true;
      continue;
    }

    //to print all tokens
    if (!strcmp(argv[i], "-print"))
    {
      printTokens = true;
      continue;
    }


    if (!strcmp(argv[i], "-dM"))
    {
      isPrintMacro = true;
      continue;
    }

    if (!strcmp(argv[i], "-dotfile"))
    {
      isDotfile = true;
      continue;
    }

    if (!strcmp(argv[i], "-fcommon"))
    {
      opt_fcommon = true;
      continue;
    }

    if (!strcmp(argv[i], "-fno-common"))
    {
      opt_fcommon = false;
      continue;
    }


    if (!strcmp(argv[i], "-fno-builtin"))
    {
      opt_fbuiltin = false;
      continue;
    }

    if (!strcmp(argv[i], "-c"))
    {
      opt_c = true;
      continue;
    }

    if (!strcmp(argv[i], "-E"))
    {
      opt_E = true;
      continue;
    }

    // sometimes we can have -I dir or -Idir
    if (!strncmp(argv[i], "-I", 2))
    {
      if (strlen(argv[i]) == 2)
        strarray_push(&include_paths, argv[++i]);
      else
        strarray_push(&include_paths, argv[i] + 2);
      continue;
    }

    // seems to be used to define macros ?
    if (!strcmp(argv[i], "-D"))
    {
      char *tmp = argv[++i];
      // define(argv[++i]);
      check_parms_length(tmp);
      define(tmp);
      continue;
    }

    if (!strncmp(argv[i], "-D", 2))
    {
      char *tmp = argv[i] + 2;
      check_parms_length(tmp);
      define(tmp);
      // define(argv[i] + 2);
      continue;
    }

    if (!strcmp(argv[i], "-U"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      undef_macro(tmp);
      // undef_macro(argv[++i]);
      continue;
    }

    if (!strncmp(argv[i], "-U", 2))
    {
      char *tmp = argv[i] + 2;
      check_parms_length(tmp);
      undef_macro(tmp);
      // undef_macro(argv[i] + 2);
      continue;
    }

    if (!strcmp(argv[i], "-include"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      strarray_push(&opt_include, tmp);
      // strarray_push(&opt_include, argv[++i]);
      continue;
    }

    if (!strcmp(argv[i], "-x"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      opt_x = parse_opt_x(tmp);
      continue;
    }

    if (!strncmp(argv[i], "-x", 2))
    {
      char *tmp = argv[i] + 2;
      check_parms_length(tmp);
      opt_x = parse_opt_x(tmp);
      continue;
    }

    if (!strncmp(argv[i], "-l", 2) || !strncmp(argv[i], "-Wl,", 4))
    {
      if (!strncmp(argv[i], "-Wl,-z", 6))
        continue;
      char *tmp = argv[i];
      check_parms_length(tmp);
      strarray_push(&input_paths, tmp);
      // strarray_push(&input_paths, argv[i]);
      continue;
    }

    if (!strcmp(argv[i], "-Xlinker"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, tmp);
      // strarray_push(&ld_extra_args, argv[++i]);
      continue;
    }


    // not sure why the --version-script is interpreted as -version-script ?
    if (!strcmp(argv[i], "-version-script") || !strcmp(argv[i], "--version-script"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, "--version-script");
      strarray_push(&ld_extra_args, tmp);
      // strarray_push(&ld_extra_args, argv[++i]);
      continue;
    }

    if (!strcmp(argv[i], "-x"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, tmp);
      // strarray_push(&ld_extra_args, argv[++i]);
      continue;
    }

    if (!strcmp(argv[i], "-s"))
    {
      strarray_push(&ld_extra_args, "-s");
      continue;
    }

    if (!strcmp(argv[i], "-M"))
    {
      opt_M = true;
      continue;
    }

    if (!strcmp(argv[i], "-MF"))
    {
      opt_MF = argv[++i];
      check_parms_length(opt_MF);
      continue;
    }

    if (!strcmp(argv[i], "-MP"))
    {
      opt_MP = true;
      continue;
    }

    if (!strcmp(argv[i], "-MT"))
    {
      if (opt_MT == NULL)
        opt_MT = argv[++i];
      else
        opt_MT = format("%s %s", opt_MT, argv[++i]);
      check_parms_length(opt_MT);
      continue;
    }

    if (!strcmp(argv[i], "-MD"))
    {
      opt_MD = true;
      continue;
    }

    if (!strcmp(argv[i], "-MQ"))
    {
      if (opt_MT == NULL)
        opt_MT = quote_makefile(argv[++i]);
      else
        opt_MT = format("%s %s", opt_MT, quote_makefile(argv[++i]));
      check_parms_length(opt_MT);
      continue;
    }

    if (!strcmp(argv[i], "-MMD"))
    {
      opt_MD = opt_MMD = true;
      continue;
    }

    if (!strcmp(argv[i], "-fpic") || !strcmp(argv[i], "-fPIC"))
    {
      opt_fpic = true;      
      continue;
    }

    //trying to fix -fpie parameter =====ISS-156 forcing shared if -pie is received
    if (!strcmp(argv[i], "-fpie") || !strcmp(argv[i], "-fPIE") || !strcmp(argv[i], "-pie"))
    {
      opt_fpie = true;
      strarray_push(&ld_extra_args, "-pie");
      continue;
    }

    if (!strcmp(argv[i], "-fno-pic"))
    {
      opt_fpic = false;
      continue;
    }

    if (!strcmp(argv[i], "-cc1-input"))
    {
      base_file = argv[++i];
      check_parms_length(base_file);
      isCc1input = true;
      continue;
    }

    if (!strcmp(argv[i], "-cc1-output"))
    {
      isCc1output = true;
      output_file = argv[++i];
      check_parms_length(output_file);
      continue;
    }

    if (!strcmp(argv[i], "-idirafter"))
    {
      char *tmp = argv[i++];
      check_parms_length(tmp);
      strarray_push(&idirafter, tmp);
      // strarray_push(&idirafter, argv[i++]);
      continue;
    }

    if (!strcmp(argv[i], "-static"))
    {
      opt_static = true;
      strarray_push(&ld_extra_args, "-static");
      continue;
    }

    if (!strcmp(argv[i], "-shared"))
    {
      opt_shared = true;
      //opt_fpic = true;
      strarray_push(&ld_extra_args, "-shared");
      continue;
    }

    if (!strcmp(argv[i], "-pthread"))
    {
      strarray_push(&ld_extra_args, "-lpthread");
      continue;
    }

    if (!strncmp(argv[i], "-L", 2))
    {
      //strarray_push(&ld_extra_args, "-L");
      char *tmp = argv[i];
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, tmp);
      continue;
    }

    if (!strcmp(argv[i], "-L"))
    {
      strarray_push(&ld_extra_args, "-L");
      char *tmp = argv[++i];
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, tmp);
      // strarray_push(&ld_extra_args, argv[++i]);
      continue;
    }

    if (!strncmp(argv[i], "-L", 2))
    {
      strarray_push(&ld_extra_args, "-L");
      char *tmp = argv[i] + 2;
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, tmp);
      // strarray_push(&ld_extra_args, argv[i] + 2);
      continue;
    }

    if (!strcmp(argv[i], "-hashmap-test"))
    {
      hashmap_test();
      exit(0);
    }

    if (!strcmp(argv[i], "-dumpmachine"))
    {
      dump_machine();
      exit(0);
    }

    if (!strcmp(argv[i], "-dumpversion"))
    {
      dump_version();
      exit(0);
    }


    //-soname create a symbolic link before calling the linker like in gcc -Wl,-soname,libcurl.so.4 -o libcurl.so.4.8.0
    if (!strcmp(argv[i], "-soname"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      strarray_push(&ld_extra_args, "-soname");
      strarray_push(&ld_extra_args, tmp);
      // symbolic_name = tmp;
      continue;
    }


    if (!strcmp(argv[i], "Wl,-rpath,") || !strcmp(argv[i], "-rpath"))
    {
      char *tmp = argv[++i];
      check_parms_length(tmp);
      r_path = tmp;
      strarray_push(&ld_extra_args, "-rpath");
      strarray_push(&ld_extra_args, r_path);
      continue;
    }

    //for printing AST
    if (!strcmp(argv[i], "-A")) {
      opt_A = true;
      continue;
    } 

    //other options -Axxx ignored
    if (startsWith(argv[i], "-A"))
    {
      continue;
    }

      if (!strcmp(argv[i], "-rdynamic")) {
      strarray_push(&input_paths, "-Wl,--export-dynamic");
      continue;
    }

    if (!strncmp(argv[i], "-g", 2)) {
      if (argv[i][2] == '0')
        opt_g = false;
      else
        opt_g = true;
      continue;
    }


    if (!strcmp(argv[i], "-nostdinc")) {
      opt_nostdinc = true;
      continue;
    }

    if (!strcmp(argv[i], "-nostdlib")) {
      opt_nostdlib = true;
      continue;
    }

    if (!strcmp(argv[i], "-fp-model")) {
      i++; // Skip the argument following -fp-model
      continue;
    }

    // These options are ignored for now.
    if (!strncmp(argv[i], "-O", 2) ||
        !strncmp(argv[i], "-W", 2) ||
        !strncmp(argv[i], "-P", 2) || 
        !strcmp(argv[i], "-ffreestanding") ||
        !strcmp(argv[i], "-fno-omit-frame-pointer") ||
        !strcmp(argv[i], "-fomit-frame-pointer") ||   
        !strcmp(argv[i], "-funwind-tables") ||   
        !strcmp(argv[i], "-fno-stack-protector") ||
        !strcmp(argv[i], "-fno-strict-aliasing") ||
        !strcmp(argv[i], "-m64") ||
        !strcmp(argv[i], "-m32") ||
        !strcmp(argv[i], "--whole-archive") ||
        !strcmp(argv[i], "--no-whole-archive") ||
        !strcmp(argv[i], "-fsigned-char") ||
        !strcmp(argv[i], "-Bsymbolic") ||
        !strcmp(argv[i], "-z") ||
        !strcmp(argv[i], "defs") ||
        !strcmp(argv[i], "-pedantic") ||
        !strcmp(argv[i], "-mno-red-zone") ||
        !strcmp(argv[i], "-fvisibility=default") ||
        !strcmp(argv[i], "-fvisibility=hidden") ||
        // !strcmp(argv[i], "-Werror=invalid-command-line-argument") ||
        // !strcmp(argv[i], "-Werror=unknown-warning-option") ||
        !strcmp(argv[i], "-Wsign-compare") ||
        !strcmp(argv[i], "-Wundef") ||
        !strcmp(argv[i], "-Wpointer-arith") ||
        !strcmp(argv[i], "-Wvolatile-register-var") ||
        !strcmp(argv[i], "-Wformat") ||
        !strcmp(argv[i], "-Wformat-security") ||
        !strcmp(argv[i], "-Wduplicated-branches") ||
        !strcmp(argv[i], "-Wduplicated-cond") ||
        !strcmp(argv[i], "-Wbad-function-cast") ||
        !strcmp(argv[i], "-Wwrite-strings") || 
        !strcmp(argv[i], "-Wlogical-op") || 
        !strcmp(argv[i], "-Wshadow=local") || 
        !strcmp(argv[i], "-Wmultistatement-macros") || 
        !strcmp(argv[i], "-fstack-protector") || 
        !strcmp(argv[i], "-fstack-protector-strong") || 
        !strcmp(argv[i], "-fstack-clash-protection") || 
        !strcmp(argv[i], "-fdiagnostics-show-option") || 
        !strcmp(argv[i], "-fasynchronous-unwind-tables") || 
        !strcmp(argv[i], "-fexceptions") || 
        !strcmp(argv[i], "--print-search-dirs") || 
        !strcmp(argv[i], "-fdiagnostics-show-option") || 
        !strcmp(argv[i], "-Xc") ||
        !strcmp(argv[i], "-Aa") ||
        !strcmp(argv[i], "-w") ||
        !strcmp(argv[i], "--param=ssp-buffer-size=4") ||
        !strcmp(argv[i], "-fno-lto") ||
        !strcmp(argv[i], "-c99") ||
        !strcmp(argv[i], "-fdiagnostics-color=always")  ||
        !strcmp(argv[i], "-mfpmath=sse") ||
        !strcmp(argv[i], "-ffunction-sections")  ||   
        !strcmp(argv[i], "-fdata-sections")    ||  
        !strcmp(argv[i], "-fprofile-arcs")    ||          
        !strcmp(argv[i], "-ftest-coverage")    ||                  
        !strcmp(argv[i], "-mindirect-branch-register")         
        )
      continue;

    if (startsWith(argv[i], "-std"))
    {
      continue;
    }


    if (argv[i][0] == '-' && argv[i][1] != '\0')
      error("%s : %s:%d: error: in parse_args unknown argument: %s", MAIN_C, __FILE__, __LINE__, argv[i]);

    strarray_push(&input_paths, argv[i]);
  }

  for (int i = 0; i < idirafter.len; i++)
    strarray_push(&include_paths, idirafter.data[i]);


  if (input_paths.len == 0) {
    if (!opt_v)
      error("%s : %s:%d: error: in parse_args no input files", MAIN_C, __FILE__, __LINE__);
    exit(0);
  }

  // -E implies that the input is the C macro language.
  if (opt_E)
    opt_x = FILE_C;
}


static FILE *open_file(char *path)
{
  if (!path || strcmp(path, "-") == 0)
    return stdout;

  FILE *out = fopen(path, "w");
  if (!out)
    error("%s : %s:%d: error: in open_file cannot open output file: %s: %s", MAIN_C, __FILE__, __LINE__, path, strerror(errno));
  return out;
}

static bool endswith(char *p, char *q)
{
  int len1 = strlen(p);
  int len2 = strlen(q);
  return (len1 >= len2) && !strcmp(p + len1 - len2, q);
}

// returns filename example ./test/hello.c returns hello.c
char *extract_filename(char *tmpl)
{
  char *filename = basename(strdup(tmpl));
  return format("%s", filename);
}

char * extract_path(char* tmpl)
{
    char* parent = calloc(1, sizeof(char) * 300);
    int parentLen;
    char* last = strrchr(tmpl, '/');

    if (last != NULL) {

        parentLen = strlen(tmpl) - strlen(last + 1);
        if (parentLen > 300)
          error("%s : %s:%d: error: no enough size for parent in getParent function %d expected ", MAIN_C, __FILE__, __LINE__, parentLen);
        strncpy(parent, tmpl, parentLen);
    } 

return parent;
}


// Replace file extension
char *replace_extn(char *tmpl, char *extn)
{
  char *filename = extract_filename(tmpl);
  char *dot = strrchr(filename, '.');
  if (dot)
    *dot = '\0';
  return format("%s%s", filename, extn);
}

static void cleanup(void)
{
  if (!isDebug)
  {
    for (int i = 0; i < tmpfiles.len; i++)
      unlink(tmpfiles.data[i]);
  }

  if ((isDebug && f != NULL) || (printTokens && f != NULL))
    fclose(f);

  // for dot diagrams
  if (isDotfile && dotf != NULL)
  {
    fprintf(dotf, "}\n");
    fclose(dotf);
  }
}

static char *create_tmpfile(void)
{
  char *path = strdup("/tmp/chibicc-XXXXXX");
  if (path == NULL)
    error("%s : in create_tmpfile path path is null", MAIN_C);
  int fd = mkstemp(path);
  if (fd == -1)
    error("%s : %s:%d: error: in create_tmpfile mkstemp failed: %s", MAIN_C, __FILE__, __LINE__, strerror(errno));
  close(fd);

  strarray_push(&tmpfiles, path);
  return path;
}

static void run_subprocess(char **argv)
{
  // If -### or -debug is given, dump the subprocess's command line.
  if (opt_hash_hash_hash)
  {
    fprintf(stdout, "%s", argv[0]);
    for (int i = 1; argv[i]; i++)
      fprintf(stdout, " %s", argv[i]);
    fprintf(stdout, "\n");
  }

  if (isDebug && f != NULL)
  {
    fprintf(f, "%s", argv[0]);
    for (int i = 1; argv[i]; i++)
      fprintf(f, " %s", argv[i]);
    fprintf(f, "\n");
  }

  if (fork() == 0)
  {

    execvp(argv[0], argv);
    fprintf(stderr, "%s : %s:%d: error: in run_subprocess exec failed: %s: %s\n", MAIN_C, __FILE__, __LINE__, argv[0], strerror(errno));
    _exit(1);
  }

  // Wait for the child process to finish.
  int status;
  while (wait(&status) > 0)
    ;
  if (status != 0)
    exit(1);
}

static void run_cc1(int argc, char **argv, char *input, char *output)
{
  char **args = calloc(argc + 10, sizeof(char *));
  if (args == NULL)
    error("%s : %s:%d: error: in run_cc1 args is null", MAIN_C, __FILE__, __LINE__);
  memcpy(args, argv, argc * sizeof(char *));
  args[argc++] = "-cc1";

  if (input)
  {
    args[argc++] = "-cc1-input";
    args[argc++] = input;
  }

  if (output)
  {
    args[argc++] = "-cc1-output";
    args[argc++] = output;
  }

  run_subprocess(args);
  free(args);
}

// Print tokens to stdout. Used for -E.
static void print_tokens(Token *tok)
{
  FILE *out = open_file(opt_o ? opt_o : "-");

  int line = 1;
  for (; tok->kind != TK_EOF; tok = tok->next)
  {
    if (line > 1 && tok->at_bol)
      fprintf(out, "\n");
    if (tok->has_space && !tok->at_bol)
      fprintf(out, " ");
    fprintf(out, "%.*s", tok->len, tok->loc);
    line++;
  }
  fprintf(out, "\n");
}

static bool in_std_include_path(char *path)
{
  for (int i = 0; i < std_include_paths.len; i++)
  {
    char *dir = std_include_paths.data[i];
    int len = strlen(dir);
    if (strncmp(dir, path, len) == 0 && path[len] == '/')
      return true;
  }
  return false;
}

// If -M options is given, the compiler write a list of input files to
// stdout in a format that "make" command can read. This feature is
// used to automate file dependency management.
static void print_dependencies(void)
{
  char *path;
  if (opt_MF)
    path = opt_MF;
  else if (opt_MD)
  {
    // fixing the issue with file.d created in the current directory if no -o parameter or in the output directory define by -o parameter
    path = replace_extn(opt_o ? opt_o : base_file, ".d");
    if (opt_o != NULL)
    {
      char *fullpath;
      //char *filename;
      //filename = extract_filename(opt_o);
      fullpath = extract_path(opt_o);
      strncat(fullpath, path, strlen(path));
      path = fullpath;
    }
  }
  else if (opt_o)
    path = opt_o;
  else
    path = "-";

  FILE *out = open_file(path);
  if (opt_MT)
    fprintf(out, "%s:", opt_MT);
  else
    fprintf(out, "%s:", quote_makefile(replace_extn(base_file, ".o")));

  File **files = get_input_files();

  for (int i = 0; files[i]; i++)
  {
    if (opt_MMD && in_std_include_path(files[i]->name))
      continue;
    fprintf(out, " \\\n  %s", files[i]->name);
  }

  fprintf(out, "\n\n");

  if (opt_MP)
  {
    for (int i = 1; files[i]; i++)
    {
      if (opt_MMD && in_std_include_path(files[i]->name))
        continue;
      fprintf(out, "%s:\n\n", quote_makefile(files[i]->name));
    }
  }
}

static Token *must_tokenize_file(char *path)
{
  Token *tok = tokenize_file(path);
  if (!tok)
    error("%s : %s:%d: error: in must_tokenize_file %s: %s", MAIN_C, __FILE__, __LINE__, path, strerror(errno));
  return tok;
}

static Token *append_tokens(Token *tok1, Token *tok2)
{
  if (!tok1 || tok1->kind == TK_EOF)
    return tok2;

  Token *t = tok1;
  while (t->next->kind != TK_EOF)
    t = t->next;
  t->next = tok2;
  return tok1;
}

static void cc1(void)
{
  Token *tok = NULL;

  // Process -include option
  for (int i = 0; i < opt_include.len; i++)
  {
    char *incl = opt_include.data[i];

    char *path;
    if (file_exists(incl))
    {
      path = incl;
    }
    else
    {
      path = search_include_paths(incl);
      if (!path)
        error("%s : %s:%d: error: in cc1 -include: %s: %s", MAIN_C, __FILE__, __LINE__, incl, strerror(errno));
    }

    Token *tok2 = must_tokenize_file(path);
    tok = append_tokens(tok, tok2);
  }

  // Tokenize and parse.
  Token *tok2 = must_tokenize_file(base_file);
  bool isReadLine = false;
  tok = append_tokens(tok, tok2);
  tok = preprocess(tok, isReadLine);


  // If -M or -MD are given, print file dependencies.
  if (opt_M || opt_MD)
  {
    print_dependencies();
    if (opt_M)
      return;
  }

  //print macro in preprocess.c
  if (isPrintMacro)
  {
    return;
  }

  // If -E is given, print out preprocessed C code as a result.
  if (opt_E)
  {
    print_tokens(tok);
    return;
  }

  Obj *prog = parse(tok);
  if (opt_A) {
    print_ast(f, prog);
    return;
  }

  // Open a temporary output buffer.
  char *buf;
  size_t buflen;
  FILE *output_buf = open_memstream(&buf, &buflen);

  // Traverse the AST to emit assembly.
  codegen(prog, output_buf);
  fclose(output_buf);

  // Write the asembly text to a file.
  FILE *out = open_file(output_file);
  fwrite(buf, buflen, 1, out);
  fclose(out);
}

static void assemble(char *input, char *output)
{
  
  if (endswith(input, ".S")) {
    char *cmd[] = {"gcc", "-c", "-masm=intel", input, "-o", output, NULL};
    run_subprocess(cmd);
  } else {
    char *cmd[] = {"as", "-c", input, "-o", output, NULL};
    run_subprocess(cmd);
  }
}

// static void symbolic_link(char *input, char *output) {
//   char *cmd[] = {"ln", "-s", "-f", output, input, NULL};
//   run_subprocess(cmd);
// }

void dump_machine(void)
{
  fprintf(stdout, DEFAULT_TARGET_MACHINE "\n");
}

void dump_version(void)
{
  fprintf(stdout, VERSION "\n");
}



static char *find_file(char *pattern)
{
  char *path = NULL;
  glob_t buf = {};
  glob(pattern, 0, NULL, &buf);
  if (buf.gl_pathc > 0)
    path = strdup(buf.gl_pathv[buf.gl_pathc - 1]);
  globfree(&buf);
  return path;
}

// Returns true if a given file exists.
bool file_exists(char *path)
{
  struct stat st;
  return !stat(path, &st);
}

static char *find_libpath(void)
{
  if (file_exists("/usr/lib/x86_64-linux-gnu/crti.o"))
    return "/usr/lib/x86_64-linux-gnu";
  if (file_exists("/usr/lib64/crti.o"))
    return "/usr/lib64";
  error("%s : %s:%d: error: in find_libpath library path is not found", MAIN_C, __FILE__, __LINE__);
}

static char *find_gcc_libpath(void)
{
  char *paths[] = {
      "/usr/lib/gcc/x86_64-linux-gnu/*/crtbegin.o",
      "/usr/lib/gcc/x86_64-*/*/crtbegin.o",
      "/usr/lib/gcc/x86_64-pc-linux-gnu/*/crtbegin.o", // For Gentoo
      "/usr/lib/gcc/x86_64-redhat-linux/*/crtbegin.o", // For Fedora
  };

  for (int i = 0; i < sizeof(paths) / sizeof(*paths); i++)
  {
    char *path = find_file(paths[i]);
    if (path)
      return dirname(path);
  }

  error("%s : %s:%d: error: in find_gcc_libpath gcc library path is not found", MAIN_C, __FILE__, __LINE__);
}

static void run_linker(StringArray *inputs, char *output)
{
  StringArray arr = {};
  if (opt_linker != NULL)
  {
    strarray_push(&arr, opt_linker);
  }
  else
  {
    strarray_push(&arr, "ld");
  }
  strarray_push(&arr, "-o");
  strarray_push(&arr, output);
  strarray_push(&arr, "-m");
  strarray_push(&arr, "elf_x86_64");
  strarray_push(&arr, "-allow-multiple-definition");


  //for some projects like POSTGRES it seems that the specific path for the project 
  //should be defined first
  for (int i = 0; i < ld_extra_args.len; i++) {
    //printf("====%s\n", ld_extra_args.data[i]);
    strarray_push(&arr, ld_extra_args.data[i]);
  }


  //enabling verbose mode for linker in case of debug
  if (isDebug)
    strarray_push(&arr, "--verbose=1");

  char *libpath = find_libpath();
  char *gcc_libpath = find_gcc_libpath();

  // Only add startup files if not using -nostdlib
  if (!opt_nostdlib) {
    if (opt_shared)
    {
      strarray_push(&arr, format("%s/crti.o", libpath));
      strarray_push(&arr, format("%s/crtbeginS.o", gcc_libpath));
    }
    //trying to fix ====ISS-156 fpie parameter
    else if (opt_fpie) {
      strarray_push(&arr, format("%s/Scrt1.o", libpath));
      strarray_push(&arr, format("%s/crti.o", libpath));
      strarray_push(&arr, format("%s/crtbeginS.o", gcc_libpath));
      strarray_push(&arr, format("%s/crtendS.o", gcc_libpath));

    }
  else
    {
      strarray_push(&arr, format("%s/crt1.o", libpath));
      strarray_push(&arr, format("%s/crti.o", libpath));
      strarray_push(&arr, format("%s/crtbegin.o", gcc_libpath));    
    }
  }

  strarray_push(&arr, format("-L%s", gcc_libpath));
 // strarray_push(&arr, "-L../../../src/interfaces/libpq");
  strarray_push(&arr, "-L/usr/lib/x86_64-linux-gnu");
  strarray_push(&arr, "-L/usr/lib64");
  strarray_push(&arr, "-L/lib64");
  strarray_push(&arr, "-L/usr/lib/x86_64-linux-gnu");
  strarray_push(&arr, "-L/lib/x86_64-linux-gnu");
  strarray_push(&arr, "-L/usr/lib/x86_64-pc-linux-gnu");
  strarray_push(&arr, "-L/usr/lib/x86_64-redhat-linux");
  strarray_push(&arr, "-L/usr/lib");
  strarray_push(&arr, "-L/lib");   
  strarray_push(&arr, "-L.");
  //strarray_push(&arr, "-L/usr/lib/gcc/x86_64-linux-gnu/11/x86_64-linux-gnu");


  if (!opt_static)
  {
    strarray_push(&arr, "-dynamic-linker");
    strarray_push(&arr, "/lib64/ld-linux-x86-64.so.2");
      //adding -lm to fix issue with math.h
      if (!opt_nostdlib)
        strarray_push(&arr, "-lm");
  }

  
  for (int i = 0; i < inputs->len; i++) {
    //printf("====%s\n", inputs->data[i]);
    strarray_push(&arr, inputs->data[i]);
  }

 
  if (opt_static)
  {
    strarray_push(&arr, "--start-group");
    strarray_push(&arr, "-lgcc");
    strarray_push(&arr, "-lgcc_eh");
    strarray_push(&arr, "-lc");
    strarray_push(&arr, "--end-group");
  }
  else 
  {
    strarray_push(&arr, "-lc");
    strarray_push(&arr, "-lgcc");
    strarray_push(&arr, "--as-needed");
    strarray_push(&arr, "-lgcc_s");
    //strarray_push(&arr, "--no-as-needed");
  }

  // Add the ending object file if not using -nostdlib
  if (!opt_nostdlib) {
    if (opt_shared)
      strarray_push(&arr, format("%s/crtendS.o", gcc_libpath));
    else if(!opt_fpie)
      strarray_push(&arr, format("%s/crtend.o", gcc_libpath));
  }

  strarray_push(&arr, format("%s/crtn.o", libpath));
  strarray_push(&arr, NULL);

  if (isDebug)
      print_string_array(&arr);    
  run_subprocess(arr.data);
}

static FileType get_file_type(char *filename)
{

  if (endswith(filename, ".a"))
    return FILE_AR;
  if (endswith(filename, ".so") || strstr(filename, ".so."))
    return FILE_DSO;
  if (endswith(filename, ".lo"))
    return FILE_DSO;
  if (endswith(filename, ".o"))
    return FILE_OBJ;
  if (endswith(filename, ".c"))
    return FILE_C;
  if (endswith(filename, ".s") || endswith(filename, ".S") ||
      endswith(filename, ".asm"))
    return FILE_ASM;
  if (endswith(filename, ".so.4"))
    return FILE_DSO;
  if (endswith(filename, ".rsp"))
    return FILE_RSP;

  if (opt_x != FILE_NONE)
    return opt_x;


  error("%s : %s:%d: error: in get_file_type <command line>: unknown file extension: %s", MAIN_C, __FILE__, __LINE__, filename);
}

int main(int argc, char **argv)
{

  int file_count = 0;
  // Enable core dumps and set up signal handlers
  enable_core_dump();
  setup_signal_handlers();

  atexit(cleanup);
  ctx = calloc(1, sizeof(Context));

  parse_args(argc, argv);

  // the parsing need to be done before trying to open the log file
  if ((isDebug && f == NULL) || (printTokens && f == NULL) || opt_A)
  {
    f = fopen(logFile, "w");
    if (f == NULL)
    {
      error("%s : %s:%d: error: in main Issue with -debug or -printparameter, file not opened!", MAIN_C, __FILE__, __LINE__);
      exit(1);
    }
  }

  // init_macros can call tokenize functions moving here to be able to print debug values
  init_macros();


  if (opt_cc1 && !isCc1input)
  {
    error("%s : %s:%d: error: in main with -cc1 parameter -cc1-input is mandatory!", MAIN_C, __FILE__, __LINE__);
    usage(-1);
  }

  if (opt_cc1)
  {
    add_default_include_paths(argv[0]);
    cc1();
    return 0;
  }

  //from @fuhsnn fix
  if (input_paths.len > 1 && opt_o && (opt_c || opt_S || opt_E))
    if (++file_count > 1)
    error("%s : %s:%d: error: in main cannot specify '-o' with '-c,' '-S' or '-E' with multiple files", MAIN_C, __FILE__, __LINE__);

  StringArray ld_args = {};

  for (int i = 0; i < input_paths.len; i++)
  {
    char *input = input_paths.data[i];

    if (!strncmp(input, "-l", 2))
    {
      strarray_push(&ld_args, input);
      continue;
    }

    if (!strncmp(input, "-Wl,", 4))
    {
      char *s = strdup(input + 4);
      char *arg = strtok(s, ",");
      while (arg)
      {
        strarray_push(&ld_args, arg);
        arg = strtok(NULL, ",");
      }
      continue;
    }

    char *output;
    if (opt_o)
      output = opt_o;
    else if (opt_S)
      output = replace_extn(input, ".s");
    else
      output = replace_extn(input, ".o");

    FileType type = get_file_type(input);

 
    // Handle .o or .a
    if (type == FILE_OBJ || type == FILE_AR || type == FILE_DSO)
    {
      strarray_push(&ld_args, input);
      continue;
    }

    // Handle .s, -S, .asm
    if (type == FILE_ASM)
    {
      if (!opt_S)
        assemble(input, output);
      continue;
    }

    if (type == FILE_RSP)
    {
      continue;
    }

    assert(type == FILE_C);

    // Just preprocess
    if (opt_E || opt_M)
    {
      run_cc1(argc, argv, input, NULL);
      continue;
    }

    // Compile
    if (opt_S)
    {
      run_cc1(argc, argv, input, output);
      continue;
    }

    if (opt_A) {
      run_cc1(argc, argv, input, NULL);
      continue;
    }
    // Compile and assemble
    if (opt_c)
    {
      char *tmp = create_tmpfile();
      run_cc1(argc, argv, input, tmp);
      assemble(tmp, output);
      continue;
    }

    // Compile, assemble and link
    char *tmp1 = create_tmpfile();
    char *tmp2 = create_tmpfile();
    run_cc1(argc, argv, input, tmp1);
    assemble(tmp1, tmp2);
    strarray_push(&ld_args, tmp2);
    continue;
  }

  if (ld_args.len > 0)
  {
    // if (symbolic_name)
    //   symbolic_link(symbolic_name, opt_o);  
    run_linker(&ld_args, opt_o ? opt_o : "a.out");
  }

  free(opt_MT);

  return 0;
}


bool startsWith(const char *restrict string, const char *restrict prefix)
{
    while(*prefix)
    {
        if(*prefix++ != *string++)
            return 0;
    }

    return 1;
}