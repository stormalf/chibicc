#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stddef.h>

#undef DEBUGASSERT
#if defined(DEBUGBUILD)
#define DEBUGASSERT(x) assert(x)
#else
#define DEBUGASSERT(x) do { } while(0)
#endif
#define BUFFSIZE 326 /* buffer for long-to-str and float-to-str calcs, should
                        fit negative DBL_MAX (317 letters) */
#define MAX_PARAMETERS 128 
/* conversion and display flags */
enum {
  FLAGS_NEW        = 0,
  FLAGS_SPACE      = 1<<0,
  FLAGS_SHOWSIGN   = 1<<1,
  FLAGS_LEFT       = 1<<2,
  FLAGS_ALT        = 1<<3,
  FLAGS_SHORT      = 1<<4,
  FLAGS_LONG       = 1<<5,
  FLAGS_LONGLONG   = 1<<6,
  FLAGS_LONGDOUBLE = 1<<7,
  FLAGS_PAD_NIL    = 1<<8,
  FLAGS_UNSIGNED   = 1<<9,
  FLAGS_OCTAL      = 1<<10,
  FLAGS_HEX        = 1<<11,
  FLAGS_UPPER      = 1<<12,
  FLAGS_WIDTH      = 1<<13, /* '*' or '*<num>$' used */
  FLAGS_WIDTHPARAM = 1<<14, /* width PARAMETER was specified */
  FLAGS_PREC       = 1<<15, /* precision was specified */
  FLAGS_PRECPARAM  = 1<<16, /* precision PARAMETER was specified */
  FLAGS_CHAR       = 1<<17, /* %c story */
  FLAGS_FLOATE     = 1<<18, /* %e or %E */
  FLAGS_FLOATG     = 1<<19  /* %g or %G */
};


/* Data type to read from the arglist */
typedef enum {
  FORMAT_UNKNOWN = 0,
  FORMAT_STRING,
  FORMAT_PTR,
  FORMAT_INT,
  FORMAT_INTPTR,
  FORMAT_LONG,
  FORMAT_LONGLONG,
  FORMAT_DOUBLE,
  FORMAT_LONGDOUBLE,
  FORMAT_WIDTH /* For internal use */
} FormatType;



typedef enum {
  CURLE_OK = 0,
  CURLE_UNSUPPORTED_PROTOCOL,    /* 1 */
  CURLE_FAILED_INIT,             /* 2 */
  CURLE_URL_MALFORMAT,           /* 3 */
  CURLE_NOT_BUILT_IN,            /* 4 - [was obsoleted in August 2007 for
                                    7.17.0, reused in April 2011 for 7.21.5] */
  CURLE_COULDNT_RESOLVE_PROXY,   /* 5 */
  CURLE_COULDNT_RESOLVE_HOST,    /* 6 */
  CURLE_COULDNT_CONNECT,         /* 7 */
  CURLE_WEIRD_SERVER_REPLY,      /* 8 */
  CURLE_REMOTE_ACCESS_DENIED,    /* 9 a service was denied by the server
                                    due to lack of access - when login fails
                                    this is not returned. */
  CURLE_FTP_ACCEPT_FAILED,       /* 10 - [was obsoleted in April 2006 for
                                    7.15.4, reused in Dec 2011 for 7.24.0]*/
  CURLE_FTP_WEIRD_PASS_REPLY,    /* 11 */
  CURLE_FTP_ACCEPT_TIMEOUT,      /* 12 - timeout occurred accepting server
                                    [was obsoleted in August 2007 for 7.17.0,
                                    reused in Dec 2011 for 7.24.0]*/
  CURLE_FTP_WEIRD_PASV_REPLY,    /* 13 */
  CURLE_FTP_WEIRD_227_FORMAT,    /* 14 */
  CURLE_FTP_CANT_GET_HOST,       /* 15 */
  CURLE_HTTP2,                   /* 16 - A problem in the http2 framing layer.
                                    [was obsoleted in August 2007 for 7.17.0,
                                    reused in July 2014 for 7.38.0] */
  CURLE_FTP_COULDNT_SET_TYPE,    /* 17 */
  CURLE_PARTIAL_FILE,            /* 18 */
  CURLE_FTP_COULDNT_RETR_FILE,   /* 19 */
  CURLE_OBSOLETE20,              /* 20 - NOT USED */
  CURLE_QUOTE_ERROR,             /* 21 - quote command failure */
  CURLE_HTTP_RETURNED_ERROR,     /* 22 */
  CURLE_WRITE_ERROR,             /* 23 */
  CURLE_OBSOLETE24,              /* 24 - NOT USED */
  CURLE_UPLOAD_FAILED,           /* 25 - failed upload "command" */
  CURLE_READ_ERROR,              /* 26 - couldn't open/read from file */
  CURLE_OUT_OF_MEMORY,           /* 27 */
  CURLE_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
  CURLE_OBSOLETE29,              /* 29 - NOT USED */
  CURLE_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
  CURLE_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
  CURLE_OBSOLETE32,              /* 32 - NOT USED */
  CURLE_RANGE_ERROR,             /* 33 - RANGE "command" didn't work */
  CURLE_HTTP_POST_ERROR,         /* 34 */
  CURLE_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
  CURLE_BAD_DOWNLOAD_RESUME,     /* 36 - couldn't resume download */
  CURLE_FILE_COULDNT_READ_FILE,  /* 37 */
  CURLE_LDAP_CANNOT_BIND,        /* 38 */
  CURLE_LDAP_SEARCH_FAILED,      /* 39 */
  CURLE_OBSOLETE40,              /* 40 - NOT USED */
  CURLE_FUNCTION_NOT_FOUND,      /* 41 - NOT USED starting with 7.53.0 */
  CURLE_ABORTED_BY_CALLBACK,     /* 42 */
  CURLE_BAD_FUNCTION_ARGUMENT,   /* 43 */
  CURLE_OBSOLETE44,              /* 44 - NOT USED */
  CURLE_INTERFACE_FAILED,        /* 45 - CURLOPT_INTERFACE failed */
  CURLE_OBSOLETE46,              /* 46 - NOT USED */
  CURLE_TOO_MANY_REDIRECTS,      /* 47 - catch endless re-direct loops */
  CURLE_UNKNOWN_OPTION,          /* 48 - User specified an unknown option */
  CURLE_SETOPT_OPTION_SYNTAX,    /* 49 - Malformed setopt option */
  CURLE_OBSOLETE50,              /* 50 - NOT USED */
  CURLE_OBSOLETE51,              /* 51 - NOT USED */
  CURLE_GOT_NOTHING,             /* 52 - when this is a specific error */
  CURLE_SSL_ENGINE_NOTFOUND,     /* 53 - SSL crypto engine not found */
  CURLE_SSL_ENGINE_SETFAILED,    /* 54 - can not set SSL crypto engine as
                                    default */
  CURLE_SEND_ERROR,              /* 55 - failed sending network data */
  CURLE_RECV_ERROR,              /* 56 - failure in receiving network data */
  CURLE_OBSOLETE57,              /* 57 - NOT IN USE */
  CURLE_SSL_CERTPROBLEM,         /* 58 - problem with the local certificate */
  CURLE_SSL_CIPHER,              /* 59 - couldn't use specified cipher */
  CURLE_PEER_FAILED_VERIFICATION, /* 60 - peer's certificate or fingerprint
                                     wasn't verified fine */
  CURLE_BAD_CONTENT_ENCODING,    /* 61 - Unrecognized/bad encoding */
  CURLE_OBSOLETE62,              /* 62 - NOT IN USE since 7.82.0 */
  CURLE_FILESIZE_EXCEEDED,       /* 63 - Maximum file size exceeded */
  CURLE_USE_SSL_FAILED,          /* 64 - Requested FTP SSL level failed */
  CURLE_SEND_FAIL_REWIND,        /* 65 - Sending the data requires a rewind
                                    that failed */
  CURLE_SSL_ENGINE_INITFAILED,   /* 66 - failed to initialise ENGINE */
  CURLE_LOGIN_DENIED,            /* 67 - user, password or similar was not
                                    accepted and we failed to login */
  CURLE_TFTP_NOTFOUND,           /* 68 - file not found on server */
  CURLE_TFTP_PERM,               /* 69 - permission problem on server */
  CURLE_REMOTE_DISK_FULL,        /* 70 - out of disk space on server */
  CURLE_TFTP_ILLEGAL,            /* 71 - Illegal TFTP operation */
  CURLE_TFTP_UNKNOWNID,          /* 72 - Unknown transfer ID */
  CURLE_REMOTE_FILE_EXISTS,      /* 73 - File already exists */
  CURLE_TFTP_NOSUCHUSER,         /* 74 - No such user */
  CURLE_OBSOLETE75,              /* 75 - NOT IN USE since 7.82.0 */
  CURLE_OBSOLETE76,              /* 76 - NOT IN USE since 7.82.0 */
  CURLE_SSL_CACERT_BADFILE,      /* 77 - could not load CACERT file, missing
                                    or wrong format */
  CURLE_REMOTE_FILE_NOT_FOUND,   /* 78 - remote file not found */
  CURLE_SSH,                     /* 79 - error from the SSH layer, somewhat
                                    generic so the error message will be of
                                    interest when this has happened */

  CURLE_SSL_SHUTDOWN_FAILED,     /* 80 - Failed to shut down the SSL
                                    connection */
  CURLE_AGAIN,                   /* 81 - socket is not ready for send/recv,
                                    wait till it's ready and try again (Added
                                    in 7.18.2) */
  CURLE_SSL_CRL_BADFILE,         /* 82 - could not load CRL file, missing or
                                    wrong format (Added in 7.19.0) */
  CURLE_SSL_ISSUER_ERROR,        /* 83 - Issuer check failed.  (Added in
                                    7.19.0) */
  CURLE_FTP_PRET_FAILED,         /* 84 - a PRET command failed */
  CURLE_RTSP_CSEQ_ERROR,         /* 85 - mismatch of RTSP CSeq numbers */
  CURLE_RTSP_SESSION_ERROR,      /* 86 - mismatch of RTSP Session Ids */
  CURLE_FTP_BAD_FILE_LIST,       /* 87 - unable to parse FTP file list */
  CURLE_CHUNK_FAILED,            /* 88 - chunk callback reported error */
  CURLE_NO_CONNECTION_AVAILABLE, /* 89 - No connection available, the
                                    session will be queued */
  CURLE_SSL_PINNEDPUBKEYNOTMATCH, /* 90 - specified pinned public key did not
                                     match */
  CURLE_SSL_INVALIDCERTSTATUS,   /* 91 - invalid certificate status */
  CURLE_HTTP2_STREAM,            /* 92 - stream error in HTTP/2 framing layer
                                    */
  CURLE_RECURSIVE_API_CALL,      /* 93 - an api function was called from
                                    inside a callback */
  CURLE_AUTH_ERROR,              /* 94 - an authentication function returned an
                                    error */
  CURLE_HTTP3,                   /* 95 - An HTTP/3 layer problem */
  CURLE_QUIC_CONNECT_ERROR,      /* 96 - QUIC connection error */
  CURLE_PROXY,                   /* 97 - proxy handshake error */
  CURLE_SSL_CLIENTCERT,          /* 98 - client-side certificate required */
  CURLE_UNRECOVERABLE_POLL,      /* 99 - poll/select returned fatal error */
  CURL_LAST /* never use! */
} CURLcode;


