#include <stdint.h>
typedef uintptr_t Datum;

extern Datum
numeric_abbrev_convert_var(const char *var, char *nss);

int main() {
    return 0;
}