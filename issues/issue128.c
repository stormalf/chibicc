#include <netinet/in.h>

struct fdinfo
{
    int fd;
    int lasterr;
    union sockaddr_u remoteaddr;
    socklen_t ss_len;
};

typedef struct fd_list
{
    struct fdinfo *fds;
    int nfds, maxfds, fdmax;
    int state; /* incremented each time the list is modified */
} fd_list_t;

struct fdinfo *get_fdinfo(const fd_list_t *fdl, int fd)
{
    int x;

    for (x = 0; x < fdl->nfds; x++)
        if (fdl->fds[x].fd == fd)
            return &fdl->fds[x];

    return NULL;
}
static fd_list_t client_fdlist, broadcast_fdlist;

struct sockaddr_storage
{
    __SOCKADDR_COMMON(ss_); /* Address family, etc.  */
    char __ss_padding[_SS_PADSIZE];
    __ss_aligntype __ss_align; /* Force desired alignment.  */
};

union sockaddr_u
{
    struct sockaddr_storage storage;
    struct sockaddr_in in;
    struct sockaddr_in6 in6;
    struct sockaddr sockaddr;
};

int main(void)
{
    int socket_accept = 0;
    struct fdinfo *lfdi = get_fdinfo(&client_fdlist, socket_accept);
    union sockaddr_u localaddr = lfdi->remoteaddr;

    return 0;
}
