#include "cut_socket.h"

ssize_t __cut_socket_write(struct _reent *r, void *fd, const char *ptr, size_t len)
{
    int sockfd = *(int *) fd;
    int rc     = RPLWRAP(send)(sockfd, ptr, len, 0);
    return (ssize_t) __cut_get_nsysnet_result(r, rc);
}