/* Type for length arguments in socket calls.  */
#ifndef __socklen_t_defined
typedef __socklen_t socklen_t;
# define __socklen_t_defined
#endif

#define TEST_ERR_MAJOR_BAD     (CURLcode) 126
#define TEST_ERR_RUNS_FOREVER  (CURLcode) 125
#define TEST_ERR_EASY_INIT     (CURLcode) 124
#define TEST_ERR_MULTI         (CURLcode) 123
#define TEST_ERR_NUM_HANDLES   (CURLcode) 122
#define TEST_ERR_SELECT        (CURLcode) 121
#define TEST_ERR_SUCCESS       (CURLcode) 120
#define TEST_ERR_FAILURE       (CURLcode) 119
#define TEST_ERR_USAGE         (CURLcode) 118
#define TEST_ERR_FOPEN         (CURLcode) 117
#define TEST_ERR_FSTAT         (CURLcode) 116
#define TEST_ERR_BAD_TIMEOUT   (CURLcode) 115



#define SIZEOF_CURL_OFF_T 8
#    define CURL_TYPEOF_CURL_OFF_T     long
#    define CURL_FORMAT_CURL_OFF_T     "ld"
#    define CURL_FORMAT_CURL_OFF_TU    "lu"
#    define CURL_SUFFIX_CURL_OFF_T     L
#    define CURL_SUFFIX_CURL_OFF_TU    UL

#  define CURL_TYPEOF_CURL_SOCKLEN_T socklen_t
#  define CURL_PULL_SYS_TYPES_H      1
#  define CURL_PULL_SYS_SOCKET_H     1


#ifdef CURL_TYPEOF_CURL_OFF_T
  typedef CURL_TYPEOF_CURL_OFF_T curl_off_t;
#endif


#if (SIZEOF_CURL_OFF_T > SIZEOF_LONG)
#  define MPRNT_SUFFIX_CURL_OFF_T  LL
#else
#  define MPRNT_SUFFIX_CURL_OFF_T  L
#endif

#if defined(__STDC__) || defined(_MSC_VER) || defined(__cplusplus) || \
  defined(__HP_aCC) || defined(__BORLANDC__) || defined(__LCC__) || \
  defined(__POCC__) || defined(__SALFORDC__) || defined(__HIGHC__) || \
  defined(__ILEC400__)
  /* This compiler is believed to have an ISO compatible preprocessor */
#define CURL_ISOCPP
#else
  /* This compiler is believed NOT to have an ISO compatible preprocessor */
#undef CURL_ISOCPP
#endif



#ifdef CURL_ISOCPP
#  define MPRNT_OFF_T_C_HELPER2(Val,Suffix) Val ## Suffix
#else
#  define MPRNT_OFF_T_C_HELPER2(Val,Suffix) Val/**/Suffix
#endif
#define MPRNT_OFF_T_C_HELPER1(Val,Suffix) MPRNT_OFF_T_C_HELPER2(Val,Suffix)
#define MPRNT_OFF_T_C(Val)  MPRNT_OFF_T_C_HELPER1(Val,MPRNT_SUFFIX_CURL_OFF_T)


#define BUFSZ    256
#define USHORT_TESTS_ARRSZ 1 + 100
#define SSHORT_TESTS_ARRSZ 1 + 100
#define UINT_TESTS_ARRSZ   1 + 100
#define SINT_TESTS_ARRSZ   1 + 100
#define ULONG_TESTS_ARRSZ  1 + 100
#define SLONG_TESTS_ARRSZ  1 + 100
#define COFFT_TESTS_ARRSZ  1 + 100

#ifdef HAVE_LONG_LONG_TYPE
#  define mp_intmax_t LONG_LONG_TYPE
#  define mp_uintmax_t unsigned LONG_LONG_TYPE
#else
#  define mp_intmax_t long
#  define mp_uintmax_t unsigned long
#endif


struct nsprintf {
  char *buffer;
  size_t length;
  size_t max;
};

/* Lower-case digits.  */
static const char lower_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

/* Upper-case digits.  */
static const char upper_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";




