#include <string.h>
#include <stdio.h>
#include <stddef.h>
//#include <stdbool.h>
//#define FALSE false
/* the kind of data that is passed to information_callback */
// typedef enum {
//   CURLINFO_TEXT = 0,
//   CURLINFO_HEADER_IN,    /* 1 */
//   CURLINFO_HEADER_OUT,   /* 2 */
//   CURLINFO_DATA_IN,      /* 3 */
//   CURLINFO_DATA_OUT,     /* 4 */
//   CURLINFO_SSL_DATA_IN,  /* 5 */
//   CURLINFO_SSL_DATA_OUT, /* 6 */
//   CURLINFO_END
// } curl_infotype;

// /* Return code for when the pre-request callback has terminated without
//    any errors */
// #define CURL_PREREQFUNC_OK 0
// /* Return code for when the pre-request callback wants to abort the
//    request */
// #define CURL_PREREQFUNC_ABORT 1

// /* All possible error codes from all sorts of curl functions. Future versions
//    may return other values, stay prepared.

//    Always add new return codes last. Never *EVER* remove any. The return
//    codes must remain the same!
//  */

// typedef enum {
//   CURLE_OK = 0,
//   CURLE_UNSUPPORTED_PROTOCOL,    /* 1 */
//   CURLE_FAILED_INIT,             /* 2 */
//   CURLE_URL_MALFORMAT,           /* 3 */
//   CURLE_NOT_BUILT_IN,            /* 4 - [was obsoleted in August 2007 for
//                                     7.17.0, reused in April 2011 for 7.21.5] */
//   CURLE_COULDNT_RESOLVE_PROXY,   /* 5 */
//   CURLE_COULDNT_RESOLVE_HOST,    /* 6 */
//   CURLE_COULDNT_CONNECT,         /* 7 */
//   CURLE_WEIRD_SERVER_REPLY,      /* 8 */
//   CURLE_REMOTE_ACCESS_DENIED,    /* 9 a service was denied by the server
//                                     due to lack of access - when login fails
//                                     this is not returned. */
//   CURLE_FTP_ACCEPT_FAILED,       /* 10 - [was obsoleted in April 2006 for
//                                     7.15.4, reused in Dec 2011 for 7.24.0]*/
//   CURLE_FTP_WEIRD_PASS_REPLY,    /* 11 */
//   CURLE_FTP_ACCEPT_TIMEOUT,      /* 12 - timeout occurred accepting server
//                                     [was obsoleted in August 2007 for 7.17.0,
//                                     reused in Dec 2011 for 7.24.0]*/
//   CURLE_FTP_WEIRD_PASV_REPLY,    /* 13 */
//   CURLE_FTP_WEIRD_227_FORMAT,    /* 14 */
//   CURLE_FTP_CANT_GET_HOST,       /* 15 */
//   CURLE_HTTP2,                   /* 16 - A problem in the http2 framing layer.
//                                     [was obsoleted in August 2007 for 7.17.0,
//                                     reused in July 2014 for 7.38.0] */
//   CURLE_FTP_COULDNT_SET_TYPE,    /* 17 */
//   CURLE_PARTIAL_FILE,            /* 18 */
//   CURLE_FTP_COULDNT_RETR_FILE,   /* 19 */
//   CURLE_OBSOLETE20,              /* 20 - NOT USED */
//   CURLE_QUOTE_ERROR,             /* 21 - quote command failure */
//   CURLE_HTTP_RETURNED_ERROR,     /* 22 */
//   CURLE_WRITE_ERROR,             /* 23 */
//   CURLE_OBSOLETE24,              /* 24 - NOT USED */
//   CURLE_UPLOAD_FAILED,           /* 25 - failed upload "command" */
//   CURLE_READ_ERROR,              /* 26 - could not open/read from file */
//   CURLE_OUT_OF_MEMORY,           /* 27 */
//   CURLE_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
//   CURLE_OBSOLETE29,              /* 29 - NOT USED */
//   CURLE_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
//   CURLE_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
//   CURLE_OBSOLETE32,              /* 32 - NOT USED */
//   CURLE_RANGE_ERROR,             /* 33 - RANGE "command" did not work */
//   CURLE_HTTP_POST_ERROR,         /* 34 */
//   CURLE_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
//   CURLE_BAD_DOWNLOAD_RESUME,     /* 36 - could not resume download */
//   CURLE_FILE_COULDNT_READ_FILE,  /* 37 */
//   CURLE_LDAP_CANNOT_BIND,        /* 38 */
//   CURLE_LDAP_SEARCH_FAILED,      /* 39 */
//   CURLE_OBSOLETE40,              /* 40 - NOT USED */
//   CURLE_FUNCTION_NOT_FOUND,      /* 41 - NOT USED starting with 7.53.0 */
//   CURLE_ABORTED_BY_CALLBACK,     /* 42 */
//   CURLE_BAD_FUNCTION_ARGUMENT,   /* 43 */
//   CURLE_OBSOLETE44,              /* 44 - NOT USED */
//   CURLE_INTERFACE_FAILED,        /* 45 - CURLOPT_INTERFACE failed */
//   CURLE_OBSOLETE46,              /* 46 - NOT USED */
//   CURLE_TOO_MANY_REDIRECTS,      /* 47 - catch endless re-direct loops */
//   CURLE_UNKNOWN_OPTION,          /* 48 - User specified an unknown option */
//   CURLE_SETOPT_OPTION_SYNTAX,    /* 49 - Malformed setopt option */
//   CURLE_OBSOLETE50,              /* 50 - NOT USED */
//   CURLE_OBSOLETE51,              /* 51 - NOT USED */
//   CURLE_GOT_NOTHING,             /* 52 - when this is a specific error */
//   CURLE_SSL_ENGINE_NOTFOUND,     /* 53 - SSL crypto engine not found */
//   CURLE_SSL_ENGINE_SETFAILED,    /* 54 - can not set SSL crypto engine as
//                                     default */
//   CURLE_SEND_ERROR,              /* 55 - failed sending network data */
//   CURLE_RECV_ERROR,              /* 56 - failure in receiving network data */
//   CURLE_OBSOLETE57,              /* 57 - NOT IN USE */
//   CURLE_SSL_CERTPROBLEM,         /* 58 - problem with the local certificate */
//   CURLE_SSL_CIPHER,              /* 59 - could not use specified cipher */
//   CURLE_PEER_FAILED_VERIFICATION, /* 60 - peer's certificate or fingerprint
//                                      was not verified fine */
//   CURLE_BAD_CONTENT_ENCODING,    /* 61 - Unrecognized/bad encoding */
//   CURLE_OBSOLETE62,              /* 62 - NOT IN USE since 7.82.0 */
//   CURLE_FILESIZE_EXCEEDED,       /* 63 - Maximum file size exceeded */
//   CURLE_USE_SSL_FAILED,          /* 64 - Requested FTP SSL level failed */
//   CURLE_SEND_FAIL_REWIND,        /* 65 - Sending the data requires a rewind
//                                     that failed */
//   CURLE_SSL_ENGINE_INITFAILED,   /* 66 - failed to initialise ENGINE */
//   CURLE_LOGIN_DENIED,            /* 67 - user, password or similar was not
//                                     accepted and we failed to login */
//   CURLE_TFTP_NOTFOUND,           /* 68 - file not found on server */
//   CURLE_TFTP_PERM,               /* 69 - permission problem on server */
//   CURLE_REMOTE_DISK_FULL,        /* 70 - out of disk space on server */
//   CURLE_TFTP_ILLEGAL,            /* 71 - Illegal TFTP operation */
//   CURLE_TFTP_UNKNOWNID,          /* 72 - Unknown transfer ID */
//   CURLE_REMOTE_FILE_EXISTS,      /* 73 - File already exists */
//   CURLE_TFTP_NOSUCHUSER,         /* 74 - No such user */
//   CURLE_OBSOLETE75,              /* 75 - NOT IN USE since 7.82.0 */
//   CURLE_OBSOLETE76,              /* 76 - NOT IN USE since 7.82.0 */
//   CURLE_SSL_CACERT_BADFILE,      /* 77 - could not load CACERT file, missing
//                                     or wrong format */
//   CURLE_REMOTE_FILE_NOT_FOUND,   /* 78 - remote file not found */
//   CURLE_SSH,                     /* 79 - error from the SSH layer, somewhat
//                                     generic so the error message will be of
//                                     interest when this has happened */

