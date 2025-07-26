#include <stdio.h>

int main() {
    FILE *f = fopen("issues/topology.txt", "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    char line[128];
    int sockets = 0;
    int cores = 0;

    while (fgets(line, sizeof(line), f)) {
        int n;
        if (sscanf(line, "sockets %d", &n) == 1) {
            sockets = n;
        } else if (sscanf(line, "cores %d", &n) == 1) {
            cores = n;
        }
    }
    fclose(f);

    printf("sockets = %d\n", sockets);
    printf("cores = %d\n", cores);

    return 0;
}
