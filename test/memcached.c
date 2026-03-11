#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

/* --- Memcached binary protocol helpers --- */

struct mc_header {
    uint8_t  magic;
    uint8_t  opcode;
    uint16_t keylen;
    uint8_t  extlen;
    uint8_t  datatype;
    uint16_t status;
    uint32_t bodylen;
    uint32_t opaque;
    uint64_t cas;
} __attribute__((packed));

static void send_binary_set(int fd, const char *key, const char *val, size_t vlen) {
    struct mc_header h;
    memset(&h, 0, sizeof(h));

    h.magic   = 0x80;        // request
    h.opcode  = 0x01;        // SET
    h.keylen  = htons(strlen(key));
    h.extlen  = 8;           // flags + expiration
    h.bodylen = htonl(8 + strlen(key) + vlen);

    uint32_t flags = htonl(0);
    uint32_t exptime = htonl(0);

    write(fd, &h, sizeof(h));
    write(fd, &flags, 4);
    write(fd, &exptime, 4);
    write(fd, key, strlen(key));
    write(fd, val, vlen);

    struct mc_header resp;
    read(fd, &resp, sizeof(resp));
}

static int send_binary_get(int fd, const char *key, char *buf, size_t buflen) {
    struct mc_header h;
    memset(&h, 0, sizeof(h));

    h.magic  = 0x80;
    h.opcode = 0x00;       // GET
    h.keylen = htons(strlen(key));
    h.bodylen = htonl(strlen(key));

    write(fd, &h, sizeof(h));
    write(fd, key, strlen(key));

    struct mc_header resp;
    int r = read(fd, &resp, sizeof(resp));
    if (r <= 0)
        return -1;

    uint32_t bl = ntohl(resp.bodylen);
    if (bl > buflen)
        bl = buflen;

    // extlen (flags) = 4 bytes
    if (bl > 4) {
        uint32_t tmp;
        read(fd, &tmp, 4);
        return read(fd, buf, bl - 4);
    }

    return 0;
}

/* ---- Worker thread: repeatedly set/get large values ---- */

static void worker(const char *host, int port, int worker_id) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) _exit(1);

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port   = htons(port);
    inet_pton(AF_INET, host, &sa.sin_addr);

    if (connect(fd, (struct sockaddr*)&sa, sizeof(sa)) < 0)
        _exit(2);

    printf("[worker %d] connected\n", worker_id);

    char *large = malloc(2 * 1024 * 1024); // 2MB payload -> triggers extstore
    memset(large, 'A' + (worker_id % 26), 2 * 1024 * 1024);

    char recvbuf[2 * 1024 * 1024];

    for (int i = 0; i < 100; i++) {
        send_binary_set(fd, "ext_key", large, 2 * 1024 * 1024);
        int got = send_binary_get(fd, "ext_key", recvbuf, sizeof(recvbuf));
        if (got <= 0) {
            printf("[worker %d] GET failed at iteration %d\n", worker_id, i);
            _exit(3);
        }
    }

    printf("[worker %d] done\n", worker_id);
    close(fd);
    _exit(0);
}

/* ---- Main ---- */

int main(int argc, char **argv) {
    const char *host = "127.0.0.1";
    int port = 11211;
    int workers = 4;

    printf("Starting synthetic binary-extstore test\n");

    for (int i = 0; i < workers; i++) {
        pid_t pid = fork();
        if (pid == 0)
            worker(host, port, i);
    }

    int status;
    while (wait(&status) > 0) {
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
            printf("Worker exited with failure\n");
    }

    printf("All workers done\n");
    return 0;
}