//   CURLE_SSL_SHUTDOWN_FAILED,     /* 80 - Failed to shut down the SSL
//                                     connection */
//   CURLE_AGAIN,                   /* 81 - socket is not ready for send/recv,
//                                     wait till it is ready and try again (Added
//                                     in 7.18.2) */
//   CURLE_SSL_CRL_BADFILE,         /* 82 - could not load CRL file, missing or
//                                     wrong format (Added in 7.19.0) */
//   CURLE_SSL_ISSUER_ERROR,        /* 83 - Issuer check failed.  (Added in
//                                     7.19.0) */
//   CURLE_FTP_PRET_FAILED,         /* 84 - a PRET command failed */
//   CURLE_RTSP_CSEQ_ERROR,         /* 85 - mismatch of RTSP CSeq numbers */
//   CURLE_RTSP_SESSION_ERROR,      /* 86 - mismatch of RTSP Session Ids */
//   CURLE_FTP_BAD_FILE_LIST,       /* 87 - unable to parse FTP file list */
//   CURLE_CHUNK_FAILED,            /* 88 - chunk callback reported error */
//   CURLE_NO_CONNECTION_AVAILABLE, /* 89 - No connection available, the
//                                     session will be queued */
//   CURLE_SSL_PINNEDPUBKEYNOTMATCH, /* 90 - specified pinned public key did not
//                                      match */
//   CURLE_SSL_INVALIDCERTSTATUS,   /* 91 - invalid certificate status */
//   CURLE_HTTP2_STREAM,            /* 92 - stream error in HTTP/2 framing layer
//                                     */
//   CURLE_RECURSIVE_API_CALL,      /* 93 - an api function was called from
//                                     inside a callback */
//   CURLE_AUTH_ERROR,              /* 94 - an authentication function returned an
//                                     error */
//   CURLE_HTTP3,                   /* 95 - An HTTP/3 layer problem */
//   CURLE_QUIC_CONNECT_ERROR,      /* 96 - QUIC connection error */
//   CURLE_PROXY,                   /* 97 - proxy handshake error */
//   CURLE_SSL_CLIENTCERT,          /* 98 - client-side certificate required */
//   CURLE_UNRECOVERABLE_POLL,      /* 99 - poll/select returned fatal error */
//   CURLE_TOO_LARGE,               /* 100 - a value/data met its maximum */
//   CURLE_ECH_REQUIRED,            /* 101 - ECH tried but failed */
//   CURL_LAST /* never use! */
// } CURLcode;

