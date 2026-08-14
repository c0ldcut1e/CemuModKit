#include "cut_socket.h"

ssize_t __cut_socket_read(struct _reent *r, void *fd, char *ptr, size_t len)
{
    int sockfd = *(int *) fd;
    int rc     = RPLWRAP(recv)(sockfd, ptr, len, 0);
    return (ssize_t) __cut_get_nsysnet_result(r, rc);
}
