#include <assert.h>
int main(void) {
        unsigned int k = sizeof("z");
        union {
                char b[k];
        } w = { .b = "z" };
        assert(w.b[0] == 'z' && w.b[1] == '\0');

        return 0;
}