/* Authentication mechanism flags */
#define SASL_MECH_LOGIN             (1 << 0)
#define SASL_MECH_PLAIN             (1 << 1)
#define SASL_MECH_CRAM_MD5          (1 << 2)
#define SASL_MECH_DIGEST_MD5        (1 << 3)
#define SASL_MECH_GSSAPI            (1 << 4)
#define SASL_MECH_EXTERNAL          (1 << 5)
#define SASL_MECH_NTLM              (1 << 6)
#define SASL_MECH_XOAUTH2           (1 << 7)
#define SASL_MECH_OAUTHBEARER       (1 << 8)
#define SASL_MECH_SCRAM_SHA_1       (1 << 9)
#define SASL_MECH_SCRAM_SHA_256     (1 << 10)

#define ZERO_NULL 0

/* Authentication mechanism values */
#define SASL_AUTH_NONE          0
#define SASL_AUTH_ANY           0xffff
//#define SASL_AUTH_DEFAULT       (SASL_AUTH_ANY & ~SASL_MECH_EXTERNAL)


#define ISLOWHEXALHA(x) (((x) >= 'a') && ((x) <= 'f'))
#define ISUPHEXALHA(x) (((x) >= 'A') && ((x) <= 'F'))

#define ISLOWCNTRL(x) ((unsigned char)(x) <= 0x1f)
#define IS7F(x) ((x) == 0x7f)
typedef unsigned int bit;
// #define BIT(x) bit x:1