struct unsshort_st {
  unsigned short num;   /* unsigned short  */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


struct sigshort_st {
  short num;            /* signed short    */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


struct unsint_st {
  unsigned int num;     /* unsigned int    */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


struct sigint_st {
  int num;              /* signed int      */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


struct unslong_st {
  unsigned long num;    /* unsigned long   */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


struct siglong_st {
  long num;             /* signed long     */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


struct curloff_st {
  curl_off_t num;       /* curl_off_t      */
  const char *expected; /* expected string */
  char result[BUFSZ];   /* result string   */
};


static struct unsshort_st us_test[USHORT_TESTS_ARRSZ];
static struct sigshort_st ss_test[SSHORT_TESTS_ARRSZ];
static struct unsint_st   ui_test[UINT_TESTS_ARRSZ];
static struct sigint_st   si_test[SINT_TESTS_ARRSZ];
static struct unslong_st  ul_test[ULONG_TESTS_ARRSZ];
static struct siglong_st  sl_test[SLONG_TESTS_ARRSZ];
static struct curloff_st  co_test[COFFT_TESTS_ARRSZ];






static int test_unsigned_short_formatting(void)
{
  int i, j;
  int num_ushort_tests = 0;
  int failed = 0;

  i = 1; us_test[i].num = 0xFFFFU; us_test[i].expected = "65535";
  i++; us_test[i].num = 0xFF00U; us_test[i].expected = "65280";
  i++; us_test[i].num = 0x00FFU; us_test[i].expected = "255";

  i++; us_test[i].num = 0xF000U; us_test[i].expected = "61440";
  i++; us_test[i].num = 0x0F00U; us_test[i].expected = "3840";
  i++; us_test[i].num = 0x00F0U; us_test[i].expected = "240";
  i++; us_test[i].num = 0x000FU; us_test[i].expected = "15";

  i++; us_test[i].num = 0xC000U; us_test[i].expected = "49152";
  i++; us_test[i].num = 0x0C00U; us_test[i].expected = "3072";
  i++; us_test[i].num = 0x00C0U; us_test[i].expected = "192";
  i++; us_test[i].num = 0x000CU; us_test[i].expected = "12";

  i++; us_test[i].num = 0x0001U; us_test[i].expected = "1";
  i++; us_test[i].num = 0x0000U; us_test[i].expected = "0";

  num_ushort_tests = i;

  return failed;
}


static int test_signed_short_formatting(void)
{
  int i, j;
  int num_sshort_tests = 0;
  int failed = 0;

  i = 1; ss_test[i].num = 0x7FFF; ss_test[i].expected = "32767";
  i++; ss_test[i].num = 0x7FFE; ss_test[i].expected = "32766";
  i++; ss_test[i].num = 0x7FFD; ss_test[i].expected = "32765";
  i++; ss_test[i].num = 0x7F00; ss_test[i].expected = "32512";
  i++; ss_test[i].num = 0x07F0; ss_test[i].expected = "2032";
  i++; ss_test[i].num = 0x007F; ss_test[i].expected = "127";

  i++; ss_test[i].num = 0x7000; ss_test[i].expected = "28672";
  i++; ss_test[i].num = 0x0700; ss_test[i].expected = "1792";
  i++; ss_test[i].num = 0x0070; ss_test[i].expected = "112";
  i++; ss_test[i].num = 0x0007; ss_test[i].expected = "7";

  i++; ss_test[i].num = 0x5000; ss_test[i].expected = "20480";
  i++; ss_test[i].num = 0x0500; ss_test[i].expected = "1280";
  i++; ss_test[i].num = 0x0050; ss_test[i].expected = "80";
  i++; ss_test[i].num = 0x0005; ss_test[i].expected = "5";

  i++; ss_test[i].num = 0x0001; ss_test[i].expected = "1";
  i++; ss_test[i].num = 0x0000; ss_test[i].expected = "0";

  i++; ss_test[i].num = -0x7FFF -1; ss_test[i].expected = "-32768";
  i++; ss_test[i].num = -0x7FFE -1; ss_test[i].expected = "-32767";
  i++; ss_test[i].num = -0x7FFD -1; ss_test[i].expected = "-32766";
  i++; ss_test[i].num = -0x7F00 -1; ss_test[i].expected = "-32513";
  i++; ss_test[i].num = -0x07F0 -1; ss_test[i].expected = "-2033";
  i++; ss_test[i].num = -0x007F -1; ss_test[i].expected = "-128";

  i++; ss_test[i].num = -0x7000 -1; ss_test[i].expected = "-28673";
  i++; ss_test[i].num = -0x0700 -1; ss_test[i].expected = "-1793";
  i++; ss_test[i].num = -0x0070 -1; ss_test[i].expected = "-113";
  i++; ss_test[i].num = -0x0007 -1; ss_test[i].expected = "-8";

  i++; ss_test[i].num = -0x5000 -1; ss_test[i].expected = "-20481";
  i++; ss_test[i].num = -0x0500 -1; ss_test[i].expected = "-1281";
  i++; ss_test[i].num = -0x0050 -1; ss_test[i].expected = "-81";
  i++; ss_test[i].num = -0x0005 -1; ss_test[i].expected = "-6";

  i++; ss_test[i].num =  0x0000 -1; ss_test[i].expected = "-1";

  num_sshort_tests = i;

  return failed;
}


static int test_unsigned_int_formatting(void)
{
  int i, j;
  int num_uint_tests = 0;
  int failed = 0;

#if (SIZEOF_INT == 2)

  i = 1; ui_test[i].num = 0xFFFFU; ui_test[i].expected = "65535";
  i++; ui_test[i].num = 0xFF00U; ui_test[i].expected = "65280";
  i++; ui_test[i].num = 0x00FFU; ui_test[i].expected = "255";

  i++; ui_test[i].num = 0xF000U; ui_test[i].expected = "61440";
  i++; ui_test[i].num = 0x0F00U; ui_test[i].expected = "3840";
  i++; ui_test[i].num = 0x00F0U; ui_test[i].expected = "240";
  i++; ui_test[i].num = 0x000FU; ui_test[i].expected = "15";

  i++; ui_test[i].num = 0xC000U; ui_test[i].expected = "49152";
  i++; ui_test[i].num = 0x0C00U; ui_test[i].expected = "3072";
  i++; ui_test[i].num = 0x00C0U; ui_test[i].expected = "192";
  i++; ui_test[i].num = 0x000CU; ui_test[i].expected = "12";

  i++; ui_test[i].num = 0x0001U; ui_test[i].expected = "1";
  i++; ui_test[i].num = 0x0000U; ui_test[i].expected = "0";

  num_uint_tests = i;

#elif (SIZEOF_INT == 4)

  i = 1; ui_test[i].num = 0xFFFFFFFFU; ui_test[i].expected = "4294967295";
  i++; ui_test[i].num = 0xFFFF0000U; ui_test[i].expected = "4294901760";
  i++; ui_test[i].num = 0x0000FFFFU; ui_test[i].expected = "65535";

  i++; ui_test[i].num = 0xFF000000U; ui_test[i].expected = "4278190080";
  i++; ui_test[i].num = 0x00FF0000U; ui_test[i].expected = "16711680";
  i++; ui_test[i].num = 0x0000FF00U; ui_test[i].expected = "65280";
  i++; ui_test[i].num = 0x000000FFU; ui_test[i].expected = "255";

  i++; ui_test[i].num = 0xF0000000U; ui_test[i].expected = "4026531840";
  i++; ui_test[i].num = 0x0F000000U; ui_test[i].expected = "251658240";
  i++; ui_test[i].num = 0x00F00000U; ui_test[i].expected = "15728640";
  i++; ui_test[i].num = 0x000F0000U; ui_test[i].expected = "983040";
  i++; ui_test[i].num = 0x0000F000U; ui_test[i].expected = "61440";
  i++; ui_test[i].num = 0x00000F00U; ui_test[i].expected = "3840";
  i++; ui_test[i].num = 0x000000F0U; ui_test[i].expected = "240";
  i++; ui_test[i].num = 0x0000000FU; ui_test[i].expected = "15";

  i++; ui_test[i].num = 0xC0000000U; ui_test[i].expected = "3221225472";
  i++; ui_test[i].num = 0x0C000000U; ui_test[i].expected = "201326592";
  i++; ui_test[i].num = 0x00C00000U; ui_test[i].expected = "12582912";
  i++; ui_test[i].num = 0x000C0000U; ui_test[i].expected = "786432";
  i++; ui_test[i].num = 0x0000C000U; ui_test[i].expected = "49152";
  i++; ui_test[i].num = 0x00000C00U; ui_test[i].expected = "3072";
  i++; ui_test[i].num = 0x000000C0U; ui_test[i].expected = "192";
  i++; ui_test[i].num = 0x0000000CU; ui_test[i].expected = "12";

  i++; ui_test[i].num = 0x00000001U; ui_test[i].expected = "1";
  i++; ui_test[i].num = 0x00000000U; ui_test[i].expected = "0";

  num_uint_tests = i;

#elif (SIZEOF_INT == 8)

  /* !checksrc! disable LONGLINE all */
  i = 1; ui_test[i].num = 0xFFFFFFFFFFFFFFFFU; ui_test[i].expected = "18446744073709551615";
  i++; ui_test[i].num = 0xFFFFFFFF00000000U; ui_test[i].expected = "18446744069414584320";
  i++; ui_test[i].num = 0x00000000FFFFFFFFU; ui_test[i].expected = "4294967295";

  i++; ui_test[i].num = 0xFFFF000000000000U; ui_test[i].expected = "18446462598732840960";
  i++; ui_test[i].num = 0x0000FFFF00000000U; ui_test[i].expected = "281470681743360";
  i++; ui_test[i].num = 0x00000000FFFF0000U; ui_test[i].expected = "4294901760";
  i++; ui_test[i].num = 0x000000000000FFFFU; ui_test[i].expected = "65535";

  i++; ui_test[i].num = 0xFF00000000000000U; ui_test[i].expected = "18374686479671623680";
  i++; ui_test[i].num = 0x00FF000000000000U; ui_test[i].expected = "71776119061217280";
  i++; ui_test[i].num = 0x0000FF0000000000U; ui_test[i].expected = "280375465082880";
  i++; ui_test[i].num = 0x000000FF00000000U; ui_test[i].expected = "1095216660480";
  i++; ui_test[i].num = 0x00000000FF000000U; ui_test[i].expected = "4278190080";
  i++; ui_test[i].num = 0x0000000000FF0000U; ui_test[i].expected = "16711680";
  i++; ui_test[i].num = 0x000000000000FF00U; ui_test[i].expected = "65280";
  i++; ui_test[i].num = 0x00000000000000FFU; ui_test[i].expected = "255";

  i++; ui_test[i].num = 0xF000000000000000U; ui_test[i].expected = "17293822569102704640";
  i++; ui_test[i].num = 0x0F00000000000000U; ui_test[i].expected = "1080863910568919040";
  i++; ui_test[i].num = 0x00F0000000000000U; ui_test[i].expected = "67553994410557440";
  i++; ui_test[i].num = 0x000F000000000000U; ui_test[i].expected = "4222124650659840";
  i++; ui_test[i].num = 0x0000F00000000000U; ui_test[i].expected = "263882790666240";
  i++; ui_test[i].num = 0x00000F0000000000U; ui_test[i].expected = "16492674416640";
  i++; ui_test[i].num = 0x000000F000000000U; ui_test[i].expected = "1030792151040";
  i++; ui_test[i].num = 0x0000000F00000000U; ui_test[i].expected = "64424509440";
  i++; ui_test[i].num = 0x00000000F0000000U; ui_test[i].expected = "4026531840";
  i++; ui_test[i].num = 0x000000000F000000U; ui_test[i].expected = "251658240";
  i++; ui_test[i].num = 0x0000000000F00000U; ui_test[i].expected = "15728640";
  i++; ui_test[i].num = 0x00000000000F0000U; ui_test[i].expected = "983040";
  i++; ui_test[i].num = 0x000000000000F000U; ui_test[i].expected = "61440";
  i++; ui_test[i].num = 0x0000000000000F00U; ui_test[i].expected = "3840";
  i++; ui_test[i].num = 0x00000000000000F0U; ui_test[i].expected = "240";
  i++; ui_test[i].num = 0x000000000000000FU; ui_test[i].expected = "15";

  i++; ui_test[i].num = 0xC000000000000000U; ui_test[i].expected = "13835058055282163712";
  i++; ui_test[i].num = 0x0C00000000000000U; ui_test[i].expected = "864691128455135232";
  i++; ui_test[i].num = 0x00C0000000000000U; ui_test[i].expected = "54043195528445952";
  i++; ui_test[i].num = 0x000C000000000000U; ui_test[i].expected = "3377699720527872";
  i++; ui_test[i].num = 0x0000C00000000000U; ui_test[i].expected = "211106232532992";
  i++; ui_test[i].num = 0x00000C0000000000U; ui_test[i].expected = "13194139533312";
  i++; ui_test[i].num = 0x000000C000000000U; ui_test[i].expected = "824633720832";
  i++; ui_test[i].num = 0x0000000C00000000U; ui_test[i].expected = "51539607552";
  i++; ui_test[i].num = 0x00000000C0000000U; ui_test[i].expected = "3221225472";
  i++; ui_test[i].num = 0x000000000C000000U; ui_test[i].expected = "201326592";
  i++; ui_test[i].num = 0x0000000000C00000U; ui_test[i].expected = "12582912";
  i++; ui_test[i].num = 0x00000000000C0000U; ui_test[i].expected = "786432";
  i++; ui_test[i].num = 0x000000000000C000U; ui_test[i].expected = "49152";
  i++; ui_test[i].num = 0x0000000000000C00U; ui_test[i].expected = "3072";
  i++; ui_test[i].num = 0x00000000000000C0U; ui_test[i].expected = "192";
  i++; ui_test[i].num = 0x000000000000000CU; ui_test[i].expected = "12";

  i++; ui_test[i].num = 0x00000001U; ui_test[i].expected = "1";
  i++; ui_test[i].num = 0x00000000U; ui_test[i].expected = "0";

  num_uint_tests = i;

#endif


  return failed;
}


static int test_signed_int_formatting(void)
{
  int i, j;
  int num_sint_tests = 0;
  int failed = 0;

#if (SIZEOF_INT == 2)

  i = 1; si_test[i].num = 0x7FFF; si_test[i].expected = "32767";
  i++; si_test[i].num = 0x7FFE; si_test[i].expected = "32766";
  i++; si_test[i].num = 0x7FFD; si_test[i].expected = "32765";
  i++; si_test[i].num = 0x7F00; si_test[i].expected = "32512";
  i++; si_test[i].num = 0x07F0; si_test[i].expected = "2032";
  i++; si_test[i].num = 0x007F; si_test[i].expected = "127";

  i++; si_test[i].num = 0x7000; si_test[i].expected = "28672";
  i++; si_test[i].num = 0x0700; si_test[i].expected = "1792";
  i++; si_test[i].num = 0x0070; si_test[i].expected = "112";
  i++; si_test[i].num = 0x0007; si_test[i].expected = "7";

  i++; si_test[i].num = 0x5000; si_test[i].expected = "20480";
  i++; si_test[i].num = 0x0500; si_test[i].expected = "1280";
  i++; si_test[i].num = 0x0050; si_test[i].expected = "80";
  i++; si_test[i].num = 0x0005; si_test[i].expected = "5";

  i++; si_test[i].num = 0x0001; si_test[i].expected = "1";
  i++; si_test[i].num = 0x0000; si_test[i].expected = "0";

  i++; si_test[i].num = -0x7FFF -1; si_test[i].expected = "-32768";
  i++; si_test[i].num = -0x7FFE -1; si_test[i].expected = "-32767";
  i++; si_test[i].num = -0x7FFD -1; si_test[i].expected = "-32766";
  i++; si_test[i].num = -0x7F00 -1; si_test[i].expected = "-32513";
  i++; si_test[i].num = -0x07F0 -1; si_test[i].expected = "-2033";
  i++; si_test[i].num = -0x007F -1; si_test[i].expected = "-128";

  i++; si_test[i].num = -0x7000 -1; si_test[i].expected = "-28673";
  i++; si_test[i].num = -0x0700 -1; si_test[i].expected = "-1793";
  i++; si_test[i].num = -0x0070 -1; si_test[i].expected = "-113";
  i++; si_test[i].num = -0x0007 -1; si_test[i].expected = "-8";

  i++; si_test[i].num = -0x5000 -1; si_test[i].expected = "-20481";
  i++; si_test[i].num = -0x0500 -1; si_test[i].expected = "-1281";
  i++; si_test[i].num = -0x0050 -1; si_test[i].expected = "-81";
  i++; si_test[i].num = -0x0005 -1; si_test[i].expected = "-6";

  i++; si_test[i].num =  0x0000 -1; si_test[i].expected = "-1";

  num_sint_tests = i;

#elif (SIZEOF_INT == 4)

  i = 1; si_test[i].num = 0x7FFFFFFF; si_test[i].expected = "2147483647";
  i++; si_test[i].num = 0x7FFFFFFE; si_test[i].expected = "2147483646";
  i++; si_test[i].num = 0x7FFFFFFD; si_test[i].expected = "2147483645";
  i++; si_test[i].num = 0x7FFF0000; si_test[i].expected = "2147418112";
  i++; si_test[i].num = 0x00007FFF; si_test[i].expected = "32767";

  i++; si_test[i].num = 0x7F000000; si_test[i].expected = "2130706432";
  i++; si_test[i].num = 0x007F0000; si_test[i].expected = "8323072";
  i++; si_test[i].num = 0x00007F00; si_test[i].expected = "32512";
  i++; si_test[i].num = 0x0000007F; si_test[i].expected = "127";

  i++; si_test[i].num = 0x70000000; si_test[i].expected = "1879048192";
  i++; si_test[i].num = 0x07000000; si_test[i].expected = "117440512";
  i++; si_test[i].num = 0x00700000; si_test[i].expected = "7340032";
  i++; si_test[i].num = 0x00070000; si_test[i].expected = "458752";
  i++; si_test[i].num = 0x00007000; si_test[i].expected = "28672";
  i++; si_test[i].num = 0x00000700; si_test[i].expected = "1792";
  i++; si_test[i].num = 0x00000070; si_test[i].expected = "112";
  i++; si_test[i].num = 0x00000007; si_test[i].expected = "7";

  i++; si_test[i].num = 0x50000000; si_test[i].expected = "1342177280";
  i++; si_test[i].num = 0x05000000; si_test[i].expected = "83886080";
  i++; si_test[i].num = 0x00500000; si_test[i].expected = "5242880";
  i++; si_test[i].num = 0x00050000; si_test[i].expected = "327680";
  i++; si_test[i].num = 0x00005000; si_test[i].expected = "20480";
  i++; si_test[i].num = 0x00000500; si_test[i].expected = "1280";
  i++; si_test[i].num = 0x00000050; si_test[i].expected = "80";
  i++; si_test[i].num = 0x00000005; si_test[i].expected = "5";

  i++; si_test[i].num = 0x00000001; si_test[i].expected = "1";
  i++; si_test[i].num = 0x00000000; si_test[i].expected = "0";

  i++; si_test[i].num = -0x7FFFFFFF -1; si_test[i].expected = "-2147483648";
  i++; si_test[i].num = -0x7FFFFFFE -1; si_test[i].expected = "-2147483647";
  i++; si_test[i].num = -0x7FFFFFFD -1; si_test[i].expected = "-2147483646";
  i++; si_test[i].num = -0x7FFF0000 -1; si_test[i].expected = "-2147418113";
  i++; si_test[i].num = -0x00007FFF -1; si_test[i].expected = "-32768";

  i++; si_test[i].num = -0x7F000000 -1; si_test[i].expected = "-2130706433";
  i++; si_test[i].num = -0x007F0000 -1; si_test[i].expected = "-8323073";
  i++; si_test[i].num = -0x00007F00 -1; si_test[i].expected = "-32513";
  i++; si_test[i].num = -0x0000007F -1; si_test[i].expected = "-128";

  i++; si_test[i].num = -0x70000000 -1; si_test[i].expected = "-1879048193";
  i++; si_test[i].num = -0x07000000 -1; si_test[i].expected = "-117440513";
  i++; si_test[i].num = -0x00700000 -1; si_test[i].expected = "-7340033";
  i++; si_test[i].num = -0x00070000 -1; si_test[i].expected = "-458753";
  i++; si_test[i].num = -0x00007000 -1; si_test[i].expected = "-28673";
  i++; si_test[i].num = -0x00000700 -1; si_test[i].expected = "-1793";
  i++; si_test[i].num = -0x00000070 -1; si_test[i].expected = "-113";
  i++; si_test[i].num = -0x00000007 -1; si_test[i].expected = "-8";

  i++; si_test[i].num = -0x50000000 -1; si_test[i].expected = "-1342177281";
  i++; si_test[i].num = -0x05000000 -1; si_test[i].expected = "-83886081";
  i++; si_test[i].num = -0x00500000 -1; si_test[i].expected = "-5242881";
  i++; si_test[i].num = -0x00050000 -1; si_test[i].expected = "-327681";
  i++; si_test[i].num = -0x00005000 -1; si_test[i].expected = "-20481";
  i++; si_test[i].num = -0x00000500 -1; si_test[i].expected = "-1281";
  i++; si_test[i].num = -0x00000050 -1; si_test[i].expected = "-81";
  i++; si_test[i].num = -0x00000005 -1; si_test[i].expected = "-6";

  i++; si_test[i].num =  0x00000000 -1; si_test[i].expected = "-1";

  num_sint_tests = i;

#elif (SIZEOF_INT == 8)

  i = 1; si_test[i].num = 0x7FFFFFFFFFFFFFFF; si_test[i].expected = "9223372036854775807";
  i++; si_test[i].num = 0x7FFFFFFFFFFFFFFE; si_test[i].expected = "9223372036854775806";
  i++; si_test[i].num = 0x7FFFFFFFFFFFFFFD; si_test[i].expected = "9223372036854775805";
  i++; si_test[i].num = 0x7FFFFFFF00000000; si_test[i].expected = "9223372032559808512";
  i++; si_test[i].num = 0x000000007FFFFFFF; si_test[i].expected = "2147483647";

  i++; si_test[i].num = 0x7FFF000000000000; si_test[i].expected = "9223090561878065152";
  i++; si_test[i].num = 0x00007FFF00000000; si_test[i].expected = "140733193388032";
  i++; si_test[i].num = 0x000000007FFF0000; si_test[i].expected = "2147418112";
  i++; si_test[i].num = 0x0000000000007FFF; si_test[i].expected = "32767";

  i++; si_test[i].num = 0x7F00000000000000; si_test[i].expected = "9151314442816847872";
  i++; si_test[i].num = 0x007F000000000000; si_test[i].expected = "35747322042253312";
  i++; si_test[i].num = 0x00007F0000000000; si_test[i].expected = "139637976727552";
  i++; si_test[i].num = 0x0000007F00000000; si_test[i].expected = "545460846592";
  i++; si_test[i].num = 0x000000007F000000; si_test[i].expected = "2130706432";
  i++; si_test[i].num = 0x00000000007F0000; si_test[i].expected = "8323072";
  i++; si_test[i].num = 0x0000000000007F00; si_test[i].expected = "32512";
  i++; si_test[i].num = 0x000000000000007F; si_test[i].expected = "127";

  i++; si_test[i].num = 0x7000000000000000; si_test[i].expected = "8070450532247928832";
  i++; si_test[i].num = 0x0700000000000000; si_test[i].expected = "504403158265495552";
  i++; si_test[i].num = 0x0070000000000000; si_test[i].expected = "31525197391593472";
  i++; si_test[i].num = 0x0007000000000000; si_test[i].expected = "1970324836974592";
  i++; si_test[i].num = 0x0000700000000000; si_test[i].expected = "123145302310912";
  i++; si_test[i].num = 0x0000070000000000; si_test[i].expected = "7696581394432";
  i++; si_test[i].num = 0x0000007000000000; si_test[i].expected = "481036337152";
  i++; si_test[i].num = 0x0000000700000000; si_test[i].expected = "30064771072";
  i++; si_test[i].num = 0x0000000070000000; si_test[i].expected = "1879048192";
  i++; si_test[i].num = 0x0000000007000000; si_test[i].expected = "117440512";
  i++; si_test[i].num = 0x0000000000700000; si_test[i].expected = "7340032";
  i++; si_test[i].num = 0x0000000000070000; si_test[i].expected = "458752";
  i++; si_test[i].num = 0x0000000000007000; si_test[i].expected = "28672";
  i++; si_test[i].num = 0x0000000000000700; si_test[i].expected = "1792";
  i++; si_test[i].num = 0x0000000000000070; si_test[i].expected = "112";
  i++; si_test[i].num = 0x0000000000000007; si_test[i].expected = "7";

  i++; si_test[i].num = 0x0000000000000001; si_test[i].expected = "1";
  i++; si_test[i].num = 0x0000000000000000; si_test[i].expected = "0";

  i++; si_test[i].num = -0x7FFFFFFFFFFFFFFF -1; si_test[i].expected = "-9223372036854775808";
  i++; si_test[i].num = -0x7FFFFFFFFFFFFFFE -1; si_test[i].expected = "-9223372036854775807";
  i++; si_test[i].num = -0x7FFFFFFFFFFFFFFD -1; si_test[i].expected = "-9223372036854775806";
  i++; si_test[i].num = -0x7FFFFFFF00000000 -1; si_test[i].expected = "-9223372032559808513";
  i++; si_test[i].num = -0x000000007FFFFFFF -1; si_test[i].expected = "-2147483648";

  i++; si_test[i].num = -0x7FFF000000000000 -1; si_test[i].expected = "-9223090561878065153";
  i++; si_test[i].num = -0x00007FFF00000000 -1; si_test[i].expected = "-140733193388033";
  i++; si_test[i].num = -0x000000007FFF0000 -1; si_test[i].expected = "-2147418113";
  i++; si_test[i].num = -0x0000000000007FFF -1; si_test[i].expected = "-32768";

  i++; si_test[i].num = -0x7F00000000000000 -1; si_test[i].expected = "-9151314442816847873";
  i++; si_test[i].num = -0x007F000000000000 -1; si_test[i].expected = "-35747322042253313";
  i++; si_test[i].num = -0x00007F0000000000 -1; si_test[i].expected = "-139637976727553";
  i++; si_test[i].num = -0x0000007F00000000 -1; si_test[i].expected = "-545460846593";
  i++; si_test[i].num = -0x000000007F000000 -1; si_test[i].expected = "-2130706433";
  i++; si_test[i].num = -0x00000000007F0000 -1; si_test[i].expected = "-8323073";
  i++; si_test[i].num = -0x0000000000007F00 -1; si_test[i].expected = "-32513";
  i++; si_test[i].num = -0x000000000000007F -1; si_test[i].expected = "-128";

  i++; si_test[i].num = -0x7000000000000000 -1; si_test[i].expected = "-8070450532247928833";
  i++; si_test[i].num = -0x0700000000000000 -1; si_test[i].expected = "-504403158265495553";
  i++; si_test[i].num = -0x0070000000000000 -1; si_test[i].expected = "-31525197391593473";
  i++; si_test[i].num = -0x0007000000000000 -1; si_test[i].expected = "-1970324836974593";
  i++; si_test[i].num = -0x0000700000000000 -1; si_test[i].expected = "-123145302310913";
  i++; si_test[i].num = -0x0000070000000000 -1; si_test[i].expected = "-7696581394433";
  i++; si_test[i].num = -0x0000007000000000 -1; si_test[i].expected = "-481036337153";
  i++; si_test[i].num = -0x0000000700000000 -1; si_test[i].expected = "-30064771073";
  i++; si_test[i].num = -0x0000000070000000 -1; si_test[i].expected = "-1879048193";
  i++; si_test[i].num = -0x0000000007000000 -1; si_test[i].expected = "-117440513";
  i++; si_test[i].num = -0x0000000000700000 -1; si_test[i].expected = "-7340033";
  i++; si_test[i].num = -0x0000000000070000 -1; si_test[i].expected = "-458753";
  i++; si_test[i].num = -0x0000000000007000 -1; si_test[i].expected = "-28673";
  i++; si_test[i].num = -0x0000000000000700 -1; si_test[i].expected = "-1793";
  i++; si_test[i].num = -0x0000000000000070 -1; si_test[i].expected = "-113";
  i++; si_test[i].num = -0x0000000000000007 -1; si_test[i].expected = "-8";

  i++; si_test[i].num =  0x0000000000000000 -1; si_test[i].expected = "-1";

  num_sint_tests = i;

#endif

 
  return failed;
}


static int test_unsigned_long_formatting(void)
{
  int i, j;
  int num_ulong_tests = 0;
  int failed = 0;

#if (SIZEOF_LONG == 2)

  i = 1; ul_test[i].num = 0xFFFFUL; ul_test[i].expected = "65535";
  i++; ul_test[i].num = 0xFF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x00FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x0F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x00F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x0C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x00C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x0001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x0000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#elif (SIZEOF_LONG == 4)

  i = 1; ul_test[i].num = 0xFFFFFFFFUL; ul_test[i].expected = "4294967295";
  i++; ul_test[i].num = 0xFFFF0000UL; ul_test[i].expected = "4294901760";
  i++; ul_test[i].num = 0x0000FFFFUL; ul_test[i].expected = "65535";

  i++; ul_test[i].num = 0xFF000000UL; ul_test[i].expected = "4278190080";
  i++; ul_test[i].num = 0x00FF0000UL; ul_test[i].expected = "16711680";
  i++; ul_test[i].num = 0x0000FF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x000000FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF0000000UL; ul_test[i].expected = "4026531840";
  i++; ul_test[i].num = 0x0F000000UL; ul_test[i].expected = "251658240";
  i++; ul_test[i].num = 0x00F00000UL; ul_test[i].expected = "15728640";
  i++; ul_test[i].num = 0x000F0000UL; ul_test[i].expected = "983040";
  i++; ul_test[i].num = 0x0000F000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x00000F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x000000F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x0000000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC0000000UL; ul_test[i].expected = "3221225472";
  i++; ul_test[i].num = 0x0C000000UL; ul_test[i].expected = "201326592";
  i++; ul_test[i].num = 0x00C00000UL; ul_test[i].expected = "12582912";
  i++; ul_test[i].num = 0x000C0000UL; ul_test[i].expected = "786432";
  i++; ul_test[i].num = 0x0000C000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x00000C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x000000C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x0000000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x00000001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x00000000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#elif (SIZEOF_LONG == 8)

  i = 1; ul_test[i].num = 0xFFFFFFFFFFFFFFFFUL; ul_test[i].expected = "18446744073709551615";
  i++; ul_test[i].num = 0xFFFFFFFF00000000UL; ul_test[i].expected = "18446744069414584320";
  i++; ul_test[i].num = 0x00000000FFFFFFFFUL; ul_test[i].expected = "4294967295";

  i++; ul_test[i].num = 0xFFFF000000000000UL; ul_test[i].expected = "18446462598732840960";
  i++; ul_test[i].num = 0x0000FFFF00000000UL; ul_test[i].expected = "281470681743360";
  i++; ul_test[i].num = 0x00000000FFFF0000UL; ul_test[i].expected = "4294901760";
  i++; ul_test[i].num = 0x000000000000FFFFUL; ul_test[i].expected = "65535";

  i++; ul_test[i].num = 0xFF00000000000000UL; ul_test[i].expected = "18374686479671623680";
  i++; ul_test[i].num = 0x00FF000000000000UL; ul_test[i].expected = "71776119061217280";
  i++; ul_test[i].num = 0x0000FF0000000000UL; ul_test[i].expected = "280375465082880";
  i++; ul_test[i].num = 0x000000FF00000000UL; ul_test[i].expected = "1095216660480";
  i++; ul_test[i].num = 0x00000000FF000000UL; ul_test[i].expected = "4278190080";
  i++; ul_test[i].num = 0x0000000000FF0000UL; ul_test[i].expected = "16711680";
  i++; ul_test[i].num = 0x000000000000FF00UL; ul_test[i].expected = "65280";
  i++; ul_test[i].num = 0x00000000000000FFUL; ul_test[i].expected = "255";

  i++; ul_test[i].num = 0xF000000000000000UL; ul_test[i].expected = "17293822569102704640";
  i++; ul_test[i].num = 0x0F00000000000000UL; ul_test[i].expected = "1080863910568919040";
  i++; ul_test[i].num = 0x00F0000000000000UL; ul_test[i].expected = "67553994410557440";
  i++; ul_test[i].num = 0x000F000000000000UL; ul_test[i].expected = "4222124650659840";
  i++; ul_test[i].num = 0x0000F00000000000UL; ul_test[i].expected = "263882790666240";
  i++; ul_test[i].num = 0x00000F0000000000UL; ul_test[i].expected = "16492674416640";
  i++; ul_test[i].num = 0x000000F000000000UL; ul_test[i].expected = "1030792151040";
  i++; ul_test[i].num = 0x0000000F00000000UL; ul_test[i].expected = "64424509440";
  i++; ul_test[i].num = 0x00000000F0000000UL; ul_test[i].expected = "4026531840";
  i++; ul_test[i].num = 0x000000000F000000UL; ul_test[i].expected = "251658240";
  i++; ul_test[i].num = 0x0000000000F00000UL; ul_test[i].expected = "15728640";
  i++; ul_test[i].num = 0x00000000000F0000UL; ul_test[i].expected = "983040";
  i++; ul_test[i].num = 0x000000000000F000UL; ul_test[i].expected = "61440";
  i++; ul_test[i].num = 0x0000000000000F00UL; ul_test[i].expected = "3840";
  i++; ul_test[i].num = 0x00000000000000F0UL; ul_test[i].expected = "240";
  i++; ul_test[i].num = 0x000000000000000FUL; ul_test[i].expected = "15";

  i++; ul_test[i].num = 0xC000000000000000UL; ul_test[i].expected = "13835058055282163712";
  i++; ul_test[i].num = 0x0C00000000000000UL; ul_test[i].expected = "864691128455135232";
  i++; ul_test[i].num = 0x00C0000000000000UL; ul_test[i].expected = "54043195528445952";
  i++; ul_test[i].num = 0x000C000000000000UL; ul_test[i].expected = "3377699720527872";
  i++; ul_test[i].num = 0x0000C00000000000UL; ul_test[i].expected = "211106232532992";
  i++; ul_test[i].num = 0x00000C0000000000UL; ul_test[i].expected = "13194139533312";
  i++; ul_test[i].num = 0x000000C000000000UL; ul_test[i].expected = "824633720832";
  i++; ul_test[i].num = 0x0000000C00000000UL; ul_test[i].expected = "51539607552";
  i++; ul_test[i].num = 0x00000000C0000000UL; ul_test[i].expected = "3221225472";
  i++; ul_test[i].num = 0x000000000C000000UL; ul_test[i].expected = "201326592";
  i++; ul_test[i].num = 0x0000000000C00000UL; ul_test[i].expected = "12582912";
  i++; ul_test[i].num = 0x00000000000C0000UL; ul_test[i].expected = "786432";
  i++; ul_test[i].num = 0x000000000000C000UL; ul_test[i].expected = "49152";
  i++; ul_test[i].num = 0x0000000000000C00UL; ul_test[i].expected = "3072";
  i++; ul_test[i].num = 0x00000000000000C0UL; ul_test[i].expected = "192";
  i++; ul_test[i].num = 0x000000000000000CUL; ul_test[i].expected = "12";

  i++; ul_test[i].num = 0x00000001UL; ul_test[i].expected = "1";
  i++; ul_test[i].num = 0x00000000UL; ul_test[i].expected = "0";

  num_ulong_tests = i;

#endif

 
  return failed;
}


static int test_signed_long_formatting(void)
{
  int i, j;
  int num_slong_tests = 0;
  int failed = 0;

#if (SIZEOF_LONG == 2)

  i = 1; sl_test[i].num = 0x7FFFL; sl_test[i].expected = "32767";
  i++; sl_test[i].num = 0x7FFEL; sl_test[i].expected = "32766";
  i++; sl_test[i].num = 0x7FFDL; sl_test[i].expected = "32765";
  i++; sl_test[i].num = 0x7F00L; sl_test[i].expected = "32512";
  i++; sl_test[i].num = 0x07F0L; sl_test[i].expected = "2032";
  i++; sl_test[i].num = 0x007FL; sl_test[i].expected = "127";

  i++; sl_test[i].num = 0x7000L; sl_test[i].expected = "28672";
  i++; sl_test[i].num = 0x0700L; sl_test[i].expected = "1792";
  i++; sl_test[i].num = 0x0070L; sl_test[i].expected = "112";
  i++; sl_test[i].num = 0x0007L; sl_test[i].expected = "7";

  i++; sl_test[i].num = 0x5000L; sl_test[i].expected = "20480";
  i++; sl_test[i].num = 0x0500L; sl_test[i].expected = "1280";
  i++; sl_test[i].num = 0x0050L; sl_test[i].expected = "80";
  i++; sl_test[i].num = 0x0005L; sl_test[i].expected = "5";

  i++; sl_test[i].num = 0x0001L; sl_test[i].expected = "1";
  i++; sl_test[i].num = 0x0000L; sl_test[i].expected = "0";

  i++; sl_test[i].num = -0x7FFFL -1L; sl_test[i].expected = "-32768";
  i++; sl_test[i].num = -0x7FFEL -1L; sl_test[i].expected = "-32767";
  i++; sl_test[i].num = -0x7FFDL -1L; sl_test[i].expected = "-32766";
  i++; sl_test[i].num = -0x7F00L -1L; sl_test[i].expected = "-32513";
  i++; sl_test[i].num = -0x07F0L -1L; sl_test[i].expected = "-2033";
  i++; sl_test[i].num = -0x007FL -1L; sl_test[i].expected = "-128";

  i++; sl_test[i].num = -0x7000L -1L; sl_test[i].expected = "-28673";
  i++; sl_test[i].num = -0x0700L -1L; sl_test[i].expected = "-1793";
  i++; sl_test[i].num = -0x0070L -1L; sl_test[i].expected = "-113";
  i++; sl_test[i].num = -0x0007L -1L; sl_test[i].expected = "-8";

  i++; sl_test[i].num = -0x5000L -1L; sl_test[i].expected = "-20481";
  i++; sl_test[i].num = -0x0500L -1L; sl_test[i].expected = "-1281";
  i++; sl_test[i].num = -0x0050L -1L; sl_test[i].expected = "-81";
  i++; sl_test[i].num = -0x0005L -1L; sl_test[i].expected = "-6";

  i++; sl_test[i].num =  0x0000L -1L; sl_test[i].expected = "-1";

  num_slong_tests = i;

#elif (SIZEOF_LONG == 4)

  i = 1; sl_test[i].num = 0x7FFFFFFFL; sl_test[i].expected = "2147483647";
  i++; sl_test[i].num = 0x7FFFFFFEL; sl_test[i].expected = "2147483646";
  i++; sl_test[i].num = 0x7FFFFFFDL; sl_test[i].expected = "2147483645";
  i++; sl_test[i].num = 0x7FFF0000L; sl_test[i].expected = "2147418112";
  i++; sl_test[i].num = 0x00007FFFL; sl_test[i].expected = "32767";

  i++; sl_test[i].num = 0x7F000000L; sl_test[i].expected = "2130706432";
  i++; sl_test[i].num = 0x007F0000L; sl_test[i].expected = "8323072";
  i++; sl_test[i].num = 0x00007F00L; sl_test[i].expected = "32512";
  i++; sl_test[i].num = 0x0000007FL; sl_test[i].expected = "127";

  i++; sl_test[i].num = 0x70000000L; sl_test[i].expected = "1879048192";
  i++; sl_test[i].num = 0x07000000L; sl_test[i].expected = "117440512";
  i++; sl_test[i].num = 0x00700000L; sl_test[i].expected = "7340032";
  i++; sl_test[i].num = 0x00070000L; sl_test[i].expected = "458752";
  i++; sl_test[i].num = 0x00007000L; sl_test[i].expected = "28672";
  i++; sl_test[i].num = 0x00000700L; sl_test[i].expected = "1792";
  i++; sl_test[i].num = 0x00000070L; sl_test[i].expected = "112";
  i++; sl_test[i].num = 0x00000007L; sl_test[i].expected = "7";

  i++; sl_test[i].num = 0x50000000L; sl_test[i].expected = "1342177280";
  i++; sl_test[i].num = 0x05000000L; sl_test[i].expected = "83886080";
  i++; sl_test[i].num = 0x00500000L; sl_test[i].expected = "5242880";
  i++; sl_test[i].num = 0x00050000L; sl_test[i].expected = "327680";
  i++; sl_test[i].num = 0x00005000L; sl_test[i].expected = "20480";
  i++; sl_test[i].num = 0x00000500L; sl_test[i].expected = "1280";
  i++; sl_test[i].num = 0x00000050L; sl_test[i].expected = "80";
  i++; sl_test[i].num = 0x00000005L; sl_test[i].expected = "5";

  i++; sl_test[i].num = 0x00000001L; sl_test[i].expected = "1";
  i++; sl_test[i].num = 0x00000000L; sl_test[i].expected = "0";

  i++; sl_test[i].num = -0x7FFFFFFFL -1L; sl_test[i].expected = "-2147483648";
  i++; sl_test[i].num = -0x7FFFFFFEL -1L; sl_test[i].expected = "-2147483647";
  i++; sl_test[i].num = -0x7FFFFFFDL -1L; sl_test[i].expected = "-2147483646";
  i++; sl_test[i].num = -0x7FFF0000L -1L; sl_test[i].expected = "-2147418113";
  i++; sl_test[i].num = -0x00007FFFL -1L; sl_test[i].expected = "-32768";

  i++; sl_test[i].num = -0x7F000000L -1L; sl_test[i].expected = "-2130706433";
  i++; sl_test[i].num = -0x007F0000L -1L; sl_test[i].expected = "-8323073";
  i++; sl_test[i].num = -0x00007F00L -1L; sl_test[i].expected = "-32513";
  i++; sl_test[i].num = -0x0000007FL -1L; sl_test[i].expected = "-128";

  i++; sl_test[i].num = -0x70000000L -1L; sl_test[i].expected = "-1879048193";
  i++; sl_test[i].num = -0x07000000L -1L; sl_test[i].expected = "-117440513";
  i++; sl_test[i].num = -0x00700000L -1L; sl_test[i].expected = "-7340033";
  i++; sl_test[i].num = -0x00070000L -1L; sl_test[i].expected = "-458753";
  i++; sl_test[i].num = -0x00007000L -1L; sl_test[i].expected = "-28673";
  i++; sl_test[i].num = -0x00000700L -1L; sl_test[i].expected = "-1793";
  i++; sl_test[i].num = -0x00000070L -1L; sl_test[i].expected = "-113";
  i++; sl_test[i].num = -0x00000007L -1L; sl_test[i].expected = "-8";

  i++; sl_test[i].num = -0x50000000L -1L; sl_test[i].expected = "-1342177281";
  i++; sl_test[i].num = -0x05000000L -1L; sl_test[i].expected = "-83886081";
  i++; sl_test[i].num = -0x00500000L -1L; sl_test[i].expected = "-5242881";
  i++; sl_test[i].num = -0x00050000L -1L; sl_test[i].expected = "-327681";
  i++; sl_test[i].num = -0x00005000L -1L; sl_test[i].expected = "-20481";
  i++; sl_test[i].num = -0x00000500L -1L; sl_test[i].expected = "-1281";
  i++; sl_test[i].num = -0x00000050L -1L; sl_test[i].expected = "-81";
  i++; sl_test[i].num = -0x00000005L -1L; sl_test[i].expected = "-6";

  i++; sl_test[i].num =  0x00000000L -1L; sl_test[i].expected = "-1";

  num_slong_tests = i;

#elif (SIZEOF_LONG == 8)

  i = 1; sl_test[i].num = 0x7FFFFFFFFFFFFFFFL; sl_test[i].expected = "9223372036854775807";
  i++; sl_test[i].num = 0x7FFFFFFFFFFFFFFEL; sl_test[i].expected = "9223372036854775806";
  i++; sl_test[i].num = 0x7FFFFFFFFFFFFFFDL; sl_test[i].expected = "9223372036854775805";
  i++; sl_test[i].num = 0x7FFFFFFF00000000L; sl_test[i].expected = "9223372032559808512";
  i++; sl_test[i].num = 0x000000007FFFFFFFL; sl_test[i].expected = "2147483647";

  i++; sl_test[i].num = 0x7FFF000000000000L; sl_test[i].expected = "9223090561878065152";
  i++; sl_test[i].num = 0x00007FFF00000000L; sl_test[i].expected = "140733193388032";
  i++; sl_test[i].num = 0x000000007FFF0000L; sl_test[i].expected = "2147418112";
  i++; sl_test[i].num = 0x0000000000007FFFL; sl_test[i].expected = "32767";

  i++; sl_test[i].num = 0x7F00000000000000L; sl_test[i].expected = "9151314442816847872";
  i++; sl_test[i].num = 0x007F000000000000L; sl_test[i].expected = "35747322042253312";
  i++; sl_test[i].num = 0x00007F0000000000L; sl_test[i].expected = "139637976727552";
  i++; sl_test[i].num = 0x0000007F00000000L; sl_test[i].expected = "545460846592";
  i++; sl_test[i].num = 0x000000007F000000L; sl_test[i].expected = "2130706432";
  i++; sl_test[i].num = 0x00000000007F0000L; sl_test[i].expected = "8323072";
  i++; sl_test[i].num = 0x0000000000007F00L; sl_test[i].expected = "32512";
  i++; sl_test[i].num = 0x000000000000007FL; sl_test[i].expected = "127";

  i++; sl_test[i].num = 0x7000000000000000L; sl_test[i].expected = "8070450532247928832";
  i++; sl_test[i].num = 0x0700000000000000L; sl_test[i].expected = "504403158265495552";
  i++; sl_test[i].num = 0x0070000000000000L; sl_test[i].expected = "31525197391593472";
  i++; sl_test[i].num = 0x0007000000000000L; sl_test[i].expected = "1970324836974592";
  i++; sl_test[i].num = 0x0000700000000000L; sl_test[i].expected = "123145302310912";
  i++; sl_test[i].num = 0x0000070000000000L; sl_test[i].expected = "7696581394432";
  i++; sl_test[i].num = 0x0000007000000000L; sl_test[i].expected = "481036337152";
  i++; sl_test[i].num = 0x0000000700000000L; sl_test[i].expected = "30064771072";
  i++; sl_test[i].num = 0x0000000070000000L; sl_test[i].expected = "1879048192";
  i++; sl_test[i].num = 0x0000000007000000L; sl_test[i].expected = "117440512";
  i++; sl_test[i].num = 0x0000000000700000L; sl_test[i].expected = "7340032";
  i++; sl_test[i].num = 0x0000000000070000L; sl_test[i].expected = "458752";
  i++; sl_test[i].num = 0x0000000000007000L; sl_test[i].expected = "28672";
  i++; sl_test[i].num = 0x0000000000000700L; sl_test[i].expected = "1792";
  i++; sl_test[i].num = 0x0000000000000070L; sl_test[i].expected = "112";
  i++; sl_test[i].num = 0x0000000000000007L; sl_test[i].expected = "7";

  i++; sl_test[i].num = 0x0000000000000001L; sl_test[i].expected = "1";
  i++; sl_test[i].num = 0x0000000000000000L; sl_test[i].expected = "0";

  i++; sl_test[i].num = -0x7FFFFFFFFFFFFFFFL -1L; sl_test[i].expected = "-9223372036854775808";
  i++; sl_test[i].num = -0x7FFFFFFFFFFFFFFEL -1L; sl_test[i].expected = "-9223372036854775807";
  i++; sl_test[i].num = -0x7FFFFFFFFFFFFFFDL -1L; sl_test[i].expected = "-9223372036854775806";
  i++; sl_test[i].num = -0x7FFFFFFF00000000L -1L; sl_test[i].expected = "-9223372032559808513";
  i++; sl_test[i].num = -0x000000007FFFFFFFL -1L; sl_test[i].expected = "-2147483648";

  i++; sl_test[i].num = -0x7FFF000000000000L -1L; sl_test[i].expected = "-9223090561878065153";
  i++; sl_test[i].num = -0x00007FFF00000000L -1L; sl_test[i].expected = "-140733193388033";
  i++; sl_test[i].num = -0x000000007FFF0000L -1L; sl_test[i].expected = "-2147418113";
  i++; sl_test[i].num = -0x0000000000007FFFL -1L; sl_test[i].expected = "-32768";

  i++; sl_test[i].num = -0x7F00000000000000L -1L; sl_test[i].expected = "-9151314442816847873";
  i++; sl_test[i].num = -0x007F000000000000L -1L; sl_test[i].expected = "-35747322042253313";
  i++; sl_test[i].num = -0x00007F0000000000L -1L; sl_test[i].expected = "-139637976727553";
  i++; sl_test[i].num = -0x0000007F00000000L -1L; sl_test[i].expected = "-545460846593";
  i++; sl_test[i].num = -0x000000007F000000L -1L; sl_test[i].expected = "-2130706433";
  i++; sl_test[i].num = -0x00000000007F0000L -1L; sl_test[i].expected = "-8323073";
  i++; sl_test[i].num = -0x0000000000007F00L -1L; sl_test[i].expected = "-32513";
  i++; sl_test[i].num = -0x000000000000007FL -1L; sl_test[i].expected = "-128";

  i++; sl_test[i].num = -0x7000000000000000L -1L; sl_test[i].expected = "-8070450532247928833";
  i++; sl_test[i].num = -0x0700000000000000L -1L; sl_test[i].expected = "-504403158265495553";
  i++; sl_test[i].num = -0x0070000000000000L -1L; sl_test[i].expected = "-31525197391593473";
  i++; sl_test[i].num = -0x0007000000000000L -1L; sl_test[i].expected = "-1970324836974593";
  i++; sl_test[i].num = -0x0000700000000000L -1L; sl_test[i].expected = "-123145302310913";
  i++; sl_test[i].num = -0x0000070000000000L -1L; sl_test[i].expected = "-7696581394433";
  i++; sl_test[i].num = -0x0000007000000000L -1L; sl_test[i].expected = "-481036337153";
  i++; sl_test[i].num = -0x0000000700000000L -1L; sl_test[i].expected = "-30064771073";
  i++; sl_test[i].num = -0x0000000070000000L -1L; sl_test[i].expected = "-1879048193";
  i++; sl_test[i].num = -0x0000000007000000L -1L; sl_test[i].expected = "-117440513";
  i++; sl_test[i].num = -0x0000000000700000L -1L; sl_test[i].expected = "-7340033";
  i++; sl_test[i].num = -0x0000000000070000L -1L; sl_test[i].expected = "-458753";
  i++; sl_test[i].num = -0x0000000000007000L -1L; sl_test[i].expected = "-28673";
  i++; sl_test[i].num = -0x0000000000000700L -1L; sl_test[i].expected = "-1793";
  i++; sl_test[i].num = -0x0000000000000070L -1L; sl_test[i].expected = "-113";
  i++; sl_test[i].num = -0x0000000000000007L -1L; sl_test[i].expected = "-8";

  i++; sl_test[i].num =  0x0000000000000000L -1L; sl_test[i].expected = "-1";

  num_slong_tests = i;

#endif

 
  return failed;
}


static int test_curl_off_t_formatting(void)
{
  int i, j;
  int num_cofft_tests = 0;
  int failed = 0;

  i = 1; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFF); co_test[i].expected = "9223372036854775807";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFE); co_test[i].expected = "9223372036854775806";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFD); co_test[i].expected = "9223372036854775805";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFFFFFF00000000); co_test[i].expected = "9223372032559808512";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x000000007FFFFFFF); co_test[i].expected = "2147483647";

