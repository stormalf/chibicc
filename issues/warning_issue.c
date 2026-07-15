#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *palloc(size_t size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

static const char *fix_locale(const char *loc_str, const char *lang)
{
    char *fixed_str = NULL;

    if (strcmp(lang, "und") == 0) {
        const char *remainder = loc_str + strlen("und");

        fixed_str = palloc(strlen("root") + strlen(remainder) + 1);
        strcpy(fixed_str, "root");
        strcat(fixed_str, remainder);

        loc_str = fixed_str;
    }

    return loc_str;
}

int main(void)
{
    const char *result;

    /* Basic replacement */
    result = fix_locale("und", "und");
    assert(strcmp(result, "root") == 0);
    free((void *)result);

    /* Preserve suffix */
    result = fix_locale("und-US", "und");
    assert(strcmp(result, "root-US") == 0);
    free((void *)result);

    result = fix_locale("und_Latn_US", "und");
    assert(strcmp(result, "root_Latn_US") == 0);
    free((void *)result);

    /* No replacement */
    result = fix_locale("en-US", "en");
    assert(strcmp(result, "en-US") == 0);

    puts("OK");
    return 0;
}
