#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Your storebuffer function as provided
static int storebuffer(int output, FILE *data) {
    char **buffer = (char **)data;
    unsigned char outc = (unsigned char)output;
    **buffer = outc;
    (*buffer)++;
    return outc; // act like fputc()
}

// Dummy dprintf_formatf replacement for testing (just calls vsnprintf internally)
int dprintf_formatf(char **buffer_ptr, int (*output_func)(int, FILE *), const char *fmt, va_list ap) {
    // We'll just format into a temp buffer, then call output_func per char:
    char tmp[1024];
    int len = vsnprintf(tmp, sizeof(tmp), fmt, ap);
    if (len < 0) return len;

    for (int i = 0; i < len; i++) {
        output_func(tmp[i], (FILE *)buffer_ptr);
    }
    return len;
}

int curl_msprintf(char *buffer, const char *format, ...) {
    va_list ap_save;
    int retcode;
    va_start(ap_save, format);
    retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
    va_end(ap_save);
    *buffer = 0;  // Null-terminate the string
    return retcode;
}

int main(void) {
    char buf[256];
    unsigned short val = 65535;

    int len = curl_msprintf(buf, "Value: %hu", val);

    printf("Formatted length: %d\n", len);
    printf("Formatted string: '%s'\n", buf);

    if (len > 0 && strcmp(buf, "Value: 65535") == 0) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }

    return 0;
}