  i++; co_test[i].num = MPRNT_OFF_T_C(0x7FFF000000000000); co_test[i].expected = "9223090561878065152";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x00007FFF00000000); co_test[i].expected = "140733193388032";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x000000007FFF0000); co_test[i].expected = "2147418112";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000007FFF); co_test[i].expected = "32767";

  i++; co_test[i].num = MPRNT_OFF_T_C(0x7F00000000000000); co_test[i].expected = "9151314442816847872";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x007F000000000000); co_test[i].expected = "35747322042253312";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x00007F0000000000); co_test[i].expected = "139637976727552";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000007F00000000); co_test[i].expected = "545460846592";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x000000007F000000); co_test[i].expected = "2130706432";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x00000000007F0000); co_test[i].expected = "8323072";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000007F00); co_test[i].expected = "32512";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x000000000000007F); co_test[i].expected = "127";

  i++; co_test[i].num = MPRNT_OFF_T_C(0x7000000000000000); co_test[i].expected = "8070450532247928832";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0700000000000000); co_test[i].expected = "504403158265495552";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0070000000000000); co_test[i].expected = "31525197391593472";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0007000000000000); co_test[i].expected = "1970324836974592";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000700000000000); co_test[i].expected = "123145302310912";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000070000000000); co_test[i].expected = "7696581394432";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000007000000000); co_test[i].expected = "481036337152";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000700000000); co_test[i].expected = "30064771072";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000070000000); co_test[i].expected = "1879048192";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000007000000); co_test[i].expected = "117440512";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000700000); co_test[i].expected = "7340032";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000070000); co_test[i].expected = "458752";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000007000); co_test[i].expected = "28672";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000700); co_test[i].expected = "1792";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000070); co_test[i].expected = "112";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000007); co_test[i].expected = "7";

  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000001); co_test[i].expected = "1";
  i++; co_test[i].num = MPRNT_OFF_T_C(0x0000000000000000); co_test[i].expected = "0";

  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFF) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372036854775808";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFE) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372036854775807";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFFFFFFFFFD) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372036854775806";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFFFFFF00000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223372032559808513";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000007FFFFFFF) -MPRNT_OFF_T_C(1); co_test[i].expected = "-2147483648";

  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7FFF000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9223090561878065153";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x00007FFF00000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-140733193388033";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000007FFF0000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-2147418113";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000007FFF) -MPRNT_OFF_T_C(1); co_test[i].expected = "-32768";

  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7F00000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-9151314442816847873";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x007F000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-35747322042253313";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x00007F0000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-139637976727553";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000007F00000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-545460846593";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000007F000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-2130706433";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x00000000007F0000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-8323073";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000007F00) -MPRNT_OFF_T_C(1); co_test[i].expected = "-32513";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x000000000000007F) -MPRNT_OFF_T_C(1); co_test[i].expected = "-128";

  i++; co_test[i].num = -MPRNT_OFF_T_C(0x7000000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-8070450532247928833";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0700000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-504403158265495553";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0070000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-31525197391593473";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0007000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1970324836974593";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000700000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-123145302310913";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000070000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-7696581394433";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000007000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-481036337153";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000700000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-30064771073";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000070000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1879048193";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000007000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-117440513";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000700000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-7340033";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000070000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-458753";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000007000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-28673";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000000700) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1793";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000000070) -MPRNT_OFF_T_C(1); co_test[i].expected = "-113";
  i++; co_test[i].num = -MPRNT_OFF_T_C(0x0000000000000007) -MPRNT_OFF_T_C(1); co_test[i].expected = "-8";

  i++; co_test[i].num =  MPRNT_OFF_T_C(0x0000000000000000) -MPRNT_OFF_T_C(1); co_test[i].expected = "-1";

  num_cofft_tests = i;

  
  return failed;
}




int main() {

printf("%ld\n",0xFFFFFFFFFFFFFFFFU);
printf("%d\n",0x00000000FFFF0000U);
printf("%ld\n",0xFFFF000000000000UL);
printf("%ld\n",0x0000FFFF00000000UL);
printf("%ld\n", sizeof(long));
printf("%ld\n", sizeof(int));
printf("%ld\n", sizeof(unsigned int));
printf("%ld\n", SIZEOF_INT);
printf("%ld\n", SIZEOF_LONG);
printf("%ld\n", sizeof(unsigned int));


return 0;
}