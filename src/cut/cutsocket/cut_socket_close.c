#include "cut_socket.h"

int __cut_socket_close(struct _reent *r, void *fd)
{
    int sockfd = *(int *) fd;
    int rc     = RPLWRAP(socketclose)(sockfd);
    return __cut_get_nsysnet_result(r, rc);
}
