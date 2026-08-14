#include "cut_socket.h"

ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
    int rc;
    sockfd = __cut_get_nsysnet_fd(sockfd);
    if (sockfd == -1)
    {
        return -1;
    }
    rc = RPLWRAP(recv)(sockfd, buf, len, flags);
    return (ssize_t) __cut_get_nsysnet_result(NULL, rc);
}
