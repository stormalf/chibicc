#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated PostgreSQL memory allocation functions
void *palloc(size_t size) {
    return malloc(size);
}

char *pstrdup(const char *str) {
    return strdup(str);
}

void
ParseLongOption(const char *string, char **name, char **value)
{
    size_t equal_pos;
    char *cp;

    equal_pos = strcspn(string, "=");

    if (string[equal_pos] == '=')
    {
        *name = palloc(equal_pos + 1);
        strlcpy(*name, string, equal_pos + 1);

        *value = pstrdup(&string[equal_pos + 1]);
    }
    else
    {
        /* no equal sign in string */
        *name = pstrdup(string);
        *value = NULL;
    }

    for (cp = *name; *cp; cp++)
        if (*cp == '-')
            *cp = '_';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s --option\n", argv[0]);
        return 1;
    }

    char *name = NULL;
    char *value = NULL;

    ParseLongOption(argv[1], &name, &value);

    printf("Parsed Name: %s\n", name);
    if (value != NULL)
        printf("Parsed Value: %s\n", value);
    else
        printf("No value provided.\n");

    // Free allocated memory
    free(name);
    free(value);

    return 0;
}