#define ISLOWPRINT(x) (((x) >= 9) && ((x) <= 0x0d))

#define ISPRINT(x)  (ISLOWPRINT(x) || (((x) >= ' ') && ((x) <= 0x7e)))
#define ISGRAPH(x)  (ISLOWPRINT(x) || (((x) > ' ') && ((x) <= 0x7e)))
#define ISCNTRL(x) (ISLOWCNTRL(x) || IS7F(x))
#define ISALPHA(x) (ISLOWER(x) || ISUPPER(x))
#define ISXDIGIT(x) (ISDIGIT(x) || ISLOWHEXALHA(x) || ISUPHEXALHA(x))
#define ISALNUM(x)  (ISDIGIT(x) || ISLOWER(x) || ISUPPER(x))
#define ISUPPER(x)  (((x) >= 'A') && ((x) <= 'Z'))
#define ISLOWER(x)  (((x) >= 'a') && ((x) <= 'z'))
#define ISDIGIT(x)  (((x) >= '0') && ((x) <= '9'))
#define ISBLANK(x)  (((x) == ' ') || ((x) == '\t'))
#define ISSPACE(x)  (ISBLANK(x) || (((x) >= 0xa) && ((x) <= 0x0d)))
#define ISURLPUNTCS(x) (((x) == '-') || ((x) == '.') || ((x) == '_') || \
                        ((x) == '~'))


// /* Protocol dependent SASL parameters */
// struct SASLproto {
//   const char *service;     /* The service name */
//   CURLcode (*sendauth)(struct Curl_easy *data, const char *mech,
//                        const struct bufref *ir);
//                            /* Send authentication command */
//   CURLcode (*contauth)(struct Curl_easy *data, const char *mech,
//                        const struct bufref *contauth);
//                            /* Send authentication continuation */
//   CURLcode (*cancelauth)(struct Curl_easy *data, const char *mech);
//                            /* Cancel authentication. */
//   CURLcode (*getmessage)(struct Curl_easy *data, struct bufref *out);
//                            /* Get SASL response message */
//   size_t maxirlen;         /* Maximum initial response + mechanism length,
//                               or zero if no max. This is normally the max
//                               command length - other characters count.
//                               This has to be zero for non-base64 protocols. */
//   int contcode;            /* Code to receive when continuation is expected */
//   int finalcode;           /* Code to receive upon authentication success */
//   unsigned short defmechs; /* Mechanisms enabled by default */
//   unsigned short flags;    /* Configuration flags. */
// };


// /* SASL machine states */
// typedef enum {
//   SASL_STOP,
//   SASL_PLAIN,
//   SASL_LOGIN,
//   SASL_LOGIN_PASSWD,
//   SASL_EXTERNAL,
//   SASL_CRAMMD5,
//   SASL_DIGESTMD5,
//   SASL_DIGESTMD5_RESP,
//   SASL_NTLM,
//   SASL_NTLM_TYPE2MSG,
//   SASL_GSSAPI,
//   SASL_GSSAPI_TOKEN,
//   SASL_GSSAPI_NO_DATA,
//   SASL_OAUTH2,
//   SASL_OAUTH2_RESP,
//   SASL_GSASL,
//   SASL_CANCEL,
//   SASL_FINAL
// } saslstate;


