#include "cut_socket.h"

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int rc;
    sockfd = __cut_get_nsysnet_fd(sockfd);
    if (sockfd == -1)
    {
        return -1;
    }
    rc = RPLWRAP(getsockname)(sockfd, addr, addrlen);
    return __cut_get_nsysnet_result(NULL, rc);
}
