#define SIZEOF_CURL_OFF_T 8
#include "curl_setup.h"

#define CURLWARNING(id, message)                                        \
  static void __attribute__((__warning__(message)))                     \
  __attribute__((__unused__)) __attribute__((__noinline__))             \
  id(void) { __asm__(""); }



CURLWARNING(_curl_easy_setopt_err_long,
  "curl_easy_setopt expects a long argument for this option")
CURLWARNING(_curl_easy_setopt_err_curl_off_t,
  "curl_easy_setopt expects a curl_off_t argument for this option")
CURLWARNING(_curl_easy_setopt_err_string,
              "curl_easy_setopt expects a "
              "string ('char *' or char[]) argument for this option"
  )
CURLWARNING(_curl_easy_setopt_err_write_callback,
  "curl_easy_setopt expects a curl_write_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_resolver_start_callback,
              "curl_easy_setopt expects a "
              "curl_resolver_start_callback argument for this option"
  )
CURLWARNING(_curl_easy_setopt_err_read_cb,
  "curl_easy_setopt expects a curl_read_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_ioctl_cb,
  "curl_easy_setopt expects a curl_ioctl_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_sockopt_cb,
  "curl_easy_setopt expects a curl_sockopt_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_opensocket_cb,
              "curl_easy_setopt expects a "
              "curl_opensocket_callback argument for this option"
  )
CURLWARNING(_curl_easy_setopt_err_progress_cb,
  "curl_easy_setopt expects a curl_progress_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_debug_cb,
  "curl_easy_setopt expects a curl_debug_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_ssl_ctx_cb,
  "curl_easy_setopt expects a curl_ssl_ctx_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_conv_cb,
  "curl_easy_setopt expects a curl_conv_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_seek_cb,
  "curl_easy_setopt expects a curl_seek_callback argument for this option")
CURLWARNING(_curl_easy_setopt_err_cb_data,
              "curl_easy_setopt expects a "
              "private data pointer as argument for this option")
CURLWARNING(_curl_easy_setopt_err_error_buffer,
              "curl_easy_setopt expects a "
              "char buffer of CURL_ERROR_SIZE as argument for this option")
CURLWARNING(_curl_easy_setopt_err_FILE,
  "curl_easy_setopt expects a 'FILE *' argument for this option")
CURLWARNING(_curl_easy_setopt_err_postfields,
  "curl_easy_setopt expects a 'void *' or 'char *' argument for this option")
CURLWARNING(_curl_easy_setopt_err_curl_httpost,
              "curl_easy_setopt expects a 'struct curl_httppost *' "
              "argument for this option")
CURLWARNING(_curl_easy_setopt_err_curl_mimepost,
              "curl_easy_setopt expects a 'curl_mime *' "
              "argument for this option")
CURLWARNING(_curl_easy_setopt_err_curl_slist,
  "curl_easy_setopt expects a 'struct curl_slist *' argument for this option")
CURLWARNING(_curl_easy_setopt_err_CURLSH,
  "curl_easy_setopt expects a CURLSH* argument for this option")

CURLWARNING(_curl_easy_getinfo_err_string,
  "curl_easy_getinfo expects a pointer to 'char *' for this info")
CURLWARNING(_curl_easy_getinfo_err_long,
  "curl_easy_getinfo expects a pointer to long for this info")
CURLWARNING(_curl_easy_getinfo_err_double,
  "curl_easy_getinfo expects a pointer to double for this info")
CURLWARNING(_curl_easy_getinfo_err_curl_slist,
  "curl_easy_getinfo expects a pointer to 'struct curl_slist *' for this info")
CURLWARNING(_curl_easy_getinfo_err_curl_tlssesssioninfo,
              "curl_easy_getinfo expects a pointer to "
              "'struct curl_tlssessioninfo *' for this info")
CURLWARNING(_curl_easy_getinfo_err_curl_certinfo,
              "curl_easy_getinfo expects a pointer to "
              "'struct curl_certinfo *' for this info")
CURLWARNING(_curl_easy_getinfo_err_curl_socket,
  "curl_easy_getinfo expects a pointer to curl_socket_t for this info")
CURLWARNING(_curl_easy_getinfo_err_curl_off_t,
  "curl_easy_getinfo expects a pointer to curl_off_t for this info")


static void h1_tunnel_go_state(char *cf,
                               char *ts,
                               int new_state,
                               char *data)
{
  switch(new_state) {
  case 1:
    cf = "world!";
    FALLTHROUGH();

  case 2:
    ts = "welcome!";
    FALLTHROUGH();

  case 3:
    data = "hello";
    break;
    
  }
}

int main() {
    return 0;
}