// /* Per-connection parameters */
// struct SASL {
//   const struct SASLproto *params; /* Protocol dependent parameters */
//   saslstate state;           /* Current machine state */
//   const char *curmech;       /* Current mechanism id. */
//   unsigned short authmechs;  /* Accepted authentication mechanisms */
//   unsigned short prefmech;   /* Preferred authentication mechanism */
//   unsigned short authused;   /* Auth mechanism used for the connection */
//   BIT(resetprefs);           /* For URL auth option parsing. */
//   BIT(mutual_auth);          /* Mutual authentication enabled (GSSAPI only) */
//   BIT(force_ir);             /* Protocol always supports initial response */
// };


/* Supported mechanisms */
static const struct {
  const char    *name;  /* Name */
  size_t         len;   /* Name length */
  unsigned short bit;   /* Flag bit */
} mechtable[] = {
  { "LOGIN",        5,  SASL_MECH_LOGIN },
  { "PLAIN",        5,  SASL_MECH_PLAIN },
  { "CRAM-MD5",     8,  SASL_MECH_CRAM_MD5 },
  { "DIGEST-MD5",   10, SASL_MECH_DIGEST_MD5 },
  { "GSSAPI",       6,  SASL_MECH_GSSAPI },
  { "EXTERNAL",     8,  SASL_MECH_EXTERNAL },
  { "NTLM",         4,  SASL_MECH_NTLM },
  { "XOAUTH2",      7,  SASL_MECH_XOAUTH2 },
  { "OAUTHBEARER",  11, SASL_MECH_OAUTHBEARER },
  { "SCRAM-SHA-1",  11, SASL_MECH_SCRAM_SHA_1 },
  { "SCRAM-SHA-256",13, SASL_MECH_SCRAM_SHA_256 },
  { ZERO_NULL,      0,  0 }
};

unsigned short Curl_sasl_decode_mech(const char *ptr, size_t maxlen,
                                     size_t *len)
{
  unsigned int i;
  char c;

  for(i = 0; mechtable[i].name; i++) {
    if(maxlen >= mechtable[i].len &&
       !memcmp(ptr, mechtable[i].name, mechtable[i].len)) {
      if(len)
        *len = mechtable[i].len;

      if(maxlen == mechtable[i].len)
        return mechtable[i].bit;

      c = ptr[mechtable[i].len];
      if(!ISUPPER(c) && !ISDIGIT(c) && c != '-' && c != '_')
        return mechtable[i].bit;
    }
  }

  return 0;
}

// CURLcode Curl_sasl_parse_url_auth_option(struct SASL *sasl,
//                                          const char *value, size_t len)
// {
//   CURLcode result = CURLE_OK;
//   size_t mechlen;

//   if(!len)
//     return CURLE_URL_MALFORMAT;

//   if(sasl->resetprefs) {
//     sasl->resetprefs = FALSE;
//     sasl->prefmech = SASL_AUTH_NONE;
//   }

//   if(!strncmp(value, "*", len))
//     sasl->prefmech = SASL_AUTH_DEFAULT;
//   else {
//     unsigned short mechbit = Curl_sasl_decode_mech(value, len, &mechlen);
//     if(mechbit && mechlen == len)
//       sasl->prefmech |= mechbit;
//     else
//       result = CURLE_URL_MALFORMAT;
//   }

//   return result;
// }

int main() {
    char *ptr = "hello";
    size_t maxlen = 200;
    size_t len = strlen(ptr);
    unsigned short result = Curl_sasl_decode_mech(ptr, maxlen, &len);
    printf("result = %d\n", result);
    return 0;
}